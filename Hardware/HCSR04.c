#include "stm32f10x.h"                  // Device header
#include "HCSR04.h"
#include "Time.h"
#include "Delay.h"

uint16_t Time;

void TIM4_Init(void){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	TIM_InternalClockConfig(TIM4);
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;          // 不分频
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;      // 向上计数模式
    TIM_TimeBaseInitStructure.TIM_Period = 7199;                         // 自动重装载寄存器 (ARR)，对应更新事件间隔 0.0001s = 100us
    TIM_TimeBaseInitStructure.TIM_Prescaler = 0;                         // 预分频器 (PSC)，不分频
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;                 // 仅在高级定时器中有效，普通定时器置 0
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStructure);

    TIM_ClearFlag(TIM4, TIM_FLAG_Update);
    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);

    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;                      // 定时器 4 中断通道
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                      // 使能中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;            // 抢占优先级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;                   // 响应优先级
    NVIC_Init(&NVIC_InitStructure);

    TIM_Cmd(TIM4, ENABLE);
}

void TIM4_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM4, TIM_IT_Update) == SET)
    {
        if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5) == 1)
        {
            Time++;
        }
        TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
    }
}
void HCSR04_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_ResetBits(GPIOA, GPIO_Pin_4);
}

void HCSR04_Start(void)
{
    GPIO_SetBits(GPIOA, GPIO_Pin_4);
    Delay_us(45);
    GPIO_ResetBits(GPIOA, GPIO_Pin_4);

    Time = 0;
    TIM4_Init();
}

uint16_t HCSR04_GetValue(void)
{
    HCSR04_Start(); 
		Delay_ms(100); 
    TIM_Cmd(TIM4, DISABLE);
    return ((Time * 0.0001f) * 34000) / 2;
}
