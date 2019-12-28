/*
 * OS.c
 *
 *  Created on: Oct 22, 2019
 *      Author: PeterKleber
 */

#include "OS.h"

static uint8 Buffer_ptr = 0;
static uint8 OS_init_flag = 0;
volatile uint16 OS_Tick_Count = 0;
volatile uint8 ISR_Generated_Flag = 0;
//static uint8 System_Tick_Count = 0 ;
//static uint16 Max_Run_Time = 0;
static uint8 Timer_Select ;	

static uint8 Current_Ready_Task_Counter=0;
static uint8 Total_Ready_Task = 0;
static uint8 Task_Iterator = 0;
ST_Task_Info Task_Buffer[BUFFER_SIZE];

ST_Task_Info *Task_Ready_Buffer[BUFFER_SIZE];

static void Sorting_Tasks(void);

//Call back function for the ISR to set the flag
void ISR_Systick (void) 
{ 
	PORTB &= ~(1<<PB4);
	PORTB ^= (1<<PB0);
	uint8 i=0;
	Task_Iterator = 0;
	for ( i = 0; i < Buffer_ptr; i++)
	{
		Task_Buffer[i].Task_Counter++;											 //when an ISR happens increment all the Task counter
				
		if(Task_Buffer[i].Task_Counter == Task_Buffer[i].Run_Time )				 // compare the task counter by its Run time
		{
			Task_Buffer[i].Task_Counter=0;										 // Reset the task counter when it reached its turn
			Task_Buffer[i].Status = Ready ;										 //make the Current Status of current Task be Ready
			Task_Ready_Buffer[Current_Ready_Task_Counter]=(&Task_Buffer[i]);	 //Copy the address of the ready Tasks into another buffer for processing where Task_Ready_Buffer is a array of pointer to structure
			Current_Ready_Task_Counter++;										 // See how many tasks that has the turn to be run at this system tick ( Count how many ready tasks at this system tick )
		}
	}
			
	Total_Ready_Task = Current_Ready_Task_Counter;
}


void CPU_Sleep (void)
{
		MCUCR |= (1<<SE);
}


EnmOSError_t OS_Init(const OS_ConfigType *ConfigPtr) 
{
	Timer_Select = ConfigPtr->timer;
	
	if (OS_init_flag == 0) 
	{
		if (ConfigPtr != NULL_PTR) 
		{
			//Initialize Task buffer
			for (uint8 i = 0; i < BUFFER_SIZE; i++) 
			{
				Task_Buffer[i].Ptr = NULL_PTR;
				Task_Buffer[i].Run_Time = 0;
				Task_Buffer[i].Mode = NO_MODE;     //Outside the enum values
				Task_Buffer[i].Status = Idle;
				Task_Buffer[i].Priority = (uint8)200; 
				Task_Buffer[i].Task_Counter = 0;
			}

			TIMER_ID_init(Timer_Select);
			
			//send callback function
			if ((ConfigPtr->timer) == TIMER_0) 
			{
				Timer0_COMP_Set_Callback(ISR_Systick);
			} else if ((ConfigPtr->timer) == TIMER_1) 
			{
				Timer1_COMP_Set_Callback(ISR_Systick);
			} else if ((ConfigPtr->timer) == TIMER_2) 
			{
				Timer2_COMP_Set_Callback(ISR_Systick);
			}

			Time_Delay(Timer_Select,(ConfigPtr->Resolution), ms);		
			OS_init_flag = 1;
		}
	}

	return OS_OK;
}

EnmOSError_t OS_Create_Task(const ST_Task_Info *ST_Incoming_Task_Info )
{
	EnmOSError_t OS_Error = OS_OK;
	
	if (OS_init_flag == 1) 
	{

		if (ST_Incoming_Task_Info->Ptr != NULL_PTR) 
		{

			if (Buffer_ptr < BUFFER_SIZE) 
			{
				Task_Buffer[Buffer_ptr].Ptr = ST_Incoming_Task_Info->Ptr;
				Task_Buffer[Buffer_ptr].Mode = ST_Incoming_Task_Info->Mode;
				Task_Buffer[Buffer_ptr].Run_Time = ST_Incoming_Task_Info->Run_Time;
				Task_Buffer[Buffer_ptr].Status = Ready;
				Task_Buffer[Buffer_ptr].Priority = ST_Incoming_Task_Info->Priority;
				
				Sorting_Tasks();
				
				Buffer_ptr++;
			}
			
			else
			{
				OS_Error = OS_NOK;
			}
		}
		
		else
		{
			OS_Error = OS_NOK;	
		}
	}
	return OS_Error;
}

