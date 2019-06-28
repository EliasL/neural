/*
 * tiny_potential.c
 *
 * Created: 18.06.2018 18:50:16
 *  Authors: Bendik Bogfjellmo, Elias Lundheim
 */ 


//As to preserve modularity, we try to keep any external use of functions to a minimum.


#include <atmel_start.h>
#include "tiny_potential.h"
#include <math.h>
#include "tiny_dendrites/tiny_ADC_dendrites.h"
#include "tiny_DAC_axon/tiny_DAC_axon.h"
#include "Potential_to_RGB/Potential_to_RGB.h"
#include "ISR_timer_counter/ISR_timer_counter.h"
#include "tiny_button/tiny_button.h"
#include "spont_pulse/spont_pulse.h"
#include <stdbool.h>

static double tiny_potential = 0;
double tiny_potential_change = 0;
static _Bool spontaneous_pulse_mode = false;

#define TINY_POTENTIAL_TIME_CONST 100 //Tau should be equal to 100ms as per the specifications. This constant determines how fast the potential will decay over time.
#define POST_FIRE_POTENTIAL 0 //post-fire-potential is described as -80mV in the specs. (reference?)

/*
Internal function to enable incrementing or decrementing
potential from the signal of a button push or dendrite.
*/
static void tiny_potential_increase_by(int8_t delta_potential)
{
	tiny_potential += delta_potential;
}

/*
internal function within the module to manually set the potential.
function is used to manually set the potential post-pulse to post_fire_potential.
*/
static void tiny_potential_set(int8_t new_potential)
{
	tiny_potential = new_potential;
}


//function to update potential as it should decay over time and converge towards 0.
static void tiny_potential_time_update(double time_since_last_update)//time since last update will have to be given in ms, and therefore needs precision.
{
	tiny_potential *= (exp(-(time_since_last_update/TINY_POTENTIAL_TIME_CONST)));
}



/*
Function to update potential and set spontaneous pulse mode
by using the master update function in the button module.
*/
static void tiny_potential_button_update()
{
	if (tiny_button_get_state()) // If the button is pressed, we want the neuron to fire
	{
		tiny_potential_increase_by(26);
	}
	spontaneous_pulse_mode = tiny_button_is_spont_pulse_on();
}

/*
The function which will run in the main loop.
This function will run on interrupts by the RTC module.
*/
void tiny_potential_master_update(double time_since_last_update)
{
	//Some of the potential in the neuron has decayed away
	tiny_potential_time_update(time_since_last_update);//set the potential in accordance with the time since last update.
	
	//Update potential with values from dendrites
	tiny_potential_change = tiny_ADC_dendrite_potential();
	tiny_potential_increase_by(tiny_potential_change);
	
	//Update potential with values from button
	tiny_potential_button_update();
	
	//Update potential with values from spontaneous pulse.
	if (spontaneous_pulse_mode)
	{
		tiny_potential_increase_by(spont_pulse_delta_potential());
	}
	
	//Check to see if the axon should fire
	if (tiny_potential > 50)
	{
		//The neurons potential is very high, so we fire twice
		tiny_DAC_axon_master_update(true, true);//DAC is used to write pulse signal.
		tiny_potential_set(POST_FIRE_POTENTIAL);//post-pulse potential is set.
	}
	else if (tiny_potential > 25)
	{
		//The neurons potential is high enough to fire
		tiny_DAC_axon_master_update(true, false);
		tiny_potential_set(POST_FIRE_POTENTIAL);
	}
	else
	{
		//The neurons potential is not high enough to fire
		tiny_DAC_axon_master_update(false, false);//DAC needs to be updated so that the timed pulses can be written later on.
		
		if(tiny_potential < -25)
		{
			//The neurons potential is low enough to remove a queued fire (Fire less)
			if(tiny_DAC_axon_neg_pulse_queue_check())
			{
				tiny_potential_set(0);
			}
		}
	}
	
	//Update the led
	potential_to_RGB_update_LEDs(tiny_potential);
}
