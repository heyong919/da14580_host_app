/*
 * app_msg.c
 *
 *  Created on: 2016Äê10ÔÂ31ÈÕ
 *      Author: heyong
 */

#include "app_msg.h"
#include "app_api.h"

extern app_stack_callback_t user_stack_callback;

stack_msg_t* msg_alloc_buffer(uint16_t paralen)
{
	uint8_t *buffer = malloc(sizeof(stack_msg_t)+paralen);
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
  int16_t result;
  result = enqueue_tail(msg);
  if(result < 0)
  {
    printf("enqueue failed, queue full!\n");
  }

  // trigger write if possible
  transport_trigger_write();
}

int32_t msg_recv_handler(stack_msg_t *msg) {
  printf("received msg [%x][%x][%x][%x]", msg->type, msg->src_id, msg->dst_id, msg->length);

  switch(msg->type) {
  case GAPM_CMP_EVT:
    user_stack_callback.gapm_cmd_cmp_evt((struct gapm_cmp_evt *)msg->data);
  case GAPM_DEVICE_READY_IND:
    user_stack_callback.gapm_device_ready_indication((struct gapm_device_ready_ind *)msg->data);
    break;
  case GAPM_DEV_NAME_IND:
    user_stack_callback.gapm_dev_name_indication((struct gapm_dev_name_ind *)msg->data);
    break;
  case GAPM_APPEARANCE_IND:
    user_stack_callback.gapm_appearance_indication((struct gapm_appearance_ind *)msg->data);
    break;
  case GAPM_DEV_VERSION_IND:
    user_stack_callback.gapm_dev_version_indication((struct gapm_dev_version_ind *)msg->data);
    break;
  case GAPM_DEV_BDADDR_IND:
    user_stack_callback.gapm_dev_bdaddr_indication((struct gapm_dev_bdaddr_ind *)msg->data);
    break;
  case GAPM_WHITE_LIST_SIZE_IND:
    user_stack_callback.gapm_white_list_size_indication((struct gapm_white_list_size_ind *)msg->data);
    break;
  case GAPM_ADV_REPORT_IND:
    user_stack_callback.gapm_adv_report_indication((struct gapm_adv_report_ind *)msg->data);
    break;
  case GAPM_PEER_NAME_IND:
    user_stack_callback.gapm_peer_name_indication((struct gapm_peer_name_ind *)msg->data);
    break;
  case GAPM_UPDATED_PRIVACY_IND:
    user_stack_callback.gapm_updated_privacy_indication((struct gapm_updated_privacy_ind *)msg->data);
    break;
  case GAPM_UPDATED_RECON_ADDR_IND:
    user_stack_callback.gapm_updated_recon_addr_indication((struct gapm_updated_recon_addr_ind *)msg->data);
    break;
  case GAPM_ADDR_SOLVED_IND:
    user_stack_callback.gapm_addr_solved_indication((struct gapm_addr_solved_ind *)msg->data);
    break;
  case GAPM_USE_ENC_BLOCK_IND:
    user_stack_callback.gapm_use_enc_block_indication((struct gapm_use_enc_block_ind *)msg->data);
    break;
  case GAPM_GEN_RAND_NB_IND:
    user_stack_callback.gapm_gen_rand_nb_indication((struct gapm_gen_rand_nb_ind *)msg->data);
    break;


  }
}

