/**
 ****************************************************************************************
 *
 * @file rwip_config.h
 *
 * @brief Configuration of the RW IP SW
 *
 * Copyright (C) RivieraWaves 2009-2013
 *
 ****************************************************************************************
 */

#ifndef _RWIP_CONFIG_H_
    #define _RWIP_CONFIG_H_

/**
 ****************************************************************************************
 * @addtogroup ROOT
 * @{
 *
 *  Information about RW SW IP options and flags
 *
 *        BT_DUAL_MODE             BT/BLE Dual Mode
 *        BT_STD_MODE              BT Only
 *        BLE_STD_MODE             BLE Only
 *
 *        RW_DM_SUPPORT            Dual mode is supported
 *        RW_BLE_SUPPORT           Configured as BLE only
 *
 *        BLE_EMB_PRESENT          BLE controller exists
 *        BLE_HOST_PRESENT         BLE host exists
 *
 * @name RW Stack Configuration
 * @{
 ****************************************************************************************
 */

/*
 * DEFINES
 ****************************************************************************************
 */

/******************************************************************************************/
/* --------------------------   GENERAL SETUP       --------------------------------------*/
/******************************************************************************************/

#include "da14580_config.h"
#include "stdtypes.h"

#ifdef CFG_BLE
	/// Application role definitions
	#define BLE_BROADCASTER             (CFG_BROADCASTER || CFG_ALLROLES)
	#define BLE_OBSERVER                (CFG_OBSERVER    || CFG_ALLROLES)
	#define BLE_PERIPHERAL              (CFG_PERIPHERAL  || CFG_ALLROLES)
	#define BLE_CENTRAL                 (CFG_CENTRAL     || CFG_ALLROLES)

	#if !BLE_BROADCASTER && !BLE_OBSERVER && !BLE_PERIPHERAL && !BLE_CENTRAL
		#error "No application role defined"
	#endif

	/// Maximum number of simultaneous connections
	#if BLE_CENTRAL
		#define BLE_CONNECTION_MAX      CFG_CON
	#elif BLE_PERIPHERAL
		#define BLE_CONNECTION_MAX      1
	#else
		#define BLE_CONNECTION_MAX      1
	#endif

	/// Number of tx data buffers
	#if BLE_CONNECTION_MAX == 1
		#if BLE_CENTRAL || BLE_PERIPHERAL
			#define BLE_TX_BUFFER_DATA  5
		#else
			#define BLE_TX_BUFFER_DATA  0
		#endif
	#else
		#define BLE_TX_BUFFER_DATA      (BLE_CONNECTION_MAX * 3)
	#endif // BLE_CONNECTION_MAX == 1

	#if BLE_CENTRAL || BLE_PERIPHERAL
		/// Number of tx advertising buffers
		#define BLE_TX_BUFFER_ADV       3
		/// Number of tx control buffers
		#define BLE_TX_BUFFER_CNTL      BLE_CONNECTION_MAX
	#else
		#if BLE_BROADCASTER
			/// Number of tx advertising buffers
			#define BLE_TX_BUFFER_ADV   2
			/// Number of tx control buffers
			#define BLE_TX_BUFFER_CNTL  0
		#else
			/// Number of tx advertising buffers
			#define BLE_TX_BUFFER_ADV   1
			/// Number of tx control buffers
			#define BLE_TX_BUFFER_CNTL  0
		#endif
	#endif // BLE_CENTRAL || BLE_PERIPHERAL

	/// Total number of elements in the TX buffer pool
	#define BLE_TX_BUFFER_CNT           (BLE_TX_BUFFER_DATA + BLE_TX_BUFFER_CNTL + BLE_TX_BUFFER_ADV)

	/// Number of receive buffers in the RX ring. This number defines the interrupt
	/// rate during a connection event. An interrupt is asserted every BLE_RX_BUFFER_CNT/2
	/// reception. This number has an impact on the size of the exchange memory. This number
	/// may have to be increased when CPU is very slow to free the received data, in order not
	/// to overflow the RX ring of buffers.
	#if BLE_CENTRAL || BLE_PERIPHERAL
		#define BLE_RX_BUFFER_CNT       8
	#elif BLE_BROADCASTER
		#define BLE_RX_BUFFER_CNT       1
	#else
		#define BLE_RX_BUFFER_CNT       4
	#endif

	/// Max advertising reports before sending the info to the host
	#define BLE_ADV_REPORTS_MAX         1

	/// Use of security manager block
	#define RW_BLE_USE_CRYPT  CFG_SECURITY_ON

