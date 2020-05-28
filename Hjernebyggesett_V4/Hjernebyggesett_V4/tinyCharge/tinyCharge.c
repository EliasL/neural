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
#include "tinyDebugger/tinyDebugger.h"
#include "tinyAxon/tinyAxon.h"
#include "tinyDendrite/tinyDendrite.h"

_Bool connected_to_charger;

_Bool tinyCharge_is_connected_to_charger(){
	return connected_to_charger;
}

_Bool tinyCharge_is_fully_charged(){
	return CHARGING_STATUS_PIN_get_level();
}


void tinyCharge_DAC_dissable(){
	
	// We need some way to disable the DAC to prevent huge current draw when charging (64mA). When there is no code uploaded to the attiny, there is no problem.
	// We're going to try to enable the pin as a dendrite, since they seem to be doing fine. Completely uninitializing the pin probably caused a microchip to be fried.
	
	DAC_0_uninit();
	DAC_0_disable();
	
}

void tinyCharge_DAC_enable(){
	
	// We need some way to disable the DAC to prevent huge current draw when charging (64mA). When there is no code uploaded to the attiny, there is no problem.
	// We're going to try to enable the pin as a dendrite, since they seem to be doing fine. Completely uninitializing the pin probably caused a microchip to be fried.
	
	DAC_0_init();
	DAC_0_enable();
}

/*
Checks if the levels of the dendrites and axon are at charging levels
and updates the mode accordingly
*/
void tinyCharge_update_charging_mode(){
	_Bool charge = tinyAxon_check_charge_level() || tinyDendrite_check_charge_level();
	tinyCharge_set_charging_mode(charge);
}


void tinyCharge_switch_mode(){
	
	if(connected_to_charger){
		// Switch from main to charging mode
		
		// Set LED
		tinyLED_set_color_mode(OUT_LED, CHARGING_COLOR, SWING);
		tinyLED_set_color(INN_LED, OFF);


		// Stop axon from firing
		// (There is a small chance that the neuron is put into charging mode as it is firing. The axon is then never told to stop firing)
		tinyAxon_stop_sending_pulse();

		// disable DAC
		tinyCharge_DAC_dissable();
		
	}
	else{
		// Switch from charge to main mode
		
		// Set LED
		tinyLED_set_color(OUT_LED, OFF);
		tinyLED_set_color(INN_LED, OFF);
		
		// enable DAC
		tinyCharge_DAC_enable();
	}
}

void tinyCharge_set_charging_mode(_Bool charging_status){
	if(charging_status != connected_to_charger){
		connected_to_charger = charging_status;
		tinyCharge_switch_mode();
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


//Thinks it's charging when axon fires