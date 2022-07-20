#include "task_test.h"

#include "svc_task.h"
#include "svc_log.h"

static void taskTestRunner(uint8_t, void *);

void taskTestInit()
{
    svcTaskAdd(2000, 1, taskTestRunner, 0);
}

void taskTestRunner(uint8_t id, void *args)
{
    svcLogWrite((uint8_t *)"Task[TEST] Running...\n");
}
