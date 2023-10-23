/******************************************************/
/******************************************************/
/**************		Author:Basem Moufreh 	***********/
/**************		Layer:HAL    			***********/
/**************		SWC:SSD					***********/
/**************		Version:1.00			***********/
#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "SSD_interface.h"
#include <util\delay.h>
#include "BIT_MATH.h"


u8 SSD_u8SetNumber(u8 Copy_u8Number,SSD_t* SSD)
{
	/*Check for errors*/
	u8 Local_u8ErrorState=0,temp;

	/*Numbers of the seven segment from 0 TO 9*/
	//int Seven_segment_inc[10]={0b11111,0b11110,0b11101,0b11100,0b11011,0b11010,0b111001,0b10000,0b1111,0b0110};
	int Seven_segment_inc[10]={0,1,2,3,0b00000100,0b00000101,6,7,8,9};
	/*Check Comman type*/
	if (SSD ->COM_TYPE ==COM_Anode)
	{


		/*Display the number to the port*/
		DIO_u8SetPortDirection(SSD->PORT,DIO_u8PORT_OUTPUT);//make the port output
		DIO_u8SetPinDirection(SSD->EnablePort,SSD->EnablePin,DIO_u8PIN_OUTPUT);//make the enable pin direction output

		//temp = (Copy_u8Number & 0x07) | (((Copy_u8Number)&(0x8))<<1);
		//temp &=Copy_u8Number;
		/*DIO_GetPinValue(DIO_u8PORTB,DIO_u8PIN0,&Copy_u8Number);
		DIO_GetPinValue(DIO_u8PORTB,DIO_u8PIN1,&Copy_u8Number);
		DIO_GetPinValue(DIO_u8PORTB,DIO_u8PIN2,&Copy_u8Number);
		DIO_GetPinValue(DIO_u8PORTB,DIO_u8PIN3,&Copy_u8Number);*/

		DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN0,GET_BIT(Copy_u8Number,0));
		DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN1,GET_BIT(Copy_u8Number,1));
		DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN2,GET_BIT(Copy_u8Number,2));
		DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN4,GET_BIT(Copy_u8Number,3));
		//DIO_u8SetPortValue(SSD->PORT,Seven_segment_inc[temp]);//display The desired number
		DIO_u8SetPinValue(SSD->EnablePort,SSD->EnablePin,DIO_u8PIN_LOW);//enable 7 segment
		_delay_ms(3);//Delay for multiplexing
		DIO_u8SetPinValue(SSD->EnablePort,SSD->EnablePin,DIO_u8PIN_HIGH);//disable 7 segment
		//DIO_u8SetPortValue(SSD->PORT,DIO_u8PORT_LOW);//Output nothing on the 7 segment
		/*DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN0,DIO_u8PIN_LOW);
		DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN1,DIO_u8PIN_LOW);
		DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN2,DIO_u8PIN_LOW);
		DIO_u8SetPinValue(DIO_u8PORTB,DIO_u8PIN4,DIO_u8PIN_LOW);*/
		_delay_ms(3);//Delay for multiplexing


	}


	else if(SSD ->COM_TYPE ==COM_Cathode)
	{
		/*Display the number to the port*/
		DIO_u8SetPortDirection(SSD->PORT,DIO_u8PORT_OUTPUT);//make the port output
		DIO_u8SetPinDirection(SSD->EnablePort,SSD->EnablePin,DIO_u8PIN_OUTPUT);//make the enable pin direction output
		/*Make the number to the port*/
		DIO_u8SetPortValue(SSD->PORT,Seven_segment_inc[Copy_u8Number]);//display The desired number
		DIO_u8SetPinValue(SSD->EnablePort,SSD->EnablePin,DIO_u8PIN_LOW);//enable 7 segment
		_delay_ms(10);//Delay for multiplexing
		DIO_u8SetPinValue(SSD->EnablePort,SSD->EnablePin,DIO_u8PIN_HIGH);//disable 7 segment
		DIO_u8SetPortValue(SSD->PORT,DIO_u8PORT_LOW);//Output nothing on the 7 segment
		_delay_ms(10);//Delay for multiplexing
	}
	else
	{
		Local_u8ErrorState=1;
	}

	return Local_u8ErrorState;
}

