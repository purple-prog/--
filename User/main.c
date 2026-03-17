#include "stm32f10x.h"
#include "Delay.h"
#include "LED.h"
#include "Key.h"
#include "Motor.h"
#include "TIM3_PWM.h"
#include "Trace.h"
#include "Servo.h"
#include "Control.h"

extern u8 RxData;

int main(void){
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	LED_Init();
	Key_Init();
	Motor_Init();
	TIM3_PWM_Init(7199,1);
	Trace_Init();
	Servo_Init(1999,719);
	Servo_SetAngle(88);
	
	Motor_Speed(0,0);
	LED_Close();
	
	while(1){
		LED_Open();
		Trace_task();
	}
}
