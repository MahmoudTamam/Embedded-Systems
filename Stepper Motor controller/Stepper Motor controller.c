/*
 * Embedded_School_Task_1.c
 *
 * Created: 2/29/2016 9:25:56 PM
 *  Author: Mahmoud
 */ 

#include "DIO.h"
#include "BTN.h"
#include "GPT.h"
#include "LED.h"
#include "STEPPER.h"

#define BTNSPEED_Up_ID	0
#define BTNSPEED_Dn_ID	1
#define BTNMode_ID	2
#define BTNDirection_ID	3
#define Right_LED 0
#define LEFT_LED 1
#define MODE_FULL_LED 2
#define MODE_HALF_LED 3

void STEP_Task(void);
void LED_Task(void);
void STEPPER_UP(unsigned char id);
void STEPPER_DN(unsigned char id);
void STEPPER_Mode(unsigned char id);
void STEPPER_Direction(unsigned char id);
void (*State[4]) (unsigned char id) = {STEPPER_UP,STEPPER_DN,STEPPER_Mode,STEPPER_Direction};

static unsigned char DIR = Right;
static unsigned char MOD = FULL_STEP_Mode;
static unsigned char Current_LEDS [2] = {Right_LED, MODE_FULL_LED};
static unsigned char Speed_ID = 4;
static unsigned char Speed[5] = {254,127,63,31,15}; //976,487,243,97,48 //1sec,0.5,0.25,0.1,0.05
//Errors and upgrades: - Transfer from half to full - add Stepper speed function to GPT -GPT New generic driver -DIO New generic driver
int main(void)
{
	unsigned char SPEED_Up,SPEED_Dn,Mode,Direction;
	unsigned char Transition_ready = 5;
	BTN_Init();
	LED_Init();
	STEP_Init();
	STEPPER_Mode(STEP1_Id);
    STEPPER_Direction(STEP1_Id);
	GPT_Timer250msInit(LED_Task);
	GPT_TimerInit(STEP_Task,Speed[Speed_ID]);
    while(1)
    {
		BTN_GetBtnState(BTNSPEED_Up_ID,&SPEED_Up);
		BTN_GetBtnState(BTNSPEED_Dn_ID,&SPEED_Dn);
		BTN_GetBtnState(BTNMode_ID,&Mode);
		BTN_GetBtnState(BTNDirection_ID,&Direction);
		
		if((SPEED_Up == BTN_STATE_ACTIVE) || (SPEED_Dn == BTN_STATE_ACTIVE) || (Mode== BTN_STATE_ACTIVE) || (Direction == BTN_STATE_ACTIVE))
		{
			Transition_ready = ((SPEED_Up == BTN_STATE_ACTIVE) & 0) | ((SPEED_Dn == BTN_STATE_ACTIVE) *1) | ((Mode == BTN_STATE_ACTIVE) * 2) | ((Direction == BTN_STATE_ACTIVE) *3);
		}
		else if(((SPEED_Up || SPEED_Dn || Mode || Direction)  == BTN_STATE_INACTIVE)  && (Transition_ready < 5)) // to check for falling edge of any BTN once it was High
		{
			(*State[Transition_ready]) (STEP1_Id);	
			Transition_ready = 5;
		}
	
	}	
}

void STEPPER_UP(unsigned char id)
{
	if(Speed_ID < 4){Speed_ID++;
	GPT_TimerInit(STEP_Task,Speed[Speed_ID]);}
	
}

void STEPPER_DN(unsigned char id)
{
	if(Speed_ID > 0){Speed_ID--;
	GPT_TimerInit(STEP_Task,Speed[Speed_ID]);}
	
}

void STEPPER_Mode(unsigned char id)
{
	STEP_Mode(MOD,id);
	if (MOD == FULL_STEP_Mode){Current_LEDS[1] = MODE_FULL_LED; 
	LED_Set(OFF,MODE_HALF_LED);}
	else {Current_LEDS[1] = MODE_HALF_LED;
	LED_Set(OFF,MODE_FULL_LED);}
	MOD ^= 1;
}

void STEPPER_Direction(unsigned char id)
{
	STEP_Direction(DIR,id);
	if (DIR == Right){Current_LEDS[0] = Right_LED;
	LED_Set(OFF,LEFT_LED);}
	else {Current_LEDS[0] = LEFT_LED;
	LED_Set(OFF,Right_LED);}
	DIR ^= 1;
}

void LED_Task(void)
{
	LED_Toggle(Current_LEDS[0]);
	LED_Toggle(Current_LEDS[1]);
}

void STEP_Task(void)
{
	STEP_Rotate(STEP1_Id);
}