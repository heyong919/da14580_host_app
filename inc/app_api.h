/*
 * app_api.h
 *
 *  Created on: 2016Äê10ÔÂ28ÈÕ
 *      Author: heyong
 */

#ifndef APP_API_H_
#define APP_API_H_

#include "stdtypes.h"
#include "att.h"
#include "gapm_task.h"
#include "gapc_task.h"
#include "gattm_task.h"
#include "gattc_task.h"

struct attribute_full_desc
{
	/// Element UUID
	uint8_t uuid[ATT_UUID_128_LEN];
	/// UUID size
	uint8_t uuid_size;
	/// Attribute permission
	uint8_t perm[2];
	/// Maximum length of the element
	uint8_t max_length[2];
	/// Current length of the element
	uint8_t length[2];
	/// Element value array
	uint8_t value[];
};
typedef struct attribute_full_desc attribute_full_desc_t;

// cmd | cmd_cmp_evt
// cmd | - | ind
// req | rsp
// ind | - | cfm

struct app_stack_callback
{
/// GAPM
	// Command Complete event
	int32_t (*gapm_cmd_cmp_evt)(struct gapm_cmp_evt *param);
	// Event triggered to inform that lower layers are ready
	int32_t (*gapm_device_ready_indication)(void *param);
/* Local device information */
	// Local device name indication event
	int32_t (*gapm_dev_name_indication)(struct gapm_dev_name_ind *param);
	// Local device appearance indication event
	int32_t (*gapm_appearance_indication)(struct gapm_appearance_ind *param);
	// Local device version indication event
	int32_t (*gapm_dev_version_indication)(struct gapm_dev_version_ind *param);
	// Local device BD Address indication event
	int32_t (*gapm_dev_bdaddr_indication)(struct gapm_dev_bdaddr_ind *param);
	// Advertising channel Tx power level
	int32_t (*gapm_dev_adv_tx_power_indication)(struct gapm_dev_adv_tx_power_ind *param);
/* White List */
	// White List Size indication event
	int32_t (*gapm_white_list_size_indication)(struct gapm_white_list_size_ind *param);
/* Air Operations */
	// Advertising or scanning report information event
	int32_t (*gapm_adv_report_indication)(struct gapm_adv_report_ind *param);
	// Name of peer device indication
	int32_t (*gapm_peer_name_indication)(struct gapm_peer_name_ind *param);
/* Privacy update events */
	// Privacy flag value has been updated
	int32_t (*gapm_updated_privacy_indication)(struct gapm_updated_privacy_ind *param);
	// Reconnection address has been updated
	int32_t (*gapm_updated_recon_addr_indication)(struct gapm_updated_recon_addr_ind *param);
/* Security / Encryption Toolbox */
	// Indicate that resolvable random address has been solved
	int32_t (*gapm_addr_solved_indication)(struct gapm_addr_solved_ind *param);
	//  AES-128 block result indication
	int32_t (*gapm_use_enc_block_indication)(struct gapm_use_enc_block_ind *param);
	// Random Number Indication
	int32_t (*gapm_gen_rand_nb_indication)(struct gapm_gen_rand_nb_ind *param);

/// GAPC
	// Command Complete event
	int32_t (*gapc_cmd_cmp_evt)(struct gapc_cmp_evt *param);
/* Connection state information */
	// Indicate that a connection has been established
	int32_t (*gapc_connection_req_indication)(struct gapc_connection_req_ind *param);
	// Indicate that a link has been disconnected
	int32_t (*gapc_disconnect_indication)(struct gapc_disconnect_ind *param);
/* Peer device info */
	// Name of peer device indication
	int32_t (*gapc_peer_name_indication)(struct gapc_peer_name_ind *param);
	// Indication of peer version info
	int32_t (*gapc_peer_version_indication)(struct gapc_peer_version_ind *param);
	// Indication of peer features info
	int32_t (*gapc_peer_features_indication)(struct gapc_peer_features_ind *param);
	// Indication of ongoing connection RSSI
	int32_t (*gapc_conn_rssi_indication)(struct gapc_con_rssi_ind *param);
	// Indication of ongoing connection Channel Map
	int32_t (*gapc_conn_channel_map_indication)(struct gapc_con_channel_map_ind *param);
	// Indication of peer privacy info
	int32_t (*gapc_privacy_indication)(struct gapc_privacy_ind *param);
	// Indication of peer reconnection address info
	int32_t (*gapc_recon_addr_indication)(struct gapc_recon_addr_ind *param);
/* Connection parameters update */
	// Request of updating connection parameters indication
	int32_t (*gapc_conn_param_update_req_indication)(struct gapc_param_update_req_ind *param);
	// Connection parameters updated indication
	int32_t (*gapc_conn_param_updated_indication)(struct gapc_param_updated_ind *param);
/* Bonding procedure */
	// Bonding requested by peer device indication message.
	int32_t (*gapc_bond_req_indication)(struct gapc_bond_req_ind *param);
	// Bonding information indication message
	int32_t (*gapc_bond_info_indication)(struct gapc_bond_ind *param);
/* Encryption procedure */
	// Encryption requested by peer device indication message.
	int32_t (*gapc_encrypt_req_indication)(struct gapc_encrypt_req_ind *param);
	// Encryption information indication message
	int32_t (*gapc_encrypt_info_indication)(struct gapc_encrypt_ind *param);
/* Security request procedure */
	// Security requested by peer device indication message
	int32_t (*gapc_security_indication)(struct gapc_security_ind *param);
/* Signature procedure */
	// Indicate the current sign counters to the application
	int32_t (*gapc_sign_counter_indication)(struct gapc_sign_counter_ind *param);

/// GATT
	// Command Complete event
	int32_t (*gattc_cmd_cmp_evt)(struct gattc_cmp_evt *param);
/* ATTRIBUTE CLIENT */
	// Discovery services indication
	int32_t (*gattc_disc_svc_indication)(struct gattc_disc_svc_ind *param);
	// Discover included services indication
	int32_t (*gattc_disc_svc_incl_indication)(struct gattc_disc_svc_incl_ind *param);
	// Discover characteristic indication
	int32_t (*gattc_disc_char_indication)(struct gattc_disc_char_ind *param);
	// Discovery characteristic descriptor indication
	int32_t (*gattc_disc_char_desc_indication)(struct gattc_disc_char_desc_ind *param);
	// Read response including results from peer device
	int32_t (*gattc_read_indication)(struct gattc_read_ind *param);
	// peer device triggers an event (indication or notification)
	int32_t (*gattc_notify_indication)(struct gattc_event_ind *param); // remote indication or notification
/* ATTRIBUTE SERVER */
	/* Indicate that write operation is requested. */
	// Write command indicated to upper layers.
	int32_t (*gattc_write_cmd_indication)(struct gattc_write_cmd_ind *param);
	/* Indicate that a read operation is requested. */
	// Read command indicated to upper layers.
	int32_t (*gattc_read_cmd_indication)(struct gattc_read_cmd_ind *param);

};
typedef struct app_stack_callback app_stack_callback_t;

