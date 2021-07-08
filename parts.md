# Parts and Suppliers

Sources for clock parts and related parts. 

## Clock Mechanism Suppliers

* [Klockit](http://www.klockit.com/) has raw clock parts.
* The [Takane](https://www.clockparts.com/time-and-tide-movement/) tide clock adds a reduction stage to the output of a more-or-less standard mechanism. It consists of a stack of gears in the ratio 57:58:59, thus reducing a 12 hour period (solar half-day) to 12h+25.2m (lunar half-day, tidal period). The 58 tooth gear is visible hanging below the main assembly. By running this mechanism at half speed, the hour hand corresponds to sun position and tide hand to moon position. Alternately, it may be possible to add the tide stage to an existing 24-hour movement for the same effect.
* [American Time](http://www.american-time.com/products-by-family/clock-parts-and-repairs) has a wide variety of clock mechanisms, including network clocks, AC clock motors, and more
* [ClockParts](https://www.clockparts.com/) carries movements, motors, dials, and hands, similar to Klockit.
* [Norkro](https://norkro.com/) also carries primarily quartz movements.
* [Bearwoods](https://www.bearwood.com/) carries quartz movements with a focus on wooden clocks. They have a nice guide on [choosing your clock hands](https://www.bearwood.com/how-to-choose-movements-and-hands.html).
* [Clockworks](http://www.clockworks.com/) has mechanical and spring driven movements, in addition to quartz movements. They also carry electric clock motors for AC clocks.
* [Esslinger](https://www.esslinger.com/) has clock and watch movements.


## Gears

* [Pololu 250:1 Micro Metal Gearmotor MP with Extended Motor Shaft](https://www.pololu.com/product/2384) Small motor with gearbox.
* [Solarbotics GM15 25:1 6mm Planetary Gear Pager Motor](https://solarbotics.com/product/gm15/) Another small motor with gearbox.
* [McMaster bevel gears](http://www.mcmaster.com/#standard-gears/=12kup6f)
* Metal business card suppliers may be a means of getting precise small-run small metal parts.

## Motors

* [Pololu tiny NEMA 08 Stepper](https://www.pololu.com/product/1204) one of the smallest stepper sizes outside of the wimpy 28BYJs
* [Precision Microdrive](https://www.precisionmicrodrives.com/product-catalogue) is a large OEM provider for small DC gearmotors and other actuators.
* [Anaheim Automation](https://www.anaheimautomation.com/products/stepper/stepper-motors-list.php?cID=19) supplies all kinds of stepper motors, including tiny NEMA08 and NEMA11 motors.

## Concentric Shaft Dual Stepper motors

If you want to make a clock with independent hands, you need one of these. You can [make your own](two_stepper_clock_mechanism), or buy one of these:
* [Concentric Shaft Dual Stepper Motors](http://www.jukenswisstech.com/products/x40/) by Juken Swiss
* [VID28-05](http://www.vid.wellgain.com/product.aspx?sortid=26) Instrument panel dual stepper
 motor.  
 * An [eBay source](https://www.ebay.com/itm/VID28-05-Instrument-Micro-Cluster-Dual-Shaft-Stepper-Motor-/232443758214) for them.
 * An [Aliexpress](https://www.aliexpress.com/item/Micro-stepping-motor-BKA30D-R5-Biaxially-meter-motor-BKA30D-stepper-motor-same-as-VID28-05-New/32829075642.html) source for them.
 * [Hackaday teardown](https://hackaday.io/project/7872-clock-clock-clone) on making your own [ClockClock](https://clockclock.com/) clone.

 * [Bomi Kim](http://www.new-startups.com/turn-anything-into-a-clock/) rendered what [Ben is making](two_stepper_clock_mechanism) functional - a generic two-hand mechanism.

## Mechanical parts

* [McMaster telescoping tubing](http://www.mcmaster.com/#aluminum-telescoping-tubing/=12kupe5) for multiple concentric rotating shafts (but thin walled). Brass also available.
* [Concentric turntable bearings](http://www.aliexpress.com/item-img/18-450mm-Turntable-Bearing-Swivel-Plate-Lazy-Susan-New-Great-For-Mechanical-Projects/1586614309.html) like these might be helpful in astronimical mechanisms. Also available through [VXB](http://www.vxb.com/Hardware-Turntables-Lazy-Susans-Online-s/246.htm)

# Realtime Clock Modules

[Microcrystal RV-3032-C7](https://www.microcrystal.com/en/products/real-time-clock-rtc-modules/rv-3032-c7/) is a High Performance Temperature Compensated Real-Time Clock Module with I2C interface. It claims to offer "the world's best time accuracy across industrial temperature range at ultra-low current consumption".

U-Blox [G60-ST-TM GPS timing chip](https://www.u-blox.com/en/product/ubx-g6010-st-tm-chip) 
