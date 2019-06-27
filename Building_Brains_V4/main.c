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
	VREF.CTRLA = 0x33;//sets reference voltage to 4.32 Volts. This is done to ensure relatively low interference from
	//nearby induced magnetic fields from high voltage AC-signals, such as outlets or transformers.
	uint32_t this_update_time = 1;
	uint32_t previous_update_time = 0;
	tiny_DAC_set_neur_type(false);
	while (1)
	{
		if(tiny_timed_ISR_getflag())
		{
			this_update_time = ISR_timer_count();
			tiny_potential_master_update(this_update_time - previous_update_time);
			previous_update_time = this_update_time;
			tiny_timed_ISR_setflag(false);
		 }
	}
}

