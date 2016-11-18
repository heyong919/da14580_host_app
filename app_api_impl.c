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

#undef QUEUE_TYPE
#define QUEUE_TYPE  user_operation_t*
#include <queue.h>

#define OPS_QUEUE_SIZE (32)
#define MAX_STACK_EVENT_SIZE (50)
static user_operation_t* ops_queue_buffer[OPS_QUEUE_SIZE];
static queue_t ops_queue;
static user_operation_t *user_current_op;

static app_stack_callback_t _user_stack_callback = { NULL };
//static app_stack_callback_t *user_stack_callback = &_user_stack_callback;

static stack_event_handler_map_t user_event_handler_map[MAX_STACK_EVENT_SIZE];

int32_t app_api_init() {
    // init operation queue
	queue_init(&ops_queue, ops_queue_buffer, OPS_QUEUE_SIZE);

    memset(user_event_handler_map, 0, sizeof(user_event_handler_map));
    user_current_op = NULL;
    return 0;
}

// set GAP/GATT stack callbacks
int32_t app_set_stack_callback(app_stack_callback_t *callback)
{
  //TODO: set every non-NULL func in callback to user_stack_callback
  return 0;
}

int32_t app_add_single_operation(user_operation_t *op_ptr) {
  if(op_ptr) {
    if(op_ptr->command) {
      if(enqueue_tail(&ops_queue, &op_ptr) != 0)
        printf("enqueue failed!\n");
    }
  }
  //user_current_op = get_queue_head(&ops_queue);
  return 0;
}

int32_t app_add_user_operations(user_operation_t *op_ptr) {
  while(op_ptr) {
    if(op_ptr->command) {
      if(enqueue_tail(&ops_queue, &op_ptr) != 0)
        printf("enqueue failed!\n");
      op_ptr++;
    }
    else {
      break;
    }
  }
  //user_current_op = get_queue_head(&ops_queue);
  return 0;
}

static int32_t app_user_operation_exec(user_operation_t *op) {
  if(op->command) {
    op->command();
  }
  else {
    // should not reach here
  }
  return 0;
}

int32_t app_user_start_operations() {
  user_current_op = get_queue_head(&ops_queue);
  if(user_current_op)
    app_user_operation_exec(user_current_op);
  return 0;
}

int32_t app_user_next_operateion() {
  dequeue(&ops_queue); // == user_current_op
  user_current_op = get_queue_head(&ops_queue);
  if(user_current_op) {
    app_user_operation_exec(user_current_op);
    if(user_current_op->event_id == EVENT_BYPASS) {
      // EVENT_BYPASS indicate there is no event returned as response of this command
      // we should simply jump to next operation
      app_user_next_operateion();
    }
  }
  return 0;
}

int32_t app_user_operation_handler(uint16_t src_id, int32_t ev_type, void *param) {
  if(!user_current_op)
    return 0;
  if(ev_type == user_current_op->event_id) {
    if(user_current_op->handler)
      user_current_op->handler(src_id, ev_type, param);
    else
      app_user_next_operateion();
  }
  return 0;
}

int32_t app_add_stack_event_handler(uint16_t ev_type, common_stack_event_handler_t event_handler) {
  uint32_t i=0;
  // find current map
  while(user_event_handler_map[i].event_type && user_event_handler_map[i].event_type!=ev_type) {
    i++;
  }
  user_event_handler_map[i].event_type = ev_type;
  user_event_handler_map[i].handler = event_handler;
  return 0;
}

