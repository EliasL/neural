/*
 * tinySleep.c
 *
 * Created: 13.06.2020 13:03:40
 *  Author: Elias Lundheim
 */ 


#include <avr/io.h>
#include "avr/interrupt.h"
#include "avr/wdt.h"

#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/interrupt.h>

void tinySleep_optimize_unused_pins(){
	// Don't understand it, maybe implement later
}

void tinySleep_prepare_sleep(){
  // We need to set the sleep mode and enable interrupt pins
  /*
  PCMSK0 |= (1<<PCINT7); //Enable Pin Change Interrupt 7
  
  GIMSK |= _BV(PCIE);                     // Enable Pin Change Interrupts
  PCMSK |= _BV(PCINT3);                   // Use PB3 as interrupt pin
  ADCSRA &= ~_BV(ADEN);                   // ADC off
  */
  
  //set_sleep_mode(SLEEP_MODE_PWR_DOWN);  // Set sleep mode to POWER DOWN mode
  set_sleep_mode(SLEEP_MODE_IDLE);  // Set sleep mode to POWER DOWN mode
  sleep_enable();
  
}

void tinySleep_enter_sleep(){

	
  //sleep_bod_disable();
  cli();
  sei();
  sleep_cpu();
  sleep_disable();
  
}