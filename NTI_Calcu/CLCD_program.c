/******************************************************/
/******************************************************/
/**************		Author:Basem Moufreh 	***********/
/**************		Layer:HAL    			***********/
/**************		SWC:CLCD				***********/
/**************		Version:1.00			***********/

#include "STD_TYPES.h"
#include "util/delay.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "PORT_interface.h"

#include "CLCD_interface.h"
#include "CLCD_config.h"
#include "CLCD_private.h"


void CLCD_voidInit(void)
{
#if CLCD_MODE == CLCD_8BIT_MODE
	/*1-Wait more than 30 ms*/
	_delay_ms(40);

	/*Function set Command : 2 Lines (1), 5*8 Font size (0)*/
	CLCD_voidSendCommand(0b00111000);

	/*Display on/off control:Enable display(1),Disable cursor(0),no Blink cursur(0)*/
	CLCD_voidSendCommand(0b00001100);

	/*Clear display*/
	CLCD_voidSendCommand(1);//0b00000001

#elif CLCD_MODE == CLCD_4BIT_MODE
	_delay_ms(40);
	/*Set 4 bit mode*/
	CLCD_voidSendCommand(0b0010);
	/*Function Set*/
	CLCD_voidSendCommand(0b00101000);
	_delay_us(45);
	//set display on/off control
	CLCD_voidSendCommand(0b00001111);

	_delay_us(45);
	//set display clear
	CLCD_voidSendCommand(0b00000001);
	_delay_ms(2);
	//set entry mode
	CLCD_voidSendCommand(0b00000110);

#endif
}


/*
void CLCD_voidInit4_bit(void)
{
	_delay_ms(40);
	Set 4 bit mode
	CLCD_voidSendCommand4_bit(0b0010);
	Function Set
	CLCD_voidSendCommand4_bit(0b00101000);
	_delay_us(45);
	//set display on/off control
	CLCD_voidSendCommand4_bit(0b00001111);
	_delay_us(45);
	//set display clear
	CLCD_voidSendCommand4_bit(0b00000001);
	_delay_ms(2);
	//set entry mode
	CLCD_voidSendCommand4_bit(0b00000110);

}*/

void CLCD_voidSendCommand(u8 Copy_u8Command)
{
#if CLCD_MODE == CLCD_8BIT_MODE
	/*SET RS Pin to LOW For command*/
	DIO_u8SetPinValue(CLCD_CONTROL_PORT,CLCD_RS_PIN,DIO_u8PIN_LOW);

	/*SET RW Pin to LOW To Write*/
	DIO_u8SetPinValue(CLCD_CONTROL_PORT,CLCD_RW_PIN,DIO_u8PIN_LOW);

	/*Set Command to Data Pins*/
	DIO_u8SetPortValue(CLCD_DATA_PORT,Copy_u8Command);

	/*Send Enable Pulse*/
	DIO_u8SetPinValue(CLCD_CONTROL_PORT,CLCD_E_PIN,DIO_u8PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_CONTROL_PORT,CLCD_E_PIN,DIO_u8PIN_LOW);

#elif CLCD_MODE == CLCD_4BIT_MODE

	/*SET RS Pin to LOW For command*/
	DIO_u8SetPinValue(CLCD_CONTROL_PORT,CLCD_RS_PIN,DIO_u8PIN_LOW);

	/*Send Higher data*/
	DIO_u8SetPinValue(CLCD_CONTROL_PORT,CLCD_E_PIN,DIO_u8PIN_HIGH);
	_delay_ms(4);
	u8 datah=((Copy_u8Command >>4)&0x07) | (((Copy_u8Command >>4)&(0x08))<<1);
	DIO_u8SetPortValue(CLCD_DATA_PORT,datah);
	/*Send Enable Pulse*/

	DIO_u8SetPinValue(CLCD_CONTROL_PORT,CLCD_E_PIN,DIO_u8PIN_LOW);
	_delay_ms(4);

	/*Send Lower data*/
	DIO_u8SetPinValue(CLCD_CONTROL_PORT,CLCD_E_PIN,DIO_u8PIN_HIGH);
	_delay_ms(4);
	u8 datal=(Copy_u8Command & 0x07) | (((Copy_u8Command)&(0x08))<<1);
	DIO_u8SetPortValue(CLCD_DATA_PORT,datal);
	/*Send Enable Pulse*/

	DIO_u8SetPinValue(CLCD_CONTROL_PORT,CLCD_E_PIN,DIO_u8PIN_LOW);
	_delay_ms(4);

#endif

}

