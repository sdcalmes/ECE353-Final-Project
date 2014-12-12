#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "timers.h"

//*****************************************************************************
// Initializes Timer0
//*****************************************************************************
void f14_timer0_Init(void){
		TIMER0_Type *gp_timer;
		uint32_t timer_rcgc_mask;
		uint32_t timer_pr_mask;
		int five_sec = (50000000)*(5);
		timer_rcgc_mask = SYSCTL_RCGCTIMER_R0;
		timer_pr_mask = SYSCTL_PRTIMER_R0;
		
		// Turn on the clock for the timer
		SYSCTL->RCGCTIMER |= timer_rcgc_mask;

		// Wait for the timer to turn on
		while( (SYSCTL->PRTIMER & timer_pr_mask) == 0) {};
			
			
		gp_timer = (TIMER0_Type *) TIMER0_BASE;
			
		
		// disable both the A and B timers
		gp_timer->CTL = 0x0;
		
		
		// set the timer to be in 32-bit mode
		gp_timer->CFG = TIMER_CFG_32_BIT_TIMER;
		
		
		// set the Timer A Mode Register to be in one-shot mode and count down
		gp_timer->TAMR = TIMER_TAMR_TAMR_PERIOD;		

			// set the number of clock cycles in the Timer a Interval Load register
		gp_timer->TAILR = five_sec;
		
		// Write to the Timer Interrupt Clear Register for the specified timer
		gp_timer->ICR |= TIMER_ICR_TATOCINT;
		
		//enable time-out interrupt
		gp_timer->IMR |= TIMER_IMR_TATOIM;
		
		// Enable Timer A using the Timer Control Register
		gp_timer->CTL |= TIMER_CTL_TAEN;
		
		
		NVIC_SetPriority(TIMER0A_IRQn,1);
		NVIC_EnableIRQ(TIMER0A_IRQn);
		
		
		
}




