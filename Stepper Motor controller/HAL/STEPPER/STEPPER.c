/*
 * STEPPER.c
 *
 * Created: 2/29/2016 10:32:23 PM
 *  Author: Mahmoud
 */ 

#include "STEPPER.h"
#include "DIO.h"
#include "GPT.h"

static unsigned char STEP_DIR[STEP_NUM];
static unsigned char STEP_MOD[STEP_NUM];
static unsigned char STEPPER_Mask;
static unsigned char STEP_Count;
void FULL_STEP(unsigned char NUM, unsigned char Id);
void HALF_STEP(unsigned char NUM, unsigned char Id);

typedef struct
{
	unsigned char STEPPort;
	unsigned char STEPMask[4];
}STEP_ConfigType;

static const STEP_ConfigType STEP_ConfigData[STEP_NUM] =
{
	{
			PA,{0x01,0x02,0x04,0x08}
	}
};

void STEP_Init(void)
{
	unsigned char LoopIndex;
	unsigned char STEP_Port;
	unsigned char STEP_Mask;
	unsigned char STEPNUM = 0;
	unsigned char Str_ar = 0;
	STEP_Count = 0;
	for(LoopIndex = 0 ; LoopIndex < (STEP_NUM * 4) ; LoopIndex ++)
	{
		if (((LoopIndex % 4) == 0) && (LoopIndex != 0)){++STEPNUM;}
		if (Str_ar == 4){Str_ar =0;}
		STEP_Port = STEP_ConfigData[STEPNUM].STEPPort;
		STEP_Mask = STEP_ConfigData[STEPNUM].STEPMask[Str_ar];
		Str_ar++;
		DIO_vidWritePortDirection(STEP_Port,STEP_Mask,0xFF);
	}	
} 

// set Stepper mode half or full
void STEP_Mode(unsigned char STEPMODE, unsigned char STEP_Id)
{
	if (STEPMODE == HALF_STEP_Mode)
	{
		STEP_MOD[STEP_Id] = HALF_STEP_Mode;
	}
	else if (STEPMODE == FULL_STEP_Mode)
	{
		STEP_MOD[STEP_Id] = FULL_STEP_Mode;
	}				
}

void STEP_Direction(unsigned char STEPDIR, unsigned char STEP_Id)
{
	if (STEPDIR == Left)
	{
		STEP_DIR[STEP_Id] = Left;
	}
	else if (STEPDIR == Right )
	{
		STEP_DIR[STEP_Id] = Right;
	}
}

void STEP_Rotate(unsigned char STEP_Id)
{
	unsigned char STEP_Port = STEP_ConfigData[STEP_Id].STEPPort;
	if (STEP_MOD[STEP_Id] == FULL_STEP_Mode)		
	{
		FULL_STEP(STEP_Count,STEP_Id);
		DIO_vidWritePortData(STEP_Port,0xFF,STEPPER_Mask);
		
		if (STEP_DIR[STEP_Id] == Right){++STEP_Count;}
		if(STEP_Count >= 4){STEP_Count =0;}
		if((STEP_DIR[STEP_Id] == Left) && (STEP_Count != 0)){--STEP_Count;}
		else if((STEP_DIR[STEP_Id] == Left) && (STEP_Count == 0)){STEP_Count =3;}
	}	
	else if ( STEP_MOD[STEP_Id] == HALF_STEP_Mode) 
	{
		HALF_STEP(STEP_Count,STEP_Id);
		DIO_vidWritePortData(STEP_Port,0xFF,STEPPER_Mask);
		
		if (STEP_DIR[STEP_Id] == Right){++STEP_Count;}
		if((STEP_Count == 8)){STEP_Count =0;}
		if((STEP_DIR[STEP_Id] == Left) && (STEP_Count !=0)){--STEP_Count;}
		else if((STEP_DIR[STEP_Id] == Left) && (STEP_Count == 0) ){STEP_Count =7;}
		
	}
}

void FULL_STEP(unsigned char NUM, unsigned char Id)
{
	switch(NUM){
		case 0:
			STEPPER_Mask = STEP_ConfigData[Id].STEPMask[1] | STEP_ConfigData[Id].STEPMask[3];
			break;
		case 1:
			STEPPER_Mask = STEP_ConfigData[Id].STEPMask[3] | STEP_ConfigData[Id].STEPMask[0];
			break;
		case 2:
			STEPPER_Mask = STEP_ConfigData[Id].STEPMask[0] | STEP_ConfigData[Id].STEPMask[2];
			break;
		case 3:
			STEPPER_Mask = STEP_ConfigData[Id].STEPMask[1] | STEP_ConfigData[Id].STEPMask[2];
			break;	
	}	
}

void HALF_STEP(unsigned char NUM, unsigned char Id)
{
	switch(NUM)
	{
		case 0:
			STEPPER_Mask = STEP_ConfigData[Id].STEPMask[3] | STEP_ConfigData[Id].STEPMask[1];
			break;
		case 1:
			STEPPER_Mask = STEP_ConfigData[Id].STEPMask[3];
			break;
		case 2:
			STEPPER_Mask = STEP_ConfigData[Id].STEPMask[3] | STEP_ConfigData[Id].STEPMask[0];
			break;
		case 3:
			STEPPER_Mask = STEP_ConfigData[Id].STEPMask[0];
			break;
		case 4:
			STEPPER_Mask = STEP_ConfigData[Id].STEPMask[2] | STEP_ConfigData[Id].STEPMask[0];
			break;
		case 5:
			STEPPER_Mask = STEP_ConfigData[Id].STEPMask[2];
			break;
		case 6:
			STEPPER_Mask =STEP_ConfigData[Id].STEPMask[1] | STEP_ConfigData[Id].STEPMask[2];
			break;
		case 7:
			STEPPER_Mask = STEP_ConfigData[Id].STEPMask[1];
			
			break;
	}	
}