/*
 * tinyPulse.c
 *
 * Created: 02.07.2019 13:14:50
 * Author: Elias Lundheim
 */ 

#include <stdbool.h>
#include <stdint.h>
#include "tinyTime/tinyTime.h"
#include "settings.h"
#include "tinyLED/tinyLED.h"

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


_Bool tinyPulse_is_in_pulse_mode(){
	return pulse_mode;
}

void tinyPulse_toggle_pulse_mode(){
	pulse_mode = !pulse_mode;
	
	if(tinyPulse_is_in_pulse_mode()){
		tinyLED_set_color_mode(OUT_LED, PULSEMODE_COLOR, WEAK);
		tinyLED_set_color_mode(INN_LED, PULSEMODE_COLOR, WEAK);
	}
	else{
		tinyLED_set_color(OUT_LED, LED_OFF);
		tinyLED_set_color(INN_LED, LED_OFF);
	}
}

void tinyPulse_set_pulse_mode(_Bool mode){
	if (pulse_mode != mode)
	{
		tinyPulse_toggle_pulse_mode();
	}
}

double tinyPulse_update_potential(double potential){
	if(pulse_mode){
		
		time_since_last_pulse = tinyTime_now() - time_of_last_pulse;
		
		if(time_since_last_pulse >= ideal_time_between_pulses){
			// This isn't actually a button press. You could have a separate variable for this, but it seems unnecessary.
			potential += BUTTON_PRESS_REACTION;
			time_of_last_pulse = tinyTime_now();			
		}
	}
	return potential;
}
