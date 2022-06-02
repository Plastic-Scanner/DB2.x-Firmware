# DB 2.x - Firmware

This is the firmware repository for the DB2.X (development board) of the Plastic Scanner project. More technical information is in the [docs](docs.plasticscanner.com) and general information about project on our [website](plasticscanner.com).



## Requirements

Firmware runs on DB2.x (tested on DB2.1), powered by Arduino.
Requires **PlatformIO**, a cross-platform embedded development toolset. See installation instructions [here ](https://platformio.org/install/)it can be as easy as one-click-plugin-installation (PlatformIO IDE).

In order to build and upload the firmware to DB2.x, connect the board to computer and find the *Build* and *Upload* buttons in the PlatformIO IDE OR use the following commands:

```
$ pio run -t upload 		# build and upload fw image
```

The compiled firmware image is placed in `.pio/build/<board>/firmware.hex`.  
Compilation options can be tweaked in *platformio.ini* file (see [build options](https://docs.platformio.org/en/latest/projectconf/section_env_build.html)).



## Usage

Connect your DB2.x to your laptop, build and flash the firmware and open the serial console with `$ pio device monitor` or your favourite app (e.g Putty, screen, minicom, picocom...). Enable local echo in order to see commands you're typing by adding `--echo` to command above, or pressing CTRL+T followed by CTRL+E while running it.

User can send commands like this:

```
> scan
```

which outputs a full scan, 8 values, one for each LED.

See app/main.cpp at `setup()` function which commands are defined or type `help` to list all commands.



## Development

Feedback on architecture and implementation is welcome. Firmware currently controls an Arduino, which "talks" to an ADC chip and a LED driver, communicating via the serial interface. In directory `app` are the main sources, `test` is for unit tests (which needs much more love and actual tests), `drivers` contains custom drivers for componments on board.

NOTE about drivers: at the moment, we use custom driver for the LED driver chip (`drivers/tlc59280`) and want to implement one for the ADC as well. However, at the moment we're using a third party library for the ADC, listed in *platformio.ini* at `[lib_deps]`, with sources located in `.pio/libdeps/uno/`. When a new driver is finished (checkout git branches), it will be stored in `drivers/ads1256` directory.
