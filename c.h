/**
 * \file BUSCTRL_LIB.h 
 * \brief Hardware library for RP2040 Bus fabric modue
 * \details ...
 * \author      RAVV
 * \version     0.0.1
 * \date        27/08/2023
 * \copyright   Unlicensed
 * 
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

#ifndef __BUSCTRL_LIB_
#define __BUSCTRL_LIB_

#include <stdint.h>

/**
 * \addtogroup BUS_FABRIC RP2040 BUS FABRIC MODULE
 * BUS_FABRIC groups all register of the module, typedefs, macros, etc.
 * @{
 * \brief The RP2040 bus fabric module routes addresses and data across the chip.
*/

/**
 * \addtogroup BUSCTRL_PRIORITY BUS FABRIC PRIORITY REGISTER
 * Typedef, constants and macros associated to the BUSCTRL_PRIORITY register
 * @{
 * \brief Set the priority of each master for bus fabric arbitration
*/

/**
 * \typedef __busctrl_priority_t
 * Type definition for bus priority register
*/

typedef union{
    uint32_t WORD;                          ///< Whole resiter access
    struct BITS{
        uint32_t PROC0     : 1;                  ///< RW Set Bus Fabric priority for Processor 0  
        uint32_t           : 3;             ///< Non implemented bits
        uint32_t PROC1     : 1;                 ///< RW Set Bus Fabric priority for Processor 1 
        uint32_t           : 3;             ///< Non implemented bits
        uint32_t DMA_R     : 1;                 ///< RW Set Bus Fabric priority for DMA reading port 
        uint32_t           : 3;             ///< Non implemented bits
        uint32_t DMA_W     : 1;                 ///< RW Set Bus Fabric priority for DMA writing port 
        uint32_t           : 19;            ///< Non implemented bits
    } BITS;
} __busctrl_priority_t;

/**
 * Masks definition for bus priority register
*/
#define mBUSCTRL_PROC0 0x00000001UL        ///< Set Bus Fabric priority for Processor 0  
#define mBUSCTRL_PROC1 0x00000010UL        ///< Set Bus Fabric priority for Processor 1
#define mBUSCTRL_DMA_R 0x00000100UL        ///< Set Bus Fabric priority for DMA reading port
#define mBUSCTRL_DMA_W 0x00001000UL        ///< Set Bus Fabric priority for DMA writing port
#define mBUSCTRL_PRIORITY_RESET 0x00000000 ///< Bus Fabric PRIORITY register reset value

/**
 * Constants definition for bus priority register
*/
#define kBUSCTRL_LOW_PRIORITY 0            ///< Constant value to set Bus Fabric priorities to low
#define kBUSCTRL_HIGH_PRIORITY 1           ///< Constant value to set Bus Fabric priorities to high

/** @} */

/**
 * \addtogroup BUSCTRL_PRIORITY_ACK BUS FABRIC PRIORITY ACK REGISTER
 * Typedef, constants and macros associated to the BUSCTRL_PRIORITY_ACK register
 * @{
 * 
 * \brief Bus fabric priority acknowledge 
 * ACK bit goes to 1 once all arbiters have registered the new global priority levels.
 * Arbiters update their local priority when servicing a new nonsequential access.
 * In normal circumstances this will happen almost immediately.
*/

/**
 * \typedef __busctrl_priority_ack_t
*/
typedef union{
    uint32_t WORD;                      ///< Whole register access
    struct BITS{
        uint32_t ACK: 1;                ///< RO Acknowledge of updated global priority levels  
        uint32_t reserved0 : 31;        ///< Non implemented bits
    } BITS;
} __busctrl_priority_ack_t;

/**
 * Masks definition for bus priority ack register
*/

#define mBUSCTRL_ACK 0x00000001UL              ///< RO Acknowledge of updated global priority levels  
#define mBUSCTRL_PRIORITY_ACK_RESET 0x00000000 ///< Bus Fabric PRIORITY_ACK register reset value

