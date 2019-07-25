/*
 * tinyCharge.c
 *
 * Created: 02.07.2019 14:49:13
 * Author: Elias Lundheim
 */ 

#include <stdbool.h>
#include <atmel_start.h>
#include "settings.h"
#include "tinyLED/tinyLED.h"

_Bool connected_to_charger;

_Bool tinyCharge_is_connected_to_charger(){
	return connected_to_charger;
}

_Bool tinyCharge_is_fully_charged(){
	return CHARGING_STATUS_PIN_get_level();
}

void tinyCharge_set_charging_mode(_Bool charging_status){
	if(charging_status != connected_to_charger){
		connected_to_charger = charging_status;
		tinyCharge_switch_mode();
	}
}

void tinyCharge_switch_mode(){
	
	if(connected_to_charger){
		// Switch from main to charging mode
		
		// Set LED
		tinyLED_set_color(OUT_LED, OFF);
		tinyLED_set_color_mode(INN_LED, CHARGING_COLOR, SWING);
	}
	else{
		// Switch from charge to main mode
		
		// Set LED
		tinyLED_set_color(OUT_LED, OFF);
		tinyLED_set_color(INN_LED, OFF);
	}
}


void tinyCharge_set_transistors(){
	if(connected_to_charger){
		// ChargeMode is the pin that goes to the two large transistors on the neuron.
		CHARGING_SWITCHES_PIN_set_level(false); // We want the pin low for charging
	}
	else {
		CHARGING_SWITCHES_PIN_set_level(true);
	}
}
