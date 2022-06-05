# Craft Micro SDK

![Craft Micro logo](logo.png?raw=true "Craft Micro")

The Craft Micro SDK is a code library for rapid development of graphical apps for microprocessor-based systems. The various individual libraries that make up this library (such as display and drawing libraries) might also be useful in other projects.

Craft Micro maintains an open-source software library and set of plans to craft your own microprocessor-based handheld gaming console.

Craft Micro is based on the Arduino Framework. We recommend the [PlatformIO](https://platformio.org/) plugin for VSCode for cross-platform microprocessor development.

## Status

Although it is usable, the Craft Micro SDK is pre-alpha and is not recommended for release. Feel free to try it out and use it for your own projects, but expect to find bugs, and expect parts of the codebase to change without warning.

## Examples and Documentation

A good place to begin with Craft Micro is to check out the [examples](examples/).

Refer to the [documentation](https://craftmicro.io/docs/) for more detail. The docs are also included in the repo.

## Dependencies

Craft Micro itself has no dependencies. However, it's likely that the hardware you are using, such as a TFT display, will require additional libraries - for example SPI or I2C.

The examples use an ILI9341 TFT display over SPI, and so require the SPI Arduino library. This comes bundled with Arduino Studio and PlatformIO, and almost any otther Arduino-based framework that you might use. The readme in the examples section contains details of how to add dependencies.

## Minimum requirements

Only tested on Teensy 3.6 but should work on T3.5 and other lower-memory teensy devices. Working on ESP32 support.

Examples should work with:

 1. 8kB RAM
 2. 48kB of Flash (Storage for music and graphics etc)

Recommend at least:

 1. 16kB RAM
 2. 128kB of Flash (Storage for music and graphics etc)

The library uses a linebuffer (double-buffered) instead of a full framebuffer for rendering graphics to the screen. This only requires 6 * display_width bytes of RAM. E.g. A 320 width displays scaled to 4x4 pixels (resulting in 80 pixels) requires a 480 byte linebuffer.

## Licence

Both the software and hardware components of this project are released under the **[MIT licence](https://en.wikipedia.org/wiki/MIT_License)**.

## Acknowledgements

Code from many authors has contributed to Craft Micro. This project would not be possible without them. These include:

#### Display

* **[Paul Stoffregen](mailto:)** - [ILI9341_t3](https://github.com/PaulStoffregen/ILI9341_t3)
* **[KurtE](mailto:)** - [ILI9341_t3n](https://github.com/KurtE/ILI9341_t3n)
* **[Frank Boesing](mailto:)** - [ILI9341_t3DMA](https://github.com/FrankBoesing/ILI9341_t3DMA)
* **[Adafruit industries](https://www.adafruit.com/)** - [Various libraries](https://github.com/adafruit) 

#### Graphics and animation

* **[Warren Moore](mailto:wm@warrenmoore.net)** - [AHEasing](https://github.com/warrenm/AHEasing)
* **[Rosetta Code](https://rosettacode.org/wiki/Rosetta_Code)** - [Wu's algorithm](https://rosettacode.org/wiki/Xiaolin_Wu%27s_line_algorithm)

#### Audio

* **[Romain "Artefact2" Dalmaso](mailto:artefact2@gmail.com)** - [libxm](https://github.com/Artefact2/libxm)

#### Support

* **[Teensy support forums](https://forum.pjrc.com/)**

#### Hardware

* **[Teensy microprocessor boards](https://www.pjrc.com/teensy/)**
* **[BuyDisplay](https://www.buydisplay.com)** - [ILI9341 TFT module](https://www.buydisplay.com/default/3-2-inch-capacitive-touchscreen-240x320-tft-lcd-module-display) - [ILI9488 TFT module](https://www.buydisplay.com/default/lcd-3-5-inch-320x480-tft-display-module-optl-touch-screen-w-breakout-board)