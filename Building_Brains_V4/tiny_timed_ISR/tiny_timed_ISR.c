
#include <driver_init.h>
#include <compiler.h>
#include <stdbool.h>
#include "tiny_timed_ISR/tiny_timed_ISR.h"
#include "ISR_timer_counter/ISR_timer_counter.h"


/*
This function is called every time the RTC (Real Time Clock) counter overflows. 
The RTC clock runs at 1kHz, and the number of cycles before overflow is set with RTC.PER = someHexValue (e.g. 0x20)
*/

ISR(RTC_CNT_vect)
{
	tiny_timed_ISR_setflag(true);
	
	/*
	In case of too little time to process the code between interrupts, we use the ISR (Interrupt Service Routine) to set an external flag
	so that the MCU (Micro Controller Unit) can return to normal function relatively fast after an interrupt.
	The main loop will catch up on the external flag and the external flag will remain high
	until the CPU/peripherals has completed its tasks
	*/
	
	//timer counter incrementation.
	ISR_timer_counter_increment();


	/* Overflow interrupt flag has to be cleared manually */
	RTC.INTFLAGS = RTC_OVF_bm;
}


static _Bool tiny_timed_ISR_interruptflag = false;






void tiny_timed_ISR_setflag(_Bool new_flag_val)
{
	tiny_timed_ISR_interruptflag = new_flag_val;
}

_Bool tiny_timed_ISR_getflag(void)
{
	return tiny_timed_ISR_interruptflag;
}



