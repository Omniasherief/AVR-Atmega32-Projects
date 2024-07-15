#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ErrType.h"
#include<util/delay.h>
#include "DIO_interface.h"

#include"CLCD_interface.h"
#include"CLCD_prv.h"
#include"CLCD_cfg.h"
#if CLCD_u8BIT_MODE ==FOUR_BIT
static void voidSetHalfDataPort(uint8 Copy_u8Data)
{
DIO_u8SetPinValue(CLCD_u8DATA_PORT,CLCD_u8D4_PIN,GET_BIT(Copy_u8Data,0));
DIO_u8SetPinValue(CLCD_u8DATA_PORT,CLCD_u8D5_PIN,GET_BIT(Copy_u8Data,1));
DIO_u8SetPinValue(CLCD_u8DATA_PORT,CLCD_u8D6_PIN,GET_BIT(Copy_u8Data,2));
DIO_u8SetPinValue(CLCD_u8DATA_PORT,CLCD_u8D7_PIN,GET_BIT(Copy_u8Data,3));
}
#endif

static void voidSendEnablePulse(void)
{

	// send enable pulse
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT,CLCD_u8E_PIN,DIO_u8PIN_HIGH );
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT,CLCD_u8E_PIN,DIO_u8PIN_LOW);
}


void CLCD_voidSendCmd(uint8 Copy_u8Cmd)
{ //set RS pin to low for command
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT,CLCD_u8RS_PIN,DIO_u8PIN_LOW);
	/*Set RW pin to low for writing*/
#if CLCD_u8RW_CONN_STS==DIO_CONNECTED
		DIO_u8SetPinValue(CLCD_u8CTRL_PORT, CLCD_u8RW_PIN, DIO_u8PIN_LOW);
#endif
#if CLCD_u8BIT_MODE ==EIGHT_BIT
	//send the command
	DIO_u8SetPortValue(CLCD_u8DATA_PORT,Copy_u8Cmd);
	voidSendEnablePulse();
#elif 	CLCD_u8BIT_MODE==FOUR_BIT
	/*Send the 4 Most significant bits of the command first*/
	voidSetHalfDataPort(Copy_u8Cmd >> 4);
	voidSendEnablePulse();
	voidSetHalfDataPort(Copy_u8Cmd);
	voidSendEnablePulse();
#else
#error wrong CLCD_u8BIT_MODE configuration option
#endif

}
void CLCD_voidSendData(uint8 Copy_u8Data)
{

	 //set RS pin to HIGH for DATA
		DIO_u8SetPinValue(CLCD_u8CTRL_PORT,CLCD_u8RS_PIN,DIO_u8PIN_HIGH);
		//set RW to low for writing
#if CLCD_u8RW_CONN_STS==DIO_CONNECTED
		DIO_u8SetPinValue(CLCD_u8CTRL_PORT,CLCD_u8RW_PIN,DIO_u8PIN_LOW);
#endif
#if CLCD_u8BIT_MODE == EIGHT_BIT
	/*Send the Data*/
	DIO_u8SetPortValue(CLCD_u8DATA_PORT,Copy_u8Data);//
	voidSendEnablePulse();

#elif CLCD_u8BIT_MODE == FOUR_BIT
	/*Send the 4 Most significant bits of the data first*/
	voidSetHalfDataPort(Copy_u8Data >> 4);
	voidSendEnablePulse();
	voidSetHalfDataPort(Copy_u8Data);
	voidSendEnablePulse();

#else
#error wrong CLCD_u8BIT_MODE configuration option
#endif

}
void CLCD_VoidInit(void)
{//if rs ==0 it is command ..low
	//wait for more than 39 micro s after power on
	_delay_ms(40);
#if  CLCD_u8BIT_MODE == EIGHT_BIT
	//function set command :2lines , font size 5*11
	CLCD_voidSendCmd(0b00111100);

#elif  CLCD_u8BIT_MODE == FOUR_BIT
		voidSetHalfDataPort(0b0010);
		voidSendEnablePulse();
		voidSetHalfDataPort(0b0010);
		voidSendEnablePulse();
		voidSetHalfDataPort(0b1000);
		voidSendEnablePulse();

	#endif

	//display on off control: display on, cursor off , blink cursor off
	CLCD_voidSendCmd(0b00001100);
	//clear display
	CLCD_voidSendCmd(1);

}

