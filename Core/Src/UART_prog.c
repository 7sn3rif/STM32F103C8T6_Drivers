/*
 * UART_prog.c
 *
 *  Created on: Dec 28, 2025
 *      Author:Hassan Arif
 */
#include "BIT_MATH.h"
#include"stm32f1xx.h"
#include "UART_config.h"
#include "UART_interface.h"
#include "GPIO_config.h"
#include"GPIO_interface.h"


void RCC_EnableUARTx(USARTx UART_Channel){

	switch(UART_Channel){
	case UART_CHANNEL_1:
		Set_Bit(RCC->APB2ENR,14);
		    break;
	case UART_CHANNEL_2:
			Set_Bit(RCC->APB1ENR,17);
			break;
	case UART_CHANNEL_3:
			Set_Bit(RCC->APB1ENR,18);
		     break;
	}
}





void UART_Init(USARTx UART_Channel){//--> USARTx--> UARt channel (1-->3)
	uint32_t BRR_val=F_OSC_in_HZ/UART_BAUD_RATE;
	//first of all enable clock gatting for uartx and gpiox and set the pin modes, set frame bits , enable uart
	switch(UART_Channel){
	case UART_CHANNEL_1:
		RCC_EnableUARTx(UART_CHANNEL_1);
		RCC_EnableGPIOx(GPIOA);
		GPIO_SetPinMode( GPIOA,9,A_F_PUSH_PULL_50MHZ);
		GPIO_SetPinMode(GPIOA,10 ,FLOATING_INPUT);
		USART1->BRR=BRR_val;
	    Clr_Bit(USART1->CR1,12);
	    Set_Bit(USART1->CR1,2);  // receiver enable
	    Set_Bit(USART1->CR1,3); // transmitter enable
	    Set_Bit(USART1->CR1,13);
		 break;
	case UART_CHANNEL_2:
		RCC_EnableUARTx(UART_CHANNEL_2);
		RCC_EnableGPIOx(GPIOA);
		GPIO_SetPinMode( GPIOA,2,A_F_PUSH_PULL_50MHZ);


		GPIO_SetPinMode(GPIOA,3 ,FLOATING_INPUT);
		USART2->BRR=BRR_val;
	    Clr_Bit(USART2->CR1,12);
	    Set_Bit(USART2->CR1,2);
	    Set_Bit(USART2->CR1,3);
	    Set_Bit(USART2->CR1,13);
		break;
	case UART_CHANNEL_3:
		RCC_EnableUARTx(UART_CHANNEL_3);
		RCC_EnableGPIOx(GPIOB);
		GPIO_SetPinMode( GPIOB,10,A_F_PUSH_PULL_50MHZ);
		GPIO_SetPinMode(GPIOB,11,FLOATING_INPUT);
		USART3->BRR=BRR_val;
	    Clr_Bit(USART3->CR1,12);
	    Set_Bit(USART3->CR1,2);
	    Set_Bit(USART3->CR1,3);
	    Set_Bit(USART3->CR1,13);
		break;
	}

}





void UART_SendData(USARTx UART_Channel , uint8_t data){
	switch(UART_Channel){
	case UART_CHANNEL_1:
	    USART1->DR=data;
	    while(Get_Bit(USART1->SR,6)==0);
	    break;
	case UART_CHANNEL_2:
		USART2->DR=data;
		while(Get_Bit(USART2->SR,6)==0);
		break;
	case UART_CHANNEL_3:
		USART3->DR=data;
		while(Get_Bit(USART3->SR,6)==0);
		break;

	}
}



void UART_SendString(USARTx UART_Channel, uint8_t *string){

	while(*string !='\0'){

		UART_SendData(UART_Channel, *string);
		string++;

	}
}




uint8_t UART_ReceiveData(USARTx UART_Channel ){

	switch(UART_Channel){
	case UART_CHANNEL_1:
		while(Get_Bit(USART1->SR,5)==0);
		return (uint8_t)USART1->DR;
        break;
	case UART_CHANNEL_2:
			while(Get_Bit(USART2->SR,5)==0);
			return (uint8_t)USART2->DR;
	        break;
	case UART_CHANNEL_3:
			while(Get_Bit(USART3->SR,5)==0);
			return (uint8_t)USART3->DR;
	        break;
	default: return 0;
}
}