static void Sorting_Tasks ( void )
{
	uint8 i=0;
	ST_Task_Info Swap_temp;
	uint8 Sorting_Flag=0;
	
//Bubble Sort
	do 
	{
		Sorting_Flag=0;
		
		for(i=0; i<Buffer_ptr ; i++)
		{
			if(Task_Buffer[i].Priority > Task_Buffer[i+1].Priority )
			{
				Sorting_Flag++;
				Swap_temp = Task_Buffer[i];
				Task_Buffer[i] = Task_Buffer[i+1];
				Task_Buffer[i+1] = Swap_temp;
			
			}
		}
	} while ( Sorting_Flag >0);



}

void OS_Run(void) 
{
  if (OS_init_flag == 1)
  {
	TIMER_Start(Timer_Select);
	
	/*******************************************************************************************/

	while(1)
	{
		/*******************************************************************************************/
		if(Current_Ready_Task_Counter>0)
		{
			for ( Task_Iterator = 0; Task_Iterator < Total_Ready_Task ; Task_Iterator++)	// loop on the ready tasks at this system tick and run it (execute it)
			{
				if (Task_Ready_Buffer[Task_Iterator]->Status == Ready)
				{
					Task_Ready_Buffer[Task_Iterator]->Status = Running;
					void (*Ptr_to_excute)(void) = Task_Ready_Buffer[Task_Iterator]->Ptr;
					Ptr_to_excute();
					Task_Ready_Buffer[Task_Iterator]->Status = Waiting;	
				}
			} //end of the for loop on the ready tasks

			Current_Ready_Task_Counter--;
		}	
			
		/*******************************************************************************************/
			
		 else if(Current_Ready_Task_Counter == 0)
			{
				PORTB |= (1<<PB4);
				CPU_Sleep ();
			
			}
					
	
	} // end of while (1)
		
  } // end of the OS_init_flag condition
} // end of the OS_Run Function
	

EnmOSError_t OS_Delete_Task(const ST_Task_Info *ST_Incoming_Task_Info)
{
	if (OS_init_flag == 1)
	{
		if (ST_Incoming_Task_Info->Ptr != NULL_PTR)
		{
			for (uint8 i = 0; i < Buffer_ptr; i++)
			{

				if ((ST_Incoming_Task_Info->Ptr == Task_Buffer[i].Ptr)) { //Search for the function in the buffer
					Task_Buffer[i].Status = Deleted;
					//Overwrite the not active element with the last active one
					if (Buffer_ptr > 1)
					{
						Task_Buffer[i].Ptr = Task_Buffer[Buffer_ptr - 1].Ptr;
						Task_Buffer[i].Mode = Task_Buffer[Buffer_ptr - 1].Mode;
						Task_Buffer[i].Run_Time =Task_Buffer[Buffer_ptr - 1].Run_Time;
						Task_Buffer[i].Status = Task_Buffer[Buffer_ptr - 1].Status;
						Task_Buffer[i].Priority = Task_Buffer[Buffer_ptr - 1].Priority;

						Buffer_ptr--;
					}
				}
			}

		}
	}
	return OS_OK;
}


EnmOSError_t OS_DeInit ( void )
{
	if (OS_init_flag == 1)
	{
		//Clear the Buffer
		for (uint8 i = 0; i < Buffer_ptr; i++)
		{
			Task_Buffer[i].Ptr = NULL_PTR;
			Task_Buffer[i].Run_Time = 0;
			Task_Buffer[i].Mode = NO_MODE; //Outside the enum values
			Task_Buffer[i].Status = Idle;
			Task_Buffer[i].Priority = (uint8)255;
		}

		Buffer_ptr = 0; //return Buffer_ptr to zero

		OS_init_flag = 0;

		return OS_OK;
	}
	else
	{
		return OS_NOK;
	}
	return OS_OK;
}

