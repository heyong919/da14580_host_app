/**
 ****************************************************************************************
 *
 * @file smpm.h
 *
 * @brief Header file - SMPM.
 *
 * Copyright (C) RivieraWaves 2009-2013
 *
 *
 ****************************************************************************************
 */

#ifndef SMPM_H_
#define SMPM_H_

/**
 ****************************************************************************************
 * @addtogroup SMPM Security Manager Protocol Manager
 * @ingroup SMP
 * @brief Security Manager Protocol Manager.
 *
 * This Module allows the 1-instanced modules to communicate with multi-instanced SMPC module.
 * It is only an intermediary between the actual SMPC handling SM behavior, and
 * LLM, GAP, or GATT which only indicate the index of the connection for which
 * SMPC actions are necessary.
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */

//#include "smp_common.h"       // Firmware Configuration Flags


#include "ke_msg.h"

/*
 * DEFINES
 ****************************************************************************************
 */

// Length of resolvable random address prand part
#define SMPM_RAND_ADDR_PRAND_LEN            (3)
// Length of resolvable random address hash part
#define SMPM_RAND_ADDR_HASH_LEN             (3)

/*
 * ENUMERATIONS
 ****************************************************************************************
 */

/**
 * Random Address Types
 */
enum smpm_rand_addr_type
{
    /// Private Non Resolvable  - 00 (MSB->LSB)
    SMPM_ADDR_TYPE_PRIV_NON_RESOLV          = 0x00,
    /// Private Resolvable      - 01
    SMPM_ADDR_TYPE_PRIV_RESOLV              = 0x40,
    /// Static                  - 11
    SMPM_ADDR_TYPE_STATIC                   = 0xC0,
};

#endif // (SMPM_H_)

/// @} SMPM
