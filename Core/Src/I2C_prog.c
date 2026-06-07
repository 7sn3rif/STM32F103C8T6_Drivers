/*
 * I2C_prog.c
 *
 *  Created on: Feb 20, 2026
 *      Author: Hassan Arif
 */
#include"BIT_MATH.h"
#include"stm32f1xx.h"
#include"GPIO_config.h"
#include"GPIO_interface.h"
#include"I2C_config.h"
#include"I2C_interface.h"


void I2C_Init(I2C_TypeDef *I2Cx) {
    // Step 1: Enable RCC clock and configure GPIO depending on instance
    if (I2Cx == I2C1) {
        // Enable I2C1 clock
        Set_Bit(RCC->APB1ENR, 21);

        // Enable GPIOB clock and configure PB6 (SCL), PB7 (SDA)
        RCC_EnableGPIOx(GPIOB);
        GPIO_SetPinMode(GPIOB, 6, A_F_OPEN_DRAIN_50MHZ);
        GPIO_SetPinMode(GPIOB, 7, A_F_OPEN_DRAIN_50MHZ);
    }
    else if (I2Cx == I2C2) {
        // Enable I2C2 clock
        Set_Bit(RCC->APB1ENR, 22);

        // Enable GPIOB clock and configure PB10 (SCL), PB11 (SDA)
        RCC_EnableGPIOx(GPIOB);
        GPIO_SetPinMode(GPIOB, 10, A_F_OPEN_DRAIN_50MHZ);
        GPIO_SetPinMode(GPIOB, 11, A_F_OPEN_DRAIN_50MHZ);
    }

    // Step 2: Reset I2C peripheral
    Set_Bit(I2Cx->CR1, 15);
    Clr_Bit(I2Cx->CR1, 15);

    // Step 3: Set APB1 frequency in MHz
    I2Cx->CR2 = I2C_APB1_FREQ_MHZ;

    // Step 4: Calculate and set CCR (standard mode, 100 kHz)

    uint16_t ccr_val = (I2C_APB1_FREQ_MHZ * 1000000) / (I2C_SPEED_MODE * 2);
    I2Cx->CCR = ccr_val;

    // Step 5: Calculate and set TRISE (standard mode)
   uint8_t trise=1;//Only on standard speed
    uint16_t TRISE_val = (I2C_APB1_FREQ_MHZ*trise) + 1;
    I2Cx->TRISE = TRISE_val;

    // Step 6: Enable the peripheral
    Set_Bit(I2Cx->CR1, 0);
}




Err_status I2C_StartCondition(I2C_TypeDef *I2Cx) {

    Err_status LOC_err = NOErr;
    uint32_t timeoutcount = 0;

    //  Wait until BUSY = 0
    while (Get_Bit(I2Cx->SR2,1)) {
        if (++timeoutcount > 10000) {
            return BusBusyErr;
        }
    }

    //  Generate START
    Set_Bit(I2Cx->CR1, 8);

    timeoutcount = 0;

    //  Wait for SB flag
    while (!(Get_Bit(I2Cx->SR1, 0))) {
        if (++timeoutcount > 10000) {
            LOC_err = StartConditionErr;
            break;
        }
    }

    return LOC_err;
}



Err_status I2C_RepeatedStart(I2C_TypeDef *I2Cx){
	Err_status LOC_err = NOErr;
	    Set_Bit(I2Cx->CR1, 8); // start generation

	    uint32_t timeoutcount = 0;
	    while (!(Get_Bit(I2Cx->SR1, 0))) {
	        if (timeoutcount++ > 10000) {
	            LOC_err = RepeatedStartErr;
	            break;  // exit loop on timeout
	        }
	    }

	    return LOC_err;
	}

void I2C_StopCondition(I2C_TypeDef *I2Cx) {
    uint32_t timeoutcount = 0;

    // Generate STOP condition
    Set_Bit(I2Cx->CR1, 9);

    // Wait until BUSY flag (SR2 bit 1) clears, with timeout
    while (Get_Bit(I2Cx->SR2, 1)) {
        if (++timeoutcount > 10000) {
            // Timeout reached: break out to avoid infinite loop
            break;
        }
    }
}



