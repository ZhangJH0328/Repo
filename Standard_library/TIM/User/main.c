#include "stm32f10x.h"
#include "timer.h"
int main()
{
	//GPIO配置
	GPIO_InitTypeDef GPIO_InitStructure;//定义一个结构体
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);//开启使能时钟	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//配置为通用推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;//选择13号引脚
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//速度好像没什么要求，这里选择一个最大的
	GPIO_Init(GPIOC,&GPIO_InitStructure);//配置GPIO
	Timer_Init();//时钟初始化
	Timer_Parameter_Config();//配置时钟参数
	NVIC_Parameter_Config();//配置NVIC参数
	TIM_Cmd(TIM2,ENABLE);//启动定时器
	while(1)
	{
		
	}
	return 0;
}
