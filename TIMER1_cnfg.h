
//-------------------------------------------------------------------------------------------------//

//NOTE you should only use one mode in Timer 1 at a time

//-------------------------------------------------------------------------------------------------//

#ifndef _TIMER1_CNFG_H

#define _TIMER1_CNFG_H

//Configure Prescalar Factor for Timer 1 :-

/*prescalar_index = 0*/
#define STOP_TIMER_1     TCCR1B &= ( ~(1<<CS12) & ~(1<<CS11) & ~(1<<CS10))

/*prescalar_index = 1*/

#define TIMER1_CLEAR_PRESCALAR_BITS TCCR1B &= 0b11111000

#define TIMER1_NO_PRESCALAR()  do{\
                                 TCCR1B |= (1<<CS10);\
                                 TCCR1B &= (~(1<<CS11));\
                                 TCCR1B &= (~(1<<CS12));\
                                 }while(0)

/*prescalar_index = 2*/
#define TIMER1_PRESCALAR_8()   do{TCCR1B |= (1<<CS11);\
					   	        TCCR1B &= (~(1<<CS10) & ~(1<<CS12));}while(0)

/*prescalar_index = 3*/
#define TIMER1_PRESCALAR_64()  do{\
                                 TCCR1B |= (1<<CS11) | (1<<CS10);\
                                 TCCR1B &= (~(1<<CS12)); \
                                } while(0)


/*prescalar_index = 4*/
#define TIMER1_PRESCALAR_256() do{\
                                 TCCR1B |= ((1<<CS12));\
                                 TCCR1B &= (~(1<<CS11) & ~(1<<CS10));\
                                } while(0)

/*prescalar_index = 5*/
#define TIMER1_PRESCALAR_1024() do{\
                                  TCCR1B |= (1<<CS12) | (1<<CS10);\
                                  TCCR1B &= (~(1<<CS11));\
                                 }while(0)

/*prescalar_index = 5*/
#define EXT_TIMER_RISING() do{\
                                  TCCR1B |= (1<<CS12) | (1<<CS10);\
                                  TCCR1B &= (~(1<<CS11));\
                                 }while(0)

/*prescalar_index = 5*/
#define EXT_TIMER_FALLING() do{\
                                  TCCR1B |= (1<<CS12) | (1<<CS10);\
                                  TCCR1B &= (~(1<<CS11));\
                                 }while(0)

//-------------------------------------------------------------------------------------------------//

/*CHOOSE ONLY ONE MODE FOR TIMER 1 AT A TIME*/

//-------------------------------------------------------------------------------------------------//

// 1-Configure (Normal Mode) for Timer 1 :-

#define NORMAL_MODE_TIMER1()  do{\
                                TCCR1A &= (~(1<<WGM10) & ~(1<<WGM11));\
                                TCCR1B &= (~(1<<WGM13) & ~(1<<WGM12));\
                                }while(0)

//-------------------------------------------------------------------------------------------------//

// 2-Configure the Clear on Timer Compare ( CTC mode ) for Timer 1 :-

/* mode_no = 8 */
#define CTC_OCR1A_MODE_TIMER1() do{\
                                   TCCR1A &= (~(1<<WGM10)) & (~(1<<WGM11));\
                                   TCCR1B |= (1<<WGM12);\
                                   TCCR1B &= (~(1<<WGM13));\
                                  }while(0)

/* mode_no = 12 */
#define CTC_ICR1_MODE()  do{\
						  TCCR1A &= (~(1<<WGM10) & ~(1<<WGM11));\
					      TCCR1B |= (1<<WGM12) | (1<<WGM13);\
						 }while(0)

//-------------------------------------------------------------------------------------------------//

//3-Configure (Phase Correct PWM) for Timer 1 :-

/* mode_no = 1 */
#define PWM_PHASE_CORRECT_8_BIT()   do{\
									   TCCR1A |= (1<<WGM10);\
									   TCCR1A &= (~(1<<WGM11));\
									   TCCR1B &= (~(1<<WGM13) & ~(1<<WGM12));\
									   }while(0)

