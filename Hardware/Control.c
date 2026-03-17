#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Trace.h"
#include "Motor.h"
#include "HCSR04.h"
#include "Servo.h"

#define X1 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)
#define X2 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)
#define X3 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10)
#define X4 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)


uint16_t Middle=0;
uint16_t Left=0;
uint16_t Right=0;

void Trace_task(void){
	if(X1==0&&X2==1&&X3==0&&X4==1) Motor_Speed(4000,4000);
	else if(X1==0&&X2==1&&X3==1&&X4==1) Motor_Speed(0,4300);
	else if(X1==1&&X2==1&&X3==0&&X4==1) Motor_Speed(4300,0);
	else if(X1==1&&X2==0&&X3==1&&X4==1) Motor_Speed(-4500,4500);
	else if(X1==1&&X2==1&&X3==1&&X4==0) Motor_Speed(4500,-4500);
	
	if(X3==0&&X4==0)
	{
		Motor_Speed(0,0);
		Delay_ms(500);
		do
		{
			Motor_Speed(5200,-5200);  //原地右转
		}while(X1==0);
	}
	
	//拐左直角
	if(X2==0&&X1==0)
	{
		Motor_Speed(0,0);  //停车一下
		Delay_ms(500);
		do
		{
			Motor_Speed(-5200,5200);  //原地左转
		}while(X3==0);
	}
}
