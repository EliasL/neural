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
	return charging;
}

void tinyCharge_set_charging(_Bool charging_status){
	charging = charging_status;
	ChargeMode_set_level(false); // We want the pin low for charging
}