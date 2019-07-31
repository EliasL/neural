/*
 * settings.h
 *
 * Created: 01.07.2019 13:01:51
 * Author: Elias
 */ 

#ifndef SETTINGS_H_
#define SETTINGS_H_


/*
			VARIOUS SETTINGS
*/


// Choose whether the neuron is a EXCITATORY_NEURON or a INHIBITORY_NEURON
#define NEURONTYPE EXCITATORY_NEURON


// The neuron only keeps track of a certain number of pulses
// Note that if there are memory limitations, reducing this number might help slightly
#define MAX_NUMBER_OF_PULSES 10


// TINYPOTENTIAL_TIME_CONST determines how fast the potential will decay over time.
#define TINYPOTENTIAL_TIME_CONST 100 //(ms)


// TIMESCALE adjusts the speed of the RTC (Real Time Clock). The crystal oscillator that the RTC uses runs at 32KHz, and so
// the usual RTC period is 32 ticks (0x20 in hex), making the clock tick once every ms. When we set the TIMESCALE to two
// the period is halved, and everything runs twice as quickly. Likewise, we can set the TIMESCALE to 0.5, and make everything run
// slower. Note that some settings are effected by the timescale value. Counterintuitively, this means that they will NOT change 
// when the timescale is adjusted. See PULSEMODE_BUTTON_PRESS_TIME for an example.
#define TIMESCALE 0.05


// Sending data over USART requires a lot of time, so in order for the program to run quickly, we need to turn off sending 
// debugging messages when we want the neuron to run quickly
// Set 1 for true and 0 for false
#define DEBUGGING 1


// An alternative to turning off the debugging completely, we can choose to set DEBUG_EVERY to something larger than 1. (max 255)
// For example, setting DEBUG_EVERY to 5, will make the tiny send a debug message every 5 cycles. 
// Be aware that this will result in important events not being logged. Short events such as dendrite and axon inputs and outputs, that only
// last one or two cycles, will seldomly be picked up by debugging every 5 cycles. 
#define DEBUG_EVERY 1


// A value of n will result in n pulses every second when the neuron is in pulse mode. (max 500)
#define PULSEMODE_FREQUENCY 2


// Amount of time in ms the button needs to be held down before switching to or from pulse mode.
// Note that this value is adjusted with the TIMESCALE, so that one second is constant regardless of TIMESCALE
#define PULSEMODE_BUTTON_PRESS_TIME 2000 * TIMESCALE //(ms)


/*
			LED SETTINGS
*/


// The number of LEDs used
#define  NUMBER_OF_LEDS 2


// We give the LEDs names to clarify code
#define OUT_LED 0
#define INN_LED 1


// Brightness as a value between 0 and 1
#define LED_BRIGHTNESS 0.1


// When setting colors, make sure the color is defined in tinyLED.h


// Choose the color displayed when charging
#define CHARGING_COLOR RED


// Choose the color displayed when charging
#define CHARGING_DONE_COLOR GREEN


// Choose the color that pings with a small flash to show that the neuron is on
#define PING_COLOR BLUE


// Choose how bright the ping is (Should be very low, typically 0.02)
#define PING_BRIGHTNESS 0.02


// How many times per second a led in SWING mode swings
#define SWING_RATE 0.5 * TIMESCALE


// How many time per second a led in FLASH mode flashes
#define FLASH_RATE 1 * TIMESCALE


// How many time per second a led in PING mode flashes (The flash lasts for FLASH_TIME seconds)
#define PING_RATE 0.1 * TIMESCALE


// How long various flashes last (max 0.255, can be changed to a higher max if needed by changing uint8 to unit16) 
#define FLASH_TIME 0.2 * TIMESCALE


/*
			POTENTIAL SETTINGS
*/


// If the potential is above this value, the neuron fires
#define THRESHOLD_POTENTIAL 25


// This is how much the potential changes when we press the button
#define BUTTON_PRESS_REACTION 26


// After the axon has fired, the potential changes by this amount
// I want to test reducing the potential by -30 instead of -25 to simulate the hyperpolarization
#define POSTFIRE_POTENTIAL_REACTION -30


// Time for pulse to travel from Dendrites to axon
#define TRAVLE_DELAY 100


// Minimum time between pulses
#define FIRE_DELAY 50


// If a pulse has been queued, and the neurons potential drops significantly shortly after the pulse has been queued
// we want to remove the pulse. However, if the potential has already traveled most of the distance to the axon, we
// want to let the pulse reach the axon anyway (fire). If a pulse is less than the PULSE_NO_RETURN_TIME ms away from 
// firing, the pulse will not be removed.
#define PULSE_NO_RETURN_TIME 60


/*
			INPUT SIGNAL DEFINITIONS
			
*/

/*
Signal threshold definitions
When a Dendrite reads the ADC, these values (between 0 and 255) decide what correspond to the different signals.

See "Signalområder" in the Google Drive project Hjernebyggesett V4/Teknisk/Software
*/

#define CHARGING_THRESHOLD 232
#define NORMAL_EXCITE_THRESHOLD 199
#define HIGH_EXCITE_THRESHOLD 166
#define LOW_EXCITE_THRESHOLD 132
#define NORMAL_INHIB_THRESHOLD 99
#define HIGH_INHIB_THRESHOLD 66
#define LOW_INHIB_THRESHOLD 33

/*
Signal reaction definitions
When a Dendrite receives a signal, these values describe how the potential in the neuron changes.
*/

#define NO_SIGNAL_REACTION 0
#define HIGH_EXCITE_REACTION 52
#define NORMAL_EXCITE_REACTION 26
#define LOW_EXCITE_REACTION 20
#define HIGH_INHIB_REACTION -50
#define NORMAL_INHIB_REACTION -26
#define LOW_INHIB_REACTION -20


/*
			OUTPUT SIGNAL DEFINITIONS
			
See "Signalområder" in the Google Drive project Hjernebyggesett V4/Teknisk/Software
*/

#define NO_SIGNAL_OUTPUT 0


// Due to various complications, we resort to finding values that work by trail an error
#define EXCITATORY_NEURON_OUTPUT 200
#define INHIBITORY_NEURON_OUTPUT 116


/*
			TENCHINCAL DEFINITIONS
*/

// Number of Dendrites
// NB! Chancing this will also require you to change the "Dendrite_ports" array in tinyDendrite.c
#define TINYDENDRITE_COUNT 5

/*
Dendrite SW component signals
See PINMUX CONFIGURATOR in Atmel Start. (You can find this by right-clicking the 
project file "Building_Brains_V4" in the Solution Explorer, and selecting Re-Configure Atmel Start Project,
then in the PINMUX, look at SW component signals)
*/
#define DENDRITE_PORT_1 3
#define DENDRITE_PORT_2 1
#define DENDRITE_PORT_3 6
#define DENDRITE_PORT_4 9
#define DENDRITE_PORT_5 7

#endif /* SETTINGS_H_ */