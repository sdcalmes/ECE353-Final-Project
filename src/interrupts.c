#include "interrupts.h"
#include "pc_buffer.h"
#include "../include/uart.h"
#include "../include/adc.h"
#include "../include/eadogs102w.h"
#include "io_expander.h"
#include "boardUtil.h"

extern PC_Buffer UART0_Rx_Buffer;
extern PC_Buffer UART0_Tx_Buffer;
extern volatile bool AlertSysTick;
extern volatile bool AlertADC0SS3;
extern volatile bool AlertTIMER1A;
extern volatile int readingX;
extern volatile int readingY;
extern volatile bool matrixWrite;
extern volatile bool joyStickUpdate;
extern volatile bool AlertRX;
int packets_received;
int packets_lost;
int col = 0;

//*****************************************************************************
// Rx Portion of the UART ISR Handler
//*****************************************************************************
__INLINE static void UART0_Rx_Flow(PC_Buffer *rx_buffer)
{
  // Remove entries from the RX FIFO until the HW FIFO is empty.
  // Data should be placed in the rx_buffer.
		while((UART0->FR & UART_FR_RXFE) == 0){
			if(!pc_buffer_full(rx_buffer)){
				pc_buffer_add(rx_buffer, UART0->DR);
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
				if(!pc_buffer_empty(tx_buffer)){
            // Move data from the circular queue to the hardware FIFO
            // until the hardware FIFO is full or the circular buffer
            // is empty.
					  while( (!pc_buffer_empty(tx_buffer)) && !(UART0->FR & UART_FR_TXFF) ){
							pc_buffer_remove(tx_buffer,&c);
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
// 		if(AlertSysTick){
//			AlertSysTick = false;
//			ledMatrixWriteData(I2C_I2C_BASE, col, Led_LUT[init_squares-squares_caught][col]);
//			col++;
//			col = col % 5;
//		}
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
  ADC0->PSSI = ADC_PSSI_SS3;     // Start SS3
  ADC1->PSSI = ADC_PSSI_SS3;
  while( ( (ADC0->RIS) & ADC_RIS_INR3)  == 0)
  {
    // wait
  }
  
  readingX = ADC0->SSFIFO3 & ADC_SSFIFO3_DATA_M;    // Read 12-bit data
	readingY = ADC1->SSFIFO3 & ADC_SSFIFO3_DATA_M;
	//Clear the interrupt
  ADC0->ISC |= ADC_ISC_IN3;          // Acknowledge the conversion
	ADC1->ISC |= ADC_ISC_IN3;
		AlertADC0SS3 = true;
	
}

void WDT0_Handler(void){
	lcd_clear();	
	lcd_write_string_10pts(0,"No Input 4");
	lcd_write_string_10pts(1,"Past 10");
	lcd_write_string_10pts(2,"seconds.");
	lcd_write_string_10pts(3,"Resetting.");

}

void TIMER0A_Handler(void){
	TIMER0_Type *gp_timer;
	gp_timer = (TIMER0_Type *) TIMER0_BASE;
	printf("Packets Received: %i\tPackets Lost: %i\n",packets_received, packets_lost);
	gp_timer->ICR = 1;
	
}

//matrix timer
void TIMER3A_Handler(void){
	TIMER0_Type *gp_timer;
	gp_timer = (TIMER0_Type *) TIMER3_BASE;
	gp_timer->ICR = 1;
	matrixWrite = true;
	
}

//joystick timer
void TIMER4A_Handler(void){
	TIMER0_Type *gp_timer;
	gp_timer = (TIMER0_Type *) TIMER4_BASE;
	gp_timer->ICR = 1;
	joyStickUpdate = true;
}

void GPIOD_Handler(void){
	AlertRX = true;
	GPIOD->ICR |= PD7;
}
