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

// TINYPOTENTIAL_TIME_CONST determines how fast the potential will decay over time.
#define TINYPOTENTIAL_TIME_CONST 100 //(ms)

// If the potential is above this value, the neuron fires
#define THRESHOLD_POTENTIAL 25



/*
			SIGNAL DEFINITIONS
*/


/*
Signal threshold definitions
When a dendrite reads the ADC, what values (between 0 and 255) correspond to the different signals?
*/
#define NORMAL_EXCITE_THRESHOLD 213
#define HIGH_EXCITE_THRESHOLD 160
#define LOW_EXCITE_THRESHOLD 139
#define NORMAL_INHIB_THRESHOLD 114
#define HIGH_INHIB_THRESHOLD 87
#define LOW_INHIB_THRESHOLD 50

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
#define DENDRITE_PORT_1 5
#define DENDRITE_PORT_2 7
#define DENDRITE_PORT_3 9
#define DENDRITE_PORT_4 10
#define DENDRITE_PORT_5 11

#endif /* SETTINGS_H_ */