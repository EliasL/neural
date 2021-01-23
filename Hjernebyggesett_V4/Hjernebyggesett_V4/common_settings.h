/*
 * common_settings.h
 *
 * Created: 20.12.2020 09:09:39
 *  Author: Elias Lundheim
 */ 


#ifndef COMMON_SETTINGS_H_
#define COMMON_SETTINGS_H_


/*
This is another settings file that you can move and organize as you see fit.
The idea is to gather the more relevant settings in a smaller file with less stuff to read.
To read more about the various settings, see settings.h

HOW TO MOVE SETTIGNS:
When you find a setting you want to move from settings.h to common settings.h, you comment out the definition in settings.h like this:

	Before moving:
		// Choose whether the neuron is a EXCITATORY_NEURON or a INHIBITORY_NEURON
		#define NEURONTYPE EXCITATORY_NEURON
	
	After moving:
		// Choose whether the neuron is a EXCITATORY_NEURON or a INHIBITORY_NEURON
		//#define NEURONTYPE EXCITATORY_NEURON

The two extra "//" disables the line from the code so that it doesn't do anything. Doing this instead of deleting it, makes it easier to undo.

When you have disabled the definition in settings.h, you need to add it to common_settings.h 
You do this by copying the "#define ..." part and pasting it in this file:

	Before moving:

	After moving:
		#define NEURONTYPE EXCITATORY_NEURON
*/



#define NEURONTYPE EXCITATORY_NEURON



#endif /* COMMON SETTINGS_H_ */