/*
 * rainbows.c
 *
 * Created: 18.06.2018 18:25:12
 *  Author: Bendik
 */ 
 #include <atmel_start.h>
 #include "tinyCCLRGB/tinyCCLRGB.h"
 #include <util/delay.h>
 #include "rainbows.h"
void rainbows()
{
	uint8_t red[6] = {0x20, 0x10, 0x0, 0x0, 0x0, 0x10};
	uint8_t green[6] = {0x0, 0x10, 0x20, 0x10, 0x0, 0x0};
	uint8_t blue[6] = {0x0, 0x0, 0x0, 0x10, 0x20, 0x10};
	while (1)
	{
		for (int i = 0; i < 6; i++)
		{
			uint8_t next = i+1;
			uint8_t prev = i-1;
			if(i == 0)
			{
				prev = 5;
			}
			if(i == 5)
			{
				next = 0;
			}
			if((red[i] == 0x20) && (red[prev] > 0))
			{
				red[next]++;
				red[prev]--;
			}
			if((green[i] == 0x20) && (green[prev] > 0))
			{
				green[next]++;
				green[prev]--;
			}
			if((blue[i] == 0x20) && (blue[prev] > 0))
			{
				blue[next]++;
				blue[prev]--;
			}
			tinyCCLRGB_setColor(next, red[next], green[next], blue[next]);
			tinyCCLRGB_setColor(prev, red[prev], green[prev], blue[prev]);
		}
		tinyCCLRGB_uploadColorsToLeds();
		_delay_ms(30);
	}
}