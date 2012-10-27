#ifndef __SERVO_H
#define __SERVO_H

#include <native/task.h>
#include <native/timer.h>

#define SERVO_DEFAULT_MIN_PULSE		0.0009
#define SERVO_DEFAULT_MAX_PULSE		0.0021
#define SERVO_DEFAULT_CYCLE_LENGTH	0.02
#define SERVO_DEFAULT_SPEED		10.0
#define SERVO_DEFAULT_POSITION		0.0

typedef struct
{
	/**
	 * @brief Minimum length of pulse in seconds
	 *
	 * Defaults to 0.0009 (900 microseconds). Can only be configured after
	 * ps_init_servo() has been called but before ps_start_servo().
	 */ 
	double	min_pulse;

	/**
	 * @brief Maximum length of pulse in seconds
	 *
	 * Defaults to 0.0021 (2100 microseconds). Can only be configured after
	 * ps_init_servo() has been called but before ps_start_servo().
	 */ 
	double	max_pulse;

	/**
	 * @brief Length of the PWM cycle in seconds
	 *
	 * Defaults to 0.02 (50Hz). Can only be configured after ps_init_servo()
	 * has been called but before ps_start_servo().
	 */
	double	cycle_length;

	/**
	 * @brief Speed of servo as number of full cycles to go from extreme to extreme
	 *
	 * Defaults to 10 (10 full cycles to go from one extreme position to the
	 * other extreme position). Can be modified at any time after ps_init_servo()
	 * has been called.
	 *
	 * Note that it does not make sense to put this to a lower value than 1.0 as that
	 * is the theoretical max speed which we can generate signals for.
	 */
	double	speed;

	/**
	 * @brief Requested position of servo in range (-1, 1)
	 *
	 * Defaults to 0. Can be modified at any time after ps_init_servo() has been
	 * called, but will only have an effect after also ps_start_servo() has been
	 * called.
	 */
	double	pos;

	/**
	 * @brief Internally used last position, do not use from user program
	 */
	double	_last_pos;

	/**
	 * @brief GPIO pin this servo is connected to
	 *
	 * Cannot be modified, automatically set when calling ps_init_servo()
	 */
	int	gpio;

	/**
	 * @brief Xenomai realtime task which drives this servo
	 */
	RT_TASK	task;	
} ps_servo;

/**
 * @brief Initialize a new servo whose signal cable is connected to the given gpio pin
 */
ps_servo* ps_init_servo(int gpio);

/**
 * @brief Prepare GPIO & Xenomai
 *
 * Call once after all ps_init_servo() but before ps_start_servo()
 */ 
void ps_prepare(void);

/**
 * @brief Start the task generating PWM signal to the given servo
 */
void ps_start_servo(ps_servo* servo);

#endif //! __SERVO_H

