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
ͷ�ļ���
can.h������zkrt.h
light.h������can.h��zkrt.h
key.h������light.h
*/

void bsp_init(void) {
	SystemInit ();		/*ϵͳ��ʼ��*/
	RCC_Configuration();
	SysTick_Init();
	LED_Init();
	ADC1_Init();
	USART1_Config();
	CAN_Mode_Init(CAN_Mode_Normal);
	KEY_Init();
}
int main() {
	bsp_init();
	appcan_init();
	printf("system init\n");
	while (1) {
		appcan_prcs();
		KEY_Rock();
		if (_10ms_count - TimingDelay >= 10) {							//10msһ��ʱ��Ƭ
			_10ms_count = TimingDelay;
			ADC_StartOfConversion(ADC1);											//ÿ10msһ�Σ���ȡ���ص�ѹ
			if ((_10ms_flag % 10) == 0) {												//ÿ100msһ�Σ����ϵ�ѹ������ѹ����������
				if (MAVLINK_TX_INIT_VAL - TimingDelay > 2000) {	//��ʼ����2S�ڲ�ִ�м�飬�Ժ�ÿ�ζ�ȡ���󶼼��
					bat_read();
//					if (stand_count - TimingDelay > 500)
					if (stand_count - TimingDelay > 2000) { //modify by yanly
//						bat_check();
					}
				}
			}
			if ((_10ms_flag % 100) == 0) {											//ÿ1000msһ�Σ�����һ������
				if (MAVLINK_TX_INIT_VAL - TimingDelay > 3000) {	//��ʼ����3S�ڲ�ִ�з����������Ժ�ÿ�ζ���������
					check_light_value();
					appcan_hbpacket_send();
				}
			}
			_10ms_flag++;
		}
		if (led_rx_count - TimingDelay > 50) {
			GPIO_SetBits(GPIOB, GPIO_Pin_7);
		}
		if (led_tx_count - TimingDelay > 50) {
			GPIO_SetBits(GPIOB, GPIO_Pin_6);
		}
	}
}
