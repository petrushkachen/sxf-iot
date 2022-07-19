#include "svc_log.h"

#include "hal_uart.h"

#include <string.h>

void svcLogInit()
{
    
}

void svcLogWrite(const unsigned char *msg)
{
    halUartWrite(msg, strlen((char *)msg));
}
