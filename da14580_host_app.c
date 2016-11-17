/*
 ============================================================================
 Name        : da14580_host_app.c
 Author      : hey
 Version     :
 Copyright   : Your copyright notice
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "co_error.h"
#include "app_msg.h"
#include "app_api.h"
#include "profiles.h"
#include "transport/transport.h"

#if 0
static int32_t my_gapm_cmd_cmp_handler(struct gapm_cmp_evt *param)
{
	dbg_func();
  if(param->status == CO_ERROR_NO_ERROR) {
    switch(param->operation) {
    case GAPM_RESET:
      {
        struct gapm_set_dev_config_cmd param = {
          .operation = GAPM_SET_DEV_CONFIG,
          .role = GAP_CENTRAL_MST, // Device Role
          .appearance = 0,
          .appearance_write_perm = GAPM_WRITE_DISABLE,
          .name_write_perm = GAPM_WRITE_DISABLE,
        };
        app_gap_set_dev_config(&param);
      }
      break;
    case GAPM_SET_DEV_CONFIG:
      {
        ;
      }
      break;
    }
  }
  return 0;
}

static int32_t my_gapm_device_ready_ind_handler(void *param)
{
  dbg_func();
  return 0;
}

static int32_t my_gapm_dev_name_ind_handler(struct gapm_dev_name_ind *param)
{
  dbg_func();
  return 0;
}

static int32_t my_gapm_appearance_ind_handler(struct gapm_appearance_ind *param)
{
  dbg_func();
  return 0;
}

static int32_t my_gapm_dev_version_ind_handler(struct gapm_dev_version_ind *param)
{
  dbg_func();
  return 0;
}

static int32_t my_gapm_dev_bdaddr_ind_handler(struct gapm_dev_bdaddr_ind *param)
{
  dbg_func();
  return 0;
}

static int32_t my_gapm_dev_adv_tx_power_ind_handler(struct gapm_dev_adv_tx_power_ind *param)
{
  dbg_func();
  return 0;
}

static int32_t my_gapm_white_list_size_ind_handler(struct gapm_white_list_size_ind *param)
{
  dbg_func();
  return 0;
}

static int32_t my_gapm_adv_report_ind_handler(struct gapm_adv_report_ind *param)
{
  dbg_func();
  return 0;
}

static int32_t my_gapm_peer_name_ind_handler(struct gapm_peer_name_ind *param)
{
  dbg_func();
  return 0;
}

static int32_t my_gapm_updated_privacy_ind_handler(struct gapm_updated_privacy_ind *param)
{
  dbg_func();
  return 0;
}

static int32_t my_gapm_updated_recon_addr_ind_handler(struct gapm_updated_recon_addr_ind *param)
{
  dbg_func();
  return 0;
}

static int32_t my_gapm_addr_solved_ind_handler(struct gapm_addr_solved_ind *param)
{
  dbg_func();
  return 0;
}

static int32_t my_gapm_use_enc_block_ind_handler(struct gapm_use_enc_block_ind *param)
{
  dbg_func();
  return 0;
}

static int32_t my_gapm_gen_rand_nb_ind_handler(struct gapm_gen_rand_nb_ind *param)
{
  dbg_func();
  return 0;
}

static int32_t my_gapc_connection_req_ind_handler(struct gapc_connection_req_ind *param)
{
  dbg_func();
  return 0;
}

static int32_t my_gapc_disconnect_ind_handler(struct gapc_disconnect_ind *param)
{
  dbg_func();
  return 0;
}

static int32_t my_gapc_peer_name_ind_handler(struct gapc_peer_name_ind *param)
{
  dbg_func();
  return 0;
}

static int32_t my_gapc_peer_version_ind_handler(struct gapc_peer_version_ind *param)
{
  dbg_func();
  return 0;
}

static int32_t my_gapc_peer_features_ind_handler(struct gapc_peer_features_ind *param)
{
  dbg_func();
  return 0;
}

static int32_t my_gapc_conn_rssi_ind_handler(struct gapc_con_rssi_ind *param)
{
  dbg_func();
  return 0;
}

static int32_t my_gapc_conn_channel_map_ind_handler(struct gapc_con_channel_map_ind *param)
{
  dbg_func();
  return 0;
}

static int32_t my_gapc_privacy_ind_handler(struct gapc_privacy_ind *param)
{
  dbg_func();
  return 0;
}

static int32_t my_gapc_recon_addr_ind_handler(struct gapc_recon_addr_ind *param)
{
  dbg_func();
  return 0;
}

static int32_t my_gapc_conn_param_update_req_ind_handler(struct gapc_param_update_req_ind *param)
{
  dbg_func();
  return 0;
}

static int32_t my_gapc_conn_param_updated_ind_handler(struct gapc_param_updated_ind *param)
{
  dbg_func();
  return 0;
}

static int32_t my_gapc_bond_req_ind_handler(struct gapc_bond_req_ind *param)
{
  dbg_func();
  return 0;
}

static int32_t my_gapc_bond_info_ind_handler(struct gapc_bond_ind *param)
{
  dbg_func();
  return 0;
}

static int32_t my_gapc_encrypt_req_ind_handler(struct gapc_encrypt_req_ind *param)
{
  dbg_func();
  return 0;
}

static int32_t my_gapc_encrypt_info_ind_handler(struct gapc_encrypt_ind *param)
{
  dbg_func();
  return 0;
}

static int32_t my_gapc_security_ind_handler(struct gapc_security_ind *param)
{
  dbg_func();
  return 0;
}

static int32_t my_gapc_sign_counter_ind_handler(struct gapc_sign_counter_ind *param)
{
  dbg_func();
  return 0;
}

static int32_t my_gattc_disc_svc_ind_handler(struct gattc_disc_svc_ind *param)
{
  dbg_func();
  return 0;
}

static int32_t my_gattc_disc_svc_incl_ind_handler(struct gattc_disc_svc_incl_ind *param)
{
  dbg_func();
  return 0;
}

static int32_t my_gattc_disc_char_ind_handler(struct gattc_disc_char_ind *param)
{
  dbg_func();
  return 0;
}

static int32_t my_gattc_disc_char_desc_ind_handler(struct gattc_disc_char_desc_ind *param)
{
  dbg_func();
  return 0;
}

static int32_t my_gattc_read_ind_handler(struct gattc_read_ind *param)
{
  dbg_func();
  return 0;
}

static int32_t my_gattc_notify_ind_handler(struct gattc_event_ind *param)
{
  dbg_func();
  return 0;
}

static int32_t my_gattc_write_cmd_ind_handler(struct gattc_write_cmd_ind *param)
{
  dbg_func();
  return 0;
}

static int32_t my_gattc_read_cmd_ind_handler(struct gattc_read_cmd_ind *param)
{
  dbg_func();
  return 0;
}


static app_stack_callback_t my_stack_callback = {
  .gapm_cmd_cmp_evt = my_gapm_cmd_cmp_handler,
  .gapm_device_ready_indication = my_gapm_device_ready_ind_handler,
  .gapm_dev_name_indication = my_gapm_dev_name_ind_handler,
  .gapm_appearance_indication = my_gapm_appearance_ind_handler,
  .gapm_dev_version_indication = my_gapm_dev_version_ind_handler,
  .gapm_dev_bdaddr_indication = my_gapm_dev_bdaddr_ind_handler,
  .gapm_dev_adv_tx_power_indication = my_gapm_dev_adv_tx_power_ind_handler,
  .gapm_white_list_size_indication = my_gapm_white_list_size_ind_handler,
  .gapm_adv_report_indication = my_gapm_adv_report_ind_handler,
  .gapm_peer_name_indication = my_gapm_peer_name_ind_handler,
  .gapm_updated_privacy_indication = my_gapm_updated_privacy_ind_handler,
  .gapm_updated_recon_addr_indication = my_gapm_updated_recon_addr_ind_handler,
  .gapm_addr_solved_indication = my_gapm_addr_solved_ind_handler,
  .gapm_use_enc_block_indication = my_gapm_use_enc_block_ind_handler,
  .gapm_gen_rand_nb_indication = my_gapm_gen_rand_nb_ind_handler,
  .gapc_connection_req_indication = my_gapc_connection_req_ind_handler,
  .gapc_disconnect_indication = my_gapc_disconnect_ind_handler,
  .gapc_peer_name_indication = my_gapc_peer_name_ind_handler,
  .gapc_peer_version_indication = my_gapc_peer_version_ind_handler,
  .gapc_peer_features_indication = my_gapc_peer_features_ind_handler,
  .gapc_conn_rssi_indication = my_gapc_conn_rssi_ind_handler,
  .gapc_conn_channel_map_indication = my_gapc_conn_channel_map_ind_handler,
  .gapc_privacy_indication = my_gapc_privacy_ind_handler,
  .gapc_recon_addr_indication = my_gapc_recon_addr_ind_handler,
  .gapc_conn_param_update_req_indication = my_gapc_conn_param_update_req_ind_handler,
  .gapc_conn_param_updated_indication = my_gapc_conn_param_updated_ind_handler,
  .gapc_bond_req_indication = my_gapc_bond_req_ind_handler,
  .gapc_bond_info_indication = my_gapc_bond_info_ind_handler,
  .gapc_encrypt_req_indication = my_gapc_encrypt_req_ind_handler,
  .gapc_encrypt_info_indication = my_gapc_encrypt_info_ind_handler,
  .gapc_security_indication = my_gapc_security_ind_handler,
  .gapc_sign_counter_indication = my_gapc_sign_counter_ind_handler,
  .gattc_disc_svc_indication = my_gattc_disc_svc_ind_handler,
  .gattc_disc_svc_incl_indication = my_gattc_disc_svc_incl_ind_handler,
  .gattc_disc_char_indication = my_gattc_disc_char_ind_handler,
  .gattc_disc_char_desc_indication = my_gattc_disc_char_desc_ind_handler,
  .gattc_read_indication = my_gattc_read_ind_handler,
  .gattc_notify_indication = my_gattc_notify_ind_handler,
  .gattc_write_cmd_indication = my_gattc_write_cmd_ind_handler,
 .gattc_read_cmd_indication = my_gattc_read_cmd_ind_handler
};

#endif

static int32_t cmd_handler(char *cmd_str, int16_t len) {
  /*
  struct gapm_reset_cmd param = {
    .operation = GAPM_RESET,
  };
  app_gap_reset(&param);
  */
  app_user_start_operations();
  return 0;
}

