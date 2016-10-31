/*
 * app_api_impl.c
 *
 *  Created on: 2016Äê9ÔÂ1ÈÕ
 *      Author: heyong
 */

#include "stdtypes.h"
#include "att.h"
#include "app_api.h"
#include "app_msg.h"

typedef int (*func_ptr)();

app_stack_callback_t user_stack_callback =
{ NULL };

// set GAP/GATT stack callbacks
int app_set_stack_callback(app_stack_callback_t *callback)
{
	uint8_t i;
	app_stack_callback_t *p_user_callback = &user_stack_callback;

	for (i = 0; i < sizeof(app_stack_callback_t); i += sizeof(func_ptr))
	{
		if (*((func_ptr)(callback + i)) != NULL)
		{
			*((p_user_callback + i)) = *((callback + i));
		}
	}
	return 0;
}

/// GAPM API
/* Default commands */
// Reset link layer and the host command
int app_gap_reset(struct gapm_reset_cmd *param)
{
	uint16_t para_len = sizeof(struct gapm_reset_cmd);
	stack_msg_t *msg_buf = msg_alloc_buffer(para_len);

	msg_fill(msg_buf, GAPM_RESET_CMD, TASK_GTL, TASK_GAPM, para_len, (uint8_t *)param);
	msg_send(msg_buf);

	return 0;
}
// Cancel ongoing operation
int app_gap_cancel_operation()
{
	uint16_t para_len = 0;
	stack_msg_t *msg_buf = msg_alloc_buffer(para_len);

	msg_fill(msg_buf, GAPM_CANCEL_CMD, TASK_GTL, TASK_GAPM, para_len, NULL);
	msg_send(msg_buf);

	return 0;
}
/* Device Configuration */
// Set device configuration command
int app_gap_set_dev_config(struct gapm_set_dev_config_cmd *param)
{
	uint16_t para_len = sizeof(struct gapm_set_dev_config_cmd);
	stack_msg_t *msg_buf = msg_alloc_buffer(para_len);

	msg_fill(msg_buf, GAPM_SET_DEV_CONFIG_CMD, TASK_GTL, TASK_GAPM, para_len, (uint8_t *)param);
	msg_send(msg_buf);

	return 0;
}
// Set device name command
int app_gap_set_dev_name(struct gapm_set_dev_name_cmd *param)
{
	uint16_t para_len = sizeof(struct gapm_set_dev_name_cmd) + param->length;
	stack_msg_t *msg_buf = msg_alloc_buffer(para_len);

	msg_fill(msg_buf, GAPM_SET_DEV_NAME, TASK_GTL, TASK_GAPM, para_len, (uint8_t *)param);
	msg_send(msg_buf);

	return 0;
}
// Set device channel map
int app_gap_set_channel_map(struct gapm_set_channel_map_cmd *param)
{
}
/* Local device information */
// Get local device info command
int app_gap_get_dev_info(struct gapm_get_dev_info_cmd *param)
{
}
/* White List */
// White List Management Command
int app_gap_white_list_mgt(struct gapm_white_list_mgt_cmd *param)
{
}
/* Air Operations */
// Set advertising mode Command
int app_gap_start_advertising(struct gapm_start_advertise_cmd *param)
{
}
// Set Scan mode Command
int app_gap_start_scanning(struct gapm_start_scan_cmd *param)
{
}
// Set connection initialization Command
int app_gap_start_connection(struct gapm_start_connection_cmd *param)
{
}
/* Security / Encryption Toolbox */
// Resolve address command
int app_gap_resolve_addr(struct gapm_resolv_addr_cmd *param)
{
}
// Generate a random address.
int app_gap_gen_random_addr(struct gapm_gen_rand_addr_cmd *param)
{
}
// Use the AES-128 block in the controller
int app_gap_use_enc_block(struct gapm_use_enc_block_cmd *param)
{
}
// Generate a 8-byte random number
int app_gap_gen_random_nb(struct gapm_gen_rand_nb_cmd *param)
{
}

/// GAPC API
/* Connection state information */
// Set specific link data configuration. Reply for connection request.
int app_gap_conn_confirm(struct gapc_connection_cfm *param)
{
}
/* Link management command */
// Request disconnection of current link command.
int app_gap_disconnect(struct gapc_disconnect_cmd *param)
{
}
/* Peer device info */
// Retrieve information command
int app_gap_get_peer_info(struct gapc_get_info_cmd *param)
{
}
/* Privacy configuration */
// Set Privacy flag command.
int app_gap_set_privacy(struct gapc_set_privacy_cmd *param)
{
}
// Set Reconnection Address Value command.
int app_gap_set_recon_addr(struct gapc_set_recon_addr_cmd *param)
{
}
/* Connection parameters update */
// Perform update of connection parameters command
int app_gap_conn_param_update(struct gapc_param_update_cmd *param)
{
}
// Master confirm or not that parameters proposed by slave are accepted or not
int app_gap_conn_para_update_confirm(struct gapc_param_update_cfm *param)
{
}
/* Bonding procedure */
// Start Bonding command procedure
int app_gap_start_bonding(struct gapc_bond_cmd *param)
{
}
// Confirm requested bond information.
int app_gap_bond_confirm(struct gapc_bond_cfm *param)
{
}
/* Encryption procedure */
// Start Encryption command procedure
int app_gap_start_encrypt(struct gapc_encrypt_cmd *param)
{
}
// Confirm requested Encryption information.
int app_gap_encrypt_confirm(struct gapc_encrypt_cfm *param)
{
}
/* Security request procedure */
// Start Security Request command procedure
int app_gap_start_security(struct gapc_security_cmd *param)
{
}

/// ATT server api
/*** ATTRIBUTE SERVER ***/
// create ATT database for given attributes.
int app_create_gatt_db(attribute_full_desc_t *att_full_desc)
{
}
/*Notify Characteristic*/
/*Indicate Characteristic*/
// send an event to peer device
int app_gatt_send_event()
{
}
/* Service Changed Characteristic Indication */
//Send a Service Changed indication to a device
int app_gatt_send_svc_change(struct gattc_send_svc_changed_cmd *param)
{
}
/* Confirm write command execution. */
// Write command confirmation from upper layers.
int app_gatt_write_confirm(struct gattc_write_cmd_cfm *param)
{
}

/// ATT client api
/*** ATTRIBUTE CLIENT ***/
// Server configuration request
int app_gatt_exchange_mtu()
{
}
/*Discover All Services */
/*Discover Services by Service UUID*/
/*Find Included Services*/
/*Discover Characteristics by UUID*/
/*Discover All Characteristics of a Service*/
/*Discover All Characteristic Descriptors*/
// Discovery command
int app_gatt_discovery()
{
}
/*Read Value*/
/*Read Using UUID*/
/*Read Long Value*/
/*Read Multiple Values*/
// Read command
int app_gatt_read()
{
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
int app_gatt_write()
{
}
/* Cancel / Execute pending write operations */
// Execute write characteristic request
int app_gatt_write_execute()
{
}
/* Reception of an indication or notification from peer device. */
// Registration to peer device events (Indication/Notification).
int app_gatt_register_peer_event()
{
}

