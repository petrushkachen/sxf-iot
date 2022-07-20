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
	  //初始化
    halInit();
    svcInit();
    taskInit();

    while (1) {
			  //系统暂停1000微秒（us），即1毫秒（ms）
        halSystemDelayUs(1000);
			
			  //查看是否有任务需要执行
        svcTaskPoll(1);
    }
}

/* HAL初始化 */
void halInit()
{
	  //系统初始化
    halSystemInit();

	  //STM32F030F4P6串口初始化，波特率为9600
    halUartInit(9600);

	  //OLED屏幕初始化
    halOLED12864Init();

	  //板载DHT20温湿度传感器初始化
    Init_I2C_Sensor_Port();
	
	  //ADC初始化
	  halAdcInit();
}

/* Services层初始化 */
void svcInit()
{
	  //消息通信服务初始化
    svcMsgInit();

	  //任务管理服务初始化
    svcTaskInit();
    
	  //日志打印服务初始化
    svcLogInit();

	  //插件服务初始化
    svcPluginsInit();
}

/* Tasks层初始化 */
void taskInit()
{
    taskDataUploadInit();
}
