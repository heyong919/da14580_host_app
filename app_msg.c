/*
 * app_msg.c
 *
 *  Created on: 2016Äê10ÔÂ31ÈÕ
 *      Author: heyong
 */

#include <stdio.h>
#include "app_msg.h"
#include "app_api.h"
#include "transport/transport.h"

//extern app_stack_callback_t *user_stack_callback;

stack_msg_t* msg_alloc_buffer(uint16_t paralen)
{
	uint8_t *buffer = malloc(sizeof(stack_msg_t)+paralen);
  memset(buffer, 0, sizeof(stack_msg_t)+paralen);
	return (stack_msg_t *)buffer;
}

void msg_free_buffer(stack_msg_t *msg_p)
{
  free(msg_p);
}

int32_t msg_fill(stack_msg_t *msg_buf, uint16_t type, uint16_t srcid, uint16_t dstid, uint16_t paralen, uint8_t *param)
{
	msg_buf->length = paralen;
	if(paralen)
		memcpy(msg_buf->data, param, paralen);
	msg_buf->type = type;
	msg_buf->src_id = srcid;
	msg_buf->dst_id = dstid;

	return 0;
}

int32_t msg_send(stack_msg_t *msg)
{
  int32_t result;
  result = transport_enqueue_msg(msg);
  if(result < 0)
  {
    printf("enqueue failed, queue full!\n");
  }

  // trigger write if possible
  transport_trigger_write();
  return 0;
}

