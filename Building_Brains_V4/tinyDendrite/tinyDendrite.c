/*
 * tinyDendrites.c
 *
 * Created: 18.06.2018 13:50:15
 * Authors: Bendik Bogfjellmo, Elias Lundheim
 */ 
#include <atmel_start.h>
#include <math.h>
#include "tinyDendrite/tinyDendrite.h"
#include "settings.h"

// Signal types
enum DendriteSignal
{
	NO_SIGNAL, LOW_INHIB, NORMAL_INHIB, HIGH_INHIB, LOW_EXCITE, NORMAL_EXCITE, HIGH_EXCITE
};

uint16_t tinyDendrite_values[TINYDENDRITE_COUNT] = {0}; // Current ADC (Analog to Digital Converter) values
uint8_t dendrite_ports[TINYDENDRITE_COUNT] = {DENDRITE_PORT_1, DENDRITE_PORT_2, DENDRITE_PORT_3, DENDRITE_PORT_4, DENDRITE_PORT_5}; // Ports used on the ADC MUX
	
enum DendriteSignal tinyDendrite_current_signals[TINYDENDRITE_COUNT] = {NO_SIGNAL};
enum DendriteSignal tinyDendrite_previous_signals[TINYDENDRITE_COUNT] = {NO_SIGNAL};


/*
This function reads the voltage at the dendrite inputs with the ADC
*/
static void tinyDendrite_read_signals(void)
{
	for (int i = 0; i < TINYDENDRITE_COUNT; i++)
	{
		tinyDendrite_values[i] = ADC_get_conversion(dendrite_ports[i]);
	}
}


/*
This function converts the 8 bit value from the ADC into one of the signal types defined in DendriteSignal
*/
static void tinyDendrite_update_signals(void)
{
	for (uint8_t i = 0; i < TINYDENDRITE_COUNT; i++)
	{
		tinyDendrite_previous_signals[i] = tinyDendrite_current_signals[i];
		if (tinyDendrite_values[i] > NORMAL_EXCITE_THRESHOLD)
		{
			tinyDendrite_current_signals[i] = NORMAL_EXCITE;
		}
		else if (tinyDendrite_values[i] > HIGH_EXCITE_THRESHOLD)
		{
			tinyDendrite_current_signals[i] = HIGH_EXCITE;
		}
		else if (tinyDendrite_values[i] > LOW_EXCITE_THRESHOLD)
		{
			tinyDendrite_current_signals[i] = LOW_EXCITE;
		}
		else if (tinyDendrite_values[i] > NORMAL_INHIB_THRESHOLD)
		{
			tinyDendrite_current_signals[i] = NORMAL_INHIB;
		}
		else if (tinyDendrite_values[i] > HIGH_INHIB_THRESHOLD)
		{
			tinyDendrite_current_signals[i] = HIGH_INHIB;
		}
		else if (tinyDendrite_values[i] > LOW_INHIB_THRESHOLD)
		{
			tinyDendrite_current_signals[i] = LOW_INHIB;
		}
		else
		{
			tinyDendrite_current_signals[i] = NO_SIGNAL;
		}
		if (tinyDendrite_current_signals[i] == tinyDendrite_previous_signals[i])
		{
			tinyDendrite_current_signals[i] = NO_SIGNAL;
		}
	}
}



/*
This is the master function of the module that is callable from
outside. It uses the previously declared functions to return the potential.
*/
int16_t tinyDendrite_get_potential()
{
	//Read the analog voltage values on each of the dendrites
	tinyDendrite_read_signals();
	//Convert the digital value to the various signals defined in DendriteSignalType
	tinyDendrite_update_signals();
	
	int16_t return_potential_val = 0;
	for (int i = 0; i < TINYDENDRITE_COUNT; i++)
	{
		switch(tinyDendrite_current_signals[i])
		{
			case NO_SIGNAL:
				return_potential_val += NO_SIGNAL_REACTION;
				break;
			case HIGH_EXCITE:
				return_potential_val += HIGH_EXCITE_REACTION;
				break;
			case NORMAL_EXCITE:
				return_potential_val += NORMAL_EXCITE_REACTION;
				break;
			case LOW_EXCITE:
				return_potential_val += LOW_EXCITE_REACTION;
				break;
			case HIGH_INHIB:
				return_potential_val += HIGH_INHIB_REACTION;
				break;
			case NORMAL_INHIB:
				return_potential_val += NORMAL_INHIB_REACTION;
				break;
			case LOW_INHIB:
				return_potential_val += LOW_INHIB_REACTION;
				break;
			default:
				break;
		}
	}
	return return_potential_val;
}
