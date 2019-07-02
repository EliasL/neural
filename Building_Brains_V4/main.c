#include <atmel_start.h>
#include <util/delay.h>
#include <stdbool.h>
#include <math.h>
#include "tinyCCLRGB/tinyCCLRGB.h"
#include "tinyDendrite/tinyDendrite.h"
#include "tinyAxon/tinyAxon.h"
#include "tinyPotential/tinyPotential.h"
#include "Potential_to_RGB/Potential_to_RGB.h"
#include "tinyISR/tinyISR.h"
#include "tinyTime/tinyTime.h"
#include "tinyButton/tinyButton.h"
#include "settings.h"


int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	/*
	set reference voltage to 4.32 Volts. This is done to ensure relatively low interference from
	nearby induced magnetic fields from high voltage AC-signals, such as outlets or transformers.
	Setting this value will mean that the ADC (Analog to Digital Converter) will read 4.32v as 255, and 0v as 0.
	For some reason, instead of the reference voltage being 4.32v, it is 3.3v. 
	A plausible explanation is that the microchip does not up the voltage, so that if the microchip is only ever 
	supplied with 3.3v, it will output 3.3v as the max.
	*/
	VREF.CTRLB = VREF_ADC0REFSEL_4V34_gc;
	
	
	uint32_t current_cycle_time = 1;
	uint32_t previous_cycle_time = 0;
	uint16_t time_passed = 0;
	uint16_t volatile cycles=0;
	
	tinyDendrite_set_neuron_type(NEURONTYPE);
	
	while (1)
	{
		if(tinyISR_getflag())
		{
			current_cycle_time = tinyTime_now();
			
			
			
			tinyButton_update();
			
			time_passed = current_cycle_time - previous_cycle_time;
			tinyPotential_update(time_passed);
			
			
			
			previous_cycle_time = current_cycle_time;
			cycles++;
			tinyISR_setflag(false);
		 }
	}
}

