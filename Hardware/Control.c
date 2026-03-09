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

void Get_distance(void){
	Servo_SetAngle(90);
	Delay_ms(200);
	Middle=HCSR04_GetValue();
	
	Servo_SetAngle(150);
	Delay_ms(200);
	Left=HCSR04_GetValue();
	
	Servo_SetAngle(30);
	Delay_ms(200);
	Right=HCSR04_GetValue();
	
	Servo_SetAngle(90);
}

void Avoidance(void){
	Middle=HCSR04_GetValue();
	if(Middle>0&&Middle<=35){
		Motor_Speed(0,0);
		Get_distance();
		
		if(Left>=Right){
			Motor_Speed(-3800,-3800);
			Delay_ms(600);
			Motor_Speed(0,0);
			Delay_ms(200);
			Motor_Speed(-4300,4300);
			Delay_ms(800);
		}
		else{
			Motor_Speed(-3800,-3800);
			Delay_ms(600);
			Motor_Speed(0,0);
			Delay_ms(200);
			Motor_Speed(4300,-4300);
			Delay_ms(800);
		}
	}
	else{
		Motor_Speed(3800,3800);
	}
}

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
