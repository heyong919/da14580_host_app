/**
 ****************************************************************************************
 *
 * @file gapm.h
 *
 * @brief Generic Access Profile Manager Header.
 *
 * Copyright (C) RivieraWaves 2009-2013
 *
 ****************************************************************************************
 */


#ifndef _GAPM_H_
#define _GAPM_H_

/**
 ****************************************************************************************
 * @addtogroup GAPM Generic Access Profile Manager
 * @ingroup GAP
 * @brief Generic Access Profile Manager.
 *
 * The GAP Manager module is responsible for providing an API to the application in order
 * to manage all non connected stuff such as configuring device to go in desired mode
 * (discoverable, connectable, etc.) and perform required actions (scanning, connection,
 * etc.). GAP Manager is also responsible of managing GAP Controller state according to
 * corresponding BLE connection states.
 *
 * @{
 ****************************************************************************************
 */


/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "rwip_config.h"
#include "ke_task.h"
//#include "llc_task.h"
#include "gap.h"

/*
 * DEFINES
 ****************************************************************************************
 */

/// Scan filter size
#define GAPM_SCAN_FILTER_SIZE   10


/// Operation type
enum gapm_op_type
{
    /// Configuration operation
    GAPM_CFG_OP = 0x00,
    /// Air mode operation (scanning, advertising, connection establishment)
    GAPM_AIR_OP,
    /// Max number of operations
    GAPM_MAX_OP,
};

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */


/// Air operation default parameters
struct gapm_air_operation
{
    /// Operation code.
    uint8_t  code;


    /** Own BD address source of the device:
     * - GAPM_PUBLIC_ADDR: Public Address
     * - GAPM_PROVIDED_RND_ADDR: Provided random address
     * - GAPM_GEN_STATIC_RND_ADDR: Generated static random address
     * - GAPM_GEN_RSLV_ADDR: Generated resolvable private random address
     * - GAPM_GEN_NON_RSLV_ADDR: Generated non-resolvable private random address
     * - GAPM_PROVIDED_RECON_ADDR: Provided Reconnection address (only for GAPM_ADV_DIRECT)
     */
    uint8_t addr_src;

    /// Dummy data use to retrieve internal operation state (should be set to 0).
    uint16_t state;

    /// Duration of resolvable address before regenerate it.
    uint16_t renew_dur;

    /// Provided own static private random address (addr_src = 1 or 5)
    struct bd_addr addr;
};

/// @} GAPM

#endif /* _GAPM_H_ */