uint8 CLCD_u8SendString(const char* Copy_pchString)
{

uint8 Local_u8ErrorState=OK;
 if(Copy_pchString!=NULL)
 {
  uint8 Local_u8Iteratot=0u;
   while(Copy_pchString[Local_u8Iteratot]!='\0')
      {
	    CLCD_voidSendData(Copy_pchString[Local_u8Iteratot]);
	    Local_u8Iteratot++;
      }

 }
 else
  {
 	Local_u8ErrorState=  NULL_PTR_ERR;
  }
 return Local_u8ErrorState;
}
void CLCD_voidSendNumber(sint32 Copy_s32Number )
{ char Local_chNumber[10];
  uint8 Local_u8RightDigit,Local_u8Counter1=0u;
  sint8 Local_s8Counter2=0;
	if(Copy_s32Number==0)
	{
		CLCD_voidSendData('0');
		return;
	}
	else if (Copy_s32Number<0)
	{ //make -ve -> +ve and print - "sign" on clcd
		Copy_s32Number *=-1;
		CLCD_voidSendData('-');

	}
	while(Copy_s32Number!=0)
	{
		Local_u8RightDigit=(uint8)((uint32)Copy_s32Number %10);//get right most digit
		Copy_s32Number/=10; //remove right digit
		Local_chNumber[Local_u8Counter1]=Local_u8RightDigit+'0'; //CONVERT TO ASCII
		Local_u8Counter1++;


	}
	/////////////
	for(Local_s8Counter2 =(sint8)Local_u8Counter1-1; Local_s8Counter2>=0;Local_s8Counter2--)

	{
		CLCD_voidSendData(Local_chNumber[(uint8)Local_s8Counter2]);
	}
}
void CLCD_VoidGoToXY(uint8 Copy_u8Xpos,uint8 Copy_u8Ypos)
{
	uint8 Local_u8Adress ;
	if(Copy_u8Ypos==0u)
	{
		Local_u8Adress=Copy_u8Xpos;
	}
	else if(Copy_u8Ypos==1u)
	{
		Local_u8Adress=0x40+Copy_u8Xpos;

	}
	// WE CAN USE IT INSTEAD OF IF.IFELSE :Local_u8Adress=ox40*Copy_u8Ypos+Copy_u8Xpos;
   // SET BIT 7 FOR SET DDRAM ADDRESS COMMAND
	SET_BIT(Local_u8Adress,7);
	//EXECUTE SET DDRam address command
   CLCD_voidSendCmd(Local_u8Adress);

}
uint8 CLCD_u8SpecialCharacter(uint8 Copy_u8LocationNum, uint8 * Copy_puPattern,uint8 Copy_u8Xpos,uint8 Copy_u8Ypos)
{
uint8 Local_u8ErrorState=OK;
uint8 Local_u8Counter=0;
if(Copy_puPattern!=NULL)
{
	uint8 Local_u8CGRAMAddress= Copy_u8LocationNum*8;
	//set bit 6 for CGRAM ADDRESS  command
	SET_BIT(Local_u8CGRAMAddress,6u);
	// set CGRAM address
	CLCD_voidSendCmd(Local_u8CGRAMAddress);
	//write the input pattern inside cGRAM
	for(Local_u8Counter=0;Local_u8Counter<8;Local_u8Counter++)
	{
		CLCD_voidSendData(Copy_puPattern[Local_u8Counter]);
	}
	//GO BACK TO DDRAM
	CLCD_VoidGoToXY(Copy_u8Xpos,Copy_u8Ypos);
	//WRITE SPECIAL PATTERN INSIDE CGRAM " DISPLAY
	CLCD_voidSendData(Copy_u8LocationNum);
}
else
{
	Local_u8ErrorState=NULL_PTR_ERR;
}
return Local_u8ErrorState;
}

void CLCD_voidClear()
{
CLCD_voidSendCmd(1);
}

