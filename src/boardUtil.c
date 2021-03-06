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
	DisableInterrupts();
	serialDebugInit();
	pushButtonInit();
	lcdInit();
	joyStickInit();
	initialize_spi(SSI0_BASE, 3);
	i2cInit();
	rf_init();
	initialize_timers();
	EnableInterrupts();	
	
}
//*****************************************************************************
//*****************************************************************************
void initialize_timers(void)
{
	SysTick_Config(250000);
	f14_timer0_Init();
	f14_timer4_Init();
	f14_timer3_Init();
	//init 10 second watchdog
	watchdogInit(50000000*10,1);

}

//*****************************************************************************
//*****************************************************************************
void serialDebugInit(void)
{
  // Configure GPIO Pins
  uart0_config_gpio();  
  // Initialize UART0 for 8N1, interrupts enabled.
  uart0_init_115K();
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

		initializeADC(ADC0_BASE);
		initializeADC(ADC1_BASE);
	
}

//*****************************************************************************
//*****************************************************************************
void rf_init(void)
{
	GPIOA_Type *gpioPort;
	
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
  
  // Enable RF Interrupts
  gpio_enable_port(RF_IRQ_GPIO_BASE);
  gpio_config_digital_enable(RF_IRQ_GPIO_BASE,RF_IRQ_PIN);
	gpio_config_enable_input(RF_IRQ_GPIO_BASE,RF_IRQ_PIN);
	
	gpioPort = (GPIOA_Type *)RF_IRQ_GPIO_BASE;
	gpioPort->IM = 0x00;
	gpioPort->IS &= (0 << 7);
	gpioPort->IBE &= (0 << 7);
	gpioPort->IEV &= (0 << 7);
	gpioPort->ICR = RF_IRQ_PIN;
	gpioPort->IM = RF_IRQ_PIN;
	
	NVIC_SetPriority(GPIOD_IRQn,1);
	NVIC_EnableIRQ(GPIOD_IRQn);
	
  initialize_spi(RF_SPI_BASE, 0);
    
  RF_CE_PERIH->DATA |= (1 << 1);
  

}

void lcdInit(void)
{
		gpio_enable_port(GPIOA_BASE);
		gpio_enable_port(GPIOC_BASE);
		gpio_config_digital_enable(GPIOA_BASE, (PA4 | PA2 | PA3 | PA5));
		gpio_config_digital_enable(GPIOC_BASE, PC7);
		gpio_config_enable_output(GPIOC_BASE, PC7);
		gpio_config_enable_output(GPIOA_BASE, PA4);
		//gpio_config_enable_output(GPIOA_BASE, (PA4 | PA2 | PA3 | PA5));
		gpio_config_alternate_function(GPIOA_BASE, (PA2 | PA3 | PA5));
		gpio_config_port_control(GPIOA_BASE, (GPIO_PCTL_PA3_SSI0FSS | GPIO_PCTL_PA2_SSI0CLK | GPIO_PCTL_PA5_SSI0TX));
		lcd_set_pin_config (SSI0_BASE, GPIOC_BASE, PC7, GPIOA_BASE, PA4);
}

void i2cInit(void)
{
	gpio_enable_port(I2C_GPIO_BASE);
	
	//configure SCL
	gpio_config_digital_enable(I2C_GPIO_BASE, I2C_SCL_PIN);
	gpio_config_alternate_function(I2C_GPIO_BASE, I2C_SCL_PIN);
	gpio_config_port_control(I2C_GPIO_BASE, I2C_SCL_PIN_PCTL);
	
	//configure SDA
	gpio_config_digital_enable(I2C_GPIO_BASE, I2C_SDA_PIN);
	gpio_config_open_drain(I2C_GPIO_BASE, I2C_SDA_PIN);
	gpio_config_alternate_function(I2C_GPIO_BASE, I2C_SDA_PIN);
	gpio_config_port_control(I2C_GPIO_BASE, I2C_SDA_PIN_PCTL);
	
	initializeI2CMaster(I2C1_BASE);
	ioExpanderInit(I2C1_BASE);
}