/*
void CLCD_voidSendCommand4_bit(u8 Copy_u8Command)
{
	SET RS Pin to LOW For command
	DIO_u8SetPinValue(CLCD_CONTROL_PORT,CLCD_RS_PIN,DIO_u8PIN_LOW);

	Send Higher data
	DIO_u8SetPinValue(CLCD_CONTROL_PORT,CLCD_E_PIN,DIO_u8PIN_HIGH);
	_delay_ms(4);
	u16 datah=((Copy_u8Command & 0x70)>>4) | ((Copy_u8Command & 0x80)>>3);
	DIO_u8SetPortValue(CLCD_DATA_PORT,datah);
	Send Enable Pulse

	DIO_u8SetPinValue(CLCD_CONTROL_PORT,CLCD_E_PIN,DIO_u8PIN_LOW);
	_delay_ms(4);

	Send Lower data
	DIO_u8SetPinValue(CLCD_CONTROL_PORT,CLCD_E_PIN,DIO_u8PIN_HIGH);
	_delay_ms(4);
	u16 datal=(Copy_u8Command & 0x07) | ((Copy_u8Command & 0x08)<<1);
	DIO_u8SetPortValue(CLCD_DATA_PORT,datal);
	Send Enable Pulse

	DIO_u8SetPinValue(CLCD_CONTROL_PORT,CLCD_E_PIN,DIO_u8PIN_LOW);
	_delay_ms(4);
}
 */

void CLCD_voidSendData(u8 Copy_u8Data)
{
#if CLCD_MODE == CLCD_8BIT_MODE
	/*SET RS Pin to HIGH For Data*/
	DIO_u8SetPinValue(CLCD_CONTROL_PORT,CLCD_RS_PIN,DIO_u8PIN_HIGH);

	/*SET RW Pin to LOW To Write*/
	DIO_u8SetPinValue(CLCD_CONTROL_PORT,CLCD_RW_PIN,DIO_u8PIN_LOW);

	/*Set Data to Data Pins*/
	DIO_u8SetPortValue(CLCD_DATA_PORT,Copy_u8Data);

	/*Send Enable Pulse*/
	DIO_u8SetPinValue(CLCD_CONTROL_PORT,CLCD_E_PIN,DIO_u8PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_CONTROL_PORT,CLCD_E_PIN,DIO_u8PIN_LOW);

#elif CLCD_MODE == CLCD_4BIT_MODE

	/*SET RS Pin to HIGH For Data*/
	DIO_u8SetPinValue(CLCD_CONTROL_PORT,CLCD_RS_PIN,DIO_u8PIN_HIGH);

	/*Send Higher data*/
	DIO_u8SetPinValue(CLCD_CONTROL_PORT,CLCD_E_PIN,DIO_u8PIN_HIGH);
	_delay_ms(4);
	u8 datah=((Copy_u8Data >>4)&0x07) | (((Copy_u8Data >>4)&(0x08))<<1);
	DIO_u8SetPortValue(CLCD_DATA_PORT,datah);
	/*Send Enable Pulse*/

	DIO_u8SetPinValue(CLCD_CONTROL_PORT,CLCD_E_PIN,DIO_u8PIN_LOW);
	_delay_ms(4);

	/*Send Lower data*/
	DIO_u8SetPinValue(CLCD_CONTROL_PORT,CLCD_E_PIN,DIO_u8PIN_HIGH);
	_delay_ms(4);
	u8 datal=(Copy_u8Data & 0x07) | (((Copy_u8Data)&(0x08))<<1);
	DIO_u8SetPortValue(CLCD_DATA_PORT,datal);
	/*Send Enable Pulse*/

	DIO_u8SetPinValue(CLCD_CONTROL_PORT,CLCD_E_PIN,DIO_u8PIN_LOW);
	_delay_ms(4);

#endif

}

