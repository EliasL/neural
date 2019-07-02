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
#include "tinyPulse/tinyPulse.h"
#include "settings.h"

static double tinyPotential_potential = 0;

/*
Function to decay the potential towards 0
*/
static void tinyPotential_decay(double time_since_last_update)
{
	tinyPotential_potential *= (exp(-(time_since_last_update/TINYPOTENTIAL_TIME_CONST)));
}

/*
The function which will run in the main loop.
This function will run on interrupts by the RTC module.
*/
void tinyPotential_update(double time_since_last_update)
{
	//Some of the potential in the neuron has decayed away
	tinyPotential_decay(time_since_last_update);
	
	// Update potential with values from dendrites
	tinyPotential_potential = tinyDendrite_update_potential(tinyPotential_potential);
	
	// Update potential from button press
	tinyPotential_potential = tinyButton_update_potential(tinyPotential_potential);
	
	// Update potential with values from spontaneous pulse.
	tinyPotential_potential = tinyPulse_update_potential(tinyPotential_potential);
	
	// Let the axon affect the potential
	// This is also where we decide whether or not the axon should fire
	tinyPotential_potential = tinyAxon_update_potential(tinyPotential_potential);

	//Update the led
	potential_to_RGB_update_LEDs(tinyPotential_potential);
}
