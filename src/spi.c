// Copyright (c) 2014, Joe Krachey
// All rights reserved.
//
// Redistribution and use in binary form, with or without modification, 
// are permitted provided that the following conditions are met:
//
// 1. Redistributions in binary form must reproduce the above copyright 
//    notice, this list of conditions and the following disclaimer in 
//    the documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, 
// EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "spi.h"
#include "../include/sysctrl.h"

/****************************************************************************
 * This routine transmits a character out the SPI1 port.
 ****************************************************************************/
bool 
spiVerifyBaseAddr(uint32_t base)
{
  if ( base == SSI0_BASE ||
       base == SSI1_BASE ||
       base == SSI2_BASE ||
       base == SSI3_BASE
  )
  {
    return true;
  }
  else
  {
    return false;
  }
}

//*****************************************************************************
// Configure the given SPI peripheral to be 10Mhz and the given SPI mode
//*****************************************************************************
bool initialize_spi( uint32_t base_addr, uint8_t spi_mode)
{
    SSI0_Type *mySSI = (SSI0_Type *)base_addr;
  
    // Validate that a correct base address has been passed
    // Turn on the Clock Gating Register
    switch (base_addr) 
    {
      case SSI0_BASE :
      {
          SYSCTL->RCGCSSI |= SYSCTL_RCGCSSI_R0;
          while ((SYSCTL->PRSSI & SYSCTL_PRSSI_R0) == 0){}    /* wait until SSI is ready */
          break;
      }
      case SSI1_BASE :
      {
          SYSCTL->RCGCSSI |= SYSCTL_RCGCSSI_R1;
          while ((SYSCTL->PRSSI & SYSCTL_PRSSI_R1) == 0){}    /* wait until SSI is ready */
          break;
      }
      case SSI2_BASE :
      {
          SYSCTL->RCGCSSI |= SYSCTL_RCGCSSI_R2;
          while ((SYSCTL->PRSSI & SYSCTL_PRSSI_R2) == 0){}    /* wait until SSI is ready */
          break;
      }
      case SSI3_BASE :
      {
          SYSCTL->RCGCSSI |= SYSCTL_RCGCSSI_R3;
          while ((SYSCTL->PRSSI & SYSCTL_PRSSI_R3) == 0){}    /* wait until SSI is ready */
          break;
      }
      default:
      {
          return false;
      }
    }
    
    // Disable the SSI interface (Set entire register to 0).
    mySSI->CR1 =0;

    // ADD CODE
    // Set SPI clock to 5MHz.
    // Assume that we hvae a 50MHz clock
    // FSSIClk = FSysClk / (CPSDVSR * (1 + SCR))
    // Modify CPSR and CR0
		mySSI->CPSR = 10;
		mySSI->CR0 &=  ~SSI_CR0_SCR_M;
     
		// Configure SPI control0 for freescale format, data width of 8 bits
    mySSI->CR0 =   (SSI_CR0_DSS_8 | SSI_CR0_FRF_MOTO);
    
    // ADD CODE
    // Configure the SPI MODE in CR0
		mySSI->CR0 |= (spi_mode << 6);
    
    //Enable SSI
    mySSI->CR1 |= SSI_CR1_SSE;
    

  return true;
}


//*****************************************************************************
// Transmits the array of bytes found at txData to the specified SPI peripheral
// The number of bytes transmitted is determined by numBytes.
//
// The data received by the SPI ternimal is placed in an array of bytes 
// starting at the address found at rxData
//*****************************************************************************
void spiTx(uint32_t base, uint8_t *txData, int numBytes, uint8_t *rxData)
{
  uint8_t count = 0;
	SSI0_Type *mySSI = (SSI0_Type *) base;
  
  // Wait until the transmit is finished
  while((mySSI->SR & SSI_SR_TFE)!= 1){};

  // Disable the SSI interface
  mySSI->CR1 &= ~SSI_CR1_SSE;
    
  // Fill the Transmit FIFO  
  while((mySSI->SR & SSI_SR_TNF)!= 0 && (count < numBytes) )
  {
    // Send out the first byte
    mySSI->DR = *txData; 
    txData++;
    count++;
  }
                  
  //Enable SSI
  mySSI->CR1 |= SSI_CR1_SSE;
  
  for( count = 0; count < numBytes; count++)
  {
    // Wait until the recieve has finished  
    while((mySSI->SR & SSI_SR_RNE)==0){};// wait until response

    // Store the results  
    *rxData =  mySSI->DR;
    rxData++;
  }
}