static int32_t my_common_next_ops(int32_t msg_type, void *param) {
  // handle messages respectively if needed
  switch(msg_type) {
  case GAPM_CMP_EVT:
    {
      struct gapm_cmp_evt *p = (struct gapm_cmp_evt *)param;
      if(p->status != CO_ERROR_NO_ERROR) {
        printf("gapm_cmp_evt report error!(%x)(%x)\n", p->operation, p->status);
        return -1;
      }
    }
  }

  //usleep(10000);
  // deal with next ops
  app_user_next_operateion();
  return 0;
}

static int32_t user_reset_gap(void) {
  struct gapm_reset_cmd param = {
    .operation = GAPM_RESET,
  };
  app_gap_reset(&param);
  return 0;
}

static int32_t user_set_dev_config_perpheral() {
  struct gapm_set_dev_config_cmd param = {
    .operation = GAPM_SET_DEV_CONFIG,
	// Device Role
    .role = GAP_PERIPHERAL_SLV,
	// Device Appearance
    .appearance = 0,
	// Device Appearance write permission requirements for peer device
    .appearance_write_perm = GAPM_WRITE_DISABLE,
	// Device Name write permission requirements for peer device
    .name_write_perm = GAPM_WRITE_DISABLE,
	// Peripheral only: *****************************************************************
	// Slave preferred Minimum of connection interval
	.con_intv_min = 8,         // 10ms (8*1.25ms)
	// Slave preferred Maximum of connection interval
	.con_intv_max = 16,        // 20ms (16*1.25ms)
	// Slave preferred Connection latency
	.con_latency  = 0,
	// Slave preferred Link supervision timeout
	.superv_to    = 100,
	// Privacy settings bit field
	.flags = 0,
  };

  app_gap_set_dev_config(&param);
  return 0;
}

