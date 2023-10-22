
#include "STD_TYPES.h"
#include "PORT_interface.h"
#include "CLCD_interface.h"
#include "KPD_interface.h"



void main ()
{
	u8 flag=0,flag2=0;
	u8 Local_u8Operation;
	u32 Temp,Local_u8Key1=0,Local_u8Key2=0,Local_u8Result;
	PORT_voidInit();
	CLCD_voidInit();

	while(1)
	{
		do
		{
			Temp=KPD_u8GetPressedKey();
		}while(Temp == 0xff);


		if ((Temp =='+')||(Temp=='-')||(Temp=='*')||(Temp=='/'))
		{
			Local_u8Operation=Temp;
			CLCD_voidSendData(Local_u8Operation);
			while(1)
			{
				do
				{
					Temp=KPD_u8GetPressedKey();
				}while(Temp == 0xff);

				if(Temp =='=')
				{
					CLCD_voidSendData(Temp);
					switch (Local_u8Operation)
					{
					case '+':Local_u8Result=Local_u8Key1+Local_u8Key2;break;
					case '-':Local_u8Result=Local_u8Key1-Local_u8Key2;break;
					case '*':Local_u8Result=Local_u8Key1*Local_u8Key2;break;
					case '/':Local_u8Result=Local_u8Key1/Local_u8Key2;break;
					}

					CLCD_voidWriteNumber(Local_u8Result);
				}
				else
				{
					flag2++;
					if (flag2==1)
					{
						Local_u8Key2=Temp;
						CLCD_voidSendData(Local_u8Key2+'0');
					}
					else if(flag2==2)
					{
						Local_u8Key2=(Local_u8Key2*10)+Temp;
						CLCD_voidSendData(Temp+'0');
					}
					else if(flag2==3)
					{
						Local_u8Key2=(Local_u8Key2*10)+Temp;
						CLCD_voidSendData(Temp+'0');
					}
					else if(flag2==4)
					{
						Local_u8Key2=(Local_u8Key2*10)+Temp;
						CLCD_voidSendData(Temp+'0');
					}
					else if(flag2==5)
					{
						Local_u8Key2=(Local_u8Key2*10)+Temp;
						CLCD_voidSendData(Temp+'0');
					}
					else if(flag2==6)
					{
						Local_u8Key2=(Local_u8Key2*10)+Temp;
						CLCD_voidSendData(Temp+'0');
					}


				}

			}

		}
		else
		{
			flag++;
			if (flag==1)
			{
				Local_u8Key1=Temp;
				CLCD_voidSendData(Local_u8Key1+'0');
			}
			else if(flag==2)
			{
				Local_u8Key1=(Local_u8Key1*10)+Temp;
				CLCD_voidSendData(Temp+'0');
			}
			else if(flag==3)
			{
				Local_u8Key1=((Local_u8Key1*10))+Temp;
				CLCD_voidSendData(Temp+'0');
			}
			else if(flag==4)
			{
				Local_u8Key1=(Local_u8Key1*10)+Temp;
				CLCD_voidSendData(Temp+'0');
			}
			else if(flag==5)
			{
				Local_u8Key1=(Local_u8Key1*10)+Temp;
				CLCD_voidWriteNumber(Temp);
			}
			else if(flag==6)
			{
				Local_u8Key1=(Local_u8Key1*10)+Temp;
				CLCD_voidWriteNumber(Temp);
			}
		}
	}
}
