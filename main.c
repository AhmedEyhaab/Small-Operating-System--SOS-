/*
 * main.c
 *
 *  Created on: Oct 22, 2019
 *      Author: PeterKleber & Ahmed Ehab
 */


#include "OS.h"
#include<util/delay.h>

void Task1 (void);
void Task2 (void);
void Task3 (void);

ST_Task_Info Task_1_Info={Task1,6,PERIODIC,Ready,1};
ST_Task_Info Task_2_Info={Task2,3,PERIODIC,Ready,2};
ST_Task_Info Task_3_Info={Task3,12,PERIODIC,Ready,3};


int main()
{
	DDRD = 0xFF;
	DDRC = 0xFF;
	DDRB = 0xFF;
	
	OS_Init(&OS_cnfg);

	OS_Create_Task(&Task_1_Info);
	OS_Create_Task(&Task_2_Info);
	OS_Create_Task(&Task_3_Info);

	OS_Run();

	return 0;

}


void Task1 (void)
{
	PORTC ^= (1<<PC5);
	/*_delay_us(50);
	PORTC ^= (1<<PC5);*/
}

void Task2 (void)
{
	PORTC ^= (1<<PC6);
	/*_delay_us(50);
	PORTC ^= (1<<PC6);*/
}

void Task3 (void)
{
	PORTC ^= (1<<PC7);
	/*_delay_us(50);
	PORTC ^= (1<<PC7);*/
}
