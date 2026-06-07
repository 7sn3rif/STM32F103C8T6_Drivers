/*
 * PCA9685_config.h
 *
 * Created: 12/23/2025

 *  Author: HASSAN ARIF
 */


#ifndef PCA9685_CONFIG_H_
#define PCA9685_CONFIG_H_

/* PCA Address */
#define PCA9685_ADDRESS          0x40

/* I2C Instance to use */
#define PCA9685_I2C_INSTANCE     I2C1

/* Core control registers */
#define PCA9685_MODE1_REG        0x00
#define PCA9685_MODE2_REG        0x01

/* Frequency control */
#define PCA9685_PRE_SCALE_REG    0xFE

/* LED channel base addresses */
#define PCA9685_LED0_ON_L        0x06
#define PCA9685_LED0_ON_H        0x07
#define PCA9685_LED0_OFF_L       0x08
#define PCA9685_LED0_OFF_H       0x09

/* Macros to compute LEDn register addresses */
#define PCA9685_LED_ON_L(n)      (0x06 + 4*(n))
#define PCA9685_LED_ON_H(n)      (0x07 + 4*(n))
#define PCA9685_LED_OFF_L(n)     (0x08 + 4*(n))
#define PCA9685_LED_OFF_H(n)     (0x09 + 4*(n))

/* Angles */
#define MAX_ANGLE                180
#define MIN_ANGLE                0
#define MIN_PULSE                205
#define MAX_PULSE                410

#endif /* PCA9685_CONFIG_H_ */
