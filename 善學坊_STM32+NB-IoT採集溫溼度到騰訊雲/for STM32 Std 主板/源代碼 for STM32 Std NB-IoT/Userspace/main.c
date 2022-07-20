#include "main.h"

#include "task_data_upload.h"

#include "svc_plugins.h"
#include "svc_log.h"
#include "svc_task.h"
#include "svc_msg.h"

#include "hal_dht20.h"
#include "hal_oled12864.h"
#include "hal_uart.h"
#include "hal_system.h"
#include "hal_adc.h"

static void halInit(void);
static void svcInit(void);
static void taskInit(void);

int main(void)
{
	  //��ʼ��
    halInit();
    svcInit();
    taskInit();

    while (1) {
			  //ϵͳ��ͣ1000΢�루us������1���루ms��
        halSystemDelayUs(1000);
			
			  //�鿴�Ƿ���������Ҫִ��
        svcTaskPoll(1);
    }
}

/* HAL��ʼ�� */
void halInit()
{
	  //ϵͳ��ʼ��
    halSystemInit();

	  //STM32F030F4P6���ڳ�ʼ����������Ϊ9600
    halUartInit(9600);

	  //OLED��Ļ��ʼ��
    halOLED12864Init();

	  //����DHT20��ʪ�ȴ�������ʼ��
    Init_I2C_Sensor_Port();
	
	  //ADC��ʼ��
	  halAdcInit();
}

/* Services���ʼ�� */
void svcInit()
{
	  //��Ϣͨ�ŷ����ʼ��
    svcMsgInit();

	  //�����������ʼ��
    svcTaskInit();
    
	  //��־��ӡ�����ʼ��
    svcLogInit();

	  //��������ʼ��
    svcPluginsInit();
}

/* Tasks���ʼ�� */
void taskInit()
{
    taskDataUploadInit();
}
