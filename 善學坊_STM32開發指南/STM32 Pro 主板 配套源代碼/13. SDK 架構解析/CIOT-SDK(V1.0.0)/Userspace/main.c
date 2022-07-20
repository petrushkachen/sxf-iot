#include "main.h"

#include "task_test.h"

#include "svc_log.h"
#include "svc_task.h"

#include "hal_led.h"
#include "hal_uart.h"
#include "hal_system.h"

static void halInit(void);
static void svcInit(void);
static void taskInit(void);

int main(void)
{
    halInit();

    svcInit();

    taskInit();

    while (1) {
        halSystemDelayUs(1000);
        svcTaskPoll(1);
    }
}

/* HAL */
void halInit()
{
    halSystemInit();

    halUartInit(115200);

    halLedInit();
}

/* Services */
void svcInit()
{
    svcTaskInit();

    svcLogInit();
}

/* Tasks */
void taskInit()
{
    taskTestInit();
}
