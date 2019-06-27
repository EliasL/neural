/*
 * tiny_DAC_axon.c
 *
 * Created: 18.06.2018 16:10:31
 *  Author: Bendik
 */ 

#include <atmel_start.h>
#include <stdbool.h>
#include "ISR_timer_counter/ISR_timer_counter.h"
#include <math.h>
#include "Potential_to_RGB/Potential_to_RGB.h"
#include "tiny_DAC_axon/tiny_DAC_axon.h"


#define AXON_DELAY 100//dendrite delay in ms

/*
Initiates variables for neuron type, axon firing constants etc.
*/
_Bool tiny_DAC_axon_prev = false;
_Bool tiny_DAC_axon_fire = false;

_Bool this_neurons_type = EXCITATORY_NEURON;
uint8_t pulses_in_queue = 0;//variable to determine how many pulses are in queue.

uint32_t axon_pulse_time_queue [4] = {0};

/*
sets neuron type, should probably be accessible from the master function
of the entire neuron, maybe I'm wrong though.
*/
void tiny_DAC_set_neuron_type(enum NeuronType neuron_type) // Make into enum
{
	this_neurons_type = neuron_type;
}

/*
Pulse send function.
sends a pulse dependent on the neurons type.
*/
static void tiny_DAC_axon_send_pulse(void)
{
	if (this_neurons_type == EXCITATORY_NEURON)
	{
		DAC_set_output(255);
	}
	else if(this_neurons_type == INHIBITORY_NEURON)
	{
		DAC_set_output(128);
	}
}


/*
Master update function for the module.
The function should set the DAC to fire for two
update cycles once the pulse flag is set high.
*/
static void tiny_DAC_update_axon(void)
{
	if (tiny_DAC_axon_fire)
	{
		tiny_DAC_axon_fire = false;
		tiny_DAC_axon_send_pulse();
		tiny_DAC_axon_prev = true;
	}
	else if (tiny_DAC_axon_prev)
	{
		tiny_DAC_axon_prev = false;
	}
	else if (!tiny_DAC_axon_prev && !tiny_DAC_axon_fire)
	{
		DAC_set_output(0);
	}
}


/*
Function to set firing.
Function also updates the pulse queue accordingly.
*/
static void tiny_DAC_axon_set_fire()
{
	tiny_DAC_axon_fire = true;
	pulses_in_queue--;
	axon_pulse_time_queue[0] = axon_pulse_time_queue[1];
	axon_pulse_time_queue[1] = axon_pulse_time_queue[2];
	axon_pulse_time_queue[2] = axon_pulse_time_queue[3];
	axon_pulse_time_queue[3] = 0;
}


/*
solution to remove future firing if a inhibitory signal is received
shortly after a excitatory signal.
*/
bool tiny_DAC_axon_neg_pulse_queue_check(void)
{
	uint8_t element = 5;
	for(int i = 0; i < 4; i++)
	{
		if ((ISR_timer_count()+60) < axon_pulse_time_queue[i])
		{
			element = i;
		}
	}
	if(element != 5)
	{
		axon_pulse_time_queue[element] = 0;
		pulses_in_queue--;
		return true;
	}
	else
	{
		return false;
	}
}

/*
Adds an element to the queue of axon pulse times.
The variable new_fire_time sets the time of when the axon should fire.
*/
static void tiny_DAC_axon_queue_fire_time(uint32_t new_fire_time)
{
	if (pulses_in_queue < 4)
	{
		pulses_in_queue++;
		axon_pulse_time_queue[pulses_in_queue-1] = new_fire_time;
	}
}



/*
Dirty, dirty, dirty solution to add dendrite delay.
This will be functionally the same as required by specs.
Will look into updating if I find a more elegant solution to the problem
that's at least as effective as this one.
*/
void tiny_DAC_axon_master_update(_Bool over_25, _Bool over_50)
{
	if(over_25 && over_50)
	{
		tiny_DAC_axon_queue_fire_time(ISR_timer_count() + 100);
		tiny_DAC_axon_queue_fire_time(ISR_timer_count() + 150);//hacky solution to add 2 firing pulses in case of very high received potential.
	}
	else if (over_25)
	{
		tiny_DAC_axon_queue_fire_time(ISR_timer_count()+100);
	}
	if ((pulses_in_queue > 0) && (axon_pulse_time_queue[0] < ISR_timer_count()))
	{
		tiny_DAC_axon_set_fire();
		set_LED_fire();
	}
	tiny_DAC_update_axon();
}
