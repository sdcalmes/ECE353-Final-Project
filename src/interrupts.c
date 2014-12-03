#include "interrupts.h"
#include "pc_buffer.h"
#include "../include/uart.h"

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

extern PC_Buffer UART0_Rx_Buffer;
extern PC_Buffer UART0_Tx_Buffer;

extern void UART0_Tx_Flow(PC_Buffer *tx_buffer);

//*****************************************************************************
// Rx Portion of the UART ISR Handler
//*****************************************************************************
__INLINE static void UART0_Rx_Flow(PC_Buffer *rx_buffer)
{
  // Remove entries from the RX FIFO until they are all removed
  while( !(UART0->FR & UART_FR_RXFE ))
  {
    if( ! pc_buffer_full(rx_buffer))
    {
      // Add the character to the circular buffer
      pc_buffer_add(rx_buffer,UART0->DR);
    }
  }

  // Clear the RX interrupts so it can trigger again when the hardware 
  // FIFO becomes full
  UART0->ICR |= (UART_ICR_RXIC | UART_ICR_RTIC);
}

//*****************************************************************************
// Tx Portion of the UART ISR Handler
//*****************************************************************************
__INLINE static void UART0_Tx_Flow(PC_Buffer *tx_buffer)
{
      char c;
  
        // Check to see if we have any data in the circular queue
        if( ! pc_buffer_empty(tx_buffer))
        {
            // Move data from the circular queue to the hardware FIFO
            // until the hardware FIFO is full or the circular buffer
            // is empty.
            while( (! pc_buffer_empty(tx_buffer)) && !(UART0->FR & UART_FR_TXFF ) )
            {
              pc_buffer_remove(tx_buffer, &c);  
              UART0->DR = c;
            }
        }
        else
        {
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
