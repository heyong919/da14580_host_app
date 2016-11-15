/*
 * app_api_impl.c
 *
 *  Created on: 2016Äê9ÔÂ1ÈÕ
 *      Author: heyong
 */

#include <stdio.h>
#include "stdtypes.h"
#include "att.h"
#include "app_api.h"
#include "app_msg.h"


app_stack_callback_t *user_stack_callback = NULL;

// set GAP/GATT stack callbacks
int32_t app_set_stack_callback(app_stack_callback_t *callback)
{
	user_stack_callback = callback;
	return 0;
}

/// GAPM API
/* Default commands */
// Reset link layer and the host command
int32_t app_gap_reset(struct gapm_reset_cmd *param)
{
	uint16_t para_len = sizeof(struct gapm_reset_cmd);
	stack_msg_t *msg_buf = msg_alloc_buffer(para_len);

	dbg_func();
  msg_fill(msg_buf, GAPM_RESET_CMD, TASK_GTL, TASK_GAPM, para_len, (uint8_t *)param);
	msg_send(msg_buf);

	return 0;
}
// Cancel ongoing operation
int32_t app_gap_cancel_operation()
{
	uint16_t para_len = 0;
	stack_msg_t *msg_buf = msg_alloc_buffer(para_len);

	dbg_func();
  msg_fill(msg_buf, GAPM_CANCEL_CMD, TASK_GTL, TASK_GAPM, para_len, NULL);
	msg_send(msg_buf);

	return 0;
}
/* Device Configuration */
// Set device configuration command
int32_t app_gap_set_dev_config(struct gapm_set_dev_config_cmd *param)
{
	uint16_t para_len = sizeof(struct gapm_set_dev_config_cmd);
	stack_msg_t *msg_buf = msg_alloc_buffer(para_len);

	dbg_func();
  msg_fill(msg_buf, GAPM_SET_DEV_CONFIG_CMD, TASK_GTL, TASK_GAPM, para_len, (uint8_t *)param);
	msg_send(msg_buf);

	return 0;
}
// Set device name command
int32_t app_gap_set_dev_name(struct gapm_set_dev_name_cmd *param)
{
	uint16_t para_len = sizeof(struct gapm_set_dev_name_cmd) + param->length;
	stack_msg_t *msg_buf = msg_alloc_buffer(para_len);

	dbg_func();
  msg_fill(msg_buf, GAPM_SET_DEV_NAME, TASK_GTL, TASK_GAPM, para_len, (uint8_t *)param);
	msg_send(msg_buf);

	return 0;
}
// Set device channel map
int32_t app_gap_set_channel_map(struct gapm_set_channel_map_cmd *param)
{
	dbg_func();
	return 0;
}
/* Local device information */
// Get local device info command
int32_t app_gap_get_dev_info(struct gapm_get_dev_info_cmd *param)
{
	dbg_func();
	return 0;
}
/* White List */
// White List Management Command
int32_t app_gap_white_list_mgt(struct gapm_white_list_mgt_cmd *param)
{
	dbg_func();
	return 0;
}
/* Air Operations */
// Set advertising mode Command
int32_t app_gap_start_advertising(struct gapm_start_advertise_cmd *param)
{
	uint16_t para_len = sizeof(struct gapm_start_advertise_cmd);
	stack_msg_t *msg_buf = msg_alloc_buffer(para_len);

	dbg_func();
  msg_fill(msg_buf, GAPM_START_ADVERTISE_CMD, TASK_GTL, TASK_GAPM, para_len, (uint8_t *)param);
	msg_send(msg_buf);

	return 0;
}
// Set Scan mode Command
int32_t app_gap_start_scanning(struct gapm_start_scan_cmd *param)
{
	uint16_t para_len = sizeof(struct gapm_start_scan_cmd);
	stack_msg_t *msg_buf = msg_alloc_buffer(para_len);

	dbg_func();
  msg_fill(msg_buf, GAPM_START_SCAN_CMD, TASK_GTL, TASK_GAPM, para_len, (uint8_t *)param);
	msg_send(msg_buf);

	return 0;
}
// Set connection initialization Command
int32_t app_gap_start_connection(struct gapm_start_connection_cmd *param)
{
	dbg_func();
	return 0;
}
/* Security / Encryption Toolbox */
// Resolve address command
int32_t app_gap_resolve_addr(struct gapm_resolv_addr_cmd *param)
{
	dbg_func();
	return 0;
}
// Generate a random address.
int32_t app_gap_gen_random_addr(struct gapm_gen_rand_addr_cmd *param)
{
	dbg_func();
	return 0;
}
// Use the AES-128 block in the controller
int32_t app_gap_use_enc_block(struct gapm_use_enc_block_cmd *param)
{
	dbg_func();
	return 0;
}
// Generate a 8-byte random number
int32_t app_gap_gen_random_nb(struct gapm_gen_rand_nb_cmd *param)
{
	dbg_func();
	return 0;
}

