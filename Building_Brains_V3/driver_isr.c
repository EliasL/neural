
#include <driver_init.h>
#include <compiler.h>
#include <stdbool.h>
#include "tiny_timed_ISR/tiny_timed_ISR.h"
#include "ISR_timer_counter/ISR_timer_counter.h"


/*
ISR(RTC_CNT_vect)
{
	tiny_timed_ISR_setflag(true);
	
	
	
	//timer counter incrementation.
	ISR_timer_counter_increment();


	Overflow interrupt flag has to be cleared manually
	RTC.INTFLAGS = RTC_OVF_bm;
}
*/