# DB 2.x - Firmware

This is the firmware repository for the Development Board 2 of the [Plastic Scanner](https://plasticscanner.com/) project. More technical information and resources are available on the [documentation](https://docs.plasticscanner.com) webpage.



## Prerequisites

In order to build and flash the firmware you will need **PlatformIO**, a cross-platform embedded development toolset. See installation instructions [here](https://platformio.org/install/).

It is available as a plugin to many popular text editors and IDEs, so installing it can be as easy as one-click-plugin-installation (PlatformIO IDE).
Or, if you prefer a minimal installation and pure command-line usage, install PlatformIO Core (e.g. `sudo apt install platformio` on Ubuntu linux).



## Building and uploading the firmware

We use PlatformIO build system for compiling, uploading and debugging the firmware. Find the *Build* and *Upload* buttons in the PlatformIO IDE or use the following command-line tools (within this repository):

```
$ pio run					# build fw image
$ pio run -t upload 		# build and upload fw image
```

The compiled firmware image is placed in `.pio/build/<board>/firmware.hex`.  
Compilation options can be tweaked in *platformio.ini* file (see [build options](https://docs.platformio.org/en/latest/projectconf/section_env_build.html)).



## Usage

Connect your DB2.x to your laptop, build and flash the firmware and open the serial console (e.g. `$ pio device monitor` or your favourite app like Putty, screen, minicom, picocom...). 

Following commands are implemented:
`LED <number> <state>` for toggling leds on/off. Example `LED 1 ON`  
`ADC` reads a adc float value. TODO clarify better.  
`SCAN` starts a scanning sequence, flashing each led measuring adc and moving on.


