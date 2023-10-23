
#include "STD_TYPES.h"
#include "SSD_interface.h"
#include "DIO_interface.h"
#include <util/delay.h>
int main(void)
{
	/*Create TWO seven segment*/
	/*typedef struct
{
	u8 COM_TYPE;
	u8 PORT;
	u8 EnablePort;
	u8 EnablePin;
}SSD_t;*/
	SSD_t SSD1 = {COM_Anode,DIO_u8PORTB,DIO_u8PORTB,DIO_u8PIN6};
	SSD_t SSD2 = {COM_Anode,DIO_u8PORTB,DIO_u8PORTB,DIO_u8PIN5};
	SSD_t SSD3 = {COM_Anode,DIO_u8PORTB,DIO_u8PORTA,DIO_u8PIN2};
	SSD_t SSD4 = {COM_Anode,DIO_u8PORTB,DIO_u8PORTA,DIO_u8PIN3};
	u8 a,b,c,d;
	while(1)
	{
		/*Hna ana mlesh d3wa el multiplexing sh8al azay ana bs b5rg el rkm*/
		//pass the number i want and the address of the object of the struct

		/*BIT Masking*/
		//DIO_u8SetPortDirection(DIO_u8PORTB,0b11101000);
		/*SSD_u8SetNumber(2,&SSD1);
		SSD_u8SetNumber(3,&SSD2);
		SSD_u8SetNumber(2,&SSD3);
		SSD_u8SetNumber(3,&SSD4);*/

		/*Counting up*/
		for(a=0;a<9;a++)
		{
			//SSD_u8SetNumber(a,&SSD1);
			//_delay_ms(500);
			for(b=0;b<9;b++)
			{
				//SSD_u8SetNumber(b,&SSD2);
				//_delay_ms(500);
				for(c=0;c<9;c++)
				{
					//SSD_u8SetNumber(c,&SSD3);
					//_delay_ms(500);
					for(d=0;d<9;d++)
					{
						/*Delay on the whole operation to be able to see the change*/
						for (u8 i=0;i<50;i++)
						{
						SSD_u8SetNumber(a,&SSD1);
						SSD_u8SetNumber(b,&SSD2);
						SSD_u8SetNumber(c,&SSD3);
						SSD_u8SetNumber(d,&SSD4);
						}

					}
				}
			}
		}

	}
}
