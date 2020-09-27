/*
 * tinyLED.c
 *
 * Created: 15.06.2018 16:20:11
 * Authors: Bendik Bogfjellmo, Elias Lundheim
 */ 

#include <atmel_start.h>
#include <util/delay.h>
#include <stdio.h>
#include <math.h>
#include "tinyLED.h"
#include "settings.h"
#include "tinyTime/tinyTime.h"
#include "tinyDebugger/tinyDebugger.h"

/*

tinyLED

This script lets you not only set the color of a led, but it also lets
you set the mode of a led, to for example a sin curve. In order to do this, we store
the color and mode of the LEDs in one array, and then the actual value of
the LEDs at at given time in a different array.

*/

struct RGB_Color
{
	uint8_t red;
	uint8_t green;
	uint8_t blue;
};


struct ColorSetting
{
	enum Colors color;
	enum ColorModes mode;
};

// list containing the current values for each led
struct ColorSetting tinyLED_settings[NUMBER_OF_LEDS];
struct ColorSetting tinyLED_old_settings[NUMBER_OF_LEDS];
struct RGB_Color tinyLED_old_colors[NUMBER_OF_LEDS];
uint16_t tinyLED_flash_once_time[NUMBER_OF_LEDS];


// Sometimes, if the neuron receives multiple signals on the same update,
// the neuron might receive 5 inhibitory signals, but then one exitory signal at the end.
// That will cause the neuron to signal that it received an exitory signal, but not fire.
// This can be confusing, and should be avoided.

// In order to avoid this, FLASH_ONCE lights will be queued rather than set, thus giving each light signal a minimum time to be displayed.
uint8_t flash_queue[16];      // a list of colors that should be flashed
uint8_t flash_queue_ids[16];  // we also need to keep track of what LED should flash
uint8_t flashes_in_queue = 0; // variable to determine how many flashes are in queue.

/*
adds a color to the flash queue
*/
void tinyLED_queue_flash(uint8_t LED_id, enum Colors color)
{
	// We ignore a request to queue a flash if the queue is full
	if(flashes_in_queue < 16){
		flash_queue[flashes_in_queue] = color;
		flash_queue_ids[flashes_in_queue] = LED_id;
		flashes_in_queue++;
	}
}

/*
changes the values in the variables stored in the LED-array.
*/
void tinyLED_set_color(uint8_t LED_id, enum Colors color)
{
	tinyLED_set_color_mode(LED_id, color, STABLE);
}

enum Colors tinyLED_get_color(uint8_t LED_id)
{
	return tinyLED_settings[LED_id].color;
}

/*
changes the values in the variables stored in the LED-array.
*/
void tinyLED_set_color_mode(uint8_t LED_id, enum Colors color, enum ColorModes mode)
{
	// If we are in pulse mode, we want to stay in pulse mode after we have flashed a light.
	// We do this by storing the previous mode in old settings.
	// However, it can happen that two flashes comes very quickly after one another, that leads
	// to an infinite flash loop, therefore, we only store the settings if it is not flash mode.
	if(tinyLED_settings[LED_id].mode != FLASH_ONCE){
		// We use two lines to avoid pointer trouble. (I'm not good with pointers)
		tinyLED_old_settings[LED_id].color = tinyLED_settings[LED_id].color;
		tinyLED_old_settings[LED_id].mode = tinyLED_settings[LED_id].mode;
	}
	
	struct ColorSetting new_setting = {.color=color, .mode=mode};
	tinyLED_settings[LED_id] = new_setting;
	if (mode == FLASH_ONCE)
	{
		// If there is only one flash in the queue, we can let it flash longer
		if(flashes_in_queue>1){
			tinyLED_flash_once_time[LED_id] = 1000*QUEUE_FLASH_TIME;
		}
		else{
			tinyLED_flash_once_time[LED_id] = 1000*FLASH_TIME;
		}
	}
}

