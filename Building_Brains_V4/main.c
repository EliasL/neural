#include <atmel_start.h>
#include <util/delay.h>
#include <stdbool.h>
#include <math.h>
#include "tinyCCLRGB/tinyCCLRGB.h"
#include "tiny_dendrites/tiny_ADC_dendrites.h"
#include "tiny_DAC_axon/tiny_DAC_axon.h"
#include "tiny_potential/tiny_potential.h"
#include "Potential_to_RGB/Potential_to_RGB.h"
#include "tiny_timed_ISR/tiny_timed_ISR.h"
#include "ISR_timer_counter/ISR_timer_counter.h"


int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	/*
	set reference voltage to 4.32 Volts. This is done to ensure relatively low interference from
	nearby induced magnetic fields from high voltage AC-signals, such as outlets or transformers.
	Setting this value will mean that the ADC (Analog to Digital Converter) will read 4.32v as 255, and 0v as 0.
	For some reason, instead of the reference voltage being 4.32v, it is 3.3v. 
	*/
	VREF.CTRLB = VREF_ADC0REFSEL_4V34_gc;
	
	
	uint32_t current_time = 1;
	uint32_t previous_cycle_time = 0;
	uint16_t time_passed_since_last_cycle = 0;
	uint16_t volatile cycles=0;
	tiny_DAC_set_neuron_type(EXCITATORY_NEURON);
	while (1)
	{
		if(tiny_timed_ISR_getflag())
		{
			current_time = ISR_timer_count();
			time_passed_since_last_cycle = current_time - previous_cycle_time;
			
			tiny_potential_master_update(time_passed_since_last_cycle);
			
			previous_cycle_time = current_time;
			tiny_timed_ISR_setflag(false);
			cycles++;
		 }
	}
}

