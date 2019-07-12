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
#include "tinyTime/tinyTime.h"
#include "tinyButton/tinyButton.h"
#include "tinyPulse/tinyPulse.h"
#include "settings.h"
#include "tinyDebugger/tinyDebugger.h"

static double tinyPotential_potential = 0;
static uint32_t previous_update_time = 0;

/*
Function to decay the potential towards 0
*/
static void tinyPotential_decay()
{
		
	uint8_t time_since_last_update = tinyTime_now() - previous_update_time;
	tinyPotential_potential *= (exp(-((float)time_since_last_update/(float)TINYPOTENTIAL_TIME_CONST)));
	if(fabs(tinyPotential_potential)<0.1){
		tinyPotential_potential=0;
	}
	previous_update_time = tinyTime_now();
}

/*
The function which will run in the main loop.
This function will run on interrupts by the RTC module.
*/
void tinyPotential_update()
{
	//Some of the potential in the neuron has decayed away
	tinyPotential_decay();
	// Update potential with values from Dendrites
	tinyPotential_potential = tinyDendrite_update_potential(tinyPotential_potential);
	tinyDebugger_send_double("DendP", tinyPotential_potential);
	
	// Update potential from button press
	tinyPotential_potential = tinyButton_update_potential(tinyPotential_potential);
	
	// Update potential with values from spontaneous pulse.
	tinyPotential_potential = tinyPulse_update_potential(tinyPotential_potential);
	
	// Let the axon affect the potential
	// This is also where we decide whether or not the axon should fire
	tinyPotential_potential = tinyAxon_update_potential(tinyPotential_potential);
	tinyDebugger_send_double("AxonP", tinyPotential_potential);
}
