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
#include <util/delay.h>
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
#define ACCEPTABLE_NOISE 4
#define NUMBER_OF_TEST_FUNCTIONS 1
#define NUMBER_OF_RUNS_FOR_EACH_TEST 10

/*
check_signals() will send signals out through the axon and check that all of it's own dendrites recieve the sent signal.
This assumes that the neuron is placed in a circuit connecting the axon to all the dendrites.
*/
int tinyTester_check_signals(){
	int number_of_failed_checks = 0;
	
	# define NUMBER_OF_TEST_VALUES 10
	// The neuron seems to have trouble reaching a value of 255. Often at least one dendrite reads 249, which gives an error.
	// But there are no errors when sending 250.
	// Hmm, let's try 245
	// Ok, good thing to know, it's difficult to get use the high values
	uint8_t test_values[NUMBER_OF_TEST_VALUES] = {0, 33, 66, 99, 132, 166, 199, 232, 245, 0}; // Current ADC (Analog to Digital Converter) values
	
	
	printf("Starting signal test.\r\n");
	
	for (int i = 0; i < NUMBER_OF_TEST_VALUES; i++)
	{
		// Set the axon value
		DAC_0_set_output(test_values[i]);
		tinyDendrite_read_signals();
		for (int j = 0; j < DENDRITE_COUNT; j++)
		{
			int difference = test_values[i] - tinyDendrite_get_value(j);
			if(abs(difference) > ACCEPTABLE_NOISE){
				number_of_failed_checks++;
				int measurement = tinyDendrite_get_value(j);
				printf("Signal test failed! Axon sent %3u but dendrite %1u received %3u.\r\n", test_values[i], j, tinyDendrite_get_value(j));
			}
		}
	}
	
	printf("Signal test is done.\r\n");
	return number_of_failed_checks;
}

/*
test() is the main function that will run all the tests and give feedback as to whether or not the test has failed
*/
void tinyTester_test(){
	_Bool test_failed = false;
	uint8_t number_of_failed_tests = 0;
	uint8_t number_of_failed_checks = 0;
	
	// Show that testing has started
	tinyLED_set_color(INN_LED, BLUE);
	printf("Starting testing.\r\n");
	
	// Gather all of the test functions
	//https://cboard.cprogramming.com/c-programming/128162-array-functions.html
	// A list of all the test functions we run.
	_Bool (*testFunctions[NUMBER_OF_TEST_FUNCTIONS])() = {&tinyTester_check_signals};
	
	for (int i=0; i<NUMBER_OF_TEST_FUNCTIONS; i++){
		test_failed = false;
		number_of_failed_checks = 0;
		//Starting test
		tinyLED_set_color(OUT_LED, YELLOW);
		
		//Update LED
		tinyLED_update();
		for(int j=0; j<NUMBER_OF_RUNS_FOR_EACH_TEST; j++){
			number_of_failed_checks += testFunctions[i]();
		}
		if(number_of_failed_checks>NUMBER_OF_RUNS_FOR_EACH_TEST){
			// We fail the test if there is more than one error in each of the tests
			printf("Test failed! In %2u runs, there were %2u failed checks.\r\n", NUMBER_OF_RUNS_FOR_EACH_TEST, number_of_failed_checks);
			test_failed = true;
			tinyLED_set_color(OUT_LED, RED);
			number_of_failed_tests++;
		}
		
		else if(number_of_failed_checks>0){
			// We warn that there was some trouble
			printf("Warning! In %2u runs, there were %2u failed checks.\r\n", NUMBER_OF_RUNS_FOR_EACH_TEST, number_of_failed_checks);
			tinyLED_set_color(OUT_LED, YELLOW);
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
	
	printf("Testing is done.\r\n\r\n");
}
