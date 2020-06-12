/*
 * tinyADCDendrites.h
 *
 * Created: 18.06.2018 13:50:42
 * Authors: Bendik Bogfjellmo, Elias Lundheim
 */ 


#ifndef TINYDendrite_H_
#define TINYDendrite_H_


void tinyDendrite_read_signals(void);


uint8_t tinyDendrite_get_value(uint8_t dendrite_number);

double tinyDendrite_update_potential(double potential);

_Bool tinyDendrite_check_charge_level(void);

void tinyDendrite_update_signals(void);


#endif /* TINYADCDendriteS_H_ */
