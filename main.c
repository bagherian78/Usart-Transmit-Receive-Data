#include "stm32f4xx.h"                  // Device header
char  str[50];
uint32_t i=0,a=0;
char reci[1024] = {};
char tmp='m';
//static void NVIC_Config(void);
void USART2_IRQHandler(void)
	{
		while(USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == RESET);
		reci[i] = USART2->DR;
		//USART_SendData(USART2, tmp);
		i++;
			/*if(reci[0]=='1')
			{
			    GPIO_SetBits(GPIOD,GPIO_Pin_12);
					GPIO_ResetBits(GPIOD,GPIO_Pin_13);
					GPIO_ResetBits(GPIOD,GPIO_Pin_14);
					GPIO_ResetBits(GPIOD,GPIO_Pin_15);
			
			}	
       if(tmp=='2')
			{
			    GPIO_ResetBits(GPIOD,GPIO_Pin_12);
					GPIO_SetBits(GPIOD,GPIO_Pin_13);
					GPIO_ResetBits(GPIOD,GPIO_Pin_14);
					GPIO_ResetBits(GPIOD,GPIO_Pin_15);
			
			}				
       if(tmp=='3')
			{
			    GPIO_ResetBits(GPIOD,GPIO_Pin_12);
					GPIO_ResetBits(GPIOD,GPIO_Pin_13);
					GPIO_SetBits(GPIOD,GPIO_Pin_14);
					GPIO_ResetBits(GPIOD,GPIO_Pin_15);
			
			}		
       if(tmp=='4')
			{
			    GPIO_ResetBits(GPIOD,GPIO_Pin_12);
					GPIO_ResetBits(GPIOD,GPIO_Pin_13);
					GPIO_ResetBits(GPIOD,GPIO_Pin_14);
					GPIO_SetBits(GPIOD,GPIO_Pin_15);
			
			}		
		*/
}
int main(){

	
	GPIO_InitTypeDef my_usart_gpio;
	USART_InitTypeDef my_usart2;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);				//enable USART2
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);					//enable GPIOA
	
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2);				//GPIOA2 to AF
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2);				//GPIOA3 to AF

	//---------------------------- GPIO init------------------------------------
	
	my_usart_gpio.GPIO_Mode=GPIO_Mode_AF;
	my_usart_gpio.GPIO_Pin=GPIO_Pin_2|GPIO_Pin_3;
	my_usart_gpio.GPIO_PuPd=GPIO_PuPd_UP;
	my_usart_gpio.GPIO_Speed=GPIO_Speed_100MHz;
	
	GPIO_Init(GPIOA,&my_usart_gpio);
	
	//--------------------------------------------------------------------------
	
	//---------------------------- USART init ----------------------------------
	
	
	my_usart2.USART_BaudRate=115200;
	my_usart2.USART_WordLength=USART_WordLength_8b;
	my_usart2.USART_StopBits= USART_StopBits_1;
	my_usart2.USART_Parity=USART_Parity_No;
	my_usart2.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	my_usart2.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	//i don't know what is Usart_HardeareFlowControl
	
	//UART Flow Control is a method for slow and fast devices to communicate with each other over UART without the risk of losing data.
	//
	
	USART_Init(USART2,&my_usart2);
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	
	//--------------------------------------------------------------------------
	
	//-----------------------------enable usart --------------------------------
	
	USART_Cmd(USART2,ENABLE); 
	RCC->AHB1ENR|=RCC_AHB1ENR_GPIODEN;
	GPIOD->MODER|=1<<24|1<<26|1<<28|1<<30;
	//--------------------------------------------------------------------------
	NVIC_EnableIRQ(USART2_IRQn);
	
	while(1){
		
		//USART_SendData(USART2, 0x23);
		//for(int i=0;i<=168000000;i++){}
		USART2_IRQHandler();
	}
}