/*
void CLCD_voidSendData4_bit(u8 Copy_u8Data)
{
	SET RS Pin to HIGH For Data
	DIO_u8SetPinValue(CLCD_CONTROL_PORT,CLCD_RS_PIN,DIO_u8PIN_HIGH);

	Send Higher data
	DIO_u8SetPinValue(CLCD_CONTROL_PORT,CLCD_E_PIN,DIO_u8PIN_HIGH);
	_delay_ms(4);
	u16 datah=((Copy_u8Data & 0x70)>>4) | ((Copy_u8Data & 0x80)>>3);
	DIO_u8SetPortValue(CLCD_DATA_PORT,datah);
	Send Enable Pulse

	DIO_u8SetPinValue(CLCD_CONTROL_PORT,CLCD_E_PIN,DIO_u8PIN_LOW);
	_delay_ms(4);

	Send Lower data
	DIO_u8SetPinValue(CLCD_CONTROL_PORT,CLCD_E_PIN,DIO_u8PIN_HIGH);
	_delay_ms(4);
	u16 datal=(Copy_u8Data & 0x07) | ((Copy_u8Data & 0x08)<<1);
	DIO_u8SetPortValue(CLCD_DATA_PORT,datal);
	Send Enable Pulse

	DIO_u8SetPinValue(CLCD_CONTROL_PORT,CLCD_E_PIN,DIO_u8PIN_LOW);
	_delay_ms(4);

}*/

void CLCD_voidSendString(const char* Copy_pcString)
{
#if CLCD_MODE == CLCD_8BIT_MODE
	u8 Local_u8Counter = 0;
	while (Copy_pcString[Local_u8Counter] !='\0')
	{
		CLCD_voidSendData(Copy_pcString[Local_u8Counter]);
		Local_u8Counter++;
	}

#elif CLCD_MODE == CLCD_4BIT_MODE
	u8 Local_u8Counter = 0;
	while (Copy_pcString[Local_u8Counter] !='\0')
	{
		CLCD_voidSendData(Copy_pcString[Local_u8Counter]);
		Local_u8Counter++;
	}

#endif

}

void CLCD_voidGoToXY(u8 Copy_u8XPos,u8 Copy_u8YPos)
{
	/*In case of 20*4 Matrix*/
	/*if you wanted to get back to 16*2 delete third and fourth conditions*/
	u8 Local_u8Address=0;

	if (Copy_u8YPos == 0)
	{
		Local_u8Address = Copy_u8XPos;
	}
	else if(Copy_u8YPos == 1)
	{
		Local_u8Address = Copy_u8XPos+0x40;
	}
	else if(Copy_u8YPos == 2)
	{
		Local_u8Address = Copy_u8XPos+0x14;
	}
	else if(Copy_u8YPos == 3)
	{
		Local_u8Address = Copy_u8XPos+0x54;
	}
	/*How to send the desired memory location*/
	/*from the data sheet Send 1Address to the LCD*/
	CLCD_voidSendCommand(Local_u8Address+128);//128 in binary equals to 0b10000000
}


void CLCD_voidWriteSpecialCharacter(u8* Copy_u8Arr,u8 Copy_u8BlockNumber,u8 Copy_u8XPos,u8 Copy_u8YPos)
{
	u8 Local_u8CGRAMAddress,Local_u8Iterator;
	/*Calculate the CG RAM address whose each block is 8 Byte*/
	Local_u8CGRAMAddress = Copy_u8BlockNumber*8;

	/*Send CG RAM address command to LCD,With setting bit 6*/
	CLCD_voidSendCommand(Local_u8CGRAMAddress+64);//64 in binary 0b01000000

	/*Loop on the array and send the data or the array to the CGRAM*/

	for(Local_u8Iterator=0;Local_u8Iterator<8;Local_u8Iterator++)
	{
		CLCD_voidSendData(Copy_u8Arr[Local_u8Iterator]);
	}

	/*Go to DDRAM*/
	CLCD_voidGoToXY(Copy_u8XPos,Copy_u8YPos);

	/*Send the data on the DDRAM and the data is called by the Block number*/
	CLCD_voidSendData(Copy_u8BlockNumber);

}

void CLCD_voidWriteNumber(u32 Copy_u32Number)
{
	u8 arr[10]="0123456789";//To get the askii value
	u8 LoopCounter;
	u32 i = 1;
	u8 counter=0;//value carry the length of the number
	u32 number = Copy_u32Number;//To save the number before counting its element
	/*To count the number required to be displayed*/
	while (Copy_u32Number>0)
	{
		counter++;
		Copy_u32Number =Copy_u32Number/10;
	}
	/*To calculate the number to divide */
	for (LoopCounter=counter-1;LoopCounter>0;LoopCounter--)
	{
		i = i*10;
	}

	/*b2sm el rkm w bb3t l askii bta3o*/
	for (LoopCounter=counter;LoopCounter>0;LoopCounter--)
	{
		CLCD_voidSendData(arr[(number /i)%10]);
		i=i/10;
	}
}

