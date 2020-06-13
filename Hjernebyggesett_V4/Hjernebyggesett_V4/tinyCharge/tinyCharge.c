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
#include "tinyPulse/tinyPulse.h"

_Bool connected_to_charger;

/*
The charge_counter keeps track of how many cycles the neuron has thought that it has been connected to a charger
To avoid the axon of the neuron activating the charge mode, we require several cycles of high signal levels in order
to switch to charging mode
*/
uint8_t charge_counter = 0; 

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


void tinyCharge_switch_mode(){
	
	if(connected_to_charger){
		// Switch from main to charging mode
		
		// Set LED
		tinyLED_set_color_mode(OUT_LED, CHARGING_COLOR, SWING);
		tinyLED_set_color(INN_LED, LED_OFF);


		// Stop axon from firing
		// (There is a small chance that the neuron is put into charging mode as it is firing. The axon is then never told to stop firing)
		tinyAxon_stop_sending_pulse();

		// disable DAC
		tinyCharge_DAC_dissable();
		
		// We also turn off pulse mode, because it's confusing if it suddenly comes on
		// after it has been charging
		tinyPulse_set_pulse_mode(false);
		
	}
	else{
		// Switch from charge to main mode
		
		// Set LED
		tinyLED_set_color(OUT_LED, LED_OFF);
		tinyLED_set_color(INN_LED, LED_OFF);
		
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

/*
Checks if the levels of the dendrites and axon are at charging levels
and updates the mode accordingly
*/
void tinyCharge_update_charging_mode(){
	// For complicated reasons, the axon_check_level will be high even when the charger is not connected
	// WHEN the neuron is in charging mode, hence we ignore the axon level when the neuron is in charging mode
	_Bool charging;
	if(connected_to_charger){
		charging = tinyDendrite_check_charge_level();
	} else{
		charging = tinyDendrite_check_charge_level() || tinyAxon_check_charge_level();
	}
	
	// In order to prevent the axon from stimulating itself, we only switch into charging mode when the conditions have been right for several cycles
	if(!connected_to_charger && charging){
		charge_counter++;
		if(charge_counter > CYCLES_REQUIRED_FOR_CHARGING_MODE_SWITCH){
			charge_counter = 0;
			tinyCharge_set_charging_mode(charging);
		}
	}
	else{
		tinyCharge_set_charging_mode(charging);
	}
}



void tinyCharge_set_transistors(){
	if(connected_to_charger){
		// ChargeMode is the pin that goes to the two large transistors on the neuron.
		CHARGING_SWITCHES_PIN_set_level(false); // We want the pin low for charging
		BATTERY_ISOLATION_PIN_set_level(true);
	}
	else {
		CHARGING_SWITCHES_PIN_set_level(true);
		BATTERY_ISOLATION_PIN_set_level(false);
	}
}


//Thinks it's charging when axon fires