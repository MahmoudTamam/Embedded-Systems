/*
 * STEPPER.h
 *
 * Created: 2/29/2016 10:32:36 PM
 *  Author: Mahmoud
 */ 


#ifndef STEPPER_H_
#define STEPPER_H_	

#define STEP_NUM 1

#define HALF_STEP_Mode 0
#define FULL_STEP_Mode 1
#define Left 0
#define Right 1
#define STEP1_Id 0

extern void STEP_Init(void);
extern void STEP_Mode(unsigned char STEPMODE, unsigned char STEP_Id);
extern void STEP_Direction(unsigned char STEPDIR, unsigned char STEP_Id);
extern void STEP_Rotate(unsigned char STEP_Id);

#endif /* STEPPER_H_ */