/* mode_no = 2 */
#define PWM_PHASE_CORRECT_9_BIT()  do{\
									 TCCR1A &= (~(1<<WGM10));\
									 TCCR1A |= (1<<WGM11);\
									 TCCR1B &= (~(1<<WGM13) & ~(1<<WGM12));\
									 }while(0)

/* mode_no = 3 */
#define PWM_PHASE_CORRECT_10_BIT() do{\
									 TCCR1A |= (1<<WGM10) | (1<<WGM11); \
									 TCCR1B &= (~(1<<WGM13) & ~(1<<WGM12));\
									}while(0)

/* mode_no = 10 */
#define PWM_PHASE_CORRECT_ICR1()   do{\
									 TCCR1A &= (~(1<<WGM10);\
									 TCCR1A |= (1<<WGM11));\
									 TCCR1B &= (~(1<<WGM12));\
									 TCCR1B |= (1<<WGM13);\
									 }while(0)

/* mode_no = 11 */
#define PWM_PHASE_CORRECT_OCR1A()  do{\
									 TCCR1A |= (1<<WGM10) | (1<<WGM11); \
								     TCCR1B &= (~(1<<WGM12));\
								     TCCR1B |= (1<<WGM13);\
									 }while(0)

//-------------------------------------------------------------------------------------------------//

//4- Configure (FAST PWM) for Timer 1 :-

/* mode_no = 5 */
#define FAST_PWM_8_BIT()	do{\
							   TCCR1A |= (1<<WGM10);\
							   TCCR1A &= (~(1<<WGM11));\
							   TCCR1B |= (1<<WGM12);\
							   TCCR1B &= (~(1<<WGM13));\
							   }while(0)

/* mode_no = 6 */
#define FAST_PWM_9_BIT()	do{\
							   TCCR1A &= (~(1<<WGM10))\
							   TCCR1A |= (1<<WGM11);\
							   TCCR1B |= (1<<WGM12);\
							   TCCR1B &= (~(1<<WGM13));\
							   }while(0)

/* mode_no = 7 */
#define FAST_PWM_10_BIT()	do{\
							   TCCR1A |= (1<<WGM11) | (1<<WGM10);\
							   TCCR1B |= (1<<WGM12);\
							   TCCR1B &= (~(1<<WGM13));\
							   }while(0)

/* mode_no = 14 */
#define FAST_PWM_ICR1()		do{\
							   TCCR1A &= (~(1<<WGM10));\
							   TCCR1A |= (1<<WGM11);\
							   TCCR1B |= (1<<WGM13) | (1<<WGM12);\
							   }while(0)

 /* mode_no = 15 */
#define	FAST_PWM_OCR1A()	do{\
							   TCCR1A |= (1<<WGM10) | (1<<WGM11);\
							   TCCR1B |= (1<<WGM13) | (1<<WGM12);\
							  }while(0)


//-------------------------------------------------------------------------------------------------//


//5- Configure (ICU mode) for Timer 1 using ICR Register :-

/* Rising edge and no noise cancellation */
#define ICU_RISING_EDGE()  do\
							{\
							TCCR1A = 0;\
							TCCR1B |= (1<<ICES1);\
							TCCR1B &= (~(1<<ICNC1));\
							} while(0)

/* Falling edge and no noise cancellation */
#define ICU_FALLING_EDGE() do{\
							TCCR1A = 0;\
							TCCR1B &= (~(1<<ICNC1) & ~(1<<ICES1));\
							}while(0)


//-------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------//

// These are the types of Operation for Normal and CTC mode using OCR1A Register:-

/* COM_Mode_no = 0*/
#define COM_1A_NORMAL()	do{\
							TCCR1A &= (~(1<<COM1A1)) & (~(1<<COM1A0)) ;\
						  }while(0)


/* COM_Mode_no = 1*/
#define COM_1A_TOGGLE()	do{\
						   TCCR1A &= (~(1<<COM1A1));\
						   TCCR1A |= (1<<COM1A0);\
						  }while(0)

