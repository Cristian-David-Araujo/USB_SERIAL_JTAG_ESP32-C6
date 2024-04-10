/**
 * @file USB_SERIAL_JTAG_ESP32-C6_LIB.h
 * @author Cristian David Araujo A. (cristian.araujo@udea.edu.co)
 * @brief Hardware library for ESP32-C6 USB Serial JTAG Controller
 * @version 0.1
 * @date 2024-03-29
 * 
 * @copyright Unlicensed
 * 
 * This header file declarates the data types, constants, macros, and the module structure
 * for controlling the memory mapped register for the Bus Fabric module. The defined data 
 * structures follow a standard naming notation.
 * 
 * The naming notation is as follows:
 * 
 * MODULE STRUCTURE                 ==>   s + MODULEname + [MODULEnumber]
 * MMIO REGISTER                    ==>   r + MODULEname + [MODULEnumber] + _ + REGISTERname + [REGISTERnumber]
 * MMIO REGISTER ATOMIC WRITE XOR   ==>   xor + MODULEname + [MODULEnumber] + _ + REGISTERname + [REGISTERnumber]
 * MMIO REGISTER ATOMIC WRITE SET   ==>   set + MODULEname + [MODULEnumber] + _ + REGISTERname + [REGISTERnumber]
 * MMIO REGISTER ATOMIC WRITE CLR   ==>   clr + MODULEname + [MODULEnumber] + _ + REGISTERname + [REGISTERnumber]
 * REGISTER BITFIELD or BIT         ==>   b + MODULEname + [MODULEnumber] + _ + BITFIELDname
 * BITFIELD CONTANT VALUEs          ==>   k + MODULEname + _ + BITFIELDname + _ + CONSTANTname
 * MODULE MASKs                     ==>   m + MODULEname + _ + MASKname
 * REGISTER TYPE                    ==>   __ + MODULEname + _ + REGISTERname + _t
 * STRUCTURE TYPE                   ==>   __ + MODULEname + _ + _t
 * 
 * The structure of this file is as follows:
 * 
 * 1. Register definition
 *    a. Data type
 *    b. Register masks
 *    c. Bitifield constant values
 * 2. Module structure definition
 *    a. Data type
 *    b. Module masks
 *    c. Structure access macro
 * 3. Register access macros
 *    a. Whole register access macro
 *    b. Bitfields access macro
 * 
 * 
 *  
 */

#ifndef USB_SERIAL_JTAG_ESP32_C6_LIB_H
#define USB_SERIAL_JTAG_ESP32_C6_LIB_H

#include <stdint.h>

/********************************************************************************************************************************
************************************************** Configuration Registers ******************************************************
*********************************************************************************************************************************/

/**
 * \typedef __usbSerialJtag_ep1Reg_t
 * FIFO access for the CDC-ACM data IN and OUT endpoints
 */
typedef union {
    uint32_t WORD;
    struct {
        uint32_t RDWR_BYTE: 8; // 0-7 (R/W)  Write or read byte data to or from UART TX/RX FIFO
        uint32_t RESERVED: 24; // 8-31
    } BITS;
} __usbSerialJtag_ep1Reg_t;

/**
 * Masks definition for the __usbSerialJtag_ep1Reg_t register
 */
#define mUSBSERIALJTAG_EP1REG_RDWR_BYTE 0x000000FFUL // Set/Get (R/W) Write or read byte data to or from UART TX/RX FIFO
#define mUSBSERIALJTAG_EP1REG_RESET 0x00000000UL // Reset value for the __usbSerialJtag_ep1Reg_t register


/**
 * \typedef __usbSerialJtag_ep1ConfReg_t
 * Configuration and control registers forthe CDC-ACM FIFOs
 */
typedef union {
    uint32_t WORD;
    struct {
        uint32_t WR_DONE: 1; // 0 (WT)  Configures whether to represent writing byte data to UART TX FIFO is done
        uint32_t SERIAL_IN_EP_DATA_FREE: 1; // 1 (RO)  Represents whether UART TX FIFO has space available
        uint32_t SERIAL_OUT_EP_DATA_AVAIL: 1; // 2 (RO)  Represents whether there is data in UART RX FIFO
        uint32_t RESERVED: 29; // 3-31
    } BITS;
} __usbSerialJtag_ep1ConfReg_t;

/**
 * Masks definition for the __usbSerialJtag_ep1ConfReg_t register
 */
#define mUSBSERIALJTAG_EP1CONFREG_WR_DONE 0x00000001UL // Set (WT) the WR_DONE field of the __usbSerialJtag_ep1ConfReg_t register
#define mUSBSERIALJTAG_EP1CONFREG_SERIAL_IN_EP_DATA_FREE 0x00000002UL // Get (RO) Represents whether UART TX FIFO has space available
#define mUSBSERIALJTAG_EP1CONFREG_SERIAL_OUT_EP_DATA_AVAIL 0x00000004UL // Get (RO) Represents whether there is data in UART RX FIFO
#define mUSBSERIALJTAG_EP1CONFREG_RESET 0x00000002UL // Reset value for the __usbSerialJtag_ep1ConfReg_t register


/**
 * \typedef __usbSerialJtag_conf0Reg_t;
 * PHY hardware configuration
 */
typedef union {
    uint32_t WORD;
    struct {
        uint32_t PHY_SEL: 1; // 0 (R/W)  Configures whether to select internal or external PHY
        uint32_t EXCHG_PINS_OVERRIDE: 1; // 1 (R/W)  Configures whether to enable software control USB D+ D- exchange
        uint32_t EXCHG_PINS: 1; // 2 (R/W)  Configures whether to enable USB D+ D- exchange
        uint32_t VREFH: 2; // 3-4 (R/W) Configures single-end input high threshold
        uint32_t VREFL: 2; // 5-6 (R/W) Configures single-end input low threshold
        uint32_t VREF_OVERRIDE: 1; // 7 (R/W)  Configures whether to enable software control input thresh-old
        uint32_t PAD_PULL_OVERRIDE: 1; // 8 (R/W)  Configures whether to enable software to control USB D+ D- pullup and pulldown
        uint32_t DP_PULLUP: 1; // 9 (R/W)  Configures whether to enable USB D+ pull up when PAD_PULL_OVERRIDE is 1
        uint32_t DP_PULLDOWN: 1; // 10 (R/W) Configures whether to enable USB D+ pull down when PAD_PULL_OVERRIDE is 1
        uint32_t DM_PULLUP: 1; // 11 (R/W) Configures whether to enable USB D- pull up when PAD_PULL_OVERRIDE is 1
        uint32_t DM_PULLDOWN: 1; // 12 (R/W) Configures whether to enable USB D- pull down when PAD_PULL_OVERRIDE is 1
        uint32_t PULLUP_VALUE: 1; // 13 (R/W) Configures the pull up value when PAD_PULL_OVERRIDE is 1
        uint32_t USB_PAD_ENABLE: 1; // 14 (R/W) Configures whether to enable USB pad function
        uint32_t USB_JTAG_BRIDGE_EN: 1; // 15 (R/W) Configures whether to disconnect usb_jtag and in-ternal JTAG
        uint32_t RESERVED: 16; // 16-31
    } BITS;
} __usbSerialJtag_conf0Reg_t;

/**
 * Masks definition for the __usbSerialJtag_conf0Reg_t register
 */
#define mUSBSERIALJTAG_CONF0REG_PHY_SEL 0x00000001UL // Set/Get (R/W) Configures whether to select internal or external PHY
#define mUSBSERIALJTAG_CONF0REG_EXCHG_PINS_OVERRIDE 0x00000002UL // Set/Get (R/W) Configures whether to enable software control USB D+ D- exchange
#define mUSBSERIALJTAG_CONF0REG_EXCHG_PINS 0x00000004UL // Set/Get (R/W) Configures whether to enable USB D+ D- exchange
#define mUSBSERIALJTAG_CONF0REG_VREFH 0x00000018UL // Set/Get (R/W) Configures single-end input high threshold
#define mUSBSERIALJTAG_CONF0REG_VREFL 0x00000060UL // Set/Get (R/W) Configures single-end input low threshold
#define mUSBSERIALJTAG_CONF0REG_VREF_OVERRIDE 0x00000080UL // Set/Get (R/W) Configures whether to enable software control input thresh-old
#define mUSBSERIALJTAG_CONF0REG_PAD_PULL_OVERRIDE 0x00000100UL // Set/Get (R/W) Configures whether to enable software to control USB D+ D- pullup and pulldown
#define mUSBSERIALJTAG_CONF0REG_DP_PULLUP 0x00000200UL // Set/Get (R/W) Configures whether to enable USB D+ pull up when PAD_PULL_OVERRIDE is 1
#define mUSBSERIALJTAG_CONF0REG_DP_PULLDOWN 0x00000400UL // Set/Get (R/W) Configures whether to enable USB D+ pull down when PAD_PULL_OVERRIDE is 1
#define mUSBSERIALJTAG_CONF0REG_DM_PULLUP 0x00000800UL // Set/Get (R/W) Configures whether to enable USB D- pull up when PAD_PULL_OVERRIDE is 1
#define mUSBSERIALJTAG_CONF0REG_DM_PULLDOWN 0x00001000UL // Set/Get (R/W) Configures whether to enable USB D- pull down when PAD_PULL_OVERRIDE is 1
#define mUSBSERIALJTAG_CONF0REG_PULLUP_VALUE 0x00002000UL // Set/Get (R/W) Configures the pull up value when PAD_PULL_OVERRIDE is 1
#define mUSBSERIALJTAG_CONF0REG_USB_PAD_ENABLE 0x00004000UL // Set/Get (R/W) Configures whether to enable USB pad function
#define mUSBSERIALJTAG_CONF0REG_USB_JTAG_BRIDGE_EN 0x00008000UL // Set/Get (R/W) Configures whether to disconnect usb_jtag and in-ternal JTAG
#define mUSBSERIALJTAG_CONF0REG_RESET 0x00004200UL // Reset value for the __usbSerialJtag_conf0Reg_t register
/**
 * Constant definitions for the __usbSerialJtag_conf0Reg_t register
 */
