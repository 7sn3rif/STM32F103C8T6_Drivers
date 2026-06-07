/*
 * EXTI_prog.c
 *
 *  Created on: Feb 12, 2026
 *      Author: Hassan Arif
 */
#include"BIT_MATH.h"
#include"stm32f1xx.h"
#include"GPIO_interface.h"
#include"EXTI_config.h"
#include"EXTI_interface.h"



 static void (*EXTI_Callbacks[16])(void) = {0};




void EXTI_Init(EXTI_GPIO_Port GPIO_Port_x,uint8_t EXTIx , uint8_t mode){


    RCC_EnableAFIO();

	//map the gpio port to the exti line
	uint8_t regIndex=0;
	uint8_t pos=EXTIx;

	if(EXTIx>=EXTI0 && EXTIx<=EXTI3){
		regIndex=0;

	}
	else if(EXTIx>=EXTI4 && EXTIx<=EXTI7){
			regIndex=1;
			pos-=4;

		}
	else if(EXTIx>=EXTI8 && EXTIx<=EXTI11){
				regIndex=2;
				pos-=8;

			}
	else if(EXTIx>=EXTI12 && EXTIx<=EXTI15){
					regIndex=3;
					pos-=12;

				}

	else{
		//out of range
     return;
	}

	AFIO->EXTICR[regIndex]&= ~( (0b1111) << (4 * pos));
	AFIO->EXTICR[regIndex] |=( GPIO_Port_x << (4 * pos));


	//unmask event and interrupt
	Set_Bit(EXTI->IMR,EXTIx);
	//SET_BIT(EXTI->EMR,EXTIx);


	//set mode
   switch(mode){
     case RISING_EDGE:
    	 Set_Bit(EXTI->RTSR,EXTIx);
    	 Clr_Bit(EXTI->FTSR,EXTIx); break;
     case FALLING_EDGE:
         	 Set_Bit(EXTI->FTSR,EXTIx);
         	 Clr_Bit(EXTI->RTSR,EXTIx); break;
     case BOTH_EDGES:
         	 Set_Bit(EXTI->RTSR,EXTIx);
         	 Set_Bit(EXTI->FTSR,EXTIx); break;

   }
   Set_Bit(EXTI->PR, EXTIx);
}













void EXTI_EnableLine(uint8_t EXTIx){
	if(EXTIx==EXTI0){
		NVIC_EnableIRQn(EXTI0_IRQn);
	}
	else if(EXTIx==EXTI1){
		NVIC_EnableIRQn(EXTI1_IRQn);
	}

	else if(EXTIx==EXTI2){
		NVIC_EnableIRQn(EXTI2_IRQn);
	}
	else if(EXTIx==EXTI3){
		NVIC_EnableIRQn(EXTI3_IRQn);
	}

	else if(EXTIx==EXTI4){
		NVIC_EnableIRQn(EXTI4_IRQn);
	}
	else if((EXTIx>=EXTI5)&&(EXTIx<=EXTI9)){
		NVIC_EnableIRQn(EXTI9_5_IRQn);
	}
	else if((EXTIx>=EXTI10)&&(EXTIx<=EXTI15)){
			NVIC_EnableIRQn(EXTI15_10_IRQn);
		}
	else{
		return;
	}
}









void EXTI_DisableLine(uint8_t EXTIx ){
	     if(EXTIx==EXTI0){
			NVIC_DisableIRQn(EXTI0_IRQn);
		}
		else if(EXTIx==EXTI1){
			NVIC_DisableIRQn(EXTI1_IRQn);
		}

		else if(EXTIx==EXTI2){
			NVIC_DisableIRQn(EXTI2_IRQn);
		}
		else if(EXTIx==EXTI3){
			NVIC_DisableIRQn(EXTI3_IRQn);
		}

		else if(EXTIx==EXTI4){
			NVIC_DisableIRQn(EXTI4_IRQn);
		}
		else if((EXTIx>=EXTI5)&&(EXTIx<=EXTI9)){
			NVIC_DisableIRQn(EXTI9_5_IRQn);
		}
		else if((EXTIx>=EXTI10)&&(EXTIx<=EXTI15)){
			NVIC_DisableIRQn(EXTI15_10_IRQn);
			}
		else{
			return;
		}
	}















void EXTI_SetCallBack(void (*function_ptr)(void), uint8_t EXTIx)
{
	if (EXTIx > EXTI15) return;
	if (function_ptr == NULL) return;

	EXTI_Callbacks[EXTIx] = function_ptr;
}












//Helper functions
void NVIC_EnableIRQn(uint8_t EXTIx_IRQn ){
if(EXTIx_IRQn<32){
	Set_Bit(NVIC->ISER[0],EXTIx_IRQn);
                 }
else{
	Set_Bit(NVIC->ISER[1],(EXTIx_IRQn-32));

    }
}





void NVIC_DisableIRQn(uint8_t EXTIx_IRQn ){
	if(EXTIx_IRQn<32){
		Set_Bit(NVIC->ICER[0],EXTIx_IRQn);
	                 }
	else{
		Set_Bit(NVIC->ICER[1],(EXTIx_IRQn-32));

	    }
}






//ISRs
void EXTI0_IRQHandler(void)
{
    if (Get_Bit(EXTI->PR, EXTI0)) {
        if (EXTI_Callbacks[EXTI0] != NULL) {
            EXTI_Callbacks[EXTI0]();
        }
        Set_Bit(EXTI->PR, EXTI0);   // clear pending
    }
}

void EXTI1_IRQHandler(void)
{
    if (Get_Bit(EXTI->PR, EXTI1)) {
        if (EXTI_Callbacks[EXTI1] != NULL) {
            EXTI_Callbacks[EXTI1]();
        }
        Set_Bit(EXTI->PR, EXTI1);   // clear pending
    }
}

void EXTI2_IRQHandler(void)
{
    if (Get_Bit(EXTI->PR, EXTI2)) {
        if (EXTI_Callbacks[EXTI2] != NULL) {
            EXTI_Callbacks[EXTI2]();
        }
        Set_Bit(EXTI->PR, EXTI2);   // clear pending
    }
}

void EXTI3_IRQHandler(void)
{
    if (Get_Bit(EXTI->PR, EXTI3)) {
        if (EXTI_Callbacks[EXTI3] != NULL) {
            EXTI_Callbacks[EXTI3]();
        }
        Set_Bit(EXTI->PR, EXTI3);   // clear pending
    }
}

void EXTI4_IRQHandler(void)
{
    if (Get_Bit(EXTI->PR, EXTI4)) {
        if (EXTI_Callbacks[EXTI4] != NULL) {
            EXTI_Callbacks[EXTI4]();
        }
        Set_Bit(EXTI->PR, EXTI4);   // clear pending
    }
}

void EXTI9_5_IRQHandler(void)
{
    for (uint8_t line = 5; line <= 9; line++) {
        if (Get_Bit(EXTI->PR, line)) {
            if (EXTI_Callbacks[line] != NULL) {
                EXTI_Callbacks[line]();
            }
            Set_Bit(EXTI->PR, line);   // clear pending
        }
    }
}

void EXTI15_10_IRQHandler(void)
{
    for (uint8_t line = 10; line <= 15; line++) {
        if (Get_Bit(EXTI->PR, line)) {
            if (EXTI_Callbacks[line] != NULL) {
                EXTI_Callbacks[line]();
            }
            Set_Bit(EXTI->PR, line);   // clear pending
        }
    }
}
