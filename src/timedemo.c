/*====================================================================
* Project:  Board Support Package (BSP) examples
* Function: example demonstrating timer interrupt functionality
*
* Copyright HighTec EDV-Systeme GmbH 1982-2019
*====================================================================*/

#include "bspconfig.h"
#include "timer.h"
#include "led.h"

#ifdef __TRICORE__
#if !defined(__TC161__) && !defined(__TC162__)
#include <machine/intrinsics.h>
#endif /* !__TC161__ && !__TC162__ */

#if defined(__TC161__)
#include "system_tc2x.h"
#endif /* __TC161__  */

#if defined(__TC162__)
#include "system_tc3x.h"
#endif /* __TC162__  */
#endif /* __TRICORE__ */

#define SYSTIME_CLOCK	10	/* timer event rate [Hz] */

/* TimeDemo variables and definitions */
#define DEMO_BUFSIZE	10

static unsigned int aBuffer[DEMO_BUFSIZE];

static unsigned int Hours = 0;
static unsigned int Minutes = 0;
static unsigned int Seconds = 0;

static volatile int eventFlag = 0;
static volatile unsigned int runcount = 0;

/* timer callback handler */
static void my_timer_handler(void)
{
	eventFlag = 1;
	++runcount;
}

int main(void)
{
	unsigned int i;

#ifdef __TRICORE__
#if defined(__TC161__) || defined(__TC162__)
	SYSTEM_Init();
#endif /* __TC161__ || __TC162__ */
#endif /* __TRICORE__ */

	/* initialise timer at SYSTIME_CLOCK rate */
	TimerInit(SYSTIME_CLOCK);
	/* add own handler for timer interrupts */
	TimerSetHandler(my_timer_handler);

	/* initialise LEDs */
	InitLED();

#ifdef __TRICORE__
#if !defined(__TC161__) && !defined(__TC162__)
	/* enable global interrupts */
	_enable();
#endif /* !__TC161__ && !__TC162__ */
#endif /* __TRICORE__ */

	while (1)
	{
		/* check flag set by timer ISR in every 100 ms */
		if (eventFlag == 1)
		{
			/* clear the flag */
			eventFlag = 0;

			i = runcount;
			aBuffer[i % DEMO_BUFSIZE] = i;

			/* toggle LED0 in every 100 ms */
			LEDTOGGLE(0);

			/*
				instruction barrier (as sequence point):
				prevent compiler from optimising out access to our variables
			 */
			__asm volatile ("" : : : "memory");

			/* handle software timer */
			if (0 == (i % SYSTIME_CLOCK))
			{
				/* toggle LED1 every second */
				LEDTOGGLE(1);
				if (60 == ++Seconds)
				{
					Seconds = 0;
					/* toggle LED2 every minute */
					LEDTOGGLE(2);

					if (60 == ++Minutes)
					{
						Minutes = 0;
						/* toggle LED3 every hour */
						LEDTOGGLE(3);

						if (24 == ++Hours)
						{
							Hours = 0;
						}
					}
				}
			}
		}
	}

	return 0;
}