#define kUSBSERIALJTAG_CONF0REG_PHY_SEL_InternalPHY 0 // Constant value to set the PHY_SEL field
#define kUSBSERIALJTAG_CONF0REG_PHY_SEL_ExternalPHY 1 // Constant value to set the PHY_SEL field
#define kUSBSERIALJTAG_CONF0REG_VREFH_1V76 0 // Constant value to set the VREFH field
#define kUSBSERIALJTAG_CONF0REG_VREFH_1V84 1 // Constant value to set the VREFH field
#define kUSBSERIALJTAG_CONF0REG_VREFH_1V92 2 // Constant value to set the VREFH field
#define kUSBSERIALJTAG_CONF0REG_VREFH_2V00 3 // Constant value to set the VREFH field
#define kUSBSERIALJTAG_CONF0REG_VREFL_0V80 0 // Constant value to set the VREFL field
#define kUSBSERIALJTAG_CONF0REG_VREFL_0V88 1 // Constant value to set the VREFL field
#define kUSBSERIALJTAG_CONF0REG_VREFL_0V96 2 // Constant value to set the VREFL field
#define kUSBSERIALJTAG_CONF0REG_VREFL_1V04 3 // Constant value to set the VREFL field
#define kUSBSERIALJTAG_CONF0REG_PULLUP_VALUE_2K2 0 // Constant value to set the PULLUP_VALUE field
#define kUSBSERIALJTAG_CONF0REG_PULLUP_VALUE_1K1 1 // Constant value to set the PULLUP_VALUE field
#define kUSBSERIALJTAG_CONF0REG_JTAG_BRIDGE_EN_CONNECTEC 0 //  Constant value to set the USB_JTAG_BRIDGE_EN field - usb_jtag is connected to the internal JTAG port of CPU
#define kUSBSERIALJTAG_CONF0REG_JTAG_BRIDGE_EN_DISCONNECTED 1 //  Constant value to set the USB_JTAG_BRIDGE_EN field - usb_jtag and the internal JTAG are disconnected, MTMS, MTDI, and MTCK are output through GPIO Matrix, and MTDO is input through GPIO Matrix




/**
 * \typedef __usbSerialJtag_testReg_t
 * Registers used for debugging the PHY
 */
typedef union {
    uint32_t WORD;
    struct {
        uint32_t TEST_ENABLE: 1; // 0 (R/W)  Configures whether to enable the test mode of the USB pad
        uint32_t TEST_USB_OE: 1; // 1 (R/W)  Configures whether to enable USB pad output
        uint32_t TEST_TX_DP: 1; // 2 (R/W)  Configures value of USB D+ in test mode when TEST_USB_OE is 1
        uint32_t TEST_TX_DM: 1; // 3 (R/W)  Configures value of USB D- in test mode when TEST_USB_OE is 1
        uint32_t TEST_RX_RCV: 1; // 4 (RO)  Represents the current logical level of the voltage difference between USB D- and USB D+ pads in test mode
        uint32_t TEST_RX_DP: 1; // 5 (RO)  Represents the logical level of the USB D+ pad in test mode
        uint32_t TEST_RX_DM: 1; // 6 (RO)  Represents the logical level of the USB D- pad in test mode
        uint32_t RESERVED: 25; // 7-31
    } BITS;
} __usbSerialJtag_testReg_t;

/**
 * Masks definition for the __usbSerialJtag_testReg_t register
 */
#define mUSBSERIALJTAG_TESTREG_TEST_ENABLE 0x00000001UL // Set/Get (R/W) Configures whether to enable the test mode of the USB pad
#define mUSBSERIALJTAG_TESTREG_TEST_USB_OE 0x00000002UL // Set/Get (R/W) Configures whether to enable USB pad output
#define mUSBSERIALJTAG_TESTREG_TEST_TX_DP 0x00000004UL // Set/Get (R/W) Configures value of USB D+ in test mode when TEST_USB_OE is 1
#define mUSBSERIALJTAG_TESTREG_TEST_TX_DM 0x00000008UL // Set/Get (R/W) Configures value of USB D- in test mode when TEST_USB_OE is 1
#define mUSBSERIALJTAG_TESTREG_TEST_RX_RCV 0x00000010UL // Get (RO) Represents the current logical level of the voltage difference between USB D- and USB D+ pads in test mode
#define mUSBSERIALJTAG_TESTREG_TEST_RX_DP 0x00000020UL // Get (RO) Represents the logical level of the USB D+ pad in test mode
#define mUSBSERIALJTAG_TESTREG_TEST_RX_DM 0x00000040UL // Get (RO) Represents the logical level of the USB D- pad in test mode
#define mUSBSERIALJTAG_TESTREG_RESET 0x00000030UL // Reset value for the __usbSerialJtag_testReg_t register


/**
 * \typedef __usbSerialJtag_miscConfReg_t
 * Clock enable control
 */
typedef union {
    uint32_t WORD;
    struct {
        uint32_t CLK_EN: 1; // 0 (R/W)  Configures whether to force clock on for register
        uint32_t RESERVED: 31; // 1-31
    } BITS;
} __usbSerialJtag_miscConfReg_t;

/**
 * Masks definition for the __usbSerialJtag_miscConfReg_t register
 */
#define mUSBSERIALJTAG_MISCCONFREG_CLK_EN 0x00000001UL // Set/Get (R/W) Configures whether to force clock on for register
#define mUSBSERIALJTAG_MISCCONFREG_RESET 0x00000000UL // Reset value for the __usbSerialJtag_miscConfReg_t register


/**
 * \typedef __usbSerialJtag_memConfReg_t
 * Memory power control
 */
typedef union {
    uint32_t WORD;
    struct {
        uint32_t USB_MEM_PD: 1; // 0 (R/W)  Configures whether to power down USB memory
        uint32_t USB_MEM_CLK_EN: 1; // 1 (R/W)  Configures whether to force clock on for USB memory
        uint32_t RESERVED: 30; // 2-31
    } BITS;
} __usbSerialJtag_memConfReg_t;

/**
 * Masks definition for the __usbSerialJtag_memConfReg_t register
 */
#define mUSBSERIALJTAG_MEMCONFREG_USB_MEM_PD 0x00000001UL // Set/Get (R/W) Configures whether to power down USB memory
#define mUSBSERIALJTAG_MEMCONFREG_USB_MEM_CLK_EN 0x00000002UL // Set/Get (R/W) Configures whether to force clock on for USB memory
#define mUSBSERIALJTAG_MEMCONFREG_RESET 0x00000002UL // Reset value for the __usbSerialJtag_memConfReg_t register


/**
 * \typedef __usbSerialJtag_chipRstReg_t
 * @brief ACM chip reset control
 */
typedef union {
    uint32_t WORD;
    struct {
        uint32_t JTAG_RTS: 1; // 0 (RO)  Represents the state of RTS signal as set by the most recent SET_LINE_CODING command
        uint32_t JTAG_DTR: 1; // 1 (RO)  Represents the state of DTR signal as set by the most recent SET_LINE_CODING command
        uint32_t USB_UART_CHIP_RST_DIS: 1; // 2 (R/W)  Configures whether to disable chip reset from USB serial channel
        uint32_t RESERVED: 29; // 3-31
    } BITS;
} __usbSerialJtag_chipRstReg_t;

/**
 * Masks definition for the __usbSerialJtag_chipRstReg_t register
 */
#define mUSBSERIALJTAG_CHIPRSTREG_JTAG_RTS 0x00000001UL // Get (RO) Represents the state of RTS signal as set by the most recent SET_LINE_CODING command
#define mUSBSERIALJTAG_CHIPRSTREG_JTAG_DTR 0x00000002UL // Get (RO) Represents the state of DTR signal as set by the most recent SET_LINE_CODING command
#define mUSBSERIALJTAG_CHIPRSTREG_USB_UART_CHIP_RST_DIS 0x00000004UL // Set/Get (R/W) Configures whether to disable chip reset from USB serial channel
#define mUSBSERIALJTAG_CHIPRSTREG_RESET 0x00000000UL // Reset value for the __usbSerialJtag_chipRstReg_t register


/**
 * \typedef __usbSerialJtag_getLineCodeW0Reg_t
 * W0 of GET_LINE_CODING command
 */
typedef union {
    uint32_t WORD;
    struct {
        uint32_t GET_LINE_CODE_W0_REG: 32; // 0-31 (R/W) Configures the value of dwDTERate set by software, which is requested by GET_LINE_CODING command
    } BITS;
} __usbSerialJtag_getLineCodeW0Reg_t;

/**
 * Masks definition for the __usbSerialJtag_getLineCodeW0Reg_t register
 */
#define mUSBSERIALJTAG_GETLINECODEW0REG_GET_LINE_CODE_W0_REG 0xFFFFFFFFUL // Set/Get (R/W) Configures the value of dwDTERate set by software, which is requested by GET_LINE_CODING command
#define mUSBSERIALJTAG_GETLINECODEW0REG_RESET 0x00000000UL // Reset value for the __usbSerialJtag_getLineCodeW0Reg_t register


/**
 * \typedef __usbSerialJtag_getLineCodeW1Reg_t
 * W1 of GET_LINE_CODING command
 */
typedef union {
    uint32_t WORD;
    struct {
        uint32_t GET_BDATA_BITS: 8; // 0-7 (R/W) Configures the value of bDataBits set by software, which is requested by GET_LINE_CODING command
        uint32_t GET_BPARITY_TYPE: 8; // 8-15 (R/W) Configures the value of bParityType set by software, which is requested by GET_LINE_CODING command
        uint32_t GET_BCHAR_FORMAT: 8; // 16-23 (R/W) Configures the value of bCharFormat set by software, which is requested by GET_LINE_CODING command
        uint32_t RESERVED: 8; // 24-31
    } BITS;
} __usbSerialJtag_getLineCodeW1Reg_t;

/**
 * Masks definition for the __usbSerialJtag_getLineCodeW1Reg_t register
 */
#define mUSBSERIALJTAG_GETLINECODEW1REG_GET_BDATA_BITS 0x000000FFUL // Set/Get (R/W) Configures the value of bDataBits set by software, which is requested by GET_LINE_CODING command
#define mUSBSERIALJTAG_GETLINECODEW1REG_GET_BPARITY_TYPE 0x0000FF00UL // Set/Get (R/W) Configures the value of bParityType set by software, which is requested by GET_LINE_CODING command
#define mUSBSERIALJTAG_GETLINECODEW1REG_GET_BCHAR_FORMAT 0x00FF0000UL // Set/Get (R/W) Configures the value of bCharFormat set by software, which is requested by GET_LINE_CODING command
#define mUSBSERIALJTAG_GETLINECODEW1REG_RESET 0x00000000UL // Reset value for the __usbSerialJtag_getLineCodeW1Reg_t register


/**
 * \typedef __usbSerialJtag_configUpdateReg_t
 * Configuration registers’ value update
 */
