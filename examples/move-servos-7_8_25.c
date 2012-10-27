#include <stdio.h>
#include <stdlib.h>
#include <servo.h>

void show_help(void);

int main(int argc, char* argv[])
{
	ps_servo*	servo7;
	ps_servo*	servo8;
	ps_servo*	servo25;

	show_help();

	// Setup a servo on GPIO07 with default parameters
	servo7 = ps_init_servo(7);
	servo8 = ps_init_servo(8);
	servo25 = ps_init_servo(25);

	// Prepare GPIO & Realtime system
	ps_prepare();

	// Start signal generation task for servo
	ps_start_servo(servo7);
	ps_start_servo(servo8);
	ps_start_servo(servo25);

	servo7->speed = 10;
	servo8->speed = 20;
	servo25->speed = 40;

	// Oscillate servo until quit
	while(1)
	{
		servo7->pos = -1.0;
		servo8->pos = -1.0;
		servo25->pos = -1.0;
		usleep(2000000);

		servo7->pos = 1.0;
		servo8->pos = 1.0;
		servo25->pos = 1.0;
		usleep(2000000);
	}
}

void show_help(void)
{
	char tmp[2];

	printf(	"README:\n" \
		"1) http://www.raspberrypi-spy.co.uk/wp-content/uploads/2012/06/Raspberry-Pi-GPIO-Layout.png\n" \
		"2) Connect servo signal cables to GPIO07, GPIO08, GPIO25\n" \
		"3) Connect external power to servos\n" \
		"4) Share ground with Raspberry Pi (pin 6)\n\n" \
		"If the above is done, press enter, otherwise Ctrl-C\n" );

	fgets(tmp, 2, stdin);
}

