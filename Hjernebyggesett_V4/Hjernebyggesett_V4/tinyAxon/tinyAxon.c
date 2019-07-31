/*
 * tinyAxon.c
 *
 * Created: 18.06.2018 16:10:31
 * Authors: Bendik Bogfjellmo, Elias Lundheim
 */ 

#include <atmel_start.h>
#include <stdbool.h>
#include <math.h>
#include "tinyTime/tinyTime.h"
#include "tinyAxon/tinyAxon.h"
#include "settings.h"
#include "tinyDebugger/tinyDebugger.h"
#include "tinyLED/tinyLED.h"


/*
Initiates variables for neuron type, axon firing constants etc.
*/
_Bool tinyAxon_has_fired = false;
_Bool tinyAxon_should_fire = false;

uint8_t pulses_in_queue = 0; //variable to determine how many pulses are in queue.

/*
When there are 0 pulses queued, all of the numbers in this list should be 0.
When we queue a pulse, we store the number of cycles until we fire.
Every cycle, we also decrease every number in this list by 1 (except if it is 0)
If a number goes from 1 to 0, we tell the axon to fire
*/
uint16_t pulse_queue[MAX_NUMBER_OF_PULSES] = {0};
	
// This function will be used with pulse_queue to find the newest pulse
uint8_t find_newest_pulse() {
	uint16_t max;
	uint8_t current_index = 0;
	uint8_t return_index = 0;
	
	max = pulse_queue[current_index];
	
	for (current_index = 1; current_index < MAX_NUMBER_OF_PULSES; current_index++) {
		if (pulse_queue[current_index] > max) {
			return_index = current_index;
			max = pulse_queue[current_index];
		}
	}
	return return_index;
}

uint8_t axonOutputValue = 0; // This variable is only used for debugging


/*
Pulse send function.
sends a pulse dependent on the neurons type.
*/
static void tinyAxon_start_sending_pulse()
{
	if (NEURONTYPE == EXCITATORY_NEURON)
	{
		DAC_0_set_output(EXCITATORY_NEURON_OUTPUT);
		axonOutputValue=EXCITATORY_NEURON_OUTPUT;
	}
	else if(NEURONTYPE == INHIBITORY_NEURON)
	{
		DAC_0_set_output(INHIBITORY_NEURON_OUTPUT);
		axonOutputValue=INHIBITORY_NEURON_OUTPUT;
	}
	
	tinyLED_set_color_mode(OUT_LED, WHITE, FLASH_ONCE);
}

void tinyAxon_stop_sending_pulse()
{
	DAC_0_set_output(NO_SIGNAL_OUTPUT);
	axonOutputValue=NO_SIGNAL_OUTPUT;
}


/*
Master update function for the module.
The function should set the DAC to fire for two
update cycles once the pulse flag is set high.
*/
static void tinyAxon_update_pulse_transmitter(void)
{
	if (tinyAxon_should_fire)
	{
		tinyAxon_should_fire = false;
		tinyAxon_has_fired = true;
		
		tinyAxon_start_sending_pulse();
	}
	else if (tinyAxon_has_fired)
	{
		tinyAxon_has_fired = false;
	}
	else if (!tinyAxon_has_fired && !tinyAxon_should_fire)
	{
		tinyAxon_stop_sending_pulse();
	}
}


/*
Function to set firing.
Function also updates the pulse queue accordingly.
*/
static void tinyAxon_fire_pulse()
{
	tinyAxon_should_fire = true;
	pulses_in_queue--;
	// TODO led update
}


/*
If the potential is very low, we want to try to remove a pulse.
*/
bool tinyAxon_remove_pulse(void)
{
	// We want to return a bool indicating whether or not a pulse actually was removed.
	if(pulses_in_queue == 0){
		//There was no pulse to remove.
		return false;
	}
	else{
		// If we are to remove a pulse, we want to remove the one that will fire last.
		uint8_t pulse_index = find_newest_pulse();
		uint16_t newest_pulse = pulse_queue[pulse_index];
	
		// Now we want to check if the pulse is too far away to be affected by the low potential, or close enough that we decide to remove it.
		// (When we say that the pulse is too far away, it refers to the biological process of how the potential spreads from Dendrites to axon).
		if(newest_pulse > PULSE_NO_RETURN_TIME){
			// We decided to remove the pulse
			pulse_queue[pulse_index] = 0;
			pulses_in_queue--;
			return true;
		}
		// Here we have found that there is a pulse queued, but it is old enough to let pass anyway, so now we need to put it back into the queue.
		else{
			return false;
		}
	}
}

