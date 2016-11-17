# da14580_host_app
This is a da14580 host application and control the chip via UART/SPI(planed).
The project is built on cygwin and is supposed to work on Linux.

## How To Test it
You must have a da14580 board with UART port connected to PC. (Only 3 wires needed)
Normally you can connect da14580's UART port to PC through a USB serail port module like FT232/CP2102/PL2303 etc.
Besides, you must download an appropiate binary to da14580 which is configured to use "external processor" mode in the SDK. (I will add the target code later.)
