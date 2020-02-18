# HidPttEmulator

Windows Form C++ application that reads GPIO input from USB HID devices and emulates keyboard inputs which can be used for setting up push-to-talk (PTT) in VOIP applications. 

![GUI](https://i.gyazo.com/afa12e883e2efc1a81df77fec5098902.png)

--------------

## Example application

A Syba USB sound card with a [C-Media CM119](http://www.repeater-builder.com/voip/pdf/cm119-datasheet.pdf) chip, with two wires soldered to pin 13 (GPIO3) and pin 37 (REGV). The program listens for input on GPIO3, and once input is detected (i.e. the circuit is closed) a continious keyboard press is simulated until the circuit is opened again. A momentary push button is connected to the circuit, and is used as PTT in Skype, while sound is picked up/played from the sound card's mic/headset ports.

![CM119 USB sound card](https://i.gyazo.com/e9b390dc40d5dd1295871ceb6926e674.png)

The software is only tested with sound cards that comes with the C-Media CM108 and CM119 chip. 

## Binaries

Pre-built binaries can be found in the [Release](/Release/) directory. All files in this folder must be downloaded and put in the same directory. 

If your device is not detected by the application, make sure that `vid` (vendor ID) and `pid` (product ID) in the `Settings.ini`-file are set correctly for your device. These values can be found in Windows device manager. The `gpio_id` is used to specify the GPIO input you want to use. By default the file is configured for the Syba USB sound card, with GPIO3 as the input.  

## Libraries used
- http://github.com/signal11/hidapi

## Related links
- http://www.repeater-builder.com/projects/fob/syba-small-fob.html
- http://www.marrold.co.uk/2018/04/converting-cm108-usb-fob-for-amateur.html
