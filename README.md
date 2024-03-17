# HidPttEmulator

Windows application that reads GPIO input from USB HID devices and emulates keyboard inputs which can be used for setting up push-to-talk (PTT) in VOIP applications. 

![GUI](https://i.gyazo.com/afa12e883e2efc1a81df77fec5098902.png)

--------------

## Example application

A Syba USB sound card with a [C-Media CM119](http://www.repeater-builder.com/voip/pdf/cm119-datasheet.pdf) chip, with two wires soldered to pin 13 (GPIO3) and pin 37 (REGV). The program listens for input on GPIO3, and once input is detected (i.e. the circuit is closed) a continious keyboard press is simulated until the circuit is opened again. A momentary push button is connected to the circuit, and is used as PTT in Skype, while sound is picked up/played from the sound card's mic/headset ports.

![CM119 USB sound card](https://i.gyazo.com/e9b390dc40d5dd1295871ceb6926e674.png)

The program has only been tested with sound cards that comes with the C-Media CM108 and CM119 chip. 

## Running the application

Download HidPttEmulator.zip from [Releases](https://github.com/EvenAR/HidPttEmulator/releases) and unzip all the folders to the same directory on your PC.

### Configuration

In order for the application to detect your USB sound card the `vid` (vendor ID) and `pid` (product ID) in `Settings.ini` must be set correctly. These values can be found by locating your sound card in Windows device manager and looking up "Device instance path":
![image](https://github.com/EvenAR/HidPttEmulator/assets/5177099/78f623d0-194f-4682-af6e-1550753b882f)

Sample config for the CM108 sound card:
```ini
[DEVICE]
vid=0x0d8c       ; vendor id
pid=0x0012       ; product id
gpio_pin=3       ; The GPIO pin number (pin 13 on CM108 is named GPIO3)
reverse_input=1  ; Use 1 if the button press closes the circuit, and 0 if it opens the circuit 
```

## Libraries used
- http://github.com/signal11/hidapi

## Credits
- http://www.repeater-builder.com/projects/fob/syba-small-fob.html
- http://www.marrold.co.uk/2018/04/converting-cm108-usb-fob-for-amateur.html
