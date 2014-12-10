//*****************************************************************************
// i2c.h
// Author: jkrachey@wisc.edu
//*****************************************************************************

#ifndef __I2C_H__
#define __I2C_H__

#include <stdint.h>
#include <stdbool.h>
#include "TM4C123GH6PM.h"

#define I2C_ACK_WAIT_COUNT    100000

//*****************************************************************************
//
// The following are defines for the bit fields in the I2C_O_MSA register.
//
//*****************************************************************************
#define I2C_MSA_SA_M            0x000000FE  // I2C Slave Address
#define I2C_MSA_RS              0x00000001  // Receive not send
#define I2C_MSA_SA_S            1
#define I2C_MSA_TX              0x00000000  // Transmit Data
#define I2C_MSA_RX              I2C_MSA_RS

//*****************************************************************************
//
// The following are defines for the bit fields in the I2C_O_SOAR register.
//
//*****************************************************************************
#define I2C_SOAR_OAR_M          0x0000007F  // I2C Slave Own Address
#define I2C_SOAR_OAR_S          0

//*****************************************************************************
//
// The following are defines for the bit fields in the I2C_O_SCSR register.
//
//*****************************************************************************
#define I2C_SCSR_OAR2SEL        0x00000008  // OAR2 Address Matched
#define I2C_SCSR_FBR            0x00000004  // First Byte Received
#define I2C_SCSR_TREQ           0x00000002  // Transmit Request
#define I2C_SCSR_DA             0x00000001  // Device Active
#define I2C_SCSR_RREQ           0x00000001  // Receive Request

//*****************************************************************************
//
// The following are defines for the bit fields in the I2C_O_MCS register.
//
//*****************************************************************************
#define I2C_MCS_CLKTO           0x00000080  // Clock Timeout Error
#define I2C_MCS_BUSBSY          0x00000040  // Bus Busy
#define I2C_MCS_IDLE            0x00000020  // I2C Idle
#define I2C_MCS_ARBLST          0x00000010  // Arbitration Lost
#define I2C_MCS_HS              0x00000010  // High-Speed Enable
#define I2C_MCS_ACK             0x00000008  // Data Acknowledge Enable
#define I2C_MCS_DATACK          0x00000008  // Acknowledge Data
#define I2C_MCS_ADRACK          0x00000004  // Acknowledge Address
#define I2C_MCS_STOP            0x00000004  // Generate STOP
#define I2C_MCS_ERROR           0x00000002  // Error
#define I2C_MCS_START           0x00000002  // Generate START
#define I2C_MCS_RUN             0x00000001  // I2C Master Enable
#define I2C_MCS_BUSY            0x00000001  // I2C Busy

//*****************************************************************************
//
// The following are defines for the bit fields in the I2C_O_SDR register.
//
//*****************************************************************************
#define I2C_SDR_DATA_M          0x000000FF  // Data for Transfer
#define I2C_SDR_DATA_S          0

//*****************************************************************************
//
// The following are defines for the bit fields in the I2C_O_MDR register.
//
//*****************************************************************************
#define I2C_MDR_DATA_M          0x000000FF  // Data Transferred
#define I2C_MDR_DATA_S          0

//*****************************************************************************
//
// The following are defines for the bit fields in the I2C_O_MTPR register.
//
//*****************************************************************************
#define I2C_MTPR_HS             0x00000080  // High-Speed Enable
#define I2C_MTPR_TPR_M          0x0000007F  // SCL Clock Period
#define I2C_MTPR_TPR_S          0

//*****************************************************************************
//
// The following are defines for the bit fields in the I2C_O_SIMR register.
//
//*****************************************************************************
#define I2C_SIMR_STOPIM         0x00000004  // Stop Condition Interrupt Mask
#define I2C_SIMR_STARTIM        0x00000002  // Start Condition Interrupt Mask
#define I2C_SIMR_DATAIM         0x00000001  // Data Interrupt Mask

//*****************************************************************************
//
// The following are defines for the bit fields in the I2C_O_SRIS register.
//
//*****************************************************************************
#define I2C_SRIS_STOPRIS        0x00000004  // Stop Condition Raw Interrupt
                                            // Status
#define I2C_SRIS_STARTRIS       0x00000002  // Start Condition Raw Interrupt
                                            // Status
#define I2C_SRIS_DATARIS        0x00000001  // Data Raw Interrupt Status

//*****************************************************************************
//
// The following are defines for the bit fields in the I2C_O_MIMR register.
//
//*****************************************************************************
#define I2C_MIMR_CLKIM          0x00000002  // Clock Timeout Interrupt Mask
#define I2C_MIMR_IM             0x00000001  // Master Interrupt Mask

//*****************************************************************************
//
// The following are defines for the bit fields in the I2C_O_MRIS register.
//
//*****************************************************************************
#define I2C_MRIS_CLKRIS         0x00000002  // Clock Timeout Raw Interrupt
                                            // Status
#define I2C_MRIS_RIS            0x00000001  // Master Raw Interrupt Status

