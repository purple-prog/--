#include "stm32f10x.h"
#include "Delay.h"
#include "LED.h"
#include "Key.h"
#include "Motor.h"
#include "TIM3_PWM.h"
#include "Trace.h"
#include "Servo.h"
#include "HCSR04.h"
#include "Control.h"

extern u8 RxData;

int main(void){
	uint8_t KeyNum;
	uint8_t trace_running=0;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	LED_Init();
	Key_Init();
	Motor_Init();
	TIM3_PWM_Init(7199,1);
	Trace_Init();
	Servo_Init(1999,719);
	Servo_SetAngle(88);
	HCSR04_Init();
	
	Motor_Speed(0,0);
	LED_Close();
	
	while(1){
		KeyNum = Key_GetNum();
		
		if(KeyNum == 1){
			trace_running = !trace_running;
			
			if(trace_running){
				LED_Open();
			}else{
				LED_Close();
				Motor_Speed(0,0);
			}
			
			// 等待松开，防止连按
			while(Key_GetNum() == 1);
		}
		
		if(trace_running){
			Trace_task();
		}else{
			Motor_Speed(0,0);
		}
	}
}
