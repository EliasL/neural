/*
 * tiny_ADC_dendrites.c
 *
 * Created: 18.06.2018 13:50:15
 *  Author: Bendik Bogfjellmo
 */ 
#include <atmel_start.h>
#include <math.h>
#include "tiny_dendrites/tiny_ADC_dendrites.h"

#define tiny_ADC_dendrite_number 5//number of dendrites

//enum type for signal.
enum tiny_ADC_dendrite_signal_type
{
	no_signal, low_inhib_signal, normal_inhib_signal, high_inhib_signal, low_excite_signal, normal_excite_signal, high_excite_signal
};

uint16_t tiny_ADC_values[5] = {0};//current ADC values
uint8_t dendrite_ports[5] = {5, 7, 9, 10, 11};//ports used on the ADC MUX.
enum tiny_ADC_dendrite_signal_type tiny_ADC_dendrite_cur_signals[5] = {no_signal};
enum tiny_ADC_dendrite_signal_type tiny_ADC_dendrite_prev_signals[5] = {no_signal};


/*
This function updates the vector containing 8-bit ADC conversions
*/
static void tiny_ADC_dendrites_update_values(void)
{
	for (int i = 0; i < tiny_ADC_dendrite_number; i++)
	{
		tiny_ADC_values[i] = ADC_get_conversion(dendrite_ports[i]);
	}
}




/*
This function updates the vector of signal types. Signal type is an enumerated type declared earlier.
Since signal type is an enumerated type from 0 to 4 we can use the floor-function from math.h to decide the value.
What the function does is take the current ADC-measurements, and return a signal value. Some precations for signal errors have been made.
The function also sets the vector for previous signals and takes into account that
if the same reading has been received twice in a row it should be no_signal.
*/
static void tiny_ADC_update_signal(void)
{
	for (uint8_t i = 0; i < 5; i++)
	{
		tiny_ADC_dendrite_prev_signals[i] = tiny_ADC_dendrite_cur_signals[i];
		if ((tiny_ADC_values[i] < 256) && (tiny_ADC_values[i] > 213))
		{
			tiny_ADC_dendrite_cur_signals[i] = normal_excite_signal;
		}
		if ((tiny_ADC_values[i] < 214) && (tiny_ADC_values[i] > 160))
		{
			tiny_ADC_dendrite_cur_signals[i] = high_excite_signal;
		}
		if ((tiny_ADC_values[i] < 161) && (tiny_ADC_values[i] > 139))
		{
			tiny_ADC_dendrite_cur_signals[i] = low_excite_signal;
		}
		if ((tiny_ADC_values[i] < 140) && (tiny_ADC_values[i] > 114))
		{
			tiny_ADC_dendrite_cur_signals[i] = normal_inhib_signal;
		}
		if ((tiny_ADC_values[i] < 115) && (tiny_ADC_values[i] > 87))
		{
			tiny_ADC_dendrite_cur_signals[i] = high_inhib_signal;
		}
		if ((tiny_ADC_values[i] < 88) && (tiny_ADC_values[i] > 50))
		{
			tiny_ADC_dendrite_cur_signals[i] = low_inhib_signal;
		}
		if (tiny_ADC_values[i] < 51)
		{
			tiny_ADC_dendrite_cur_signals[i] = no_signal;
		}
		if (tiny_ADC_dendrite_cur_signals[i] == tiny_ADC_dendrite_prev_signals[i])
		{
			tiny_ADC_dendrite_cur_signals[i] = no_signal;
		}
	}
}



/*
This is the master function of the module that is callable from
outside. It uses the previously declared functions to return
the change in potential which is the only thing any
outside libraries will have to use.
It's not exactly elegant to use a switch and a for-loop, but it works.
*/
int8_t tiny_ADC_dendrite_delta_potential()
{
	tiny_ADC_dendrites_update_values();
	tiny_ADC_update_signal();
	int16_t return_potential_val = 0;
	for (int i = 0; i < tiny_ADC_dendrite_number; i++)
	{
		switch(tiny_ADC_dendrite_cur_signals[i])
		{
			case no_signal:
				break;
			case high_excite_signal:
				return_potential_val += 52;
				break;
			case normal_excite_signal:
				return_potential_val += 26;
				break;
			case low_excite_signal:
				return_potential_val += 20;
				break;
			case high_inhib_signal:
				return_potential_val -= 50;
				break;
			case normal_inhib_signal:
				return_potential_val -= 26;
			case low_inhib_signal:
				return_potential_val -= 20;
			default:
				break;
		}
	}
	return return_potential_val;
}
