#include "io_expander.h"

// ADD CODE
// Define the 7-bit Address of the MCP23017.  You will need to examine
// page 8 of data sheet and the schematic to determine this information.  Be careful to note that
// the information in the data sheet provides an 8-bit address.  You need to specify
// the 7-bit address of the device.  
#define MCP23017_DEV_ID			0x20


// ADD CODE
#define IODIRA    0x00
#define IODIRB    0x01
#define IO_EXPANDER_GPIOA   0x12
#define IO_EXPANDER_GPIOB   0x13

#define FIXME   0x00

//*****************************************************************************
// Initializes both the A and B ports of the IO expander to be outputs.
// The IODIRA and IODIRB registers need to be set to 0x00.
//
// Paramters
//    i2c_base:   a valid base address of an I2C peripheral
//*****************************************************************************
void ioExpanderInit(uint32_t i2cBase)
{
  
  //==============================================================
  // Set Slave Address of the MCP23017 
  //==============================================================  
  i2cSetSlaveAddr(i2cBase, MCP23017_DEV_ID, I2C_WRITE);
  
  //==============================================================
  // Set the Direction of IODIRA to be outputs
  // Write 0x00 to IODIRA
  //==============================================================
  // Send the IODIRA Address
  i2cSendByte( i2cBase, IODIRA, I2C_MCS_START | I2C_MCS_RUN );

  // Set PortA to be outputs
  i2cSendByte( i2cBase, IODIRA,  I2C_MCS_RUN | I2C_MCS_STOP );

  //==============================================================
  // Set the Direction of IODIRB to be outputs
  // Write 0x00 to IODIRB
  //==============================================================
  // Send the IODIRB Address
  i2cSendByte( i2cBase, IODIRB, I2C_MCS_START | I2C_MCS_RUN );

  // Set PortB to be outputs
  i2cSendByte( i2cBase, IODIRB, I2C_MCS_RUN | I2C_MCS_STOP ); 
}


//*****************************************************************************
// Writes data to the IO expander to turn the LEDs on/off.
//
// Paramters
//    i2c_base:   a valid base address of an I2C peripheral
//    colNum:     The column number (0-4) that is going to be turned on.  
//                A logic 1 is used to turn on a given column
//    data:       The data representing which LEDs should be turned on.
//*****************************************************************************
void ledMatrixWriteData( uint32_t i2cBase, uint8_t colNum, uint8_t data)
{
  if( i2cBase != 0 && colNum <= 4)
  {
    
    //==============================================================
    // Set Slave Address of the MCP23017 
    //==============================================================  
    i2cSetSlaveAddr(i2cBase, MCP23017_DEV_ID, I2C_WRITE);
    
    //============================================================== 
    // Turn off the LEDs
    // First turn off the active LEDs
    // Write 0x00 to IO_EXPANDER_GPIOA
    //==============================================================
    // Send the GPIOA Address
    i2cSendByte( i2cBase, IO_EXPANDER_GPIOA, I2C_MCS_START | I2C_MCS_RUN);

    // Turn the rows (IO_EXPANDER_GPIOB) off
    i2cSendByte( i2cBase, 0xFF, I2C_MCS_RUN | I2C_MCS_STOP);
    

    //============================================================== 
    //Set the active column on IO_EXPANDER_GPIOB
    // Write (1 << colNum) to IO_EXPANDER_GPIOB
    //============================================================== 
    // Send the GPIOB Address. 
    i2cSendByte( i2cBase, IO_EXPANDER_GPIOB, I2C_MCS_START | I2C_MCS_RUN);

    // Set PortB so column 0 of LED matrix is on
    i2cSendByte( i2cBase, (1 << colNum), I2C_MCS_RUN | I2C_MCS_STOP);
    
    
    //============================================================== 
    //Set the LEDs to turn on to IO_EXPANDER_GPIOA
    // Write 'data' to IO_EXPANDER_GPIOA
    //============================================================== 
    // Send the GPIOA Address.  
    i2cSendByte( i2cBase, IO_EXPANDER_GPIOA, I2C_MCS_START | I2C_MCS_RUN);

    // Turn the LEDs 
    i2cSendByte( i2cBase, data, I2C_MCS_START | I2C_MCS_RUN);
  }
}
