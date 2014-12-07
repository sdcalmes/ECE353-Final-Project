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
	serialDebugInit();
	pushButtonInit();
	joyStickInit();
	lcdInit();
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
  // Configure GPIO Pins
  uart0_config_gpio();
  
  // Configure Circular Buffers
  pc_buffer_init(&UART0_Rx_Buffer , UART0_Rx_Buffer_Array, UART0_BUFFER_SIZE); 
  pc_buffer_init(&UART0_Tx_Buffer , UART0_Tx_Buffer_Array, UART0_BUFFER_SIZE); 
  
  // Initialize UART0 for 8N1, interrupts enabled.
  uart_init_115K(
    UART0_BASE, 
    SYSCTL_RCGCUART_R0, 
    SYSCTL_PRUART_R0, 
    UART0_IRQn,
    1
  );
}

//*****************************************************************************
//*****************************************************************************
void pushButtonInit(void)
{		
		//*******************************
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
	
		//*******************************
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
void joyStickInit(void)
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
#define   RF_GPIO_BASE       GPIOD_BASE
#define   RF_SPI_BASE        SSI1_BASE
#define   RF_CLK_PIN         PD0
#define   RF_MISO_PIN        PD2
#define   RF_MOSI_PIN        PD3

#define   RF_CLK_PIN_PCTL    GPIO_PCTL_PD0_SSI1CLK
#define   RF_MISO_PIN_PCTL   GPIO_PCTL_PD2_SSI1RX
#define   RF_MOSI_PIN_PCTL   GPIO_PCTL_PD3_SSI1TX

#define   RF_CS_BASE         GPIOD_BASE
#define   RF_CS_PIN          PD1

#define   RF_CE_GPIO_BASE     GPIOD_BASE
#define   RF_CE_PIN           PD6
#define   RF_CE_PERIH         GPIOD

#define   RF_IRQ_GPIO_BASE    GPIOD_BASE
#define   RF_IRQ_PIN          PD7

#define   RF_PAYLOAD_SIZE     0x04
#define   RF_CHANNEL          0x02
//*****************************************************************************
//*****************************************************************************
void rf_init(void)
{
  wireless_set_pin_config(
    RF_SPI_BASE,
    RF_PAYLOAD_SIZE,
    RF_CHANNEL,
    RF_CS_BASE,
    RF_CS_PIN,
    RF_CE_GPIO_BASE,
    RF_CE_PIN
  );
  
  gpio_enable_port(RF_GPIO_BASE);
  
  // Configure SPI CLK
  gpio_config_digital_enable(RF_GPIO_BASE, RF_CLK_PIN);
  gpio_config_alternate_function(RF_GPIO_BASE, RF_CLK_PIN);
  gpio_config_port_control(RF_GPIO_BASE, RF_CLK_PIN_PCTL);
  
  // Configure SPI MISO
  gpio_config_digital_enable(RF_GPIO_BASE, RF_MISO_PIN);
  gpio_config_alternate_function(RF_GPIO_BASE, RF_MISO_PIN);
  gpio_config_port_control(RF_GPIO_BASE, RF_MISO_PIN_PCTL);
  
  // Configure SPI MOSI
  gpio_config_digital_enable(RF_GPIO_BASE, RF_MOSI_PIN);
  gpio_config_alternate_function(RF_GPIO_BASE, RF_MOSI_PIN);
  gpio_config_port_control(RF_GPIO_BASE, RF_MOSI_PIN_PCTL);
  
  // Configure CS to be a normal GPIO pin that is controlled 
  // explicitly by software
  gpio_config_digital_enable(RF_CS_BASE,RF_CS_PIN);
  gpio_config_enable_output(RF_CS_BASE,RF_CS_PIN);
  
  // Configure CE Pin as an output
  gpio_enable_port(RF_CE_GPIO_BASE);
  gpio_config_digital_enable(RF_CE_GPIO_BASE,RF_CE_PIN);
  gpio_config_enable_output(RF_CE_GPIO_BASE,RF_CE_PIN);
  
  
  initialize_spi(RF_SPI_BASE, 0);
    
  RF_CE_PERIH->DATA |= (1 << 1);
  

}

void lcdInit(void)
{
		lcd_set_pin_config (SSI0_BASE, GPIOC_BASE, PC7, GPIOA_BASE, PA5);
}
