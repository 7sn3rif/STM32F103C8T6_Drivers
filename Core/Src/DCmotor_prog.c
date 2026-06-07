/*
 * DCmotor_prog.c
 *
 *  Created on: Feb 27, 2026
 *      Author: LENOVO
 */

#include"stm32f1xx.h"
#include"BIT_MATH.h"
#include"GPIO_config.h"
#include"GPIO_interface.h"
#include"AdvancedTIM_config.h"
#include"AdvancedTIM_interface.h"
#include"DCmotor_config.h"
#include"DCmotor_interface.h"


void DCmotor_Init(){

	TIM1_PWMInit(ENA, 12500);
	TIM1_PWMInit(ENB, 12500);
	RCC_EnableGPIOx(DC_MOTOR_PORT);
	GPIO_SetPinMode(DC_MOTOR_PORT,IN1, G_P_PUSH_PULL_50MHZ);
	GPIO_SetPinMode(DC_MOTOR_PORT,IN2, G_P_PUSH_PULL_50MHZ);
	GPIO_SetPinMode(DC_MOTOR_PORT,IN3, G_P_PUSH_PULL_50MHZ);
	GPIO_SetPinMode(DC_MOTOR_PORT,IN4, G_P_PUSH_PULL_50MHZ);

}


void DCmotor_LeftSpeed(uint8_t speed_percentage){

	TIM1_WritePWM(ENB, speed_percentage);
	GPIO_WritePin(DC_MOTOR_PORT, IN3, HIGH);
	GPIO_WritePin(DC_MOTOR_PORT, IN4, LOW);


}

void DCmotor_RightSpeed(uint8_t speed_percentage){

	TIM1_WritePWM(ENA, speed_percentage);
	GPIO_WritePin(DC_MOTOR_PORT, IN1, HIGH);
	GPIO_WritePin(DC_MOTOR_PORT, IN2, LOW);


}









void DCmotor_forward(uint8_t speed_percentage){
	   TIM1_WritePWM(ENA, speed_percentage);
	   GPIO_WritePin(DC_MOTOR_PORT, IN1, HIGH);
	   GPIO_WritePin(DC_MOTOR_PORT, IN2, LOW);
	   TIM1_WritePWM(ENB, speed_percentage);
	   GPIO_WritePin(DC_MOTOR_PORT, IN3, HIGH);
	   GPIO_WritePin(DC_MOTOR_PORT, IN4, LOW);

}



void DCmotor_Backward(uint8_t speed_percentage){
	       TIM1_WritePWM(ENA, speed_percentage);
		   GPIO_WritePin(DC_MOTOR_PORT, IN1, LOW);
		   GPIO_WritePin(DC_MOTOR_PORT, IN2, HIGH);
		   TIM1_WritePWM(ENB, speed_percentage);
		   GPIO_WritePin(DC_MOTOR_PORT, IN3, LOW);
		   GPIO_WritePin(DC_MOTOR_PORT, IN4, HIGH);


}


void DCmotor_Right(uint8_t speed_percentage){
	   TIM1_WritePWM(ENA, 0);
	   GPIO_WritePin(DC_MOTOR_PORT, IN1, LOW);
	   GPIO_WritePin(DC_MOTOR_PORT, IN2, LOW);
	   TIM1_WritePWM(ENB, speed_percentage);
	   GPIO_WritePin(DC_MOTOR_PORT, IN3, HIGH);
	   GPIO_WritePin(DC_MOTOR_PORT, IN4, LOW);





}
void DCmotor_left(uint8_t speed_percentage){


	   TIM1_WritePWM(ENA, speed_percentage);
	   GPIO_WritePin(DC_MOTOR_PORT, IN1, HIGH);
	   GPIO_WritePin(DC_MOTOR_PORT, IN2, LOW);
	   TIM1_WritePWM(ENB, 0);
	   GPIO_WritePin(DC_MOTOR_PORT, IN3, LOW);
	   GPIO_WritePin(DC_MOTOR_PORT, IN4, LOW);


}




