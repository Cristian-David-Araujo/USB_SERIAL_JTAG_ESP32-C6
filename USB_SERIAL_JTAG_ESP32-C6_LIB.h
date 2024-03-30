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
        uint32_t RDWR_BYTE: 8; // 0-7  Write or read byte data to or from UART TX/RX FIFO
        uint32_t RESERVED: 24; // 8-31
    } BITS;
} __usbSerialJtag_ep1Reg_t;


/**
 * \typedef __usbSerialJtag_ep1ConfReg_t
 * Configuration and control registers forthe CDC-ACM FIFOs
 */
typedef union {
    uint32_t WORD;
    struct {
        uint32_t WR_DONE: 1; // 0  Configures whether to represent writing byte data to UART TX FIFO is done
        uint32_t RESEERIAL_IN_EP_DATA_FREERVED: 1; // 1  Represents whether UART TX FIFO has space available
        uint32_t SERIAL_OUT_EP_DATA_AVAIL: 1; // 2  Represents whether there is data in UART RX FIFO
        uint32_t RESERVED: 29; // 3-31
    } BITS;
} __usbSerialJtag_ep1ConfReg_t;


/**
 * \typedef __usbSerialJtag_conf0Reg_t;
 * PHY hardware configuration
 */
typedef union {
    uint32_t WORD;
    struct {
        uint32_t PHY_SEL: 1; // 0  Configures whether to select internal or external PHY
        uint32_t EXCHG_PINS_OVERRIDE: 1; // 1  Configures whether to enable software control USB D+ D- exchange
        uint32_t EXCHG_PINS: 1; // 2  Configures whether to enable USB D+ D- exchange
        uint32_t VREFH: 2; // 3-4 Configures single-end input high threshold
        uint32_t VREFL: 2; // 5-6 Configures single-end input low threshold
        uint32_t VREF_OVERRIDE: 1; // 7  Configures whether to enable software control input thresh-old
        uint32_t PAD_PULL_OVERRIDE: 1; // 8  Configures whether to enable software to control USB D+ D- pullup and pulldown
        uint32_t DP_PULLUP: 1; // 9  Configures whether to enable USB D+ pull up when PAD_PULL_OVERRIDE is 1
        uint32_t DP_PULLDOWN: 1; // 10 Configures whether to enable USB D+ pull down when PAD_PULL_OVERRIDE is 1
        uint32_t DM_PULLUP: 1; // 11 Configures whether to enable USB D- pull up when PAD_PULL_OVERRIDE is 1
        uint32_t DM_PULLDOWN: 1; // 12 Configures whether to enable USB D- pull down when PAD_PULL_OVERRIDE is 1
        uint32_t PULLUP_VALUE: 1; // 13 Configures the pull up value when PAD_PULL_OVERRIDE is 1
        uint32_t USB_PAD_ENABLE: 1; // 14 Configures whether to enable USB pad function
        uint32_t USB_JTAG_BRIDGE_EN: 1; // 15 Configures whether to disconnect usb_jtag and in-ternal JTAG
        uint32_t RESERVED: 16; // 16-31
    } BITS;
} __usbSerialJtag_conf0Reg_t;


/**
 * \typedef __usbSerialJtag_testReg_t
 * Registers used for debugging the PHY
 */
typedef union {
    uint32_t WORD;
    struct {
        uint32_t TEST_ENABLE: 1; // 0  Configures whether to enable the test mode of the USB pad
        uint32_t TEST_USB_OE: 1; // 1  Configures whether to enable USB pad output
        uint32_t TEST_TX_DP: 1; // 2  Configures value of USB D+ in test mode when TEST_USB_OE is 1
        uint32_t TEST_TX_DM: 1; // 3  Configures value of USB D- in test mode when TEST_USB_OE is 1
        uint32_t TEST_RX_RCV: 1; // 4  Represents the current logical level of the voltage difference between USB D- and USB D+ pads in test mode
        uint32_t TEST_RX_DP: 1; // 5  Represents the logical level of the USB D+ pad in test mode
        uint32_t TEST_RX_DM: 1; // 6  Represents the logical level of the USB D- pad in test mode
        uint32_t RESERVED: 25; // 7-31
    } BITS;
} __usbSerialJtag_testReg_t;


/**
 * \typedef __usbSerialJtag_miscConfReg_t
 * Clock enable control
 */
typedef union {
    uint32_t WORD;
    struct {
        uint32_t CLK_EN: 1; // 0  Configures whether to force clock on for register
        uint32_t RESERVED: 31; // 1-31
    } BITS;
} __usbSerialJtag_miscConfReg_t;


/**
 * \typedef __usbSerialJtag_memConfReg_t
 * Memory power control
 */
typedef union {
    uint32_t WORD;
    struct {
        uint32_t USB_MEM_PD: 1; // 0  Configures whether to power down USB memory
        uint32_t USB_MEM_CLK_EN: 1; // 1  Configures whether to force clock on for USB memory
        uint32_t RESERVED: 30; // 2-31
    } BITS;
} __usbSerialJtag_memConfReg_t;


