#include "interrupts.h"
#include "pc_buffer.h"
#include "../include/uart.h"
#include "../include/adc.h"

extern PC_Buffer UART0_Rx_Buffer;
extern PC_Buffer UART0_Tx_Buffer;
extern volatile bool AlertSysTick;
extern int stickX;
extern int stickY;
extern volatile bool ready;

//*****************************************************************************
// Rx Portion of the UART ISR Handler
//*****************************************************************************
__INLINE static void UART0_Rx_Flow(PC_Buffer *rx_buffer)
{
  // Remove entries from the RX FIFO until the HW FIFO is empty.
  // Data should be placed in the rx_buffer.
		while((UART0->FR & UART_FR_RXFE) == 0){
			if(!pc_buffer_full(&UART0_Rx_Buffer)){
				pc_buffer_add(&UART0_Rx_Buffer, UART0->DR);
			}
		}

  // Clear the RX interrupts so it can trigger again when the hardware 
  // FIFO becomes full
	UART0->ICR |= UART_ICR_RXIC | UART_ICR_RTIC;

}

//*****************************************************************************
// Tx Portion of the UART ISR Handler
//*****************************************************************************
__INLINE static void UART0_Tx_Flow(PC_Buffer *tx_buffer)
{
      char c;
  
        // Check to see if we have any data in the circular queue
				if(!pc_buffer_empty(&UART0_Tx_Buffer)){
            // Move data from the circular queue to the hardware FIFO
            // until the hardware FIFO is full or the circular buffer
            // is empty.
					  while(!(UART0->FR & UART_FR_TXFF) && !pc_buffer_empty(&UART0_Tx_Buffer)){
							pc_buffer_remove(&UART0_Tx_Buffer,&c);
							UART0->DR = c;
						}

					}
					else{
						// Any data in the hardware FIFO will continue to be transmitted
            // but the TX empty interrupt will not be enabled since there
            // is no data in the circular buffer.
            // Disable the TX interrupts.
						UART0->IM &= ~UART_IM_TXIM;
					}
        
        // Clear the TX interrupt so it can trigger again when the hardware
        // FIFO is empty
				UART0->ICR |= UART_ICR_TXIC;

}

// SysTick Handler
void SysTick_Handler(void)
{
   uint32_t val;
 
   // Alert the main application the SysTick Timer has expired
   AlertSysTick = true;
 
   // Clears the SysTick Interrupt
   val = SysTick->VAL;
}

//*****************************************************************************
// UART0 Interrupt Service handler
//*****************************************************************************
void UART0_Handler(void)
{
    uint32_t  status;

    // Check to see if RXMIS or RTMIS is active
    status = UART0->MIS;

    if ( status & (UART_MIS_RXMIS | UART_MIS_RTMIS ) )
    {
       UART0_Rx_Flow(&UART0_Rx_Buffer);
    }

    // Check the TX interrupts
    if ( status & UART_MIS_TXMIS )
    {
      UART0_Tx_Flow(&UART0_Tx_Buffer);
    }
    return;
}

//ADC Handler. Handles the Joystick.
void ADC0SS3_Handler(void){
	ADC0_Type* myADC = (ADC0_Type*)ADC0_BASE;
	
	ready = true;
	
	//Read the X direction from PS2 joystick
	stickX = myADC->SSFIFO3;
	
	//Clear the interrupt
	myADC->ISC |= ADC_ISC_IN3;
	
}