// set GAP/GATT stack callbacks
int32_t app_set_stack_callback(app_stack_callback_t *callback);


/// GAPM API
/* Default commands */
	// Reset link layer and the host command
	int32_t app_gap_reset(struct gapm_reset_cmd *param);
	// Cancel ongoing operation
	int32_t app_gap_cancel_operation();
/* Device Configuration */
	// Set device configuration command
	int32_t app_gap_set_dev_config(struct gapm_set_dev_config_cmd *param);
	// Set device name command
	int32_t app_gap_set_dev_name(struct gapm_set_dev_name_cmd *param);
	// Set device channel map
	int32_t app_gap_set_channel_map(struct gapm_set_channel_map_cmd *param);
/* Local device information */
	// Get local device info command
	int32_t app_gap_get_dev_info(struct gapm_get_dev_info_cmd *param);
/* White List */
	// White List Management Command
	int32_t app_gap_white_list_mgt(struct gapm_white_list_mgt_cmd *param);
/* Air Operations */
	// Set advertising mode Command
	int32_t app_gap_start_advertising(struct gapm_start_advertise_cmd *param);
	// Set Scan mode Command
	int32_t app_gap_start_scanning(struct gapm_start_scan_cmd *param);
	// Set connection initialization Command
	int32_t app_gap_start_connection(struct gapm_start_connection_cmd *param);
