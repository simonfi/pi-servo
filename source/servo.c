#include <stdlib.h>
#include <sys/mman.h>

#include "servo.h"
#include "gpio.h"

void _ps_servo_task(void* _servo);

/**
 * @brief One second in microseconds
 */
#define RTIME_SECOND	(1000000000)

#define SERVO_TASK_PRIO 	99
#define SERVO_TASK_MODE 	0
#define SERVO_TASK_STACK 	0

ps_servo* ps_init_servo(int gpio)
{
	ps_servo* servo = (ps_servo*)malloc(sizeof(ps_servo));
	if (servo == NULL)
	{
		perror("malloc");
		return NULL;
	}

	// Setup defaults
	servo->min_pulse = SERVO_DEFAULT_MIN_PULSE;
	servo->max_pulse = SERVO_DEFAULT_MAX_PULSE;
	servo->cycle_length = SERVO_DEFAULT_CYCLE_LENGTH;
	servo->speed = SERVO_DEFAULT_SPEED;
	servo->pos = SERVO_DEFAULT_POSITION;
	servo->_last_pos = servo->pos;
	servo->gpio = gpio;

	return servo;
}

void ps_prepare()
{
	gpio_setup();

	mlockall(MCL_CURRENT|MCL_FUTURE);

}

void ps_start_servo(ps_servo* servo)
{
	int	err;
	char	task_name[32];

	sprintf(task_name, "servo-driver-%d", servo->gpio);

	// Ensure GPIO pin is set for output
	INP_GPIO(servo->gpio);
	OUT_GPIO(servo->gpio);	

	err = rt_task_create(	&servo->task,
				task_name,
				SERVO_TASK_STACK,
				SERVO_TASK_PRIO,
				SERVO_TASK_MODE);

	if (!err)
	{
		rt_task_start(	&servo->task,
				&_ps_servo_task,
				(void*)servo);
	} else {
		printf("rt_task_create error: %d\n", err);
	}
}


/**
 * @brief Realtime task which generates the PWM signal and updates servo position
 */
void _ps_servo_task(void* _servo)
{
	unsigned long	overruns;
	int		err;

	ps_servo* servo = (ps_servo*)_servo;

	RTIME	cycle_length = servo->cycle_length * RTIME_SECOND;
	RTIME	pulse_length;

	RTIME	pulse_max = servo->max_pulse * RTIME_SECOND;
	RTIME	pulse_min = servo->min_pulse * RTIME_SECOND;
	RTIME	pulse_diff = pulse_max-pulse_min;

	// Setup periodic task according to our cycle length
	err = rt_task_set_periodic(NULL, TM_NOW, cycle_length);

	while(1)
	{
		// Wait until start of new cycle
		err = rt_task_wait_period(&overruns);

		// Calculate length of pulse
		pulse_length = pulse_min + pulse_diff*(servo->_last_pos+1.0)*0.5;

		// Set pulse
		GPIO_SET = 1<<servo->gpio;

		// Wait until end
		rt_task_sleep(pulse_length);

		// Clear pulse
		GPIO_CLR = 1<<servo->gpio;

		// Update position and ensure we do not go out of bounds
		if (servo->pos < servo->_last_pos)
		{
			servo->_last_pos -= 2.0 / servo->speed;

			if (servo->_last_pos < servo->pos)
			{
				servo->_last_pos = servo->pos;
			}

			if (servo->_last_pos < -1.0)
			{
				servo->_last_pos = -1.0;
			}
		} else if (servo->pos > servo->_last_pos) {
			servo->_last_pos += 2.0 / servo->speed;

			if (servo->_last_pos > servo->pos)
			{
				servo->_last_pos = servo->pos;
			}

			if (servo->_last_pos > 1.0)
			{
				servo->_last_pos = 1.0;
			}
		}
	}
}

