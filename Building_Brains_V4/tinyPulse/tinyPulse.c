/*
 * tinyPulse.c
 *
 * Created: 02.07.2019 13:14:50
 * Author: Elias Lundheim
 */ 

#include <stdbool.h>
#include "tinyTime/tinyTime.h"
#include "settings.h"

/*

The tinyPulse keeps track of two things. The first is whether or not the neuron is in
pulseMode. If the neuron is in pulse mode, it should pulse with a certain frequency. 
The second thing tinyPulse keeps track of is whether or not it is time to send a pulse.
If the frequency it is set to is very low, it should seldomly send a pulse, but it should
send a pulse more often, if the frequency is higher.

*/

_Bool pulse_mode = false;
uint32_t time_of_last_pulse = 0;
uint16_t time_since_last_pulse = 0;
uint16_t ideal_time_between_pulses = 1000/PULSEMODE_FREQUENCY;

void tinyPulse_toggle_pulse_mode(){
	pulse_mode = !pulse_mode;
}

double tinyPulse_update_potential(double potential){
	if(pulse_mode){
		
		time_since_last_pulse = tinyTime_now() - time_of_last_pulse;
		
		if(time_since_last_pulse >= ideal_time_between_pulses){
			potential += BUTTON_PRESS_REACTION;
			time_of_last_pulse = tinyTime_now();			
		}
	}
	return potential;
}
