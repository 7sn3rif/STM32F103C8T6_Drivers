/*
 * AdvancedTIM_interface.h
 *
 *  Created on: Feb 23, 2026
 *      Author: Hassan
 */

#ifndef INC_ADVANCEDTIM_INTERFACE_H_
#define INC_ADVANCEDTIM_INTERFACE_H_

/*****************************************************************************
* Enum Name     : TIM1_Channel
* Description   : Maps TIM1 PWM output channels to their corresponding GPIO pins.
*                 Each enumerator represents a TIM1 channel and its associated pin.
*****************************************************************************/
typedef enum {
    CH1_PA8  = 8,   // TIM1 Channel 1 output on PA8
    CH2_PA9,        // TIM1 Channel 2 output on PA9
    CH3_PA10,       // TIM1 Channel 3 output on PA10
    CH4_PA11        // TIM1 Channel 4 output on PA11
} TIM1_Channel;

/*****************************************************************************
* Function Name : TIM1_PWMInit
* Description   : Initializes TIM1 for PWM generation on the selected channel.
* Parameters    :
*   - CHx_PAx : TIM1 channel to initialize (CH1_PA8, CH2_PA9, CH3_PA10, CH4_PA11)
*   - f_pwm   : Desired PWM frequency in Hz
* Return        : void
*****************************************************************************/
void TIM1_PWMInit(TIM1_Channel CHx_PAx, uint32_t f_pwm);

/*****************************************************************************
* Function Name : TIM1_WritePWM
* Description   : Updates the duty cycle of the selected TIM1 PWM channel.
* Parameters    :
*   - CHx_PAx     : TIM1 channel to update (CH1_PA8, CH2_PA9, CH3_PA10, CH4_PA11)
*   - duty_cycle  : Duty cycle percentage (0–100)
* Return        : void
*****************************************************************************/
void TIM1_WritePWM(TIM1_Channel CHx_PAx, uint8_t duty_cycle);



#endif /* INC_ADVANCEDTIM_INTERFACE_H_ */
