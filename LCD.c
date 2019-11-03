/*
 * LCD_FUNCTIONS.c
 *
 *
 *  Author: HOBA
 */
//library

#include "LCD.h"

//--------------------------------------------------------------------------------------------------------------------------//

#if LCD_MODE

void LCD_4Bits_Initialization (void)
	{
		LCD_4Bits_DDR = 0xFF; 						//LCD port is output
		LCD_4Bits_PORT &= ~ (1<<LCD_EN) ;			//LCD_EN = 0
		_delay_us (1000) ;							//wait for initialization and Stable Power.
		LCD_4Bits_Write_Command (0x33) ;			//$33 for 4-bit mode
		_delay_ms(100) ; 							//wait 100 microsecond between each command sent
		LCD_4Bits_Write_Command (0x32);				//$32 for 4-bit mode
		_delay_ms (100) ; 							//wait 100 microsecond between each command sent
		LCD_4Bits_Write_Command (0x28) ; 			//$28 for 4-bits, LCD 2 line , 5x7 matrix
		_delay_ms (100); 							//wait 100 microsecond between each command sent
		LCD_4Bits_Write_Command (0x0E);				//display on, cursor on
		_delay_ms (100);							//wait 100 microsecond between each command sent
		LCD_4Bits_Write_Command (0x01);				//Clear LCD
		_delay_us (2000);							//long wait as clear command takes a long time
		LCD_4Bits_Write_Command (0x06) ; 			//shift cursor right
		_delay_ms (100) ;
	}
//--------------------------------------------------------------------------------------------------------------------------//
	
void LCD_4Bits_Write_Command ( unsigned char Command )
 {

LCD_4Bits_PORT = (LCD_4Bits_PORT & 0x0F) | (Command & 0xF0) ;					//Send the Highest Nibble in Command to the outPort
LCD_4Bits_PORT &= ~(1<<LCD_RS);													//RS = 0 for command
LCD_4Bits_PORT &= ~  (1<<LCD_RW);												//RW = 0 for write

LCD_4Bits_PORT  |= (1<<LCD_EN);													//EN = 1 for High-to-Low
_delay_ms(5);																	//wait to make EN wider
LCD_4Bits_PORT &= ~ (1<<LCD_EN) ;												//EN = 0 for High-to-Low
_delay_ms(20);																	//wait for the least nibble of the Command

LCD_4Bits_PORT = (LCD_4Bits_PORT & 0x0F) | (Command <<4) ;					    // Shift the least nibble by 4 to send the Highest Nibble in   Command  to the outPort
LCD_4Bits_PORT  |= ( 1 << LCD_EN ) ;											//EN = 1 for High-to-Low
_delay_ms (1) ;																	//wait to make EN wider
LCD_4Bits_PORT &= ~ ( 1 << LCD_EN) ;											//EN = 0 for High-to-Low

}						

//wait
//--------------------------------------------------------------------------------------------------------------------------//

void LCD_4Bits_Write_Data ( unsigned char Data )
{

//static unsigned char X_axis = 1 , Y_axis = 1;

LCD_4Bits_PORT  = (LCD_4Bits_PORT & 0x0F) | (Data & 0xF0) ;			//Send the Highest Nibble in data to the outPort
LCD_4Bits_PORT |= (1 << LCD_RS);									//RS = 1 for data
LCD_4Bits_PORT &= ~ (1 << LCD_RW);									//RW = 0 for write

LCD_4Bits_PORT |= (1 << LCD_EN);									//EN = 1    for High-to-Low
 _delay_ms(5) ;
LCD_4Bits_PORT &= ~(1<< LCD_EN) ; 									//EN = 0   for High-to-Low

_delay_ms(20);														//wait for the least nibble of the Command

LCD_4Bits_PORT = (LCD_4Bits_PORT & 0x0F) | (Data <<4) ;			    // shift the least nibble by 4 to send the Highest Nibble in data  to the outPort.
LCD_4Bits_PORT |=(1 << LCD_EN);										//EN = 1    for High-to-Low
 _delay_us(5) ;
LCD_4Bits_PORT &= ~ (1<< LCD_EN) ; 									//EN = 0   for High-to-Low

/*
	X_axis++ ;

	if (X_axis >= 16 && Y_axis <3 )
	{
		X_axis = 1;
		Y_axis++;
		if (Y_axis == 3 )
		{
			X_axis = 1 , Y_axis = 1;
			LCD_4Bits_Clear();

		}

		else
		{
				LCD_4Bits_Cursor_Position(2,1);
		}

	}
*/

}
//--------------------------------------------------------------------------------------------------------------------------//
	
void LCD_4Bits_Cursor_Position( unsigned char y , unsigned char x)   		// define Cursor Position in the LCD
{
unsigned char firstCharAdr [ ] ={0x80,0xC0,0x94,0xD4} ;			// See the Table of Cursor Position adjustment

LCD_4Bits_Write_Command (  firstCharAdr [y-1] + x - 1);
_delay_ms(100);
 }
