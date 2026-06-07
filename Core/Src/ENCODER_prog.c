/*
 * ENCODER_prog.c
 *
 *  Created on: Mar 4, 2026
 *      Author: Hassan Arif
 */

#include<stdint.h>

#include"BIT_MATH.h"
#include"GPIO_config.h"
#include"GPIO_interface.h"
#include"EXTI_config.h"
#include"EXTI_interface.h"
#include"ENCODER_config.h"
#include"ENCODER_interface.h"



// Encoder 1 port
static GPIO_TypeDef *ENCODER1_PORT = GPIOA;
static EXTI_GPIO_Port ENCODER1_EXTI_PORT=GPIO_PORT_A;
// Encoder 2 port
static GPIO_TypeDef *ENCODER2_PORT = GPIOB;
static EXTI_GPIO_Port ENCODER2_EXTI_PORT=GPIO_PORT_B;
// encoder 1
static volatile int32_t encoder1_count = 0;
static volatile int32_t previous1_count=0;

static volatile uint8_t last_A1 = 0;
static volatile uint8_t last_B1 = 0;



// encoder 2
static volatile int32_t encoder2_count = 0;
static volatile int32_t previous2_count=0;

static volatile uint8_t last_A2 = 0;
static volatile uint8_t last_B2 = 0;



/*  Private Functions  */
static void ENCODER1_ProcessState(void) {
    uint8_t A = GPIO_ReadPin(ENCODER1_PORT, A1);
    uint8_t B = GPIO_ReadPin(ENCODER1_PORT, B1);

    if (A != last_A1 || B != last_B1) {
        if (A ^ last_B1)
            encoder1_count++;
        else
            encoder1_count--;

        last_A1 = A;
        last_B1 = B;
    }
}

static void ENCODER2_ProcessState(void) {
    uint8_t A = GPIO_ReadPin(ENCODER2_PORT, A2);
    uint8_t B = GPIO_ReadPin(ENCODER2_PORT, B2);

    if (A != last_A2 || B != last_B2) {
        if (A ^ last_B2)
            encoder2_count++;
        else
            encoder2_count--;

        last_A2 = A;
        last_B2 = B;
    }
}



//Callback wrappers
static void encoder1_callback_A(void) { ENCODER1_ProcessState(); }
static void encoder1_callback_B(void) { ENCODER1_ProcessState(); }
static void encoder2_callback_A(void) { ENCODER2_ProcessState(); }
static void encoder2_callback_B(void) { ENCODER2_ProcessState(); }



//main functions
void ENCODER_EXTI_Init(uint8_t encoder_x){
switch(encoder_x){
case ENCODER_1:
	RCC_EnableGPIOx(ENCODER1_PORT);

	GPIO_SetPinMode(ENCODER1_PORT, A1, INPUT_PU_PD);
	GPIO_SetPinMode(ENCODER1_PORT, B1, INPUT_PU_PD);
	GPIO_WritePin(ENCODER1_PORT, A1,HIGH);
	GPIO_WritePin(ENCODER1_PORT, B1,HIGH);

	EXTI_Init(ENCODER1_EXTI_PORT, A1, BOTH_EDGES);
	EXTI_Init(ENCODER1_EXTI_PORT, B1, BOTH_EDGES);

	EXTI_SetCallBack(encoder1_callback_A, A1);
	EXTI_SetCallBack(encoder1_callback_B, B1);

	EXTI_EnableLine(A1);
	EXTI_EnableLine(B1);

	last_A1=GPIO_ReadPin(ENCODER1_PORT, A1);
	last_B1=GPIO_ReadPin(ENCODER1_PORT, B1);

	encoder1_count=0;
	break;
case ENCODER_2:
	RCC_EnableGPIOx(ENCODER2_PORT);

	GPIO_SetPinMode(ENCODER2_PORT, A2, INPUT_PU_PD);
	GPIO_SetPinMode(ENCODER2_PORT, B2, INPUT_PU_PD);
	GPIO_WritePin(ENCODER2_PORT, A2,HIGH);
	GPIO_WritePin(ENCODER2_PORT, B2,HIGH);

	EXTI_Init(ENCODER2_EXTI_PORT, A2, BOTH_EDGES);
	EXTI_Init(ENCODER2_EXTI_PORT, B2, BOTH_EDGES);

	EXTI_SetCallBack(encoder2_callback_A, A2);
	EXTI_SetCallBack(encoder2_callback_B, B2);

	EXTI_EnableLine(A2);
	EXTI_EnableLine(B2);

	last_A2=GPIO_ReadPin(ENCODER2_PORT, A2);
	last_B2=GPIO_ReadPin(ENCODER2_PORT, B2);

	encoder2_count=0;
	break;



}
}






int32_t ENCODER_GetCount(uint8_t encoder_x){
	switch(encoder_x){
	case ENCODER_1 :
	return encoder1_count;
	break;

	case ENCODER_2 :
	return encoder2_count;
	break;

	default :
	return 0;
	break;



	}

}



void ENCODER_SetCount(uint8_t encoder_x, int32_t count){

	switch(encoder_x){
		case ENCODER_1 :
		 encoder1_count=count;
		break;

		case ENCODER_2 :
		encoder2_count=count;
		break;


		}


}





int8_t ENCODER_GetDirection(uint8_t encoder_x){
  int8_t dir=0;
	switch(encoder_x){
			case ENCODER_1 :
			 if(encoder1_count>previous1_count) dir= FORWARD;
			 else if(encoder1_count<previous1_count)  dir= REVERSE;
			 else dir= STOPPED;
			 previous1_count=encoder1_count;
			break;


			case ENCODER_2 :
			 if(encoder2_count>previous2_count)  dir=FORWARD;
			 else if(encoder2_count<previous2_count) dir= REVERSE;
			 else  dir= STOPPED;
			 previous2_count=encoder2_count;
			break;

			}

	return dir;

}