typedef union {
    uint32_t WORD;
    struct {
        uint32_t CONFIG_UPDATE: 1; // 0 (WT)  Configures whether to update the value of configuration registers from APB clock domain to 48 MHz clock domain
        uint32_t RESERVED: 31; // 1-31
    } BITS;
} __usbSerialJtag_configUpdateReg_t;

/**
 * Masks definition for the __usbSerialJtag_configUpdateReg_t register
 */
#define mUSBSERIALJTAG_CONFIGUPDATEREG_CONFIG_UPDATE 0x00000001UL // Set (WT) Configures whether to update the value of configuration registers from APB clock domain to 48 MHz clock domain.
#define mUSBSERIALJTAG_CONFIGUPDATEREG_RESET 0x00000000UL // Reset value for the __usbSerialJtag_configUpdateReg_t register


/**
 * \typedef __usbSerialJtag_serAfifoConficReg_t
 * Serial AFIFO configure register
 */
typedef union {
    uint32_t WORD;
    struct {
        uint32_t SERIAL_IN_AFIFO_RESET_WR: 1; // 0 (R/W)  Configures whether to reset CDC_ACM IN async FIFO write clock domain
        uint32_t SERIAL_IN_AFIFO_RESET_RD: 1; // 1 (R/W)  Configures whether to reset CDC_ACM IN async FIFO read clock domain
        uint32_t SERIAL_OUT_AFIFO_RESET_WR: 1; // 2 (R/W)  Configures whether to reset CDC_ACM OUT async FIFO write clock domain
        uint32_t SERIAL_OUT_AFIFO_RESET_RD: 1; // 3 (R/W)  Configures whether to reset CDC_ACM OUT async FIFO read clock domain
        uint32_t SERIAL_OUT_AFIFO_REMPTY: 1; // 4 (RO)  Represents CDC_ACM OUT async FIFO empty signal in read clock domain
        uint32_t SERIAL_IN_AFIFO_WFULL: 1; // 5 (RO)  Represents CDC_ACM IN async FIFO full signal in write clock domain
        uint32_t RESERVED: 26; // 6-31
    } BITS;
} __usbSerialJtag_serAfifoConficReg_t;

/**
 * Masks definition for the __usbSerialJtag_serAfifoConficReg_t register
 */
#define mUSBSERIALJTAG_SERAFIFOCONFICREG_SERIAL_IN_AFIFO_RESET_WR 0x00000001UL // Set/Get (R/W) Configures whether to reset CDC_ACM IN async FIFO write clock domain
#define mUSBSERIALJTAG_SERAFIFOCONFICREG_SERIAL_IN_AFIFO_RESET_RD 0x00000002UL // Set/Get (R/W) Configures whether to reset CDC_ACM IN async FIFO read clock domain
#define mUSBSERIALJTAG_SERAFIFOCONFICREG_SERIAL_OUT_AFIFO_RESET_WR 0x00000004UL // Set/Get (R/W) Configures whether to reset CDC_ACM OUT async FIFO write clock domain
#define mUSBSERIALJTAG_SERAFIFOCONFICREG_SERIAL_OUT_AFIFO_RESET_RD 0x00000008UL // Set/Get (R/W) Configures whether to reset CDC_ACM OUT async FIFO read clock domain
#define mUSBSERIALJTAG_SERAFIFOCONFICREG_SERIAL_OUT_AFIFO_REMPTY 0x00000010UL // Get (RO) Represents CDC_ACM OUT async FIFO empty signal in read clock domain
#define mUSBSERIALJTAG_SERAFIFOCONFICREG_SERIAL_IN_AFIFO_WFULL 0x00000020UL // Get (RO) Represents CDC_ACM IN async FIFO full signal in write clock domain
#define mUSBSERIALJTAG_SERAFIFOCONFICREG_RESET 0x00000010UL // Reset value for the __usbSerialJtag_serAfifoConficReg_t register



/********************************************************************************************************************************
************************************************************** Interrupt Registers **********************************************
*********************************************************************************************************************************/

/**
 * \addtogroup USB_SERIAL_JTAG_INT_X_REG 
 * Typedef, constants and macros associated to the USB_SERIAL_JTAG_INT_X_REG register
 * @{
 * 
 * \brief Interrupt X status register
 * X is RAW, ST, ENA, CLR
*/

/**
 * \typedef __usbSerialJtag_intStatusReg_t
 * Interrupt status register (RAW, ST, ENA, CLR)
 */
typedef union {
    uint32_t WORD;
    struct {
        uint32_t IN_FLUSH_INT: 1; // 0 (R/WTC/SS)  Interrupt status of JTAG_IN_FLUSH_INT
        uint32_t SOF_INT: 1; // 1 (R/WTC/SS)  Interrupt status of SOF_INT
        uint32_t OUT_RECV_PKT_INT: 1; // 2 (R/WTC/SS)  Interrupt status of OUT_RECV_PKT_INT
        uint32_t IN_EMPTY_INT: 1; // 3 (R/WTC/SS)  Interrupt status of IN_EMPTY_INT
        uint32_t PID_ERR_INT: 1; // 4 (R/WTC/SS)  Interrupt status of PID_ERR_INT
        uint32_t CRC5_ERR_INT: 1; // 5 (R/WTC/SS)  Interrupt status of CRC5_ERR_INT
        uint32_t CRC16_ERR_INT: 1; // 6 (R/WTC/SS)  Interrupt status of CRC16_ERR_INT
        uint32_t STUFF_ERR_INT: 1; // 7 (R/WTC/SS)  Interrupt status of STUFF_ERR_INT
        uint32_t IN_TOKEN_REC_IN_EP1_INT: 1; // 8 (R/WTC/SS)  Interrupt status of IN_TOKEN_REC_IN_EP1_INT
        uint32_t USB_BUS_RESET_INT: 1; // 9 (R/WTC/SS)  Interrupt status of USB_BUS_RESET_INT
        uint32_t OUT_EP1_ZERO_PAYLOAD_INT: 1; // 10 (R/WTC/SS) Interrupt status of OUT_EP1_ZERO_PAYLOAD_INT
        uint32_t OUT_EP2_ZERO_PAYLOAD_INT: 1; // 11 (R/WTC/SS) Interrupt status of OUT_EP2_ZERO_PAYLOAD_INT
        uint32_t RTS_CHG_INT: 1; // 12 (R/WTC/SS) Interrupt status of RTS_CHG_INT
        uint32_t DTR_CHG_INT: 1; // 13 (R/WTC/SS) Interrupt status of DTR_CHG_INT
        uint32_t GET_LINE_CODE_INT: 1; // 14 (R/WTC/SS) Interrupt status of GET_LINE_CODE_INT
        uint32_t SET_LINE_CODE_INT: 1; // 15 (R/WTC/SS) Interrupt status of SET_LINE_CODE_INT
        uint32_t RESERVED: 16; // 16-31
    } BITS;
} __usbSerialJtag_intStatusReg_t;

/**
 * Masks definition for the __usbSerialJtag_intStatusReg_t register
 */
#define mUSBSERIALJTAG_INTSTATUSREG_IN_FLUSH_INT 0x00000001UL // Set/Get (R/WTC/SS) Interrupt status of JTAG_IN_FLUSH_INT
#define mUSBSERIALJTAG_INTSTATUSREG_SOF_INT 0x00000002UL // Set/Get (R/WTC/SS) Interrupt status of SOF_INT
#define mUSBSERIALJTAG_INTSTATUSREG_OUT_RECV_PKT_INT 0x00000004UL // Set/Get (R/WTC/SS) Interrupt status of OUT_RECV_PKT_INT
#define mUSBSERIALJTAG_INTSTATUSREG_IN_EMPTY_INT 0x00000008UL // Set/Get (R/WTC/SS) Interrupt status of IN_EMPTY_INT
#define mUSBSERIALJTAG_INTSTATUSREG_PID_ERR_INT 0x00000010UL // Set/Get (R/WTC/SS) Interrupt status of PID_ERR_INT
#define mUSBSERIALJTAG_INTSTATUSREG_CRC5_ERR_INT 0x00000020UL // Set/Get (R/WTC/SS) Interrupt status of CRC5_ERR_INT
#define mUSBSERIALJTAG_INTSTATUSREG_CRC16_ERR_INT 0x00000040UL // Set/Get (R/WTC/SS) Interrupt status of CRC16_ERR_INT
#define mUSBSERIALJTAG_INTSTATUSREG_STUFF_ERR_INT 0x00000080UL // Set/Get (R/WTC/SS) Interrupt status of STUFF_ERR_INT
#define mUSBSERIALJTAG_INTSTATUSREG_IN_TOKEN_REC_IN_EP1_INT 0x00000100UL // Set/Get (R/WTC/SS) Interrupt status of IN_TOKEN_REC_IN_EP1_INT
#define mUSBSERIALJTAG_INTSTATUSREG_USB_BUS_RESET_INT 0x00000200UL // Set/Get (R/WTC/SS) Interrupt status of USB_BUS_RESET_INT
#define mUSBSERIALJTAG_INTSTATUSREG_OUT_EP1_ZERO_PAYLOAD_INT 0x00000400UL // Set/Get (R/WTC/SS) Interrupt status of OUT_EP1_ZERO_PAYLOAD_INT
#define mUSBSERIALJTAG_INTSTATUSREG_OUT_EP2_ZERO_PAYLOAD_INT 0x00000800UL // Set/Get (R/WTC/SS) Interrupt status of OUT_EP2_ZERO_PAYLOAD_INT
#define mUSBSERIALJTAG_INTSTATUSREG_RTS_CHG_INT 0x00001000UL // Set/Get (R/WTC/SS) Interrupt status of RTS_CHG_INT
#define mUSBSERIALJTAG_INTSTATUSREG_DTR_CHG_INT 0x00002000UL // Set/Get (R/WTC/SS) Interrupt status of DTR_CHG_INT
#define mUSBSERIALJTAG_INTSTATUSREG_GET_LINE_CODE_INT 0x00004000UL // Set/Get (R/WTC/SS) Interrupt status of GET_LINE_CODE_INT
#define mUSBSERIALJTAG_INTSTATUSREG_SET_LINE_CODE_INT 0x00008000UL // Set/Get (R/WTC/SS) Interrupt status of SET_LINE_CODE_INT
#define mUSBSERIALJTAG_INTSTATUSREG_RESET_RAW 0x00000008UL // Reset RAW value for the __usbSerialJtag_intStatusReg_t register
#define mUSBSERIALJTAG_INTSTATUSREG_RESET_ST 0x00000000UL // Reset ST value for the __usbSerialJtag_intStatusReg_t register
#define mUSBSERIALJTAG_INTSTATUSREG_RESET_ENA 0x00000000UL // Reset ENA value for the __usbSerialJtag_intStatusReg_t register
#define mUSBSERIALJTAG_INTSTATUSREG_RESET_CLR 0x00000000UL // Reset CLR value for the __usbSerialJtag_intStatusReg_t register
/** @} */