int32_t app_user_stack_event_handler(uint16_t src_id, int32_t ev_type, void *param) {
  uint32_t i=0;
  while(user_event_handler_map[i].event_type) {
	if(user_event_handler_map[i].event_type == ev_type)
		user_event_handler_map[i].handler(src_id, ev_type, param);
    i++;
  }
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
  msg_fill(msg_buf, GAPM_SET_DEV_NAME_CMD, TASK_GTL, TASK_GAPM, para_len, (uint8_t *)param);
  msg_send(msg_buf);

  return 0;
}
// Set device channel map
int32_t app_gap_set_channel_map(struct gapm_set_channel_map_cmd *param)
{
  uint16_t para_len = sizeof(struct gapm_set_channel_map_cmd);
  stack_msg_t *msg_buf = msg_alloc_buffer(para_len);

  dbg_func();
  msg_fill(msg_buf, GAPM_SET_CHANNEL_MAP_CMD, TASK_GTL, TASK_GAPM, para_len, (uint8_t *)param);
  msg_send(msg_buf);
  return 0;
}
/* Local device information */
// Get local device info command
int32_t app_gap_get_dev_info(struct gapm_get_dev_info_cmd *param)
{
  uint16_t para_len = sizeof(struct gapm_get_dev_info_cmd);
  stack_msg_t *msg_buf = msg_alloc_buffer(para_len);

  dbg_func();
  msg_fill(msg_buf, GAPM_GET_DEV_INFO_CMD, TASK_GTL, TASK_GAPM, para_len, (uint8_t *)param);
  msg_send(msg_buf);
  return 0;
}
/* White List */
// White List Management Command
int32_t app_gap_white_list_mgt(struct gapm_white_list_mgt_cmd *param)
{
  uint16_t para_len = sizeof(struct gapm_white_list_mgt_cmd) + param->nb*sizeof(struct gap_bdaddr);
  stack_msg_t *msg_buf = msg_alloc_buffer(para_len);

  dbg_func();
  msg_fill(msg_buf, GAPM_WHITE_LIST_MGT_CMD, TASK_GTL, TASK_GAPM, para_len, (uint8_t *)param);
  msg_send(msg_buf);
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
  uint16_t para_len = sizeof(struct gapm_start_connection_cmd) + param->nb_peers*sizeof(struct gap_bdaddr);
  stack_msg_t *msg_buf = msg_alloc_buffer(para_len);

  dbg_func();
  msg_fill(msg_buf, GAPM_START_CONNECTION_CMD, TASK_GTL, TASK_GAPM, para_len, (uint8_t *)param);
  msg_send(msg_buf);
  return 0;
}
/* Security / Encryption Toolbox */
// Resolve address command
int32_t app_gap_resolve_addr(struct gapm_resolv_addr_cmd *param)
{
  uint16_t para_len = sizeof(struct gapm_resolv_addr_cmd) + param->nb_key*sizeof(struct gap_sec_key);
  stack_msg_t *msg_buf = msg_alloc_buffer(para_len);

  dbg_func();
  msg_fill(msg_buf, GAPM_RESOLV_ADDR_CMD, TASK_GTL, TASK_GAPM, para_len, (uint8_t *)param);
  msg_send(msg_buf);
  return 0;
}
// Generate a random address.
int32_t app_gap_gen_random_addr(struct gapm_gen_rand_addr_cmd *param)
{
  uint16_t para_len = sizeof(struct gapm_gen_rand_addr_cmd);
  stack_msg_t *msg_buf = msg_alloc_buffer(para_len);

  dbg_func();
  msg_fill(msg_buf, GAPM_GEN_RAND_ADDR_CMD, TASK_GTL, TASK_GAPM, para_len, (uint8_t *)param);
  msg_send(msg_buf);
  return 0;
}
// Use the AES-128 block in the controller
int32_t app_gap_use_enc_block(struct gapm_use_enc_block_cmd *param)
{
  uint16_t para_len = sizeof(struct gapm_use_enc_block_cmd);
  stack_msg_t *msg_buf = msg_alloc_buffer(para_len);

  dbg_func();
  msg_fill(msg_buf, GAPM_USE_ENC_BLOCK_CMD, TASK_GTL, TASK_GAPM, para_len, (uint8_t *)param);
  msg_send(msg_buf);
  return 0;
}
// Generate a 8-byte random number
int32_t app_gap_gen_random_nb(struct gapm_gen_rand_nb_cmd *param)
{
  uint16_t para_len = sizeof(struct gapm_gen_rand_nb_cmd);
  stack_msg_t *msg_buf = msg_alloc_buffer(para_len);

  dbg_func();
  msg_fill(msg_buf, GAPM_GEN_RAND_NB_CMD, TASK_GTL, TASK_GAPM, para_len, (uint8_t *)param);
  msg_send(msg_buf);
  return 0;
}

