#include "interrupts.h"

extern bool AlertSysTick;

// SysTick Handler
void SysTick_Handler(void)
{
	
	 int count = 0;
   uint32_t val;
	
	
	if(count == 10){
   // Alert the main application the SysTick Timer has expired
   AlertSysTick = true;
 //Clear watchdog ICR register.
	 WATCHDOG0->ICR = 0x1;
	 count = 0;
	}
	else{
		count++;
	}
	 
	// Clears the SysTick Interrupt
   val = SysTick->VAL;
	 
}

void WDT0_Handler(void){
	
	while(1){};
	
}