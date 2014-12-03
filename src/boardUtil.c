#include "TM4C123GH6PM.h"
#include "boardUtil.h"


void DisableInterrupts(void)
{
  __asm {
         CPSID  I
  }
}
void EnableInterrupts(void)
{
  __asm {
    CPSIE  I
  }
}

void f14_project_boardUtil(void){
	
	uart0_config_gpio();
}

//*****************************************************************************
// Configure PA0 and PA1 to be UART pins
//*****************************************************************************
void uart0_config_gpio(void)
{
   gpio_enable_port(GPIOA_BASE);
   gpio_config_digital_enable( GPIOA_BASE, PA0 | PA1);
   gpio_config_alternate_function( GPIOA_BASE, PA0 | PA1);
   gpio_config_port_control( GPIOA_BASE, GPIO_PCTL_PA0_U0RX | GPIO_PCTL_PA1_U0TX);
}

//*****************************************************************************
//*****************************************************************************
void serialDebugInit(void)
{
  uart0_config_gpio();
  uart0_init_115K();
}

//*****************************************************************************
//*****************************************************************************
void pushButtonInit (void)
{		
		//****Configure push buttons*****
		//*******************************
		// Enable port F for push puttons
		gpio_enable_port(GPIOF_BASE);
		
		// configure the pushbuttons as digital pins
		gpio_config_digital_enable(GPIOF_BASE, PF1 | PF2 | PF3 | PF4);
		
		// Eanable push buttons up as input
		gpio_config_enable_input(GPIOF_BASE, PF1 | PF2 | PF3 | PF4);
		
		// Enable the pushbuttons with internal pull-up resistors
		gpio_config_enable_pullup(GPIOF_BASE, PF1 | PF2 | PF3 | PF4);
	
		//******Configure PS2 button*****
		//*******************************
				// Enable port F for push puttons
		gpio_enable_port(GPIOE_BASE);
		
		// configure the pushbuttons as digital pins
		gpio_config_digital_enable(GPIOE_BASE, PE0);
		
		// Eanable push buttons up as input
		gpio_config_enable_input(GPIOE_BASE, PE0);
		
		// Enable the pushbuttons with internal pull-up resistors
		gpio_config_enable_pullup(GPIOE_BASE, PE0);
}

//*****************************************************************************
//*****************************************************************************
void joyStickInit (void)
{
		// Eanble port E for the Joy-Stick
		gpio_enable_port(GPIOE_BASE);
		
		// Enable the ps2 x-dir as input
		gpio_config_enable_input(GPIOE_BASE, PE2 | PE3);
	
		// configure as anolog 
		gpio_config_analog_enable(GPIOE_BASE, PE2 | PE3);
		
		// configure alternate funtion
		gpio_config_alternate_function(GPIOE_BASE, PE2 | PE3);	
}

void lcdInit (void)
{
		lcd_set_pin_config (SSI0_BASE, GPIOC_BASE, PC7, GPIOA_BASE, PA5);
}
