#include "stm32f10x.h"

void GPIO_Config()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//开启 GPIOA的时钟
	//GPIO配置
	GPIO_InitTypeDef GPIO_InitStructure;//定义一个结构体
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//配置为复用推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;//选择9号引脚，因为PA9连着TX
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);//配置GPIOA
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//配置为复用推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//选择10号引脚，因为PA9连着RX
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);//配置GPIOA
}

void USART_Config()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//开启USART1的时钟
	//USART配置
	USART_InitTypeDef USART_InitStructure;//定义一个结构体
	USART_InitStructure.USART_BaudRate = 9600;//波特率
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//不使用流控
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;//串口模式选择发送&接收模式
	USART_InitStructure.USART_Parity = USART_Parity_No;//校验位选择不校验
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//停滞位选择1位停滞位
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长选择8位
	USART_Init(USART1,&USART_InitStructure);
	USART_Cmd(USART1,ENABLE);
}