/// GAPC API
/* Connection state information */
// Set specific link data configuration. Reply for connection request.
int32_t app_gap_conn_confirm(uint16_t conidx, struct gapc_connection_cfm *param)
{
  uint16_t para_len = sizeof(struct gapc_connection_cfm);
  stack_msg_t *msg_buf = msg_alloc_buffer(para_len);

  dbg_func();
  msg_fill(msg_buf, GAPC_CONNECTION_CFM, TASK_GTL, KE_BUILD_ID(TASK_GAPC, conidx), para_len, (uint8_t *)param);
  msg_send(msg_buf);

  return 0;
}
/* Link management command */
// Request disconnection of current link command.
int32_t app_gap_disconnect(uint16_t conidx, struct gapc_disconnect_cmd *param)
{
  uint16_t para_len = sizeof(struct gapc_disconnect_cmd);
  stack_msg_t *msg_buf = msg_alloc_buffer(para_len);

  dbg_func();
  msg_fill(msg_buf, GAPC_DISCONNECT_CMD, TASK_GTL, KE_BUILD_ID(TASK_GAPC, conidx), para_len, (uint8_t *)param);
  msg_send(msg_buf);
  return 0;
}
/* Peer device info */
// Retrieve information command
int32_t app_gap_get_peer_info(uint16_t conidx, struct gapc_get_info_cmd *param)
{
  uint16_t para_len = sizeof(struct gapc_get_info_cmd);
  stack_msg_t *msg_buf = msg_alloc_buffer(para_len);

  dbg_func();
  msg_fill(msg_buf, GAPC_GET_INFO_CMD, TASK_GTL, KE_BUILD_ID(TASK_GAPC, conidx), para_len, (uint8_t *)param);
  msg_send(msg_buf);
  return 0;
}
/* Privacy configuration */
// Set Privacy flag command.
int32_t app_gap_set_privacy(uint16_t conidx, struct gapc_set_privacy_cmd *param)
{
  uint16_t para_len = sizeof(struct gapc_set_privacy_cmd);
  stack_msg_t *msg_buf = msg_alloc_buffer(para_len);

  dbg_func();
  msg_fill(msg_buf, GAPC_SET_PRIVACY_CMD, TASK_GTL, KE_BUILD_ID(TASK_GAPC, conidx), para_len, (uint8_t *)param);
  msg_send(msg_buf);
  return 0;
}
// Set Reconnection Address Value command.
int32_t app_gap_set_recon_addr(uint16_t conidx, struct gapc_set_recon_addr_cmd *param)
{
  uint16_t para_len = sizeof(struct gapc_set_recon_addr_cmd);
  stack_msg_t *msg_buf = msg_alloc_buffer(para_len);

  dbg_func();
  msg_fill(msg_buf, GAPC_SET_RECON_ADDR_CMD, TASK_GTL, KE_BUILD_ID(TASK_GAPC, conidx), para_len, (uint8_t *)param);
  msg_send(msg_buf);
  return 0;
}
/* Connection parameters update */
// Perform update of connection parameters command
int32_t app_gap_conn_param_update(uint16_t conidx, struct gapc_param_update_cmd *param)
{
  uint16_t para_len = sizeof(struct gapc_param_update_cmd);
  stack_msg_t *msg_buf = msg_alloc_buffer(para_len);

  dbg_func();
  msg_fill(msg_buf, GAPC_PARAM_UPDATE_CMD, TASK_GTL, KE_BUILD_ID(TASK_GAPC, conidx), para_len, (uint8_t *)param);
  msg_send(msg_buf);
  return 0;
}
// Master confirm or not that parameters proposed by slave are accepted or not
int32_t app_gap_conn_para_update_confirm(uint16_t conidx, struct gapc_param_update_cfm *param)
{
  uint16_t para_len = sizeof(struct gapc_param_update_cfm);
  stack_msg_t *msg_buf = msg_alloc_buffer(para_len);

  dbg_func();
  msg_fill(msg_buf, GAPC_PARAM_UPDATE_CFM, TASK_GTL, KE_BUILD_ID(TASK_GAPC, conidx), para_len, (uint8_t *)param);
  msg_send(msg_buf);
  return 0;
}
/* Bonding procedure */
// Start Bonding command procedure
int32_t app_gap_start_bonding(uint16_t conidx, struct gapc_bond_cmd *param)
{
  uint16_t para_len = sizeof(struct gapc_bond_cmd);
  stack_msg_t *msg_buf = msg_alloc_buffer(para_len);

  dbg_func();
  msg_fill(msg_buf, GAPC_BOND_CMD, TASK_GTL, KE_BUILD_ID(TASK_GAPC, conidx), para_len, (uint8_t *)param);
  msg_send(msg_buf);
  return 0;
}
// Confirm requested bond information.
int32_t app_gap_bond_confirm(uint16_t conidx, struct gapc_bond_cfm *param)
{
  uint16_t para_len = sizeof(struct gapc_bond_cfm);
  stack_msg_t *msg_buf = msg_alloc_buffer(para_len);

  dbg_func();
  msg_fill(msg_buf, GAPC_BOND_CFM, TASK_GTL, KE_BUILD_ID(TASK_GAPC, conidx), para_len, (uint8_t *)param);
  msg_send(msg_buf);
  return 0;
}
/* Encryption procedure */
// Start Encryption command procedure
int32_t app_gap_start_encrypt(uint16_t conidx, struct gapc_encrypt_cmd *param)
{
  uint16_t para_len = sizeof(struct gapc_encrypt_cmd);
  stack_msg_t *msg_buf = msg_alloc_buffer(para_len);

  dbg_func();
  msg_fill(msg_buf, GAPC_ENCRYPT_CMD, TASK_GTL, KE_BUILD_ID(TASK_GAPC, conidx), para_len, (uint8_t *)param);
  msg_send(msg_buf);
  return 0;
}
// Confirm requested Encryption information.
int32_t app_gap_encrypt_confirm(uint16_t conidx, struct gapc_encrypt_cfm *param)
{
  uint16_t para_len = sizeof(struct gapc_encrypt_cfm);
  stack_msg_t *msg_buf = msg_alloc_buffer(para_len);

  dbg_func();
  msg_fill(msg_buf, GAPC_ENCRYPT_CFM, TASK_GTL, KE_BUILD_ID(TASK_GAPC, conidx), para_len, (uint8_t *)param);
  msg_send(msg_buf);
  return 0;
}
/* Security request procedure */
// Start Security Request command procedure
int32_t app_gap_start_security(uint16_t conidx, struct gapc_security_cmd *param)
{
  uint16_t para_len = sizeof(struct gapc_security_cmd);
  stack_msg_t *msg_buf = msg_alloc_buffer(para_len);

  dbg_func();
  msg_fill(msg_buf, GAPC_SECURITY_CMD, TASK_GTL, KE_BUILD_ID(TASK_GAPC, conidx), para_len, (uint8_t *)param);
  msg_send(msg_buf);
  return 0;
}

