/*
 * AdvancedTIM_config.h
 *
 *  Created on: Feb 23, 2026
 *      Author: Hassan Arif
 */

#ifndef INC_ADVANCEDTIM_CONFIG_H_
#define INC_ADVANCEDTIM_CONFIG_H_


#define F_CPU      8000000UL //8 MHZ

#define PRESCALER  (F_CPU/1000000UL)-1//  f timer = f CPU / prescaler +1 , now the f timer is 1MHZ

#define F_TIMER     F_CPU/(PRESCALER+1)


#endif /* INC_ADVANCEDTIM_CONFIG_H_ */
