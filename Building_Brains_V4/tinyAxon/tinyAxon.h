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

double tinyAxon_update_potential(double potential);


#endif /* tinyAxon_H_ */