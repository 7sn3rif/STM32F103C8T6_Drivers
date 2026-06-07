/*
 * DCmotor_interface.h
 *
 *  Created on: Feb 27, 2026
 *      Author: Hassan Arif
 */

#ifndef INC_DCMOTOR_INTERFACE_H_
#define INC_DCMOTOR_INTERFACE_H_

/*****************************************************************************
* Function Name : DCmotor_Init
* Description   : Initializes GPIO pins and TIM1 channels for motor control.
*                 Configures ENA (right motor) and ENB (left motor) as PWM outputs
*                 at 12.5 kHz, and IN1–IN4 as push-pull outputs for direction control.
* Parameters    : void
* Return        : void
*****************************************************************************/
void DCmotor_Init();

/*****************************************************************************
* Function Name : DCmotor_LeftSpeed
* Description   : Sets the speed of the **left motor** (ENB).
*                 Uses PWM on ENB and IN3/IN4 for direction.
*                 Intended for PID control or fine-grained speed regulation.
* Parameters    :
*   - speed_percentage : Desired speed (0–100%)
* Return        : void
*****************************************************************************/
void DCmotor_LeftSpeed(uint8_t speed_percentage);

/*****************************************************************************
* Function Name : DCmotor_RightSpeed
* Description   : Sets the speed of the **right motor** (ENA).
*                 Uses PWM on ENA and IN1/IN2 for direction.
*                 Intended for PID control or fine-grained speed regulation.
* Parameters    :
*   - speed_percentage : Desired speed (0–100%)
* Return        : void
*****************************************************************************/
void DCmotor_RightSpeed(uint8_t speed_percentage);

/*****************************************************************************
* Function Name : DCmotor_forward
* Description   : Drives both motors forward at the given speed.
*                 Internally sets IN1/IN3 HIGH and IN2/IN4 LOW.
* Parameters    :
*   - speed_percentage : Desired speed (0–100%)
* Return        : void
*****************************************************************************/
void DCmotor_forward(uint8_t speed_percentage);

/*****************************************************************************
* Function Name : DCmotor_Backward
* Description   : Drives both motors backward at the given speed.
*                 Internally sets IN1/IN3 LOW and IN2/IN4 HIGH.
* Parameters    :
*   - speed_percentage : Desired speed (0–100%)
* Return        : void
*****************************************************************************/
void DCmotor_Backward(uint8_t speed_percentage);

/*****************************************************************************
* Function Name : DCmotor_Right
* Description   : Turns the robot to the right by stopping the **right motor (ENA)**
*                 and driving the **left motor (ENB)** forward.
* Parameters    :
*   - speed_percentage : Desired speed (0–100%)
* Return        : void
*****************************************************************************/
void DCmotor_Right(uint8_t speed_percentage);

/*****************************************************************************
* Function Name : DCmotor_left
* Description   : Turns the robot to the left by stopping the **left motor (ENB)**
*                 and driving the **right motor (ENA)** forward.
* Parameters    :
*   - speed_percentage : Desired speed (0–100%)
* Return        : void
*****************************************************************************/
void DCmotor_left(uint8_t speed_percentage);

#endif /* INC_DCMOTOR_INTERFACE_H_ */
