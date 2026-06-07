/*
 * GPIO_interface.h
 *
 *  Created on: Dec 15, 2025
 *      Author: Hassan Arif
 */

#ifndef INC_GPIO_INTERFACE_H_
#define INC_GPIO_INTERFACE_H_
#include"stm32f1xx.h"


/*****************************************************************************
* Function Name : RCC_EnableGPIOx
* Description   : Enables clock gating for a specific GPIO port on APB2 bus.
* Parameters    :
*   - GPIOx : Pointer to GPIO port (GPIOA, GPIOB, GPIOC)
* Return        : void
*****************************************************************************/
void RCC_EnableGPIOx(GPIO_TypeDef *GPIOx);

/*****************************************************************************
* Function Name : RCC_EnableAFIO
* Description   : Enables clock gating for AFIO (Alternate Function I/O).
*                 Required before configuring EXTI or remapping pins.
* Parameters    : None
* Return        : void
*****************************************************************************/
void RCC_EnableAFIO();

/*****************************************************************************
* Function Name : GPIO_SetPinMode
* Description   : Configures the mode of a specific GPIO pin.
* Parameters    :
*   - GPIOx : Pointer to GPIO port (GPIOA, GPIOB, GPIOC)
*   - pin   : Pin number (0–15)
*   - mode  : Pin mode (defined in GPIO_config.h)
*             Options:
*               • G_P_PUSH_PULL_xMHZ
*               • G_P_OPEN_DRAIN_xMHZ
*               • A_F_PUSH_PULL_xMHZ
*               • A_F_OPEN_DRAIN_xMHZ
*               • ANALOG_MODE
*               • FLOATING_INPUT
*               • INPUT_PU_PD
* Return        : void
*****************************************************************************/
void GPIO_SetPinMode(GPIO_TypeDef *GPIOx, uint8_t pin, uint32_t mode);

/*****************************************************************************
* Function Name : GPIO_WritePin
* Description   : Writes a logic value to a specific GPIO pin.
* Parameters    :
*   - GPIOx : Pointer to GPIO port (GPIOA, GPIOB, GPIOC)
*   - pin   : Pin number (0–15)
*   - val   : Logic value
*             Options:
*               • HIGH
*               • LOW
* Return        : void
*****************************************************************************/
void GPIO_WritePin(GPIO_TypeDef *GPIOx, uint8_t pin, uint8_t val);

/*****************************************************************************
* Function Name : GPIO_TogglePin
* Description   : Toggles the logic state of a specific GPIO pin.
* Parameters    :
*   - GPIOx : Pointer to GPIO port (GPIOA, GPIOB, GPIOC)
*   - pin   : Pin number (0–15)
* Return        : void
*****************************************************************************/
void GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint8_t pin);

/*****************************************************************************
* Function Name : GPIO_ReadPin
* Description   : Reads the logic value of a specific GPIO pin.
* Parameters    :
*   - GPIOx : Pointer to GPIO port (GPIOA, GPIOB, GPIOC)
*   - pin   : Pin number (0–15)
* Return        : uint8_t
*                 • HIGH if pin is set
*                 • LOW  if pin is reset
*****************************************************************************/
uint8_t GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint8_t pin);

#endif /* INC_GPIO_INTERFACE_H_ */
