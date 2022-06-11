# Craft Micro SDK - Supported displays

Craft Micro has support for the following TFT displays:

- [ILI9341](#ili9341)
- [ST7789](#st7789)

## ILI9341


```cpp
craft::Display = new DisplayILI9341(
    DisplaySize::Size135x240,   // Pixel size of the display
    10,                         // Chip select pin (CS/SS)
    15,                         // Data/Command pin (DC)
    4,                          // Reset pin (RST). Optional (can pass in PIN_UNUSED)
    11,                         // Master-in/Slave-out pin (MOSI)
    13,                         // Clock pin (SCLK)
    12,                         // Slave-out/Master-in pin (MISO)
    6,                          // Backlight pin. Optional (can pass in PIN_UNUSED)
    PixelScale::x1              // Pixel scaling. Optional (default is PixelScale::x1)
);
```

Only the SPI interface is supported at this time.

## ST7789

```cpp
craft::Display = new DisplayST7789(
    DisplaySize::Size320x240,   // Pixel size of the display
    5,                          // Chip select pin (CS/SS)
    16,                         // Data/Command pin (DC)
    23,                         // Reset pin (RST). Optional (can pass in PIN_UNUSED)
    19,                         // Master-in/Slave-out pin (MOSI)
    18,                         // Clock pin (SCLK)
    4,                          // Backlight pin. Optional (can pass in PIN_UNUSED)
    PixelScale::x1              // Pixel scaling. Optional (default is PixelScale::x1)
);
```

Only the SPI interface is supported at this time.
