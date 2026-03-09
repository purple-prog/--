#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "Key.h"
#include "Motor.h"
#include "TIM3_PWM.h"
#include "Trace.h"
#include "Servo.h"
int main(void){
	uint8_t KeyNum;
	LED_Init();
	Key_Init();
	while(1){
		KeyNum=Key_GetNum();
		if(KeyNum==1)	//按键按下小车启动
			while(1){
				
			}
	}
}