int32_t msg_recv_handler(stack_msg_t *msg) {
  printf("received msg [%x][%x][%x][%x]\n", msg->type, msg->src_id, msg->dst_id, msg->length);

#if 0
  switch(msg->type) {
    // GAPM message
  case GAPM_CMP_EVT:
    if(user_stack_callback->gapm_cmd_cmp_evt)
      user_stack_callback->gapm_cmd_cmp_evt((struct gapm_cmp_evt *)msg->data);
    break;
  case GAPM_DEVICE_READY_IND:
    if(user_stack_callback->gapm_device_ready_indication)
      user_stack_callback->gapm_device_ready_indication((struct gapm_device_ready_ind *)msg->data);
    break;
  case GAPM_DEV_NAME_IND:
    if(user_stack_callback->gapm_dev_name_indication)
      user_stack_callback->gapm_dev_name_indication((struct gapm_dev_name_ind *)msg->data);
    break;
  case GAPM_APPEARANCE_IND:
    if(user_stack_callback->gapm_appearance_indication)
      user_stack_callback->gapm_appearance_indication((struct gapm_appearance_ind *)msg->data);
    break;
  case GAPM_DEV_VERSION_IND:
    if(user_stack_callback->gapm_dev_version_indication)
      user_stack_callback->gapm_dev_version_indication((struct gapm_dev_version_ind *)msg->data);
    break;
  case GAPM_DEV_BDADDR_IND:
    if(user_stack_callback->gapm_dev_bdaddr_indication)
      user_stack_callback->gapm_dev_bdaddr_indication((struct gapm_dev_bdaddr_ind *)msg->data);
    break;
  case GAPM_DEV_ADV_TX_POWER_IND:
    if(user_stack_callback->gapm_dev_adv_tx_power_indication)
      user_stack_callback->gapm_dev_adv_tx_power_indication((struct gapm_dev_adv_tx_power_ind *)msg->data);
    break;
  case GAPM_WHITE_LIST_SIZE_IND:
    if(user_stack_callback->gapm_white_list_size_indication)
      user_stack_callback->gapm_white_list_size_indication((struct gapm_white_list_size_ind *)msg->data);
    break;
  case GAPM_ADV_REPORT_IND:
    if(user_stack_callback->gapm_adv_report_indication)
      user_stack_callback->gapm_adv_report_indication((struct gapm_adv_report_ind *)msg->data);
    break;
  case GAPM_PEER_NAME_IND:
    if(user_stack_callback->gapm_peer_name_indication)
      user_stack_callback->gapm_peer_name_indication((struct gapm_peer_name_ind *)msg->data);
    break;
  case GAPM_UPDATED_PRIVACY_IND:
    if(user_stack_callback->gapm_updated_privacy_indication)
      user_stack_callback->gapm_updated_privacy_indication((struct gapm_updated_privacy_ind *)msg->data);
    break;
  case GAPM_UPDATED_RECON_ADDR_IND:
    if(user_stack_callback->gapm_updated_recon_addr_indication)
      user_stack_callback->gapm_updated_recon_addr_indication((struct gapm_updated_recon_addr_ind *)msg->data);
    break;
  case GAPM_ADDR_SOLVED_IND:
    if(user_stack_callback->gapm_addr_solved_indication)
      user_stack_callback->gapm_addr_solved_indication((struct gapm_addr_solved_ind *)msg->data);
    break;
  case GAPM_USE_ENC_BLOCK_IND:
    if(user_stack_callback->gapm_use_enc_block_indication)
      user_stack_callback->gapm_use_enc_block_indication((struct gapm_use_enc_block_ind *)msg->data);
    break;
  case GAPM_GEN_RAND_NB_IND:
    if(user_stack_callback->gapm_gen_rand_nb_indication)
      user_stack_callback->gapm_gen_rand_nb_indication((struct gapm_gen_rand_nb_ind *)msg->data);
    break;



    // GAPC message
  case GAPC_CONNECTION_REQ_IND:
    if(user_stack_callback->gapc_connection_req_indication)
      user_stack_callback->gapc_connection_req_indication((struct gapc_connection_req_ind *)msg->data);
    break;
  case GAPC_DISCONNECT_IND:
    if(user_stack_callback->gapc_disconnect_indication)
      user_stack_callback->gapc_disconnect_indication((struct gapc_disconnect_ind *)msg->data);
    break;
  case GAPC_PEER_NAME_IND:
    if(user_stack_callback->gapc_peer_name_indication)
      user_stack_callback->gapc_peer_name_indication((struct gapc_peer_name_ind *)msg->data);
    break;
  case GAPC_PEER_VERSION_IND:
    if(user_stack_callback->gapc_peer_version_indication)
      user_stack_callback->gapc_peer_version_indication((struct gapc_peer_version_ind *)msg->data);
    break;
  case GAPC_PEER_FEATURES_IND:
    if(user_stack_callback->gapc_peer_features_indication)
      user_stack_callback->gapc_peer_features_indication((struct gapc_peer_features_ind *)msg->data);
    break;
  case GAPC_CON_RSSI_IND:
    if(user_stack_callback->gapc_conn_rssi_indication)
      user_stack_callback->gapc_conn_rssi_indication((struct gapc_con_rssi_ind *)msg->data);
    break;
  case GAPC_PRIVACY_IND:
    if(user_stack_callback->gapc_privacy_indication)
      user_stack_callback->gapc_privacy_indication((struct gapc_privacy_ind *)msg->data);
    break;
  case GAPC_RECON_ADDR_IND:
    if(user_stack_callback->gapc_recon_addr_indication)
      user_stack_callback->gapc_recon_addr_indication((struct gapc_recon_addr_ind *)msg->data);
    break;
  case GAPC_PARAM_UPDATE_REQ_IND:
    if(user_stack_callback->gapc_conn_param_update_req_indication)
      user_stack_callback->gapc_conn_param_update_req_indication((struct gapc_param_update_req_ind *)msg->data);
    break;
  case GAPC_PARAM_UPDATED_IND:
    if(user_stack_callback->gapc_conn_param_updated_indication)
      user_stack_callback->gapc_conn_param_updated_indication((struct gapc_param_updated_ind *)msg->data);
    break;
  case GAPC_BOND_REQ_IND:
    if(user_stack_callback->gapc_bond_req_indication)
      user_stack_callback->gapc_bond_req_indication((struct gapc_bond_req_ind *)msg->data);
    break;
  case GAPC_BOND_IND:
    if(user_stack_callback->gapc_bond_info_indication)
      user_stack_callback->gapc_bond_info_indication((struct gapc_bond_ind *)msg->data);
    break;
  case GAPC_ENCRYPT_REQ_IND:
    if(user_stack_callback->gapc_encrypt_req_indication)
      user_stack_callback->gapc_encrypt_req_indication((struct gapc_encrypt_req_ind *)msg->data);
    break;
  case GAPC_ENCRYPT_IND:
    if(user_stack_callback->gapc_encrypt_info_indication)
      user_stack_callback->gapc_encrypt_info_indication((struct gapc_encrypt_ind *)msg->data);
    break;
  case GAPC_SECURITY_IND:
    if(user_stack_callback->gapc_security_indication)
      user_stack_callback->gapc_security_indication((struct gapc_security_ind *)msg->data);
    break;
  case GAPC_SIGN_COUNTER_IND:
    if(user_stack_callback->gapc_sign_counter_indication)
      user_stack_callback->gapc_sign_counter_indication((struct gapc_sign_counter_ind *)msg->data);
    break;
  case GAPC_CON_CHANNEL_MAP_IND:
    if(user_stack_callback->gapc_conn_channel_map_indication)
      user_stack_callback->gapc_conn_channel_map_indication((struct gapc_con_channel_map_ind *)msg->data);
    break;



    // GATTC messages
  case GATTC_DISC_SVC_IND:
    if(user_stack_callback->gattc_disc_svc_indication)
      user_stack_callback->gattc_disc_svc_indication((struct gattc_disc_svc_ind *)msg->data);
    break;
  case GATTC_DISC_SVC_INCL_IND:
    if(user_stack_callback->gattc_disc_svc_incl_indication)
      user_stack_callback->gattc_disc_svc_incl_indication((struct gattc_disc_svc_incl_ind *)msg->data);
    break;
  case GATTC_DISC_CHAR_IND:
    if(user_stack_callback->gattc_disc_char_indication)
      user_stack_callback->gattc_disc_char_indication((struct gattc_disc_char_ind *)msg->data);
    break;
  case GATTC_DISC_CHAR_DESC_IND:
    if(user_stack_callback->gattc_disc_char_desc_indication)
      user_stack_callback->gattc_disc_char_desc_indication((struct gattc_disc_char_desc_ind *)msg->data);
    break;
  case GATTC_READ_IND:
    if(user_stack_callback->gattc_read_indication)
      user_stack_callback->gattc_read_indication((struct gattc_read_ind *)msg->data);
    break;
  case GATTC_EVENT_IND:
    if(user_stack_callback->gattc_notify_indication)
      user_stack_callback->gattc_notify_indication((struct gattc_event_ind *)msg->data);
    break;
  case GATTC_WRITE_CMD_IND:
    if(user_stack_callback->gattc_write_cmd_indication)
      user_stack_callback->gattc_write_cmd_indication((struct gattc_write_cmd_ind *)msg->data);
    break;
  case GATTC_READ_CMD_IND:
    if(user_stack_callback->gattc_read_cmd_indication)
      user_stack_callback->gattc_read_cmd_indication((struct gattc_read_cmd_ind *)msg->data);
    break;

  default:
    printf("unknown event from stack:%x\n",  msg->type);
    break;
  }
#endif

  app_user_operation_handler(msg->src_id, msg->type, msg->data);
  app_user_stack_event_handler(msg->src_id, msg->type, msg->data);

  return 0;
}

