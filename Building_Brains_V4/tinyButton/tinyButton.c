/*
 * tinyButton.c
 *
 * Created: 19.06.2018 14:01:18
 * Authors: Bendik Bogfjellmo, Elias Lundheim
 */ 
#include <atmel_start.h>
#include <stdbool.h>
#include "tinyButton/tinyButton.h"
#include "tinyPotential/tinyPotential.h"
#include "tinyTime/tinyTime.h"


static _Bool button_was_pushed_down = false;

static uint32_t tinyButton_start_time = 0;

static _Bool tinyButton_spont_pulse = false;

/*
tinyButton_toggle_spont_pulse changes the state of the boolean value determining
if the neuron is in spontaneous fire-mode or not.
*/
static void tinyButton_toggle_spont_pulse(void)
{
	tinyButton_spont_pulse = !tinyButton_spont_pulse;
}

/*
function returns true if the button has been pushed and then subsequently released.
function changes state of button_spont_pulse, if button has been held down for 2 secs.
*/
static _Bool tinyButton_check(void)
{
	_Bool re_var = false;
	_Bool button_is_pushed_down = !Button_get_level();//the digital port will be read as low if the button is pushed down.
	if (!button_is_pushed_down && !button_was_pushed_down)//button is not pushed down, and was not pushed down
	{
		re_var = false;
	}
	if (button_is_pushed_down && !button_was_pushed_down)
	{
		tinyButton_start_time = tinyTime_now();
		re_var = false;
	}
	if (button_is_pushed_down && button_was_pushed_down)
	{
		if ((tinyTime_now() - tinyButton_start_time) > 2000)
		{
			tinyButton_toggle_spont_pulse();
			tinyButton_start_time = tinyTime_now();
		}
		re_var = false;
	}
	if (!button_is_pushed_down && button_was_pushed_down)
	{
		re_var = true;
	}
	button_was_pushed_down = button_is_pushed_down;
	return re_var;
}





/*
Master-function for button-checking, returns 2 if the neuron should spontaneously fire.
Returns 1 if the system has received a button push shorter than two seconds.
Returns 0 if the button is still pushed in, or it has not yet received a button push.
*/
_Bool tinyButton_get_state(void)
{
	return tinyButton_check();
}

_Bool tinyButton_is_spont_pulse_on(void)
{
	return tinyButton_spont_pulse;
}

