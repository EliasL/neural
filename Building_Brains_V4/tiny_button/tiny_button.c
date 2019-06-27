/*
 * tiny_button.c
 *
 * Created: 19.06.2018 14:01:18
 *  Authors: Bendik Bogfjellmo, Elias Lundheim 
 */ 
#include <atmel_start.h>
#include "tiny_button/tiny_button.h"
#include <stdbool.h>
#include "tiny_potential/tiny_potential.h"
#include "ISR_timer_counter/ISR_timer_counter.h"


static _Bool button_was_pushed_down = false;

static uint32_t tiny_button_start_time = 0;

static _Bool tiny_button_spont_pulse = false;

/*
tiny_button_toggle_spont_pulse changes the state of the boolean value determining
if the neuron is in spontaneous fire-mode or not.
*/
static void tiny_button_toggle_spont_pulse(void)
{
	tiny_button_spont_pulse = !tiny_button_spont_pulse;
}

/*
function returns true if the button has been pushed and then subsequently released.
function changes state of button_spont_pulse, if button has been held down for 2 secs.
*/
static _Bool tiny_button_check(void)
{
	_Bool re_var = false;
	_Bool button_is_pushed_down = !Button_get_level();//the digital port will be read as low if the button is pushed down.
	if (!button_is_pushed_down && !button_was_pushed_down)//button is not pushed down, and was not pushed down
	{
		re_var = false;
	}
	if (button_is_pushed_down && !button_was_pushed_down)
	{
		tiny_button_start_time = ISR_timer_count();
		re_var = false;
	}
	if (button_is_pushed_down && button_was_pushed_down)
	{
		if ((ISR_timer_count() - tiny_button_start_time) > 2000)
		{
			tiny_button_toggle_spont_pulse();
			tiny_button_start_time = ISR_timer_count();
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
_Bool tiny_button_get_state(void)
{
	return tiny_button_check();
}

_Bool tiny_button_is_spont_pulse_on(void)
{
	return tiny_button_spont_pulse;
}

