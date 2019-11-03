/*
 * OS.h
 *
 *  Created on: Oct 22, 2019
 *        Author: PeterKleber & Ahmed Ehab
 */

#ifndef OS_H_
#define OS_H_

#include <avr/io.h>
#include"std_types.h"
#include "Timer.h"
#include "OS_cnfg.h"



#define BUFFER_SIZE ((uint8)3)

typedef enum {Ready,Running,Waiting,Deleted,Idle}Status_t;

typedef enum {
 PERIODIC, ONE_SHOT,NO_MODE
 } Rotation_t;

typedef enum {
	OS_NOK, OS_OK
} EnmOSError_t;


typedef struct{
	void (*Ptr) (void);
	uint16 Run_Time ;
	Rotation_t Mode ;
	Status_t Status ;
	uint8 Priority; //0 is the max priority
	uint16 Task_Counter;
}ST_Task_Info;

EnmOSError_t OS_Init (const OS_ConfigType * ConfigPtr );
EnmOSError_t OS_DeInit ( void ) ;
void OS_Run(void);
EnmOSError_t OS_Create_Task(const ST_Task_Info *ST_Incoming_Task_Info );
EnmOSError_t OS_Delete_Task(const ST_Task_Info * ST_Incoming_Task_Info );
void CPU_Sleep (void);
void ISR_Generated_Flag_Setter();


#endif /* OS_H_ */