/********************************************************************************************************************************
********************************************************* Status Registers ******************************************************
*********************************************************************************************************************************/

/**
 * \typedef __usbSerialJtag_jfifoStReg_t
 * JTAG FIFO status and control registers
 */
typedef union {
    uint32_t WORD;
    struct {
        uint32_t IN_FIFO_CNT: 2; // 0-1 (RO)  Represents JTAG IN FIFO counter
        uint32_t IN_FIFO_EMPTY: 1; // 2 (RO)  Represents whether JTAG IN FIFO is empty
        uint32_t IN_FIFO_FULL: 1; // 3 (RO)  Represents whether JTAG IN FIFO is full
        uint32_t OUT_FIFO_CNT: 2; // 4-5 (RO)  Represents JTAG OUT FIFO counter
        uint32_t OUT_FIFO_EMPTY: 1; // 6 (RO)  Represents whether JTAG OUT FIFO is empty
        uint32_t OUT_FIFO_FULL: 1; // 7 (RO)  Represents whether JTAG OUT FIFO is full
        uint32_t IN_FIFO_RESET: 1; // 8 (R/W)  Configures whether to reset JTAG IN FIFO
        uint32_t OUT_FIFO_RESET: 1; // 9 (R/W)  Configures whether to reset JTAG OUT FIFO
        uint32_t RESERVED: 22; // 10-31
    } BITS;
} __usbSerialJtag_jfifoStReg_t;

/**
 * Masks definition for the __usbSerialJtag_jfifoStReg_t register
 */
#define mUSBSERIALJTAG_JFIFOSTREG_IN_FIFO_CNT 0x00000003UL // Get (RO) Represents JTAG IN FIFO counter
#define mUSBSERIALJTAG_JFIFOSTREG_IN_FIFO_EMPTY 0x00000004UL // Get (RO) Represents whether JTAG IN FIFO is empty
#define mUSBSERIALJTAG_JFIFOSTREG_IN_FIFO_FULL 0x00000008UL // Get (RO) Represents whether JTAG IN FIFO is full
#define mUSBSERIALJTAG_JFIFOSTREG_OUT_FIFO_CNT 0x00000030UL // Get (RO) Represents JTAG OUT FIFO counter
#define mUSBSERIALJTAG_JFIFOSTREG_OUT_FIFO_EMPTY 0x00000040UL // Get (RO) Represents whether JTAG OUT FIFO is empty
#define mUSBSERIALJTAG_JFIFOSTREG_OUT_FIFO_FULL 0x00000080UL // Get (RO) Represents whether JTAG OUT FIFO is full
#define mUSBSERIALJTAG_JFIFOSTREG_IN_FIFO_RESET 0x00000100UL // Set/Get (R/W) Configures whether to reset JTAG IN FIFO
#define mUSBSERIALJTAG_JFIFOSTREG_OUT_FIFO_RESET 0x00000200UL // Set/Get (R/W) Configures whether to reset JTAG OUT FIFO
#define mUSBSERIALJTAG_JFIFOSTREG_RESET 0x00000044UL // Reset value for the __usbSerialJtag_jfifoStReg_t register


/**
 * \typedef __usbSerialJtag_framNumReg_t
 * Last received SOF frame index register
 */
typedef union {
    uint32_t WORD;
    struct {
        uint32_t SOF_FRAME_INDEX: 11; // 0-10 (RO)  Represents frame index of received SOF frame
        uint32_t RESERVED: 21; // 11-31
    } BITS;
} __usbSerialJtag_framNumReg_t;

/**
 * Masks definition for the __usbSerialJtag_framNumReg_t register
 */
#define mUSBSERIALJTAG_FRAMNUMREG_SOF_FRAME_INDEX 0x000007FFUL // Get (RO) Represents frame index of received SOF frame
#define mUSBSERIALJTAG_FRAMNUMREG_RESET 0x00000000UL // Reset value for the __usbSerialJtag_framNumReg_t register


/**
 * \typedef __usbSerialJtag_inEpxStReg_t
 * IN endpoint status information (Control, CDC-ACM, CDC-ACM interrupt and JTAG IN endpoints)
 */
typedef union {
    uint32_t WORD;
    struct {
        uint32_t IN_EPX_STATE: 2; // 0-1 (RO)  Represents the state of IN endpoint X
        uint32_t IN_EPX_WR_ADDR: 7; // 2-8 (RO)  Represents write data address of IN endpoint X
        uint32_t IN_EPX_RD_ADDR: 7; // 9-15 (RO) Represents read data address of IN endpoint X
        uint32_t RESERVED: 16; // 16-31
    } BITS;
} __usbSerialJtag_inEpxStReg_t;

/**
 * Masks definition for the __usbSerialJtag_inEpxStReg_t register
 */
#define mUSBSERIALJTAG_INEPXSTREG_IN_EPX_STATE 0x00000003UL // Get (RO) Represents the state of IN endpoint X
#define mUSBSERIALJTAG_INEPXSTREG_IN_EPX_WR_ADDR 0x000001FCUL // Get (RO) Represents write data address of IN endpoint X
#define mUSBSERIALJTAG_INEPXSTREG_IN_EPX_RD_ADDR 0x0000FE00UL // Get (RO) Represents read data address of IN endpoint X
#define mUSBSERIALJTAG_INEPXSTREG_RESET 0x00000003UL // Reset value for the __usbSerialJtag_inEpxStReg_t register


/**
 * \typedef __usbSerialJtag_outEpxStReg_t
 * OUT endpoint status information (Control, CDC-ACM and JTAG OUT endpoints)
 */
typedef union {
    uint32_t WORD;
    struct {
        uint32_t OUT_EPX_STATE: 2; // 0-1  Represents the state of OUT endpoint X
        uint32_t OUT_EPX_WR_ADDR: 7; // 2-8  Represents write data address of OUT endpoint X
        uint32_t OUT_EPX_RD_ADDR: 7; // 9-15 Represents read data address of OUT endpoint X
        uint32_t EP1_REC_DATA_CNT: 7; // 16-22 Represents data count in OUT endpoint 1 when one packet is received
        uint32_t RESERVED: 9; // 23-31
    } BITS;
} __usbSerialJtag_outEpxStReg_t;

/**
 * Masks definition for the __usbSerialJtag_outEpxStReg_t register
 */
#define mUSBSERIALJTAG_OUTEPXSTREG_OUT_EPX_STATE 0x00000003UL // Get (RO) Represents the state of OUT endpoint X
#define mUSBSERIALJTAG_OUTEPXSTREG_OUT_EPX_WR_ADDR 0x000001FCUL // Get (RO) Represents write data address of OUT endpoint X
#define mUSBSERIALJTAG_OUTEPXSTREG_OUT_EPX_RD_ADDR 0x0000FE00UL // Get (RO) Represents read data address of OUT endpoint X
#define mUSBSERIALJTAG_OUTEPXSTREG_EP1_REC_DATA_CNT 0x007F0000UL // Get (RO) Represents data count in OUT endpoint 1 when one packet is received
#define mUSBSERIALJTAG_OUTEPXSTREG_RESET 0x00000003UL // Reset value for the __usbSerialJtag_outEpxStReg_t register


/**
 * \typedef __usbSerialJtag_setLineCodeW0Reg_t
 * W0 of SET_LINE_CODING command
 */
typedef union {
    uint32_t WORD;
    struct {
        uint32_t DW_DTE_RATE: 32; // 0-31 (RO) Represents the value of dwDTERate set by host through SET_LINE_CODING command
    } BITS;
} __usbSerialJtag_setLineCodeW0Reg_t;

/**
 * Masks definition for the __usbSerialJtag_setLineCodeW0Reg_t register
 */
#define mUSBSERIALJTAG_SETLINECODEW0REG_DW_DTE_RATE 0xFFFFFFFFUL // Get (RO) Represents the value of dwDTERate set by host through SET_LINE_CODING command
#define mUSBSERIALJTAG_SETLINECODEW0REG_RESET 0x00000000UL // Reset value for the __usbSerialJtag_setLineCodeW0Reg_t register


/**
 * \typedef __usbSerialJtag_setLineCodeW1Reg_t
 * W1 of SET_LINE_CODING command
 */
typedef union {
    uint32_t WORD;
    struct {
        uint32_t BCHAR_FORMAT: 8; // 0-7 (RO)  Represents the value of bCharFormat set by host through SET_LINE_CODING command
        uint32_t BPARITY_TYPE: 8; // 8-15 (RO) Represents the value of bParityType set by host through SET_LINE_CODING command
        uint32_t BDATA_BITS: 8; // 16-23 (RO) Represents the value of bDataBits set by host through SET_LINE_CODING command
        uint32_t RESERVED: 8; // 24-31
    } BITS;
} __usbSerialJtag_setLineCodeW1Reg_t;

/**
 * Masks definition for the __usbSerialJtag_setLineCodeW1Reg_t register
 */
#define mUSBSERIALJTAG_SETLINECODEW1REG_BCHAR_FORMAT 0x000000FFUL // Get (RO) Represents the value of bCharFormat set by host through SET_LINE_CODING command
#define mUSBSERIALJTAG_SETLINECODEW1REG_BPARITY_TYPE 0x0000FF00UL // Get (RO) Represents the value of bParityType set by host through SET_LINE_CODING command
#define mUSBSERIALJTAG_SETLINECODEW1REG_BDATA_BITS 0x00FF0000UL // Get (RO) Represents the value of bDataBits set by host through SET_LINE_CODING command
#define mUSBSERIALJTAG_SETLINECODEW1REG_RESET 0x00000000UL // Reset value for the __usbSerialJtag_setLineCodeW1Reg_t register


/**
 * \typedef __usbSerialJtag_busResetStReg_t
 * USB Bus reset status register
 */
typedef union {
    uint32_t WORD;
    struct {
        uint32_t BUS_RESET_ST: 1; // 0 (RO)  Represents whether USB bus reset is released
        uint32_t RESERVED: 31; // 1-31
    } BITS;
} __usbSerialJtag_busResetStReg_t;

