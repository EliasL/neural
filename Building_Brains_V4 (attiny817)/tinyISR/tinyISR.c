
#include <driver_init.h>
#include <compiler.h>
#include <stdbool.h>
#include "tinyISR/tinyISR.h"
#include "tinyTime/tinyTime.h"


/*
This function is called every time the RTC (Real Time Clock) counter overflows.
With the current settings, it will be called every ms.
The RTC clock runs at 1kHz, and the number of cycles before overflow is set with RTC.PER = someHexValue (e.g. 0x20) in src/rtc.c
*/
ISR(RTC_CNT_vect)
{
	// Set flag to let main loop run a new cycle
	tinyISR_setflag(true);
	
	// Timer counter incrementation
	tinyTime_counter_increment();

	/* Overflow interrupt flag has to be cleared manually */
	RTC.INTFLAGS = RTC_OVF_bm;
}


static _Bool tinyISR_interrupt_flag = false;


void tinyISR_setflag(_Bool new_flag_val)
{
	tinyISR_interrupt_flag = new_flag_val;
}

_Bool tinyISR_getflag(void)
{
	return tinyISR_interrupt_flag;
}



