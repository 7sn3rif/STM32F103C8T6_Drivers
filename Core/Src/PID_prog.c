/*
 * PID_prog.c
 *
 *  Created on: Feb 25, 2026
 *      Author: Hassan Arif
 */

#include"PID_interface.h"




void PID_Init(PID_TypeDef *pid, float kp, float ki, float kd, float out_min, float out_max) {
    pid->kp = kp;
    pid->ki = ki;
    pid->kd = kd;

    pid->integral = 0.0f;
    pid->derivative = 0.0f;
    pid->last_error = 0.0f;

    pid->out_min = out_min;
    pid->out_max = out_max*0.5;// half the actual output
}

void PID_SetIntegralLimit(PID_TypeDef *pid, float integral_limit){

	 pid->integral_limit = integral_limit;

}



float PID_Compute(PID_TypeDef *pid , float setpoint , float feedback , float dt){
	float error = setpoint - feedback;

	//Proportional
	float P  =  pid->kp*error;
	//Integral
	pid->integral+= error*dt;
	pid->integral=constrain(pid->integral,pid->integral_limit,-pid->integral_limit);
	float I  = pid->ki*pid->integral;

    //Derivative
	pid->derivative=(error-pid->last_error)/dt;
	float D =  (pid->kd*pid->derivative);
    //PID output
    float PID_output= P+I+D;
   PID_output= constrain(PID_output,pid->out_max,pid->out_min);
    pid->last_error=error;


    return PID_output;

}


void PID_SetGains(PID_TypeDef *pid , float kp, float ki, float kd){

	    pid->kp = kp;
	    pid->ki = ki;
	    pid->kd = kd;



}


float constrain(float val, float max_val, float min_val ){
	if(val>max_val) val = max_val;
	else if(val<min_val)   val=min_val;
	return val;

}

