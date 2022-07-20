#include "svc_button.h"

#include "hal_button.h"

static int svcButtonClickTimesCounter = 0;

static void svcButtonOnClick(void);

void svcButtonInit()
{
    halButtonSetCallback(svcButtonOnClick);
}

int svcButtonClickTimes()
{
    return svcButtonClickTimesCounter;
}

void svcButtonClickTimesClear()
{
    svcButtonClickTimesCounter = 0;
}

/* IRQ */
void svcButtonOnClick()
{
    svcButtonClickTimesCounter++;
}