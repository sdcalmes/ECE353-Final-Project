#include "gpioPort.h"
          
//*****************************************************************************
// Verifies that the base address is a valid GPIO base address
//*****************************************************************************
static bool verifyBaseAddr(uint32_t baseAddr)
{
   switch( baseAddr )
   {
     case GPIOA_BASE:
     case GPIOB_BASE:
     case GPIOC_BASE:
     case GPIOD_BASE:
     case GPIOE_BASE:
     case GPIOF_BASE:
     {
       return true;
     }
     default:
     {
       return false;
     }
   }
}

//*****************************************************************************
// Enabling the clock for the port that was passed in.
//    1.  Verify that the address passed in is a valid base address for a 
//        GPIO Port.  See line 1545 of TM4C123GH6PM.h to a list of #defines
//        for valid GPIO Ports.
//
//    2. Turn on the clock for the given port in RGCGPIO
//
//        ../include/sysctrl.h contains many useful
//        #defines that will make your code more readable and less mistake prone.
//        Search for SYSCTL_RCGCGPIO in that file.
//
//        Example 
//        SYSCTL->RCGCGPIO |= SYSCTL_RCGCGPIO_R0;
//
//    2. Wait until the clock is on by checking PRGPIO
//
//        ../include/sysctrl.h contains many useful
//        #defines that will make your code more readable and less mistake prone.
//        Search for SYSCTL_PRGPIO in that file.
//
//        Example 
//        val = SYSCTL->PRGPIO;
//
//    Steps 3 & 4 are only necessary for Ports F and D.
//
//    3. We need to set the LOCK register to 0x4C4F434B.
//
//       Example code:
//       GPIO_PORTF_LOCK_R = 0x4C4F434B ;
//
//    4. Set the commit register
//      
//        Example Code:
//        GPIO_PORTF_CR_R = 0xFF;
//*****************************************************************************
bool  gpio_enable_port(uint32_t baseAddr)
{
  uint32_t rcgc_mask = 0;
  uint32_t pr_mask = 0;
  
  // Verify that the base address and set rcgc_mask and pr_mask
   switch( baseAddr )
   {
     case GPIOA_BASE:
     {
       // ADD CODE
       // Set rcgc_mask and pr_mask for GPIO Port A
       rcgc_mask = SYSCTL_RCGCGPIO_R0;
       pr_mask = SYSCTL_PRGPIO_R0; 
       break;
     }
     case GPIOB_BASE:
     {
       // ADD CODE
       // Set rcgc_mask and pr_mask for GPIO Port B
       rcgc_mask = SYSCTL_RCGCGPIO_R1;
       pr_mask = SYSCTL_PRGPIO_R1; 
       break;
     }
     case GPIOC_BASE:
     {
       // ADD CODE
       // Set rcgc_mask and pr_mask for GPIO Port C
       rcgc_mask = SYSCTL_RCGCGPIO_R2;
       pr_mask = SYSCTL_PRGPIO_R2; 
       break;
     }
     case GPIOD_BASE:
     {
       // ADD CODE
       // Set rcgc_mask and pr_mask for GPIO Port D
       rcgc_mask = SYSCTL_RCGCGPIO_R3;
       pr_mask = SYSCTL_PRGPIO_R3; 
       break;
     }
     case GPIOE_BASE:
     {
       // ADD CODE
       // Set rcgc_mask and pr_mask for GPIO Port E
       rcgc_mask = SYSCTL_RCGCGPIO_R4;
       pr_mask = SYSCTL_PRGPIO_R4; 
       break;
     }
     case GPIOF_BASE:
     {
       // ADD CODE
       // Set rcgc_mask and pr_mask for GPIO Port F
       rcgc_mask = SYSCTL_RCGCGPIO_R5;
       pr_mask = SYSCTL_PRGPIO_R5; 
       break;
     }
     default:
     {
       return false;
     }
   }
   
   // ADD CODE
   // Turn the clock on using the rcgc_mask
   SYSCTL->RCGCGPIO |= rcgc_mask;

   // ADD CODE
   // Wait for the PRGPIO to indicate the port is ready
   while( (SYSCTL->PRGPIO & pr_mask) == 0)
   {
     // do nothing
   }
    
   // If PortD set the LOCK and CR registers
   if(baseAddr == GPIOD_BASE )
  {
     GPIO_PORTD_LOCK_R = 0x4C4F434B ;
     GPIO_PORTD_CR_R = 0xFF;
  }

   // If PortF set the LOCK and CR registers
  if(baseAddr == GPIOF_BASE )

  {
     GPIO_PORTF_LOCK_R = 0x4C4F434B ;
     GPIO_PORTF_CR_R = 0xFF;
  }
  
  return true;
}