//--------------------------------------------------------------------------------------------------------------------------//

void LCD_4Bits_Clear (void)
{
    LCD_4Bits_Write_Command (0x01);			 //Clear LCD
    _delay_us (2000);			 //long wait as clear command takes a long time
	LCD_4Bits_Cursor_Position ( 1 , 1) ;
}
//--------------------------------------------------------------------------------------------------------------------------//

void LCD_4Bits_Shift_Right(void)
{
	LCD_4Bits_Write_Command(0x0C);
}
//--------------------------------------------------------------------------------------------------------------------------//

void LCD_4Bits_Shift_Left(void)
{
	LCD_4Bits_Write_Command(0x08);
}
//--------------------------------------------------------------------------------------------------------------------------//

void LCD_4Bits_Print_Character( char row , char column , char ch )
{
	
	LCD_4Bits_Cursor_Position(row,column);
	
	LCD_4Bits_Write_Data (ch );

}
//--------------------------------------------------------------------------------------------------------------------------//

void LCD_4Bits_Print_String( char row , char column , char *str )
{

	LCD_4Bits_Cursor_Position(row,column);
	unsigned char i = 0;

	while (str [i] != '\0')                 // till reaches its end (null Terminator)
		{
		LCD_4Bits_Write_Data (str[i] );
		i++ ;
		}
}
//--------------------------------------------------------------------------------------------------------------------------//
	
void LCD_4Bits_Print_Number(char row , char column ,long num)
{
	
	LCD_4Bits_Cursor_Position(row,column);
	
	if (0<=num)
	{
		
		if (num<=9) LCD_4Bits_Write_Data(num+'0');
		
		else if(num<=99)
		{
			LCD_4Bits_Write_Data((num/10)+'0');
			LCD_4Bits_Write_Data((num%10)+'0');
		}
		else if(num<=999)
		{
			LCD_4Bits_Write_Data((num/100)+'0');
			LCD_4Bits_Write_Data(((num/10)%10)+'0');
			LCD_4Bits_Write_Data((num%10)+'0');
		}
		
		else if(num<=99999)
		{
			LCD_4Bits_Write_Data( ( (num/10000) ) +'0');
			LCD_4Bits_Write_Data( ( (num/1000) %10 )+'0');
			LCD_4Bits_Write_Data( ( (num/100) %10 ) +'0');
			LCD_4Bits_Write_Data( ( (num/10) %10 )+'0');
			LCD_4Bits_Write_Data((num%10)+'0');
		}
	}
	
	if (0>num)
	{
		num = -1*num;
		
		if (num<=9)
		{
			LCD_4Bits_Write_Data('-');
			LCD_4Bits_Write_Data(num+'0');
		}
		else if(num<=99)
		{
			LCD_4Bits_Write_Data('-');
			LCD_4Bits_Write_Data((num/10)+'0');
			LCD_4Bits_Write_Data((num%10)+'0');
		}
		else if(num<=999)
		{
			LCD_4Bits_Write_Data('-');
			LCD_4Bits_Write_Data((num/100)+'0');
			LCD_4Bits_Write_Data(((num/10)%10)+'0');
			LCD_4Bits_Write_Data((num%10)+'0');
		}
		
	}

}
//--------------------------------------------------------------------------------------------------------------------------//

#else


void LCD_8Bits_Initialization (void )
{
	LCD_8Bits_DATA_DDR = 0xFF;			         //make the Data Port an Outport.
	LCD_8Bits_COMMAND_DDR = 0xFF; 				 //make the Command Port an Outport.
	LCD_8Bits_COMMAND_PORT &= ~ (1<<LCD_EN) ;    //LCD_EN = 0
	_delay_us(2000); 							 //wait for initialization and Stable Power.
	LCD_8Bits_Write_Command (0x38) ; 			 //8-bits, LCD 2 line , 5x7 matrix
	LCD_8Bits_Write_Command (0x0E);  			 //display on, cursor on
	LCD_8Bits_Write_Command (0x01) ;	 		 //Clear LCD
	_delay_us(2000); 							 //long wait since clear command takes long time
	LCD_8Bits_Write_Command (0x06);				 //shift cursor right
}
//--------------------------------------------------------------------------------------------------------------------------//

void LCD_8Bits_Write_Command ( unsigned char Command )
{
	LCD_8Bits_DATA_PORT = Command;  				 //send Command to data port
	LCD_8Bits_COMMAND_PORT &= ~ (1 << LCD_RS);  	//RS = 0 for command
	LCD_8Bits_COMMAND_PORT &= ~ (1 << LCD_RW); 		//RW = 0 for write
	LCD_8Bits_COMMAND_PORT |= (1 << LCD_EN); 		//EN = 1 for High-to-Low pulse
	_delay_us(1); 									//wait to make enable wide
	LCD_8Bits_COMMAND_PORT &= ~ (1<<LCD_EN) ;		//EN = 0 for High-to-Low pulse
	_delay_us (100);								//wait to make enable wide
}
//--------------------------------------------------------------------------------------------------------------------------//

