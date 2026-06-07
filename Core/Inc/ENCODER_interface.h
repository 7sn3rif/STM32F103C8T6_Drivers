/*
 * ENCODER_interface.h
 *
 *  Created on: Mar 4, 2026
 *      Author: Hassan Arif
 */

#ifndef INC_ENCODER_INTERFACE_H_
#define INC_ENCODER_INTERFACE_H_


/*****************************************************************************
* Function Name : ENCODER_EXTI_Init
* Description   : Initializes the specified encoder using EXTI interrupts.
*                 Configures encoder pins as inputs with pull-up/down and
*                 attaches EXTI callbacks for quadrature decoding.
* Parameters    :
*   - encoder_x : Encoder identifier (ENCODER_1, ENCODER_2)
* Return        : void
*****************************************************************************/
void ENCODER_EXTI_Init(uint8_t encoder_x);

/*****************************************************************************
* Function Name : ENCODER_GetCount
* Description   : Returns the current tick count of the specified encoder.
* Parameters    :
*   - encoder_x : Encoder identifier (ENCODER_1, ENCODER_2)
* Return        : int32_t — current tick count
*****************************************************************************/
int32_t ENCODER_GetCount(uint8_t encoder_x);

/*****************************************************************************
* Function Name : ENCODER_SetCount
* Description   : Manually sets the tick count of the specified encoder.
* Parameters    :
*   - encoder_x : Encoder identifier (ENCODER_1, ENCODER_2)
*   - count     : New tick count value
* Return        : void
*****************************************************************************/
void ENCODER_SetCount(uint8_t encoder_x, int32_t count);

/*****************************************************************************
* Function Name : ENCODER_GetDirection
* Description   : Determines the rotation direction of the specified encoder
*                 based on tick count changes.
* Parameters    :
*   - encoder_x : Encoder identifier (ENCODER_1, ENCODER_2)
* Return        : int8_t — FORWARD, REVERSE, or STOPPED
*****************************************************************************/
int8_t ENCODER_GetDirection(uint8_t encoder_x);

/*****************************************************************************
* Function Name : ENCODER_Reset
* Description   : Resets the tick count of the specified encoder to zero.
* Parameters    :
*   - encoder_x : Encoder identifier (ENCODER_1, ENCODER_2)
* Return        : void
*****************************************************************************/
void ENCODER_Reset(uint8_t encoder_x);

#endif /* INC_ENCODER_INTERFACE_H_ */

