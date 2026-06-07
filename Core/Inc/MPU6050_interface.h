/*
 * MPU6050_interface.h
 *
 *  Created on: Feb 26, 2026
 *      Author: Hassan Arif
 */

#include <stdint.h>
#include <inttypes.h>

#ifndef INC_MPU6050_INTERFACE_H_
#define INC_MPU6050_INTERFACE_H_

/*****************************************************************************
* Struct Name   : MPU_raw_data
* Description   : Holds raw sensor values directly read from MPU6050 registers.
* Members       :
*   - Accel_x, Accel_y, Accel_z : Raw accelerometer readings (LSB)
*   - Gyro_x, Gyro_y, Gyro_z    : Raw gyroscope readings (LSB)
*   - Temperature               : Raw temperature register value (LSB)
*****************************************************************************/
typedef struct {
    int16_t Accel_x, Accel_y, Accel_z;
    int16_t Gyro_x, Gyro_y, Gyro_z;
    float   Temperature;
} MPU_raw_data;

/*****************************************************************************
* Struct Name   : MPU_real_data
* Description   : Holds scaled sensor values converted into physical units.
* Members       :
*   - Accel_x, Accel_y, Accel_z : Acceleration in g
*   - Gyro_x, Gyro_y, Gyro_z    : Angular velocity in °/s
*   - Temperature               : Temperature in °C
*****************************************************************************/
typedef struct {
    int16_t Accel_x, Accel_y, Accel_z;
    int16_t Gyro_x, Gyro_y, Gyro_z;
    float   Temperature;
} MPU_real_data;

/*****************************************************************************
* Function Name : MPU6050_Init
* Description   : Initializes the MPU6050 sensor with default configuration.
*                 Typically sets up power management, sample rate, and ranges.
* Parameters    : void
* Return        : void
*****************************************************************************/
void MPU6050_Init();

/*****************************************************************************
* Function Name : MPU6050_StartLocation
* Description   : Sets the internal register pointer of the MPU6050 to the
*                 starting location for data readout (ACCEL_XOUT_H).
* Parameters    : void
* Return        : void
*****************************************************************************/
void MPU6050_StartLocation();

/*****************************************************************************
* Function Name : MPU6050_ReadRawVal
* Description   : Reads raw accelerometer, gyroscope, and temperature values
*                 directly from the MPU6050 registers.
* Parameters    :
*   - Sensor_raw_data : Pointer to struct to store raw values
* Return        : void
*****************************************************************************/
void MPU6050_ReadRawVal(MPU_raw_data *Sensor_raw_data);

/*****************************************************************************
* Function Name : MPU6050_ReadScaledVal
* Description   : Reads sensor values and converts them into physical units
*                 (g for acceleration, °/s for angular velocity, °C for temperature).
* Parameters    :
*   - Sensor_real_data : Pointer to struct to store scaled values
* Return        : void
*****************************************************************************/
void MPU6050_ReadScaledVal(MPU_real_data *Sensor_real_data);

/*****************************************************************************
* Function Name : MPU6050_WriteRegister
* Description   : Writes a single byte of data to a specific MPU6050 register.
* Parameters    :
*   - slaveAddr : 7-bit I2C address of the MPU6050
*   - regAddr   : Register address to write to
*   - data      : Byte of data to write
* Return        : Err_status
*                 • NOErr           : Write successful
*                 • NACKErr         : Slave sent NACK
*                 • TimeoutErr      : Timeout waiting for flag
*****************************************************************************/
Err_status MPU6050_WriteRegister(uint8_t slaveAddr, uint8_t regAddr, uint8_t data);

#endif /* INC_MPU6050_INTERFACE_H_ */
