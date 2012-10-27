pi-servo
========

PWM Servo Control for Raspberry Pi running Xenomai realtime GNU/Linux


Credits & License
=================

Written by Simon Finne <simon.finne@loopon.com>

Feel free to use as you want, on your own responsibility. The code is provided
"as is", no warranty.

Thank you to Gert van Loo & Dom for GPIO example code:
http://elinux.org/RPi_Low-level_peripherals#GPIO_Driving_Example_.28C.29


Description
===========

Extremely simple library for generating PWM (Pulse Width Modulated) signals on
the Raspberry PI GPIO pins, as used by common r/c servos.


Quick-start
===========

* Get & install Xenomai for the Raspberry Pi:
  http://powet.eu/2012/07/25/raspberry-pi-xenomai/

* Connect the signal cable of a servo to GPIO07 (pin 26)
  http://www.raspberrypi-spy.co.uk/wp-content/uploads/2012/06/Raspberry-Pi-GPIO-Layout.png

* Connect external power source to your servo and ensure you share the ground with
  your Raspberry Pi (pin 6)

* Run "make examples" and then execute "examples/move-servo-7"


