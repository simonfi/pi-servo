#include <stdio.h>
#include <stdlib.h>
#include <servo.h>

void show_help(void);

int main(int argc, char* argv[])
{
	ps_servo*	servo7;

	show_help();

	// Setup a servo on GPIO07 with default parameters
	servo7 = ps_init_servo(7);

	// Prepare GPIO & Realtime system
	ps_prepare();

	// Start signal generation task for servo
	ps_start_servo(servo7);

	// Oscillate servo until quit
	while(1)
	{
		servo7->pos = -1.0;
		usleep(1000000);

		servo7->pos = 1.0;
		usleep(1000000);
	}
}

void show_help(void)
{
	char tmp[2];

	printf(	"README:\n" \
		"1) http://www.raspberrypi-spy.co.uk/wp-content/uploads/2012/06/Raspberry-Pi-GPIO-Layout.png\n" \
		"2) Connect servo signal cable to GPIO07 (pin 26)\n" \
		"3) Connect external power to servo\n" \
		"4) Share ground with Raspberry Pi (pin 6)\n\n" \
		"If the above is done, press enter, otherwise Ctrl-C\n" );

	fgets(tmp, 2, stdin);
}