/**
 * Masks definition for the __usbSerialJtag_busResetStReg_t register
 */
#define mUSBSERIALJTAG_BUSRESETSTREG_BUS_RESET_ST 0x00000001UL // Get (RO) Represents whether USB bus reset is released
#define mUSBSERIALJTAG_BUSRESETSTREG_RESET 0x00000001UL // Reset value for the __usbSerialJtag_busResetStReg_t register


/********************************************************************************************************************************
******************************************************** Version Registers ******************************************************
*********************************************************************************************************************************/

/**
 * \typedef __usbSerialJtag_dateReg_t
 * Date register
 */

typedef union {
    uint32_t WORD;
    struct {
        uint32_t DATE: 32; // 0-31 Version control register
    } BITS;
} __usbSerialJtag_dateReg_t;

/**
 * Masks definition for the __usbSerialJtag_dateReg_t register
 */
#define mUSBSERIALJTAG_DATEREG_DATE 0xFFFFFFFFUL // Get (RO) Version control register
#define mUSBSERIALJTAG_DATEREG_RESET 0x02109220UL // Reset value for the __usbSerialJtag_dateReg_t register


/********************************************************************************************************************************
*************************************************Fields Structure Definition ****************************************************
*********************************************************************************************************************************/
/**
 * \typedef __usbSerialJtag__t
*/
typedef struct {
    //Configuration Registers
    volatile __usbSerialJtag_ep1Reg_t ep1Reg; // 0x0000 : FIFO access for the CDC-ACM data IN and OUT endpoints
    volatile __usbSerialJtag_ep1ConfReg_t ep1ConfReg; // 0x0004 : Configuration and control registers for the CDC-ACM FIFOs
    
    //Interrupt Registers
    volatile __usbSerialJtag_intStatusReg_t intRawReg; // 0x0008 : Interrupt RAW status register
    volatile __usbSerialJtag_intStatusReg_t intStReg; // 0x000C : Interrupt status register
    volatile __usbSerialJtag_intStatusReg_t intEnaReg; // 0x0010 : Interrupt enable register
    volatile __usbSerialJtag_intStatusReg_t intClrReg; // 0x0014 : Interrupt clear register

    //Configuration Registers
    volatile __usbSerialJtag_conf0Reg_t conf0Reg; // 0x0018 : PHY hardware configuration
    volatile __usbSerialJtag_testReg_t testReg; // 0x001C : Registers used for debugging the PHY

    //Status Registers
    volatile __usbSerialJtag_jfifoStReg_t jfifoStReg; // 0x0020 : JTAG FIFO status and control registers
    volatile __usbSerialJtag_framNumReg_t framNumReg; // 0x0024 : Last received SOF frame index register
    volatile __usbSerialJtag_inEpxStReg_t inEp0StReg; // 0x0028 : Control IN endpoint status information
    volatile __usbSerialJtag_inEpxStReg_t inEp1StReg; // 0x002C : CDC-ACM IN endpoint status information
    volatile __usbSerialJtag_inEpxStReg_t inEp2StReg; // 0x0030 : CDC-ACM interrupt IN endpoint status information
    volatile __usbSerialJtag_inEpxStReg_t inEp3StReg; // 0x0034 : JTAG IN endpoint status information
    volatile __usbSerialJtag_outEpxStReg_t outEp0StReg; // 0x0038 : Control OUT endpoint status information
    volatile __usbSerialJtag_outEpxStReg_t outEp1StReg; // 0x003C : CDC-ACM OUT endpoint status information
    volatile __usbSerialJtag_outEpxStReg_t outEp2StReg; // 0x0040 : JTAG OUT endpoint status information

    //Configuration Registers
    volatile __usbSerialJtag_miscConfReg_t miscConfReg; // 0x0044 : Clock enable control
    volatile __usbSerialJtag_memConfReg_t memConfReg; // 0x0048 : Memory power control
    volatile __usbSerialJtag_chipRstReg_t chipRstReg; // 0x004C : CDC-ACM chip reset control

    //Status Registers
    volatile __usbSerialJtag_setLineCodeW0Reg_t setLineCodeW0Reg; // 0x0050 : W0 of SET_LINE_CODING command
    volatile __usbSerialJtag_setLineCodeW1Reg_t setLineCodeW1Reg; // 0x0054 : W1 of SET_LINE_CODING command

    //Configuration Registers
    volatile __usbSerialJtag_getLineCodeW0Reg_t getLineCodeW0Reg; // 0x0058 : W0 of GET_LINE_CODING command
    volatile __usbSerialJtag_getLineCodeW1Reg_t getLineCodeW1Reg; // 0x005C : W1 of GET_LINE_CODING command
    volatile __usbSerialJtag_configUpdateReg_t configUpdateReg; // 0x0060 : Configuration registers’ value update
    volatile __usbSerialJtag_serAfifoConficReg_t serAfifoConficReg; // 0x0064 : Serial AFIFO configure register

    //Status Registers
    volatile __usbSerialJtag_busResetStReg_t busResetStReg; // 0x0068 : USB Bus reset status register

    uint32_t RESERVED_0[5]; // 0x006C-0x007C

    //Version Registers
    volatile __usbSerialJtag_dateReg_t dateReg; // 0x0080 : Date register

} __usbSerialJtag_t;

#define kUSB_SERIAL_JTAG_BASE_ADDR 0x6000F000UL
#define sUSB_SERIAL_JTAG (*((__usbSerialJtag_t *) kUSB_SERIAL_JTAG_BASE_ADDR))


/**
 * \addtogroup USB_SERIAL_JTAG_EP1_REG
 * @{
 */
#define rUSB_SERIAL_JTAG_EP1 sUSB_SERIAL_JTAG.ep1Reg.WORD // FIFO access for the CDC-ACM data IN and OUT endpoints
#define bUSB_SERIAL_JTAG_EP1_RDWR_BYTE sUSB_SERIAL_JTAG.ep1Reg.BITS.RDWR_BYTE // 0-7 (R/W) Represents the byte to be written to the FIFO or read from UART TX/RX FIFO
/** @} */

/**
 * \addtogroup USB_SERIAL_JTAG_EP1_CONF_REG
 * @{
 */
#define rUSB_SERIAL_JTAG_EP1_CONF sUSB_SERIAL_JTAG.ep1ConfReg.WORD // Configuration and control registers for the CDC-ACM FIFOs
#define bUSB_SERIAL_JTAG_EP1_CONF_WR_DONE sUSB_SERIAL_JTAG.ep1ConfReg.BITS.WR_DONE // 0 (WT)  Configures whether to represent writing byte data to UART TX FIFO is done
#define bUSB_SERIAL_JTAG_EP1_CONF_SERIAL_IN_EP_DATA_FREE sUSB_SERIAL_JTAG.ep1ConfReg.BITS.SERIAL_IN_EP_DATA_FREE // 1 (RO)  Represents whether UART TX FIFO has space available
#define bUSB_SERIAL_JTAG_EP1_CONF_SERIAL_OUT_EP_DATA_AVAIL sUSB_SERIAL_JTAG.ep1ConfReg.BITS.SERIAL_OUT_EP_DATA_AVAIL // 2 (RO)  Represents whether there is data in UART RX FIFO
/** @} */

/**
 * \addtogroup USB_SERIAL_JTAG_CONF0_REG
 * @{
 */
#define rUSB_SERIAL_JTAG_CONF0 sUSB_SERIAL_JTAG.conf0Reg.WORD // PHY hardware configuration
#define bUSB_SERIAL_JTAG_CONF0_PHY_SEL sUSB_SERIAL_JTAG.conf0Reg.BITS.PHY_SEL // 0 (R/W)  Configures whether to select internal or external PHY
#define bUSB_SERIAL_JTAG_CONF0_EXCHG_PINS_OVERRIDE sUSB_SERIAL_JTAG.conf0Reg.BITS.EXCHG_PINS_OVERRIDE // 1 (R/W)  Configures whether to override the exchange pins
#define bUSB_SERIAL_JTAG_CONF0_EXCHG_PINS sUSB_SERIAL_JTAG.conf0Reg.BITS.EXCHG_PINS // 2 (R/W)   Configures whether to enable USB D+ D- exchange
#define bUSB_SERIAL_JTAG_CONF0_VREFH sUSB_SERIAL_JTAG.conf0Reg.BITS.VREFH // 3-4 (R/W) Configures single-end input high threshold
#define bUSB_SERIAL_JTAG_CONF0_VREFL sUSB_SERIAL_JTAG.conf0Reg.BITS.VREFL // 5-6 (R/W) Configures single-end input low threshold
#define bUSB_SERIAL_JTAG_CONF0_VREF_OVERRIDE sUSB_SERIAL_JTAG.conf0Reg.BITS.VREF_OVERRIDE // 7 (R/W)  Configures whether to enable software control input thresh-old
#define bUSB_SERIAL_JTAG_CONF0_PAD_PULL_OVERRIDE sUSB_SERIAL_JTAG.conf0Reg.BITS.PAD_PULL_OVERRIDE // 8 (R/W)  Configures whether to enable software to control USB D+ D- pullup and pulldown
#define bUSB_SERIAL_JTAG_CONF0_DP_PULLUP sUSB_SERIAL_JTAG.conf0Reg.BITS.DP_PULLUP // 9 (R/W)  Configures whether to enable USB D+ pull up when PAD_PULL_OVERRIDE is 1
#define bUSB_SERIAL_JTAG_CONF0_DP_PULLDOWN sUSB_SERIAL_JTAG.conf0Reg.BITS.DP_PULLDOWN // 10 (R/W) Configures whether to enable USB D+ pull down when PAD_PULL_OVERRIDE is 1
#define bUSB_SERIAL_JTAG_CONF0_DM_PULLUP sUSB_SERIAL_JTAG.conf0Reg.BITS.DM_PULLUP // 11 (R/W) Configures whether to enable USB D- pull up when PAD_PULL_OVERRIDE is 1
#define bUSB_SERIAL_JTAG_CONF0_DM_PULLDOWN sUSB_SERIAL_JTAG.conf0Reg.BITS.DM_PULLDOWN // 12 (R/W) Configures whether to enable USB D- pull down when PAD_PULL_OVERRIDE is 1
#define bUSB_SERIAL_JTAG_CONF0_PULLUP_VALUE sUSB_SERIAL_JTAG.conf0Reg.BITS.PULLUP_VALUE // 13 (R/W) Configures the pull up value when PAD_PULL_OVERRIDE is 1
#define bUSB_SERIAL_JTAG_CONF0_USB_PAD_ENABLE sUSB_SERIAL_JTAG.conf0Reg.BITS.USB_PAD_ENABLE // 14 (R/W) Configures whether to enable USB pad function
#define bUSB_SERIAL_JTAG_CONF0_USB_JTAG_BRIDGE_EN sUSB_SERIAL_JTAG.conf0Reg.BITS.USB_JTAG_BRIDGE_EN // 15 (R/W) Configures whether to disconnect usb_jtag and in-ternal JTAG
/** @} */

