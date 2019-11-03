/*
 * OS_cnfg.h
 *
 *  Created on: Oct 22, 2019
 *       Author: PeterKleber & Ahmed Ehab
 */

#ifndef OS_CNFG_H_
#define OS_CNFG_H_

#include"std_types.h"
#include"Timer.h"

typedef enum {
	TIMER_0, TIMER_1, TIMER_2
} Timer_ID;

typedef struct {
	Timer_ID timer;
	uint8 Resolution;
} OS_ConfigType ;

extern OS_ConfigType OS_cnfg ;

#endif /* OS_CNFG_H_ */