void LCD_8Bits_Write_Data ( unsigned char Data )
{
	//static unsigned char X_axis = 1 , Y_axis = 1;
	
	LCD_8Bits_DATA_PORT = Data; 				//send Data to Data port
	LCD_8Bits_COMMAND_PORT |= (1<<LCD_RS) ;                           //RS = 1 for data
	LCD_8Bits_COMMAND_PORT &= ~ (1<<LCD_RW);  		//RW = 0 for write
	LCD_8Bits_COMMAND_PORT |= (1 << LCD_EN); 		//EN = 1 for High-to-Low pulse
	_delay_us(1); 						//wait to make enable wide
	LCD_8Bits_COMMAND_PORT &= ~ (1<<LCD_EN) ;		//EN = 0 for High-to-Low pulse
	_delay_us (100);						//wait to make enable wide
	
	/*
		X_axis++ ;

		if (X_axis >= 16 && Y_axis <3 )
		{
			X_axis = 1;
			Y_axis++;
			if (Y_axis == 3 )
			{
				X_axis = 1 , Y_axis = 1;
				LCD_8Bits_Clear();

			}

			else
			{
				LCD_8Bits_Cursor_Position(2,1);
			}

		}
	*/
}
//--------------------------------------------------------------------------------------------------------------------------//

void LCD_8Bits_Cursor_Position( unsigned char y , unsigned char x)   		// define Cursor Position in the LCD
{
	unsigned char firstCharAdr [ ] ={0x80,0xC0,0x94,0xD4} ;			// See the Table of Cursor Position adjustment

	LCD_8Bits_Write_Command (  firstCharAdr [y-1] + x - 1);
	_delay_ms(100);
}
//--------------------------------------------------------------------------------------------------------------------------//

void LCD_8Bits_Clear (void)
{
	LCD_8Bits_Write_Command (0x01);			 //Clear LCD
	_delay_us (2000);			 //long wait as clear command takes a long time
	LCD_8Bits_Cursor_Position ( 1 , 1) ;
}
//--------------------------------------------------------------------------------------------------------------------------//

void LCD_8Bits_Shift_Right(void)
{
	LCD_8Bits_Write_Command(0x0C);
}
//--------------------------------------------------------------------------------------------------------------------------//

void LCD_8Bits_Shift_Left(void)
{
	LCD_8Bits_Write_Command(0x08);
}
//--------------------------------------------------------------------------------------------------------------------------//

void LCD_8Bits_Print_Character( char row , char column ,  char ch )
{
	 LCD_8Bits_Cursor_Position(row,column);
	 LCD_8Bits_Write_Data ( ch );

}
//--------------------------------------------------------------------------------------------------------------------------//

void LCD_8Bits_Print_String( char row , char column , char *str )
{
	LCD_8Bits_Cursor_Position(row,column);
	unsigned char i = 0;

	while (str [i] != '\0')                 // till reaches its end (null Terminator)
	{
		LCD_8Bits_Write_Data (str[i] );
		i++ ;
	}
}
//--------------------------------------------------------------------------------------------------------------------------//

void LCD_8Bits_Print_Number( char row , char column ,long num)
{
	LCD_8Bits_Cursor_Position(row,column);
	
	if (0<=num)
	{
		
		if (num<=9) LCD_8Bits_Write_Data(num+'0');
		else if(num<=99)
		{
			LCD_8Bits_Write_Data((num/10)+'0');
			LCD_8Bits_Write_Data((num%10)+'0');
		}
		else if(num<=999)
		{
			LCD_8Bits_Write_Data((num/100)+'0');
			LCD_8Bits_Write_Data(((num/10)%10)+'0');
			LCD_8Bits_Write_Data((num%10)+'0');
		}
		
		else if(num<=99999)
		{
			LCD_8Bits_Write_Data( ( (num/10000) ) +'0');
			LCD_8Bits_Write_Data( ( (num/1000) %10 )+'0');
			LCD_8Bits_Write_Data( ( (num/100) %10 ) +'0');
			LCD_8Bits_Write_Data( ( (num/10) %10 )+'0');
			LCD_8Bits_Write_Data((num%10)+'0');
		}
	}
	
	if (0>num)
	{
		num = -1*num;
		
		if (num<=9)
		{
			LCD_8Bits_Write_Data('-');
			LCD_8Bits_Write_Data(num+'0');
		}
		else if(num<=99)
		{
			LCD_8Bits_Write_Data('-');
			LCD_8Bits_Write_Data((num/10)+'0');
			LCD_8Bits_Write_Data((num%10)+'0');
		}
		else if(num<=999)
		{
			LCD_8Bits_Write_Data(0x2d);
			LCD_8Bits_Write_Data((num/100)+'0');
			LCD_8Bits_Write_Data(((num/10)%10)+'0');
			LCD_8Bits_Write_Data((num%10)+'0');
		}
		
	}

}

#endif
//--------------------------------------------------------------------------------------------------------------------------//