/// ATT server api
/*** ATTRIBUTE SERVER ***/
// create ATT database for given attributes.
int32_t app_create_gatt_db(attribute_full_desc_t *att_full_desc)
{
  // TODO
  dbg_func();
  return 0;
}
/*Notify Characteristic*/
/*Indicate Characteristic*/
// send an event to peer device
int32_t app_gatt_send_event(uint16_t conidx, struct gattc_send_evt_cmd *param)
{
  uint16_t para_len = sizeof(struct gattc_send_evt_cmd);
  stack_msg_t *msg_buf = msg_alloc_buffer(para_len);

  dbg_func();
  msg_fill(msg_buf, GATTC_SEND_EVT_CMD, TASK_GTL, KE_BUILD_ID(TASK_GATTC, conidx), para_len, (uint8_t *)param);
  msg_send(msg_buf);
  return 0;
}
/* Service Changed Characteristic Indication */
//Send a Service Changed indication to a device
int32_t app_gatt_send_svc_change(uint16_t conidx, struct gattc_send_svc_changed_cmd *param)
{
  dbg_func();
  return 0;
}
/* Confirm write command execution. */
// Write command confirmation from upper layers.
int32_t app_gatt_write_confirm(uint16_t conidx, struct gattc_write_cmd_cfm *param)
{
  uint16_t para_len = sizeof(struct gattc_write_cmd_cfm);
  stack_msg_t *msg_buf = msg_alloc_buffer(para_len);

  dbg_func();
  msg_fill(msg_buf, GATTC_WRITE_CMD_CFM, TASK_GTL, KE_BUILD_ID(TASK_GATTC, conidx), para_len, (uint8_t *)param);
  msg_send(msg_buf);
  return 0;
}

