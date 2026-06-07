/*
 * ADC_prog.c
 *
 *  Created on: Mar 3, 2026
 *      Author: Hassan Arif
 */

#include "BIT_MATH.h"
#include "stm32f1xx.h"
#include "GPIO_config.h"
#include "GPIO_interface.h"
#include "ADC_config.h"
#include "ADC_interface.h"


void RCC_EnableADC(ADC_TypeDef *ADCx) {
    if      (ADCx == ADC1) { Set_Bit(RCC->APB2ENR, 9);  }
    else if (ADCx == ADC2) { Set_Bit(RCC->APB2ENR, 10); }
}


void ADC_Init(ADC_TypeDef *ADCx) {

    /* Enable ADC Clock */
    RCC_EnableADC(ADCx);

    /* ADC Prescaler PCLK2/2 */
    RCC->CFGR &= ~(0x3 << 14);

    /* Single conversion, no scan, right-aligned */
    Clr_Bit(ADCx->CR1, 8);     // SCAN  = 0
    Clr_Bit(ADCx->CR2, 1);     // CONT  = 0
    Clr_Bit(ADCx->CR2, 11);    // ALIGN = 0

    /* Software trigger */
    ADCx->CR2 |=  (0x7 << 17); // EXTSEL = 111 → SWSTART
    Set_Bit(ADCx->CR2, 20);    // EXTTRIG = 1

    /* 1 conversion in sequence */
    ADCx->SQR1 &= ~(0xF << 20);

    /* Power ON */
    Set_Bit(ADCx->CR2, 0);     // ADON = 1

    /* Stabilisation delay */
    for (volatile uint16_t i = 0; i < 10; i++);

    /* Reset Calibration */
    Set_Bit(ADCx->CR2, 3);
    while (Get_Bit(ADCx->CR2, 3));

    /* Start Calibration */
    Set_Bit(ADCx->CR2, 2);
    while (Get_Bit(ADCx->CR2, 2));
}


uint16_t ADC_ReadChannel(ADC_TypeDef *ADCx, uint8_t channel) {

    /* Configure GPIO as analog input */
    if (channel <= 7) {
        RCC_EnableGPIOx(GPIOA);
        GPIO_SetPinMode(GPIOA, channel, ANALOG_MODE);
    } else {
        RCC_EnableGPIOx(GPIOB);
        GPIO_SetPinMode(GPIOB, (channel - 8), ANALOG_MODE);
    }

    /* Set sampling time → 239.5 cycles */
    ADCx->SMPR2 &= ~(0x7 << (channel * 3));
    ADCx->SMPR2 |=  (0x7 << (channel * 3));

    /* Set channel in SQ1 */
    ADCx->SQR3 &= ~(0x1F);
    ADCx->SQR3 |=  (channel & 0x1F);

    /* Start conversion */
    Set_Bit(ADCx->CR2, 22);    // SWSTART = 1

    /* Wait for EOC */
    while (!Get_Bit(ADCx->SR, 1));

    return (uint16_t)(ADCx->DR & 0x0FFF);
}
