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

// A value of n will make n pulses every second when the neuron is in pulse mode. (max 500)
#define PULSEMODE_FREQUENCY 2

// Amount of time in ms the button needs to be held down before switching to or from pulse mode.
#define PULSEMODE_BUTTON_PRESS_TIME 2000 //(ms)

// TINYPOTENTIAL_TIME_CONST determines how fast the potential will decay over time.
#define TINYPOTENTIAL_TIME_CONST 100 //(ms)



/*
			POTENTIAL SETTINGS
*/
// If the potential is above this value, the neuron fires
#define THRESHOLD_POTENTIAL 25

#define BUTTON_PRESS_REACTION 26

// After the axon has fired, the potential changes by this amount
// I want to test reducing the potential by -30 instead of -25 to simulate the hyperpolarization
#define POSTFIRE_POTENTIAL_REACTION -30

// Time for pulse to travel from dendrites to axon
#define TRAVLE_DELAY 100

// Minimum time between pulses
#define FIRE_DELAY 50

// If a pulse has been queued, and the neurons potential drops significantly shortly after the pulse has been queued
// we want to remove the pulse. However, if the potential has already traveled most of the distance to the axon, we
// want to let the pulse reach the axon anyway (fire). An UNDO_PERIOD of 0 would mean that a queued pulse is never removed.
#define UNDO_PERIOD 60


/*
			INPUT SIGNAL DEFINITIONS
			
*/

/*
Signal threshold definitions
When a dendrite reads the ADC, what values (between 0 and 255) correspond to the different signals?

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
When a dendrite receives a signal, how does the potential in the neuron change?
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
#define EXCITATORY_NEURON_OUTPUT 215
#define INHIBITORY_NEURON_OUTPUT 116


/*
			TENCHINCAL DEFINITIONS
*/

// Number of dendrites
// NB! Chancing this will also require you to change "dendrite_ports" in tinyDendrite.c
#define TINYDENDRITE_COUNT 5

/*
Dendrite SW component signals
See PINMUX CONFIGURATOR in Atmel Start. (You can find this by right-clicking the 
project file "Building_Brains_V4" in the Solution Explorer, and selecting Re-Configure Atmel Start Project)
*/
#define DENDRITE_PORT_1 7
#define DENDRITE_PORT_2 5
#define DENDRITE_PORT_3 9
#define DENDRITE_PORT_4 11
#define DENDRITE_PORT_5 10

#endif /* SETTINGS_H_ */