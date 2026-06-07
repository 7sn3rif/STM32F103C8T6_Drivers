/*
 * UART_interface.h
 *
 *  Created on: Dec 28, 2025
 *      Author: Hassan Arif
 */

#ifndef INC_UART_INTERFACE_H_
#define INC_UART_INTERFACE_H_

typedef enum {
    UART_CHANNEL_1 = 1,
    UART_CHANNEL_2,
    UART_CHANNEL_3
} USARTx;

/*****************************************************************************
* Function Name : RCC_EnableUARTx
* Description   : Enables clock gating for a specific UART channel.
*                 This is a helper function and typically not called directly
*                 in application code.
* Parameters    :
*   - UART_Channel : UART channel (UART_CHANNEL_1, UART_CHANNEL_2, UART_CHANNEL_3)
* Return        : void
*****************************************************************************/
void RCC_EnableUARTx(USARTx UART_Channel);

/*****************************************************************************
* Function Name : UART_Init
* Description   : Initializes a UART channel with the configured baud rate.
*                 Configures GPIO pins for TX (Alternate Function Push-Pull)
*                 and RX (Floating Input), sets frame format, and enables UART.
* Parameters    :
*   - UART_Channel : UART channel (UART_CHANNEL_1, UART_CHANNEL_2, UART_CHANNEL_3)
* Return        : void
*****************************************************************************/
void UART_Init(USARTx UART_Channel);

/*****************************************************************************
* Function Name : UART_SendData
* Description   : Sends a single byte of data through the specified UART channel.
* Parameters    :
*   - UART_Channel : UART channel (UART_CHANNEL_1, UART_CHANNEL_2, UART_CHANNEL_3)
*   - data         : Byte to be transmitted
* Return        : void
*****************************************************************************/
void UART_SendData(USARTx UART_Channel, uint8_t data);

/*****************************************************************************
* Function Name : UART_SendString
* Description   : Sends a null-terminated string through the specified UART channel.
* Parameters    :
*   - UART_Channel : UART channel (UART_CHANNEL_1, UART_CHANNEL_2, UART_CHANNEL_3)
*   - string       : Pointer to null-terminated string
* Return        : void
*****************************************************************************/
void UART_SendString(USARTx UART_Channel, uint8_t *string);

/*****************************************************************************
* Function Name : UART_ReceiveData
* Description   : Receives a single byte of data from the specified UART channel.
*                 Function blocks until data is available.
* Parameters    :
*   - UART_Channel : UART channel (UART_CHANNEL_1, UART_CHANNEL_2, UART_CHANNEL_3)
* Return        : uint8_t
*                 • Received byte
*****************************************************************************/
uint8_t UART_ReceiveData(USARTx UART_Channel);

#endif /* INC_UART_INTERFACE_H_ */
