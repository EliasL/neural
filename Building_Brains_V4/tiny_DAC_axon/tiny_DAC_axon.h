/*
 * tiny_DAC_axon.h
 *
 * Created: 18.06.2018 16:10:46
 *  Author: Bendik
 */ 


#ifndef TINY_DAC_AXON_H_
#define TINY_DAC_AXON_H_


enum NeuronType
{
	EXCITATORY_NEURON, INHIBITORY_NEURON
};

void tiny_DAC_set_neuron_type(enum NeuronType neuron_type);
void tiny_DAC_axon_master_update(_Bool over_25, _Bool over_50);
bool tiny_DAC_axon_neg_pulse_queue_check(void);


#endif /* TINY_DAC_AXON_H_ */