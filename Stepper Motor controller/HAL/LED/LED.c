/*
 * LED.c
 *
 * Created: 3/4/2016 8:58:56 PM
 *  Author: Mahmoud
 */ 
#include "LED.h"
#include "DIO.h"

static unsigned char Toggle [LED_NUM] = {OFF,OFF,OFF,OFF};

typedef struct
{
	unsigned char LEDPort;
	unsigned char LEDMask;
}LED_ConfigType;

static const LED_ConfigType LED_ConfigData[LED_NUM] =
{
	{
			PB,0x01
	}
	,
	{
			PB,0x02
	}
	,
	{
			PB,0x04
	}
	,
	{
			PB,0x08
	}
};

void LED_Init(void)
{
	unsigned char LoopIndex;
	unsigned char LEDPort;
	unsigned char LEDMask;
	for(LoopIndex = 0 ; LoopIndex < LED_NUM ; LoopIndex ++)
	{
		LEDPort = LED_ConfigData[LoopIndex].LEDPort;
		LEDMask = LED_ConfigData[LoopIndex].LEDMask;
		DIO_vidWritePortDirection(LEDPort,LEDMask,0xFF);
		DIO_vidWritePortData(LEDPort,LEDMask,ON);
	}
}

void LED_Set(unsigned char SET,unsigned char id)
{
		unsigned char LEDPort = LED_ConfigData[id].LEDPort;
		unsigned char LEDMask = LED_ConfigData[id].LEDMask;
		DIO_vidWritePortData(LEDPort,LEDMask,SET);
		Toggle[id] = SET;
}

void LED_Toggle(unsigned char id)
{
	Toggle[id] = ~(Toggle[id]);
	LED_Set(Toggle[id],id);
}