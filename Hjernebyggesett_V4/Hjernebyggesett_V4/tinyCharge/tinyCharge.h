/*
 * tinyCharge.h
 *
 * Created: 02.07.2019 14:49:32
 * Author: Elias Lundheim
 */ 


#ifndef TINYCHARGE_H_
#define TINYCHARGE_H_



_Bool tinyCharge_is_connected_to_charger();

_Bool tinyCharge_is_fully_charged();

void tinyCharge_set_charging_mode(_Bool charging_status);

void tinyCharge_set_transistors();

#endif /* TINYCHARGE_H_ */