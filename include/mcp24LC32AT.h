#ifndef __MCP24LC32AT_H__
#define __MCP24LC32AT_H__


#include <stdint.h>
#include "i2c.h"


#define MCP24LC32AT_DEV_ID    0xA0


i2c_status_t mcp_24LC32AT_byte_write
( 
  uint32_t  i2c_base,
  uint16_t  eepromDataAddress,
  uint8_t   data
);

i2c_status_t mcp_24LC32AT_byte_read
( 
  uint32_t  i2c_base,
  uint16_t  address,
  uint8_t   *data
);


#endif
