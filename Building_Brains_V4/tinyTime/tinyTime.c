/*
 * tinyTime.c
 *
 * Created: 19.06.2018 13:39:52
 * Authors: Bendik Bogfjellmo, Elias Lundheim
 */ 
 #include <stdint.h>
 #include <atmel_start.h>

/*
ISR will periodically interrupt with a period of ~1ms
*/

//timer_counter
uint32_t time_counter = 0; // Will overflow after 49 days.

/*
This function increments the time counter.
When applied in a timed Interrupt Service Routine
it will increment each time the Interrupt service routine is called.
If the Interrupt Service Routine is clocked by a crystal oscillator
it gives a very precise timer-counter.
*/
void tinyTime_counter_increment(void)
{
	time_counter++;
}


/*
This function is callable by external libraries to give them the counted time so far.
*/
uint32_t tinyTime_now(void)
{
	return time_counter;
}