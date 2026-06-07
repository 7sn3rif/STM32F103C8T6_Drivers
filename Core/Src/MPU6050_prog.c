/*
 * MPU6050_prog.c
 *
 *  Created on: Feb 26, 2026
 *      Author: Hassan Arif
 */
#include "BIT_MATH.h"
#include "stm32f1xx.h"
#include "I2C_interface.h"
#include "MPU6050_config.h"
#include "MPU6050_interface.h"



void delay_ms(uint32_t ms)
{
	for (uint32_t i = 0; i < ms * 8000; i++)
		;
}



void MPU6050_Init(){
	I2C_Init(MPU_I2C_CHANNEL);
	MPU6050_WriteRegister(MPU6050_ADDR, MPU6050_PWR_MGMT_1, 0x00);//wake up from sleep
	delay_ms(20);

	/* Sample rate = gyro output rate /(SMPLRT_DIV+1)
	 * for sample rate 1 and if the gyro output 8 khz SMPLRT_DIV must be = 7
	 */
	MPU6050_WriteRegister(MPU6050_ADDR, MPU6050_SMPLRT_DIV, 0x07);
	delay_ms(5);
	MPU6050_WriteRegister(MPU6050_ADDR, MPU6050_CONFIG, MPU6050_DLPF_260HZ  );//Fs=8KHz
	delay_ms(5);

	MPU6050_WriteRegister(MPU6050_ADDR, MPU6050_ACCEL_CONFIG, MPU6050_ACCEL_RANGE_2G);// Accelerometer full scale range +/- 2g
	delay_ms(5);
	MPU6050_WriteRegister(MPU6050_ADDR, MPU6050_GYRO_CONFIG, MPU6050_GYRO_RANGE_250);//Gyroscope full scale range +/- 250 degree
	delay_ms(5);
	MPU6050_WriteRegister(MPU6050_ADDR, MPU6050_INT_ENABLE, 0x1);/*When set to 1, this bit enables the Data Ready interrupt, which occurs each
	time a write operation to all of the sensor registers has been completed.*/
	delay_ms(5);

}




void MPU6050_StartLocation(){
	uint8_t data = MPU6050_ACCEL_XOUT_H;
	// Step 1: Tell MPU6050 where to start (ACCEL_XOUT_H)
	I2C_MasterTransmit(MPU_I2C_CHANNEL, MPU6050_ADDR, &data, 1);

}





void MPU6050_ReadRawVal(MPU_raw_data *Sensor_raw_data){
	MPU6050_StartLocation();
	uint8_t mpu_read_val[14];
	I2C_MasterReceive(MPU_I2C_CHANNEL, MPU6050_ADDR, mpu_read_val, 14);
//                                byte high << 8  |  byte low
	//accelerometer raw data
	Sensor_raw_data->Accel_x=(mpu_read_val[0]<<8) |  mpu_read_val[1];
	Sensor_raw_data->Accel_y=(mpu_read_val[2]<<8) |  mpu_read_val[3];
	Sensor_raw_data->Accel_z=(mpu_read_val[4]<<8) |  mpu_read_val[5];

	//temperature raw data
	Sensor_raw_data->Temperature=(int16_t)(mpu_read_val[6]<<8) |  mpu_read_val[7];

	//gyroscope   raw data
	Sensor_raw_data->Gyro_x=(mpu_read_val[8]<<8) |  mpu_read_val[9];
	Sensor_raw_data->Gyro_y=(mpu_read_val[10]<<8) |  mpu_read_val[11];
	Sensor_raw_data->Gyro_z=(mpu_read_val[12]<<8) |  mpu_read_val[13];

}




void MPU6050_ReadScaledVal(MPU_real_data *Sensor_real_data){
    MPU_raw_data raw_data;
    MPU6050_ReadRawVal(&raw_data);
    delay_ms(50);
    /*********    Datasheet calculations      *********/

    // Accelerometer (±2g → 16384 LSB/g)
    Sensor_real_data->Accel_x = raw_data.Accel_x / 16384.0;
    Sensor_real_data->Accel_y = raw_data.Accel_y / 16384.0;
    Sensor_real_data->Accel_z = raw_data.Accel_z / 16384.0;

    // Temperature
    Sensor_real_data->Temperature = (float)(raw_data.Temperature / 340.0) + 36.53;

    // Gyroscope (±250 °/s → 131 LSB/(°/s))
    Sensor_real_data->Gyro_x = raw_data.Gyro_x / 131.0;
    Sensor_real_data->Gyro_y = raw_data.Gyro_y / 131.0;
    Sensor_real_data->Gyro_z = raw_data.Gyro_z / 131.0;
}







/**** helping functions ***/
Err_status MPU6050_WriteRegister(uint8_t slaveAddr , uint8_t regAddr , uint8_t data )
{
	Err_status status;
	status = I2C_StartCondition(MPU_I2C_CHANNEL);
	if(status != NOErr) return status;

	status = I2C_MasterSendAddress(MPU_I2C_CHANNEL, slaveAddr, I2C_Write);
	if(status != NOErr) return status;


	status = I2C_MasterSendData(MPU_I2C_CHANNEL, regAddr);
	if(status != NOErr) return status;


	status = I2C_MasterSendData(MPU_I2C_CHANNEL, data);
	if(status != NOErr) return status;


	I2C_StopCondition(MPU_I2C_CHANNEL);


    return NOErr;
}


