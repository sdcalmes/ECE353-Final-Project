#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "timers.h"

void 
	f14_timer1_Init(uint32_t ticks){
	
	TIMER0_Type *gp_timer;
		uint32_t timer_rcgc_mask;
		uint32_t timer_pr_mask;
		timer_rcgc_mask = SYSCTL_RCGCTIMER_R1;
		timer_pr_mask = SYSCTL_PRTIMER_R1;
		
		// Turn on the clock for the timer
		SYSCTL->RCGCTIMER |= timer_rcgc_mask;

		// Wait for the timer to turn on
		while( (SYSCTL->PRTIMER & timer_pr_mask) == 0) {}
			
		gp_timer = (TIMER0_Type *) TIMER1_BASE;
			
		// disable both the A and B timers
		gp_timer->CTL = 0x0;
			
		// set the timer to be in 32-bit mode
		gp_timer->CFG = TIMER_CFG_32_BIT_TIMER;
			
		// set the Timer A Mode Register to be periodic and count down
		gp_timer->TAMR = TIMER_TAMR_TAMR_PERIOD;
		gp_timer->TAMR |= 0x10;

		gp_timer->TAILR = 50000000;

		gp_timer->ICR |= TIMER_ICR_TATOCINT;
			gp_timer->CTL |= TIMER_CTL_TAEN;

}


//*****************************************************************************
// Starts Timer1.  
// Assumes the timer has already been configured using f14_timer1_init()
//*****************************************************************************
void f14_timer0_start(uint32_t count){
		TIMER0_Type *gp_timer;
		gp_timer = (TIMER0_Type *) TIMER1_BASE;
	
		// set the number of clock cycles in the Timer a Interval Load register
		gp_timer->TAILR = 1000000;
		
	// Enable Timer A using the Timer Control Register
		gp_timer->CTL |= TIMER_CTL_TAEN;
}

//*****************************************************************************
// Stops Timer1
// Assumes the timer has already been configured using f14_timer1_init()
//*****************************************************************************
float f14_timer0_stop(void){
		int ticks;
		TIMER0_Type *gp_timer;
		gp_timer = (TIMER0_Type *) TIMER1_BASE;
		
		//disable Timer 1 A
		gp_timer->CTL &= ~TIMER_CTL_TAEN;
	
		// clear the time-out interupt
		gp_timer->ICR = TIMER_ICR_TATOCINT;
	
		//get ticks
		ticks = (gp_timer->TAV);
		gp_timer->TAV = 0;
		return ticks;
}

float timer0_get_ticks(void){
	TIMER0_Type *gp_timer;
	gp_timer = (TIMER0_Type *) TIMER1_BASE;
	return (gp_timer->TAV);
}



