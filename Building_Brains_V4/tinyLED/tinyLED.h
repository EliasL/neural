/*
 * tinyLED
 * This is a general purpose library for controlling WS2812 LEDs with the ATtiny817 (or any ATtiny 1-series MCU with matching peripherals)
 * Created: 15.06.2018 16:20:30
 * Authors: Bendik Bogfjellmo, Elias Lundheim
 */ 


#ifndef tinyLED_H_
#define tinyLED_H_


enum Colors{
	OFF, RED, BLUE, GREEN, WHITE
};

enum ColorModes
{
	STABLE, FLASH, SWING
};

void tinyLED_update(void);
void tinyLED_set_color(uint8_t LED_id, enum Colors color);
void tinyLED_set_color_mode(uint8_t LED_id, enum Colors color, enum ColorModes mode);
	


#endif /* RGBLIB_H_ */