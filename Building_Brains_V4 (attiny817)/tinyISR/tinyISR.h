/*
 * tinyISR.h
 *
 * Created: 19.06.2018 00:14:19
 * Authors: Bendik Bogfjellmo, Elias Lundheim
 */ 


#ifndef TINYISR_H_
#define TINYISR_H_

void tinyISR_setflag(_Bool new_flag_val);

_Bool tinyISR_getflag(void);


#endif /* TINY_TIMED_ISR_H_ */