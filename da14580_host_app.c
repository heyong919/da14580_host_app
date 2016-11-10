/*
 ============================================================================
 Name        : da14580_host_app.c
 Author      : hey
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "app_api.h"


static int32_t my_gapm_cmd_cmp_handler(struct gapm_cmp_evt *param)
{
  return 0;
}

static int32_t my_gapm_device_ready_ind_handler(void *param)
{
  return 0;
}

static int32_t my_gapm_dev_name_ind_handler(struct gapm_dev_name_ind *param)
{
  return 0;
}

static int32_t my_gapm_appearance_ind_handler(struct gapm_appearance_ind *param)
{
  return 0;
}

static int32_t my_gapm_dev_version_ind_handler(struct gapm_dev_version_ind *param)
{
  return 0;
}

static int32_t my_gapm_dev_bdaddr_ind_handler(struct gapm_dev_bdaddr_ind *param)
{
  return 0;
}

static int32_t my_gapm_dev_adv_tx_power_ind_handler(struct gapm_dev_adv_tx_power_ind *param)
{
  return 0;
}

static int32_t my_gapm_white_list_size_ind_handler(struct gapm_white_list_size_ind *param)
{
  return 0;
}

static int32_t my_gapm_adv_report_ind_handler(struct gapm_adv_report_ind *param)
{
  return 0;
}

static int32_t my_gapm_peer_name_ind_handler(struct gapm_peer_name_ind *param)
{
  return 0;
}

static int32_t my_gapm_updated_privacy_ind_handler(struct gapm_updated_privacy_ind *param)
{
  return 0;
}

static int32_t my_gapm_updated_recon_addr_ind_handler(struct gapm_updated_recon_addr_ind *param)
{
  return 0;
}

static int32_t my_gapm_addr_solved_ind_handler(struct gapm_addr_solved_ind *param)
{
  return 0;
}

static int32_t my_gapm_use_enc_block_ind_handler(struct gapm_use_enc_block_ind *param)
{
  return 0;
}

static int32_t my_gapm_gen_rand_nb_ind_handler(struct gapm_gen_rand_nb_ind *param)
{
  return 0;
}

static int32_t my_gapc_connection_req_ind_handler(struct gapc_connection_req_ind *param)
{
  return 0;
}

static int32_t my_gapc_disconnect_ind_handler(struct gapc_disconnect_ind *param)
{
  return 0;
}

static int32_t my_gapc_peer_name_ind_handler(struct gapc_peer_name_ind *param)
{
  return 0;
}

static int32_t my_gapc_peer_version_ind_handler(struct gapc_peer_version_ind *param)
{
  return 0;
}

static int32_t my_gapc_peer_features_ind_handler(struct gapc_peer_features_ind *param)
{
  return 0;
}

static int32_t my_gapc_conn_rssi_ind_handler(struct gapc_con_rssi_ind *param)
{
  return 0;
}

static int32_t my_gapc_conn_channel_map_ind_handler(struct gapc_con_channel_map_ind *param)
{
  return 0;
}

static int32_t my_gapc_privacy_ind_handler(struct gapc_privacy_ind *param)
{
  return 0;
}

static int32_t my_gapc_recon_addr_ind_handler(struct gapc_recon_addr_ind *param)
{
  return 0;
}

static int32_t my_gapc_conn_param_update_req_ind_handler(struct gapc_param_update_req_ind *param)
{
  return 0;
}

static int32_t my_gapc_conn_param_updated_ind_handler(struct gapc_param_updated_ind *param)
{
  return 0;
}

static int32_t my_gapc_bond_req_ind_handler(struct gapc_bond_req_ind *param)
{
  return 0;
}

static int32_t my_gapc_bond_info_ind_handler(struct gapc_bond_ind *param)
{
  return 0;
}

static int32_t my_gapc_encrypt_req_ind_handler(struct gapc_encrypt_req_ind *param)
{
  return 0;
}

static int32_t my_gapc_encrypt_info_ind_handler(struct gapc_encrypt_ind *param)
{
  return 0;
}

static int32_t my_gapc_security_ind_handler(struct gapc_security_ind *param)
{
  return 0;
}

static int32_t my_gapc_sign_counter_ind_handler(struct gapc_sign_counter_ind *param)
{
  return 0;
}

static int32_t my_gattc_disc_svc_ind_handler(struct gattc_disc_svc_ind *param)
{
  return 0;
}

static int32_t my_gattc_disc_svc_incl_ind_handler(struct gattc_disc_svc_incl_ind *param)
{
  return 0;
}

static int32_t my_gattc_disc_char_ind_handler(struct gattc_disc_char_ind *param)
{
  return 0;
}

static int32_t my_gattc_disc_char_desc_ind_handler(struct gattc_disc_char_desc_ind *param)
{
  return 0;
}

static int32_t my_gattc_read_ind_handler(struct gattc_read_ind *param)
{
  return 0;
}

static int32_t my_gattc_notify_ind_handler(struct gattc_event_ind *param)
{
  return 0;
}

static int32_t my_gattc_write_cmd_ind_handler(struct gattc_write_cmd_ind *param)
{
  return 0;
}

static int32_t my_gattc_read_cmd_ind_handler(struct gattc_read_cmd_ind *param)
{
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


int main(void) {
	printf("!!!Hello World!!!"); /* prints !!!Hello World!!! */

  // TODO: add interface config to parameter
  transport_init();

  // set stack callback
  app_set_stack_callback(&my_stack_callback);

  transport_start();
	return EXIT_SUCCESS;
}