/**
 * Constants definition for bus priority ack register
*/
#define kBUSCTRL_ACK_OK 1                      ///< Value for PRIORITY_ACK register acknowledge
/** @} */

/**
 * \addtogroup BUSCTRL_PERFCTR_N BUS FABRIC PERFORMANCE COUNTER N
 * Typedef, constants and macros associated to the BUSCTRL_PERFCTR_N register
 * @{
 * 
 * \brief Bus fabric performance counter N
 * Count some event signal from the busfabric arbiters.
 * Write any value to clear. Select an event to count using PERFSEL N register.
*/

/**
 * \typedef __busctrl_perfctrn_t
*/
typedef union{
    uint32_t WORD;                              ///< Whole register access
    struct BITS{
        uint32_t VALUE: 24;                     ///< WC Busfabric saturating performance counter N value
        uint32_t reserved0 : 8;                 ///< Non implemented bits
    } BITS;
} __busctrl_perfctrn_t;

/**
 * Masks definition for bus performance counter N register
*/
#define mBUSCTRL_COUNTER_VALUE 0x00FFFFFFUL    ///< WC Busfabric saturating performance counter N value  
#define mBUSCTRL_PERFCTRN_RESET 0x00000000     ///< Bus Fabric PERFCTR N register reset value

/** @} */

/**
 * \addtogroup BUSCTRL_PERFSEL_N BUS FABRIC PERFORMANCE COUNTER EVENT SELECTOR N
 * Typedef, constants and macros associated to the BUSCTRL_PERFSEL_N register
 * @{
 * 
 * \brief Bus fabric performance counter event selector N
 * Select an event for PERFCTRN. Count either contested accesses, or all
 * accesses, on a downstream port of the main crossbar.
*/

/**
 * \typedef __busctrl_perfseln_t
 * Type declaration for register bus fabric performance counter event selector N
*/
typedef union{
    uint32_t WORD;                              ///< Whole register access
    struct BITS{
        uint32_t VALUE: 5;                      ///< RW Busfabric saturating performance counter event selector N value
        uint32_t reserved0 : 27;                ///< Non implemented bits
    } BITS;
} __busctrl_perfseln_t;

/**
 * Masks definition for bus performance counter event selector N register
*/

#define mBUSCTRL_SELECTOR_VALUE 0x0000001FUL   ///< RW Busfabric saturating performance counter event selector N value 
#define mBUSCTRL_PERFSELN_RESET 0x0000001FUL   ///< Bus Fabric PERFSEL N register reset value

/**
 * Constants definition for bus fabric performance counter event selector N
*/
#define kBUSCTRL_SEL_APB_CONTESTED 0x00        ///<< Select to count APB (SLOW PERI) contested accesses on PERFCTR N register
#define kBUSCTRL_SEL_APB 0x01                  ///< Select to count all APB (SLOW PERI) accesses on PERFCTR N rsgister
#define kBUSCTRL_SEL_FASTPERI_CONTESTED 0x02   ///< Select to count FASTPERI constested accesses on PERFCTR N register
#define kBUSCTRL_SEL_FASTPERI 0x03             ///< Select to count all FASTPERI accesses on PERFCTR N rsgister
#define kBUSCTRL_SEL_SRAM5_CONTESTED 0x04      ///< Select to count SRAM5 contested accesses on PERFCTR N register
#define kBUSCTRL_SEL_SRAM5 0x05                ///< Select to count all SRAM5 accesses on  PERFCTR N rsgister
#define kBUSCTRL_SEL_SRAM4_CONTESTED 0x06      ///< Select to count SRAM4 contested accesses on PERFCTR N register
#define kBUSCTRL_SEL_SRAM4 0x07                ///< Select to count all SRAM4 accesses on  PERFCTR N rsgister
#define kBUSCTRL_SEL_SRAM3_CONTESTED 0x08      ///< Select to count SRAM3 contested accesses on PERFCTR N register
#define kBUSCTRL_SEL_SRAM3 0x09                ///< Select to count all SRAM3 accesses on  PERFCTR N rsgister
#define kBUSCTRL_SEL_SRAM2_CONTESTED 0x0A      ///< Select to count SRAM2 contested accesses on PERFCTR N register
#define kBUSCTRL_SEL_SRAM2 0x0B                ///< Select to count all SRAM2 accesses on  PERFCTR N rsgister
#define kBUSCTRL_SEL_SRAM1_CONTESTED 0x0C      ///< Select to count SRAM1 contested accesses on PERFCTR N register
#define kBUSCTRL_SEL_SRAM1 0x0D                ///< Select to count all SRAM1 accesses on  PERFCTR N rsgister
#define kBUSCTRL_SEL_SRAM0_CONTESTED 0x0E      ///< Select to count SRAM0 contested accesses on PERFCTR N register
#define kBUSCTRL_SEL_SRAM0 0x0F                ///< Select to count all SRAM0 accesses on  PERFCTR N rsgister
#define kBUSCTRL_SEL_XIP_CONTESTED 0x10        ///< Select to count XIP MAIN contested accesses on PERFCTR N register
#define kBUSCTRL_SEL_XIP 0x11                  ///< Select to count all XIP MAIN accesses on  PERFCTR N rsgister
#define kBUSCTRL_SEL_ROM_CONTESTED 0x12        ///< Select to count ROM contested accesses on PERFCTR N register
#define kBUSCTRL_SEL_ROM 0x12                  ///< Select to count all ROM accesses on  PERFCTR N rsgister

