/*
 * tinyDendrites.c
 *
 * Created: 18.06.2018 13:50:15
 * Authors: Bendik Bogfjellmo, Elias Lundheim
 */ 
#include <atmel_start.h>
#include <math.h>
#include <stdio.h>
#include "tinyDendrite/tinyDendrite.h"
#include "settings.h"
#include "tinyCharge/tinyCharge.h"
#include "tinyDebugger/tinyDebugger.h"

// Signal types
enum DendriteSignal
{
	NO_SIGNAL, LOW_INHIB, NORMAL_INHIB, HIGH_INHIB, LOW_EXCITE, NORMAL_EXCITE, HIGH_EXCITE, CHARGING
};

uint16_t tinyDendrite_values[TINYDENDRITE_COUNT] = {0}; // Current ADC (Analog to Digital Converter) values
uint8_t Dendrite_ports[TINYDENDRITE_COUNT] = {DENDRITE_PORT_1, DENDRITE_PORT_2, DENDRITE_PORT_3, DENDRITE_PORT_4, DENDRITE_PORT_5}; // Ports used on the ADC MUX
	
enum DendriteSignal tinyDendrite_current_signals[TINYDENDRITE_COUNT] = {NO_SIGNAL};
enum DendriteSignal tinyDendrite_previous_signals[TINYDENDRITE_COUNT] = {NO_SIGNAL};


/*
This function reads the voltage at the Dendrite inputs with the ADC
*/
static void tinyDendrite_read_signals(void)
{
	for (int i = 0; i < TINYDENDRITE_COUNT; i++)
	{
		tinyDendrite_values[i] = ADC_get_conversion(Dendrite_ports[i]);
	}
	tinyDebugger_send_int("D1", tinyDendrite_values[0]);
	tinyDebugger_send_int("D2", tinyDendrite_values[1]);
	tinyDebugger_send_int("D3", tinyDendrite_values[2]);
	tinyDebugger_send_int("D4", tinyDendrite_values[3]);
	tinyDebugger_send_int("D5", tinyDendrite_values[4]);
}


/*
This function converts the 8 bit value from the ADC into one of the signal types defined in DendriteSignal
We also update the charging state
*/
void tinyDendrite_update_signals(void)
{
	
	//Read the analog voltage values on each of the Dendrites
	tinyDendrite_read_signals();
	
	_Bool charging = false;
	
	for (uint8_t i = 0; i < TINYDENDRITE_COUNT; i++)
	{
		tinyDendrite_previous_signals[i] = tinyDendrite_current_signals[i];
		if (tinyDendrite_values[i] > CHARGING_THRESHOLD)
		{
			tinyDendrite_current_signals[i] = CHARGING;
			charging = true;
		}
		else if (tinyDendrite_values[i] > NORMAL_EXCITE_THRESHOLD)
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
	tinyCharge_set_charging_mode(charging);
}



/*
This is the master function of the module that is callable from
outside. It uses the previously declared functions to return the potential.
*/
int16_t tinyDendrite_get_potential()
{
	//Convert the digital value to the various signals defined in DendriteSignalType
	tinyDendrite_update_signals();
	
	int16_t return_potential_val = 0;
	for (uint8_t i = 0; i < TINYDENDRITE_COUNT; i++)
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
			case CHARGING:
				// Nothing happens
				break;
			default:
				break;
		}
	}
	return return_potential_val;
}

double tinyDendrite_update_potential(double potential){
	
	int16_t potential_change = tinyDendrite_get_potential();
	potential += potential_change;
	return potential;
}