# Clock Club

*The first rule of Clock Club is that no one checks the time at Clock Club.*

This repository contains information on making clocks and timepieces.

## What You Should Know In Advance

This repo is written for students and scholars of interactive design. It assumes you know a little about computer programming. Examples are written in a few programming frameworks that are common in interaction design programs like NYU's [ITP](https://itp.nyu.edu), where this repo was developed. For further reading on some of the basics we assume, you might want to check out the [ITP Physical Computing Site](https://itp.nyu.edu/physcomp/), the [ITP Fabrication Site](https://itp.nyu.edu/fab/), or the [ITP Intro to Computational Media site](https://github.com/ITPNYU/ICM-2017).

## Tools and Platforms Used in This Repository

* [Arduino](https://www.arduino.cc)
* [p5.js](http://p5js.org/)
* [Raspberry Pi](http://raspberrypi.org/)
* [Vectorworks](http://www.vectorworks.net/) - we rely on the free educational version of Vectorworks' software for [students and educators](http://www.vectorworks.net/education)
* [Bantam Tools](https://www.bantamtools.com/) (formerly Othermill) CNC machines

## Projects In This Repository

* [Clocks in JavaScript using p5.js](https://github.com/ITPNYU/clock-club/tree/master/P5JS_examples)
  * [Clock Animation Test](P5JS_examples/clockAnimationTest/) - a sketch that animates three images like a clock to test out different hand and face ideas.
* [Programmable LED Clocks](https://github.com/ITPNYU/clock-club/tree/master/Programmable_LED_examples)
* [Setting the Time on a Microcontroller-Driven LED (or other) Clock Project](https://github.com/ITPNYU/clock-club/tree/master/Microcontroller_Time_Setting_Methods)
* [Microcontroller-Driven Quartz Clocks](https://github.com/ITPNYU/clock-club/tree/master/Analog_Clock_Control)
* [Making Your Own Clock Hands](https://github.com/ITPNYU/clock-club/tree/master/Making_Custom_Clock_Hands)
* [Two Stepper Motor-Driven Clock Mechanism](https://github.com/ITPNYU/clock-club/tree/master/two_stepper_clock_mechanism)
* Notes on controlling the [VID28-05](VID28-05_mechanism), a two-stepper, concentric shaft mechanism, useful for when you want to make clocks where the two hands are not coupled to each other's movement. 
* [Tabletop Clock](TabletopClock001) - a tabletop clock device built for the [ITP Tangible Interaction](https://itp.nyu.edu/classes/tangible-interaction) class.

### [Insipiration Links](works.md)

A collection of existing timepieces and time-related projects

### [Bibliography](bibliography.md)

A collection of books and articles on clocks and time

### Information

[ClickSpring](https://www.youtube.com/channel/UCworsKCR-Sx6R6-BnIjS2MA) is making precision clocks in a small workshop.

[Suncalc](https://github.com/mourner/suncalc) is a javascript library for calculating the apparent position of the moon and sun given a date and latlong. [Mooncalc](https://www.mooncalc.org) is the same for the moon, and [this table by Don Cross](http://cosinekitty.com/solar_system.html) updates in real time for many solar system objects.

[Armillary Sphere](https://vimeo.com/55019500) An animation for the Museum of the History of Science Oxford explaining armillary spheres.

[Astrolabe](https://www.ted.com/talks/tom_wujec_demos_the_13th_century_astrolabe#t-2360) Tom Wujec explains astrolabes.

[Paper Astrolabes](http://www.mhs.ox.ac.uk/students/03to04/Astrolabes/Starholder_intro.html) An exhibit of paper astrolabes from the 1500's, with instructions on building them.

[Accutron patent](http://www.decadecounter.com/accutron/US3162006.pdf), one of several, that shows the electromagnetically driven tuning fork timing mechanism. [This page](http://www.decadecounter.com/accutron/docs.htm) has a list of several more Accutron documents.

[Tom Shannon](http://www.google.com/patents/US4579460) synchronous world clock with Fuller-Sadao map.

[Clock instructable](http://www.instructables.com/id/How-to-build-C3Jr-a-sophisticated-word-clock/) detailing several more word clocks, including C3Jr mentioned in the first ITP Camp Clock Club session.

[NY Horological Society](http://www.hs-ny.org/) teaches watch-making classes.

### Parts

#### Clock Mechanism Suppliers

* [Klockit](http://www.klockit.com/) has raw clock parts.
* The [Takane](https://www.clockparts.com/time-and-tide-movement/) tide clock adds a reduction stage to the output of a more-or-less standard mechanism. It consists of a stack of gears in the ratio 57:58:59, thus reducing a 12 hour period (solar half-day) to 12h+25.2m (lunar half-day, tidal period). The 58 tooth gear is visible hanging below the main assembly. By running this mechanism at half speed, the hour hand corresponds to sun position and tide hand to moon position. Alternately, it may be possible to add the tide stage to an existing 24-hour movement for the same effect.
* [American Time](http://www.american-time.com/products-by-family/clock-parts-and-repairs) has a wide variety of clock mechanisms, including network clocks, AC clock motors, and more
* [ClockParts](https://www.clockparts.com/) carries movements, motors, dials, and hands, similar to Klockit.
* [Norkro](https://norkro.com/) also carries primarily quartz movements.
* [Bearwoods](https://www.bearwood.com/) carries quartz movements with a focus on wooden clocks. They have a nice guide on [choosing your clock hands](https://www.bearwood.com/how-to-choose-movements-and-hands.html).
* [Clockworks](http://www.clockworks.com/) has mechanical and spring driven movements, in addition to quartz movements. They also carry electric clock motors for AC clocks.
* [Esslinger](https://www.esslinger.com/) has clock and watch movements.


#### Gears

* [Pololu 250:1 Micro Metal Gearmotor MP with Extended Motor Shaft](https://www.pololu.com/product/2384) Small motor with gearbox.
* [Solarbotics GM15 25:1 6mm Planetary Gear Pager Motor](https://solarbotics.com/product/gm15/) Another small motor with gearbox.
* [McMaster bevel gears](http://www.mcmaster.com/#standard-gears/=12kup6f)
* Metal business card suppliers may be a means of getting precise small-run small metal parts.

#### Motors

* [Pololu tiny NEMA 08 Stepper](https://www.pololu.com/product/1204) one of the smallest stepper sizes outside of the wimpy 28BYJs
* [Precision Microdrive](https://www.precisionmicrodrives.com/product-catalogue) is a large OEM provider for small DC gearmotors and other actuators.
* [Anaheim Automation](https://www.anaheimautomation.com/products/stepper/stepper-motors-list.php?cID=19) supplies all kinds of stepper motors, including tiny NEMA08 and NEMA11 motors.

#### Concentric Shaft Dual Stepper motors

If you want to make a clock with independent hands, you need one of these. You can [make your own](two_stepper_clock_mechanism), or buy one of these:
* [Concentric Shaft Dual Stepper Motors](http://www.jukenswisstech.com/products/x40/) by Juken Swiss
* [VID28-05](http://www.vid.wellgain.com/product.aspx?sortid=26) Instrument panel dual stepper
 motor.  
 * AN [eBay source](https://www.ebay.com/itm/VID28-05-Instrument-Micro-Cluster-Dual-Shaft-Stepper-Motor-/232443758214) for them.
 * An [Aliexpress](https://www.aliexpress.com/item/Micro-stepping-motor-BKA30D-R5-Biaxially-meter-motor-BKA30D-stepper-motor-same-as-VID28-05-New/32829075642.html) source for them.
 * [Hackaday teardown](https://hackaday.io/project/7872-clock-clock-clone) on making your own [ClockClock](https://clockclock.com/) clone.

 * [Bomi Kim](http://www.new-startups.com/turn-anything-into-a-clock/) rendered what [Ben is making](two_stepper_clock_mechanism) functional - a generic two-hand mechanism.

#### Mechanical parts

* [McMaster telescoping tubing](http://www.mcmaster.com/#aluminum-telescoping-tubing/=12kupe5) for multiple concentric rotating shafts (but thin walled). Brass also available.
* [Concentric turntable bearings](http://www.aliexpress.com/item-img/18-450mm-Turntable-Bearing-Swivel-Plate-Lazy-Susan-New-Great-For-Mechanical-Projects/1586614309.html) like these might be helpful in astronimical mechanisms. Also available through [VXB](http://www.vxb.com/Hardware-Turntables-Lazy-Susans-Online-s/246.htm)


#### Faces/Dials

* Laser etching powder-coated parts - laser removes paint.
* The opposite - laser fixes paint to part. Brand name?
