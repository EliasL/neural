/*
 * tinyDendriteites.c
 *
 * Created: 18.06.2018 13:50:15
 * Authors: Bendik Bogfjellmo, Elias Lundheim
 */ 
#include <atmel_start.h>
#include <math.h>
#include "tinyDendrite/tinyDendrite.h"
#include "settings.h"
#include "tinyCharge/tinyCharge.h"

// Signal types
enum DendriteiteSignal
{
	NO_SIGNAL, LOW_INHIB, NORMAL_INHIB, HIGH_INHIB, LOW_EXCITE, NORMAL_EXCITE, HIGH_EXCITE, CHARGING
};

uint16_t tinyDendriteite_values[TINYDendriteITE_COUNT] = {0}; // Current ADC (Analog to Digital Converter) values
uint8_t Dendriteite_ports[TINYDendriteITE_COUNT] = {DendriteITE_PORT_1, DendriteITE_PORT_2, DendriteITE_PORT_3, DendriteITE_PORT_4, DendriteITE_PORT_5}; // Ports used on the ADC MUX
	
enum DendriteiteSignal tinyDendriteite_current_signals[TINYDendriteITE_COUNT] = {NO_SIGNAL};
enum DendriteiteSignal tinyDendriteite_previous_signals[TINYDendriteITE_COUNT] = {NO_SIGNAL};


/*
This function reads the voltage at the Dendriteite inputs with the ADC
*/
static void tinyDendriteite_read_signals(void)
{
	for (int i = 0; i < TINYDendriteITE_COUNT; i++)
	{
		tinyDendriteite_values[i] = ADC_get_conversion(Dendriteite_ports[i]);
	}
}


/*
This function converts the 8 bit value from the ADC into one of the signal types defined in DendriteiteSignal
We also update the charging state
*/
void tinyDendriteite_update_signals(void)
{
	tinyCharge_set_charging(false);
	
	for (uint8_t i = 0; i < TINYDendriteITE_COUNT; i++)
	{
		tinyDendriteite_previous_signals[i] = tinyDendriteite_current_signals[i];
		if (tinyDendriteite_values[i] > CHARGING_THRESHOLD)
		{
			tinyDendriteite_current_signals[i] = CHARGING;
			tinyCharge_set_charging(true);
		}
		else if (tinyDendriteite_values[i] > NORMAL_EXCITE_THRESHOLD)
		{
			tinyDendriteite_current_signals[i] = NORMAL_EXCITE;
		}
		else if (tinyDendriteite_values[i] > HIGH_EXCITE_THRESHOLD)
		{
			tinyDendriteite_current_signals[i] = HIGH_EXCITE;
		}
		else if (tinyDendriteite_values[i] > LOW_EXCITE_THRESHOLD)
		{
			tinyDendriteite_current_signals[i] = LOW_EXCITE;
		}
		else if (tinyDendriteite_values[i] > NORMAL_INHIB_THRESHOLD)
		{
			tinyDendriteite_current_signals[i] = NORMAL_INHIB;
		}
		else if (tinyDendriteite_values[i] > HIGH_INHIB_THRESHOLD)
		{
			tinyDendriteite_current_signals[i] = HIGH_INHIB;
		}
		else if (tinyDendriteite_values[i] > LOW_INHIB_THRESHOLD)
		{
			tinyDendriteite_current_signals[i] = LOW_INHIB;
		}
		else
		{
			tinyDendriteite_current_signals[i] = NO_SIGNAL;
		}
		if (tinyDendriteite_current_signals[i] == tinyDendriteite_previous_signals[i])
		{
			tinyDendriteite_current_signals[i] = NO_SIGNAL;
		}
	}
}



/*
This is the master function of the module that is callable from
outside. It uses the previously declared functions to return the potential.
*/
int16_t tinyDendriteite_get_potential()
{
	//Read the analog voltage values on each of the Dendriteites
	tinyDendriteite_read_signals();
	//Convert the digital value to the various signals defined in DendriteiteSignalType
	tinyDendriteite_update_signals();
	
	int16_t return_potential_val = 0;
	for (int i = 0; i < TINYDendriteITE_COUNT; i++)
	{
		switch(tinyDendriteite_current_signals[i])
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

double tinyDendriteite_update_potential(double potential){
	
	uint16_t potential_change = tinyDendriteite_get_potential();
	potential += potential_change;
	return potential;
}