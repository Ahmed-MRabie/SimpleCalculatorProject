//******************************************************************************************************************************************
//**************Auther: Ahmed M.Rabie     ****************************************************************************************************
//**************File  : Program of LCD  *****************************************************************************************************
//**************Date  : 14/9/2022          *****************************************************************************************************
//**************Var   : V1                ******************************************************************************************************
//**************Desc  :                   ******************************************************************************************************
//*********************************************************************************************************************************************
//**********************************************************************************************************************************************

#include "STD_TYPES.h"
#include "Bit-math.h"
#include <avr/delay.h>

#include "DIO_interface.h"

#include "LCD_interface.h"
#include "LCD_private.h"
#include "LCD_cfg.h"


void LCD_VidInit(void){
	//LCD_ControlPort(A-0) PinOut(0,1,2)
	DIO_VidSetPortDirectoin(LCD_ControlPort,0xff);
	DIO_VidSetPinValue(LCD_ControlPort,LCD_RS_Pin,HIGH);
	DIO_VidSetPinValue(LCD_ControlPort,LCD_RW_Pin,HIGH);
	DIO_VidSetPinValue(LCD_ControlPort,LCD_E_Pin,HIGH);
	//LCD_DataPort(C-2)  AllPinsOut(0xff)
	DIO_VidSetPortDirectoin(LCD_DataPort,0xff);
	DIO_VidSetPortValue(LCD_DataPort,0);

#if LCD_MOOD_SELECITION == LCD_8_BIT_INITIZATION
	_delay_ms(35);
	/* Function Set Comnd */
	LCD_vidSendComnd(LCD_FunctionSetComnd);
	_delay_us(40);
	/* Display ON/OFF Control Comnd */
	LCD_vidSendComnd(LCD_DisplayONControlComnd);
	_delay_us(40);
	/* Display Clear Comnd */
	LCD_vidSendComnd(LCD_DisplayClearComnd);
	_delay_ms(2);
	/* Entry Mode Set Comnd */
	LCD_vidSendComnd(LCD_EntryModeSetComnd);

#elif LCD_MOOD_SELECITION == LCD_4_BIT_INITIZATION
	_delay_ms(35);
	/* Function Set Comnd */
	LCD_vidSendComnd(LCD_FunctionSetComnd_4_BITS1);
	LCD_vidSendComnd(LCD_FunctionSetComnd_4_BITS2);
	_delay_us(40);
	/* Display ON/OFF Control Comnd */
	LCD_vidSendComnd(LCD_DisplayONControlComnd);
	_delay_us(40);
	/* Display Clear Comnd */
	LCD_vidSendComnd(LCD_DisplayClearComnd);
	_delay_ms(2);
	/* Entry Mode Set Comnd */
	LCD_vidSendComnd(LCD_EntryModeSetComnd);
#endif
}

void LCD_vidSendComnd(u8 Copy_U8Comnd){
#if LCD_MOOD_SELECITION == LCD_8_BIT_INITIZATION
	/* Rs = 0 */
	DIO_VidSetPinValue(LCD_ControlPort , LCD_RS_Pin , 0);
	/* Rw = 0 */
	DIO_VidSetPinValue(LCD_ControlPort , LCD_RW_Pin , 0);
	/* Write Command */
	DIO_VidSetPortValue(LCD_DataPort , Copy_U8Comnd);
	/* E = 1 */
	DIO_VidSetPinValue(LCD_ControlPort , LCD_E_Pin , 1);
	_delay_us(1);
	/* E = 0 */
	DIO_VidSetPinValue(LCD_ControlPort , LCD_E_Pin , 0);
#elif LCD_MOOD_SELECITION == LCD_4_BIT_INITIZATION
	/* Rs = 0 */
	DIO_VidSetPinValue(LCD_ControlPort , LCD_RS_Pin , 0);
	/* Rw = 0 */
	DIO_VidSetPinValue(LCD_ControlPort , LCD_RW_Pin , 0);
	/* Write Command */
	DIO_VidSetPortValue(LCD_DataPort , Copy_U8Comnd);
	/* E = 1 */
	DIO_VidSetPinValue(LCD_ControlPort , LCD_E_Pin , 1);
	_delay_us(1);
	/* E = 0 */
	DIO_VidSetPinValue(LCD_ControlPort , LCD_E_Pin , 0);
	/* Write the rest of Command */
	DIO_VidSetPortValue(LCD_DataPort , Copy_U8Comnd<<4);
	/* E = 1 */
	DIO_VidSetPinValue(LCD_ControlPort , LCD_E_Pin , 1);
	_delay_us(1);
	/* E = 0 */
	DIO_VidSetPinValue(LCD_ControlPort , LCD_E_Pin , 0);
#endif
}

void LCD_vidSendChar(u8 Copy_U8Char){
#if LCD_MOOD_SELECITION == LCD_8_BIT_INITIZATION
	/* Rs = 1 */
	DIO_VidSetPinValue(LCD_ControlPort , LCD_RS_Pin , 1);
	/* Rw = 0 */
	DIO_VidSetPinValue(LCD_ControlPort , LCD_RW_Pin , 0);
	/* Write Char */
	DIO_VidSetPortValue(LCD_DataPort , Copy_U8Char);
	/* E = 1 */
	DIO_VidSetPinValue(LCD_ControlPort , LCD_E_Pin , 1);
	_delay_us(1);
	/* E = 0 */
	DIO_VidSetPinValue(LCD_ControlPort , LCD_E_Pin , 0);
#elif LCD_MOOD_SELECITION == LCD_4_BIT_INITIZATION
	/* Rs = 1 */
	DIO_VidSetPinValue(LCD_ControlPort , LCD_RS_Pin , 1);
	/* Rw = 0 */
	DIO_VidSetPinValue(LCD_ControlPort , LCD_RW_Pin , 0);
	/* Write Char */
	DIO_VidSetPortValue(LCD_DataPort , Copy_U8Char);
	/* E = 1 */
	DIO_VidSetPinValue(LCD_ControlPort , LCD_E_Pin , 1);
	_delay_us(1);
	/* E = 0 */
	DIO_VidSetPinValue(LCD_ControlPort , LCD_E_Pin , 0);
	/* Write The rest ot Char */
	DIO_VidSetPortValue(LCD_DataPort , Copy_U8Char<<4);
	/* E = 1 */
	DIO_VidSetPinValue(LCD_ControlPort , LCD_E_Pin , 1);
	_delay_us(1);
	/* E = 0 */
	DIO_VidSetPinValue(LCD_ControlPort , LCD_E_Pin , 0);
#endif
}

