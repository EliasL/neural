/*
 * tinyLED.c
 *
 * Created: 15.06.2018 16:20:11
 * Authors: Bendik Bogfjellmo, Elias Lundheim
 */ 

#include <atmel_start.h>
#include <util/delay.h>
#include <math.h>
#include "tinyLED.h"
#include "settings.h"

/*

tinyLED

This script lets you not only set the color of a led, but it also lets
you set the mode of a led to a sin curve. In order to do this, we store
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
struct ColorSetting tinyLED_colors[NUMBER_OF_LEDS];

/*
changes the values in the variables stored in the LED-array.
*/
void tinyLED_set_color(uint8_t LED_id, enum Colors color)
{
	tinyLED_set_color_mode(LED_id, color, STABLE);
}
/*
changes the values in the variables stored in the LED-array.
*/
void tinyLED_set_color_mode(uint8_t LED_id, enum Colors color, enum ColorModes mode)
{
	struct ColorSetting setting = {.color=color, .mode=mode};
	tinyLED_colors[LED_id] = setting;
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
	RGB_Color rgb_color;
	switch(color)
	{
		case OFF:
			rgb_color = (RGB_Color){0, 0, 0};
			break;
		case RED:
			rgb_color = (RGB_Color){255*LED_BRIGHTNESS, 0, 0};
			break;
		case GREEN:
			rgb_color = (RGB_Color){0, 255*LED_BRIGHTNESS, 0};
			break;
		case BLUE:
			rgb_color = (RGB_Color){0, 0, 255*LED_BRIGHTNESS};
			break;
		case WHITE:
			// Should the /3 be there? This requires testing
			rgb_color = (RGB_Color){255/3*LED_BRIGHTNESS, 255/3*LED_BRIGHTNESS, 255/3*LED_BRIGHTNESS};
			break;
		default:
			rgb_color = (RGB_Color){0, 0, 0};
				break;
	}
	return rgb_color;
			
};

/*
function to write the current LED-array on to the LEDs and
effectively update the values stored in the LEDs to the values stored in the MCU.
*/
void tinyLED_update(void)
{
	uint32_t now = tinyTime_now();
	float sinValue = fabs(sin(now/(1000*2*M_PI*SWING_RATE)))/2;
	_Bool flash_on = now%(1000/FLASH_RATE)>500/FLASH_RATE;
	
	
	
	RGB_Color rgb_color;
	
	for (uint8_t i = 0; i < NUMBER_OF_LEDS; i++)
	{
		
		rgb_color = tinyLED_enum_to_RGB_Color(tinyLED_colors[i].color);
		
		switch(tinyLED_colors[i].mode)
		{
			case STABLE:
				break;
			case FLASH:
				rgb_color = (RGB_Color){rgb_color.red*flash_on, rgb_color.green*flash_on, rgb_color.blue*flash_on};
				break;
			case SWING:
				rgb_color = (RGB_Color){rgb_color.red*sinValue, rgb_color.green*sinValue, rgb_color.blue*sinValue};
				break;
			default:
				break;
		}
		return rgb_color;
		
		//For some reason unknown to the writer the data-bus to the LEDs is serialized as GRB
		//which means the 24-bit data-bus will look like [Green[0:7], Red[0:7], Blue[0:7]]
		tinyLED_SPIWriteByte(rgb_color.green);
		tinyLED_SPIWriteByte(rgb_color.red);
		tinyLED_SPIWriteByte(rgb_color.blue);
	}
}



