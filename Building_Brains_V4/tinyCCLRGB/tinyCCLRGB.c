/*
 * tinyCCLRGB.c
 *
 * Created: 15.06.2018 16:20:11
 *  Author: Bendik Bogfjellmo
 */ 

#include <atmel_start.h>
#include <util/delay.h>
#include "tinyCCLRGB.h"


//Initiating constants and allocating memory for color-variables.
#define TINYCCLRGB_LEDCOUNT 6
static struct tinyCCLRGB_color tinyCCLRGB_colors[TINYCCLRGB_LEDCOUNT];


/*
changes the values in the variables stored in the led-array.
*/
void tinyCCLRGB_setColor(uint8_t led, uint8_t red, uint8_t green, uint8_t blue) 
{
	tinyCCLRGB_colors[led].red = red;
	tinyCCLRGB_colors[led].green = green;
	tinyCCLRGB_colors[led].blue = blue;
}

//setting default values for the pins in the array.

/*
Function used to send a byte over SPI, which in turn gets
translated to the bit-sequence required by the LEDs over the CCL.
*/
static void tinyCCLRGB_SPIWriteByte(uint8_t byte)
{
	SPI0.INTFLAGS = SPI0_INTFLAGS; // clear the write collision flag to allow writing
	TCA0.SINGLE.CNT = 0; // reset TCA counter register to ensure the first rising edge of the PWM is predictable
	
	// start TCA
	TCA0.SINGLE.CTRLA = TCA_SPLIT_CLKSEL_DIV1_gc | 1 << TCA_SPLIT_ENABLE_bp;
	SPI0_DATA = byte;

	while((SPI0.INTFLAGS & SPI_RXCIE_bm) == 0){} // wait for transfer to complete
	TCA0.SINGLE.CTRLA = TCA_SPLIT_CLKSEL_DIV1_gc | 0 << TCA_SPLIT_ENABLE_bp; //Stop TCA
}

/*
function to write the current LED-array on to the LEDs and
effectively update the values stored in the LEDs to the values stored in the MCU.
*/
void tinyCCLRGB_uploadColorsToLeds(void)
{
	for (uint8_t i = 0; i < TINYCCLRGB_LEDCOUNT; i++)
	{
		//For some reason unknown to the writer the data-bus to the LEDs is serialized as GRB
		//which means the 24-bit data-bus will look like [Green[0:7], Red[0:7], Blue[0:7]]
		tinyCCLRGB_SPIWriteByte(tinyCCLRGB_colors[i].green);
		tinyCCLRGB_SPIWriteByte(tinyCCLRGB_colors[i].red);
		tinyCCLRGB_SPIWriteByte(tinyCCLRGB_colors[i].blue);
	}
}

