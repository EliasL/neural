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
#include "tinyPulse/tinyPulse.h"
#include "settings.h"
#include "common_settings.h"


static _Bool button_was_pushed_down = false;

_Bool button_press = false;
_Bool ignore_next_button_press = false;

// We use this variable to see how long the button has been held down
static uint32_t tinyButton_start_time = 0;

/*
If the button has been let go, we change button_press to true. This only lasts one cycle, before it is set to false again.
If the button is held down for longer than PULSEMODE_BUTTON_PRESS_TIME, we toggle the pulse mode state.
*/
void tinyButton_update(void)
{
	button_press = false;
	_Bool button_is_pushed_down = !BUTTON_PIN_get_level(); // The digital port will be read as low if the button is pushed down.

	if (button_is_pushed_down && !button_was_pushed_down)
	{
		tinyButton_start_time = tinyTime_now();
	}
	if (button_is_pushed_down && button_was_pushed_down)
	{
		if ((tinyTime_now() - tinyButton_start_time) > PULSEMODE_BUTTON_PRESS_TIME)
		{
			tinyPulse_toggle_pulse_mode();
			tinyButton_start_time = tinyTime_now();
			// We don't want switching to pulse mode to count as a button press, so we ignore the next button press
			ignore_next_button_press = true;
		}
	}
	if (!button_is_pushed_down && button_was_pushed_down)
	{
		if(!ignore_next_button_press){
			button_press = true;
		}
		else{
			ignore_next_button_press = false;
		}
		
	}
	button_was_pushed_down = button_is_pushed_down;
}

double tinyButton_update_potential(double potential){
	if(button_press){
		potential += BUTTON_PRESS_REACTION;
	}
	return potential;
}