/*
Function used to send a byte over SPI, which in turn gets
translated to the bit-sequence required by the LEDs over the CCL.
*/
static void tinyLED_SPIWriteByte(uint8_t byte)
{
	SPI0.INTFLAGS = SPI0_INTFLAGS; // clear the write collision flag to allow writing
	TCA0.SINGLE.CNT = 0; // reset TCA counter register to ensure the first rising edge of the PWM is predictable
	
	// start TCA
	TCA0.SINGLE.CTRLA = TCA_SPLIT_CLKSEL_DIV1_gc | 1 << TCA_SPLIT_ENABLE_bp;
	SPI0_DATA = byte;

	while((SPI0.INTFLAGS & SPI_RXCIE_bm) == 0){} // wait for transfer to complete
	TCA0.SINGLE.CTRLA = TCA_SPLIT_CLKSEL_DIV1_gc | 0 << TCA_SPLIT_ENABLE_bp; //Stop TCA
}

static struct RGB_Color tinyLED_enum_to_RGB_Color(enum Colors color){
	struct RGB_Color rgb_color;
	switch(color)
	{
		case LED_OFF:
			rgb_color = (struct RGB_Color){0, 0, 0};
			break;
		case RED:
			rgb_color = (struct RGB_Color){255*LED_BRIGHTNESS, 0, 0};
			break;
		case GREEN:
			rgb_color = (struct RGB_Color){0, 255*LED_BRIGHTNESS, 0};
			break;
		case BLUE:
			rgb_color = (struct RGB_Color){0, 0, 255*LED_BRIGHTNESS};
			break;
		case YELLOW:
			rgb_color = (struct RGB_Color){255*LED_BRIGHTNESS, 255*LED_BRIGHTNESS, 0};
			break;
		case WHITE:
			// Should the /3 be there? This requires testing.
			// After testing, findings were that at 0.1 brightness, one would see the three LEDs instead of one white led
			// We try with /2 instead.
			// We find that the best results come from not dividing by anything. At leasts in the lower brightness settings, and that
			// is where we suspect it will be most of the time. When we divide, the LEDs are so weak, that they appear as three lights instead of one.
			rgb_color = (struct RGB_Color){255*LED_BRIGHTNESS, 255*LED_BRIGHTNESS, 255*LED_BRIGHTNESS};
			break;
		default:
			rgb_color = (struct RGB_Color){0, 0, 0};
			break;
	}
	return rgb_color;
			
};
// This might be cause of strange light behavior?
//Message		expected 'struct RGB_Color *' but argument is of type 'struct RGB_Color (*)[2]'	Hjernebyggesett_V4	C:\Users\Elias Lundheim\Documents\GitHub\neural\Hjernebyggesett_V4\Hjernebyggesett_V4\tinyLED\tinyLED.c	121
_Bool tinyLED_RGB_Color_Compare(struct RGB_Color (*a)[NUMBER_OF_LEDS], struct RGB_Color (*b)[NUMBER_OF_LEDS]){
	for (int i=0; i<NUMBER_OF_LEDS; i++)
	{
		if(!((*a)[i].red==(*b)[i].red && (*a)[i].green==(*b)[i].green && (*a)[i].blue==(*b)[i].blue)){
			return false;
		}
	}
	return true;
}

