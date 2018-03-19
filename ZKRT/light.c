#include "light.h"
#include "zkrt.h"	//调用需要
#include "can.h"	//解析CAN的字节
#include "appcan.h"

uint32_t stand_count = 0XFFFFFFFF;
//APP数据解析处理
uint8_t zkrt_SetFlag = 0;
uint8_t zkrt_SetFlagCounter = 0;
uint8_t zkrt_LastSetFlag = 1;
extern uint8_t BlinkFlag ;
recv_zkrt_packet_handlest recv_handle={0};
zkrt_packet_t *sub_throw_zkrt_packet_can1_rx = &recv_handle.packet;
void app_msg_handle(void)
{
	if(zkrt_decode(&recv_handle) ==0)
		return;
	
	switch (sub_throw_zkrt_packet_can1_rx->command)
	{
		case ZK_COMMAND_NORMAL:          
		{
			stand_count = TimingDelay;
			if (sub_throw_zkrt_packet_can1_rx->data[0] == 1)
			{
					if(zkrt_SetFlag!=zkrt_LastSetFlag)
					{
						zkrt_SetFlag ++;
					
						if(zkrt_SetFlag>=3) zkrt_SetFlag = 1;
					
						zkrt_LastSetFlag = zkrt_SetFlag;
						if(zkrt_SetFlag==1)
						{
							BlinkFlag = 1;
						}
						else if(zkrt_SetFlag==2)
						{
							BlinkFlag = 2;
						}
					}
			}
			else
			{
//				GPIO_ResetBits(GPIOA, GPIO_Pin_6);
					BlinkFlag = 3;  // Turn Off Light
					zkrt_LastSetFlag = 0x08;
			}
		}	
	}
}
//检查当前灯光值
void check_light_value(void)
{
	uint8_t value = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6);
	lightchb->v1 = value;
}
