/*
 * tinyTester.c
 *
 * Created: 12.06.2020 13:48:57
 *  Author: Elias Lundheim
 *
 * The tinyTester should be a function that is run before the main program loop.
 * It will be it's own while loop, that runs various tests and gives feedback by lighting up
 * LEDs. 
 */ 


#include <stdbool.h>
#include <atmel_start.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "tinyDendrite/tinyDendrite.h"
#include "tinyAxon/tinyAxon.h"
#include "tinyTime/tinyTime.h"
#include "settings.h"
#include "tinyDebugger/tinyDebugger.h"
#include "tinyLED/tinyLED.h"

// how far away from the sent signal, the received signal can deviate without
// triggering a fail
#define ACCEPTABLE_NOISE 5
#define NUMBER_OF_TEST_FUNCTIONS 1

/*
check_signals() will send signals out through the axon and check that all of it's own dendrites recieve the sent signal.
This assumes that the neuron is placed in a circuit connecting the axon to all the dendrites.
*/
_Bool tinyTester_check_signals(){	
	_Bool test_failed = false;
	
	# define NUMBER_OF_TEST_VALUES 10
	uint8_t test_values[NUMBER_OF_TEST_VALUES] = {0, 33, 66, 99, 132, 166, 199, 232, 250, 0}; // Current ADC (Analog to Digital Converter) values
	
	
	printf("Starting testing.\r\n");
	
	for (int i = 0; i < NUMBER_OF_TEST_VALUES; i++)
	{
		// Set the axon value
		DAC_0_set_output(test_values[i]);
		tinyDendrite_read_signals();
		for (int j = 0; j < DENDRITE_COUNT; j++)
		{
			int difference = test_values[i] - tinyDendrite_get_value(j);
			if(abs(difference) > ACCEPTABLE_NOISE){
				test_failed = true;
				printf("Signal test failed! Axon sent %3u but dendrite %1u received %3u.\r\n", test_values[i], j, tinyDendrite_get_value(j));
			}
		}
	}
	
	printf("Testing is done.\r\n\r\n");
	return test_failed;
}

/*
test() is the main function that will run all the tests and give feedback as to whether or not the test has failed
*/
void tinyTester_test(){
	_Bool test_failed = false;
	uint8_t number_of_failed_tests = 0;
	
	// Show that testing has started
	tinyLED_set_color(INN_LED, BLUE);
	
	// Gather all of the test functions
	//https://cboard.cprogramming.com/c-programming/128162-array-functions.html
	// A list of all the test functions we run.
	_Bool (*testFunctions[NUMBER_OF_TEST_FUNCTIONS])() = {&tinyTester_check_signals};
	
	for (int i=0; i<NUMBER_OF_TEST_FUNCTIONS; i++){
		test_failed = false;
		//Starting test
		tinyLED_set_color(OUT_LED, YELLOW);
		
		//Update LED
		tinyLED_update();
		
		test_failed = testFunctions[i]();
		if(test_failed){
			tinyLED_set_color(OUT_LED, RED);
			number_of_failed_tests++;
		}
		else{
			tinyLED_set_color(OUT_LED, GREEN);
		}
		
		// Update LED
		tinyLED_update();
	}
	
	//Final verdict
	if(number_of_failed_tests>0){
		tinyLED_set_color(INN_LED, RED);
		}else{
		tinyLED_set_color(INN_LED, GREEN);
	}
}