/**
 * \addtogroup USB_SERIAL_JTAG_TEST_REG
 * @{
 */
#define rUSB_SERIAL_JTAG_TEST sUSB_SERIAL_JTAG.testReg.WORD // Registers used for debugging the PHY
#define bUSB_SERIAL_JTAG_TEST_ENABLE sUSB_SERIAL_JTAG.testReg.BITS.TEST_ENABLE // 0 (R/W)  Configures whether to enable the test mode of the USB pad
#define bUSB_SERIAL_JTAG_TEST_USB_OE sUSB_SERIAL_JTAG.testReg.BITS.TEST_USB_OE // 1 (R/W)  Configures whether to enable USB pad output
#define bUSB_SERIAL_JTAG_TEST_TX_DP sUSB_SERIAL_JTAG.testReg.BITS.TEST_TX_DP // 2 (R/W)  Configures value of USB D+ in test mode when TEST_USB_OE is 1
#define bUSB_SERIAL_JTAG_TEST_TX_DM sUSB_SERIAL_JTAG.testReg.BITS.TEST_TX_DM // 3 (R/W)  Configures value of USB D- in test mode when TEST_USB_OE is 1
#define bUSB_SERIAL_JTAG_TEST_RX_RCV sUSB_SERIAL_JTAG.testReg.BITS.TEST_RX_RCV // 4 (RO)  Represents the current logical level of the voltage difference between USB D- and USB D+ pads in test mode
#define bUSB_SERIAL_JTAG_TEST_RX_DP sUSB_SERIAL_JTAG.testReg.BITS.TEST_RX_DP // 5 (RO)  Represents the logical level of the USB D+ pad in test mode
#define bUSB_SERIAL_JTAG_TEST_RX_DM sUSB_SERIAL_JTAG.testReg.BITS.TEST_RX_DM // 6 (RO)  Represents the logical level of the USB D- pad in test mode
/** @} */

/**
 * \addtogroup USB_SERIAL_JTAG_MISC_CONF_REG
 * @{
 */
#define rUSB_SERIAL_JTAG_MISC_CONF sUSB_SERIAL_JTAG.miscConfReg.WORD // Clock enable control
#define bUSB_SERIAL_JTAG_MISC_CONF_CLK_EN sUSB_SERIAL_JTAG.miscConfReg.BITS.CLK_EN // 0 (R/W)  Configures whether to force clock on for registerk
/** @} */

/**
 * \addtogroup USB_SERIAL_JTAG_MEM_CONF_REG
 * @{
 */
#define rUSB_SERIAL_JTAG_MEM_CONF sUSB_SERIAL_JTAG.memConfReg.WORD // Memory power control
#define bUSB_SERIAL_JTAG_USB_MEM_PD sUSB_SERIAL_JTAG.memConfReg.BITS.USB_MEM_PD // 0 (R/W)  Configures whether to power down USB memory
#define bUSB_SERIAL_JTAG_USB_MEM_CLK_EN sUSB_SERIAL_JTAG.memConfReg.BITS.USB_MEM_CLK_EN // 1 (R/W)  Configures whether to force clock on for USB memory
/** @} */

/**
 * \addtogroup USB_SERIAL_JTAG_CHIP_RST_REG
 * @{
 */
#define rUSB_SERIAL_JTAG_CHIP_RST sUSB_SERIAL_JTAG.chipRstReg.WORD // CDC-ACM chip reset control
#define bUSB_SERIAL_JTAG_RTS sUSB_SERIAL_JTAG.chipRstReg.BITS.JTAG_RTS // 0 (RO)  Represents the state of RTS signal as set by the most recent SET_LINE_CODING command
#define bUSB_SERIAL_JTAG_DTR sUSB_SERIAL_JTAG.chipRstReg.BITS.JTAG_DTR // 1 (RO)  Represents the state of DTR signal as set by the most recent SET_LINE_CODING command
#define bUSB_SERIAL_JTAG_USB_UART_CHIP_RST_DIS sUSB_SERIAL_JTAG.chipRstReg.BITS.USB_UART_CHIP_RST_DIS // 2 (R/W)  Configures whether to disable chip reset from USB serial channel
/** @} */

/**
 * \addtogroup USB_SERIAL_JTAG_GET_LINE_CODE_W0_REG
 * @{
 */
#define rUSB_SERIAL_JTAG_GET_LINE_CODE_W0 sUSB_SERIAL_JTAG.getLineCodeW0Reg.WORD // W0 of GET_LINE_CODING command
/** @} */

/**
 * \addtogroup USB_SERIAL_JTAG_GET_LINE_CODE_W1_REG
 * @{
 */
#define rUSB_SERIAL_JTAG_GET_LINE_CODE_W1 sUSB_SERIAL_JTAG.getLineCodeW1Reg.WORD // W1 of GET_LINE_CODING command
#define bUSB_SERIAL_JTAG_GET_BDATA_BITS sUSB_SERIAL_JTAG.getLineCodeW1Reg.BITS.GET_BDATA_BITS // 0-7 (R/W) Configures the value of bDataBits set by software, which is requested by GET_LINE_CODING command
#define bUSB_SERIAL_JTAG_GET_BPARITY_TYPE sUSB_SERIAL_JTAG.getLineCodeW1Reg.BITS.GET_BPARITY_TYPE // 8-15 (R/W) Configures the value of bParityType set by software, which is requested by GET_LINE_CODING command
#define bUSB_SERIAL_JTAG_GET_BCHAR_FORMAT sUSB_SERIAL_JTAG.getLineCodeW1Reg.BITS.GET_BCHAR_FORMAT // 16-23 (R/W) Configures the value of bCharFormat set by software, which is requested by GET_LINE_CODING command
/** @} */

/**
 * \addtogroup USB_SERIAL_JTAG_CONFIG_UPDATE_REG
 * @{
 */
#define rUSB_SERIAL_JTAG_CONFIG_UPDATE sUSB_SERIAL_JTAG.configUpdateReg.WORD // Configuration registers’ value update
#define bUSB_SERIAL_JTAG_CONFIG_UPDATE sUSB_SERIAL_JTAG.configUpdateReg.BITS.UPDATE // 0 (WT)  Configures whether to update the value of configuration registers from APB clock domain to 48 MHz clock domain
/** @} */

/**
 * \addtogroup USB_SERIAL_JTAG_SER_AFIFO_CONFIC_REG
 * @{
 */
#define rUSB_SERIAL_JTAG_SER_AFIFO_CONFIC sUSB_SERIAL_JTAG.serAfifoConficReg.WORD // Serial AFIFO configure register
#define bUSB_SERIAL_JTAG_SERIAL_IN_AFIFO_RESET_WR sUSB_SERIAL_JTAG.serAfifoConficReg.BITS.SERIAL_IN_AFIFO_RESET_WR // 0 (R/W)  Configures whether to reset CDC_ACM IN async FIFO write clock domain
#define bUSB_SERIAL_JTAG_SERIAL_IN_AFIFO_RESET_RD sUSB_SERIAL_JTAG.serAfifoConficReg.BITS.SERIAL_IN_AFIFO_RESET_RD // 1 (R/W)  Configures whether to reset CDC_ACM IN async FIFO read clock domain
#define bUSB_SERIAL_JTAG_SERIAL_OUT_AFIFO_RESET_WR sUSB_SERIAL_JTAG.serAfifoConficReg.BITS.SERIAL_OUT_AFIFO_RESET_WR // 2 (R/W)  Configures whether to reset CDC_ACM OUT async FIFO write clock domain
#define bUSB_SERIAL_JTAG_SERIAL_OUT_AFIFO_RESET_RD sUSB_SERIAL_JTAG.serAfifoConficReg.BITS.SERIAL_OUT_AFIFO_RESET_RD // 3 (R/W)  Configures whether to reset CDC_ACM OUT async FIFO read clock domain
#define bUSB_SERIAL_JTAG_SERIAL_OUT_AFIFO_REMPTY sUSB_SERIAL_JTAG.serAfifoConficReg.BITS.SERIAL_OUT_AFIFO_REMPTY // 4 (RO)  Represents CDC_ACM OUT async FIFO empty signal in read clock domain
#define bUSB_SERIAL_JTAG_SERIAL_IN_AFIFO_WFULL sUSB_SERIAL_JTAG.serAfifoConficReg.BITS.SERIAL_IN_AFIFO_WFULL // 5 (RO)  Represents CDC_ACM IN async FIFO full signal in write clock domain
/** @} */

/**
 * \addtogroup USB_SERIAL_JTAG_INT_RAW_REG
 * @{
 */