/** @} */


/**
 * \typedef __busctrl_t
*/

typedef struct {
    volatile __busctrl_priority_t        PRIORITY;       ///< Set the priority of each master for bus arbitration.
    volatile __busctrl_priority_ack_t    PRIORITY_ACK;   ///< Bus priority acknowledge
    volatile __busctrl_perfctrn_t        PERFCTR0;       ///< Bus fabric performance counter 0
    volatile __busctrl_perfseln_t        PERFSEL0;       ///< Bus fabric performance event select for PERFCTR0
    volatile __busctrl_perfctrn_t        PERFCTR1;       ///< Bus fabric performance counter 1
    volatile __busctrl_perfseln_t        PERFSEL1;       ///< Bus fabric performance event select for PERFCTR1
    volatile __busctrl_perfctrn_t        PERFCTR2;       ///< Bus fabric performance counter 2
    volatile __busctrl_perfseln_t        PERFSEL2;       ///< Bus fabric performance event select for PERFCTR2
    volatile __busctrl_perfctrn_t        PERFCTR3;       ///< Bus fabric performance counter 2
    volatile __busctrl_perfseln_t        PERFSEL3;       ///< Bus fabric performance event select for PERFCTR3
}__busctrl_t;

#define sBUSCTRL (*((__busctrl_t *)( 0x40030000)))       ///< Normal RW access struct for BUS FABRIC CONTROL module
#define sBUSCTRL_XOR (*((__busctrl_t *)( 0x40031000)))   ///< Atomic XOR WO access struct for BUS FABRIC CONTROL module
#define sBUSCTRL_SET (*((__busctrl_t *)( 0x40032000)))   ///< Atomic SET WO access struct for BUS FABRIC CONTROL module
#define sBUSCTRL_CLR (*((__busctrl_t *)( 0x40033000)))   ///< Atomic CLEAR WO access struct for BUS FABRIC CONTROL module


/**
 * \addtogroup BUSCTRL_PRIORITY
 * @{
 */

