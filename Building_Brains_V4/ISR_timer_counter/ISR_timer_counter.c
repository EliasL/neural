/*
 * ISR_timer_counter.c
 *
 * Created: 19.06.2018 13:39:52
 *  Author: Bendik Bogfjellmo
 */ 
 #include <stdint.h>
 #include <atmel_start.h>

/*
ISR will periodically interrupt with a period of ~1ms
This library only contains one counter at the moment
but I will probably have to implement a couple of more timers
so that we're able to time all the functionalities that will have to
be timed in parallel.
*/


//timer_counter initialization.
static uint32_t timer_counter_integer = 0; //Will overflow after 49 days. Is that a problem?

/*
This function increments the timer.
When applied in a timed Interrupt Service Routine
it will increment each time the Interrupt service routine is called.
If the Interrupt Service Routine is clocked by a crystal oscillator
it gives a very precise timer-counter.
*/
void ISR_timer_counter_increment(void)
{
	timer_counter_integer++;
}


/*
This function is callable by external libraries to give them the counted time so far.
*/
uint32_t ISR_timer_count(void)
{
	return timer_counter_integer;
}