#define rUSB_SERIAL_JTAG_INT_RAW sUSB_SERIAL_JTAG.intRawReg.WORD // Interrupt RAW status register
#define bUSB_SERIAL_JTAG_JTAG_IN_FLUSH_INT_RAW sUSB_SERIAL_JTAG.intRawReg.BITS.IN_FLUSH_INT // 0 (R/WTC/SS)  Interrupt status of JTAG_IN_FLUSH_INT
#define bUSB_SERIAL_JTAG_SOF_INT_RAW sUSB_SERIAL_JTAG.intRawReg.BITS.SOF_INT // 1 (R/WTC/SS)  Interrupt status of SOF_INT
#define bUSB_SERIAL_JTAG_SERIAL_OUT_RECV_PKT_INT_RAW sUSB_SERIAL_JTAG.intRawReg.BITS.OUT_RECV_PKT_INT // 2 (R/WTC/SS)  Interrupt status of OUT_RECV_PKT_INT
#define bUSB_SERIAL_JTAG_SERIAL_IN_EMPTY_INT_RAW sUSB_SERIAL_JTAG.intRawReg.BITS.IN_EMPTY_INT // 3 (R/WTC/SS)  Interrupt status of IN_EMPTY_INT
#define bUSB_SERIAL_JTAG_PID_ERR_INT_RAW sUSB_SERIAL_JTAG.intRawReg.BITS.PID_ERR_INT // 4 (R/WTC/SS)  Interrupt status of PID_ERR_INT
#define bUSB_SERIAL_JTAG_CRC5_ERR_INT_RAW sUSB_SERIAL_JTAG.intRawReg.BITS.CRC5_ERR_INT // 5 (R/WTC/SS)  Interrupt status of CRC5_ERR_INT
#define bUSB_SERIAL_JTAG_CRC16_ERR_INT_RAW sUSB_SERIAL_JTAG.intRawReg.BITS.CRC16_ERR_INT // 6 (R/WTC/SS)  Interrupt status of CRC16_ERR_INT
#define bUSB_SERIAL_JTAG_STUFF_ERR_INT_RAW sUSB_SERIAL_JTAG.intRawReg.BITS.STUFF_ERR_INT // 7 (R/WTC/SS)  Interrupt status of STUFF_ERR_INT
#define bUSB_SERIAL_JTAG_IN_TOKEN_REC_IN_EP1_INT_RAW sUSB_SERIAL_JTAG.intRawReg.BITS.IN_TOKEN_REC_IN_EP1_INT // 8 (R/WTC/SS)  Interrupt status of IN_TOKEN_REC_IN_EP1_INT
#define bUSB_SERIAL_JTAG_USB_BUS_RESET_INT_RAW sUSB_SERIAL_JTAG.intRawReg.BITS.USB_BUS_RESET_INT // 9 (R/WTC/SS)  Interrupt status of USB_BUS_RESET_INT
#define bUSB_SERIAL_JTAG_OUT_EP1_ZERO_PAYLOAD_INT_RAW sUSB_SERIAL_JTAG.intRawReg.BITS.OUT_EP1_ZERO_PAYLOAD_INT // 10 (R/WTC/SS) Interrupt status of OUT_EP1_ZERO_PAYLOAD_INT
#define bUSB_SERIAL_JTAG_OUT_EP2_ZERO_PAYLOAD_INT_RAW sUSB_SERIAL_JTAG.intRawReg.BITS.OUT_EP2_ZERO_PAYLOAD_INT // 11 (R/WTC/SS) Interrupt status of OUT_EP2_ZERO_PAYLOAD_INT
#define bUSB_SERIAL_JTAG_RTS_CHG_INT_RAW sUSB_SERIAL_JTAG.intRawReg.BITS.RTS_CHG_INT // 12 (R/WTC/SS) Interrupt status of RTS_CHG_INT
#define bUSB_SERIAL_JTAG_DTR_CHG_INT_RAW sUSB_SERIAL_JTAG.intRawReg.BITS.DTR_CHG_INT // 13 (R/WTC/SS) Interrupt status of DTR_CHG_INT
#define bUSB_SERIAL_JTAG_GET_LINE_CODE_INT_RAW sUSB_SERIAL_JTAG.intRawReg.BITS.GET_LINE_CODE_INT // 14 (R/WTC/SS) Interrupt status of GET_LINE_CODE_INT
#define bUSB_SERIAL_JTAG_SET_LINE_CODE_INT_RAW sUSB_SERIAL_JTAG.intRawReg.BITS.SET_LINE_CODE_INT // 15 (R/WTC/SS) Interrupt status of SET_LINE_CODE_INT
/** @} */

/**
 * \addtogroup USB_SERIAL_JTAG_INT_ST_REG
 * @{
 */
#define rUSB_SERIAL_JTAG_INT_ST sUSB_SERIAL_JTAG.intStReg.WORD // Interrupt ST status register
#define bUSB_SERIAL_JTAG_JTAG_IN_FLUSH_INT_ST sUSB_SERIAL_JTAG.intStReg.BITS.IN_FLUSH_INT // 0 (R/WTC/SS)  Interrupt status of JTAG_IN_FLUSH_INT
#define bUSB_SERIAL_JTAG_SOF_INT_ST sUSB_SERIAL_JTAG.intStReg.BITS.SOF_INT // 1 (R/WTC/SS)  Interrupt status of SOF_INT
#define bUSB_SERIAL_JTAG_SERIAL_OUT_RECV_PKT_INT_ST sUSB_SERIAL_JTAG.intStReg.BITS.OUT_RECV_PKT_INT // 2 (R/WTC/SS)  Interrupt status of OUT_RECV_PKT_INT
#define bUSB_SERIAL_JTAG_SERIAL_IN_EMPTY_INT_ST sUSB_SERIAL_JTAG.intStReg.BITS.IN_EMPTY_INT // 3 (R/WTC/SS)  Interrupt status of IN_EMPTY_INT
#define bUSB_SERIAL_JTAG_PID_ERR_INT_ST sUSB_SERIAL_JTAG.intStReg.BITS.PID_ERR_INT // 4 (R/WTC/SS)  Interrupt status of PID_ERR_INT
#define bUSB_SERIAL_JTAG_CRC5_ERR_INT_ST sUSB_SERIAL_JTAG.intStReg.BITS.CRC5_ERR_INT // 5 (R/WTC/SS)  Interrupt status of CRC5_ERR_INT
#define bUSB_SERIAL_JTAG_CRC16_ERR_INT_ST sUSB_SERIAL_JTAG.intStReg.BITS.CRC16_ERR_INT // 6 (R/WTC/SS)  Interrupt status of CRC16_ERR_INT
#define bUSB_SERIAL_JTAG_STUFF_ERR_INT_ST sUSB_SERIAL_JTAG.intStReg.BITS.STUFF_ERR_INT // 7 (R/WTC/SS)  Interrupt status of STUFF_ERR_INT
#define bUSB_SERIAL_JTAG_IN_TOKEN_REC_IN_EP1_INT_ST sUSB_SERIAL_JTAG.intStReg.BITS.IN_TOKEN_REC_IN_EP1_INT // 8 (R/WTC/SS)  Interrupt status of IN_TOKEN_REC_IN_EP1_INT
#define bUSB_SERIAL_JTAG_USB_BUS_RESET_INT_ST sUSB_SERIAL_JTAG.intStReg.BITS.USB_BUS_RESET_INT // 9 (R/WTC/SS)  Interrupt status of USB_BUS_RESET_INT
#define bUSB_SERIAL_JTAG_OUT_EP1_ZERO_PAYLOAD_INT_ST sUSB_SERIAL_JTAG.intStReg.BITS.OUT_EP1_ZERO_PAYLOAD_INT // 10 (R/WTC/SS) Interrupt status of OUT_EP1_ZERO_PAYLOAD_INT
#define bUSB_SERIAL_JTAG_OUT_EP2_ZERO_PAYLOAD_INT_ST sUSB_SERIAL_JTAG.intStReg.BITS.OUT_EP2_ZERO_PAYLOAD_INT // 11 (R/WTC/SS) Interrupt status of OUT_EP2_ZERO_PAYLOAD_INT
#define bUSB_SERIAL_JTAG_RTS_CHG_INT_ST sUSB_SERIAL_JTAG.intStReg.BITS.RTS_CHG_INT // 12 (R/WTC/SS) Interrupt status of RTS_CHG_INT
#define bUSB_SERIAL_JTAG_DTR_CHG_INT_ST sUSB_SERIAL_JTAG.intStReg.BITS.DTR_CHG_INT // 13 (R/WTC/SS) Interrupt status of DTR_CHG_INT
#define bUSB_SERIAL_JTAG_GET_LINE_CODE_INT_ST sUSB_SERIAL_JTAG.intStReg.BITS.GET_LINE_CODE_INT // 14 (R/WTC/SS) Interrupt status of GET_LINE_CODE_INT
#define bUSB_SERIAL_JTAG_SET_LINE_CODE_INT_ST sUSB_SERIAL_JTAG.intStReg.BITS.SET_LINE_CODE_INT // 15 (R/WTC/SS) Interrupt status of SET_LINE_CODE_INT
/** @} */

/**
 * \addtogroup USB_SERIAL_JTAG_INT_ENA_REG
 * @{
 */
#define rUSB_SERIAL_JTAG_INT_ENA sUSB_SERIAL_JTAG.intEnaReg.WORD // Interrupt ENA status register
#define bUSB_SERIAL_JTAG_JTAG_IN_FLUSH_INT_ENA sUSB_SERIAL_JTAG.intEnaReg.BITS.IN_FLUSH_INT // 0 (R/WTC/SS)  Interrupt status of JTAG_IN_FLUSH_INT
#define bUSB_SERIAL_JTAG_SOF_INT_ENA sUSB_SERIAL_JTAG.intEnaReg.BITS.SOF_INT // 1 (R/WTC/SS)  Interrupt status of SOF_INT
#define bUSB_SERIAL_JTAG_SERIAL_OUT_RECV_PKT_INT_ENA sUSB_SERIAL_JTAG.intEnaReg.BITS.OUT_RECV_PKT_INT // 2 (R/WTC/SS)  Interrupt status of OUT_RECV_PKT_INT
#define bUSB_SERIAL_JTAG_SERIAL_IN_EMPTY_INT_ENA sUSB_SERIAL_JTAG.intEnaReg.BITS.IN_EMPTY_INT // 3 (R/WTC/SS)  Interrupt status of IN_EMPTY_INT
#define bUSB_SERIAL_JTAG_PID_ERR_INT_ENA sUSB_SERIAL_JTAG.intEnaReg.BITS.PID_ERR_INT // 4 (R/WTC/SS)  Interrupt status of PID_ERR_INT
#define bUSB_SERIAL_JTAG_CRC5_ERR_INT_ENA sUSB_SERIAL_JTAG.intEnaReg.BITS.CRC5_ERR_INT // 5 (R/WTC/SS)  Interrupt status of CRC5_ERR_INT
#define bUSB_SERIAL_JTAG_CRC16_ERR_INT_ENA sUSB_SERIAL_JTAG.intEnaReg.BITS.CRC16_ERR_INT // 6 (R/WTC/SS)  Interrupt status of CRC16_ERR_INT
#define bUSB_SERIAL_JTAG_STUFF_ERR_INT_ENA sUSB_SERIAL_JTAG.intEnaReg.BITS.STUFF_ERR_INT // 7 (R/WTC/SS)  Interrupt status of STUFF_ERR_INT
#define bUSB_SERIAL_JTAG_IN_TOKEN_REC_IN_EP1_INT_ENA sUSB_SERIAL_JTAG.intEnaReg.BITS.IN_TOKEN_REC_IN_EP1_INT // 8 (R/WTC/SS)  Interrupt status of IN_TOKEN_REC_IN_EP1_INT
#define bUSB_SERIAL_JTAG_USB_BUS_RESET_INT_ENA sUSB_SERIAL_JTAG.intEnaReg.BITS.USB_BUS_RESET_INT // 9 (R/WTC/SS)  Interrupt status of USB_BUS_RESET_INT
#define bUSB_SERIAL_JTAG_OUT_EP1_ZERO_PAYLOAD_INT_ENA sUSB_SERIAL_JTAG.intEnaReg.BITS.OUT_EP1_ZERO_PAYLOAD_INT // 10 (R/WTC/SS) Interrupt status of OUT_EP1_ZERO_PAYLOAD_INT
#define bUSB_SERIAL_JTAG_OUT_EP2_ZERO_PAYLOAD_INT_ENA sUSB_SERIAL_JTAG.intEnaReg.BITS.OUT_EP2_ZERO_PAYLOAD_INT // 11 (R/WTC/SS) Interrupt status of OUT_EP2_ZERO_PAYLOAD_INT
#define bUSB_SERIAL_JTAG_RTS_CHG_INT_ENA sUSB_SERIAL_JTAG.intEnaReg.BITS.RTS_CHG_INT // 12 (R/WTC/SS) Interrupt status of RTS_CHG_INT
#define bUSB_SERIAL_JTAG_DTR_CHG_INT_ENA sUSB_SERIAL_JTAG.intEnaReg.BITS.DTR_CHG_INT // 13 (R/WTC/SS) Interrupt status of DTR_CHG_INT
#define bUSB_SERIAL_JTAG_GET_LINE_CODE_INT_ENA sUSB_SERIAL_JTAG.intEnaReg.BITS.GET_LINE_CODE_INT // 14 (R/WTC/SS) Interrupt status of GET_LINE_CODE_INT
#define bUSB_SERIAL_JTAG_SET_LINE_CODE_INT_ENA sUSB_SERIAL_JTAG.intEnaReg.BITS.SET_LINE_CODE_INT // 15 (R/WTC/SS) Interrupt status of SET_LINE_CODE_INT
/** @} */

