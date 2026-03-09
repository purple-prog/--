#include "stm32f10x.h"
#include "Delay.h"
#include "TIM3_PWM.h"
void MOTOR_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}	
		
void Motor_Speed(int Left_Speed ,int Right_Speed)
{
	//左侧电机
	if(Left_Speed>0)
	{
		TIM_SetCompare2(TIM3,Left_Speed);
		GPIO_SetBits(GPIOB, GPIO_Pin_7);
		GPIO_ResetBits(GPIOB, GPIO_Pin_8);
	}
	else if(Left_Speed<0)
	{
		TIM_SetCompare2(TIM3,-Left_Speed);
		GPIO_ResetBits(GPIOB, GPIO_Pin_7);
		GPIO_SetBits(GPIOB, GPIO_Pin_8);
	}
	else
	{
		TIM_SetCompare2(TIM3,0);
		GPIO_SetBits(GPIOB, GPIO_Pin_7);
		GPIO_SetBits(GPIOB, GPIO_Pin_8);
	}
	
	
	//右侧电机
	if(Right_Speed>0)
	{
		TIM_SetCompare1(TIM3,Right_Speed);
		GPIO_SetBits(GPIOB, GPIO_Pin_5);
		GPIO_ResetBits(GPIOB, GPIO_Pin_6);
	}
	else if(Right_Speed<0)
	{
		TIM_SetCompare1(TIM3,-Right_Speed);
		GPIO_ResetBits(GPIOB, GPIO_Pin_5);
		GPIO_SetBits(GPIOB, GPIO_Pin_6);
	}
	else
	{
		TIM_SetCompare1(TIM3,0); 
		GPIO_SetBits(GPIOB, GPIO_Pin_5);
		GPIO_SetBits(GPIOB, GPIO_Pin_6);
	}
	
}
