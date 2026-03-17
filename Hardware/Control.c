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
	if(X1==1&&X2==0&&X3==0&&X4==1) Motor_Speed(2000,2000);
	else if(X1==1&&X2==0&&X3==1&&X4==1) Motor_Speed(2000,1500);
	else if(X1==1&&X2==1&&X3==0&&X4==1) Motor_Speed(2000,1500);
	else if (X1==1&&X2==1&&X3==0&&X4==1) Motor_Speed(1500, 2000);
    else if (X1 == 0 && X2 == 0 && X3 == 1 && X4 == 1) Motor_Speed(2000, 500);
    else if (X1 == 1 && X2 == 1 && X3 == 0 && X4 == 0) Motor_Speed(500, 2000);
    else if (X1 == 1 && X2 == 1 && X3 == 1 && X4 == 1) Motor_Speed(0, 0);
    if (X1 == 0 && X2 == 0) {
        Motor_Speed(0, 0);
        Delay_ms(300);
        do {
            Motor_Speed(-5200, 5200);
            Delay_ms(10);
        } while (X3 == 0);
        Motor_Speed(0, 0);
        Delay_ms(200);
    }
    if (X3 == 0 && X4 == 0) {
        Motor_Speed(0, 0);
        Delay_ms(300);
        do {
            Motor_Speed(5200, -5200);
            Delay_ms(10);
        } while (X2 == 0);
        Motor_Speed(0, 0);
        Delay_ms(200);
    }
}