/* Security / Encryption Toolbox */
	// Resolve address command
	int32_t app_gap_resolve_addr(struct gapm_resolv_addr_cmd *param);
	// Generate a random address.
	int32_t app_gap_gen_random_addr(struct gapm_gen_rand_addr_cmd *param);
	// Use the AES-128 block in the controller
	int32_t app_gap_use_enc_block(struct gapm_use_enc_block_cmd *param);
	// Generate a 8-byte random number
	int32_t app_gap_gen_random_nb(struct gapm_gen_rand_nb_cmd *param);


/// GAPC API
/* Connection state information */
	// Set specific link data configuration. Reply for connection request.
	int32_t app_gap_conn_confirm(struct gapc_connection_cfm *param);
/* Link management command */
	// Request disconnection of current link command.
	int32_t app_gap_disconnect(struct gapc_disconnect_cmd *param);
/* Peer device info */
	// Retrieve information command
	int32_t app_gap_get_peer_info(struct gapc_get_info_cmd *param);
/* Privacy configuration */
	// Set Privacy flag command.
	int32_t app_gap_set_privacy(struct gapc_set_privacy_cmd *param);
	// Set Reconnection Address Value command.
	int32_t app_gap_set_recon_addr(struct gapc_set_recon_addr_cmd *param);
/* Connection parameters update */
	// Perform update of connection parameters command
	int32_t app_gap_conn_param_update(struct gapc_param_update_cmd *param);
	// Master confirm or not that parameters proposed by slave are accepted or not
	int32_t app_gap_conn_para_update_confirm(struct gapc_param_update_cfm *param);
/* Bonding procedure */
	// Start Bonding command procedure
	int32_t app_gap_start_bonding(struct gapc_bond_cmd *param);
	// Confirm requested bond information.
	int32_t app_gap_bond_confirm(struct gapc_bond_cfm *param);
/* Encryption procedure */
	// Start Encryption command procedure
	int32_t app_gap_start_encrypt(struct gapc_encrypt_cmd *param);
	// Confirm requested Encryption information.
	int32_t app_gap_encrypt_confirm(struct gapc_encrypt_cfm *param);
/* Security request procedure */
	// Start Security Request command procedure
	int32_t app_gap_start_security(struct gapc_security_cmd *param);


/// ATT server api
/*** ATTRIBUTE SERVER ***/
	// create ATT database for given attributes.
	int32_t app_create_gatt_db(attribute_full_desc_t *att_full_desc);
/*Notify Characteristic*/
/*Indicate Characteristic*/
	// send an event to peer device
	int32_t app_gatt_send_event();
/* Service Changed Characteristic Indication */
	//Send a Service Changed indication to a device
	int32_t app_gatt_send_svc_change(struct gattc_send_svc_changed_cmd *param);
/* Confirm write command execution. */
	// Write command confirmation from upper layers.
	int32_t app_gatt_write_confirm(struct gattc_write_cmd_cfm *param);


/// ATT client api
/*** ATTRIBUTE CLIENT ***/
	// Server configuration request
	int32_t app_gatt_exchange_mtu();
	/*Discover All Services */
	/*Discover Services by Service UUID*/
	/*Find Included Services*/
	/*Discover Characteristics by UUID*/
	/*Discover All Characteristics of a Service*/
	/*Discover All Characteristic Descriptors*/
	// Discovery command
	int32_t app_gatt_discovery();
	/*Read Value*/
	/*Read Using UUID*/
	/*Read Long Value*/
	/*Read Multiple Values*/
	// Read command
	int32_t app_gatt_read();
	/*Write without response*/
	/*Write without response with Authentication*/
	/*Write Characteristic Value*/
	/*Signed Write Characteristic Value*/
	/*Write Long Characteristic Value*/
	/*Characteristic Value Reliable Write*/
	/*Write Characteristic Descriptors*/
	/*Write Long Characteristic Descriptors*/
	/*Characteristic Value Reliable Write*/
	// Write command request
	int32_t app_gatt_write();
	/* Cancel / Execute pending write operations */
	// Execute write characteristic request
	int32_t app_gatt_write_execute();
	/* Reception of an indication or notification from peer device. */
	// Registration to peer device events (Indication/Notification).
	int32_t app_gatt_register_peer_event();



#endif /* APP_API_H_ */
