#include "watchdog.h"

void watchdogInit(uint32_t ticks, uint8_t priority){
	
	SYSCTL->RCGCWD |= SYSCTL_RCGCWD_R0;
	while((SYSCTL->PRWD & SYSCTL_PRWD_R0) != 1);
	WATCHDOG0->LOAD = ticks;
	WATCHDOG0->CTL |= 0x3;

	NVIC_SetPriority(WATCHDOG0_IRQn, priority);
	NVIC_EnableIRQ(WATCHDOG0_IRQn);
  
}
