#include "task_uart.h"

#include "svc_log.h"
#include "svc_task.h"

static void taskUartRunner(uint8_t, void *);

void taskUartInit()
{
    svcTaskAdd(1000, 1, taskUartRunner, 0);
}

void taskUartRunner(uint8_t id, void *args)
{
    svcLogWrite((uint8_t *)"Task[UART] Running...\n");
}
