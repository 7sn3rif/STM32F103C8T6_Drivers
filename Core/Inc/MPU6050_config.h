/*
 * MPU6050_config.h
 *
 *  Created on: Feb 26, 2026
 *      Author: LENOVO
 */

#ifndef INC_MPU6050_CONFIG_H_
#define INC_MPU6050_CONFIG_H_
//----------------------I2C Channel--------------------
#define MPU_I2C_CHANNEL  I2C1

// -------------------- I2C Address --------------------
// AD0 pin low = 0x68, AD0 pin high = 0x69
#define MPU6050_ADDR_LOW   0x68
#define MPU6050_ADDR_HIGH  0x69
#define MPU6050_ADDR       MPU6050_ADDR_LOW   // default

// -------------------- Register Addresses --------------------
#define MPU6050_SMPLRT_DIV       0x19  // Sample rate divider
#define MPU6050_CONFIG           0x1A  // DLPF + external sync
#define MPU6050_GYRO_CONFIG      0x1B  // Gyro range
#define MPU6050_ACCEL_CONFIG     0x1C  // Accel range
#define MPU6050_INT_ENABLE       0x38  // Interrupt enable
#define MPU6050_INT_STATUS       0x3A  // Interrupt status

// Sensor output registers
#define MPU6050_ACCEL_XOUT_H     0x3B
#define MPU6050_ACCEL_XOUT_L     0x3C
#define MPU6050_ACCEL_YOUT_H     0x3D
#define MPU6050_ACCEL_YOUT_L     0x3E
#define MPU6050_ACCEL_ZOUT_H     0x3F
#define MPU6050_ACCEL_ZOUT_L     0x40
#define MPU6050_TEMP_OUT_H       0x41
#define MPU6050_TEMP_OUT_L       0x42
#define MPU6050_GYRO_XOUT_H      0x43
#define MPU6050_GYRO_XOUT_L      0x44
#define MPU6050_GYRO_YOUT_H      0x45
#define MPU6050_GYRO_YOUT_L      0x46
#define MPU6050_GYRO_ZOUT_H      0x47
#define MPU6050_GYRO_ZOUT_L      0x48

// Power management
#define MPU6050_PWR_MGMT_1       0x6B
#define MPU6050_PWR_MGMT_2       0x6C

// -------------------- Configuration Options --------------------

// Accelerometer ranges (ACCEL_CONFIG bits [4:3])
#define MPU6050_ACCEL_RANGE_2G   0x00  // ±2g, 16384 LSB/g
#define MPU6050_ACCEL_RANGE_4G   0x01  // ±4g, 8192 LSB/g
#define MPU6050_ACCEL_RANGE_8G   0x02  // ±8g, 4096 LSB/g
#define MPU6050_ACCEL_RANGE_16G  0x03  // ±16g, 2048 LSB/g

// Gyroscope ranges (GYRO_CONFIG bits [4:3])
#define MPU6050_GYRO_RANGE_250   0x00  // ±250 °/s, 131 LSB/(°/s)
#define MPU6050_GYRO_RANGE_500   0x01  // ±500 °/s, 65.5 LSB/(°/s)
#define MPU6050_GYRO_RANGE_1000  0x02  // ±1000 °/s, 32.8 LSB/(°/s)
#define MPU6050_GYRO_RANGE_2000  0x03  // ±2000 °/s, 16.4 LSB/(°/s)

// Digital Low Pass Filter (CONFIG bits [2:0])
#define MPU6050_DLPF_260HZ       0x00  // 260 Hz BW, 8 kHz
#define MPU6050_DLPF_184HZ       0x01  // 184 Hz BW, 1 kHz
#define MPU6050_DLPF_94HZ        0x02  // 94 Hz BW, 1 kHz
#define MPU6050_DLPF_44HZ        0x03  // 44 Hz BW, 1 kHz
#define MPU6050_DLPF_21HZ        0x04  // 21 Hz BW, 1 kHz
#define MPU6050_DLPF_10HZ        0x05  // 10 Hz BW, 1 kHz
#define MPU6050_DLPF_5HZ         0x06  // 5 Hz BW, 1 kHz

#endif // MPU6050_CONFIG_H


