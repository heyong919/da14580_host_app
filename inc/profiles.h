/*
 * profiles.h
 *
 *  Created on: 2016/11/17
 *      Author: heyong
 */

#ifndef INC_PROFILES_H_
#define INC_PROFILES_H_

#pragma pack(1)
#include "prf_types.h"

#include "gapm.h"
#include "gapm_task.h"
#include "gapc.h"
#include "gapc_task.h"

#include "gatt.h"
#include "gattm_task.h"
#include "gattc_task.h"

#include "diss.h"
#include "diss_task.h"
#pragma pack()

/*** GAP DEFINITIONS ***/
#define MAX_SCAN_DEVICES 9
/// Local address type
#define APP_ADDR_TYPE     0
/// Advertising channel map
#define APP_ADV_CHMAP     0x07
/// Advertising filter policy
#define APP_ADV_POL       0
/// Advertising minimum interval
#define APP_ADV_INT_MIN   0x800
/// Advertising maximum interval
#define APP_ADV_INT_MAX   0x800
/// Advertising data maximal length
#define APP_ADV_DATA_MAX_SIZE           (ADV_DATA_LEN - 3)
/// Scan Response data maximal length
#define APP_SCAN_RESP_DATA_MAX_SIZE     (SCAN_RSP_DATA_LEN)
#if (BLE_SPOTA_RECEIVER)
    #define APP_DFLT_ADV_DATA        "\x09\x03\x03\x18\x02\x18\x04\x18\xF5\xFE"
    #define APP_DFLT_ADV_DATA_LEN    (8+2)
#else
    #define APP_DFLT_ADV_DATA        "\x07\x03\x03\x18\x02\x18\x04\x18"
    #define APP_DFLT_ADV_DATA_LEN    (8)
#endif
#define APP_SCNRSP_DATA         "\x09\xFF\x00\x60\x52\x57\x2D\x42\x4C\x45"
#define APP_SCNRSP_DATA_LENGTH  (10)
#define APP_DFLT_DEVICE_NAME    ("HY_TEST")


/*** DISS DEFINITIONS ***/
/// Manufacturer Name (up to 18 chars)
#define APP_DIS_MANUFACTURER_NAME       ("Dialog Semiconductor")
#define APP_DIS_MANUFACTURER_NAME_LEN   (11)
/// Model Number String (up to 18 chars)
#define APP_DIS_MODEL_NB_STR            ("DA14580")
#define APP_DIS_MODEL_NB_STR_LEN        (7)
/// System ID - LSB -> MSB (FIXME)
#define APP_DIS_SYSTEM_ID               ("\x12\x34\x56\xFF\xFE\x9A\xBC\xDE")
#define APP_DIS_SYSTEM_ID_LEN           (8)
#define APP_DIS_SW_REV                  ""
#define APP_DIS_FIRM_REV                "v0.0.1"
#define APP_DIS_FEATURES                (DIS_MANUFACTURER_NAME_CHAR_SUP | DIS_MODEL_NB_STR_CHAR_SUP | DIS_SYSTEM_ID_CHAR_SUP | DIS_SW_REV_STR_CHAR_SUP | DIS_FIRM_REV_STR_CHAR_SUP | DIS_PNP_ID_CHAR_SUP)
/// PNP ID
#define APP_DISS_PNP_COMPANY_ID_TYPE    (0x01)
#define APP_DISS_PNP_VENDOR_ID          (0x00D2)
#define APP_DISS_PNP_PRODUCT_ID         (0x0580)
#define APP_DISS_PNP_PRODUCT_VERSION    (0x0100)


#endif /* INC_PROFILES_H_ */
