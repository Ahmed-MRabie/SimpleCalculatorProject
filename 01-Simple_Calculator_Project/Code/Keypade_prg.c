//******************************************************************************************************************************************
//**************Auther: Ahmed M.Rabie        ****************************************************************************************************
//**************File  : program of Keypade   *****************************************************************************************************
//**************Date  : 24/2/2023            *****************************************************************************************************
//**************Var   : V2                   ******************************************************************************************************
//**************Desc  :                      ******************************************************************************************************
//*********************************************************************************************************************************************
//**********************************************************************************************************************************************

#include "STD_TYPES.h"
#include "Bit-math.h"
#define F_CPU 8000000UL
#include <util/delay.h>

#include "DIO_interface.h"

#include "Keypade_interface.h"
#include "Keypad_private.h"
#include "Keypade_cfg.h"

/*
 be care to write in main :
    while (1){

	 num = KPD_U8GetPressedKey();
	 if ( !( num == 50 ||  num == '/' ||  num == '*' ||  num == '+' ||  num == '-' ||  num == '=' || num == '%')  )
	 {
		 LCD_vidWriteNum(num ) ;
	 }//end if
	 else if (num != 50){
	     LCD_vidSendChar(num);
	 }

   }//end while loop
 */


/* Array of Pins*/
const u8 KPD_Au8RowsPins[4] = { KPD_R1_PIN , KPD_R2_PIN , KPD_R3_PIN , KPD_R4_PIN };
const u8 KPD_Au8ColsPins[4] = { KPD_C1_PIN , KPD_C2_PIN , KPD_C3_PIN , KPD_C4_PIN };


/* Array of Keys*/
#if KPD_Tyep == KPD_NormalNum
const u8 KPD_Au8Keys[4][4] = {
		{ 1 ,  2  ,  3  ,  4 },
		{ 5 ,  6  ,  7  ,  8 },
		{ 9 ,  10 ,  11 , 12 },
		{ 13 , 14 ,  15 , 16 }
};
#elif KPD_Tyep == KPD_SmallCalc
const u8 KPD_Au8Keys[4][4] = {
		{ 1 , 2 , 3 ,'/'},
		{ 4 , 5 , 6 ,'*'},
		{ 7 , 8 , 9 ,'-'},
		{'%', 0 ,'=','+'}
};
#endif



void KPD_VidInitc(void){
	DIO_VidSetPortDirectoin(KPD_PORT , KPD_DIR);
	DIO_VidSetPortValue(KPD_PORT , KPD_PORT_Value);
}



u8 KPD_U8GetPressedKey(void){
	u8 LOC_U8Key = KPD_U8_KEY_NOT_PRESSED;
	u8 LOC_U8Pressed;
	u8 LOC_U8RowCounter;
	u8 LOC_U8ColumnCounter;

	/* Activate Each Row */
	for( LOC_U8RowCounter = 0 ; LOC_U8RowCounter < KPD_ROW_NUM ; LOC_U8RowCounter++)
	{
		DIO_VidSetPinValue(KPD_PORT , KPD_Au8RowsPins[LOC_U8RowCounter], LOW);

		/* Check which input pins has zero */
		for( LOC_U8ColumnCounter = 0 ; LOC_U8ColumnCounter < KPD_COL_NUM ; LOC_U8ColumnCounter++)
		{
			LOC_U8Pressed = DIO_U8GetPinValue( KPD_PORT , KPD_Au8ColsPins[LOC_U8ColumnCounter] );
			if( LOW == LOC_U8Pressed ) /* Switch is Pressed */
			{
				/* Debouncing*/
				_delay_ms(5);
				LOC_U8Pressed = DIO_U8GetPinValue( KPD_PORT , KPD_Au8ColsPins[LOC_U8ColumnCounter] );
				/* Check if Pin is still LOW */
				while ( LOW == LOC_U8Pressed )
				{
					LOC_U8Pressed = DIO_U8GetPinValue( KPD_PORT , KPD_Au8ColsPins[LOC_U8ColumnCounter] );
				}
				/* Show the key*/
				LOC_U8Key = KPD_Au8Keys[LOC_U8RowCounter][LOC_U8ColumnCounter];
			}
		}
		DIO_VidSetPinValue(KPD_PORT , KPD_Au8RowsPins[LOC_U8RowCounter], HIGH);
	}
	return LOC_U8Key;
}
