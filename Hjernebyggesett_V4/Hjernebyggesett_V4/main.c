#include <atmel_start.h>
#include <stdbool.h>
#include <math.h>
#include "tinyDendrite/tinyDendrite.h"
#include "tinyAxon/tinyAxon.h"
#include "tinyPotential/tinyPotential.h"
#include "tinyISR/tinyISR.h"
#include "tinyTime/tinyTime.h"
#include "tinyButton/tinyButton.h"
#include "tinyCharge/tinyCharge.h"
#include "settings.h"
#include "tinyDebugger/tinyDebugger.h"
#include "tinyLED/tinyLED.h"

/*
Notes for future development

If you ever need to re-create or re-configure the project with the atmel start thing, and you overwrite all the files
you need to comment out, or remove the code in driver_isr.c in order to avoid creating multiple definitions of __vector_6

The user labels for the dendrites (DENn_PIN) are shortened from DENDRITEn_PIN. Having the longer name resulted in a segmentation error,
probably due to a lac of memory in the MC (Micro Chip). Keep this in mind if you get a segmentation error. 

*/


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
	
	VREF.CTRLA |= VREF_DAC0REFSEL_4V34_gc;
	while (1)
	{
		// We don't want to update the neuron too often because of various reasons. The tinyISR_getflag is set every ms, and so the loop is only run once every ms.  
		if(tinyISR_getflag())
		{
			
			if(tinyCharge_is_connected_to_charger()){
				// Charge loop
				
				if(tinyCharge_is_fully_charged()){
					tinyLED_set_color(INN_LED, CHARGING_DONE_COLOR);
					tinyLED_set_color(OUT_LED, OFF)
				}				
				// We check the Dendrites in order to detect if we have stopped charging
				tinyDendrite_update_signals();
				
			}
			else{
				// Main loop			
				
				// Set LED
				if(tinyLED_get_color(OUT_LED) == OFF && PING_COLOR != OFF){
					tinyLED_set_color_mode(OUT_LED, PING_COLOR, PING);
				}
				
				// Update button	
				tinyButton_update();
				
				// Update the potential (This is where most of the important stuff happens)
				tinyPotential_update();
			}
			// Update LED
			tinyLED_update();
				
			// Switch transistors
			tinyCharge_set_transistors();
			
			// Prepare for next cycle
			tinyISR_setflag(false);
			tinyDebugger_send_uint32("time", tinyTime_now());
			tinyDebugger_end_line();
			
		 }
	}
}

