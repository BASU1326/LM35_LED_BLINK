/*
 * File:   main.c
 * Author: basus
 *
 * Created on 9 March, 2024, 6:36 PM
 */


#include <xc.h>
#include "adc.h"
unsigned short flag;

void init_config(void)
{
    /* External peripheral enable bit make it 1 */
    PEIE = 1;
    
    /* Config PORTB as digital */
	ADCON1 = 0x0F;
    
    /* Make the RB0 led pin as output pin */
	TRISB0 = 0;
    
    /* Configure the adc */
    init_adc();
    
    /* Configure the timer0 */
    init_timer0();
    
    /* Enable the Global interrupt enable bit */
    GIE = 1;
}

void main(void) 
{
    unsigned short adc_reg_val, temp;

    init_config();

    while (1)
    {
        /* In pic18f4580 lm35 is connected to the channel-6 */
        /* Read the digital value from the adc */
        adc_reg_val = read_adc(CHANNEL6);
        
        /* If the value from lm35 is 10mV then its 1 degree C */
        /* To convert digital value to degree celsious */
        temp = (adc_reg_val * ((float)5/1023) * 100);
        
        /* If the temp is less than 30 degree C */
        if(temp < 30)
        {
            flag = 1;
        }
        /* If the temp is more than 30 degree C */
        else if(temp > 30)
        {
            flag = 0;
        }
    }
    return;
}