void CLCD_voidHamoksha()
{
	uint8 Local_u8HamokshaPattern0[8]= {0b0000000,
            0b00000000,
            0b00000000,
            0b00000000,
            0b00000001
           ,0b00011111,
            0b00011111,0};

	uint8 Local_u8HamokshaPattern1[8]= //NORMAL
                                        {0b00001110,
                                         0b00001110,
                                         0b00010101,
                                         0b00010101,
                                         0b00000100
                                        ,0b00001010,
                                         0b00001010,0};

	uint8 Local_u8HamokshaPattern2[8]= //Dance
	                                        {0b00001110,
	                                         0b00011111,
	                                         0b00010101,
	                                         0b00000100,
	                                         0b00000100
	                                        ,0b00010001,
	                                         0b00010001,0};
	uint8 Local_u8HamokshaPattern3[8]= //Dance
	                                        {0b00001110,
	                                         0b00011111,
	                                         0b00010101,
	                                         0b00000100,
	                                         0b00000100
	                                        ,0b00001010,
	                                         0b00001010,0};
	uint8 Local_u8HamokshaPattern4[8]= //rRUN
                                        {0b00001110,
                                         0b00001110,
                                         0b00000100,
                                         0b00000100,
                                         0b00000100
                                        ,0b00001010,
                                         0b00001010,0};
	uint8 Local_u8HamokshaPattern5[8]= //rRUN
                                        {0b00001110,
                                         0b00001110,
                                         0b00000100,
                                         0b00000100,
                                         0b00000100
                                        ,0b00001001,
                                         0b00001001,0};
	uint8 Local_u8HamokshaPattern42[8]= //football
	                                        {0b00001110,
	                                         0b00001110,
	                                         0b00000100,
	                                         0b00000101,
	                                         0b00000101
	                                        ,0b00001010,
	                                         0b00001000,0};
	//GUN

	uint8 Local_u8HamokshaPattern6[8]={0b00011111,
            0b00011111,
            0b00011111,
            0b00011111,
            0b00011111
           ,0b00011111,
            0b00011111,0};
	uint8 Local_u8HamokshaPattern7[8]={0b00011111,
	            0b00011111,
	            0b00011111,
	            0b00011111,
	            0b00000000
	           ,0b00000000,
	            0b00000000,0};



	//SHOOT
uint8 Local_u8HamokshaPattern8[8]={0b00001110,
                                   0b00001110,
                                   0b00001110,
                                   0b00000000,
                                   0b00000000
                                  ,0b00000000,
                                   0b00000000,0};





CLCD_voidClear();
	CLCD_VoidGoToXY(0,0);
	CLCD_u8SendString("HI I AM HAMOKSHA");

	CLCD_u8SpecialCharacter(0,Local_u8HamokshaPattern1,7,1);
	_delay_ms(700);
	CLCD_voidClear();
	CLCD_VoidGoToXY(0,0);
	CLCD_u8SendString("I CAN RUN");
	_delay_ms(600);
uint8 i=0;
while(i<16)
	{   CLCD_voidClear();
		CLCD_u8SpecialCharacter(0,Local_u8HamokshaPattern4,i++,1);
		_delay_ms(40);
		CLCD_u8SpecialCharacter(0,Local_u8HamokshaPattern5,i,1);
		_delay_ms(40);
		        i++;

	}
CLCD_voidClear();
CLCD_VoidGoToXY(0,0);
	CLCD_u8SendString("I CAN DANCE");
	_delay_ms(600);
	 i=0;
	while(i<10)
	{
		CLCD_u8SpecialCharacter(0,Local_u8HamokshaPattern1,7,1);
		_delay_ms(40);
		CLCD_u8SpecialCharacter(1,Local_u8HamokshaPattern2,7,1);
		_delay_ms(40);
		CLCD_u8SpecialCharacter(2,Local_u8HamokshaPattern3,7,1);
		_delay_ms(40);
        i++;

	}
	CLCD_voidClear();
	CLCD_VoidGoToXY(0,0);
	CLCD_u8SendString(" I play Football");
	_delay_ms(600);
	i=0;
	{
		while(i<16)
			{   CLCD_voidClear();
				CLCD_u8SpecialCharacter(0,Local_u8HamokshaPattern4,i++,1);
				_delay_ms(40);
				CLCD_u8SpecialCharacter(0,Local_u8HamokshaPattern42,i,1);
				_delay_ms(40);
				        i++;

			}

	}

	CLCD_voidClear();
	CLCD_VoidGoToXY(0,0);
	CLCD_u8SendString(" DON'T KILL ME");
	_delay_ms(600);
	CLCD_voidClear();
		CLCD_u8SpecialCharacter(0,Local_u8HamokshaPattern1,13,1);


			CLCD_u8SpecialCharacter(1,Local_u8HamokshaPattern6,0,1);
			CLCD_u8SpecialCharacter(2,Local_u8HamokshaPattern7,1,1);
			CLCD_u8SpecialCharacter(3,Local_u8HamokshaPattern7,2,1);

			CLCD_u8SpecialCharacter(4,Local_u8HamokshaPattern8,4,1);
			_delay_ms(30);
			CLCD_u8SpecialCharacter(5,Local_u8HamokshaPattern8,7,1);
			_delay_ms(30);
			CLCD_u8SpecialCharacter(6,Local_u8HamokshaPattern8,9,1);
            _delay_ms(30);

			CLCD_u8SpecialCharacter(0,Local_u8HamokshaPattern0,13,1);
			_delay_ms(300);
		}