/* COM_Mode_no = 2*/
#define COM_1A_CLEAR()	do{\
						   TCCR1A |= (1<<COM1A0);\
						   TCCR1A &= (~(1<<COM1A1));\
						  }while(0)

/* COM_Mode_no = 3*/
#define COM_1A_SET		TCCR1A |= (1<<COM1A1) | (1<<COM1A0)



//-------------------------------------------------------------------------------------------------//

// These are the types of Operation for Fast and Phase Correct PWM mode using OCR1A Register:-

/* COM_Mode_no = 0*/
//Disconnect the PWM, Normal Mode Operation
#define COM_1A_PWM_DISCONNECT		TCCR1A &= (~(1<<COM1A1) & ~(1<<COM1A0))

/* COM_Mode_no = 1*/
#define COM_1A_PWM_TOGGLE_DISCONNECT	 do{\
									TCCR1A |= (1<<COM1A0);\
								    TCCR1A &= (~(1<<COM1A1));\
								   }while(0)


//___________ Channel A __________________//
/* COM_Mode_no = 2*/
#define COM_1A_PWM_NON_INVERTED() do{\
									TCCR1A |= (1<<COM1A0);\
								    TCCR1A &= (~(1<<COM1A1));\
								   }while(0)

/* COM_Mode_no = 3*/
#define COM_1A_PWM_INVERTED()		do{\
									TCCR1A |= (1<<COM1A1) | (1<<COM1A0);\
									}while(0)



//___________ Channel B__________________//
/* COM_Mode_no = 2*/
#define COM_1B_PWM_NON_INVERTED()	do{\
										TCCR1A |= (1<<COM1B1) | (1<<COM1B0);\
									}while(0)


/* COM_Mode_no = 3*/
#define COM_1B_PWM_INVERTED()	do{\
									TCCR1A |= (1<<COM1B0);\
									TCCR1A &= (~(1<<COM1B1));\
								}while(0)	





//-------------------------------------------------------------------------------------------------//

//---------------------------------------------------------------------------//
//Enable Global Interrupt
#define ENABLE_GLOBAL_INTERRUPT  SREG |= 1u<<7


//Configure TIMSK for interrupt for Timer 1 :-

#define ENABLE_TOIE1	TIMSK|= (1<<TOIE1)						//Timer Overflow Interrupt Enable for timer 1.

#define ENABLE_OCIE1A   TIMSK |= (1<<OCIE1A)					//Output Compare Interrupt Enable for timer 1A.

#define ENABLE_OCIE1B	TIMSK|= (1<<OCIE1B)						//Output Compare Interrupt Enable for timer 1B.

#define ENABLE_TICIE1	TIMSK|= (1<<TICIE1)						//Timer (1) Input Capture Interrupt Enable for timer 1.



//-------------------------------------------------------------------------------------------------//

//Configure TIFR for Timer 1 for Polling on Flags :-

#define POLL_ON_TOV1()   while ( (TIFR & (1<<TOV1)) == 0)	 // Polling on the Timer Overflow Flag for timer 1.
#define POLL_ON_OCF1A()  while ( (TIFR & (1<<OCF1A)) == 0)	 // Polling on Output Compare Flag for timer 1A.
#define POLL_ON_OCF1B()  while ( (TIFR & (1<<OCF1B)) == 0)	 // Polling on Output Compare Flag for timer 1B.
#define POLL_ON_ICF1()   while ( (TIFR & (1<<ICF1)) == 0)	 // Polling on the input capture flag.

#define CLEAR_TOV1	  TIFR = ( 1<< TOV1)					 //Clear TOV1 Flag
#define CLEAR_OCF1A	  TIFR = ( 1<< OCF1A)					 //Clear OCF1A Flag
#define CLEAR_OCF1B   TIFR = ( 1<< OCF1B)					 //Clear OCF1B Flag
#define CLEAR_ICF1	  TIFR = ( 1<< ICF1)					 //Clear ICF1 Flag

//-------------------------------------------------------------------------------------------------//


//define Constants Macro :-

#define INVERTING_PWM	  1
#define NON_INVERTING_PWM 0


//-------------------------------------------------------------------------------------------------//

#endif
