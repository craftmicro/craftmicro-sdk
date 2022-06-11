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

The examples use an ILI9341 TFT display over SPI, and so require the SPI Arduino library. This comes bundled with Arduino Studio and PlatformIO, and almost any other Arduino-based framework that you might use. The readme in the examples section contains details of how to add dependencies.

## Minimum requirements

Tested on:
- [Teensy 3.6](https://www.pjrc.com/store/teensy36.html)
- [ESP32](https://www.espressif.com/en/products/socs/esp32) ([TTGO T-Display](http://www.lilygo.cn/prod_view.aspx?Id=1126))

Recommend at least:

 1. 16kB RAM
 2. 128kB of Flash (Storage for music and graphics etc)

_Minimum requirements are as-yet untested. This section will be updated as new devices are tested._

To keep memory usage low, this SDK uses a linebuffer (double-buffered) instead of a full framebuffer for rendering graphics to the screen. This only requires 6 * display_width bytes of RAM. E.g. A 320 width displays scaled to 4x4 pixels (resulting in 80 pixels) requires a 480 byte linebuffer.

## Licence

Both the software and hardware components of this project are released under the **[MIT licence](https://en.wikipedia.org/wiki/MIT_License)**.

## Acknowledgements

Code from many authors has contributed to Craft Micro. This project would not be possible without them. There are too many people to thank, but a special shout-out goes to [Adafruit industries](https://www.adafruit.com/) for their amazing, comprehensive and well-written [software libraries](https://github.com/adafruit).
