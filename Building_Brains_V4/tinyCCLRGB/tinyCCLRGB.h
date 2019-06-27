/*
 * tinyCCLRGB
 * This is a general purpose library for controlling WS2812 LEDs with the ATtiny817 (or any ATtiny 1-series MCU with matching peripherals)
 * Created: 15.06.2018 16:20:30
 *  Author: Bendik Bogfjellmo
 */ 


#ifndef TINYCCLRGB_H_
#define TINYCCLRGB_H_

void tinyCCLRGB_uploadColorsToLeds(void);
void tinyCCLRGB_setColor(uint8_t led, uint8_t red, uint8_t green, uint8_t blue);


struct tinyCCLRGB_color
{
	uint8_t red;
	uint8_t green;
	uint8_t blue;
};



#endif /* RGBLIB_H_ */