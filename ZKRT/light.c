#include "light.h"
#include "zkrt.h"	//������Ҫ
#include "can.h"	//����CAN���ֽ�
#include "appcan.h"

uint32_t stand_count = 0XFFFFFFFF;
//APP���ݽ�������
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
				GPIO_SetBits(GPIOA, GPIO_Pin_6);
//				printf("can 12v on\n");
			}
			else
			{
				GPIO_ResetBits(GPIOA, GPIO_Pin_6);
//				printf("can 12v off\n");
			}			
			break;
		}
		default:
		{
			break;
		}
	}
}
//��鵱ǰ�ƹ�ֵ
void check_light_value(void)
{
	uint8_t value = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6);
	lightchb->v1 = value;
}
