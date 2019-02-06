/*
 * tiny_potential.c
 *
 * Created: 18.06.2018 18:50:16
 *  Author: Bendik
 */ 


//As to preserve modularity, we try to keep any external use of functions to a minimum.


#include <atmel_start.h>
#include "tiny_potential.h"
#include <math.h>
#include "tiny_dendrites/tiny_ADC_dendrites.h"
#include "tiny_DAC_axon/tiny_DAC_axon.h"
#include "Potential_to_RGB/Potential_to_RGB.h"
#include "ISR_timer_counter/ISR_timer_counter.h"
#include "pullup_pushbutton/pullup_pushbutton.h"
#include "spont_pulse/spont_pulse.h"
#include <stdbool.h>

static double tiny_potential = 0;
static _Bool spontaneous_pulse_mode = false;

#define tiny_potential_time_const 100 //Tau should be equal to 100ms as per the specifications.
#define post_fire_potential 0 //post-fire-potential is described as -80mV in the specs.

/*
Internal function to enable incrementing or decrementing
potential from the signal of a button push or dendrite.
*/
static void tiny_potential_manual_update(int8_t delta_potential)
{
	tiny_potential += delta_potential;
}

/*
internal function within the module to manually set the potential.
function is used to manually set the potential post-pulse to post_fire_potential.
*/
static void tiny_potential_manual_set(int8_t new_potential)
{
	tiny_potential = new_potential;
}


//function to update potential as it should decay over time and converge towards 0.
static void tiny_potential_time_update(double time_since_last_update)//time since last update will have to be given in ms, and therefore needs precision.
{
	tiny_potential *= (exp(-(time_since_last_update/tiny_potential_time_const)));
}



/*
Function to update potential and set spontaneous pulse mode
by using the master update function in the button module.
*/
static void tiny_potential_pullup_pushbutton_update()
{
	if (pullup_pushbutton_get_state())
	{
		tiny_potential_manual_update(26);
	}
	spontaneous_pulse_mode = pullup_pushbutton_is_spont_pulse_on();
}

/*
The function which will run in the main loop.
This function will run on interrupts by the RTC module.
*/
void tiny_potential_master_update(double time_since_last_update)
{
	tiny_potential_manual_update(tiny_ADC_dendrite_delta_potential());
	//Update potential with values from dendrites, button and spontaneous pulse.
	tiny_potential_pullup_pushbutton_update();
	if (spontaneous_pulse_mode)
	{
		tiny_potential_manual_update(spont_pulse_delta_potential());
	}
	if (tiny_potential > 50)
	{
		tiny_DAC_axon_master_update(true, true);//DAC is used to write pulse signal.
		tiny_potential_manual_set(post_fire_potential);//post-pulse potential is set.
		potential_to_RGB_update_LEDs(tiny_potential);//true is used to denote that the LEDs should write out a pulse signal.
	}
	if ((tiny_potential > 25) && (tiny_potential < 50))
	{
		tiny_DAC_axon_master_update(true, false);
		tiny_potential_manual_set(post_fire_potential);
		potential_to_RGB_update_LEDs(tiny_potential);
	}
	else
	{
		potential_to_RGB_update_LEDs(tiny_potential);//write potential to LEDs in case the potential is not at the threshold potential.
		tiny_DAC_axon_master_update(false, false);//DAC needs to be updated so that the timed pulses can be written later on.
		if(tiny_potential < -25)
		{
			if(tiny_DAC_axon_neg_pulse_queue_check())
			{
				tiny_potential_manual_set(0);
			}
		}
	}
	tiny_potential_time_update(time_since_last_update);//set the potential in accordance with the time since last update.
}