/// GAPC API
/* Connection state information */
// Set specific link data configuration. Reply for connection request.
int32_t app_gap_conn_confirm(struct gapc_connection_cfm *param)
{
	uint16_t para_len = sizeof(struct gapc_connection_cfm);
	stack_msg_t *msg_buf = msg_alloc_buffer(para_len);

	dbg_func();
  msg_fill(msg_buf, GAPC_CONNECTION_CFM, TASK_GTL, TASK_GAPM, para_len, (uint8_t *)param);
	msg_send(msg_buf);

	return 0;
}
/* Link management command */
// Request disconnection of current link command.
int32_t app_gap_disconnect(struct gapc_disconnect_cmd *param)
{
	dbg_func();
	return 0;
}
/* Peer device info */
// Retrieve information command
int32_t app_gap_get_peer_info(struct gapc_get_info_cmd *param)
{
	dbg_func();
	return 0;
}
/* Privacy configuration */
// Set Privacy flag command.
int32_t app_gap_set_privacy(struct gapc_set_privacy_cmd *param)
{
	dbg_func();
	return 0;
}
// Set Reconnection Address Value command.
int32_t app_gap_set_recon_addr(struct gapc_set_recon_addr_cmd *param)
{
	dbg_func();
	return 0;
}
/* Connection parameters update */
// Perform update of connection parameters command
int32_t app_gap_conn_param_update(struct gapc_param_update_cmd *param)
{
	dbg_func();
	return 0;
}
// Master confirm or not that parameters proposed by slave are accepted or not
int32_t app_gap_conn_para_update_confirm(struct gapc_param_update_cfm *param)
{
	dbg_func();
	return 0;
}
/* Bonding procedure */
// Start Bonding command procedure
int32_t app_gap_start_bonding(struct gapc_bond_cmd *param)
{
	dbg_func();
	return 0;
}
// Confirm requested bond information.
int32_t app_gap_bond_confirm(struct gapc_bond_cfm *param)
{
	dbg_func();
	return 0;
}
/* Encryption procedure */
// Start Encryption command procedure
int32_t app_gap_start_encrypt(struct gapc_encrypt_cmd *param)
{
	dbg_func();
	return 0;
}
// Confirm requested Encryption information.
int32_t app_gap_encrypt_confirm(struct gapc_encrypt_cfm *param)
{
	dbg_func();
	return 0;
}
/* Security request procedure */
// Start Security Request command procedure
int32_t app_gap_start_security(struct gapc_security_cmd *param)
{
	dbg_func();
	return 0;
}

/// ATT server api
/*** ATTRIBUTE SERVER ***/
// create ATT database for given attributes.
int32_t app_create_gatt_db(attribute_full_desc_t *att_full_desc)
{
	dbg_func();
	return 0;
}
/*Notify Characteristic*/
/*Indicate Characteristic*/
// send an event to peer device
int32_t app_gatt_send_event()
{
	dbg_func();
	return 0;
}
/* Service Changed Characteristic Indication */
//Send a Service Changed indication to a device
int32_t app_gatt_send_svc_change(struct gattc_send_svc_changed_cmd *param)
{
	dbg_func();
	return 0;
}
/* Confirm write command execution. */
// Write command confirmation from upper layers.
int32_t app_gatt_write_confirm(struct gattc_write_cmd_cfm *param)
{
	dbg_func();
	return 0;
}

/// ATT client api
/*** ATTRIBUTE CLIENT ***/
// Server configuration request
int32_t app_gatt_exchange_mtu()
{
	dbg_func();
	return 0;
}
/*Discover All Services */
/*Discover Services by Service UUID*/
/*Find Included Services*/
/*Discover Characteristics by UUID*/
/*Discover All Characteristics of a Service*/
/*Discover All Characteristic Descriptors*/
// Discovery command
int32_t app_gatt_discovery()
{
	dbg_func();
	return 0;
}
/*Read Value*/
/*Read Using UUID*/
/*Read Long Value*/
/*Read Multiple Values*/
// Read command
int32_t app_gatt_read()
{
	dbg_func();
	return 0;
}
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
int32_t app_gatt_write()
{
	dbg_func();
	return 0;
}
/* Cancel / Execute pending write operations */
// Execute write characteristic request
int32_t app_gatt_write_execute()
{
	dbg_func();
	return 0;
}
/* Reception of an indication or notification from peer device. */
// Registration to peer device events (Indication/Notification).
int32_t app_gatt_register_peer_event()
{
	dbg_func();
	return 0;
}

