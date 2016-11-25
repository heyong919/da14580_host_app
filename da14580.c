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
#include "stdtypes.h"
#include "co_error.h"
#include "app_msg.h"
#include "app_api.h"
#include "profiles.h"
#include "transport.h"

#define MAX_KNOWN_DEVICE  8

#define DEV_BOND  (1<<1)
#define DEV_CONNECTED  (1<<2)

enum {
  STATE_INIT,
  STATE_ADVERTISING,
  STATE_CONNECTING,
  STATE_CONNECTED,
  STATE_BONDING,
  STATE_BONDED,
};

typedef struct {
  uint16_t state;
  uint16_t role;
  struct bd_addr adv_addr;
  uint16_t conidx;
  uint16_t conhdl;
  uint16_t idx;
  uint16_t rssi;
  uint16_t adv_data_len;
  char adv_data[ADV_DATA_LEN + 1];
  struct gapc_ltk ltk;
  struct gapc_irk irk;
  struct gap_sec_key csrk;
} ble_dev_t;

typedef struct {
  int16_t state;
  int16_t num_of_known_device;
  ble_dev_t devices[MAX_KNOWN_DEVICE]; //FIXME: TODO: device[0] indicate itself and the current connected device info
  void *profile_data;
} app_context_t;

static app_context_t app_cntx;

#if 0
/*
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
*/
#endif

static int32_t cmd_handler(char *cmd_str, uint32_t len) {
  /*
  struct gapm_reset_cmd param = {
    .operation = GAPM_RESET,
  };
  app_gap_reset(&param);
  */
  app_user_start_operations();
  return 0;
}

