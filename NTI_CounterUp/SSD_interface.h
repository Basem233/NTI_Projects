/******************************************************/
/******************************************************/
/**************		Author:Basem Moufreh 	***********/
/**************		Layer:HAL    			***********/
/**************		SWC:SSD					***********/
/**************		Version:1.00			***********/

#ifndef SSD_INTERFACE_H_
#define SSD_INTERFACE_H_

#define COM_Anode 0
#define COM_Cathode 1

/*Hna bdl mykon 3ndi too many arguments ll function w ta5od mni storage kbera
  Kol ely b3mlo hwa struct b7ot feh kol l arguments bta3ty w bb3t fe el function
  Adress bta3 object mn l struct da w da bywfr fe l storage */
typedef struct
{
	u8 COM_TYPE;
	u8 PORT;
	u8 EnablePort;
	u8 EnablePin;
}SSD_t;

/*Function to display the desired number and to enable the 7 segemant*/
u8 SSD_u8SetNumber(u8 Copy_u8Number,SSD_t* SSD);




#endif
