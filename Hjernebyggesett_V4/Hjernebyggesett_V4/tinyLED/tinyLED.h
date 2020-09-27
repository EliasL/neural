/*
 * tinyLED
 * This is a general purpose library for controlling WS2812 LEDs with the ATtiny817 (or any ATtiny 1-series MCU with matching peripherals)
 * Created: 15.06.2018 16:20:30
 * Authors: Bendik Bogfjellmo, Elias Lundheim
 */ 


#ifndef tinyLED_H_
#define tinyLED_H_


enum Colors{
	LED_OFF, RED, BLUE, GREEN, YELLOW, WHITE
};

enum ColorModes
{
	STABLE, WEAK, FLASH, SWING, PING, FLASH_ONCE
};

void tinyLED_update(void);
void tinyLED_set_color(uint8_t LED_id, enum Colors color);
enum Colors tinyLED_get_color(uint8_t LED_id);
void tinyLED_set_color_mode(uint8_t LED_id, enum Colors color, enum ColorModes mode);
void tinyLED_queue_flash(uint8_t LED_id, enum Colors color);
	


#endif /* RGBLIB_H_ */