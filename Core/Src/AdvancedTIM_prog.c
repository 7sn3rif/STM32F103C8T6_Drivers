/*
 * AdvancedTIM_prog.c
 *
 *  Created on: Feb 23, 2026
 *      Author: Hassan Arif
 */

#include"BIT_MATH.h"
#include"stm32f1xx.h"
#include"GPIO_config.h"
#include"GPIO_interface.h"
#include"AdvancedTIM_config.h"
#include"AdvancedTIM_interface.h"

static uint32_t arr_val=0;

void TIM1_PWMInit(TIM1_Channel CHx_PAx,uint32_t f_pwm){
	//Enable GPIOA and AFIO and TIM1
	RCC_EnableAFIO();
	RCC_EnableGPIOx(GPIOA);
	Set_Bit(RCC->APB2ENR,11);//--> Enable Timer 1
	//Set Pin mode:
	GPIO_SetPinMode(GPIOA, CHx_PAx, A_F_PUSH_PULL_50MHZ);



/*
 * prescaler = (F_CPU/1000000) - 1
 *  F CPU = 8MHZ --> in the config.h file
 *  f timer = F CPU / prescaler + 1
 *  f timer = 1MHZ
 */
  TIM1->PSC=PRESCALER;//, = (F CPU/1000000) -1


  /* Enable Auto-Reload Preload */
     Set_Bit(TIM1->CR1, 7);   // ARPE = 1


  /* ARR = ( F timer / F PWM ) -1

   */

  arr_val=(F_TIMER/f_pwm)-1;
  TIM1->ARR=arr_val;//-> set auto reload value



  /* Generate update event to load PSC & ARR */
      Set_Bit(TIM1->EGR, 0);   // UG bit



  /*
   Setting the PWM mode and enable Capture Compare
   */
  switch(CHx_PAx) {
    case CH1_PA8:
      TIM1->CCMR1 &= ~(0b111 << 4);     // clear OC1M
      TIM1->CCMR1 |=  (0b110 << 4);     // OC1M = 110 (PWM mode 1)
      Set_Bit(TIM1->CCMR1, 3);          // OC1PE = 1 (preload enable)
      Set_Bit(TIM1->CCER,0);            //Capture Compare Output Enable
      break;

    case CH2_PA9:
      TIM1->CCMR1 &= ~(0b111 << 12);    // clear OC2M
      TIM1->CCMR1 |=  (0b110 << 12);    // OC2M = 110 (PWM mode 1)
      Set_Bit(TIM1->CCMR1, 11);         // OC2PE = 1 (preload enable)
      Set_Bit(TIM1->CCER,4);            //Capture Compare Output Enable
      break;

    case CH3_PA10:
      TIM1->CCMR2 &= ~(0b111 << 4);     // clear OC3M
      TIM1->CCMR2 |=  (0b110 << 4);     // OC3M = 110 (PWM mode 1)
      Set_Bit(TIM1->CCMR2, 3);          // OC3PE = 1 (preload enable)
      Set_Bit(TIM1->CCER,8);            //Capture Compare Output Enable
      break;

    case CH4_PA11:
      TIM1->CCMR2 &= ~(0b111 << 12);    // clear OC4M
      TIM1->CCMR2 |=  (0b110 << 12);    // OC4M = 110 (PWM mode 1)
      Set_Bit(TIM1->CCMR2, 11);         // OC4PE = 1 (preload enable)
      Set_Bit(TIM1->CCER,12);            //Capture Compare Output Enable
      break;

  }

  // Enable main Output
  Set_Bit(TIM1->BDTR,15);

  //Start Counting
  Set_Bit(TIM1->CR1,0);


}





void TIM1_WritePWM(TIM1_Channel CHx_PAx,uint8_t duty_cycle){
    if(duty_cycle>100){

    	duty_cycle=100;
    }
	uint32_t ccr_val = ((duty_cycle * (arr_val + 1)) / 100);
	//write CCR val
	switch(CHx_PAx){
	 case CH1_PA8 :
		 TIM1->CCR1=ccr_val;
		 break;
	 case CH2_PA9 :
		 TIM1->CCR2=ccr_val;
		 break;
	 case CH3_PA10:
		 TIM1->CCR3=ccr_val;
		 break;
	 case CH4_PA11 :
	     TIM1->CCR4=ccr_val;
	     break;




	                 }
}
