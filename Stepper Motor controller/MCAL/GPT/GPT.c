/*
 * GPT.c
 *
 * Created: 06/02/2016 10:44:10 ?
 *  Author: hossam
 */ 
#include "GPT.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#define Prescalar 1024
static PfType Timer250msCallBackPtr;
static PfType TimerCallBackPtr;

void GPT_Timer250msInit(PfType CallBackPtr)
{
	sei();
	Timer250msCallBackPtr = CallBackPtr;
	OCR0 = 243;
	TIMSK |= 1<<OCIE0;
	TCNT0 = 0x00;
	TCCR0 = 0x00;
	TCCR0 |= (1<<WGM01) | (1<<CS00) | (1<<CS02); //1024 prescalar
		
}
void GPT_TimerInit(PfType CallBackPtr,unsigned char counter)
{
	sei();
	TimerCallBackPtr = CallBackPtr;
	OCR2 = counter;
	TIMSK |= 1<<OCIE2;
	TCNT2 = 0x00;
	TCCR2 = 0x00;
	TCCR2 |= (1<<WGM21) | 0x07;
	
}

ISR(TIMER0_COMP_vect)
{
	Timer250msCallBackPtr();
}

ISR(TIMER2_COMP_vect)
{
	sei();
	TimerCallBackPtr();
}

