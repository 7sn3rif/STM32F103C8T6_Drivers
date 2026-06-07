/*
 * EXTI_interface.h
 *
 *  Created on: Feb 1, 2026
 *      Author:Hassan Arif
 */

#ifndef INC_EXTI_INTERFACE_H_
#define INC_EXTI_INTERFACE_H_




/*****************************************************************************
* Function Name : EXTI_Init
* Description   : Initializes an EXTI line with a specific GPIO port and trigger mode.
*                 IMPORTANT: Before calling this function, configure the corresponding
*                 GPIO pin as an INPUT (Floating, Pull-Up, or Pull-Down) depending on
*                 your external signal requirements.
* Parameters    :
*   - GPIO_Port_x : GPIO port (A, B, or C)
*   - EXTIx       : EXTI line number (0–15)
*   - mode        : Trigger mode
*                   Options:
*                     • RISING_EDGE
*                     • FALLING_EDGE
*                     • BOTH_EDGES
* Return        : void
*****************************************************************************/
void EXTI_Init(EXTI_GPIO_Port GPIO_Port_x, uint8_t EXTIx, uint8_t mode);

/*****************************************************************************
* Function Name : EXTI_EnableLine
* Description   : Enables NVIC interrupt for a specific EXTI line.
* Parameters    :
*   - EXTIx : EXTI line number (0–15)
* Return        : void
*****************************************************************************/
void EXTI_EnableLine(uint8_t EXTIx);

/*****************************************************************************
* Function Name : EXTI_DisableLine
* Description   : Disables NVIC interrupt for a specific EXTI line.
* Parameters    :
*   - EXTIx : EXTI line number (0–15)
* Return        : void
*****************************************************************************/
void EXTI_DisableLine(uint8_t EXTIx);

/*****************************************************************************
* Function Name : EXTI_SetCallBack
* Description   : Registers a callback function for a specific EXTI line.
* Parameters    :
*   - function_ptr : Pointer to user-defined function
*   - EXTIx        : EXTI line number (0–15)
* Return        : void
*****************************************************************************/
void EXTI_SetCallBack(void (*function_ptr)(void), uint8_t EXTIx);

/*****************************************************************************
* Function Name : NVIC_EnableIRQn
* Description   : Helper function to enable NVIC interrupt for a given IRQ number.
* Parameters    :
*   - EXTIx_IRQn : IRQ number corresponding to EXTI line
* Return        : void
*****************************************************************************/
void NVIC_EnableIRQn(uint8_t EXTIx_IRQn);

/*****************************************************************************
* Function Name : NVIC_DisableIRQn
* Description   : Helper function to disable NVIC interrupt for a given IRQ number.
* Parameters    :
*   - EXTIx_IRQn : IRQ number corresponding to EXTI line
* Return        : void
*****************************************************************************/
void NVIC_DisableIRQn(uint8_t EXTIx_IRQn);


#endif /* INC_EXTI_INTERFACE_H_ */
