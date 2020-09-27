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
#include "tinyLED/tinyLED.h"
#include "tinyAxon/tinyAxon.h"

// Signal types
enum DendriteSignal
{
	NO_SIGNAL, LOW_INHIB, NORMAL_INHIB, HIGH_INHIB, LOW_EXCITE, NORMAL_EXCITE, HIGH_EXCITE, CHARGING
};

uint8_t tinyDendrite_values[DENDRITE_COUNT] = {0}; // Current ADC (Analog to Digital Converter) values
uint8_t Dendrite_ports[DENDRITE_COUNT] = {DENDRITE_PORT_1, DENDRITE_PORT_2, DENDRITE_PORT_3, DENDRITE_PORT_4, DENDRITE_PORT_5}; // Ports used on the ADC MUX
	
enum DendriteSignal tinyDendrite_current_signals[DENDRITE_COUNT] = {NO_SIGNAL};
enum DendriteSignal tinyDendrite_previous_signals[DENDRITE_COUNT] = {NO_SIGNAL};


/*
This function reads the voltage at the Dendrite inputs with the ADC
*/
void tinyDendrite_read_signals(void)
{
	for (int i = 0; i < DENDRITE_COUNT; i++)
	{
		tinyDendrite_values[i] = ADC_0_get_conversion(Dendrite_ports[i]);
	}
}

uint8_t tinyDendrite_get_value(uint8_t dendrite_number){
	return tinyDendrite_values[dendrite_number];
}

_Bool tinyDendrite_check_charge_level(void)
{
	_Bool charging = false;
	
	tinyDendrite_read_signals();
	for (uint8_t i = 0; i < DENDRITE_COUNT; i++)
	{
		tinyDendrite_previous_signals[i] = tinyDendrite_current_signals[i];
		if (tinyDendrite_values[i] > CHARGING_THRESHOLD)
		{
			tinyDendrite_current_signals[i] = CHARGING;
			charging = true;
		}
	}
	return charging;
}

/*
This function converts the 8 bit value from the ADC into one of the signal types defined in DendriteSignal
*/
void tinyDendrite_update_signals(void)
{
	
	// This function does not read the dendrite values! Read_signals must be called somewhere prior to this function!
	// As of writing this, the update_charging_mode function in main runs check_charge_level, so 
	// the tinyDendrite_values are updated when update_signals is called later
	
	tinyDebugger_send_uint8("D1", tinyDendrite_values[0]);
	tinyDebugger_send_uint8("D2", tinyDendrite_values[1]);
	tinyDebugger_send_uint8("D3", tinyDendrite_values[2]);
	tinyDebugger_send_uint8("D4", tinyDendrite_values[3]);
	tinyDebugger_send_uint8("D5", tinyDendrite_values[4]);
	
	for (uint8_t i = 0; i < DENDRITE_COUNT; i++)
	{
		tinyDendrite_previous_signals[i] = tinyDendrite_current_signals[i];
		if (tinyDendrite_values[i] > CHARGING_THRESHOLD)
		{
			tinyDendrite_current_signals[i] = CHARGING;
			// Previously, we used this function to check charging, but this has now
			// been moved to tinyDendrite_check_charging.
			//charging = true;
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
}



/*
This is the master function of the module that is callable from
outside. It uses the previously declared functions to return the potential.
*/
int16_t tinyDendrite_get_potential()
{
	if(tinyAxon_is_firing() && IGNORE_INPUT_WHILE_FIRING){
		
		return NO_SIGNAL_REACTION;
	}
	
	//Convert the digital value to the various signals defined in DendriteSignalType
	tinyDendrite_update_signals();
	
	int16_t return_potential_val = 0;
	for (uint8_t i = 0; i < DENDRITE_COUNT; i++)
	{
		switch(tinyDendrite_current_signals[i])
		{
			case NO_SIGNAL:
				return_potential_val += NO_SIGNAL_REACTION;
				break;
			case HIGH_EXCITE:
				return_potential_val += HIGH_EXCITE_REACTION;
				tinyLED_queue_flash(INN_LED, GREEN);
				break;
			case NORMAL_EXCITE:
				return_potential_val += NORMAL_EXCITE_REACTION;
				tinyLED_queue_flash(INN_LED, GREEN);
				break;
			case LOW_EXCITE:
				return_potential_val += LOW_EXCITE_REACTION;
				tinyLED_queue_flash(INN_LED, GREEN);
				break;
			case HIGH_INHIB:
				return_potential_val += HIGH_INHIB_REACTION;
				tinyLED_queue_flash(INN_LED, RED);
				break;
			case NORMAL_INHIB:
				return_potential_val += NORMAL_INHIB_REACTION;
				tinyLED_queue_flash(INN_LED, RED);
				break;
			case LOW_INHIB:
				return_potential_val += LOW_INHIB_REACTION;
				tinyLED_queue_flash(INN_LED, RED);
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