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
//#define NEURONTYPE EXCITATORY_NEURON


// The neuron only keeps track of a certain number of pulses (When a pulse is queued, it is stored in an array of this length.)
// Note that if there are memory limitations, reducing this number might help slightly
#define MAX_NUMBER_OF_PULSES 10


// TINYPOTENTIAL_TIME_CONST determines how fast the potential will decay over time.
#define TINYPOTENTIAL_TIME_CONST 100 //(ms)


// TIMESCALE adjusts the speed of the RTC (Real Time Clock). The crystal oscillator that the RTC uses runs at 32KHz, and so
// the usual RTC period is 32 ticks (0x20 in hex), making the clock tick once every ms. When we set the TIMESCALE to two
// the period is halved, and everything runs twice as quickly. Likewise, we can set the TIMESCALE to 0.5, and make everything run
// slower. Note that some settings are effected by the timescale value. Counterintuitively, this means that they will NOT change 
// when the timescale is adjusted. See PULSEMODE_BUTTON_PRESS_TIME for an example.
#define TIMESCALE 1
// Sending data over USART requires a lot of time, so in order for the program to run quickly, we need to turn off sending 
// debugging messages when we want the neuron to run quickly
// Debugging in high timescales (above 0.1), often leads to strange behavior
// Set 1 for true and 0 for false
#define DEBUGGING 0


// A value of n will result in n pulses every second when the neuron is in pulse mode. (max 500)
#define PULSEMODE_FREQUENCY 2 


// Amount of time in ms the button needs to be held down before switching to or from pulse mode.
// Note that this value is adjusted with the TIMESCALE, so that one second is constant regardless of TIMESCALE
#define PULSEMODE_BUTTON_PRESS_TIME 2000 * TIMESCALE //(ms)


// The axon affects the dendrites. Setting this value to 1 will make the neuron ignore inputs while it is firing.
#define IGNORE_INPUT_WHILE_FIRING 0

/*
			LED SETTINGS
*/


// The number of LEDs used
#define  NUMBER_OF_LEDS 2


// We give the LEDs names to clarify code
#define OUT_LED 1
#define INN_LED 0


// Brightness as a value between 0 and 1 (Should be lower than 1 since some lights go above this LED brightness)
#define LED_BRIGHTNESS 0.1

// When the potential is at this value, the LED should light up with LED_BRIGHTNESS strength
#define FULL_BRIGHTNESS_POTENTIAL 25

// When setting colors, make sure the color is defined in tinyLED.h


// Choose the color displayed when charging
#define CHARGING_COLOR RED


// Choose the color displayed when charging
#define CHARGING_DONE_COLOR GREEN


// Choose the color that pings with a small flash to show that the neuron is on
// Choose the color OFF to disable pinging
#define PING_COLOR LED_OFF

// Choose how bright the ping is (Should be very low, typically 0.02)
#define PING_BRIGHTNESS 0.02


// Choose what color to display when the neuron is in puse mode
#define PULSEMODE_COLOR LED_OFF

// Choose how bright the weak light mode should be
#define WEAK_BRIGHTNESS 0.1


// How many times per second a led in SWING mode swings
#define SWING_RATE 0.5 * TIMESCALE


// How many time per second a led in FLASH mode flashes
#define FLASH_RATE 1 * TIMESCALE


// How many time per second a led in PING mode flashes (The flash lasts for FLASH_TIME seconds)
#define PING_RATE 0.1 * TIMESCALE


// How long flashes last
#define FLASH_TIME 0.1 * TIMESCALE

// In order to distinguish between two subsequent flashes, we include a "off time"
// If the LED is trying to flash, but the next pulse is within FLASH_OFF_TIME seconds of 
// firing, the LED is turned off instead.
#define FLASH_OFF_TIME 0.012 * TIMESCALE

/*
			POTENTIAL SETTINGS
*/


// If the potential is above this value, the neuron fires
#define THRESHOLD_POTENTIAL 25

// If the potential is below this value, the neuron attempts to remove a queued pulse
#define REMOVE_PULSE_THRESHOLD -20


// This is how much the potential changes when we press the button
#define BUTTON_PRESS_REACTION 26


// After the axon has fired, the potential changes by this amount
// I want to test reducing the potential by -30 instead of -25 to simulate the hyperpolarization
#define POSTFIRE_POTENTIAL_REACTION -25

// To avoid having the neuron potential very close to zero, but not exactly zero, we set the potential 
// equal to zero when the absolute value of the potential is less than this variable
#define POLARIZATION_OFFSET 0.1


// Time for pulse to travel from Dendrites to axon
#define TRAVLE_DELAY 100


// Minimum time between pulses
#define FIRE_DELAY 15


// If a pulse has been queued, and the neurons potential drops significantly shortly after the pulse has been queued
// we want to remove the pulse. However, if the potential has already traveled most of the distance to the axon, we
// want to let the pulse reach the axon anyway (fire). If a pulse is less than the PULSE_NO_RETURN_TIME ms away from 
// firing, the pulse will not be removed.
#define PULSE_NO_RETURN_TIME 0


/*
			INPUT SIGNAL DEFINITIONS
			
*/

/*
Signal threshold definitions
When a Dendrite reads the ADC, these values (between 0 and 255) decide what correspond to the different signals.

These values work ok for amplifying resistance of 2.2kohm, and reductive resistance of 5kohm

See "Signalområder" in the Google Drive project Hjernebyggesett V4/Teknisk/Software

But then also see "Signal vekting" in Hjernebyggesett V4/Teknisk/Hardware/Kretskort
and realsize that it's not a simple linear realationship between signal and resistance,
so these thresholds are found by trail and error.
*/


#define CHARGING_THRESHOLD 254
#define NORMAL_EXCITE_THRESHOLD 218
#define HIGH_EXCITE_THRESHOLD 181
#define LOW_EXCITE_THRESHOLD 145
#define NORMAL_INHIB_THRESHOLD 100
#define HIGH_INHIB_THRESHOLD 73
#define LOW_INHIB_THRESHOLD 36

/*
Signal reaction definitions
When a Dendrite receives a signal, these values describe how the potential in the neuron changes.
See Signalområder doc in drive
*/

#define NO_SIGNAL_REACTION 0
#define HIGH_EXCITE_REACTION 52
#define NORMAL_EXCITE_REACTION 25
#define LOW_EXCITE_REACTION 20
#define HIGH_INHIB_REACTION -50
#define NORMAL_INHIB_REACTION -25
#define LOW_INHIB_REACTION -20


/*
			OUTPUT SIGNAL DEFINITIONS
			
See "Signalområder" in the Google Drive project Hjernebyggesett V4/Teknisk/Software
*/

#define NO_SIGNAL_OUTPUT 0


// Due to various complications, we resort to finding values that work by trail an error
#define EXCITATORY_NEURON_OUTPUT 236
#define INHIBITORY_NEURON_OUTPUT 110


/*
			TENCHINCAL DEFINITIONS
*/
// To avoid that the axon firing activates the charge mode, we require several cycles of high signal levels in order
// to switch to charging mode.
#define CYCLES_REQUIRED_FOR_CHARGING_MODE_SWITCH 10

// Number of Dendrites
// NB! Chancing this will also require you to change the "Dendrite_ports" array in tinyDendrite.c
#define DENDRITE_COUNT 5

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