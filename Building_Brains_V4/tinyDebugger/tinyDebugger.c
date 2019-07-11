/*
 * tinyDebugger.c
 *
 * Created: 04.07.2019 08:52:27
 * Author: Elias Lundheim
 */ 

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "tinyDebugger.h"
#include "settings.h"

/*
The idea is that throughout the project, we can prepare to send various variables, and label them appropriately.
Then, at the end of the main loop, we write them all to the pc via USART. 
Our python script (if running), will pick them up and plot the values in real time.
*/


// We use 10 as an arbitrary max, you could increase this if you need to watch more variables.
const char *data_to_send[10] = {NULL};


void tinyDebugger_send_int(const char* name, int value){
	if(DEBUGGING){
		printf("%s:%d;", name, value);
	}
}

void tinyDebugger_send_uint8(const char* name, uint8_t value){
	if(DEBUGGING){
		printf("%s:%u;", name, value);
	}
}

void tinyDebugger_send_double(const char* name, double value){
	if(DEBUGGING){
		#define NUMBER_OF_DECIMALS 1
		char number[20]; // Arbitrary max
		dtostrf(value,1,NUMBER_OF_DECIMALS, number);
		printf("%s:%s;", name, number);
	}
}
void tinyDebugger_send_string(const char* name, char * value){
	if(DEBUGGING){
		printf("%s:%s;", name, value);
	}
}
void tinyDebugger_end_line(){
	if(DEBUGGING){
		printf("\r\n");
	}
}