static int32_t user_set_dev_config_central() {
  struct gapm_set_dev_config_cmd param = {
    .operation = GAPM_SET_DEV_CONFIG,
	// Device Role
    .role = GAP_CENTRAL_MST,
	// Device Appearance
    .appearance = 0,
	// Device Appearance write permission requirements for peer device
    .appearance_write_perm = GAPM_WRITE_DISABLE,
	// Device Name write permission requirements for peer device
    .name_write_perm = GAPM_WRITE_DISABLE,
  };

  app_gap_set_dev_config(&param);
  return 0;
}

static int32_t user_profile_diss_create_db() {
  struct diss_create_db_req req = {
    .features = (DIS_MANUFACTURER_NAME_CHAR_SUP
				  | DIS_MODEL_NB_STR_CHAR_SUP
				  | DIS_SYSTEM_ID_CHAR_SUP
				  | DIS_SW_REV_STR_CHAR_SUP
				  | DIS_FIRM_REV_STR_CHAR_SUP
				  | DIS_PNP_ID_CHAR_SUP),
  };
  return app_diss_create_db(&req);
}

static int32_t user_profile_diss_config() {
	//static uint8_t step=0;
	uint8_t len;
	{
		// Set Manufacturer Name value in the DB
		struct diss_set_char_val_req *req_name =
				(struct diss_set_char_val_req *)malloc(sizeof(struct diss_set_char_val_req) + APP_DIS_MANUFACTURER_NAME_LEN);
		memset(req_name, 0, sizeof(struct diss_set_char_val_req) + APP_DIS_MANUFACTURER_NAME_LEN);
		// Fill in the parameter structure
		req_name->char_code     = DIS_MANUFACTURER_NAME_CHAR;
		req_name->val_len       = APP_DIS_MANUFACTURER_NAME_LEN;
		memcpy(&req_name->val[0], APP_DIS_MANUFACTURER_NAME, APP_DIS_MANUFACTURER_NAME_LEN);

		app_diss_set_char_value(req_name);
	}

	// Set Model Number String value in the DB
	{
		struct diss_set_char_val_req *req_mod =
						(struct diss_set_char_val_req *)malloc(sizeof(struct diss_set_char_val_req) + APP_DIS_MODEL_NB_STR_LEN);
		memset(req_mod, 0, sizeof(struct diss_set_char_val_req) + APP_DIS_MODEL_NB_STR_LEN);
		// Fill in the parameter structure
		req_mod->char_code     = DIS_MODEL_NB_STR_CHAR;
		req_mod->val_len       = APP_DIS_MODEL_NB_STR_LEN;
		memcpy(&req_mod->val[0], APP_DIS_MODEL_NB_STR, APP_DIS_MODEL_NB_STR_LEN);

		app_diss_set_char_value(req_mod);
	}

	// Set System ID value in the DB
	{
		struct diss_set_char_val_req *req_id =
						(struct diss_set_char_val_req *)malloc(sizeof(struct diss_set_char_val_req) + APP_DIS_SYSTEM_ID_LEN);
		memset(req_id, 0, sizeof(struct diss_set_char_val_req) + APP_DIS_SYSTEM_ID_LEN);
		// Fill in the parameter structure
		req_id->char_code     = DIS_SYSTEM_ID_CHAR;
		req_id->val_len       = APP_DIS_SYSTEM_ID_LEN;
		memcpy(&req_id->val[0], APP_DIS_SYSTEM_ID, APP_DIS_SYSTEM_ID_LEN);

		app_diss_set_char_value(req_id);
	}

	// Set the software version in the DB. This is the reference design sw version
	{
		struct diss_set_char_val_req *req_id;
		len = strlen(APP_DIS_SW_REV);
		req_id = (struct diss_set_char_val_req *)malloc(sizeof(struct diss_set_char_val_req) + len);
		memset(req_id, 0, sizeof(struct diss_set_char_val_req) + len);
		// Fill in the parameter structure
		req_id->char_code     = DIS_SW_REV_STR_CHAR;
		req_id->val_len       = len;
		memcpy(&req_id->val[0], APP_DIS_SW_REV, len);

		app_diss_set_char_value(req_id);
	}

	// Set the firmware version in the DB. This is the common code sw version
	{
		struct diss_set_char_val_req *req_id;
		len = strlen(APP_DIS_FIRM_REV);
		req_id = (struct diss_set_char_val_req *)malloc(sizeof(struct diss_set_char_val_req) + len);
		memset(req_id, 0, sizeof(struct diss_set_char_val_req) + len);
		// Fill in the parameter structure
		req_id->char_code     = DIS_FIRM_REV_STR_CHAR;
		req_id->val_len       = len;
		memcpy(&req_id->val[0], APP_DIS_FIRM_REV, len);

		app_diss_set_char_value(req_id);
	}

	// Set the PNP ID in the DB
	{
		struct diss_set_char_val_req *req_id;
		uint16_t ids[3];
		req_id = (struct diss_set_char_val_req *)malloc(sizeof(struct diss_set_char_val_req) + DIS_PNP_ID_LEN);
		memset(req_id, 0, sizeof(struct diss_set_char_val_req) + DIS_PNP_ID_LEN);
		// Fill in the parameter structure
		req_id->char_code     = DIS_PNP_ID_CHAR;
		req_id->val_len       = DIS_PNP_ID_LEN;
		req_id->val[0]        = APP_DISS_PNP_COMPANY_ID_TYPE;
		ids[0]                = APP_DISS_PNP_VENDOR_ID;
		ids[1]                = APP_DISS_PNP_PRODUCT_ID;
		ids[2]                = APP_DISS_PNP_PRODUCT_VERSION;
		memcpy(&req_id->val[1], ids, 6);

		app_diss_set_char_value(req_id);
	}
	return 0;
}

