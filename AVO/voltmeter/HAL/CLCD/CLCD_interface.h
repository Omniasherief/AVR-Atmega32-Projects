#ifndef CLCD_INTERFACE_H
#define CLCD_INTERFACE_H

void CLCD_voidSendCmd(uint8 Copy_u8Cmd);
void CLCD_voidSendData(uint8 Copy_u8Data);
void CLCD_VoidInit(void);
uint8 CLCD_u8SendString(const char* Copy_pchString);
void CLCD_VoidGoToXY(uint8 Copy_u8Xpos,uint8 Copy_u8Ypos);
void CLCD_voidSendNumber(sint32 Copy_s32Number);
 uint8 CLCD_u8SpecialCharacter(uint8 Copy_u8LocationNum, uint8 * Copy_puPattern,uint8 Copy_u8Xpos,uint8 Copy_u8Ypos);
 void CLCD_voidClear();
 void CLCD_voidMyNameSin();
 void CLCD_voidHamoksha();
#endif
