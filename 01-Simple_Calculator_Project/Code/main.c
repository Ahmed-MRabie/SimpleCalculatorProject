//*********************************************************************************************************************************************
//******************************************************************************************************************************************
//************** Auther: Ahmed M.Rabie      ****************************************************************************************************
//************** File  : Calc Prog          *****************************************************************************************************
//************** Date  : 2/2/2023           *****************************************************************************************************
//************** Var   : V1                 ******************************************************************************************************
//************** Desc  : Simple Calculator  ******************************************************************************************************
//*********************************************************************************************************************************************
//**********************************************************************************************************************************************


#include "STD_TYPES.h"
#include "Bit-math.h"
#include "DIO_interface.h"
#include "Keypade_interface.h"
#include "LCD_interface.h"

#define F_CPU 8000000UL
#include <util/delay.h>

void Calc_VidClear(void);
void Calc_VidError(void);
void Calc_VidGetValues(void);
void Calc_VidClearToDoAnatherOpration(void);

u8 Arr1[3];    //Array for first num group
u8 index1 = 0;
f32 Value1;
u8 Flag_EndG1 = 0;

u8 Arr2[3];    //Array for secand num group
u8 index2 = 0;
f32 Value2;


u8 Statment1 = 0;
u8 Statment2 = 0;
u8 Stat_Flag = 0;

f32 Ruselt;
u8 Ruselt_Flag = 0;

int main(void){

	LCD_VidInit();
	KPD_VidInitc();

	u8 num;
	//u32 Arr_Calc[9];

	_delay_ms(3000);
	LCD_vidWriteString("Loading.");
	_delay_ms(250);
	LCD_vidSendChar('.');
	_delay_ms(250);
	LCD_vidSendChar('.');
	_delay_ms(250);
	LCD_vidSendChar('.');
	_delay_ms(250);

	LCD_VidDisplayClear();

	LCD_VidGoToXY(1,4);
	LCD_vidWriteString("Welcame");
	LCD_VidGoToXY(2,2);
	LCD_vidWriteString("Clac Is Ready");
	_delay_ms(1200);

	LCD_VidDisplayClear();

	while(1){
		num = KPD_U8GetPressedKey();

		/* For Numbers */
		if ( !( num == KPD_U8_KEY_NOT_PRESSED ||  num == '/' ||  num == '*' ||  num == '+' ||  num == '-' ||  num == '=' || num == '%')  )
		{
			if(Flag_EndG1 == 0){
				Arr1[index1] = num;
				index1++;
			}
			else if (Flag_EndG1 == 1){
				Arr2[index2] = num;
				index2++;
			}
			LCD_vidWriteNum(num);

			/* Error if group num1,2 greater than 3 digits */
			if( index1 > 3 || index2 > 3  )
				Calc_VidError();

			Calc_VidClearToDoAnatherOpration();

		}

		/* Clear*/
		else if(num !=KPD_U8_KEY_NOT_PRESSED && num == '%' )
		{
			Calc_VidClear();
		}


		/* For Statment */
		else if ( !( num == KPD_U8_KEY_NOT_PRESSED || num == '=') )
		{
			Flag_EndG1 = 1;
			Stat_Flag++;

			/* For first Statment */
			if( Stat_Flag == 1 )
			{
				Statment1 = num;
				LCD_vidSendChar(Statment1);
			}
			/* For Secand Statment */
			else if( Stat_Flag >= 2 )
			{
				Statment2 = num;
				/* if input secand statment delete first statment */
				if( Statment2 != Statment1)
				{
					if( index1 == 1 ){
						LCD_VidGoToXY(1,1);
						LCD_vidSendChar(Statment2);
					}
					else if( index1 == 2 ){
						LCD_VidGoToXY(1,2);
						LCD_vidSendChar(Statment2);
					}
					else if( index1 == 3 ){
						LCD_VidGoToXY(1,3);
						LCD_vidSendChar(Statment2);
					}
					Statment1 = Statment2;
				}
			}
			Calc_VidClearToDoAnatherOpration();


		}

		/* For "=" End Value */
		else if ( num !=KPD_U8_KEY_NOT_PRESSED && num == '=' )
		{
			Ruselt_Flag++;
			LCD_vidSendChar(num);

			Calc_VidGetValues();

			switch(Statment1)
			{
				case '+' :
							Ruselt = Value1 + Value2;
							break;
				case '-' :
							Ruselt = Value1 - Value2;
							break;
				case '*' :
							Ruselt = Value1 * Value2;
							break;
				case '/' :
							Ruselt = Value1 / Value2;
							break;

				default:  Ruselt = -1;
			}

			/* To Detect Negative Numbers */
			if( Statment1 == '-'  && Value2 > Value1)
			{
				LCD_vidSendChar('-');
				Ruselt = Value2 - Value1;
			}



			/* To Show The Ruselt On LCD */
			if( Ruselt == -1 )
				Calc_VidError();
			else
			{
				/* To Detect Float Numbers */
				LCD_VidWriteFloatNum(Ruselt);
			}

			/* Error if divided by 0 */
			if( Statment1 == '/' && Value2 == 0)
				Calc_VidError();
		}


	}
	return 0;
}





void Calc_VidClear(void){
	Flag_EndG1 = 0;
	index1 = 0;
	index2 = 0;
	Value1 = 0;
	Value2 = 0;
	Ruselt = -1;
	Stat_Flag = 0;
	Ruselt_Flag = 0;
	LCD_VidDisplayClear();
}

void Calc_VidError(void){
	Calc_VidClear();
	LCD_vidWriteString("Error");
	_delay_ms(1000);
	Calc_VidClear();
}


void Calc_VidClearToDoAnatherOpration(void){
	/* Clear to do a nather opratian */
	if(Ruselt_Flag >= 1)
	{
		Calc_VidClear();
	}
}
void Calc_VidGetValues(void){
	if( index1 == 3 && index2 == 3 )
	{
		Value1 = Arr1[0]*100 + Arr1[1]*10 + Arr1[2];
		Value2 = Arr2[0]*100 + Arr2[1]*10 + Arr2[2];
	}
	else if (index1 == 3 && index2 == 2)
	{
		Value1 = Arr1[0]*100 + Arr1[1]*10 + Arr1[2];
		Value2 = Arr2[0]*10 + Arr2[1];
	}
	else if (index1 == 3 && index2 == 1)
	{
		Value1 = Arr1[0]*100 + Arr1[1]*10 + Arr1[2];
		Value2 = Arr2[0];
	}
	else if (index1 == 2 && index2 == 3)
	{
		Value1 = Arr1[0]*10 + Arr1[1];
		Value2 = Arr2[0]*100 + Arr2[1]*10 + Arr2[2];
	}
	else if (index1 == 2 && index2 == 2)
	{
		Value1 = Arr1[0]*10 + Arr1[1];
		Value2 = Arr2[0]*10 + Arr2[1];
	}
	else if (index1 == 2 && index2 == 1)
	{
		Value1 = Arr1[0]*10 + Arr1[1];
		Value2 = Arr2[0];
	}
	else if (index1 == 1 && index2 == 1)
	{
		Value1 = Arr1[0];
		Value2 = Arr2[0];
	}
	else if (index1 == 1 && index2 == 2)
	{
		Value1 = Arr1[0];
		Value2 = Arr2[0]*10 + Arr2[1];
	}
	else if (index1 == 1 && index2 == 3)
	{
		Value1 = Arr1[0];
		Value2 = Arr2[0]*100 + Arr2[1]*10 + Arr2[2];
	}
}
