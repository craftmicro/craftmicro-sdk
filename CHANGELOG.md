# Craft Micro SDK change log

## v0.4.0 (WIP)

- Performance improvements (now 40644)
  - Implemented pixel stack to render pipeline
  - Improvements to pixel draw routine

## v0.3.0

Craft Micro SDK now supports a user-supplied framebuffer. This can be used with libraries like [GFX Library for Arduino](https://github.com/moononournation/Arduino_GFX) to drive ESP32 displays without graphics RAM, such as the ST7701S. [See an example of this in action](https://github.com/craftmicro/craftmicro-examples/tree/main/ZX2D10GE01R-V4848-PIO).

**Breaking changes**

- Changed display adapter method signatures
- Linebuffer height argument removed from display

**Changes**

- Added support for user-provided framebuffer
- Fixed: Linebuffer size other than 1 not working

**Known bugs**

- GUI library not working

## v0.2.0

Craft Micro SDK now supports a user-supplied display object, giving the user choice of display library to use. It's been tested with Bodmer's [TFT_eSPI](https://github.com/Bodmer/TFT_eSPI) (see [example](https://github.com/craftmicro/craftmicro-examples/tree/main/TTGO-T-Display-PIO)) as well as the [GFX Library for Arduino](https://github.com/moononournation/Arduino_GFX) (see [example](https://github.com/craftmicro/craftmicro-examples/tree/main/ZX2D10GE01R-V4848-PIO)).

**Changes**

- Abstracted display away from library (user now supplies interface)
- Added animated sprite format (and Aseprite script to generate them)
- Fixed text rendering

**Known bugs**

- GUI library not working
- Linebuffer size other than 1 not working
