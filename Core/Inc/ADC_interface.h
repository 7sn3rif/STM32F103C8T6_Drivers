/*
 * ADC_interface.h
 *
 *  Created on: Mar 3, 2026
 *      Author: Hassan Arif
 */

#ifndef INC_ADC_INTERFACE_H_
#define INC_ADC_INTERFACE_H_

#include"stm32f1xx.h"

/*****************************************************************************
* Function Name : RCC_EnableADC
* Description   : Enables the clock for the specified ADC peripheral on APB2.
* Parameters    :
*   - ADCx : Pointer to ADC peripheral (ADC1, ADC2)
* Return        : void
*****************************************************************************/
void RCC_EnableADC(ADC_TypeDef *ADCx);

/*****************************************************************************
* Function Name : ADC_Init
* Description   : Initializes the specified ADC for single software-triggered
*                 conversion. Powers on and calibrates the ADC.
* Parameters    :
*   - ADCx : Pointer to ADC peripheral (ADC1, ADC2)
* Return        : void
*****************************************************************************/
void ADC_Init(ADC_TypeDef *ADCx);

/*****************************************************************************
* Function Name : ADC_ReadChannel
* Description   : Performs a single conversion on the given channel and
*                 returns the 12-bit result.
* Parameters    :
*   - ADCx    : Pointer to ADC peripheral (ADC1, ADC2)
*   - channel : ADC channel (use CH_Ax / CH_Bx defines from ADC_config.h)
* Return        : uint16_t — 12-bit result (0–4095)
*****************************************************************************/
uint16_t ADC_ReadChannel(ADC_TypeDef *ADCx, uint8_t channel);

#endif /* INC_ADC_INTERFACE_H_ */
