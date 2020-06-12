/*
 * tinyPulse.h
 *
 * Created: 02.07.2019 13:15:08
 * Author: Elias Lundheim
 */ 


#ifndef TINYPULSE_H_
#define TINYPULSE_H_


_Bool tinyPulse_is_in_pulse_mode();

void tinyPulse_toggle_pulse_mode();

void tinyPulse_set_pulse_mode(_Bool mode);

double tinyPulse_update_potential(double potential);



#endif /* TINYPULSE_H_ */