/// ATT client api
/*** ATTRIBUTE CLIENT ***/
// Server configuration request
int32_t app_gatt_exchange_mtu(uint16_t conidx, struct gattc_exc_mtu_cmd *param)
{
  uint16_t para_len = sizeof(struct gattc_exc_mtu_cmd);
  stack_msg_t *msg_buf = msg_alloc_buffer(para_len);

  dbg_func();
  msg_fill(msg_buf, GATTC_EXC_MTU_CMD, TASK_GTL, KE_BUILD_ID(TASK_GATTC, conidx), para_len, (uint8_t *)param);
  msg_send(msg_buf);
  return 0;
}
/*Discover All Services */
/*Discover Services by Service UUID*/
/*Find Included Services*/
/*Discover Characteristics by UUID*/
/*Discover All Characteristics of a Service*/
/*Discover All Characteristic Descriptors*/
// Discovery command
int32_t app_gatt_discovery(uint16_t conidx, struct gattc_disc_cmd *param)
{
  uint16_t para_len = sizeof(struct gattc_disc_cmd) + param->uuid_len;
  stack_msg_t *msg_buf = msg_alloc_buffer(para_len);

  dbg_func();
  msg_fill(msg_buf, GATTC_DISC_CMD, TASK_GTL, KE_BUILD_ID(TASK_GATTC, conidx), para_len, (uint8_t *)param);
  msg_send(msg_buf);
  return 0;
}
/*Read Value*/
/*Read Using UUID*/
/*Read Long Value*/
/*Read Multiple Values*/
// Read command
int32_t app_gatt_read(uint16_t conidx, struct gattc_read_cmd *param)
{
  uint16_t para_len = sizeof(struct gattc_read_cmd);
  stack_msg_t *msg_buf = msg_alloc_buffer(para_len);

  dbg_func();
  msg_fill(msg_buf, GATTC_READ_CMD, TASK_GTL, KE_BUILD_ID(TASK_GATTC, conidx), para_len, (uint8_t *)param);
  msg_send(msg_buf);
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
int32_t app_gatt_write(uint16_t conidx, struct gattc_write_cmd *param)
{
  uint16_t para_len = sizeof(struct gattc_write_cmd) + param->length;
  stack_msg_t *msg_buf = msg_alloc_buffer(para_len);

  dbg_func();
  msg_fill(msg_buf, GATTC_WRITE_CMD, TASK_GTL, KE_BUILD_ID(TASK_GATTC, conidx), para_len, (uint8_t *)param);
  msg_send(msg_buf);
  return 0;
}
/* Cancel / Execute pending write operations */
// Execute write characteristic request
int32_t app_gatt_write_execute(uint16_t conidx, struct gattc_execute_write_cmd *param)
{
  uint16_t para_len = sizeof(struct gattc_execute_write_cmd);
  stack_msg_t *msg_buf = msg_alloc_buffer(para_len);

  dbg_func();
  msg_fill(msg_buf, GATTC_EXECUTE_WRITE_CMD, TASK_GTL, KE_BUILD_ID(TASK_GATTC, conidx), para_len, (uint8_t *)param);
  msg_send(msg_buf);
  return 0;
}
/* Reception of an indication or notification from peer device. */
// Registration to peer device events (Indication/Notification).
int32_t app_gatt_register_peer_event(uint16_t conidx, struct gattc_reg_to_peer_evt_cmd *param)
{
  uint16_t para_len = sizeof(struct gattc_reg_to_peer_evt_cmd);
  stack_msg_t *msg_buf = msg_alloc_buffer(para_len);

  dbg_func();
  msg_fill(msg_buf, GATTC_REG_TO_PEER_EVT_CMD, TASK_GTL, KE_BUILD_ID(TASK_GATTC, conidx), para_len, (uint8_t *)param);
  msg_send(msg_buf);
  return 0;
}

/// SIG profiles related API
/* DISS Profile */
// create attribute db
int32_t app_diss_create_db(struct diss_create_db_req *param)
{
  uint16_t para_len = sizeof(struct diss_create_db_req);
  stack_msg_t *msg_buf = msg_alloc_buffer(para_len);

  dbg_func();
  msg_fill(msg_buf, DISS_CREATE_DB_REQ, TASK_GTL, TASK_DISS, para_len, (uint8_t *)param);
  msg_send(msg_buf);

  return 0;
}
// set diss related char value like manufacturer name, serial num etc.
int32_t app_diss_set_char_value(struct diss_set_char_val_req *param)
{
  uint16_t para_len = sizeof(struct diss_set_char_val_req) + param->val_len;
  stack_msg_t *msg_buf = msg_alloc_buffer(para_len);

  dbg_func();
  msg_fill(msg_buf, DISS_SET_CHAR_VAL_REQ, TASK_GTL, TASK_DISS, para_len, (uint8_t *)param);
  msg_send(msg_buf);
  return 0;
}
int32_t app_diss_enable(struct diss_enable_req *param)
{
  uint16_t para_len = sizeof(struct diss_enable_req);
  stack_msg_t *msg_buf = msg_alloc_buffer(para_len);

  dbg_func();
  msg_fill(msg_buf, DISS_ENABLE_REQ, TASK_GTL, TASK_DISS, para_len, (uint8_t *)param);
  msg_send(msg_buf);

  return 0;
}