/**
 * \addtogroup USB_SERIAL_JTAG_INT_CLR_REG
 * @{
 */
#define rUSB_SERIAL_JTAG_INT_CLR sUSB_SERIAL_JTAG.intClrReg.WORD // Interrupt CLR status register
#define bUSB_SERIAL_JTAG_JTAG_IN_FLUSH_INT_CLR sUSB_SERIAL_JTAG.intClrReg.BITS.IN_FLUSH_INT // 0 (R/WTC/SS)  Interrupt status of JTAG_IN_FLUSH_INT
#define bUSB_SERIAL_JTAG_SOF_INT_CLR sUSB_SERIAL_JTAG.intClrReg.BITS.SOF_INT // 1 (R/WTC/SS)  Interrupt status of SOF_INT
#define bUSB_SERIAL_JTAG_SERIAL_OUT_RECV_PKT_INT_CLR sUSB_SERIAL_JTAG.intClrReg.BITS.OUT_RECV_PKT_INT // 2 (R/WTC/SS)  Interrupt status of OUT_RECV_PKT_INT
#define bUSB_SERIAL_JTAG_SERIAL_IN_EMPTY_INT_CLR sUSB_SERIAL_JTAG.intClrReg.BITS.IN_EMPTY_INT // 3 (R/WTC/SS)  Interrupt status of IN_EMPTY_INT
#define bUSB_SERIAL_JTAG_PID_ERR_INT_CLR sUSB_SERIAL_JTAG.intClrReg.BITS.PID_ERR_INT // 4 (R/WTC/SS)  Interrupt status of PID_ERR_INT
#define bUSB_SERIAL_JTAG_CRC5_ERR_INT_CLR sUSB_SERIAL_JTAG.intClrReg.BITS.CRC5_ERR_INT // 5 (R/WTC/SS)  Interrupt status of CRC5_ERR_INT
#define bUSB_SERIAL_JTAG_CRC16_ERR_INT_CLR sUSB_SERIAL_JTAG.intClrReg.BITS.CRC16_ERR_INT // 6 (R/WTC/SS)  Interrupt status of CRC16_ERR_INT
#define bUSB_SERIAL_JTAG_STUFF_ERR_INT_CLR sUSB_SERIAL_JTAG.intClrReg.BITS.STUFF_ERR_INT // 7 (R/WTC/SS)  Interrupt status of STUFF_ERR_INT
#define bUSB_SERIAL_JTAG_IN_TOKEN_REC_IN_EP1_INT_CLR sUSB_SERIAL_JTAG.intClrReg.BITS.IN_TOKEN_REC_IN_EP1_INT // 8 (R/WTC/SS)  Interrupt status of IN_TOKEN_REC_IN_EP1_INT
#define bUSB_SERIAL_JTAG_USB_BUS_RESET_INT_CLR sUSB_SERIAL_JTAG.intClrReg.BITS.USB_BUS_RESET_INT // 9 (R/WTC/SS)  Interrupt status of USB_BUS_RESET_INT
#define bUSB_SERIAL_JTAG_OUT_EP1_ZERO_PAYLOAD_INT_CLR sUSB_SERIAL_JTAG.intClrReg.BITS.OUT_EP1_ZERO_PAYLOAD_INT // 10 (R/WTC/SS) Interrupt status of OUT_EP1_ZERO_PAYLOAD_INT
#define bUSB_SERIAL_JTAG_OUT_EP2_ZERO_PAYLOAD_INT_CLR sUSB_SERIAL_JTAG.intClrReg.BITS.OUT_EP2_ZERO_PAYLOAD_INT // 11 (R/WTC/SS) Interrupt status of OUT_EP2_ZERO_PAYLOAD_INT
#define bUSB_SERIAL_JTAG_RTS_CHG_INT_CLR sUSB_SERIAL_JTAG.intClrReg.BITS.RTS_CHG_INT // 12 (R/WTC/SS) Interrupt status of RTS_CHG_INT
#define bUSB_SERIAL_JTAG_DTR_CHG_INT_CLR sUSB_SERIAL_JTAG.intClrReg.BITS.DTR_CHG_INT // 13 (R/WTC/SS) Interrupt status of DTR_CHG_INT
#define bUSB_SERIAL_JTAG_GET_LINE_CODE_INT_CLR sUSB_SERIAL_JTAG.intClrReg.BITS.GET_LINE_CODE_INT // 14 (R/WTC/SS) Interrupt status of GET_LINE_CODE_INT
#define bUSB_SERIAL_JTAG_SET_LINE_CODE_INT_CLR sUSB_SERIAL_JTAG.intClrReg.BITS.SET_LINE_CODE_INT // 15 (R/WTC/SS) Interrupt status of SET_LINE_CODE_INT
/** @} */

/**
 * \addtogroup USB_SERIAL_JTAG_JFIFO_ST_REG
 * @{
 */
#define rUSB_SERIAL_JTAG_JFIFO_ST sUSB_SERIAL_JTAG.jfifoStReg.WORD // JTAG FIFO status and control registers
#define bUSB_SERIAL_JTAG_IN_FIFO_CNT sUSB_SERIAL_JTAG.jfifoStReg.BITS.IN_FIFO_CNT // 0-1 (RO) Represents JTAG IN FIFO counter
#define bUSB_SERIAL_JTAG_IN_FIFO_EMPTY sUSB_SERIAL_JTAG.jfifoStReg.BITS.IN_FIFO_EMPTY // 2 (RO) Represents whether JTAG IN FIFO is empty
#define bUSB_SERIAL_JTAG_IN_FIFO_FULL sUSB_SERIAL_JTAG.jfifoStReg.BITS.IN_FIFO_FULL // 3 (RO) Represents whether JTAG IN FIFO is full
#define bUSB_SERIAL_JTAG_OUT_FIFO_CNT sUSB_SERIAL_JTAG.jfifoStReg.BITS.OUT_FIFO_CNT // 4-5 (RO) Represents JTAG OUT FIFO counter
#define bUSB_SERIAL_JTAG_OUT_FIFO_EMPTY sUSB_SERIAL_JTAG.jfifoStReg.BITS.OUT_FIFO_EMPTY // 6 (RO) Represents whether JTAG OUT FIFO is empty
#define bUSB_SERIAL_JTAG_OUT_FIFO_FULL sUSB_SERIAL_JTAG.jfifoStReg.BITS.OUT_FIFO_FULL // 7 (RO) Represents whether JTAG OUT FIFO is full
#define bUSB_SERIAL_JTAG_IN_FIFO_RESET sUSB_SERIAL_JTAG.jfifoStReg.BITS.IN_FIFO_RESET // 8 (R/W) Configures whether to reset JTAG IN FIFO
#define bUSB_SERIAL_JTAG_OUT_FIFO_RESET sUSB_SERIAL_JTAG.jfifoStReg.BITS.OUT_FIFO_RESET // 9 (R/W) Configures whether to reset JTAG OUT FIFO
/** @} */

/**
 * \addtogroup USB_SERIAL_JTAG_FRAM_NUM_REG
 * @{
 */
#define rUSB_SERIAL_JTAG_FRAM_NUM sUSB_SERIAL_JTAG.framNumReg.WORD // Last received SOF frame index register
#define bUSB_SERIAL_JTAG_SOF_FRAME_INDEX sUSB_SERIAL_JTAG.framNumReg.BITS.SOF_FRAME_INDEX // 0-10 (RO) Represents frame index of received SOF frame
/** @} */

/**
 * \addtogroup USB_SERIAL_JTAG_IN_EP0_ST_REG
 * @{
 */
#define rUSB_SERIAL_JTAG_IN_EP0_ST sUSB_SERIAL_JTAG.inEp0StReg.WORD // Control IN endpoint status information
#define bUSB_SERIAL_JTAG_IN_EP0_STATE sUSB_SERIAL_JTAG.inEp0StReg.BITS.IN_EP_STATE // 0-1 (RO) Represents state of IN Endpoint 0
#define bUSB_SERIAL_JTAG_IN_EP0_WR_ADDR sUSB_SERIAL_JTAG.inEp0StReg.BITS.IN_EP_WR_ADDR // 2-8 (RO) Represents write data address of IN endpoint 0
#define bUSB_SERIAL_JTAG_IN_EP0_RD_ADDR sUSB_SERIAL_JTAG.inEp0StReg.BITS.IN_EP_RD_ADDR // 9-15 (RO) Represents read data address of IN endpoint 0
/** @} */














#endif // USB_SERIAL_JTAG_ESP32_C6_LIB_H