void CLCD_voidMyNameSin()
{
	uint8 Local_u81letter[8]={0b00000111,
                        0b00000100,
                        0b00011111,
                        0b00000100,
                        0b00000100,
                        0b00000100,
                        0b00000100,0};
	uint8 Local_u82letter[8]={0b00000000,
                              0b00000000,
                              0b00000111,
                              0b00000101,
                              0b00000111,
                              0b00011111,
                              0b00000000,0};
	uint8 Local_u83letter[8]={0b00000000,
                              0b00000000,
                              0b00000000,
                              0b00000101,
                              0b00000001,
                              0b00011111,
                              0b00000000,0};
	uint8 Local_u84letter[8]={0b00000000,
                              0b00000000,
                              0b00000001,
                              0b00000001,
                              0b00011111,
                              0b00000000,
                              0b00001010,0};
    uint8 Local_u85letter[8]={0b00001010,
                              0b00000000,
                              0b00001111,
                              0b00001001,
                              0b00001111,
                              0b00000001,
                              0b00000000,0
                              };
   // sint8 j;
    for(uint8 i=15,j=0; (i>0 && j<2) ;i--,j++)
    {
	CLCD_u8SpecialCharacter(0,Local_u81letter,i--,j);
	CLCD_u8SpecialCharacter(1,Local_u82letter,i--,j);
	CLCD_u8SpecialCharacter(2,Local_u83letter,i--,j);
	CLCD_u8SpecialCharacter(3,Local_u84letter,i--,j);
	CLCD_u8SpecialCharacter(4,Local_u85letter,i,j);
	_delay_ms(80);
	CLCD_voidClear();
	if(j==1)
	{
		j=-1;
	}
    }



}
void void_HamokshaF()
{
	uint8 Local_u8HamokshaPattern4[8]= //rRUN
	                                        {0b00001110,
	                                         0b00001110,
	                                         0b00000100,
	                                         0b00000100,
	                                         0b00000100
	                                        ,0b00001010,
	                                         0b00001010,0};
		uint8 Local_u8HamokshaPattern5[8]= //rRUN
	                                        {0b00001110,
	                                         0b00001110,
	                                         0b00000100,
	                                         0b00000100,
	                                         0b00000100
	                                        ,0b00001001,
	                                         0b00001001,0};

		uint8 i=0;
		while(i<16)
			{   CLCD_voidClear();
		   	//CLCD_VoidGoToXY(5,0);
		   	//CLCD_u8SendString("WELCOME");
			    CLCD_u8SpecialCharacter(0,Local_u8HamokshaPattern4,i++,1);
				_delay_ms(40);
				CLCD_u8SpecialCharacter(0,Local_u8HamokshaPattern5,i,1);
				_delay_ms(40);
				        i++;
            }
}
void void_HamokshaB()
{

	uint8 Local_u8HamokshaPattern4[8]= //rRUN
	                                        {0b00001110,
	                                         0b00001110,
	                                         0b00000100,
	                                         0b00000100,
	                                         0b00000100
	                                        ,0b00001010,
	                                         0b00001010,0};
		uint8 Local_u8HamokshaPattern5[8]= //rRUN
	                                        {0b00001110,
	                                         0b00001110,
	                                         0b00000100,
	                                         0b00000100,
	                                         0b00000100
	                                        ,0b00001001,
	                                         0b00001001,0};

	uint8 i=16;
	  while(i<=16)
		   	{   CLCD_voidClear();
		   //	CLCD_VoidGoToXY(5,0);
		   	//CLCD_u8SendString("DONE");
		   		CLCD_u8SpecialCharacter(0,Local_u8HamokshaPattern4,i--,1);
		   		_delay_ms(40);
		   		CLCD_u8SpecialCharacter(0,Local_u8HamokshaPattern5,i,1);
		   		_delay_ms(40);
		   		        i--;

		   	}
}
