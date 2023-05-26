//******************************************************************************************************************************************
//**************Auther: Ahmed M.Rabie     ****************************************************************************************************
//**************File  : interface of LCD  *****************************************************************************************************
//**************Date  : 14/9/2022          *****************************************************************************************************
//**************Var   : V1                ******************************************************************************************************
//**************Desc  :                   ******************************************************************************************************
//*********************************************************************************************************************************************
//**********************************************************************************************************************************************

#ifndef LCD_INTERFACE_H
#define LCD_INTERFACE_H


#define LCD_DisplayClearComnd          0b00000001

void LCD_VidInit(void);
void LCD_vidSendComnd(u8 Copy_U8Comnd);
void LCD_vidSendChar(u8 Copy_U8Char);
void LCD_vidWriteString(u8 *Copy_U8String);
void LCD_vidWriteNum(u32 Copy_U32Num);
void LCD_VidGoToXY(u8 Copy_U8LineNum,u8 Copy_U8Location);
void LCD_VidSetCGRAMAddress(u8 Copy_U8Address);
void LCD_VidReadFromCGRAMAddress(u8 Copy_U8Address);
void LCD_VidDrawChar(u8 Copy_U8Char1 , u8 Copy_U8Char2 , u8 Copy_U8Char3 , u8 Copy_U8Char4 , u8 Copy_U8Char5 , u8 Copy_U8Char6 , u8 Copy_U8Char7 , u8 Copy_U8Char8 );
void LCD_VidWriteShiftChar(u8 Copy_U8Address , u8 Copy_U8LineNum , u8 Copy_U8Location);
void LCD_VidDrawCharByArray(u8 *Copy_U8Arr);
void LCD_VidDisplayClear(void);
void LCD_VidWriteFloatNum(f32 Copy_F32Num);


#endif