/**
 * \typedef __usbSerialJtag_chipRstReg_t
 * CDC-ACM chip reset control
 */
typedef union {
    uint32_t WORD;
    struct {
        uint32_t JTAG_RTS: 1; // 0  Represents the state of RTS signal as set by the most recent SET_LINE_CODING command
        uint32_t JTAG_DTR: 1; // 1  Represents the state of DTR signal as set by the most recent SET_LINE_CODING command
        uint32_t USB_UART_CHIP_RST_DIS: 1; // 2  Configures whether to disable chip reset from USB serial channel
        uint32_t RESERVED: 29; // 3-31
    } BITS;
} __usbSerialJtag_chipRstReg_t;


/**
 * \typedef __usbSerialJtag_getLineCodeW0Reg_t
 * W0 of GET_LINE_CODING command
 */
typedef union {
    uint32_t WORD;
    struct {
        uint32_t GET_LINE_CODE_W0_REG: 32; // 0-31 Configures the value of dwDTERate set by software, which is requested by GET_LINE_CODING command
    } BITS;
} __usbSerialJtag_getLineCodeW0Reg_t;

/**
 * \typedef __usbSerialJtag_getLineCodeW1Reg_t
 * W1 of GET_LINE_CODING command
 */
typedef union {
    uint32_t WORD;
    struct {
        uint32_t GET_BDATA_BITS: 8; // 0-7 Configures the value of bDataBits set by software, which is requested by GET_LINE_CODING command
        uint32_t GET_BPARITY_TYPE: 8; // 8-15 Configures the value of bParityType set by software, which is requested by GET_LINE_CODING command
        uint32_t GET_BCHAR_FORMAT: 8; // 16-23 Configures the value of bCharFormat set by software, which is requested by GET_LINE_CODING command
        uint32_t RESERVED: 8; // 24-31
    } BITS;
} __usbSerialJtag_getLineCodeW1Reg_t;


/**
 * \typedef __usbSerialJtag_configUpdateReg_t
 * Configuration registers’ value update
 */
typedef union {
    uint32_t WORD;
    struct {
        uint32_t CONFIG_UPDATE: 1; // 0  Configures whether to update the value of configuration registers from APB clock domain to 48 MHz clock domain.
        uint32_t RESERVED: 31; // 1-31
    } BITS;
} __usbSerialJtag_configUpdateReg_t;


/**
 * \typedef __usbSerialJtag_serAfifoConficReg_t
 * Serial AFIFO configure register
 */
typedef union {
    uint32_t WORD;
    struct {
        uint32_t SERIAL_IN_AFIFO_RESET_WR: 1; // 0  Configures whether to reset CDC_ACM IN async FIFO write clock domain
        uint32_t SERIAL_IN_AFIFO_RESET_RD: 1; // 1  Configures whether to reset CDC_ACM IN async FIFO read clock domain
        uint32_t SERIAL_OUT_AFIFO_RESET_WR: 1; // 2  Configures whether to reset CDC_ACM OUT async FIFO write clock domain
        uint32_t SERIAL_OUT_AFIFO_RESET_RD: 1; // 3  Configures whether to reset CDC_ACM OUT async FIFO read clock domain
        uint32_t SERIAL_OUT_AFIFO_REMPTY: 1; // 4  Represents CDC_ACM OUT async FIFO empty signal in read clock domain
        uint32_t SERIAL_IN_AFIFO_WFULL: 1; // 5  Represents CDC_ACM IN async FIFO full signal in write clock domain
        uint32_t RESERVED: 26; // 6-31
    } BITS;
} __usbSerialJtag_serAfifoConficReg_t;



/********************************************************************************************************************************
************************************************************** Interrupt Registers **********************************************
*********************************************************************************************************************************/

/**
 * \typedef __usbSerialJtag_intStatusReg_t
 * Interrupt status register (RAW, ST, ENA, CLR)
 */
