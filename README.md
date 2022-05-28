# Craft Micro SDK

![mac logo](logo.png?raw=true "mac")

The Craft Micro SDK is a code library for rapid development of graphical apps for microprocessor-based systems. The various individual libraries that make up this library (such as display and drawing libraries) might also be useful in other projects.

Craft Micro maintains an open-source software library and set of plans to craft your own microprocessor-based handheld gaming console.

## Status

This library is pre-alpha and is not ready for release. Large parts of the codebase may change without warning.

## Examples and Documentation

A good place to begin with Craft Micro is to check out the [examples](examples/).

Then take a look at the [documentation](https://craftmicro.io/docs/) for more detail!

## Developer notes 2022-03-19
### TODO next
- Improve linebuffer for speed
- Improve portability
- Vector rendering
- Radial gradient
- Sprite stamping, animation, rotation
- Attempt to measure RAM usage
- ESP32 support

## Change history
 - **2022-03-19** Added masks (and inverse masks)
 - **2022-03-18** Refactored memory pooling and linked lists to use templated classes
 - **2022-03-18** Added ability to set any size buffer (from single line to full frame)
 - **2022-03-17** Filters (shaders) for tint, HSV, colormask, lighten/darken. Variable height framebuffer
 - **2022-03-16** Working linear gradient.
 - **2022-03-10** Refactored line buffer and display implementation.
 - **2021-09-19** Reorganised codebase into subfolders.
 - **2021-05-25** Completely refactored to stage and display list approach (like Flash).
 - **2021-04-27** Completely rewritten to convert framebuffer to linebuffer.
 - **2019-04-14** Many bitmap and vector features implemented. Working on GUI components.
 - **2018-04-24** Very much a work in progress. Only display components currently implemented.

## Prerequisites

Only tested on Teensy 3.6 but should work on T3.5 and other lower-memory teensy devices.

#### Minimum requirements:

 1. 16kB RAM
 2. 40kB of Flash (Storage for music and graphics etc)

The library uses a linebuffer (double-buffered) instead of a full framebuffer for rendering graphics to the screen. This only requires 6 * display_width bytes of RAM. E.g. A 320 width displays scaled to 4x4 pixels (resulting in 80 pixels) requires a 480 byte linebuffer.

#### Recommended:

 - Teensy 3.6 with 256kB RAM and 1MB Flash

## Licence

Both the software and hardware components of this project are released under the **[MIT licence](https://en.wikipedia.org/wiki/MIT_License)**, except for the various parts by other authors that may have their own licences (for example, libxm is under the WTFPL).

## Acknowledgements

Code from many authors has contributed to Craft Micro. This project would not be possible without them. These include:

#### Display

* **[Paul Stoffregen](mailto:)** - [ILI9341_t3](https://github.com/PaulStoffregen/ILI9341_t3)
* **[KurtE](mailto:)** - [ILI9341_t3n](https://github.com/KurtE/ILI9341_t3n)
* **[Frank Boesing](mailto:)** - [ILI9341_t3DMA](https://github.com/FrankBoesing/ILI9341_t3DMA)

#### Graphics and animation

* **[Warren Moore](wm@warrenmoore.net)** - [AHEasing](https://github.com/warrenm/AHEasing)
* **[Rosetta Code](https://rosettacode.org/wiki/Rosetta_Code)** - [Wu's algorithm](https://rosettacode.org/wiki/Xiaolin_Wu%27s_line_algorithm)

#### Audio

* **[Romain "Artefact2" Dalmaso](mailto:artefact2@gmail.com)** - [libxm](https://github.com/Artefact2/libxm)

#### Support

* **[Teensy support forums](https://forum.pjrc.com/)**

#### Hardware

* **[Teensy microprocessor boards](https://www.pjrc.com/teensy/)**
* **[BuyDisplay](https://www.buydisplay.com)** - [ILI9341 TFT module](https://www.buydisplay.com/default/3-2-inch-capacitive-touchscreen-240x320-tft-lcd-module-display) - [ILI9488 TFT module](https://www.buydisplay.com/default/lcd-3-5-inch-320x480-tft-display-module-optl-touch-screen-w-breakout-board)