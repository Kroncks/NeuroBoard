#include <NeuroBoard.h>
#include <WiFi.h>
#include <WebServer.h>


static const char* WIFI_SSID = "NeuroBoard-ALL-IN";
static const char* WIFI_PASS = "12345678";


WebServer server(80);
WiFiServer streamServer(81);


static const char INDEX_HTML[] PROGMEM = R"html(
<!DOCTYPE html><html>
<head>
<meta charset="utf-8">
<title>NeuroBoard ALL-IN</title>
<style>
  body{margin:0;background:#111;color:#eee;font-family:sans-serif;display:flex;flex-direction:column;align-items:center;padding:20px}
  h2{margin:0 0 12px}
  .row{display:flex;gap:12px;flex-wrap:wrap;justify-content:center;margin:12px 0}
  button{border:0;border-radius:8px;padding:12px 18px;font-size:1rem;cursor:pointer;color:#fff;background:#2d6cdf}
  button.green{background:#1f9d55}
  img{max-width:100%;border:2px solid #333;border-radius:8px;background:#000}
  #status{min-height:1.4em;color:#aaa}
</style>
</head>
<body>
<h2>NeuroBoard ALL-IN</h2>
<img id="live">
<div class="row">
  <button onclick="snap()">Snapshot</button>
  <button class="green" onclick="saveSD()">Save to SD</button>
</div>
<div id="status"></div>
<img id="snap" style="display:none">
<script>
  const ip = location.hostname;
  document.getElementById('live').src = 'http://' + ip + ':81';
  function snap(){
    const img = document.getElementById('snap');
    img.style.display = 'block';
    img.src = '/capture?t=' + Date.now();
  }
  function saveSD(){
    const status = document.getElementById('status');
    status.textContent = 'Saving...';
    fetch('/save').then(r => r.text()).then(t => status.textContent = t).catch(() => {
      status.textContent = 'Save failed';
    });
  }
</script>
</body></html>
)html";


static void setLed(uint8_t r, uint8_t g, uint8_t b)
{
    NeuroBoard.setRGB(r, g, b);
}


static bool savePhotoToSD()
{
    if(!NeuroBoard.hasCamera() || !NeuroBoard.hasSD())
    {
        return false;
    }

    camera_fb_t* fb = esp_camera_fb_get();
    if(!fb)
    {
        return false;
    }

    char path[32];
    snprintf(path, sizeof(path), "/photo_%lu.jpg", (unsigned long)millis());

    File file = SD_MMC.open(path, FILE_WRITE);
    if(!file)
    {
        esp_camera_fb_return(fb);
        return false;
    }

    bool ok = file.write(fb->buf, fb->len) == fb->len;
    file.close();
    esp_camera_fb_return(fb);

    return ok;
}


static void handleRoot()
{
    server.send_P(200, "text/html", INDEX_HTML);
}


static void handleCapture()
{
    if(!NeuroBoard.hasCamera())
    {
        server.send(503, "text/plain", "Camera not available");
        return;
    }

    camera_fb_t* fb = esp_camera_fb_get();
    if(!fb)
    {
        server.send(503, "text/plain", "Camera capture failed");
        return;
    }

    server.sendHeader("Content-Disposition", "inline; filename=capture.jpg");
    server.send_P(200, "image/jpeg", (const char*)fb->buf, fb->len);
    esp_camera_fb_return(fb);
}


static void handleSave()
{
    if(!NeuroBoard.hasCamera())
    {
        server.send(503, "text/plain", "Camera not available");
        return;
    }

    if(!NeuroBoard.hasSD())
    {
        server.send(503, "text/plain", "SD card not available");
        return;
    }

    if(!savePhotoToSD())
    {
        server.send(500, "text/plain", "Failed to save photo");
        return;
    }

    server.send(200, "text/plain", "Photo saved to SD");
}


static void handleNotFound()
{
    server.send(404, "text/plain", "Not found");
}


static void streamTask(void*)
{
    for(;;)
    {
        WiFiClient client = streamServer.accept();
        if(!client)
        {
            vTaskDelay(1);
            continue;
        }

        while(client.connected())
        {
            String line = client.readStringUntil('\n');
            if(line == "\r" || line.isEmpty())
            {
                break;
            }
        }

        client.print(
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: multipart/x-mixed-replace; boundary=frame\r\n"
            "Access-Control-Allow-Origin: *\r\n\r\n"
        );

        while(client.connected() && NeuroBoard.hasCamera())
        {
            camera_fb_t* fb = esp_camera_fb_get();
            if(!fb)
            {
                vTaskDelay(1);
                continue;
            }

            client.printf(
                "--frame\r\nContent-Type: image/jpeg\r\nContent-Length: %u\r\n\r\n",
                fb->len
            );
            client.write(fb->buf, fb->len);
            client.print("\r\n");
            esp_camera_fb_return(fb);
        }

        client.stop();
    }
}


void setup()
{
    NeuroBoard.begin();
    setLed(255, 165, 0);

    WiFi.softAP(WIFI_SSID, WIFI_PASS);
    delay(300);

    NeuroBoard.logMessagef("[AP] %s", WiFi.softAPIP().toString().c_str());

    bool cameraOk = NeuroBoard.initCamera();
    bool sdOk = NeuroBoard.initSD();

    if(cameraOk)
    {
        sensor_t* sensor = esp_camera_sensor_get();
        sensor->set_vflip(sensor, 0);
        sensor->set_hmirror(sensor, 0);
        sensor->set_framesize(sensor, FRAMESIZE_QVGA);
    }

    if(cameraOk && sdOk)
    {
        setLed(0, 255, 0);
    }
    else
    {
        setLed(255, 0, 0);
    }

    server.on("/", handleRoot);
    server.on("/capture", handleCapture);
    server.on("/save", handleSave);
    server.onNotFound(handleNotFound);
    server.begin();

    streamServer.begin();
    xTaskCreatePinnedToCore(streamTask, "stream", 4096, nullptr, 1, nullptr, 0);

    NeuroBoard.logMessagef("[HTTP] Ready");
}


void loop()
{
    server.handleClient();
}