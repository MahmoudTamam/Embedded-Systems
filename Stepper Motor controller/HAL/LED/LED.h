/*
 * LED.h
 *
 * Created: 3/4/2016 8:59:15 PM
 *  Author: Mahmoud
 */ 


#ifndef LED_H_
#define LED_H_
#define  OFF 0x00
#define  ON 0xFF
#define LED_NUM 4
#define LED1_Id 0
#define LED2_Id 1
#define LED3_Id 2
#define LED4_Id 3

extern void LED_Init(void);
extern void LED_Set(unsigned char SET,unsigned char id);
extern void LED_Toggle(unsigned char id); 

#endif /* LED_H_ */