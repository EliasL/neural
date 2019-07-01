/*
 * tinyPotential.c
 *
 * Created: 18.06.2018 18:50:16
 * Authors: Bendik Bogfjellmo, Elias Lundheim
 */ 


#include <atmel_start.h>
#include <math.h>
#include <stdbool.h>
#include "tinyPotential.h"
#include "tinyDendrite/tinyDendrite.h"
#include "tinyAxon/tinyAxon.h"
#include "Potential_to_RGB/Potential_to_RGB.h"
#include "tinyTime/tinyTime.h"
#include "tinyButton/tinyButton.h"
#include "spont_pulse/spont_pulse.h"
#include "settings.h"

static double tinyPotential_potential = 0;
double tinyPotential_change = 0; // This variable is for debugging
static _Bool spontaneous_pulse_mode = false;

/*
Internal function to enable incrementing or decrementing
potential from the signal of a button push or dendrite.
*/
static void tinyPotential_increase_by(int8_t delta_potential)
{
	tinyPotential_potential += delta_potential;
}

/*
Function to decay the potential towards 0
*/
static void tinyPotential_decay(double time_since_last_update)
{
	tinyPotential_potential *= (exp(-(time_since_last_update/TINYPOTENTIAL_TIME_CONST)));
}


/*
Function to update potential and set spontaneous pulse mode
by using the master update function in the button module.
*/
static void tinyPotential_button_update()
{
	if (tinyButton_get_state()) // If the button is pressed, we want the neuron to fire
	{
		tinyPotential_increase_by(THRESHOLD_POTENTIAL + 1);
	}
	spontaneous_pulse_mode = tinyButton_is_spont_pulse_on();
}

/*
The function which will run in the main loop.
This function will run on interrupts by the RTC module.
*/
void tinyPotential_update(double time_since_last_update)
{
	//Some of the potential in the neuron has decayed away
	tinyPotential_decay(time_since_last_update);
	
	//Update potential with values from dendrites
	tinyPotential_change = tinyDendrite_get_potential();
	tinyPotential_increase_by(tinyPotential_change);
	
	//Update potential with values from button
	tinyPotential_button_update();
	
	//Update potential with values from spontaneous pulse.
	if (spontaneous_pulse_mode)
	{
		tinyPotential_increase_by(spont_pulse_delta_potential());
	}
	
	// let the axon affect the potential
	tinyPotential_potential = tinyAxon_update_potential(tinyPotential_potential);

	//Update the led
	potential_to_RGB_update_LEDs(tinyPotential_potential);
}
