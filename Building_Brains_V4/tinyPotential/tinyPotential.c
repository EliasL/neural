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
#include "tinyDebugger/tinyDebugger.h"

static double tinyPotential_potential = 0;

/*
Function to decay the potential towards 0
*/
static void tinyPotential_decay()
{
	// Previously, we kept track of time in case the microchip for some reason uses more than one ms on a cycle
	// but for simplification, we just assume that each cycle will take one ms. The consequences for a cycle taking longer
	// are negligible. 
	
	double time_since_last_update = 1;
	tinyPotential_potential *= (exp(-(time_since_last_update/TINYPOTENTIAL_TIME_CONST)));
	if(fabs(tinyPotential_potential)<0.1){
		tinyPotential_potential=0;
	}
}

/*
The function which will run in the main loop.
This function will run on interrupts by the RTC module.
*/
void tinyPotential_update()
{
	tinyDebugger_send_double("Potential", tinyPotential_potential);
	//Some of the potential in the neuron has decayed away
	tinyPotential_decay();
	
	// Update potential with values from Dendrites
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