typedef union {
    uint32_t WORD;
    struct {
        uint32_t IN_FLUSH_INT: 1; // 0  Interrupt status of JTAG_IN_FLUSH_INT
        uint32_t SOF_INT: 1; // 1  Interrupt status of SOF_INT
        uint32_t OUT_RECV_PKT_INT: 1; // 2  Interrupt status of OUT_RECV_PKT_INT
        uint32_t IN_EMPTY_INT: 1; // 3  Interrupt status of IN_EMPTY_INT
        uint32_t PID_ERR_INT: 1; // 4  Interrupt status of PID_ERR_INT
        uint32_t CRC5_ERR_INT: 1; // 5  Interrupt status of CRC5_ERR_INT
        uint32_t CRC16_ERR_INT: 1; // 6  Interrupt status of CRC16_ERR_INT
        uint32_t STUFF_ERR_INT: 1; // 7  Interrupt status of STUFF_ERR_INT
        uint32_t IN_TOKEN_REC_IN_EP1_INT: 1; // 8  Interrupt status of IN_TOKEN_REC_IN_EP1_INT
        uint32_t USB_BUS_RESET_INT: 1; // 9  Interrupt status of USB_BUS_RESET_INT
        uint32_t OUT_EP1_ZERO_PAYLOAD_INT: 1; // 10 Interrupt status of OUT_EP1_ZERO_PAYLOAD_INT
        uint32_t OUT_EP2_ZERO_PAYLOAD_INT: 1; // 11 Interrupt status of OUT_EP2_ZERO_PAYLOAD_INT
        uint32_t RTS_CHG_INT: 1; // 12 Interrupt status of RTS_CHG_INT
        uint32_t DTR_CHG_INT: 1; // 13 Interrupt status of DTR_CHG_INT
        uint32_t GET_LINE_CODE_INT: 1; // 14 Interrupt status of GET_LINE_CODE_INT
        uint32_t SET_LINE_CODE_INT: 1; // 15 Interrupt status of SET_LINE_CODE_INT
        uint32_t RESERVED: 16; // 16-31
    } BITS;
} __usbSerialJtag_intStatusReg_t;


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
        uint32_t IN_FIFO_CNT: 2; // 0-1  Represents JTAG IN FIFO counter
        uint32_t IN_FIFO_EMPTY: 1; // 2  Represents whether JTAG IN FIFO is empty
        uint32_t IN_FIFO_FULL: 1; // 3  Represents whether JTAG IN FIFO is full
        uint32_t OUT_FIFO_CNT: 2; // 4-5  Represents JTAG OUT FIFO counter
        uint32_t OUT_FIFO_EMPTY: 1; // 6  Represents whether JTAG OUT FIFO is empty
        uint32_t OUT_FIFO_FULL: 1; // 7  Represents whether JTAG OUT FIFO is full
        uint32_t IN_FIFO_RESET: 1; // 8  Configures whether to reset JTAG IN FIFO
        uint32_t OUT_FIFO_RESET: 1; // 9  Configures whether to reset JTAG OUT FIFO
        uint32_t RESERVED: 22; // 10-31

    } BITS;
} __usbSerialJtag_jfifoStReg_t;


/**
 * \typedef __usbSerialJtag_framNumReg_t
 * Last received SOF frame index register
 */
typedef union {
    uint32_t WORD;
    struct {
        uint32_t SOF_FRAME_INDEX: 11; // 0-10  Represents frame index of received SOF frame
        uint32_t RESERVED: 21; // 11-31
    } BITS;
} __usbSerialJtag_framNumReg_t;


/**
 * \typedef __usbSerialJtag_inEpxStReg_t
 * IN endpoint status information (Control, CDC-ACM, CDC-ACM interrupt and JTAG IN endpoints)
 */
typedef union {
    uint32_t WORD;
    struct {
        uint32_t IN_EPX_STATE: 2; // 0-1  Represents the state of IN endpoint X
        uint32_t IN_EPX_WR_ADDR: 7; // 2-8  Represents write data address of IN endpoint X
        uint32_t IN_EPX_RD_ADDR: 7; // 9-15 Represents read data address of IN endpoint X
        uint32_t RESERVED: 16; // 16-31
    } BITS;
} __usbSerialJtag_inEpxStReg_t;


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
 * \typedef __usbSerialJtag_setLineCodeW0Reg_t
 * W0 of SET_LINE_CODING command
 */
typedef union {
    uint32_t WORD;
    struct {
        uint32_t DW_DTE_RATE: 32; // 0-31 Represents the value of dwDTERate set by host through SET_LINE_CODING command
    } BITS;
} __usbSerialJtag_setLineCodeW0Reg_t;


/**
 * \typedef __usbSerialJtag_setLineCodeW1Reg_t
 * W1 of SET_LINE_CODING command
 */
typedef union {
    uint32_t WORD;
    struct {
        uint32_t BCHAR_FORMAT: 8; // 0-7  Represents the value of bCharFormat set by host through SET_LINE_CODING command
        uint32_t BPARITY_TYPE: 8; // 8-15 Represents the value of bParityType set by host through SET_LINE_CODING command
        uint32_t BDATA_BITS: 8; // 16-23 Represents the value of bDataBits set by host through SET_LINE_CODING command
        uint32_t RESERVED: 8; // 24-31
    } BITS;
} __usbSerialJtag_setLineCodeW1Reg_t;


/**
 * \typedef __usbSerialJtag_busResetStReg_t
 * USB Bus reset status register
 */
typedef union {
    uint32_t WORD;
    struct {
        uint32_t BUS_RESET_ST: 1; // 0  Represents whether USB bus reset is released
        uint32_t RESERVED: 31; // 1-31
    } BITS;
} __usbSerialJtag_busResetStReg_t;


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
#endif // USB_SERIAL_JTAG_ESP32_C6_LIB_H