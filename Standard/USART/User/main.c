#include "stm32f10x.h"
#include "config.h"
uint16_t Data;
int main()
{
	GPIO_Config();
	USART_Config();
	while(1)
	{
		if(USART_GetFlagStatus(USART1,USART_FLAG_RXNE) == SET)//收到数据
		{
			Data = USART_ReceiveData(USART1);
			USART_SendData(USART1,Data);
			while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);//等待数据完全进入移位寄存器
		}
	}
	return 0;
}