//*****************************************************************************
//
// The following are defines for the bit fields in the I2C_O_SMIS register.
//
//*****************************************************************************
#define I2C_SMIS_STOPMIS        0x00000004  // Stop Condition Masked Interrupt
                                            // Status
#define I2C_SMIS_STARTMIS       0x00000002  // Start Condition Masked Interrupt
                                            // Status
#define I2C_SMIS_DATAMIS        0x00000001  // Data Masked Interrupt Status

//*****************************************************************************
//
// The following are defines for the bit fields in the I2C_O_SICR register.
//
//*****************************************************************************
#define I2C_SICR_STOPIC         0x00000004  // Stop Condition Interrupt Clear
#define I2C_SICR_STARTIC        0x00000002  // Start Condition Interrupt Clear
#define I2C_SICR_DATAIC         0x00000001  // Data Interrupt Clear

//*****************************************************************************
//
// The following are defines for the bit fields in the I2C_O_MMIS register.
//
//*****************************************************************************
#define I2C_MMIS_CLKMIS         0x00000002  // Clock Timeout Masked Interrupt
                                            // Status
#define I2C_MMIS_MIS            0x00000001  // Masked Interrupt Status

//*****************************************************************************
//
// The following are defines for the bit fields in the I2C_O_MICR register.
//
//*****************************************************************************
#define I2C_MICR_CLKIC          0x00000002  // Clock Timeout Interrupt Clear
#define I2C_MICR_IC             0x00000001  // Master Interrupt Clear

//*****************************************************************************
//
// The following are defines for the bit fields in the I2C_O_SOAR2 register.
//
//*****************************************************************************
#define I2C_SOAR2_OAR2EN        0x00000080  // I2C Slave Own Address 2 Enable
#define I2C_SOAR2_OAR2_M        0x0000007F  // I2C Slave Own Address 2
#define I2C_SOAR2_OAR2_S        0

//*****************************************************************************
//
// The following are defines for the bit fields in the I2C_O_MCR register.
//
//*****************************************************************************
#define I2C_MCR_SFE             0x00000020  // I2C Slave Function Enable
#define I2C_MCR_MFE             0x00000010  // I2C Master Function Enable
#define I2C_MCR_LPBK            0x00000001  // I2C Loopback

//*****************************************************************************
//
// The following are defines for the bit fields in the I2C_O_SACKCTL register.
//
//*****************************************************************************
#define I2C_SACKCTL_ACKOVAL     0x00000002  // I2C Slave ACK Override Value
#define I2C_SACKCTL_ACKOEN      0x00000001  // I2C Slave ACK Override Enable

//*****************************************************************************
//
// The following are defines for the bit fields in the I2C_O_MCLKOCNT register.
//
//*****************************************************************************
#define I2C_MCLKOCNT_CNTL_M     0x000000FF  // I2C Master Count
#define I2C_MCLKOCNT_CNTL_S     0

//*****************************************************************************
//
// The following are defines for the bit fields in the I2C_O_MBMON register.
//
//*****************************************************************************
#define I2C_MBMON_SDA           0x00000002  // I2C SDA Status
#define I2C_MBMON_SCL           0x00000001  // I2C SCL Status

//*****************************************************************************
//
// The following are defines for the bit fields in the I2C_O_PP register.
//
//*****************************************************************************
#define I2C_PP_HS               0x00000001  // High-Speed Capable

//*****************************************************************************
//
// The following are defines for the bit fields in the I2C_O_PC register.
//
//*****************************************************************************
#define I2C_PC_HS               0x00000001  // High-Speed Capable


typedef enum {
  I2C_OK, 
  I2C_NULL_PTR, 
  I2C_BUS_ERROR,
  I2C_ARBLST,
  I2C_ACK_RXED,
  I2C_NO_ACK,
  I2C_INVALID_BASE
} i2c_status_t;

typedef enum {
  I2C_READ  = I2C_MSA_RX,
  I2C_WRITE = I2C_MSA_TX
} i2c_read_write_t;


typedef struct {
  uint32_t    BaseAddr;
} I2C_CONFIG;

//*****************************************************************************
// Initializes a given I2C peripheral to operate at 100KHz.  This assumes
// MCU core is running at 50MHz
//
// Paramters:
//    base_addr:  The base address of the I2C peripheral that is being
//                configured
//
// Return Value:
//    Returns I2C_OK if the base address is a valid I2C peripheral
//    Returns I2C_INVALID_BASE if the base address is not a valid I2C address
//*****************************************************************************
i2c_status_t initializeI2CMaster(uint32_t base_addr);

//*****************************************************************************
// Sets the slave address that is currently being addressed.
//
// Paramters:
//    baseAddr:  The base address of the I2C peripheral that is being
//                configured
//    slaveAddr: The address of the slave device being accessed.  This is a 
//                7-bit slave address
//    readWrite: If the the transaction will be a read or write operation.
//               read = 0x01.  write = 0x00
// Return Value:
//    Returns I2C_OK if the base address is a valid I2C peripheral
//    Returns I2C_INVALID_BASE if the base address is not a valid I2C address
//*****************************************************************************
i2c_status_t i2cSetSlaveAddr(
  uint32_t baseAddr, 
  uint8_t slaveAddr,
  i2c_read_write_t readWrite
);


