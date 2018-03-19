#include "sys.h"
#include "led.h"
#include "zkrt.h"
#include "adc.h"
#include "uart.h"
#include "can.h"
#include "light.h"
#include "key.h"
#include "appcan.h"
/*
头文件中
can.h包含了zkrt.h
light.h包含了can.h、zkrt.h
key.h包含了light.h
*/

void bsp_init(void)
{
	SystemInit ();		/*系统初始化*/
	RCC_Configuration();
	SysTick_Init();
	LED_Init();
	ADC1_Init();
	USART1_Config();
	CAN_Mode_Init(CAN_Mode_Normal);
	KEY_Init();
}
extern uint8_t BlinkFlag ;
void LightBlink(void)
{
		if(BlinkFlag==1){
			GPIO_SetBits(GPIOA, GPIO_Pin_6);
				printf("key 12v on\n");
		}
	
	 else if(BlinkFlag == 2)
	 {
			if (_Lightms_count - TimingDelay >= 50)								//10ms一个时间片
			{
				_Lightms_count = TimingDelay;
				 if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6) == 0)
					{
						GPIO_SetBits(GPIOA, GPIO_Pin_6);
			//			printf("key 12v on\n");
					}
					else
					{
						GPIO_ResetBits(GPIOA, GPIO_Pin_6);
			//			printf("key 12v off\n");
					}
			}
		}
	 else if(BlinkFlag == 3)
	 {
			GPIO_ResetBits(GPIOA, GPIO_Pin_6);
//			printf("key 12v off\n");
	 }
}

/*
2018-2-28  增加爆闪功能，控制LED灯
*/
int main()
{
  bsp_init();
	appcan_init();
	printf("system init\n");
	while (1)
	{		
		app_msg_handle();
		KEY_Rock();
		LightBlink();
		if (_10ms_count - TimingDelay >= 10)								//10ms一个时间片
		{
			_10ms_count = TimingDelay;
			ADC_StartOfConversion(ADC1);											//每10ms一次，读取板载电压
			if ((_10ms_flag%10) == 0)													//每100ms一次，整合电压、检测电压、发送心跳
			{				
				if (MAVLINK_TX_INIT_VAL - TimingDelay > 2000)		//初始化的2S内不执行检查，以后每次读取到后都检查
				{
					bat_read();
//					if (stand_count - TimingDelay > 500)
					if (stand_count - TimingDelay > 2000)  //modify by yanly
					{
//						bat_check();
					}
				}
			}
			if ((_10ms_flag%100) == 0)												//每1000ms一次，发送一次心跳
			{
				if (MAVLINK_TX_INIT_VAL - TimingDelay > 3000)		//初始化的3S内不执行发送心跳，以后每次都发送心跳
				{
					check_light_value();
					appcan_hbpacket_send();
				}
			}
			_10ms_flag++;
		}
		if (led_rx_count - TimingDelay > 50)
		{
			GPIO_SetBits(GPIOB, GPIO_Pin_7);
		}
		if (led_tx_count - TimingDelay > 50)
		{
			GPIO_SetBits(GPIOB, GPIO_Pin_6);
		}
	}
}
