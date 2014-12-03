#ifndef __ECE353_INTERRUPTS_H__
#define __ECE353_INTERRUPTS_H__

#include <stdint.h>
#include <stdbool.h>
#include "TM4C123.h"

//************************************************************************
// Write the SysTick Handler so that it will set AlertSysTick  one every
// second.  The SysTick timer is configured to interrupt once every 100ms
// so you will need to create a static variable and keep track of how many
// times a SysTick interrupt has to occur for 1 second to have passed.
//
// The SysTick timer will also need to clear the watchdog by setting the 
// WATCHDOG0 ICR register.  Read the data sheet to determine the correct 
// value.
//
// Make sure to clear the SysTick Interrupt as well.  
//************************************************************************
void SysTick_Handler(void);

//************************************************************************
// Place only an infinite loop into this handler
//************************************************************************
void WDT0_Handler(void);

#endif
