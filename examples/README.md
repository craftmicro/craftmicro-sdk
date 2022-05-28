# Craft Micro SDK - Examples

Craft Micro uses the Arduino framework, so any IDE that uses this framework should be work.

Below are examples for two common tools, PlatformIO and the Arduino IDE. Craft Micro highly recommends [PlatformIO](https://platformio.org) for cross-platform microprocessor development.

## Run the examples using PlatformIO

### One-time setup
1. Install [VSCode (Visual Studio Code)](https://code.visualstudio.com/download) and the [PlatformIO IDE (plugin for VSCode)](https://platformio.org/platformio-ide)
2. Clone Craft Micro SDK from github. In these examples we clone it to `C:/libraries/craftmicro-sdk`

### Project setup
1. [Create a new PlatformIO project](https://docs.platformio.org/en/stable/integration/ide/vscode.html#quick-start)
2. Choose a location and your dev board, and select `arduino` as the framework (*)
3. Once the project has been created, edit `platformio.ini`
    1. Add `lib_extra_dirs` with the path to where you cloned the Craft Micro SDK (**)
    2. Add `lib_deps` and specify the `SPI` library (required for the ILI9341 TFT display)
    3. See below for what your ini file might look like
4. Copy and paste on of the example `main.cpp` files into your project's `src` directory
5. Build and deploy!

In our example we are targetting the Teensy 3.6 dev board. Our `platformio.ini` looks like this:

```
[env:teensy36]
platform = teensy
board = teensy36
framework = arduino
lib_extra_dirs =
    C:/libraries/
lib_deps =
    SPI
```

_(*) Only the Arduino framework is supported at this time. You will not be able to target boards that do not support the Arduino framework._

_(**) Note that the path should be to the library folder (the parent of the Craft Micro folder), not to the Craft Micro folder itself_

## Run the examples using Arduino IDE

### One-time setup
1. Install [Arduino IDE](https://www.arduino.cc/en/software)
2. You may need to install additional tools for your dev board. In our example we are using a Teensy 3.6 board, so we need to [install TeensyDuino](https://www.pjrc.com/teensy/td_download.html).
3. Clone Craft Micro SDK from github into your `Arduino/libraries` folder ([help](https://forum.arduino.cc/t/ino-cant-find-the-library/543190))

### Project setup
1. Run Arduino IDE and create a new sketch if you need to
2. Copy and paste the code from `main.cpp` in one of the examples into your sketch
3. Save the sketch, then open the folder where the sketch is saved and create the subfolders `examples/resources/`
    1. Copy the resources your example needs from `craftmicro-sdk/examples/resources` to `my-sketch/examples/resources`
4. Build and deploy!
