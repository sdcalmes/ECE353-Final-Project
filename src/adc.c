#include "../include/adc.h"
#include "../include/sysctrl.h"

/******************************************************************************
 * Initializes ADC to use Sample Sequencer #3, triggered by software, no IRQs
 *****************************************************************************/
bool initializeADC(  uint32_t adc_base ){
	ADC0_Type* myAdc;
	
	//Enable clock for adc and wait for peripheral
	SYSCTL->RCGCADC |= SYSCTL_RCGCADC_R0;
	while(!(SYSCTL->PRADC & SYSCTL_PRADC_R0));
	
	myAdc = (ADC0_Type*)adc_base;
	
	//Disable Sample Sequencer 3
	myAdc->ACTSS &= ~ADC_ACTSS_ASEN3;
	
	//Set ADC to be triggered by Timer0A
	myAdc->EMUX |= ADC_EMUX_EM3_TIMER;
	
	//Set to take 16 samples
	myAdc->SAC = 4;
	
	//Configure SS3, so sequence ends after END0
	myAdc->SSCTL3 |= (ADC_SSCTL3_END0 | ADC_SSCTL3_IE0);
	
	//Enable interrupts
	myAdc->IM |= ADC_IM_MASK3;
	
	//Set channel
	myAdc->SSMUX3 = 1;
	
	//Set priority for SS3, and enable interrupt
	NVIC_SetPriority(ADC0SS3_IRQn, 1);
	NVIC_EnableIRQ(ADC0SS3_IRQn);
	
	//enable ss3
	myAdc->ACTSS |= ADC_ACTSS_ASEN3;
	
	//Start SS3
	myAdc->PSSI = ADC_PSSI_SS3;
	return true;
}

/******************************************************************************
 * Reads SSMUX3 for the given ADC.  Busy waits until completion
 *****************************************************************************/
uint32_t getADCValue( uint32_t adc_base, uint8_t channel)
{
  ADC0_Type  *myADC;
  uint32_t result;
  
  if( adc_base == 0)
  {
    return false;
  }
  
  myADC = (ADC0_Type *)adc_base;
  
  myADC->SSMUX3 = channel;          // Set the Channel
  
  myADC->ACTSS |= ADC_ACTSS_ASEN3;  // Enable SS3
  
  myADC->PSSI =   ADC_PSSI_SS3;     // Start SS3
  
  while( (myADC->RIS & ADC_RIS_INR3)  == 0)
  {
    // wait
  }
  
  result = myADC->SSFIFO3 & 0xFFF;    // Read 12-bit data
  
  myADC->ISC  = ADC_ISC_IN3;          // Ack the conversion
  
  return result;
}