static int32_t user_init_profiles_db(){

  return 0;
}

static int32_t user_start_advertising() {
  uint8_t device_name_length;
  uint8_t device_name_avail_space;
  uint8_t device_name_temp_buf[64];
  struct gapm_start_advertise_cmd *cmd = malloc(sizeof(struct gapm_start_advertise_cmd));
  memset(cmd, 0, sizeof(struct gapm_start_advertise_cmd));
  cmd->op.code     = GAPM_ADV_UNDIRECT;
  cmd->op.addr_src = GAPM_PUBLIC_ADDR;
  cmd->intv_min    = APP_ADV_INT_MIN;
  cmd->intv_max    = APP_ADV_INT_MAX;
  cmd->channel_map = APP_ADV_CHMAP;
  cmd->info.host.mode = GAP_GEN_DISCOVERABLE;
/*-----------------------------------------------------------------------------------
* Set the Advertising Data and the Scan Response Data
*---------------------------------------------------------------------------------*/
  cmd->info.host.adv_data_len = APP_DFLT_ADV_DATA_LEN;
  memcpy(&cmd->info.host.adv_data[0], APP_DFLT_ADV_DATA, cmd->info.host.adv_data_len);
  cmd->info.host.scan_rsp_data_len = APP_SCNRSP_DATA_LENGTH;
  memcpy(&cmd->info.host.scan_rsp_data[0], APP_SCNRSP_DATA, cmd->info.host.scan_rsp_data_len);

  // Get remaining space in the Advertising Data - 2 bytes are used for name length/flag
  device_name_avail_space = APP_ADV_DATA_MAX_SIZE - cmd->info.host.adv_data_len - 2;
  // Check if data can be added to the Advertising data
  if (device_name_avail_space > 0)
  {
	  // Get the Device Name to add in the Advertising Data (Default one or NVDS one)
	  {
		  // Get default Device Name (No name if not enough space)
		  device_name_length = strlen(APP_DFLT_DEVICE_NAME);
		  memcpy(&device_name_temp_buf[0], APP_DFLT_DEVICE_NAME, device_name_length);
	  }

	  if(device_name_length > 0)
	  {
		  // Check available space
		  device_name_length = (device_name_length>device_name_avail_space?device_name_avail_space:device_name_length);

		  // Fill Length
		  cmd->info.host.adv_data[cmd->info.host.adv_data_len]     = device_name_length + 1;
		  // Fill Device Name Flag
		  cmd->info.host.adv_data[cmd->info.host.adv_data_len + 1] = '\x09';
		  // Copy device name
		  memcpy(&cmd->info.host.adv_data[cmd->info.host.adv_data_len + 2], device_name_temp_buf, device_name_length);

		  // Update Advertising Data Length
		  cmd->info.host.adv_data_len += (device_name_length + 2);
	  }
  }

  app_gap_start_advertising(cmd);
  printf("Advertising...\n");
  return 0;
}