void LCD_vidWriteString(u8 *Copy_U8String ){
	u8 Local_Index = 0;
	while( Copy_U8String[Local_Index] != '\0' ){
		LCD_vidSendChar(Copy_U8String[Local_Index]);
		Local_Index++;
	}
}

void LCD_vidWriteNum(u32 Copy_U32Num){
	u8 Local_U8Arr[16];
	u8 Local_U8Index = 0;

	if (Copy_U32Num == 0)
		LCD_vidSendChar('0');

	while(Copy_U32Num != 0){
		Local_U8Index++;
		Local_U8Arr[Local_U8Index] = Copy_U32Num % 10 ;
		Copy_U32Num = Copy_U32Num / 10 ;
	}
	while(Local_U8Index != 0){
		LCD_vidSendChar(Local_U8Arr[Local_U8Index]+'0');
		Local_U8Index--;
	}
}


void LCD_VidWriteFloatNum(f32 Copy_F32Num)
{
	if(Copy_F32Num < 0.0 && Copy_F32Num > -1.0)
	{
	  LCD_vidSendChar('-');
	 }

	 f32 LOC_U8Data = Copy_F32Num-(s32)Copy_F32Num;  /*Decimal part of the number */
	 LCD_vidWriteNum((s32)Copy_F32Num);    /*Display real part of the number */

	 if(LOC_U8Data == 0.0)
	 {
	  return;    /*End if Decimal part is zero*/
	 }

	 LCD_vidSendChar('.');  /* Display Decimal character*/
	 s32 LOC_U8X=(u32)(LOC_U8Data*1000.0);  /*Accuracy up to 3 Decimal Digits */

	 if(LOC_U8X < 0)
	 {
	  LOC_U8X=~(LOC_U8X)+1;    /*2nd Complement to print positive number after decimal in case number is negative*/
	 }

	 u32 LOC_U8Y=LOC_U8X;
	 u8 LOC_U8Digit=0;

	 while(LOC_U8X != 0)  /*Calculate Number of Digits after Decimal (if zero after '.' direct won't be calculated)*/
	 {
	  LOC_U8Digit++;
	  LOC_U8X/=10;
	 }

	 for(u8 LOC_U8i=3;LOC_U8i>LOC_U8Digit;LOC_U8i--)  /* Display zeros after'.' direct */
	 {
		 LCD_vidWriteNum(0);
	 }

	 LCD_vidWriteNum(LOC_U8Y); /*Display Decimal number*/

}

void LCD_VidGoToXY(u8 Copy_U8LineNum,u8 Copy_U8Location){
	/* Copy_U8Location <= 39 */
	if(Copy_U8Location <= 39){
		switch(Copy_U8LineNum){
			case LCD_u8_Line1 : LCD_vidSendComnd(0x80+Copy_U8Location); break;
			case LCD_u8_Line2 : LCD_vidSendComnd(0xc0+Copy_U8Location); break;
		}
	}

}

void LCD_VidSetCGRAMAddress(u8 Copy_U8Address){

		LCD_vidSendComnd((0b01000000) + (8*Copy_U8Address) );
		_delay_us(40);

}

void LCD_VidDrawChar(u8 Copy_U8Char1 , u8 Copy_U8Char2 , u8 Copy_U8Char3 , u8 Copy_U8Char4 , u8 Copy_U8Char5 , u8 Copy_U8Char6 , u8 Copy_U8Char7 , u8 Copy_U8Char8 ){
	LCD_vidSendChar(Copy_U8Char1);
	LCD_vidSendChar(Copy_U8Char2);
	LCD_vidSendChar(Copy_U8Char3);
	LCD_vidSendChar(Copy_U8Char4);
	LCD_vidSendChar(Copy_U8Char5);
	LCD_vidSendChar(Copy_U8Char6);
	LCD_vidSendChar(Copy_U8Char7);
	LCD_vidSendChar(Copy_U8Char8);

}

void LCD_VidWriteShiftChar(u8 Copy_U8Address , u8 Copy_U8LineNum , u8 Copy_U8Location){

	LCD_VidGoToXY(Copy_U8LineNum,Copy_U8Location);
	LCD_vidSendChar(Copy_U8Address);
}

void LCD_VidDrawCharByArray(u8 *Copy_U8Arr){
	LCD_vidSendChar(Copy_U8Arr[0]);
	LCD_vidSendChar(Copy_U8Arr[1]);
	LCD_vidSendChar(Copy_U8Arr[2]);
	LCD_vidSendChar(Copy_U8Arr[3]);
	LCD_vidSendChar(Copy_U8Arr[4]);
	LCD_vidSendChar(Copy_U8Arr[5]);
	LCD_vidSendChar(Copy_U8Arr[6]);
	LCD_vidSendChar(Copy_U8Arr[7]);
}

void LCD_VidDisplayClear(void){
	LCD_vidSendComnd(LCD_DisplayClearComnd);
	_delay_ms(2);
}