Err_status I2C_MasterSendAddress(I2C_TypeDef *I2Cx,uint8_t slave_address,I2C_Direction I2C_rw ){
	 Err_status LOC_err=NOErr;
	I2Cx->DR=slave_address<<1|I2C_rw;// Send Address + I2C direction
	uint32_t timeoutcount=0;
	while(!(Get_Bit(I2Cx->SR1,1))){
		//  Check NACK (AF flag)
		        if (Get_Bit(I2Cx->SR1,10))
		        {
		            Clr_Bit(I2Cx->SR1,10);  // Clear AF
		           return NACKErr;
		        }
		if(timeoutcount++ > 10000){
	return AddressSendErr;
		break;
		}
    }
	//only clears Address if it was actually set
	(void)I2Cx->SR1;
	(void)I2Cx->SR2;//Reading it after SR1 to clear address flag
	return LOC_err;
}


Err_status I2C_MasterSendData(I2C_TypeDef *I2Cx,uint8_t data){
	Err_status LOC_err=NOErr;
	I2Cx->DR=data;
	uint32_t timeoutcount=0;
	while(!(Get_Bit(I2Cx->SR1,7))){ //check TXE
			if(timeoutcount++ > 10000){
		LOC_err=DataSendErr;
			break;
			}
	    }

	return LOC_err;

}

Err_status I2C_MasterReadData(I2C_TypeDef *I2Cx,uint8_t *data){
	Err_status LOC_err=NOErr;
	uint32_t timeoutcount=0U;
	while(!(Get_Bit(I2Cx->SR1,6))){//check RXNE
		if(++timeoutcount > 10000U){
			LOC_err=DataReceiveErr;
				break;
				}
	}
	/* Read data register (clears RXNE) */
	*data=(uint8_t)(I2Cx->DR&0xff);//mask it to ensure 8 bit data is taken

	return LOC_err;

}





	Err_status I2C_SlaveAckOrNack(I2C_TypeDef *I2Cx) {
	    Err_status LOC_err = NOErr;

	    // Check ACK bit in CR1 (bit 10)
	    if (Get_Bit(I2Cx->CR1, 10)) {
	        LOC_err = AckStatus;   // Slave will acknowledge
	    } else {
	        LOC_err = NackStatus;  // Slave will not acknowledge
	    }

	    return LOC_err;
	}


	uint8_t I2C_SlaveReceiveData(I2C_TypeDef *I2Cx){
		uint32_t timeoutcount = 0U;
		while(!(Get_Bit(I2Cx->SR1,6))){//check RXNE--> wait for data to be received
				if(++timeoutcount > 10000){
					return 0xff; //timeout indicator
						break;
						}
			}

		return(uint8_t)(I2Cx->DR & 0xFF);
	}




	Err_status I2C_MasterTransmit(I2C_TypeDef *I2Cx, uint8_t slave_address, uint8_t *data, uint16_t length) {
	    Err_status status;

	    // Generate START
	    status = I2C_StartCondition(I2Cx);
	    if (status != NOErr) return status;

	    // Send slave address with WRITE
	    status = I2C_MasterSendAddress(I2Cx, slave_address, I2C_Write);
	    if (status != NOErr) return status;

	    // Send all bytes
	    for (uint16_t i = 0; i < length; i++) {
	        status = I2C_MasterSendData(I2Cx, data[i]);
	        if (status != NOErr) return status;
	    }

	    // Generate STOP
	    I2C_StopCondition(I2Cx);

	    return NOErr;
	}







	Err_status I2C_MasterReceive(I2C_TypeDef *I2Cx,
	                             uint8_t slave_address,
	                             uint8_t *buffer,
	                             uint16_t length)
	{
	    Err_status status;

	    if (length == 0) return NOErr;

	    Set_Bit(I2Cx->CR1,10); // Enable ACK

	    status = I2C_StartCondition(I2Cx);
	    if(status != NOErr) return status;

	    status = I2C_MasterSendAddress(I2Cx,
	                                   slave_address,
	                                   I2C_Read);
	    if(status != NOErr) return status;

	    /*  SINGLE BYTE  */
	    if(length == 1)
	    {
	        Clr_Bit(I2Cx->CR1,10);   // NACK BEFORE receive
	        I2C_StopCondition(I2Cx);

	        status = I2C_MasterReadData(I2Cx,&buffer[0]);
	        return status;
	    }

	    /* MULTI BYTE  */
	    for(uint16_t i=0;i<length;i++)
	    {
	        if(i == length-2)
	        {
	            Clr_Bit(I2Cx->CR1,10); // prepare NACK
	            I2C_StopCondition(I2Cx);
	        }

	        status = I2C_MasterReadData(I2Cx,&buffer[i]);
	        if(status != NOErr) return status;
	    }

	    return NOErr;
	}