/*
Adds an element to the queue
*/
static void tinyAxon_add_pulse(uint16_t new_pulse)
{
	// We want to check each slot in the pulse_queue, and
	// if we find an empty slot (0), we add a pulse.
	for (uint8_t i = 0; i<MAX_NUMBER_OF_PULSES; i++)
	{
		if(pulse_queue[i] == 0){
			pulse_queue[i] = new_pulse;
			pulses_in_queue++;
			// We return so we only ever add one
			break;
		}
	}
	// We might not add any pulses if the list is full, but we still pretend as though we have.
	// Maybe this should be changed in the future?
}



/*
Decides whether or not the axon should fire
If the axon does fire, the potential is reduced
*/
double tinyAxon_update_potential(double potential)
{	
	//While the neuron has enough potential to fire, we want to fire more
	while (potential > THRESHOLD_POTENTIAL)
	{
		// We have to check if there are already queued pulses, so that the frequency never exceeds FIRE_DELAY
		if(pulses_in_queue>0){
			uint16_t newest_pulse = pulse_queue[find_newest_pulse()];
			
			// There is at least one pulse in the queue, and it is so close, that we need to offset the new pulse, so that we keep at least
			// one FIRE_DELAY between each pulse
			if(newest_pulse + FIRE_DELAY > TRAVLE_DELAY){
				tinyAxon_add_pulse(newest_pulse + FIRE_DELAY);
			}
			// There is at least one pulse in the queue, but it's far enough away to ignore
			else{
				tinyAxon_add_pulse(TRAVLE_DELAY);
			}
		}
		// There are no pulses in the queue, so we add a pulse as normal
		else{
			tinyAxon_add_pulse(TRAVLE_DELAY);		
		}
		
		potential += POSTFIRE_POTENTIAL_REACTION; // This is usually defined as a negative value, don't be confused by the +=
		
		tinyLED_set_color_mode(INN_LED, GREEN, FLASH_ONCE);
	}
	
	// If the neuron has a very low potential, we want to remove a pulse from the queue (if there is one)
	if(potential < -THRESHOLD_POTENTIAL && pulses_in_queue > 0) // Perhaps this should be a separate variable? For now, we will just simply use -THRESHOLD_POTENTIAL
	{
		// The neurons potential is low enough to attempt to remove a queued fire (Fire less)
		if(tinyAxon_remove_pulse())
		{
			// The potential has evened out a bit
			potential += THRESHOLD_POTENTIAL;
		}
	}
	
	// If there are pulses in the queue, we want to reduce the time in each of the pulse_queue elements
	if (pulses_in_queue > 0)
	{
		for (uint8_t i = 0; i<MAX_NUMBER_OF_PULSES; i++)
		{
			if(pulse_queue[i] != 0){
				pulse_queue[i]--;
				
				// If the time went from 1 to 0, we fire the axon
				if(pulse_queue[i] == 0){
					
					// We fire the axon
					tinyAxon_fire_pulse();
				}
			}
		}
	}
	
	// Here we set the actual output of the DAC (Digital to Analog Converter)
	tinyAxon_update_pulse_transmitter();
	
	// We need to check if the axon is connected to a charger. We do this by checking the AXON_CHECK_PIN. If it is hight while the axon is not firing, it must be connected to a charger
	if(AXON_CHECK_PIN_get_level() && !tinyAxon_should_fire){
		//tinyCharge_set_charging_mode(true);
	}
	
	tinyDebugger_send_uint8("Axon", axonOutputValue);
	tinyDebugger_send_uint8("Pulses", pulses_in_queue);
	
	return potential;
}
