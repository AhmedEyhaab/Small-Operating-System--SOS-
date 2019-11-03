/*
 * TIMER_cnfg.h
 *
 *  Created on: Sep 24, 2019
 *      Author: HOBA
 */

#ifndef TIMER_CNFG_H_
#define TIMER_CNFG_H_

#include "std_types.h"

#include "TIMER1_cnfg.h"


typedef enum {timer0=0,timer1,timer2,NUM_OF_TIMERS=3,CHANNEL_A=10,CHANNEL_B=11,CHANNEL_A_B=12}TIMER_t; // types
	
typedef enum {Channel_A=10,Channel_B,Channel_A_B}Channel_t; // types

#define MAX_NUM_OF_TIMERS 3
#define NA 0xff

//----------------------------------- TIIMER_PINS ------------------------------------//

//Define Output Compare Pin 1A and 1B and Input Capture Register for Timer 1:-

#define DDR_TIMER_1		DDRD
#define PORT_TIMER_1	PORTD
#define PIN_TIMER_1		PIND

#define OC1B	PD4
#define OC1A	PD5
#define ICP		PD6


#define DDR_ICU	 DDRD
#define PORT_ICU PORTD
#define PIN_ICU	 PIND

//Define Output Compare Pin for Timer 0:-

#define DDR_TIMER_0		DDRB
#define PORT_TIMER_0	PORTB
#define PIN_TIMER_0		PINB
#define OC0				PB3

//Define Output Compare Pin for Timer 2:-
#define DDR_TIMER_2		DDRD
#define PORT_TIMER_2	PORTD
#define PIN_TIMER_2		PIND
#define OC2				PD7


/* TIMER # */
#define TIMER0    0
#define TIMER1    1
#define TIMER2    2

/* PRESCALER */
#define PRESCALER0             0
#define PRESCALER8             1
#define PRESCALER64            2
#define PRESCALER256           3
#define PRESCALER1024          4
#define EXTERNAL_CLK_RISING    5
#define EXTERNAL_CLK_FALLING   6

typedef enum { prescaler1=0, prescaler8=1,prescaler64=2,prescaler256=3,prescaler1024=4,prescaler32 = 7,prescaler128 = 8 } prescaler_factor_t;

/* PRESCALER TIMER 2 */
#define PRESCALER32             7
#define PRESCALER128            8

/* WGM MODE */
#define NORMAL_MODE        10
#define CTC_MODE           11
#define FAST_PWM_MODE      12
#define PHASE_CORRECT_MODE 13

typedef enum {NORMAL_mode=10,CTC_mode=11,FAST_PWM_mode=12,PHASE_CORRECT_mode=13  } TIMER_mode_t;
/* COM MODE */
#define NORMAL			  20
#define TOGGLE			  21
#define CLEAR			  22
#define SET				  23

/* Another Naming for COM MODE */
#define NORMAL_OPERATION  20
#define TOGGLE_OPERATION  21
#define CLEAR_OPERATION	  22
#define SET_OPERATION	  23

/* PWM MODE */
#define INVERTING 	   34
#define NON_INVERTING  35

/* INTERRUPT */
#define INTERRUPT     41
#define NO_INTERRUPT  40
#define POLLING		  40

/* ICU */
#define ICU_USED     51
#define NO_ICU_USED  50


/* INITIALIZATION	 */
#define INITIALIZED			1
#define NOT_INITIALIZED		0


//Flag PWM
#define PWM_MODE		71
#define NON_PWM_MODE	70


/* Enable Interrupt Overflow s */
#define ENABLE_OVERFLOW_INTERRUPT_TIMER0	TIMSK |= (1<<TOIE0)
#define ENABLE_OVERFLOW_INTERRUPT_TIMER1	TIMSK |= (1<<TOIE1)
#define ENABLE_OVERFLOW_INTERRUPT_TIMER2	TIMSK |= (1<<TOIE2)


/* Enable Interrupt OUTPUT_COMPARE  */
#define ENABLE_OUTPUT_COMPARE_INTERRUPT_TIMER0		TIMSK |= (1u<<OCIE0)
#define ENABLE_OUTPUT_COMPARE_INTERRUPT_TIMER1		TIMSK |= (1<<OCIE1A)
#define ENABLE_OUTPUT_COMPARE_INTERRUPT_TIMER2		TIMSK |= (1u<<OCIE2)

//-------- Define Channels of Timer 1---------//
#define CHANNEL_A	10
#define CHANNEL_B	11
#define CHANNEL_A_B 12


typedef struct
{
  uint8 timer;
  uint8 WGM_mode;
  uint8 COM_mode;
  uint8 interrupt;
  uint8 ICU;
  uint8 prescalar;
  uint8 IS_init;
} TIMER_cnfg_t ;

extern TIMER_cnfg_t TIMER_cnfg_arr[NUM_OF_TIMERS];

#endif /* TIMER_CNFG_H_ */