/*
function to write the current LED-array on to the LEDs and
effectively update the values stored in the LEDs to the values stored in the MCU.
*/
void tinyLED_update(void)
{
			
	uint32_t now = tinyTime_now();	
	
	// This is a sin curve, but between 0 and 1 instead of -1 and 1
	double sinValue = 0.5+sin((double)now/(100*M_PI/SWING_RATE))/2;
	
	// If FLASH_RATE is one, then that means that the left side of the "<" will just count from 0 to 1000, and flash_on will be true for half of the time
	_Bool flash_on = now%(uint32_t)(1000/FLASH_RATE)  <   500/FLASH_RATE;
	
	// PING_RATE is usually small, so the left side counts to some large number. Since flash_time usually is also quite small,
	// the left side will usually be larger than the right
	_Bool ping_on =  now%(uint32_t)(1000/PING_RATE)   <   1000*FLASH_TIME;
	
	// This is where we store all the actual color values we want to send to the LED
	struct RGB_Color rgb_colors[NUMBER_OF_LEDS];
	
		
	for (uint8_t i = 0; i < NUMBER_OF_LEDS; i++)
	{		
		// Convert enum to RGB_Color
		rgb_colors[i] = tinyLED_enum_to_RGB_Color(tinyLED_settings[i].color);
		
		// Check if there is a flash that can be queued
		// Complicated code (bad code): The best implementation would be to have a separate flash queue for each
		// LED, but I can't be bothered to deal with nested arrays. So we check a couple of things
		// It should work well so long as two LEDs aren't being queued to at the same time. If that does happen, 
		// nothing should break, but it will be slower to get the flashes out.
		if (flashes_in_queue>0 && tinyLED_settings[i].mode !=FLASH_ONCE && flash_queue_ids[flashes_in_queue] == i)
		{
			// This implementation is easier, but it means that the last flash into the queue is the first out.
			tinyLED_set_color_mode(flash_queue_ids[flashes_in_queue], flash_queue[flashes_in_queue], FLASH_ONCE);
			flashes_in_queue--;
		}
		
		// Adjust colors according to mode
		switch(tinyLED_settings[i].mode)
		{
			case STABLE:
				break;
			case WEAK:
				rgb_colors[i] = (struct RGB_Color){rgb_colors[i].red*WEAK_BRIGHTNESS, rgb_colors[i].green*WEAK_BRIGHTNESS, rgb_colors[i].blue*WEAK_BRIGHTNESS};
				break;
			case FLASH:
				rgb_colors[i] = (struct RGB_Color){rgb_colors[i].red*flash_on, rgb_colors[i].green*flash_on, rgb_colors[i].blue*flash_on};
				break;
			case SWING:
				rgb_colors[i] = (struct RGB_Color){rgb_colors[i].red*sinValue, rgb_colors[i].green*sinValue, rgb_colors[i].blue*sinValue};
				break;
			case PING:
				// in the line below, fmin will either return 1 or 0, so each rgb color is either 0 or 255*PING_BRIGHTNESS
				rgb_colors[i] = (struct RGB_Color){255*PING_BRIGHTNESS*fmin(1,rgb_colors[i].red)*ping_on, 255*PING_BRIGHTNESS*fmin(1,rgb_colors[i].green)*ping_on, 255*PING_BRIGHTNESS*fmin(1,rgb_colors[i].blue)*ping_on};
				break;
			case FLASH_ONCE:
				if(tinyLED_flash_once_time[i]>0){
					rgb_colors[i] = (struct RGB_Color){rgb_colors[i].red, rgb_colors[i].green, rgb_colors[i].blue};
					tinyLED_flash_once_time[i]--;
				}
				else{
					// Here we return to the previous color and mode
					tinyLED_settings[i].color = tinyLED_old_settings[i].color;
					tinyLED_settings[i].mode = tinyLED_old_settings[i].mode;
				}
				break;
			default:
				break;
		}
	}
	
	// We only write to the LEDs if there is something to change. (eg. in SWING mode, we update the LEDs almost every cycle)
	if(!tinyLED_RGB_Color_Compare(&rgb_colors, &tinyLED_old_colors)){
		for (uint8_t i = 0; i < NUMBER_OF_LEDS; i++)
		{
			// Write to LEDs
			//For some reason, the data-bus to the LEDs is serialized as GRB
			//which means the 24-bit data-bus will look like [Green[0:7], Red[0:7], Blue[0:7]]
			tinyLED_SPIWriteByte(rgb_colors[i].green);
			tinyLED_SPIWriteByte(rgb_colors[i].red);
			tinyLED_SPIWriteByte(rgb_colors[i].blue);
			tinyLED_old_colors[i] = rgb_colors[i];
		}
	}
}



