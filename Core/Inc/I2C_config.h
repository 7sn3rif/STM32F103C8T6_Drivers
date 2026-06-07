/*
 * I2C_config.h
 *
 *  Created on: Feb 20, 2026
 *      Author: Hassan Arif
 */

#ifndef INC_I2C_CONFIG_H_
#define INC_I2C_CONFIG_H_

// APB1 clock frequency in MHz (needed for CR2)
#define I2C_APB1_FREQ_MHZ 8

// I2C speed mode
#define I2C_SPEED_STANDARD 100000 // 100 kHz
#define I2C_SPEED_FAST 400000 // 400 kHz
#define I2C_SPEED_MODE I2C_SPEED_STANDARD

#endif /* INC_I2C_CONFIG_H_ */