//*****************************************************************************
// Setting a pins as a digital enable requires writing to DEN register
//
// Paramters
//    pins  -   A bit mask indicating which pins should be configured as digital
//              pins.  Modify only the bits where the bitmask is equal to 1.
//
// Use section 10.5 of the TM4C123 data sheet to determine the bits to set in 
// the DEN register.
//
//*****************************************************************************
bool  gpio_config_digital_enable(uint32_t baseAddr, uint8_t pins)
{
  GPIOA_Type  *gpioPort;
  
  // ADD CODE
  // Verify that the base address is a valid GPIO base address
  // using the verifyBaseAddr function provided above
  if( verifyBaseAddr(baseAddr) == false)
    {
      return false;
    }
  
  // ADD CODE
  // Type Cast the base address to a GPIOA_Type pointer
  gpioPort = (GPIOA_Type *)baseAddr;
  
  // ADD CODE
  // Turn on the digital enable
  gpioPort->DEN |= pins;
    
  return true;
}

//*****************************************************************************
// Setting a GPIO pin as an output requires setting the DIR register
//
// Paramters
//    pins  -   A bit mask indicating which pins should be configured as output
//              pins.  Modify only the bits where the bitmask is equal to 1.
//
// Use section 10.5 of the TM4C123 data sheet to determine the bits to set in 
// the DIR register.
//*****************************************************************************
bool  gpio_config_enable_output(uint32_t baseAddr, uint8_t pins)
{
  GPIOA_Type  *gpioPort;
  
  // ADD CODE
  // Verify that the base address is a valid GPIO base address
  // using the verifyBaseAddr function provided above
  if( verifyBaseAddr(baseAddr) == false)
    {
      return false;
    }
    
  // ADD CODE
  // Type Cast the base address to a GPIOA_Type pointer
  gpioPort = (GPIOA_Type *)baseAddr;
  
  // ADD CODE
  // Set the pins as outputs
  gpioPort->DIR |= pins;
  return true;
}

//*****************************************************************************
// Setting a GPIO pin as an input requires setting the DIR register
//
// Paramters
//    pins  -   A bit mask indicating which pins should be configured as input
//              pins.  Modify only the bits where the bitmask is equal to 1.
//
// Use section 10.5 of the TM4C123 data sheet to determine the bits to set in 
// the DIR register.
//
//*****************************************************************************
bool  gpio_config_enable_input(uint32_t baseAddr, uint8_t pins)

{
  GPIOA_Type  *gpioPort;

  // ADD CODE
  // Verify that the base address is a valid GPIO base address
  // using the verifyBaseAddr function provided above
  
  if( verifyBaseAddr(baseAddr) == false)
    {
      return false;
    }

  // ADD CODE
  // Type Cast the base address to a GPIOA_Type pointer
  gpioPort = (GPIOA_Type *)baseAddr;

  // ADD CODE
  // Set the pins as inputs
  gpioPort->DIR &= ~pins;
  return true;
}


