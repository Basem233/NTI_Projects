/******************************************************/
/******************************************************/
/**************		Author:Basem Moufreh 	***********/
/**************		Layer:HAL    			***********/
/**************		SWC:CLCD				***********/
/**************		Version:1.00			***********/

/*Preprocessor file guard*/
#ifndef CLCD_INTERFACE_H_
#define CLCD_INTERFACE_H_

void CLCD_voidSendCommand(u8 Copy_u8Command);

void CLCD_voidSendData(u8 Copy_u8Data);

void CLCD_voidInit(void);

void CLCD_voidInit4_bit(void);

void CLCD_voidSendCommand4_bit(u8 Copy_u8Command);

void CLCD_voidSendData4_bit(u8 Copy_u8Data);

/*Ay haga hthsel askii value yb2a lazm tkon char*/
void CLCD_voidSendString(const char* Copy_pcString);

void CLCD_voidGoToXY(u8 Copy_u8XPos,u8 Copy_u8YPos);

void CLCD_voidWriteSpecialCharacter(u8* Copy_u8Arr,u8 Copy_u8BlockNumber,u8 Copy_u8XPos,u8 Copy_u8YPos);

void CLCD_voidWriteNumber(u32 Copy_u32Number);

#endif
