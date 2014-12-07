#include "../include/uart.h"

#include "pc_buffer.h"

#define UART0_BUFFER_SIZE 80

extern void DisableInterrupts(void);
extern void EnableInterrupts(void);

extern PC_Buffer UART0_Rx_Buffer;
extern PC_Buffer UART0_Tx_Buffer;



/****************************************************************************
 * Verify that the uart base address is valid
 ****************************************************************************/
bool verifyUartBase(uint32_t base)
{
   switch(base)
   {
     case UART0_BASE:
     case UART1_BASE:
     case UART2_BASE:
     case UART3_BASE:
     case UART4_BASE:
     case UART5_BASE:
     case UART6_BASE:
     case UART7_BASE:
     {
       return true;
     }
     default:
     {
       return false;
     }
   }
}

/****************************************************************************
 * This routine transmits a single character out the UART / COM port.
 * Only the lower 8 bits of the 'data' variable are transmitted.
 ****************************************************************************/
void uartTxPollChar(uint32_t base, char data)
{
  UART0_Type *myUart =((UART0_Type *) base);

  if( verifyUartBase(base) == false)
  {
    return;
  }

  if ( data != 0)
  {
    while( ((myUart->FR)&(UART_FR_TXFF)) != 0 );
    myUart->DR = data;
  }
  return;
}

/****************************************************************************
 * This routine transmits a character string out the UART / COM port.
 * Only the lower 8 bits of the 'data' variable are transmitted.
 ****************************************************************************/
void uartTxPoll(uint32_t base, char *data)
{
  UART0_Type *myUart =((UART0_Type *) base);

  if( verifyUartBase(base) == false)
  {
    return;
  }

  if ( data != 0)
  {
    while(*data != '\0')
    {
      while( ((myUart->FR)&(UART_FR_TXFF)) != 0 );
      myUart->DR = *data;
      data++;
    }
  }
  return;
}

/****************************************************************************
 * This routine returns a character received from the UART/COM port.
 * If blocking is enabled, this routine should not return until data
 * is available. If blocking is disabled and no data is available,
 * this function should return 0.
 ****************************************************************************/
char uartRxPoll(uint32_t base, bool block)
{
  UART0_Type *myUart =((UART0_Type *) base);

  if( verifyUartBase(base) == false)
  {
    return 0;
  }

  if( (block == false) && !(myUart->FR & UART_FR_RXFE))
  {
       return myUart->DR;
  }
  else if((block == false) && (myUart->FR & UART_FR_RXFE))
  {
    return 0;
  }

  while(myUart->FR & UART_FR_RXFE && block)
  {
    // Wait
  }

   return myUart->DR;
}



/****************************************************************************
 *
 ****************************************************************************/
int uartRx(bool block)
{
   int c;

   while (pc_buffer_empty(&UART0_Rx_Buffer))
   {
      if (!block)
         return -1;
   }

   DisableInterrupts();
   pc_buffer_remove(&UART0_Rx_Buffer, (char *)&c);
   EnableInterrupts();
   
   return c;
}

/****************************************************************************
 *
 ****************************************************************************/
void uartTx(int data)
{

  // If there is sapce in the hardwere FIFO, and the circular
  // Queue is empty, send the data to the FIFO.
  if( pc_buffer_empty(&UART0_Tx_Buffer) && !(UART0->FR & UART_FR_TXFF) )
  {
    UART0->DR =   data;
  }
  else
  {
    // Test to see if the circular buffer is full
    // If it is, we wait until there is space.
    while( pc_buffer_full(&UART0_Tx_Buffer))
    {
        // wait
    }

    DisableInterrupts();
    // Add the character to the circular buffer
    pc_buffer_add(&UART0_Tx_Buffer, (char) data);
    EnableInterrupts();
  }

  // If you're in this function, you want to send data
  // so enable TX interrupts even if they are already enabled.
  UART0->IM |= UART_IM_TXIM;

  return;
}

//************************************************************************
// Configure UART0 to be 115200, 8N1.  Data will be sent/recieved using
// polling (Do Not enable interrupts)
//************************************************************************
bool uart_init_115K(
  uint32_t base_addr, 
  uint32_t rcgc_mask, 
  uint32_t pr_mask, 
  IRQn_Type irq_mask,
  uint32_t  irq_priority
)
{
    UART0_Type *myUart;
    if( verifyUartBase(base_addr) == false)
    {
      return false;
    }
    
    myUart = (UART0_Type *)base_addr;
    
    // Turn on the UART Clock
    SYSCTL->RCGCUART |= rcgc_mask;
    
    // Wait until the UART is ready
    while( (SYSCTL->PRUART & pr_mask) == 0)
    {
      // busy wait
    }
    
    // Set the baud rate
    myUart->IBRD = 27;
    myUart->FBRD = 9;
    
    // Disable UART
    myUart->CTL &= ~UART_CTL_UARTEN;
    
    // Configure the Line Control for 8N1, FIFOs
    myUart->LCRH =   UART_LCRH_WLEN_8 | UART_LCRH_FEN;

    // Configure the FIFO Interrupt Levels
    myUart->IFLS = UART_IFLS_RX7_8 | UART_IFLS_TX1_8;
    
    // Turn on the UART Interrupts  for Tx, Rx, and Rx Timeout
    myUart->IM = UART_IM_RXIM | UART_IM_TXIM | UART_IM_RTIM;
    
    // Set the priority to 1
    NVIC_SetPriority(irq_mask, irq_priority);
  
    // Enable the NVIC for the watchdog timer
    NVIC_EnableIRQ(irq_mask); 
        
    // Enable Tx, Rx, and the UART
    myUart->CTL =  UART_CTL_RXE |  UART_CTL_TXE |  UART_CTL_UARTEN;
    
    return true;

}


//****************************************************************************
//  This function is called from MicroLIB's stdio library.  By implementing
//  this function, MicroLIB's getchar(), scanf(), etc will now work.
// ****************************************************************************/
int fgetc(FILE* stream)
{
   char c;

   if (stream != stdin)
   {
      errno = EINVAL; // should probably be ENOSTR
      return EOF;
   }

   c = uartRx(true);

   if (c == '\r')
      c = '\n';

   fputc(c, stdout);

   return c;
}

//****************************************************************************
// This function is called from MicroLIB's stdio library.  By implementing
// this function, MicroLIB's putchar(), puts(), printf(), etc will now work.
// ****************************************************************************/
int fputc(int c, FILE* stream)
{
   if (stream != stdout) // bah! to stderr
   {
      errno = EINVAL; // should probably be ENOSTR
      return EOF;
   }

   uartTx(c);

   if (c == '\n')
      uartTx('\r');

   return c;
}

