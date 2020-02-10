# Hardware 

![Clone of Digispark ATtiny85 USB development board][image]

The board is a [clone of a Digispark USB development board][board] with an
[ATtiny85 microcontroller][attiny85]. For your convenience, this board has been
pre-flashed with [micronucleus v2.04a][micronucleus] (an Arduino IDE compatible
bootloader).  In other words, you can program this board using the Arduino IDE,
if you [configure the Arduino IDE accordingly][digistump] (Use Digispark
default - 16.5Mhz).  (Caveat: the instructions found above do not seem to work
out of the box with the latest micronucleus bootloader, but I'm sure [you can
figure it out][reflash])

If for some reason you want to install a different bootloader, that is also an
option, but you will need to [reflash the bootloader using ISP][reflash]. For
this purpose you can e.g. use another Arduino board (Arduino Uno or Nano will
work for sure)

[board]: http://pan.baidu.com/s/1dD0Do57
[digistump]: https://digistump.com/wiki/digispark/tutorials/connecting
[attiny85]: http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-2586-AVR-8-bit-Microcontroller-ATtiny25-ATtiny45-ATtiny85_Datasheet.pdf
[micronucleus]: https://github.com/micronucleus/micronucleus
[reflash]: http://westsideelectronics.com/attiny85-easy/
[image]: board.jpg