//*****************************************************************************
// Initiates a stop condition.  This function is used when the master does
// not receive and ACK.
//
// Paramters:
//    baseAddr:  The base address of the I2C peripheral that is being
//                configured
// Return Value:
//    Returns I2C_OK if the base address is a valid I2C peripheral
//    Returns I2C_INVALID_BASE if the base address is not a valid I2C address
//*****************************************************************************
i2c_status_t i2cStop(
  uint32_t baseAddr
)  ;

//*****************************************************************************
// Sends one byte of data over a I2C bus.  
//
// Paramters:
//    baseAddr:  The base address of the I2C peripheral that is being
//                configured
//    byte:      The next byte of the data transaction.
//    mcs:       Sets master control register of the I2C peripheral. Since a
//               data transaction can consist of multiple bytes, the value
//               of mcs is used to determine when start and stop bits are 
//               generated.
//
// Examples:
//    Sending control word (i2c address) + write 1st byte of data. This
//    assumes that additional bytes will follow in the transaction
//    i2cSendByte(I2C0_BASE, byte, I2C_MCS_START | I2C_MCS_RUN);
//
//    Sending a byte in the middle of a multi-byte operation. (> 2 bytes)
//    i2cSendByte(I2C0_BASE, byte, I2C_MCS_RUN);
//
//    Sending final byte  of data
//    i2cSendByte(I2C0_BASE, byte, I2C_MCS_RUN | I2C_MCS_STOP);
//
//    Sending control word (i2c address) + a single byte transaction.
//    i2cSendByte(I2C0_BASE, byte, I2C_MCS_START | I2C_MCS_RUN | I2C_MCS_STOP);
//
// Return Value:
//    Returns I2C_OK if the base address is a valid and the data was 
//    transmitted sucessfully.
//*****************************************************************************
i2c_status_t i2cSendByte(
  uint32_t baseAddr, 
  uint8_t byte, 
  uint8_t mcs
);

//*****************************************************************************
// Reads one byte of data over a I2C bus.  
//
// Paramters:
//    baseAddr:  The base address of the I2C peripheral that is being
//                configured
//    data:      The data read by the transaction.
//    mcs:       Sets master control register of the I2C peripheral. Since a
//               data transaction can consist of multiple bytes, the value
//               of mcs is used to determine when start and stop bits are 
//               generated.
//
// Examples:
//    * Sending control word (i2c address) + read 1st byte of data. This
//    * assumes that additional bytes be read after this byte.  This
//    * would be used for reading multiple bytes at consecutive addresses
//    * in the slave address.  
//    i2cGetByte(I2C0_BASE, byte, I2C_MCS_START | I2C_MCS_RUN);
//
//    * Reading a byte in the middle of a multi-byte operation. (> 2 bytes)
//    i2cGetByte(I2C0_BASE, byte, I2C_MCS_RUN);
//
//    * Reading final byte of data in a multi-byte read 
//    i2cGetByte(I2C0_BASE, byte, I2C_MCS_RUN | I2C_MCS_STOP);
//
//    * Sending control word (i2c address) + reading a single byte read.
//    i2cGetByte(I2C0_BASE, byte, I2C_MCS_START | I2C_MCS_RUN | I2C_MCS_STOP);
//
// Return Value:
//    Returns I2C_OK if the base address is a valid and the data was 
//    transmitted sucessfully.
//*****************************************************************************
i2c_status_t i2cGetByte(
  uint32_t baseAddr, 
  uint8_t *data, 
  uint8_t mcs
) ;

//*****************************************************************************
// Determines if the last byte of data transmitted was ACKed.  
//
// Paramters:
//    baseAddr:  The base address of the I2C peripheral that is being accessed
//
// Returns
//    Returns true if the data was ACKed
//    Returns false if the data was not ACKed or i2c_base is invalid
//*****************************************************************************
bool
I2CMasterDatAck(
uint32_t i2c_base
);

//*****************************************************************************
// Determines if the address (control word) was ACKed.  
//
// Paramters:
//    baseAddr:  The base address of the I2C peripheral that is being accessed
//
// Returns
//    Returns true if the address was ACKed
//    Returns false if the address was not ACKed or i2c_base is invalid
//*****************************************************************************
bool
I2CMasterAdrAck(
uint32_t i2c_base
);

//*****************************************************************************
// Determines if the I2C device is busy transmitting data.  
//
// Paramters:
//    baseAddr:  The base address of the I2C peripheral that is being accessed
//
// Returns
//    Returns true if the I2C device is busy
//    Returns false if the I2C device is NOT busy or i2c_base is invalid
//*****************************************************************************
bool
I2CMasterBusy(
uint32_t i2c_base
);

//*****************************************************************************
// verifies if the base addressed passed to a function is a valid I2C address
//*****************************************************************************
bool
i2cVerifyBaseAddr(
  uint32_t i2c_base
);

#endif