#endif //defined(CFG_BLE)

/// Accelerometer Application
#define BLE_APP_ACCEL                   0

#if defined(CFG_PRF_ACCEL) || defined(CFG_PRF_PXPR) || defined(CFG_APP_KEYBOARD) || \
	defined(CFG_PRF_STREAMDATAH) || defined(CFG_PRF_SPOTAR)
	#define BLE_APP_SLAVE               1
#else
	#define BLE_APP_SLAVE               0
#endif

#ifndef __DA14581__
	#define BLE_APP_TASK_SIZE           (BLE_APP_PRESENT + BLE_APP_SEC + BLE_APP_HT + BLE_APP_NEB + \
										 BLE_APP_HID + BLE_APP_DIS + BLE_APP_BATT + BLE_APP_ACCEL)
#else
	#define BLE_APP_TASK_SIZE           BLE_APP_PRESENT
#endif

#if (BLE_CENTRAL || BLE_PERIPHERAL)
#define BLE_L2CM      1
#define BLE_L2CC      1
#define BLE_ATTM      1
#define BLE_GATTM     1
#define BLE_GATTC     1
#define BLE_ATTC      1
#define BLE_ATTS      1
#endif //(BLE_CENTRAL || BLE_PERIPHERAL)

/// Tasks types definition
enum KE_TASK_TYPE
{
    TASK_NONE           = 0xFF,

    // Link Layer Tasks
    TASK_LLM            = 0   ,
    TASK_LLC            = 1   ,
    TASK_LLD            = 2   ,
    TASK_DBG            = 3   ,

    TASK_L2CM           = 4   ,
    TASK_L2CC           = 5   ,
    TASK_SMPM           = 6   ,
    TASK_SMPC           = 7   ,
    TASK_ATTM           = 8   ,   // Attribute Protocol Manager Task
    TASK_ATTC           = 9   ,   // Attribute Protocol Client Task
		
    TASK_ATTS           = 10  ,   // Attribute Protocol Server Task
    TASK_GATTM          = 11  ,   // Generic Attribute Profile Manager Task
    TASK_GATTC          = 12  ,   // Generic Attribute Profile Controller Task
    TASK_GAPM           = 13  ,   // Generic Access Profile Manager
    TASK_GAPC           = 14  ,   // Generic Access Profile Controller
    
    TASK_PROXM          = 15  ,   // Proximity Monitor Task
    TASK_PROXR          = 16  ,   // Proximity Reporter Task
    TASK_FINDL          = 17  ,   // Find Me Locator Task
    TASK_FINDT          = 18  ,   // Find Me Target Task
    TASK_HTPC           = 19  ,   // Health Thermometer Collector Task
    TASK_HTPT           = 20  ,   // Health Thermometer Sensor Task
    TASK_ACCEL          = 21  ,   // Accelerometer Sensor Task
    TASK_BLPS           = 22  ,   // Blood Pressure Sensor Task
    TASK_BLPC           = 23  ,   // Blood Pressure Collector Task
    TASK_HRPS           = 24  ,   // Heart Rate Sensor Task
    TASK_HRPC           = 25  ,   // Heart Rate Collector Task
    TASK_TIPS           = 26  ,   // Time Server Task
    TASK_TIPC           = 27  ,   // Time Client Task
    TASK_DISS           = 28  ,   // Device Information Service Server Task
    TASK_DISC           = 29  ,   // Device Information Service Client Task
    TASK_SCPPS          = 30  ,   // Scan Parameter Profile Server Task
    TASK_SCPPC          = 31  ,   // Scan Parameter Profile Client Task
    TASK_BASS           = 32  ,   // Battery Service Server Task
    TASK_BASC           = 33  ,   // Battery Service Client Task
    TASK_HOGPD          = 34  ,   // HID Device Task
    TASK_HOGPBH         = 35  ,   // HID Boot Host Task
    TASK_HOGPRH         = 36  ,   // HID Report Host Task
    TASK_GLPS           = 37  ,   // Glucose Profile Sensor Task
    TASK_GLPC           = 38  ,   // Glucose Profile Collector Task
    TASK_NBPS           = 39  ,   // Nebulizer Profile Server Task
    TASK_NBPC           = 40  ,   // Nebulizer Profile Client Task
    TASK_RSCPS          = 41  ,   // Running Speed and Cadence Profile Server Task
    TASK_RSCPC          = 42  ,   // Running Speed and Cadence Profile Collector Task
    TASK_CSCPS          = 43  ,   // Cycling Speed and Cadence Profile Server Task
    TASK_CSCPC          = 44  ,   // Cycling Speed and Cadence Profile Client Task
    TASK_ANPS           = 45  ,   // Alert Notification Profile Server Task
    TASK_ANPC           = 46  ,   // Alert Notification Profile Client Task
    TASK_PASPS          = 47  ,   // Phone Alert Status Profile Server Task
    TASK_PASPC          = 48  ,   // Phone Alert Status Profile Client Task

