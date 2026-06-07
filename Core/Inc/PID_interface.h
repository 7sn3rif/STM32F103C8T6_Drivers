/*
 * PID_interface.h
 *
 *  Created on: Feb 25, 2026
 *      Author: Hassan Arif
 */

#ifndef INC_PID_INTERFACE_H_
#define INC_PID_INTERFACE_H_

/*****************************************************************************
* Struct Name   : PID_TypeDef
* Description   : Defines the parameters and state variables for a PID controller.
* Members       :
*   - kp, ki, kd        : Proportional, integral, and derivative gains.
*   - derivative        : Stores the last computed derivative term.
*   - integral          : Accumulated integral term (with windup protection).
*   - last_error        : Stores the previous error for derivative calculation.
*   - out_min, out_max  : Output limits to constrain the PID output.
*   - integral_limit    : Limit for the integral term to prevent windup.
*****************************************************************************/
typedef struct{

    /*** Gains ***/
    float kp;   // Proportional gain
    float ki;   // Integral gain
    float kd;   // Derivative gain

    /*** State variables ***/
    float derivative;   // Derivative term
    float integral;     // Integral term
    float last_error;   // Previous error

    /*** Limits ***/
    float out_min;        // Minimum output limit
    float out_max;        // Maximum output limit
    float integral_limit; // Maximum allowed integral accumulation

} PID_TypeDef;

/*****************************************************************************
* Function Name : PID_Init
* Description   : Initializes a PID controller with given gains and output limits.
* Parameters    :
*   - pid      : Pointer to PID_TypeDef structure
*   - kp, ki, kd : Gains for proportional, integral, and derivative terms
*   - out_min, out_max : Minimum and maximum output limits
* Return        : void
*****************************************************************************/
void PID_Init(PID_TypeDef *pid , float kp, float ki, float kd, float out_min, float out_max);

/*****************************************************************************
* Function Name : PID_SetIntegralLimit
* Description   : Sets the maximum allowed integral accumulation to prevent windup.
* Parameters    :
*   - pid            : Pointer to PID_TypeDef structure
*   - integral_limit : Maximum allowed integral value
* Return        : void
*****************************************************************************/
void PID_SetIntegralLimit(PID_TypeDef *pid, float integral_limit);

/*****************************************************************************
* Function Name : PID_Compute
* Description   : Computes the PID output based on setpoint, feedback, and time step.
* Parameters    :
*   - pid      : Pointer to PID_TypeDef structure
*   - setpoint : Desired target value
*   - feedback : Measured system value
*   - dt       : Time step (seconds)
* Return        : float (PID output constrained within limits)
*****************************************************************************/
float PID_Compute(PID_TypeDef *pid , float setpoint , float feedback , float dt);

/*****************************************************************************
* Function Name : PID_SetGains
* Description   : Updates the PID gains dynamically.
* Parameters    :
*   - pid : Pointer to PID_TypeDef structure
*   - kp, ki, kd : New proportional, integral, and derivative gains
* Return        : void
*****************************************************************************/
void PID_SetGains(PID_TypeDef *pid , float kp, float ki, float kd);

/*****************************************************************************
*  Helping function Name : constrain
* Description   : Constrains a value within given maximum and minimum limits.
* Parameters    :
*   - val     : Input value
*   - max_val : Maximum allowed value
*   - min_val : Minimum allowed value
* Return        : float (constrained value)
*****************************************************************************/
float constrain(float val, float max_val, float min_val);

#endif /* INC_PID_INTERFACE_H_ */
