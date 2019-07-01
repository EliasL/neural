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
#include "Potential_to_RGB/Potential_to_RGB.h"
#include "tinyAxon/tinyAxon.h"
#include "include/queue.h"

// Time for pulse to travel from dendrites to axon
#define TRAVLE_DELAY 100
// Minimum time between pulses
#define FIRE_DELAY 50
// If a pulse has been queued, and the neurons potential drops significantly shortly after the pulse has been queued
// we want to remove the pulse. However, if the potential has already traveled most of the distance to the axon, we
// want to let the pulse reach the axon anyway (fire). An UNDO_PERIOD of 0 would mean that a queued pulse is never removed.
#define UNDO_PERIOD 60

/*
Initiates variables for neuron type, axon firing constants etc.
*/
_Bool tinyAxon_has_fired = false;
_Bool tinyAxon_should_fire = false;

_Bool this_neurons_type = EXCITATORY_NEURON;
uint8_t pulses_in_queue = 0; //variable to determine how many pulses are in queue.

/*
We are using a queue system, see src/queue.c
But we often want to check the element at the end of the queue (The element that is about to be dequeued)
so in addition to the queue, have an additional element (next_pulse) that is effectively part 
of the queue, but is actually a separate variable for easier access
*/
node_t *pulse_queue = NULL;
uint32_t next_pulse;

uint8_t axonOutputValue = 0;


//sets neuron type
void tinyDendrite_set_neuron_type(enum NeuronType neuron_type)
{
	this_neurons_type = neuron_type;
}

/*
Pulse send function.
sends a pulse dependent on the neurons type.
*/
static void tinyAxon_start_sending_pulse()
{
	if (this_neurons_type == EXCITATORY_NEURON)
	{
		DAC_set_output(255);
		axonOutputValue=225;
	}
	else if(this_neurons_type == INHIBITORY_NEURON)
	{
		DAC_set_output(128);
		axonOutputValue=128;
	}
}

static void tinyAxon_stop_sending_pulse()
{
	
	DAC_set_output(0);
	axonOutputValue=0;
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
	next_pulse = dequeue(&pulse_queue);
}


/*
solution to remove future firing if a inhibitory signal is received
shortly after a excitatory signal.
*/
bool tinyAxon_remove_pulse(void)
{
	// We want to remove the pulse last added to the queue
	// We also want to return a bool indicating whether or not a pulse actually was removed
	uint32_t now = tinyTime_now();
	uint32_t pulse_time = dequeue_top(&pulse_queue);
	if(pulse_time == 0){ // Here 0 is regarded as an error
		//There was no pulse to remove
		return false;
	}
	
	// Now we want to check if the pulse is too far away to be affected by the low potential, or close enough that we decide to remove it
	// (When we say that the pulse is too far away, it refers to the biological process of how the potential spreads from dendrites to axon)
	else if((now + UNDO_PERIOD) < pulse_time){
		// We decided to remove the pulse
		pulses_in_queue--;
		return true;
	}
	// Here we have found that the is a pulse queued, but it is old enough to let pass anyway, so now we need to put it back into the queue
	else{
		enqueue(&pulse_queue, pulse_time);
		return false;
	}
}

/*
Adds an element to the queue
*/
static void tinyAxon_enqueue_pulse(uint32_t new_pulse)
{
	enqueue(&pulse_queue, new_pulse);
	pulses_in_queue++;
}



/*
Decides whether or not the axon should fire
If the axon does fire, the potential is drastically reduced
*/
double tinyAxon_update_potential(double potential)
{
	int pulse_nr = 0;
	uint32_t now = tinyTime_now();
	
	//While the neuron has enough potential to fire, we want to fire more
	while (potential > 25)
	{
		tinyAxon_enqueue_pulse(now + TRAVLE_DELAY + FIRE_DELAY*pulse_nr);
		pulse_nr++;
		
		// I want to test reducing the potential by 30 instead of 25 to simulate the hyperpolarization
		potential -= 30;
	}
	
	// If the neuron has a very low potential, we want to remove a pulse from the queue (if there is one)
	if(potential < -25 && pulses_in_queue > 0)
	{
		// The neurons potential is low enough to attempt to remove a queued fire (Fire less)
		if(tinyAxon_remove_pulse())
		{
			// The potential has evened out a bit
			potential += 25;
		}
	}
	
	// If there are pulses in the queue, and the pulse has been scheduled to fire
	if ((pulses_in_queue > 0) && (next_pulse <= now))
	{
		// We fire the axon
		tinyAxon_fire_pulse();
		set_LED_fire();
	}
	
	// Here we set the actual output of the DAC (Digital to Analog Converter)
	tinyAxon_update_pulse_transmitter();
	return potential;
}
