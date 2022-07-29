#include "stm32f10x.h"
/*
时钟初始化
*/
void Timer_Init()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);//开启APB1外设时钟TIM2
	TIM_InternalClockConfig(TIM2);//使用内部时钟
}
/*
这里配置时钟参数，达到定时500ms的效果；即每500ms，LED亮灭交替进行
计算：c8t6的主频是72MHz，则Psc取3599，ARR取9999，保证定时时间为500ms
*/
void Timer_Parameter_Config()
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;//声明结构变量
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;//时钟分频，这里选择1分频，即c8t6的主频72MHz
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;//计数模式，这里选择向上计数
	TIM_TimeBaseInitStruct.TIM_Period = 9999;//自动重装器（主计数器）
	TIM_TimeBaseInitStruct.TIM_Prescaler = 3599;//预分频器
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter =0; //重复计数器
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);//使能TIM2中断
}
/*
配置NVIC参数
*/
void NVIC_Parameter_Config()
{
	NVIC_InitTypeDef NVIC_InitStruct;//声明结构变量
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//NVIC优先级分组
	NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;//中断通道，选择TIM2在NVIC的通道
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;//抢占优先级
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;//响应优先级
	NVIC_Init(&NVIC_InitStruct);//初始化
	
}
/*
定时器产生中断时，执行此函数
说明：本来想直接翻转引脚电平自动实现亮灭（像HAL库的HAL_GPIO_TogglePin（）一样），但发现标准库没有这种函数
			没太想好怎么自己造一个，只好用了一个笨办法，使用if else语句外加判别用的变量
更新：经学长指点，改为读取电平并按位取反，再写入电平
*/
void TIM2_IRQHandler(void)
{
	uint16_t Readvalue;
	Readvalue = GPIO_ReadOutputData(GPIOC);
	Readvalue = ~Readvalue;
	GPIO_Write(GPIOC,Readvalue);
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);//清除标志位
}
