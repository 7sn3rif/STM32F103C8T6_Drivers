/*
 * GPIO_prog.c
 *
 *  Created on: Dec 15, 2025
 *      Author: Hassan Arif
 */


#include"BIT_MATH.h"
#include"stm32f1xx.h"

#include "GPIO_config.h"
#include "GPIO_interface.h"


 void RCC_EnableGPIOx(GPIO_TypeDef *GPIOx){
	if (GPIOx==GPIOA){
	Set_Bit(RCC->APB2ENR,2)	;//Enable PORTA
		}
	else if (GPIOx==GPIOB){
		Set_Bit(RCC->APB2ENR,3) ;//Enable PORTB
			}
	else if (GPIOx==GPIOC){
			Set_Bit(RCC->APB2ENR,4) ;//Enable PORTC
				}
}



 void RCC_EnableAFIO(){
	 Set_Bit(RCC->APB2ENR,0);
 }


 void GPIO_SetPinMode(GPIO_TypeDef *GPIOx,uint8_t pin , uint32_t mode){
	 if(pin<8){
		 GPIOx->CRL &= ~(0xF << (BITS_PER_PIN * pin));
		GPIOx->CRL|=(mode<<(BITS_PER_PIN*pin));
	 }
	 else if(pin>=8){
		 GPIOx->CRH &= ~(0xF << ((pin - 8) * BITS_PER_PIN));
		 GPIOx->CRH |=  (mode << ((pin - 8) * BITS_PER_PIN));

	 }
 }





 void GPIO_WritePin(GPIO_TypeDef *GPIOx,uint8_t pin,uint8_t val){
if(val==HIGH){

Set_Bit(GPIOx->ODR,pin);
}
else if(val==LOW){
Clr_Bit(GPIOx->ODR,pin);
}
 }



 void GPIO_TogglePin(GPIO_TypeDef *GPIOx,uint8_t pin){
	 Toggle_Bit(GPIOx->ODR,pin);

 }

 uint8_t GPIO_ReadPin(GPIO_TypeDef *GPIOx,uint8_t pin){
	 return Get_Bit(GPIOx->IDR,pin);
 }