/* GATT Client
  1. GAPM_RESET_CMD -> GAPM_CMP_EVT
  2. app_gap_set_dev_config -> GAPM_CMP_EVT
  3. app_gap_start_scanning -> GAPM_ADV_REPORT_IND
  4. app_gap_cancel_operation -> GAPM_CMP_EVT
  5. app_gap_start_connection -> GAPM_CMP_EVT/GAPC_CONNECTION_REQ_IND
  6. 
*/
/* GATT Server
 * gapm reset
 * init db
 *     create db for SIG profiles
 *     create db for custom profiles
 * gap set dev config (peripheral)
 * start advertising
 *     app_easy_gap_undirected_advertise_start  GAPM_START_ADVERTISE_CMD
 * wait for connection
 *
*/
/*
 * attmdb_add_service     allocate handles, buffers for attributes space
 * attmdb_add_attribute
 * attmdb_att_set_value
 *
 * attmdb_svc_set_permission
*/

static user_operation_t my_operation_list[] = {
  {user_reset_gap, GAPM_CMP_EVT, my_common_next_ops},
  {user_profile_diss_create_db, DISS_CREATE_DB_CFM, my_common_next_ops},
  {user_profile_diss_config, EVENT_BYPASS, my_common_next_ops},
  {user_set_dev_config_perpheral, GAPM_CMP_EVT, my_common_next_ops},
  {user_start_advertising, GAPM_CMP_EVT, my_common_next_ops},

  // don't remove this
  {NULL, 0, NULL}
};

int main(void) {
  printf("!!!Hello World!!!"); /* prints !!!Hello World!!! */
  app_api_init();

  // TODO: add interface config to parameter
  transport_init(12);

  // set stack callback
  //app_set_stack_callback(&my_stack_callback);
  //app_add_stack_event_handler()

  // set user operation list
  app_add_user_operations((user_operation_t *)my_operation_list);

  transport_start(cmd_handler);
	return EXIT_SUCCESS;
}