//Initialize timer1,and start it.
void f14_timer1_Init(uint32_t ticks){
	
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

//initialize timer2
void f14_timer2_Init(){
		TIMER0_Type *gp_timer;
		uint32_t timer_rcgc_mask;
		uint32_t timer_pr_mask;
		timer_rcgc_mask = SYSCTL_RCGCTIMER_R2;
		timer_pr_mask = SYSCTL_PRTIMER_R2;
		
		// Turn on the clock for the timer
		SYSCTL->RCGCTIMER |= timer_rcgc_mask;

		// Wait for the timer to turn on
		while( (SYSCTL->PRTIMER & timer_pr_mask) == 0) {};
			
			
		gp_timer = (TIMER0_Type *) TIMER2_BASE;
			
		
		// disable both the A and B timers
		gp_timer->CTL = 0x0;
		
		// set the timer to be in 16-bit mode
		gp_timer->CFG = TIMER_CFG_16_BIT;
		
		
		// set the Timer A Mode Register to be in one-shot mode and count down
		gp_timer->TAMR = TIMER_TAMR_TAMR_PERIOD;
		
		
		// set the number of clock cycles in the Timer a Interval Load register
		gp_timer->TAILR = 50000000;
		
			
		// set the prescalar to 20 so that we get the 20 ms
		gp_timer->TAPMR = 1000;
		
		// Write to the Timer Interrupt Clear Register for the specified timer
		gp_timer->ICR |= TIMER_ICR_TATOCINT;
		
		//turn on interrupts
	//	gp_timer->IMR |= TIMER_IMR_TATOIM;

		// Enable Timer A using the Timer Control Register
		gp_timer->CTL |= TIMER_CTL_TAOTE | TIMER_CTL_TAEN;
}

//initialize timer2
void f14_timer3_Init(){
		TIMER0_Type *gp_timer;
		uint32_t timer_rcgc_mask;
		uint32_t timer_pr_mask;
		timer_rcgc_mask = SYSCTL_RCGCTIMER_R3;
		timer_pr_mask = SYSCTL_PRTIMER_R3;
		
		// Turn on the clock for the timer
		SYSCTL->RCGCTIMER |= timer_rcgc_mask;

		// Wait for the timer to turn on
		while( (SYSCTL->PRTIMER & timer_pr_mask) == 0) {};
			
			
		gp_timer = (TIMER0_Type *) TIMER3_BASE;
			
		
		// disable both the A and B timers
		gp_timer->CTL = 0x0;
		
		// set the timer to be in 16-bit mode
		gp_timer->CFG = TIMER_CFG_32_BIT_TIMER;
		
		
		// set the Timer A Mode Register to be in one-shot mode and count down
		gp_timer->TAMR = TIMER_TAMR_TAMR_PERIOD;
		
		
		// set the number of clock cycles in the Timer a Interval Load register
		gp_timer->TAILR = 100000;
		
			
		// set the prescalar to 20 so that we get the 20 ms
		//gp_timer->TAPMR = 100;
		
		// Write to the Timer Interrupt Clear Register for the specified timer
		gp_timer->ICR |= TIMER_ICR_TATOCINT;
					
					//enable time-out interrupt
		gp_timer->IMR |= TIMER_IMR_TATOIM;
		
		// Enable Timer A using the Timer Control Register
			gp_timer->CTL |= TIMER_CTL_TAEN;
		
		NVIC_SetPriority(TIMER3A_IRQn,1);
		NVIC_EnableIRQ(TIMER3A_IRQn);
		
}

//initialize timer2
void f14_timer4_Init(){
		TIMER0_Type *gp_timer;
		uint32_t timer_rcgc_mask;
		uint32_t timer_pr_mask;
		timer_rcgc_mask = SYSCTL_RCGCTIMER_R4;
		timer_pr_mask = SYSCTL_PRTIMER_R4;
		
		// Turn on the clock for the timer
		SYSCTL->RCGCTIMER |= timer_rcgc_mask;

		// Wait for the timer to turn on
		while( (SYSCTL->PRTIMER & timer_pr_mask) == 0) {};
			
			
		gp_timer = (TIMER0_Type *) TIMER4_BASE;
			
		
		// disable both the A and B timers
		gp_timer->CTL = 0x0;
		
		// set the timer to be in 16-bit mode
		gp_timer->CFG = TIMER_CFG_32_BIT_TIMER;
		
		
		// set the Timer A Mode Register to be in one-shot mode and count down
		gp_timer->TAMR = TIMER_TAMR_TAMR_PERIOD;
		
		
		// set the number of clock cycles in the Timer a Interval Load register
		gp_timer->TAILR = 7500000;
		
			
		// set the prescalar to 20 so that we get the 20 ms
		//gp_timer->TAPMR = 20;
		
		// Write to the Timer Interrupt Clear Register for the specified timer
		gp_timer->ICR |= TIMER_ICR_TATOCINT;
		
				//enable time-out interrupt
		gp_timer->IMR |= TIMER_IMR_TATOIM;
		
		// Enable Timer A using the Timer Control Register
			gp_timer->CTL |= TIMER_CTL_TAEN;
		
		NVIC_SetPriority(TIMER4A_IRQn,1);
		NVIC_EnableIRQ(TIMER4A_IRQn);
		
}

//Timer 5 for sending packets
void project_timer5_Init(void){
	TIMER0_Type *gp_timer;
	gp_timer = (TIMER0_Type *)TIMER5_BASE;
	SYSCTL->RCGCTIMER |= SYSCTL_RCGCTIMER_R5;
	
	while( (SYSCTL->PRTIMER & SYSCTL_PRTIMER_R5) == 0) {};
	
		
	gp_timer->CTL = 0;
		gp_timer->CFG = TIMER_CFG_32_BIT_TIMER;
		gp_timer->TAMR = TIMER_TAMR_TAMR_PERIOD;
		gp_timer->TAMR &= ~(TIMER_TAMR_TACDIR);
		
		gp_timer->TAILR = 50000000;
		
		gp_timer->IMR |= 0x1;
		
		NVIC_SetPriority(TIMER5A_IRQn, 2);
		NVIC_EnableIRQ(TIMER5A_IRQn);
		
		gp_timer->CTL |= (TIMER_CTL_TAEN);
	}


//*****************************************************************************
// Starts Timer1.  
// Assumes the timer has already been configured using f14_timer1_init()
//*****************************************************************************
void f14_timer1_start(uint32_t count){
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
float f14_timer1_stop(void){
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