static int32_t my_common_next_ops(uint16_t src_id, int32_t msg_type, void *param) {
  // handle messages respectively if needed
  switch(msg_type) {
  case GAPM_CMP_EVT:
    {
      struct gapm_cmp_evt *p = (struct gapm_cmp_evt *)param;
      if(p->status != CO_ERROR_NO_ERROR) {
        dbg_printf("gapm_cmp_evt report error!(%x)(%x)\n", p->operation, p->status);
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
    GAPM_RESET
  };
  app_gap_reset(&param);
  return 0;
}

static int32_t user_set_dev_config_perpheral() {
  struct gapm_set_dev_config_cmd param = {
    /*.operation =*/ GAPM_SET_DEV_CONFIG,
  // Device Role
    /*.role =*/ GAP_PERIPHERAL_SLV,
  // IRK
    {0},
  // Device Appearance
    /*.appearance =*/ 0,
  // Device Appearance write permission requirements for peer device
    /*.appearance_write_perm =*/ GAPM_WRITE_DISABLE,
  // Device Name write permission requirements for peer device
    /*.name_write_perm =*/ GAPM_WRITE_DISABLE,
    /*.max_mtu =*/ 64,
  // Peripheral only: *****************************************************************
  // Slave preferred Minimum of connection interval
    /*.con_intv_min =*/ 8,         // 10ms (8*1.25ms)
  // Slave preferred Maximum of connection interval
    /*.con_intv_max =*/ 16,        // 20ms (16*1.25ms)
  // Slave preferred Connection latency
    /*.con_latency  =*/ 0,
  // Slave preferred Link supervision timeout
    /*.superv_to    =*/ 100,
  // Privacy settings bit field
    /*.flags =*/ 0,
  };

  app_gap_set_dev_config(&param);
  return 0;
}

static int32_t user_set_dev_config_central() {
  struct gapm_set_dev_config_cmd param = {
    /*.operation =*/ GAPM_SET_DEV_CONFIG,
  // Device Role
    /*.role =*/ GAP_CENTRAL_MST,
  // IRK
    {0},
  // Device Appearance
    /*.appearance =*/ 0,
  // Device Appearance write permission requirements for peer device
    /*.appearance_write_perm =*/ GAPM_WRITE_DISABLE,
  // Device Name write permission requirements for peer device
    /*.name_write_perm =*/ GAPM_WRITE_DISABLE,
    /*.max_mtu =*/ 64,
  // Peripheral only: *****************************************************************
  // Slave preferred Minimum of connection interval
    /*.con_intv_min =*/ 8,         // 10ms (8*1.25ms)
  // Slave preferred Maximum of connection interval
    /*.con_intv_max =*/ 16,        // 20ms (16*1.25ms)
  // Slave preferred Connection latency
    /*.con_latency  =*/ 0,
  // Slave preferred Link supervision timeout
    /*.superv_to    =*/ 100,
  // Privacy settings bit field
    /*.flags =*/ 0,
  };

  app_gap_set_dev_config(&param);
  return 0;
}

static int32_t user_profile_diss_create_db() {
  struct diss_create_db_req req = {
    /*.features =*/ (DIS_MANUFACTURER_NAME_CHAR_SUP
          | DIS_MODEL_NB_STR_CHAR_SUP
          | DIS_SYSTEM_ID_CHAR_SUP
          | DIS_SW_REV_STR_CHAR_SUP
          | DIS_FIRM_REV_STR_CHAR_SUP
          | DIS_PNP_ID_CHAR_SUP)
  };
  return app_diss_create_db(&req);
}

static int32_t user_profile_diss_config() {
  //static uint8_t step=0;
  uint8_t len;
  {
    // Set Manufacturer Name value in the DB
    struct diss_set_char_val_req *req_name =
        (struct diss_set_char_val_req *)mem_alloc(sizeof(struct diss_set_char_val_req) + APP_DIS_MANUFACTURER_NAME_LEN);
    if(!req_name) {
      dbg_printf("malloc failed!(%d)\n", __LINE__);
      return -1;
    }
    memset(req_name, 0, sizeof(struct diss_set_char_val_req) + APP_DIS_MANUFACTURER_NAME_LEN);
    // Fill in the parameter structure
    req_name->char_code     = DIS_MANUFACTURER_NAME_CHAR;
    req_name->val_len       = APP_DIS_MANUFACTURER_NAME_LEN;
    memcpy(&req_name->val[0], APP_DIS_MANUFACTURER_NAME, APP_DIS_MANUFACTURER_NAME_LEN);

    app_diss_set_char_value(req_name);
    mem_free(req_name);
  }

  // Set Model Number String value in the DB
  {
    struct diss_set_char_val_req *req_mod =
            (struct diss_set_char_val_req *)mem_alloc(sizeof(struct diss_set_char_val_req) + APP_DIS_MODEL_NB_STR_LEN);
    if(!req_mod) {
      dbg_printf("malloc failed!(%d)\n", __LINE__);
      return -1;
    }
    memset(req_mod, 0, sizeof(struct diss_set_char_val_req) + APP_DIS_MODEL_NB_STR_LEN);
    // Fill in the parameter structure
    req_mod->char_code     = DIS_MODEL_NB_STR_CHAR;
    req_mod->val_len       = APP_DIS_MODEL_NB_STR_LEN;
    memcpy(&req_mod->val[0], APP_DIS_MODEL_NB_STR, APP_DIS_MODEL_NB_STR_LEN);

    app_diss_set_char_value(req_mod);
    mem_free(req_mod);
  }

  // Set System ID value in the DB
  {
    struct diss_set_char_val_req *req_id =
            (struct diss_set_char_val_req *)mem_alloc(sizeof(struct diss_set_char_val_req) + APP_DIS_SYSTEM_ID_LEN);
    if(!req_id) {
      dbg_printf("malloc failed!(%d)\n", __LINE__);
      return -1;
    }
    memset(req_id, 0, sizeof(struct diss_set_char_val_req) + APP_DIS_SYSTEM_ID_LEN);
    // Fill in the parameter structure
    req_id->char_code     = DIS_SYSTEM_ID_CHAR;
    req_id->val_len       = APP_DIS_SYSTEM_ID_LEN;
    memcpy(&req_id->val[0], APP_DIS_SYSTEM_ID, APP_DIS_SYSTEM_ID_LEN);

    app_diss_set_char_value(req_id);
    mem_free(req_id);
  }

  // Set the software version in the DB. This is the reference design sw version
  {
    struct diss_set_char_val_req *req_id;
    len = strlen(APP_DIS_SW_REV);
    req_id = (struct diss_set_char_val_req *)mem_alloc(sizeof(struct diss_set_char_val_req) + len);
    if(!req_id) {
      dbg_printf("malloc failed!(%d)\n", __LINE__);
      return -1;
    }
    memset(req_id, 0, sizeof(struct diss_set_char_val_req) + len);
    // Fill in the parameter structure
    req_id->char_code     = DIS_SW_REV_STR_CHAR;
    req_id->val_len       = len;
    memcpy(&req_id->val[0], APP_DIS_SW_REV, len);

    app_diss_set_char_value(req_id);
    mem_free(req_id);
  }

  // Set the firmware version in the DB. This is the common code sw version
  {
    struct diss_set_char_val_req *req_id;
    len = strlen(APP_DIS_FIRM_REV);
    req_id = (struct diss_set_char_val_req *)mem_alloc(sizeof(struct diss_set_char_val_req) + len);
    if(!req_id) {
      dbg_printf("malloc failed!(%d)\n", __LINE__);
      return -1;
    }
    memset(req_id, 0, sizeof(struct diss_set_char_val_req) + len);
    // Fill in the parameter structure
    req_id->char_code     = DIS_FIRM_REV_STR_CHAR;
    req_id->val_len       = len;
    memcpy(&req_id->val[0], APP_DIS_FIRM_REV, len);

    app_diss_set_char_value(req_id);
    mem_free(req_id);
  }

  // Set the PNP ID in the DB
  {
    struct diss_set_char_val_req *req_id;
    uint16_t ids[3];
    req_id = (struct diss_set_char_val_req *)mem_alloc(sizeof(struct diss_set_char_val_req) + DIS_PNP_ID_LEN);
    if(!req_id) {
      dbg_printf("malloc failed!(%d)\n", __LINE__);
      return -1;
    }
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
    mem_free(req_id);
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
  struct gapm_start_advertise_cmd *cmd = mem_alloc(sizeof(struct gapm_start_advertise_cmd));
  if(!cmd) {
    dbg_printf("malloc failed!(%d)\n", __LINE__);
    return -1;
  }
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
  mem_free(cmd);
  app_cntx.state = STATE_ADVERTISING;
  dbg_printf("Advertising...\n");
  return 0;
}

static int32_t my_connect_indication_handler(uint16_t src_id, uint16_t event_type, void *param) {
  struct gapc_connection_req_ind *para = param;
  struct diss_enable_req diss_req;
  struct gapc_connection_cfm *conn_cfm;
  int32_t ret=0;

  app_cntx.state = STATE_CONNECTING;
  dbg_printf("peer device connected(conhdl:%x):[%02x-%02x-%02x-%02x-%02x-%02x]\n", para->conhdl,
        para->peer_addr.addr[0], para->peer_addr.addr[1], para->peer_addr.addr[2],
        para->peer_addr.addr[3], para->peer_addr.addr[4], para->peer_addr.addr[5]);

  // Retrieve the connection index from the GAPC task instance for the connection
  app_cntx.devices[0].conidx = KE_IDX_GET(src_id);

  // Retrieve the connection handle from the parameters
  app_cntx.devices[0].conhdl = para->conhdl;

  memcpy(app_cntx.devices[0].adv_addr.addr, para->peer_addr.addr, sizeof(struct bd_addr));

  diss_req.conhdl = para->conhdl;
  diss_req.con_type = PRF_CON_DISCOVERY;
  diss_req.sec_lvl = 1;
  app_diss_enable(&diss_req); // without response

  conn_cfm = mem_alloc(sizeof(struct gapc_connection_cfm));
  if(!conn_cfm) {
    dbg_printf("malloc failed!(%d)\n", __LINE__);
    return -1;
  }
  memset(conn_cfm, 0, sizeof(struct gapc_connection_cfm));
  conn_cfm->auth = GAP_AUTH_REQ_NO_MITM_NO_BOND;
  conn_cfm->authorize = GAP_AUTHZ_NOT_SET;
  ret = app_gap_conn_confirm(KE_IDX_GET(src_id), conn_cfm);
  mem_free(conn_cfm);

  // app_add_device_to_cntx(conhdl, para->peer_addr_type, para->peer_addr, STATE_CONNECTED);
  // TBD
  app_cntx.state = STATE_CONNECTED;

  return ret;
}

static int32_t my_disconnect_indication_handler(uint16_t src_id, uint16_t event_type, void *param) {
  struct gapc_disconnect_ind *para = param;

  dbg_printf("disconnect indication: handle(%x) reason(%x)\n", para->conhdl, para->reason);
  user_start_advertising();
  return 0;
}

void app_sec_gen_ltk(uint8_t key_size)
{
    // Counter
    uint8_t i;
    app_cntx.devices[0].ltk.key_size = key_size;

    // Randomly generate the LTK and the Random Number
    for (i = 0; i < RAND_NB_LEN; i++)
    {
        app_cntx.devices[0].ltk.randnb.nb[i] = rand()%256;

    }

    // Randomly generate the end of the LTK
    for (i = 0; i < KEY_LEN; i++)
    {
        app_cntx.devices[0].ltk.ltk.key[i] = (((key_size) < (16 - i)) ? 0 : rand()%256);
    }

    // Randomly generate the EDIV
    app_cntx.devices[0].ltk.ediv = rand()%65536;
}

uint32_t app_gen_tk()
{
    // Generate a PIN Code (Between 100000 and 999999)
    return (100000 + (rand()%900000));
}

static int32_t my_peer_bond_req_handler(uint16_t src_id, uint16_t event_type, void *param) {
  struct gapc_bond_req_ind *para = param;
  struct gapc_bond_cfm * bond_cfm;
  int32_t ret=0;

  app_cntx.state = STATE_BONDING;
  bond_cfm = mem_alloc(sizeof(struct gapc_bond_cfm));
  if(!bond_cfm) {
    dbg_printf("malloc failed!(%d)\n", __LINE__);
    return -1;
  }
  memset(bond_cfm, 0, sizeof(struct gapc_bond_cfm));
  switch(para->request) {
    // Bond Pairing request
  case GAPC_PAIRING_REQ:
    {
      bond_cfm->request = GAPC_PAIRING_RSP;
      bond_cfm->accept = true;

      // OOB information
      bond_cfm->data.pairing_feat.oob            = GAP_OOB_AUTH_DATA_NOT_PRESENT;
      // Encryption key size
      bond_cfm->data.pairing_feat.key_size       = KEY_LEN;
      // IO capabilities
      bond_cfm->data.pairing_feat.iocap          = GAP_IO_CAP_NO_INPUT_NO_OUTPUT;
      // Authentication requirements
      bond_cfm->data.pairing_feat.auth           = GAP_AUTH_REQ_NO_MITM_BOND;
      //bond_cfm->data.pairing_feat.auth           = GAP_AUTH_REQ_MITM_NO_BOND;
      //Initiator key distribution
      bond_cfm->data.pairing_feat.ikey_dist      = GAP_KDIST_SIGNKEY;
      //Responder key distribution
      bond_cfm->data.pairing_feat.rkey_dist      = GAP_KDIST_ENCKEY;
      //Security requirements
      bond_cfm->data.pairing_feat.sec_req        = GAP_NO_SEC;
    }
    break;

    // Used to retrieve pairing Temporary Key
  case GAPC_TK_EXCH:
    {
      if(para->data.tk_type == GAP_TK_DISPLAY) {
        // Generate a PIN Code (between 100,000 and 999,999)
        uint32_t pin_code = app_gen_tk();
        bond_cfm->request = GAPC_TK_EXCH;
        bond_cfm->accept = true;

        memset(bond_cfm->data.tk.key, 0, KEY_LEN);

        bond_cfm->data.tk.key[12] = (uint8_t)((pin_code & 0xFF000000) >> 24);
        bond_cfm->data.tk.key[13] = (uint8_t)((pin_code & 0x00FF0000) >> 16);
        bond_cfm->data.tk.key[14] = (uint8_t)((pin_code & 0x0000FF00) >>  8);
        bond_cfm->data.tk.key[15] = (uint8_t)((pin_code & 0x000000FF) >>  0);

        dbg_printf("TK generate[%08x]\n", pin_code);
      }
      else {
        dbg_printf("tk type mismatch!\n"); //ASSERT_ERR(0);
      }
    }
    break;

    // Used for Long Term Key exchange
  case GAPC_LTK_EXCH:
    {
      uint8_t i;
      // generate ltk
      app_sec_gen_ltk(para->data.key_size);

      bond_cfm->request = GAPC_LTK_EXCH;

      bond_cfm->accept = true;

      bond_cfm->data.ltk.key_size = app_cntx.devices[0].ltk.key_size;
      bond_cfm->data.ltk.ediv = app_cntx.devices[0].ltk.ediv;

      memcpy(&(bond_cfm->data.ltk.randnb), &(app_cntx.devices[0].ltk.randnb) , RAND_NB_LEN);
      memcpy(&(bond_cfm->data.ltk.ltk), &(app_cntx.devices[0].ltk.ltk) , KEY_LEN);

      dbg_printf("LTK generate randnb[");
      for(i=0;i<RAND_NB_LEN;i++)
        dbg_printf("%x-", bond_cfm->data.ltk.randnb.nb[i]);
      dbg_printf("] ltk[");
      for(i=0;i<KEY_LEN;i++)
        dbg_printf("%x-", bond_cfm->data.ltk.ltk.key[i]);
      dbg_printf("]\n");
    }
    break;

  default:
    {
      mem_free(bond_cfm);
      return -1;
    }
  }

  ret = app_gap_bond_confirm(KE_IDX_GET(src_id), bond_cfm);
  mem_free(bond_cfm);

  return ret;
}

static int32_t my_peer_bond_info_handler(uint16_t src_id, uint16_t event_type, void *param) {
  struct gapc_bond_ind *para = param;
  uint8_t i;

  switch (para->info) {
  case GAPC_PAIRING_SUCCEED:
    if (para->data.auth | GAP_AUTH_BOND)
      app_cntx.devices[0].state |= DEV_BOND;
    dbg_printf("GAPC_PAIRING_SUCCEED with %x\n", para->data.auth);
    break;

  case GAPC_IRK_EXCH:
    memcpy(app_cntx.devices[0].irk.irk.key, para->data.irk.irk.key, KEY_LEN);
    memcpy(app_cntx.devices[0].irk.addr.addr.addr,
        para->data.irk.addr.addr.addr, BD_ADDR_LEN);
    app_cntx.devices[0].irk.addr.addr_type = para->data.irk.addr.addr_type;
    dbg_printf("bond info: irk[");
    for(i=0;i<KEY_LEN;i++)
      dbg_printf("%x-", para->data.irk.irk.key[i]);
    dbg_printf("]\n");
    break;

  case GAPC_CSRK_EXCH:
    memcpy(app_cntx.devices[0].csrk.key, para->data.csrk.key, KEY_LEN);
    //memcpy(app_cntx.devices[0].irk.addr.addr.addr,
    //    para->data.irk.addr.addr.addr, BD_ADDR_LEN);
    //app_cntx.devices[0].irk.addr.addr_type = para->data.irk.addr.addr_type;
    dbg_printf("bond info: csrk[");
    for(i=0;i<KEY_LEN;i++)
      dbg_printf("%x-", para->data.csrk.key[i]);
    dbg_printf("]\n");
    break;

  case GAPC_LTK_EXCH:
    app_cntx.devices[0].ltk.ediv = para->data.ltk.ediv;
    app_cntx.devices[0].ltk.key_size = para->data.ltk.key_size;
    memcpy(app_cntx.devices[0].ltk.ltk.key, para->data.ltk.ltk.key,
        para->data.ltk.key_size);
    memcpy(app_cntx.devices[0].ltk.randnb.nb, para->data.ltk.randnb.nb, RAND_NB_LEN);
    dbg_printf("bond info: edid[%x] randnb[", para->data.ltk.ediv);
    for(i=0;i<RAND_NB_LEN;i++)
      dbg_printf("%x-", para->data.ltk.randnb.nb[i]);
    dbg_printf("] ltk[");
    for(i=0;i<KEY_LEN;i++)
      dbg_printf("%x-", para->data.ltk.ltk.key[i]);
    dbg_printf("]\n");
    break;

  case GAPC_PAIRING_FAILED:
    {
      struct gapc_disconnect_cmd req;
      app_cntx.devices[0].state &= (~DEV_BOND);

      dbg_printf("GAPC_PAIRING_FAILED with %x\n", para->data.reason);
      req.operation = GAPC_DISCONNECT;
      req.reason = CO_ERROR_REMOTE_USER_TERM_CON;
      app_gap_disconnect(KE_IDX_GET(src_id), &req);
    }
    break;
  }

  return 0;
}

static int32_t my_peer_encrypt_req_handler(uint16_t src_id, uint16_t event_type, void *param) {
  struct gapc_encrypt_req_ind *para = param;
  struct gapc_encrypt_cfm * encypt_cfm;
  struct gapc_connection_cfm *conn_cfm;
  int32_t ret=0;

  encypt_cfm = mem_alloc(sizeof(struct gapc_bond_cfm));
  if(!encypt_cfm) {
    dbg_printf("malloc failed!(%d)\n", __LINE__);
    return -1;
  }
  memset(encypt_cfm, 0, sizeof(struct gapc_encrypt_cfm));

  if(((app_cntx.devices[0].state & STATE_BONDED)
      && (memcmp(&(app_cntx.devices[0].ltk.randnb), &(para->rand_nb), RAND_NB_LEN) == 0)
      && (app_cntx.devices[0].ltk.ediv == para->ediv)))
  {
    dbg_printf("LTK exist, update connection auth\n");
    encypt_cfm->found = true;
    encypt_cfm->key_size = app_cntx.devices[0].ltk.key_size;
    memcpy(&(encypt_cfm->ltk), &(app_cntx.devices[0].ltk.ltk), app_cntx.devices[0].ltk.key_size);

    conn_cfm = mem_alloc(sizeof(struct gapc_bond_cfm));
    if(!conn_cfm) {
      dbg_printf("malloc failed!(%d)\n", __LINE__);
      return -1;
    }
    memset(conn_cfm, 0, sizeof(struct gapc_connection_cfm));
    // update connection auth
    conn_cfm->auth = GAP_AUTH_REQ_NO_MITM_BOND;
    conn_cfm->authorize = GAP_AUTHZ_NOT_SET;
    app_gap_conn_confirm(KE_IDX_GET(src_id), conn_cfm);
    mem_free(conn_cfm);
  }
  else
  {
    encypt_cfm->found = false;
  }

  ret = app_gap_encrypt_confirm(KE_IDX_GET(src_id), encypt_cfm);
  mem_free(encypt_cfm);

  return ret;
}




/* GATT Client
 * gapm reset
 * app_gap_set_dev_config master role
 * app_inq GAPM_START_SCAN_CMD
 * wait for GAPM_ADV_REPORT_IND
 * GAPM_CANCEL_CMD to stop inq
 * choose one report dev and send GAPM_START_CONNECTION_CMD
 * wait for GAPC_CONNECTION_REQ_IND
 * app_connect_confirm GAPC_CONNECTION_CFM
 * profiles enable function
 *     (following is done in profiles tasks on target)
 *     gattc discover (several times for each services and characteristics)
 *     receive GATTC_DISC_SVC_IND / GATTC_DISC_CHAR_IND
 *     receive GATTC_CMP_EVT
 * receive profiles enable confirm
 * app_security_enable GAPC_BOND_CMD to send pairing request if not bond before
 *
 * TBD
 *
*/
/* GATT Server
 * gapm reset
 * init db
 *     create db for SIG profiles
 *     create db for custom profiles
 * gap set dev config (peripheral)
 * start advertising
 *     app_adv_start  GAPM_START_ADVERTISE_CMD
 * wait for connection
 * received GAPC_CONNECTION_REQ_IND and gapm event completion for advertising cmd
 * profiles enable fuction (maybe no response)
 * app_gap_conn_confirm GAPC_CONNECTION_CFM
 *    optional GAPC_ENCRYPT_REQ_IND -> app_gap_encrypt_confirm with LTK non-exist
 *    GAPC_BOND_REQ_IND with request=GAPC_PAIRING_REQ -> app_gap_bond_confirm with request=GAPC_PAIRING_RSP
 *    GAPC_BOND_REQ_IND with request=GAPC_LTK_EXCH -> app_gap_bond_confirm with request=GAPC_LTK_EXCH
 *    GAPC_BOND_IND with GAPC_CSRK_EXCH
 *    GAPC_BOND_IND with GAPC_PAIRING_SUCCEED
 *
*/
/*
 * attmdb_add_service     allocate handles, buffers for attributes space
 * attmdb_add_attribute
 * attmdb_att_set_value
 *
 * attmdb_svc_set_permission
*/

user_operation_t my_operation_list[] = {
  {user_reset_gap, GAPM_CMP_EVT, my_common_next_ops},
  {user_profile_diss_create_db, DISS_CREATE_DB_CFM, my_common_next_ops},
  {user_profile_diss_config, EVENT_BYPASS, my_common_next_ops},
  {user_set_dev_config_perpheral, GAPM_CMP_EVT, my_common_next_ops},
  {user_start_advertising, GAPM_CMP_EVT, my_common_next_ops},

  // don't remove this
  {NULL, 0, NULL}
};

int32_t da14580_init(int16_t port, uint32_t baudrate) {
  memset(&app_cntx, 0, sizeof(app_cntx));
  app_api_init();

  // TODO: add interface config to parameter
  transport_buff_init(port);

  // set stack callback
  //app_set_stack_callback(&my_stack_callback);
  app_add_stack_event_handler(GAPC_CONNECTION_REQ_IND, my_connect_indication_handler);
  app_add_stack_event_handler(GAPC_DISCONNECT_IND, my_disconnect_indication_handler);
  app_add_stack_event_handler(GAPC_BOND_REQ_IND, my_peer_bond_req_handler);
  app_add_stack_event_handler(GAPC_BOND_IND, my_peer_bond_info_handler);
  app_add_stack_event_handler(GAPC_ENCRYPT_REQ_IND, my_peer_encrypt_req_handler);

  // set user operation list
  app_add_user_operations((user_operation_t *)my_operation_list);

  transport_start(port, baudrate, cmd_handler);
  return 0;
}

int32_t da14580_boot_code(int16_t port, uint32_t baudrate, char *code, uint32_t len, char crc) {
  char rd_buf[8];
  char wr_buf[8];
  int8_t step, retry=10;
  int32_t ret;

  step = 1;
  if((ret=transport_start_for_download(port, baudrate)) < 0) {
      dbg_printf("transport_purge_rx failed!(%d)\n", ret);
      return -step;
    }

  step++;
  while(retry-- > 0) {
    if((ret=transport_read_poll(port, baudrate, rd_buf, 1, 200)) < 0) {
      dbg_printf("read STX(0x02) failed!(%d)(%d)\n", ret, retry);
      //return -1;
      continue;
    }

    if(rd_buf[0] != 0x02) {
      dbg_printf("STX(%x) != 0x02 failed!(%d)\n", rd_buf[0], retry);
      //return -2;
      continue;
    }
    break;
  }
  if(retry < 0)
    return -step;

  step++;
  wr_buf[0] = 0x01;
  wr_buf[1] = len&0xFF;
  wr_buf[2] = (len>>8)&0xFF;
  if((ret=transport_write_poll(port, baudrate, wr_buf, 3, 100)) < 0) {
    dbg_printf("send code length failed!(%d)\n", ret);
    return -step;
  }

  step++;
  if((ret=transport_read_poll(port, baudrate, rd_buf, 1, 100)) < 0) {
    dbg_printf("read ACK failed!(%d)\n", ret);
    return -step;
  }

  step++;
  if(rd_buf[0] != 0x06/*ACK*/) {
    dbg_printf("ACK(%x) != 0x06 failed!\n", rd_buf[0]);
    return -step;
  }

  step++;
  if((ret=transport_write_poll(port, baudrate, code, len, 5000)) < 0) {
    dbg_printf("send code data failed!(%d)\n", ret);
    return -step;
  }

  step++;
  if((ret=transport_read_poll(port, baudrate, rd_buf, 1, 500)) < 0) {
    dbg_printf("read code CRC failed!(%d)\n", ret);
    return -step;
  }

  step++;
  //crc = calc_code_crc(const char *code, uint32 len);
  if(rd_buf[0] != crc) {
    dbg_printf("CRC(%x) != %x failed!\n", rd_buf[0], crc);
    return -step;
  }

  step++;
  wr_buf[0] = 0x06; /*ACK*/
  if((ret=transport_write_poll(port, baudrate, wr_buf, 1, 100)) < 0) {
    dbg_printf("send ACK(0x06) failed!(%d)\n", ret);
    return -step;
  }

  transport_stop();
  
  dbg_printf("code start running...\n");
  return 0;
}

