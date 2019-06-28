/*
 * spont_pulse.c
 *
 * Created: 20.06.2018 14:33:47
 *  Author: Bendik
 */ 
#include <atmel_start.h>
#include "ISR_timer_counter/ISR_timer_counter.h"
#include <stdbool.h>


static uint32_t spont_pulse_timer_counter = 0;

static _Bool spont_pulse_out = false;
#define SPONT_PULSE_PERIOD 500//period for the spontaneous pulse cycle


/*
Function to check if a second has passed since last pulse out.
*/
static void spont_pulse_time_check(void)
{
	if ((ISR_timer_count() - spont_pulse_timer_counter) > SPONT_PULSE_PERIOD)
	{
		spont_pulse_timer_counter = ISR_timer_count();
		spont_pulse_out = true;
	}
	else
	{
		spont_pulse_out = false;
	}
}



/*
Function to initiate spontaneous pulse mode.
*/
static void spont_pulse_start(void)
{
	spont_pulse_out = true;
	spont_pulse_timer_counter = ISR_timer_count();
}



/*
Function to determine whether a spontaneous pulse
should increase the membrane potential or not.
*/
static _Bool spont_pulse(void)
{
	if ((ISR_timer_count() - spont_pulse_timer_counter) > SPONT_PULSE_PERIOD*2)
	{
		spont_pulse_start();
	}
	else
	{
		spont_pulse_time_check();
	}
	return spont_pulse_out;
}



/*
Callable function from outside the module, should be called every main loop cycle
while spontaneous pulse mode is active and will then return the change in potential.
*/
uint8_t spont_pulse_delta_potential(void)
{
	if (spont_pulse())
	{
		return 26;
	}
	else
	{
		return 0;
	}
}