    TASK_LANS           = 49  ,   // Location and Navigation Profile Server Task
    TASK_APP            = 50  ,   // Do not Alter. 

    TASK_LANC           = 51  ,   // Location and Navigation Profile Client Task

    TASK_CPPS           = 52  ,   // Cycling Power Profile Server Task
    TASK_CPPC           = 53  ,   // Cycling Power Profile Client Task
    
    // Start of conditionally assigned task types
    
    #if (BLE_BM_SERVER)
    TASK_BMSS           ,   // BMSS Task
    #endif

    #if (BLE_BM_CLIENT)
    TASK_BMSC         ,   // BMSC Task
    #endif

    #if BLE_SPOTA_RECEIVER
    TASK_SPOTAR         ,   // SPOTA Receiver task
    #endif

    #if BLE_STREAMDATA_DEVICE
    TASK_STREAMDATAD    ,   // Stream Data Device Server task
    #endif

    #if BLE_STREAMDATA_HOST
    TASK_STREAMDATAH    ,   // Stream Data Device Server task
    #endif

    #if BLE_ANC_CLIENT
    TASK_ANCC           ,   // ANCS Client Task
    #endif

    #if BLE_WPT_CLIENT
    TASK_WPTC           ,   // A4WP Wireless Power Transfer Client Profile Task
    #endif

    #if BLE_WPTS
    TASK_WPTS           ,   // A4WP Wireless Power Transfer Server Profile Task
    #endif

    #if BLE_APP_PTU
     TASK_APP_PTU       ,   // A4WP Wireless Power Transfer Client App Task
    #endif

    #if BLE_IEU
    TASK_IEU            ,   // Integrated Environmantal Unit Task
    #endif

    #if BLE_MPU
    TASK_MPU            ,   // Motion Processing Unit Task
    #endif

    #if BLE_WSS_SERVER
    TASK_WSSS           ,   // Weight Scale Server Task
    #endif

    #if BLE_WSS_COLLECTOR
    TASK_WSSC           ,   // Weight Scale Collector Task
    #endif

    #if BLE_UDS_SERVER
    TASK_UDSS           ,   // User Data Server Task
    #endif

    #if BLE_UDS_CLIENT
    TASK_UDSC           ,   // User Data Server Task
    #endif

    #if BLE_SPS_SERVER
    TASK_SPS_SERVER     ,   // Serial Proert Service Server Task
    #endif

    #if BLE_SPS_CLIENT
    TASK_SPS_CLIENT     ,   // Serial Proert Service Server Task
    #endif

    #if BLE_ADC_NOTIFY
    TASK_ADC_NOTIFY     ,   // Serial Proert Service Server Task
    #endif

    #if BLE_DEVICE_CONFIG
    TASK_DEVICE_CONFIG  ,   // Serial Proert Service Server Task
    #endif

    #if (BLE_BCS_SERVER)
    TASK_BCSS          ,   // Body Composition Server Task
    #endif

    #if (BLE_BCS_CLIENT)
    TASK_BCSC          ,   // Body Composition Client Task
    #endif

    #if (BLE_CTS_SERVER)
    TASK_CTSS          ,   // Current Time Server Task
    #endif

    #if (BLE_CTS_CLIENT)
    TASK_CTSC          ,   // Current Time Client Task
    #endif

    #if BLE_CUSTOM2_SERVER
	TASK_CUSTS2		    ,	// 2nd Custom profile server
    #endif

    #if BLE_CUSTOM1_SERVER
	TASK_CUSTS1		    ,	// 1st Custom profile server
    #endif

    // End of conditionally assigned task types
    
    TASK_HCI            = 60  ,
    TASK_HCIH           = 61  ,

    TASK_GTL            = 63  ,

    #if USE_AES
    TASK_AES            = 62  ,   // Task for asynchronous AES API
    #endif    

    TASK_MAX            = 64,  //MAX is 64. Do  not exceed. 
};

#endif // _RWIP_CONFIG_H_
