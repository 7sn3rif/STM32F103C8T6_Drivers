/*
 * I2C_interface.h
 *
 *  Created on: Feb 20, 2026
 *      Author: Hassan Arif
 */

#ifndef INC_I2C_INTERFACE_H_
#define INC_I2C_INTERFACE_H_

typedef enum {
    NOErr,               // No error occurred
    StartConditionErr,   // Failed to generate START (SB not set)
    RepeatedStartErr,    // Failed to generate repeated START
    AddressSendErr,      // Failed to send slave address (ADDR not set)
    DataSendErr,         // Failed to send data (TXE/BTF not set)
    DataReceiveErr,      // Failed to receive data (RXNE not set)
    AckStatus,           // Slave will acknowledge
    NackStatus,          // Slave will not acknowledge
    NACKErr,             // Slave sent NACK
    BusBusyErr,          // BUSY flag stuck
    ArbitrationLostErr,  // ARLO flag set
    OverrunUnderrunErr,  // OVR flag set
    TimeoutErr           // Timeout waiting for flag
} Err_status;

typedef enum {
    I2C_Write = 0,       // Master writing to slave
    I2C_Read  = 1        // Master reading from slave
} I2C_Direction;

/*****************************************************************************
* Function Name : I2C_Init
* Description   : Initializes the I2C peripheral with standard mode settings.
* Parameters    :
*   - I2Cx : Pointer to I2C instance (I2C1, I2C2)
* Return        : void
*****************************************************************************/
void I2C_Init(I2C_TypeDef *I2Cx);

/*****************************************************************************
* Function Name : I2C_StartCondition
* Description   : Generates a START condition on the I2C bus.
* Parameters    :
*   - I2Cx : Pointer to I2C instance
* Return        : Err_status
*****************************************************************************/
Err_status I2C_StartCondition(I2C_TypeDef *I2Cx);

/*****************************************************************************
* Function Name : I2C_RepeatedStart
* Description   : Generates a repeated START condition on the I2C bus.
* Parameters    :
*   - I2Cx : Pointer to I2C instance
* Return        : Err_status
*****************************************************************************/
Err_status I2C_RepeatedStart(I2C_TypeDef *I2Cx);

/*****************************************************************************
* Function Name : I2C_StopCondition
* Description   : Generates a STOP condition on the I2C bus.
* Parameters    :
*   - I2Cx : Pointer to I2C instance
* Return        : void
*****************************************************************************/
void I2C_StopCondition(I2C_TypeDef *I2Cx);

/*****************************************************************************
* Function Name : I2C_MasterSendAddress
* Description   : Sends slave address with read/write direction.
* Parameters    :
*   - I2Cx          : Pointer to I2C instance
*   - slave_address : 7-bit slave address
*   - I2C_rw        : Transfer direction (I2C_Write / I2C_Read)
* Return        : Err_status
*****************************************************************************/
Err_status I2C_MasterSendAddress(I2C_TypeDef *I2Cx, uint8_t slave_address, I2C_Direction I2C_rw);

/*****************************************************************************
* Function Name : I2C_MasterSendData
* Description   : Sends a single byte of data from master to slave.
* Parameters    :
*   - I2Cx : Pointer to I2C instance
*   - data : Byte to be transmitted
* Return        : Err_status
*****************************************************************************/
Err_status I2C_MasterSendData(I2C_TypeDef *I2Cx, uint8_t data);

/*****************************************************************************
* Function Name : I2C_MasterReadData
* Description   : Reads a single byte of data from slave to master.
* Parameters    :
*   - I2Cx : Pointer to I2C instance
*   - data : Pointer to variable to store received byte
* Return        : Err_status
*****************************************************************************/
Err_status I2C_MasterReadData(I2C_TypeDef *I2Cx, uint8_t *data);

/*****************************************************************************
* Function Name : I2C_SlaveAckOrNack
* Description   : Checks whether slave is configured to ACK or NACK.
* Parameters    :
*   - I2Cx : Pointer to I2C instance
* Return        : Err_status
*****************************************************************************/
Err_status I2C_SlaveAckOrNack(I2C_TypeDef *I2Cx);

/*****************************************************************************
* Function Name : I2C_SlaveReceiveData
* Description   : Receives a single byte of data in slave mode.
* Parameters    :
*   - I2Cx : Pointer to I2C instance
* Return        : uint8_t
*                 • Received byte
*                 • 0xFF if timeout occurs
*****************************************************************************/
uint8_t I2C_SlaveReceiveData(I2C_TypeDef *I2Cx);
/*****************************************************************************
* Function Name : I2C_MasterTransmit
* Description   : Transmits a sequence of bytes from master to slave.
* Parameters    :
*   - I2Cx          : Pointer to I2C instance (I2C1, I2C2)
*   - slave_address : 7-bit slave address of the target device
*   - data          : Pointer to buffer containing bytes to be transmitted
*   - length        : Number of bytes to transmit
* Return        : Err_status
*                 • NOErr           : Transmission successful
*                 • StartConditionErr : Failed to generate START condition
*                 • AddressSendErr    : Failed to send slave address
*                 • DataSendErr       : Failed to transmit data
*                 • NACKErr           : Slave sent NACK
*                 • TimeoutErr        : Timeout waiting for flag
*****************************************************************************/
Err_status I2C_MasterTransmit(I2C_TypeDef *I2Cx, uint8_t slave_address, uint8_t *data, uint16_t length);

/*****************************************************************************
* Function Name : I2C_MasterReceive
* Description   : Receives a sequence of bytes from slave to master.
* Parameters    :
*   - I2Cx          : Pointer to I2C instance (I2C1, I2C2)
*   - slave_address : 7-bit slave address of the target device
*   - buffer        : Pointer to buffer to store received bytes
*   - length        : Number of bytes to receive
* Return        : Err_status
*                 • NOErr             : Reception successful
*                 • StartConditionErr : Failed to generate START condition
*                 • AddressSendErr    : Failed to send slave address
*                 • DataReceiveErr    : Failed to receive data
*                 • NACKErr           : Slave sent NACK
*                 • TimeoutErr        : Timeout waiting for flag
*****************************************************************************/
Err_status I2C_MasterReceive(I2C_TypeDef *I2Cx, uint8_t slave_address, uint8_t *buffer, uint16_t length);

#endif /* INC_I2C_INTERFACE_H_ */
