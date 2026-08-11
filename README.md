# NeuroBoard
The NeuroBoardS3 library provides a simple interface for controlling the main hardware features of the NeuroBoardS3, including the RGB LED, SD card, and camera.

## API Reference

Use the `NeuroBoard.<function>` syntax to access the library functions.

Example :
```cpp
NeuroBoard.setRGB(0, 122, 123); // set the color of the LED
```

### Summary

| Function                       | Description          |
| ------------------------------ | -------------------- |
| `initRGB()`                    | Initialize RGB LED   |
| `setRGB(r, g, b)`              | Set the RGB LED color|
| `setBrightnessRGB(brightness)` | Set LED brightness   |
| `initSD()`                     | Initialize SD card   |
| `hasSD()`                      | Check SD card status |
| `initCamera()`                 | Initialize camera    |
| `hasCamera()`                  | Check camera status  |

### Components :

---

### RGB LED

#### `initRGB()`

Initializes the RGB LED.

```cpp
NeuroBoard.initRGB();
```

#### `setRGB(uint8_t r, uint8_t g, uint8_t b)`

Sets the RGB LED color.

```cpp
NeuroBoard.setRGB(255, 0, 0);
```

#### `setBrightnessRGB(uint8_t brightness)`

Sets the RGB LED brightness (`0–255`).

```cpp
NeuroBoard.setBrightnessRGB(100);
```

---

### SD Card

#### `initSD()`

Initializes the SD card.

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

## Examples 

You can find the examples of this library :
- On the [GitHub repository](https://github.com/Kroncks/NeuroBoard/tree/main/examples)
- On the [Platformio library page](https://registry.platformio.org/libraries/kroncks/NeuroBoard/examples)
- On the Library tab in PIO Home

- Or you can directly open them through `PIO Home > Project Examples > NeuroBoard` if you have installed the NeuroBoard Platform

*You can install the NeuroBoard Platform with `PIO Home > Platforms > Advanced installation > github.com/Kroncks/NeuroBoard > Install`*
