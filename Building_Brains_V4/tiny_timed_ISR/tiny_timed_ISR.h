/*
 * tiny_timed_ISR.h
 *
 * Created: 19.06.2018 00:14:19
 *  Author: Bendik
 */ 


#ifndef TINY_TIMED_ISR_H_
#define TINY_TIMED_ISR_H_

void tiny_timed_ISR_setflag(_Bool new_flag_val);

_Bool tiny_timed_ISR_getflag(void);


#endif /* TINY_TIMED_ISR_H_ */