//*****************************************************************************
// Enabling a pull-up resistor requires setting the PUR regsiter
//
// Paramters
//    baseAddr - Base address of GPIO port that is being enabled.
//    pins  -   A bit mask indicating which pins should be configured with a 
//              pull-up resistor
//*****************************************************************************
bool  gpio_config_enable_pullup(uint32_t baseAddr, uint8_t pins)
{
  GPIOA_Type  *gpioPort;

  // ADD CODE
  // Verify that the base address is a valid GPIO base address
  // using the verifyBaseAddr function provided above
  if( verifyBaseAddr(baseAddr) == false)
    {
      return false;
    }

    // ADD CODE
  // Type Cast the base address to a GPIOA_Type pointer  
  gpioPort = (GPIOA_Type *)baseAddr;

  // ADD CODE
  // Enable the pull-up resistors
  gpioPort->PUR |= pins;
  return true;
}

//*****************************************************************************
// Enabling a pull-up resistor requires setting the PDR regsiter
//
// Paramters
//    baseAddr - Base address of GPIO port that is being enabled.
//    pins  -   A bit mask indicating which pins should be configured with a 
//              pull-down resistor
//*****************************************************************************
bool  gpio_config_enable_pulldown(uint32_t baseAddr, uint8_t pins)
{
  GPIOA_Type  *gpioPort;

  // ADD CODE
  // Verify that the base address is a valid GPIO base address
  // using the verifyBaseAddr function provided above
  if( verifyBaseAddr(baseAddr) == false)
    {
      return false;
    }
    
  // ADD CODE
  // Type Cast the base address to a GPIOA_Type pointer
  gpioPort = (GPIOA_Type *)baseAddr;

  // ADD CODE
  // Enable the pull-down resistors
  gpioPort->PDR |= pins;
  return true;
}


//*****************************************************************************
bool  gpio_config_analog_enable(uint32_t baseAddr, uint8_t pins)
{
  GPIOA_Type  *gpioPort;

  // ADD CODE
  // Verify that the base address is a valid GPIO base address
  // using the verifyBaseAddr function provided above
  if( verifyBaseAddr(baseAddr) == false)
    {
      return false;
    }
    
  // ADD CODE
  // Type Cast the base address to a GPIOA_Type pointer
  gpioPort = (GPIOA_Type *)baseAddr;

  // ADD CODE
  // Enable analog pins
  gpioPort->AMSEL |= pins;
  return true;
}

//*****************************************************************************
bool  gpio_config_alternate_function(uint32_t baseAddr, uint8_t pins)
{
  GPIOA_Type  *gpioPort;

  // ADD CODE
  // Verify that the base address is a valid GPIO base address
  // using the verifyBaseAddr function provided above
  if( verifyBaseAddr(baseAddr) == false)
    {
      return false;
    }
    
  // ADD CODE
  // Type Cast the base address to a GPIOA_Type pointer
  gpioPort = (GPIOA_Type *)baseAddr;

  // ADD CODE
  // Enable alternate function
  gpioPort->AFSEL |= pins;
    
  return true;
}


//*****************************************************************************
bool  gpio_config_port_control(uint32_t baseAddr, uint8_t pins)
{
  GPIOA_Type  *gpioPort;

  // ADD CODE
  // Verify that the base address is a valid GPIO base address
  // using the verifyBaseAddr function provided above
  if( verifyBaseAddr(baseAddr) == false)
    {
      return false;
    }
    
  // ADD CODE
  // Type Cast the base address to a GPIOA_Type pointer
  gpioPort = (GPIOA_Type *)baseAddr;

  // ADD CODE
  // Set the port control register
  gpioPort->PCTL = pins;
    
  return true;
}

//******************************************************************************
bool  gpio_config_open_drain(uint32_t gpioBase, uint8_t pins){
	GPIOA_Type  *gpioPort;
	 // Verify that the base address is a valid GPIO base address
  // using the verifyBaseAddr function provided above
	if(!verifyBaseAddr(gpioBase)){
		return false;
	}

  // Type Cast the base address to a GPIOA_Type pointer 
	gpioPort = (GPIOA_Type *) gpioBase;	
	gpioPort->ODR |= pins;
	return true;
}
