/*
 * tinyAxon.h
 *
 * Created: 18.06.2018 16:10:46
 * Authors: Bendik Bogfjellmo, Elias Lundheim
 */ 


#ifndef TINYAXON_H_
#define TINYAXON_H_


enum NeuronType
{
	EXCITATORY_NEURON, INHIBITORY_NEURON
};

_Bool tinyAxon_is_firing();

double tinyAxon_update_potential(double potential);

_Bool tinyAxon_check_charge_level(void);

void tinyAxon_stop_sending_pulse();

#endif /* tinyAxon_H_ */