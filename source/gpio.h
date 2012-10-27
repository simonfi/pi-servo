#ifndef __SERVO_GPIO_H
#define __SERVO_GPIO_H

extern volatile unsigned *__gpio_ptr;

#define BCM2708_PERI_BASE        0x20000000
#define GPIO_BASE                (BCM2708_PERI_BASE + 0x200000)

// GPIO setup macros. Always use INP_GPIO(x) before using OUT_GPIO(x) or SET_GPIO_ALT(x,y)
#define INP_GPIO(g) *(__gpio_ptr+((g)/10)) &= ~(7<<(((g)%10)*3))
#define OUT_GPIO(g) *(__gpio_ptr+((g)/10)) |=  (1<<(((g)%10)*3))
#define SET_GPIO_ALT(g,a) *(__gpio_ptr+(((g)/10))) |= (((a)<=3?(a)+4:(a)==4?3:2)<<(((g)%10)*3))

/**
 * @brief Set gpio pins to high by writing bitmask to this address
 */
#define GPIO_SET *(__gpio_ptr+7)

/**
 * @brief Clear gpio pins by writing bitmask to this address
 */
#define GPIO_CLR *(__gpio_ptr+10)


/**
 * @brief Obtain pointers needed for GPIO access
 */
void gpio_setup(void);

#endif //! __SERVO_GPIO_H

