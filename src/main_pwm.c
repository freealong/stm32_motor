/*************************************************************************************
* Test-program for Olimex “STM32-H103”, header board for “STM32F103RBT6”.
* After program start green LED (LED_E) will blink.
*
* Program has to be compiled with optimizer setting "-O0".
* Otherwise delay via while-loop will not work correctly.
*************************************************************************************/

#include"stm32f10x.h"
#include"stm32f10x_rcc.h"
#include"stm32f10x_tim.h"
#include"stm32f10x_gpio.h"

int main(int argc, char *argv[])
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 , ENABLE);
						 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	TIM_TimeBaseInitTypeDef TIM1_TimeBaseStructure;
	TIM_OCInitTypeDef TIM1_OCInitStructure;
	/* 设置TIM1_TimeBaseStructure */
	TIM1_TimeBaseStructure.TIM_Period = 1000;			//周期
	TIM1_TimeBaseStructure.TIM_Prescaler = 72 ;        		//分频系数
	TIM1_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM1_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM1_TimeBaseStructure.TIM_RepetitionCounter=0;
	/* 初始化TIM1基本设置 */
	TIM_TimeBaseInit(TIM1, &TIM1_TimeBaseStructure);
	/* 设置TIM1_OCInitStructure */
	TIM1_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM1_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM1_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;//反向通道无效
	TIM1_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM1_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;     //互补端的极性
	TIM1_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM1_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
	TIM1_OCInitStructure.TIM_Pulse = 1000;					//脉冲数
	/* 初始化TIM1输出 */
	TIM_OC1Init(TIM1,&TIM1_OCInitStructure);	//通道1
	TIM1_OCInitStructure.TIM_Pulse = 800;
	TIM_OC2Init(TIM1,&TIM1_OCInitStructure);	//通道2
	/* 使能TIM1 */
	TIM_Cmd(TIM1, ENABLE);
	TIM_CtrlPWMOutputs(TIM1, ENABLE);

	u32 delay=10000;
	while(1)
	{
		if(delay==0)
			delay=10000;
		delay--;
	}

}

