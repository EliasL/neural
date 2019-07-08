/*
 * tinyCharge.c
 *
 * Created: 02.07.2019 14:49:13
 * Author: Elias Lundheim
 */ 

#include <stdbool.h>
#include <atmel_start.h>

_Bool charging;

_Bool tinyCharge_is_charging(){
	return false;
	//return charging;
}

void tinyCharge_set_charging(_Bool charging_status){
	charging = charging_status;
}


void tinyCharge_set_transistors(){
	if(charging){
		// ChargeMode is the pin that goes to the two large transistors on the neuron.
		CHARGING_SWITCHES_PIN_set_level(false); // We want the pin low for charging
	}
	else {
		CHARGING_SWITCHES_PIN_set_level(true);
	}
}
