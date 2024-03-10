#include <xc.h>
#include "adc.h"

extern unsigned short flag;

/* For complete 1 sec we require 20000 overflows by the timer0 */
/* So, for 0.25 sec we require (20000/4) i.e, 5000 overflows */
/* So, for 0.5 sec we require (20000/2) i.e, 10000 overflows */
void __interrupt() isr(void)
{
	static unsigned short count;
     
	if (TMR0IF)
	{
        
		TMR0 = TMR0 + 8;
        
        /* If the temp is less than 30 degree C than blink the LED for 250 milli-seconds */
        if(flag == 1)
        {
            if (count++ == 5000)
            {
                count = 0;
                LED1 = !LED1;
            }
        }
        /* If the temp is more than 30 degree C than blink the LED for 500 milli-seconds */
        else
        {
            if (count++ == 10000)
            {
                count = 0;
                LED1 = !LED1;
            }
        }
        /* Make the timer0 interrupt flag 0 to stop the recursive call of the isr() function */
        TMR0IF = 0;
	}
}

void init_timer0(void)
{
	/*
	 * Setting instruction cycle clock (Fosc / 4) as the source of
	 * timer0
	 */

/*Setting 8 bit timer register*/
	T08BIT = 1;

/* Selecting internal clock source */
	T0CS = 0;

/* Enabling timer0*/
	TMR0ON = 1;

/* disabling prescaler*/
	PSA = 1;

	TMR0 = 6;

	/* Clearing timer0 overflow interrupt flag bit */
	TMR0IF = 0;

	/* Enabling timer0 overflow interrupt */
	TMR0IE = 1;
}
