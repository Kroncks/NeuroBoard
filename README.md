# NeuroBoard
The NeuroBoardS3 library provides a simple interface for controlling the main hardware features of the NeuroBoardS3, including the RGB LED, SD card, and camera.

## API Reference

Use the `NeuroBoard.<function>` syntax to access the library functions.

Example :
```cpp
NeuroBoard.setLED(0, 122, 123); // set the color of the LED
```

### Summary

| Function                 | Description          |
| ------------------------ | -------------------- |
| `initLED()`              | Initialize RGB LED   |
| `setLED(r, g, b)`        | Set the RGB LED color|
| `setBrightnessLED(b)`    | Set LED brightness   |
| `initSD()`               | Initialize SD card   |
| `hasSD()`                | Check SD card status |
| `initCamera()`           | Initialize camera    |
| `hasCamera()`            | Check camera status  |

| Property | Description                                                          |
| -------- | -------------------------------------------------------------------- |
| `log`    | Enable/disable internal logs printed to `Serial` (`true` by default) |

### Components :

---

### RGB LED

#### `initLED()`

Initializes the RGB LED.

```cpp
NeuroBoard.initLED();
```

#### `setLED(uint8_t r, uint8_t g, uint8_t b)`

Sets the RGB LED color.

```cpp
NeuroBoard.setLED(255, 0, 0);
```

#### `setBrightnessLED(uint8_t brightness)`

Sets the RGB LED brightness (`0–255`).

```cpp
NeuroBoard.setBrightnessLED(100);
```

---

### SD Card

#### `initSD()`

Initializes the SD card.

You can use `NeuroBoard.initSD(true)` to enable formatting when the SD card mount fails.

**Returns:** `true` if successful, otherwise `false`.

```cpp
NeuroBoard.initSD();
```

#### `hasSD()`

Checks if the SD card is initialized.

**Returns:** `true` if available, otherwise `false`.

```cpp
if (NeuroBoard.hasSD()) {
    // SD available
}
```

---

### Camera

#### `initCamera()`

Initializes the camera.

**Returns:** `true` if successful, otherwise `false`.

```cpp
NeuroBoard.initCamera();
```

#### `hasCamera()`

Checks if the camera is initialized.

**Returns:** `true` if available, otherwise `false`.

```cpp
if (NeuroBoard.hasCamera()) {
    // Camera available
}
```

---

### Logging
 
#### `log`
 
Public boolean field. When `true` (default), the library prints internal
status messages to `Serial` (prefixed `[LED]`, `[SD]`, `[CAM]`). Set it to
`false` to silence these logs.
 
```cpp
NeuroBoard.log = false; // disable internal logs
```
 
---

## Examples 

You can find the examples of this library :
- On the [GitHub repository](https://github.com/Kroncks/NeuroBoardS3/tree/main/examples)
- On the [Platformio library page](https://registry.platformio.org/libraries/kroncks/NeuroBoardS3/examples)
- On the Library tab in PIO Home
- On the Packages tab in PIO Home if you have installed it
- Or you can directly open them through `PIO Home > Project Examples > NeuroBoard` if you have installed the NeuroBoard Platform

*You can install the NeuroBoard Platform with `PIO Home > Platforms > Advanced installation > github.com/Kroncks/NeuroBoardS3 > Install`*


#### Expected results of examples

| Example | What it does | Expected result |
|---|---|---|
| `1_LED` | Cycles the onboard LED through red, green, blue | 🔴 **red** → 🟢 **green** → 🔵 **blue**, 1s each, forever |
| `2_SD` | Initializes the SD card and writes `"bonsoir"` to `/test.txt` | 🟠 **orange** if the card doesn't mount<br>🟢 **green** if the mount and the write succeed<br>🔴 **red** otherwise |
| `3_Test_init_camera` | Initializes the camera only | 🟢 **green** if `initCamera()` succeeds<br>🔴 **red** otherwise |
| `4_Photo` | Initializes camera + SD, captures one frame, saves it to `/photo_<ms>.jpg` | 🟢 **green** if capture and save both succeed<br>🟣 **purple** if the camera init fails<br>🟠 **orange** if the SD card init fails<br>🔴 **red** if camera init and SD init fails, or the save fails |
| `5_Demo_complete` | Starts a Wi-Fi AP + web UI with live MJPEG stream, snapshot, and save-to-SD | ⚠️ **YOU NEED TO RENAME THE WIFI NAME FIRST**<br>🟢 **green** once everything is ready<br>🟣 **purple** if the camera init fails<br>🟠 **orange** if the SD card init fails<br>🔴 **red** if both fail |