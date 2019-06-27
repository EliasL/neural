/*
 * Potential_to_RGB.c
 *
 * Created: 18.06.2018 19:48:15
 *  Author: Bendik Bogfjellmo
 */ 

#include <atmel_start.h>
#include <math.h>
#include "tinyCCLRGB/tinyCCLRGB.h"
#include <stdbool.h>
#include "ISR_timer_counter/ISR_timer_counter.h"


#define number_of_leds 6
#define max_brightness  0x30
#define fire_flash_time 100


uint32_t fire_flash_time_counter = 0;


/*
Potential to RGB, spec requirements:
At resting potential middle light should be white. Lets say rest potential => |potential| < 1, as the potential is really precise as it is a double precision floating point.
With positive potential the upper light should be green.(Lets linearly increase this with |potential|)
With negative potential the lower light should be red.(Lets linearly increase this with |potential|)
When firing all lights turn blue for ~100ms, but this needs to be tested.
LEDs are numbered right way on top of PCB, but opposite way on bottom of PCB.
*/
static void potential_to_RGB_set_color(double potential)
{
	for (int i = 0; i < number_of_leds; i++)
	{
		tinyCCLRGB_setColor(i, 0x0, 0x0, 0x0);//Clear all LED stored values on the MCU before writing again.
	}
	double absolute_potential = abs(potential);//setting variable for absolute potential so it won't have to be calculated more than once.
	if (absolute_potential < 1)//set the middle lights as white both top side and bottom side.
	{
		tinyCCLRGB_setColor(2, max_brightness/3, max_brightness/3, max_brightness/3);
		//tinyCCLRGB_setColor(4, max_brightness/3, max_brightness/3, max_brightness/3);
	}
	else
	{
		uint8_t brightness_intensity = round((absolute_potential/25)*max_brightness);//brightness intensity for the LED that shows potential.
		if (potential < 0)
		{
			tinyCCLRGB_setColor(0, brightness_intensity, 0x0, 0x0);
			tinyCCLRGB_setColor(1, brightness_intensity, 0x0, 0x0);//sets lower LEDs red if potential is negative.
		} 
		else
		{
			tinyCCLRGB_setColor(3, 0x0, brightness_intensity, 0x0);//sets upper LEDs green if potential is positive.
			tinyCCLRGB_setColor(4, 0x0, brightness_intensity, 0x0);
		}
	}
}



//function to be called upon when firing flag has been raised.
void set_LED_fire(void)
{
	fire_flash_time_counter = ISR_timer_count();
	for (int i = 0; i < number_of_leds; i++)
	{
		tinyCCLRGB_setColor(i, max_brightness, max_brightness, max_brightness);//As per the specs, all LEDs should be blue while firing.
	}
}



void potential_to_RGB_update_LEDs(double potential)
{
	if ((ISR_timer_count() - fire_flash_time_counter) < fire_flash_time)
	{
		for (int i = 0; i < number_of_leds; i++)
		{
			tinyCCLRGB_setColor(i, max_brightness, max_brightness, max_brightness);
		}
	}
	else
	{
		potential_to_RGB_set_color(potential);
	}
	tinyCCLRGB_uploadColorsToLeds();
}
