/*
 * EXTI_config.h
 *
 *  Created on: Feb 12, 2026
 *      Author: LENOVO
 */

#ifndef INC_EXTI_CONFIG_H_
#define INC_EXTI_CONFIG_H_

//EXTI GPIO Port
typedef enum {
	GPIO_PORT_A = 0,
	GPIO_PORT_B = 1,
	GPIO_PORT_C = 2,
} EXTI_GPIO_Port;





//EXTI lines
#define EXTI0   0
#define EXTI1   1
#define EXTI2   2
#define EXTI3   3
#define EXTI4   4
#define EXTI5   5
#define EXTI6   6
#define EXTI7   7
#define EXTI8   8
#define EXTI9   9
#define EXTI10  10
#define EXTI11  11
#define EXTI12  12
#define EXTI13  13
#define EXTI14  14
#define EXTI15  15




// MODES
#define RISING_EDGE      0
#define FALLING_EDGE     1
#define BOTH_EDGES       2




/*NVIC*/

//IRQns
#define EXTI0_IRQn       6
#define EXTI1_IRQn       7
#define EXTI2_IRQn       8
#define EXTI3_IRQn       9
#define EXTI4_IRQn       10
#define EXTI9_5_IRQn     23   // shared for lines 5–9
#define EXTI15_10_IRQn   40   // shared for lines 10–15







#endif /* INC_EXTI_CONFIG_H_ */