#define rBUSCTRL_PRIORITY sBUSCTRL.PRIORITY.WORD
#define bBUSCTRL_PROC0 sBUSCTRL.PRIORITY.BITS.PROC0
#define bBUSCTRL_PROC1 sBUSCTRL.PRIORITY.BITS.PROC1
#define bBUSCTRL_DMAR sBUSCTRL.PRIORITY.BITS.DMA_R
#define bBUSCTRL_DMAW sBUSCTRL.PRIORITY.BITS.DMA_W
#define xorBUSCTRL_PROC0 sBUSCTRL_XOR.PRIORITY.WORD = mBUSCTRL_PROC0
#define xorBUSCTRL_PROC1 sBUSCTRL_XOR.PRIORITY.WORD = mBUSCTRL_PROC1
#define xorBUSCTRL_DMAR sBUSCTRL_XOR.PRIORITY.WORD = mBUSCTRL_DMA_R
#define xorBUSCTRL_DMAW sBUSCTRL_XOR.PRIORITY.WORD = mBUSCTRL_DMA_W
#define setBUSCTRL_PROC0 sBUSCTRL_SET.PRIORITY.WORD = mBUSCTRL_PROC0
#define setBUSCTRL_PROC1 sBUSCTRL_SET.PRIORITY.WORD = mBUSCTRL_PROC1
#define setBUSCTRL_DMAR sBUSCTRL_SET.PRIORITY.WORD = mBUSCTRL_DMA_R
#define setBUSCTRL_DMAW sBUSCTRL_SET.PRIORITY.WORD = mBUSCTRL_DMA_W
#define clrBUSCTRL_PROC0 sBUSCTRL_CLR.PRIORITY.WORD = mBUSCTRL_PROC0
#define clrBUSCTRL_PROC1 sBUSCTRL_CLR.PRIORITY.WORD = mBUSCTRL_PROC1
#define clrBUSCTRL_DMAR sBUSCTRL_CLR.PRIORITY.WORD = mBUSCTRL_DMA_R
#define clrBUSCTRL_DMAW sBUSCTRL_CLR.PRIORITY.WORD = mBUSCTRL_DMA_W
/** @} */

/**
 * \addtogroup BUSCTRL_PRIORITY_ACK
 * @{
 */
#define rBUSCTRL_PRIORITY_ACK sBUSCTRL.PRIORITY_ACK.WORD
#define bBUSCTRL_ACK sBUSCTRL.PRIORITY_ACK.BITS.ACK
/** @} */

/**
 * \addtogroup BUSCTRL_PERFCTR_N
 * @{
 */
#define rBUSCTRL_PERFCTR0 sBUSCTRL.PERFCTR0.WORD
#define bBUSCTRL_PERFCTR0_VALUE sBUSCTRL.PERFCTR0.BITS.VALUE

#define rBUSCTRL_PERFCTR1 sBUSCTRL.PERFCTR1.WORD
#define bBUSCTRL_PERFCTR1_VALUE sBUSCTRL.PERFCTR1.BITS.VALUE

#define rBUSCTRL_PERFCTR2 sBUSCTRL.PERFCTR2.WORD
#define bBUSCTRL_PERFCTR2_VALUE sBUSCTRL.PERFCTR2.BITS.VALUE

#define rBUSCTRL_PERFCTR3 sBUSCTRL.PERFCTR3.WORD
#define bBUSCTRL_PERFCTR3_VALUE sBUSCTRL.PERFCTR3.BITS.VALUE

/** @} */

/**
 * \addtogroup BUSCTRL_PERFSEL_N
 * @{
 */
#define rBUSCTRL_PERFSEL0 sBUSCTRL.PERFSEL0.WORD
#define bBUSCTRL_PERFSEL0_VALUE sBUSCTRL.PERFSEL0.BITS.VALUE

#define rBUSCTRL_PERFSEL1 sBUSCTRL.PERFSEL1.WORD
#define bBUSCTRL_PERFSEL1_VALUE sBUSCTRL.PERFSEL1.BITS.VALUE

#define rBUSCTRL_PERFSEL2 sBUSCTRL.PERFSEL2.WORD
#define bBUSCTRL_PERFSEL2_VALUE sBUSCTRL.PERFSEL2.BITS.VALUE

#define rBUSCTRL_PERFSEL3 sBUSCTRL.PERFSEL3.WORD
#define bBUSCTRL_PERFSEL3_VALUE sBUSCTRL.PERFSEL3.BITS.VALUE
/** @} */

/** @} */

#endif