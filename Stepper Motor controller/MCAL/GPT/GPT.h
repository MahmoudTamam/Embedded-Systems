/*
 * IncFile1.h
 *
 * Created: 06/02/2016 10:44:17 ?
 *  Author: hossam
 */ 


#ifndef INCFILE1_H_
#define INCFILE1_H_

typedef void (*PfType)(void);

extern void GPT_Timer250msInit(PfType CallBackPtr);
extern void GPT_TimerInit(PfType CallBackPtr,unsigned char counter);




#endif /* INCFILE1_H_ */