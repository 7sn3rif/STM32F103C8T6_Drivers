/*
 * GPIO_config.h
 *
 *  Created on: Dec 15, 2025
 *      Author:Hassan Arif
 */

#ifndef INC_GPIO_CONFIG_H_
#define INC_GPIO_CONFIG_H_

#define BITS_PER_PIN  4
#define HIGH          1
#define LOW           0


//outputs modes
/*general purpose */
/*push pull*/
#define G_P_PUSH_PULL_10MHZ  0x1 //CNF=00,MODE=01 AND SO ON
#define G_P_PUSH_PULL_2MHZ   0x2
#define G_P_PUSH_PULL_50MHZ  0x3
/*open drain*/
#define G_P_OPEN_DRAIN_10MHZ  0x5
#define G_P_OPEN_DRAIN_2MHZ   0x6
#define G_P_OPEN_DRAIN_50MHZ  0x7
/*ALTRENATIVE FUNCTION*/
/*PUSH PULL*/
#define A_F_PUSH_PULL_10MHZ  0x9
#define A_F_PUSH_PULL_2MHZ  0xA
#define A_F_PUSH_PULL_50MHZ  0xB
/*OPEN DRAIN*/
#define A_F_OPEN_DRAIN_10MHZ  0xD
#define A_F_OPEN_DRAIN_2MHZ   0xE
#define A_F_OPEN_DRAIN_50MHZ  0xF


//INPUT MODES
#define ANALOG_MODE 0x0
#define FLOATING_INPUT 0x4
#define INPUT_PU_PD 0x8


#endif /* INC_GPIO_CONFIG_H_ */
