/*
 * PCA9685_prog.c
 *
 *  Created on: Jun 2, 2026
 *  Author: HASSAN ARIF
 */

#include <stdint.h>
#include "stm32f1xx.h"
#include "BIT_MATH.h"
#include "I2C_config.h"
#include "I2C_interface.h"
#include "PCA9685_config.h"
#include "PCA9685_interface.h"

static uint8_t Current_Angle[16] = {0};

void PCA9685_Init(void)
{
    /* I2C Init */
    I2C_Init(PCA9685_I2C_INSTANCE);

    /* MODE1: sleep = 1 (required before prescaler write) */
    uint8_t Mode1DataByte = 0x10;
    PCA9685_WriteRegister(PCA9685_ADDRESS, PCA9685_MODE1_REG, Mode1DataByte);

    /* Prescaler for ~50Hz */
    PCA9685_WriteRegister(PCA9685_ADDRESS, PCA9685_PRE_SCALE_REG, 121);

    /* MODE1: wake up + auto increment */
    Clr_Bit(Mode1DataByte, 4);   /* sleep = 0 */
    Set_Bit(Mode1DataByte, 5);   /* AI = 1    */
    PCA9685_WriteRegister(PCA9685_ADDRESS, PCA9685_MODE1_REG, Mode1DataByte);

    /* Small delay for oscillator to stabilize (~500us) */
    for (volatile uint32_t i = 0; i < 4000; i++);

    /* MODE2: totem pole output, update on STOP */
    uint8_t Mode2DataByte = 0x01;
    Set_Bit(Mode2DataByte, 2);   /* OUTDRV = 1 */
    Clr_Bit(Mode2DataByte, 3);   /* OCH = 0    */
    PCA9685_WriteRegister(PCA9685_ADDRESS, PCA9685_MODE2_REG, Mode2DataByte);

    /* Restart */
    Set_Bit(Mode1DataByte, 7);
    PCA9685_WriteRegister(PCA9685_ADDRESS, PCA9685_MODE1_REG, Mode1DataByte);

    /* ~1ms delay */
    for (volatile uint32_t i = 0; i < 8000; i++);
}

void PCA9685_WriteAngle(uint8_t Channel, uint8_t Angle)
{
    float ratio = (Angle - MIN_ANGLE) * 1.0f / (MAX_ANGLE - MIN_ANGLE);

    uint16_t OFF_count = MIN_PULSE + (uint16_t)(ratio * (MAX_PULSE - MIN_PULSE));

    uint8_t OFF_L = (uint8_t)(OFF_count & 0xFF);
    uint8_t OFF_H = (uint8_t)((OFF_count >> 8) & 0x0F);

    PCA9685_WriteRegister(PCA9685_ADDRESS, PCA9685_LED_ON_L(Channel),  0x00);
    PCA9685_WriteRegister(PCA9685_ADDRESS, PCA9685_LED_ON_H(Channel),  0x00);
    PCA9685_WriteRegister(PCA9685_ADDRESS, PCA9685_LED_OFF_L(Channel), OFF_L);
    PCA9685_WriteRegister(PCA9685_ADDRESS, PCA9685_LED_OFF_H(Channel), OFF_H);

    Current_Angle[Channel] = Angle;
}

void PCA9685_MapAngle(uint8_t Channel, uint8_t InputVal, uint8_t MinVal, uint8_t MaxVal)
{
    float ratio = (InputVal - MinVal) * 1.0f / (MaxVal - MinVal);
    uint8_t Desired_Angle = MIN_ANGLE + (uint8_t)(ratio * (MAX_ANGLE - MIN_ANGLE));

    PCA9685_WriteAngle(Channel, Desired_Angle);
    Current_Angle[Channel] = Desired_Angle;
}

uint8_t PCA9685_ReadAngle(uint8_t Channel)
{
    return Current_Angle[Channel];
}

Err_status PCA9685_WriteRegister(uint8_t slaveAddr, uint8_t regAddr, uint8_t data)
{
    Err_status status;

    status = I2C_StartCondition(PCA9685_I2C_INSTANCE);
    if (status != NOErr) return status;

    status = I2C_MasterSendAddress(PCA9685_I2C_INSTANCE, slaveAddr, I2C_Write);
    if (status != NOErr) return status;

    status = I2C_MasterSendData(PCA9685_I2C_INSTANCE, regAddr);
    if (status != NOErr) return status;

    status = I2C_MasterSendData(PCA9685_I2C_INSTANCE, data);
    if (status != NOErr) return status;

    I2C_StopCondition(PCA9685_I2C_INSTANCE);

    return NOErr;
}

