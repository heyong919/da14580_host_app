/**
 ****************************************************************************************
 *
 * @file gapc.h
 *
 * @brief Generic Access Profile Controller Header.
 *
 * Copyright (C) RivieraWaves 2009-2013
 *
 ****************************************************************************************
 */


#ifndef _GAPC_H_
#define _GAPC_H_

/**
 ****************************************************************************************
 * @addtogroup GAPC Generic Access Profile Controller
 * @ingroup GAP
 * @brief  Generic Access Profile Controller.
 *
 * The GAP Controller module is responsible for providing an API to the application in
 * to perform GAP action related to a BLE connection (pairing, update parameters,
 * disconnect ...). GAP controller is multi-instantiated, one task instance per BLE
 * connection.
 *
 * @{
 ****************************************************************************************
 */


/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "rwip_config.h"

#if (BLE_CENTRAL || BLE_PERIPHERAL)

#include "ke_task.h"
#include "gap.h"
#include "gapc_task.h"
//#include "llc_task.h"



/*
 * DEFINES
 ****************************************************************************************
 */

/// Information source.
enum gapc_addr_src
{
    /// Local info.
    GAPC_INFO_LOCAL,
    /// Peer info.
    GAPC_INFO_PEER,
    /// Maximum info source.
    GAPC_INFO_MAX,
};



/// Link security status. This status represents the authentication/authorization/bonding levels of the connection
enum gapc_lk_sec_req
{
    /// No security requirements on current link
    GAPC_LK_SEC_NONE,
    /// Link is unauthenticated
    GAPC_LK_UNAUTHENTICATED,
    /// Link is authenticated
    GAPC_LK_AUTHENTICATED,
    /// Link is authorized
    GAPC_LK_AUTHORIZED ,
    /// Link is bonded
    GAPC_LK_BONDED,
    /// Link is Encrypted
    GAPC_LK_ENCRYPTED,
};


/// fields definitions.
enum gapc_fields
{
    /// Local connection role
    GAPC_ROLE      = 0,
    /// Encrypted connection or not
    GAPC_ENCRYPTED = 1,
    /// Authentication informations
    GAPC_AUTH      = 2,
    /// Authorization informations
    GAPC_AUTHZ     = 5,
};


/// fields mask definitions.
enum gapc_fields_mask
{
    /// Bit[0]
    GAPC_ROLE_MASK      = 0x01,
    /// Bit[1]
    GAPC_ENCRYPTED_MASK = 0x02,
    /// Bit[4-2]
    GAPC_AUTH_MASK      = 0x1C,
    /// Bit[6-5]
    GAPC_AUTHZ_MASK     = 0x60,
};

#endif // (BLE_CENTRAL || BLE_PERIPHERAL)
/// @} GAPC

#endif /* _GAPC_H_ */
