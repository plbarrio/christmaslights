# Christmas tree lights

Arduino nano and WS2811 LED strip using FastLED library project, with different animation modes, some original other adapted from FastLED examples, which are:
- Sinusoidal Waves
- Heart Beats
- Random color running up.
- KnightRider
- Alternating odd and even
- Dalí, painter brushes
- Glitter, random brights
- RainDrops
- Lightings
- FLStaticRandom
- FLFirstLight
- FLFire2012
- FLCylon
- FLJuggle

<div class="video-fallback">
  See the video: <a href="https://www.youtube.com/watch?v=vo0XyzPjOzQ">demo</a>.
</div>
<figure class="video-container">
  <iframe src="https://www.youtube.com/embed/vo0XyzPjOzQ" frameborder="0" allowfullscreen="true"> </iframe>
</figure>

## Hardware

It uses an Arduino nano, WS2811 LED strip and a button for changing the different modes.

Check [https://www.instructables.com/id/Arduino-WS2811-Christmas-Tree/](https://www.instructables.com/id/Arduino-WS2811-Christmas-Tree/) for instructions

### Bill Of Materials (BOM)

- [Arduino nano](https://aliexpress.com/item/32531372300.html). I ordered one with pins unsoldered since I soldered directly on the board. 
- [WS2811 50 LED strip](https://aliexpress.com/item/32444134206.html). There are also with [green cables](https://aliexpress.com/item/32444382333.htm) that are more discrete. 
- [Switch](https://aliexpress.com/item/32964605422.html). One with a long button is better. 
- USB charger. A used one from a cellular phone.  
- USB Cable type A male <-> type mini-B male. Reused from an old camera.  
- Plastic box. Reused a candy one.  
- A cable tie.  
- Three-wire cable.  
- Soldering tin.  
- Glue for the glue gun.
- Insulating tape
- Heat shrink tube

### Wiring

<img src="img/wiring.svg" alt="wiring"  />

#### Power

Everything is powered through the USB connector. The LED strip is powered through the _VIN_ pin for not overloading the voltage regulator.

#### LED Strip

There are many types of addressable LED strips. The ones based in WS281x are very common. This chip family makes the Pulse Width Modulation ( [PWM](https://en.wikipedia.org/wiki/Pulse-width_modulation) ) for you for each color, based on the data received in the data input pin. It uses the first block of data with every color and pushes the rest of the data flow to the next chip trough the data out pin. Fortunately, there are Arduino libraries that make all this work transparent for you.

|Arduino	|LED strip  |  Notes  |
|:---------:|:---------:|---------|
|VIN		| +5V       | Directly from USB |
|D4         | Din       | 5V logic       |
|GND        | GND       |         |

#### Microcontroller

Since the _WS2811_ LED strip needs a 5V data input we choose an Arduino with 5V logic. A 3.3V one could also be used, but we should make some sort of [logic level adaptation](https://en.wikipedia.org/wiki/Level_shifter). If not, it could work but a little voltage drop could drive to incorrect data or no data at all arriving at the LED strip.

Simpler microcontrollers as [ATtiny85](https://www.microchip.com/wwwproducts/en/ATtiny85) could be used if you want to cut more the cost. Since we only need 1 output and one input. Depending on the versions the flashing is more difficult if it does not have a USB port.

#### Switch

One with a long button will suit better to go through the case, then you can actuate it without a pencil.

It is connected to _GND_ because we use the internal [pull-up resistor](https://en.wikipedia.org/wiki/Pull-up_resistor) in Arduino to avoid false signals. Then in code a 1 will be no pulsated, and 0 pulsated.

## Author
* **Pedro Luis Barrio** - *Initial work* - [gitlab](https://gitlab.com/plbarrio)

## Acknowledgments

* Examples from [Fast Led](http://fastled.io/) library
* [Christmas Lights Arduino and WS2811](https://www.instructables.com/id/Christmas-Lights-Arduino-and-WS2811/) 
* [Arduino Xmass tree](https://visar78.jimdofree.com/)

