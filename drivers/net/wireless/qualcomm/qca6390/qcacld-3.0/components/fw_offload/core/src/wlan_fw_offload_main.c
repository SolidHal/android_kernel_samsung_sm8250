/*
 * Copyright (c) 2018-2019 The Linux Foundation. All rights reserved.
 *
 * Permission to use, copy, modify, and/or distribute this software for
 * any purpose with or without fee is hereby granted, provided that the
 * above copyright notice and this permission notice appear in all
 * copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 * AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 * PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */
/**
 * DOC: define internal APIs related to the fwol component
 */

#include "wlan_fw_offload_main.h"
#include "cds_api.h"
#include "wma.h"

struct wlan_fwol_psoc_obj *fwol_get_psoc_obj(struct wlan_objmgr_psoc *psoc)
{
	return wlan_objmgr_psoc_get_comp_private_obj(psoc,
						     WLAN_UMAC_COMP_FWOL);
}

/**
 * fwol_mpta_helper_config_get: Populate btc_mpta_helper_enable from cfg
 * @psoc: The global psoc handler
 * @coex_config: The cfg structure
 *
 * Return: none
 */
#ifdef FEATURE_MPTA_HELPER
static void
fwol_mpta_helper_config_get(struct wlan_objmgr_psoc *psoc,
			    struct wlan_fwol_coex_config *coex_config)
{
	coex_config->btc_mpta_helper_enable =
				cfg_get(psoc, CFG_COEX_MPTA_HELPER);
}
#else
static void
fwol_mpta_helper_config_get(struct wlan_objmgr_psoc *psoc,
			    struct wlan_fwol_coex_config *coex_config)
{
}
#endif

static void
fwol_init_coex_config_in_cfg(struct wlan_objmgr_psoc *psoc,
			     struct wlan_fwol_coex_config *coex_config)
{
	coex_config->btc_mode = cfg_get(psoc, CFG_BTC_MODE);
	coex_config->antenna_isolation = cfg_get(psoc, CFG_ANTENNA_ISOLATION);
	coex_config->max_tx_power_for_btc =
				cfg_get(psoc, CFG_MAX_TX_POWER_FOR_BTC);
	coex_config->wlan_low_rssi_threshold =
				cfg_get(psoc, CFG_WLAN_LOW_RSSI_THRESHOLD);
	coex_config->bt_low_rssi_threshold =
				cfg_get(psoc, CFG_BT_LOW_RSSI_THRESHOLD);
	coex_config->bt_interference_low_ll =
				cfg_get(psoc, CFG_BT_INTERFERENCE_LOW_LL);
	coex_config->bt_interference_low_ul =
				cfg_get(psoc, CFG_BT_INTERFERENCE_LOW_UL);
	coex_config->bt_interference_medium_ll =
				cfg_get(psoc, CFG_BT_INTERFERENCE_MEDIUM_LL);
	coex_config->bt_interference_medium_ul =
				cfg_get(psoc, CFG_BT_INTERFERENCE_MEDIUM_UL);
	coex_config->bt_interference_high_ll =
				cfg_get(psoc, CFG_BT_INTERFERENCE_HIGH_LL);
	coex_config->bt_interference_high_ul =
				cfg_get(psoc, CFG_BT_INTERFERENCE_HIGH_UL);
	fwol_mpta_helper_config_get(psoc, coex_config);
}

static void
fwol_init_thermal_temp_in_cfg(struct wlan_objmgr_psoc *psoc,
			      struct wlan_fwol_thermal_temp *thermal_temp)
{
	thermal_temp->thermal_temp_min_level[0] =
				cfg_get(psoc, CFG_THERMAL_TEMP_MIN_LEVEL0);
	thermal_temp->thermal_temp_max_level[0] =
				cfg_get(psoc, CFG_THERMAL_TEMP_MAX_LEVEL0);
	thermal_temp->thermal_temp_min_level[1] =
				cfg_get(psoc, CFG_THERMAL_TEMP_MIN_LEVEL1);
	thermal_temp->thermal_temp_max_level[1] =
				cfg_get(psoc, CFG_THERMAL_TEMP_MAX_LEVEL1);
	thermal_temp->thermal_temp_min_level[2] =
				cfg_get(psoc, CFG_THERMAL_TEMP_MIN_LEVEL2);
	thermal_temp->thermal_temp_max_level[2] =
				cfg_get(psoc, CFG_THERMAL_TEMP_MAX_LEVEL2);
	thermal_temp->thermal_temp_min_level[3] =
				cfg_get(psoc, CFG_THERMAL_TEMP_MIN_LEVEL3);
	thermal_temp->thermal_temp_max_level[3] =
				cfg_get(psoc, CFG_THERMAL_TEMP_MAX_LEVEL3);

	thermal_temp->thermal_mitigation_enable =
				cfg_get(psoc, CFG_THERMAL_MITIGATION_ENABLE);
	thermal_temp->throttle_period = cfg_get(psoc, CFG_THROTTLE_PERIOD);
	thermal_temp->throttle_dutycycle_level[0] =
				cfg_get(psoc, CFG_THROTTLE_DUTY_CYCLE_LEVEL0);
	thermal_temp->throttle_dutycycle_level[1]=
				cfg_get(psoc, CFG_THROTTLE_DUTY_CYCLE_LEVEL1);
	thermal_temp->throttle_dutycycle_level[2]=
				cfg_get(psoc, CFG_THROTTLE_DUTY_CYCLE_LEVEL2);
	thermal_temp->throttle_dutycycle_level[3]=
				cfg_get(psoc, CFG_THROTTLE_DUTY_CYCLE_LEVEL3);
}

QDF_STATUS fwol_init_neighbor_report_cfg(struct wlan_objmgr_psoc *psoc,
					 struct wlan_fwol_neighbor_report_cfg
					 *fwol_neighbor_report_cfg)
{
	if (!fwol_neighbor_report_cfg) {
		fwol_err("Neighbor report config pointer null");
		return QDF_STATUS_E_FAILURE;
	}

	fwol_neighbor_report_cfg->enable_bitmask =
		cfg_get(psoc, CFG_OFFLOAD_11K_ENABLE_BITMASK);
	fwol_neighbor_report_cfg->params_bitmask =
		cfg_get(psoc, CFG_OFFLOAD_NEIGHBOR_REPORT_PARAMS_BITMASK);
	fwol_neighbor_report_cfg->time_offset =
		cfg_get(psoc, CFG_OFFLOAD_NEIGHBOR_REPORT_TIME_OFFSET);
	fwol_neighbor_report_cfg->low_rssi_offset =
		cfg_get(psoc, CFG_OFFLOAD_NEIGHBOR_REPORT_LOW_RSSI_OFFSET);
	fwol_neighbor_report_cfg->bmiss_count_trigger =
		cfg_get(psoc, CFG_OFFLOAD_NEIGHBOR_REPORT_BMISS_COUNT_TRIGGER);
	fwol_neighbor_report_cfg->per_threshold_offset =
		cfg_get(psoc, CFG_OFFLOAD_NEIGHBOR_REPORT_PER_THRESHOLD_OFFSET);
	fwol_neighbor_report_cfg->cache_timeout =
		cfg_get(psoc, CFG_OFFLOAD_NEIGHBOR_REPORT_CACHE_TIMEOUT);
	fwol_neighbor_report_cfg->max_req_cap =
		cfg_get(psoc, CFG_OFFLOAD_NEIGHBOR_REPORT_MAX_REQ_CAP);

	return QDF_STATUS_SUCCESS;
}

QDF_STATUS
fwol_init_adapt_dwelltime_in_cfg(
			struct wlan_objmgr_psoc *psoc,
			struct adaptive_dwelltime_params *dwelltime_params)
{
	if (!dwelltime_params) {
		fwol_err("dwelltime params config pointer null");
		return QDF_STATUS_E_FAILURE;
	}
	dwelltime_params->is_enabled =
			cfg_get(psoc, CFG_ADAPTIVE_DWELL_MODE_ENABLED);
	dwelltime_params->dwelltime_mode =
			cfg_get(psoc, CFG_GLOBAL_ADAPTIVE_DWELL_MODE);
	dwelltime_params->lpf_weight =
			cfg_get(psoc, CFG_ADAPT_DWELL_LPF_WEIGHT);
	dwelltime_params->passive_mon_intval =
			cfg_get(psoc, CFG_ADAPT_DWELL_PASMON_INTVAL);
	dwelltime_params->wifi_act_threshold =
			cfg_get(psoc, CFG_ADAPT_DWELL_WIFI_THRESH);

	return QDF_STATUS_SUCCESS;
}

QDF_STATUS
fwol_set_adaptive_dwelltime_config(
			struct adaptive_dwelltime_params *dwelltime_params)
{
	tp_wma_handle wma_handle;
	QDF_STATUS status;

	wma_handle = cds_get_context(QDF_MODULE_ID_WMA);
	if (!wma_handle) {
		fwol_err("wma handle is null");
		return QDF_STATUS_E_FAILURE;
	}
	status = wma_send_adapt_dwelltime_params(wma_handle,
						 dwelltime_params);
	return status;
}
/**
 * fwol_parse_probe_req_ouis - form ouis from ini gProbeReqOUIs
 * @psoc: Pointer to struct wlan_objmgr_psoc context
 * @whitelist: Pointer to struct wlan_fwol_ie_whitelist
 *
 * This function parses the ini string gProbeReqOUIs which needs be to in the
 * following format:
 * "<8 characters of [0-9] or [A-F]>space<8 characters from [0-9] etc.,"
 * example: "AABBCCDD 1122EEFF"
 * and the logic counts the number of OUIS and allocates the memory
 * for every valid OUI and is stored in struct hdd_context
 *
 * Return: None
 */
static void fwol_parse_probe_req_ouis(struct wlan_objmgr_psoc *psoc,
				      struct wlan_fwol_ie_whitelist *whitelist)
{
	uint8_t probe_req_ouis[MAX_PRB_REQ_VENDOR_OUI_INI_LEN] = {0};
	uint32_t *voui = whitelist->probe_req_voui;
	char *str;
	uint8_t *token;
	uint32_t oui_indx = 0;
	int ret;
	uint32_t hex_value;

	qdf_str_lcopy(probe_req_ouis, cfg_get(psoc, CFG_PROBE_REQ_OUI),
		      MAX_PRB_REQ_VENDOR_OUI_INI_LEN);
	str = probe_req_ouis;
	whitelist->no_of_probe_req_ouis = 0;

	if (!qdf_str_len(str)) {
		fwol_info("NO OUIs to parse");
		return;
	}

	token = strsep(&str, " ");
	while (token) {
		if (qdf_str_len(token) != 8)
			goto next_token;

		ret = qdf_kstrtouint(token, 16, &hex_value);
		if (ret)
			goto next_token;

		voui[oui_indx++] = cpu_to_be32(hex_value);
		if (oui_indx >= MAX_PROBE_REQ_OUIS)
			break;
next_token:
		token = strsep(&str, " ");
	}

	if (!oui_indx) {
		whitelist->ie_whitelist = false;
		return;
	}

	whitelist->no_of_probe_req_ouis = oui_indx;
}

/**
 * fwol_validate_ie_bitmaps() - Validate all IE whitelist bitmap param values
 * @psoc: Pointer to struct wlan_objmgr_psoc
 * @whitelist: Pointer to struct wlan_fwol_ie_whitelist
 *
 * Return: True if all bitmap values are valid, else false
 */
static bool fwol_validate_ie_bitmaps(struct wlan_objmgr_psoc *psoc,
				     struct wlan_fwol_ie_whitelist *whitelist)
{
	if (!(whitelist->ie_bitmap_0 && whitelist->ie_bitmap_1 &&
	      whitelist->ie_bitmap_2 && whitelist->ie_bitmap_3 &&
	      whitelist->ie_bitmap_4 && whitelist->ie_bitmap_5 &&
	      whitelist->ie_bitmap_6 && whitelist->ie_bitmap_7))
		return false;

	/*
	 * check whether vendor oui IE is set and OUIs are present, each OUI
	 * is entered in the form of string of 8 characters from ini, therefore,
	 * for atleast one OUI, minimum length is 8 and hence this string length
	 * is checked for minimum of 8
	 */
	if ((whitelist->ie_bitmap_6 & VENDOR_SPECIFIC_IE_BITMAP) &&
	    (qdf_str_len(cfg_get(psoc, CFG_PROBE_REQ_OUI)) < 8))
		return false;

	/* check whether vendor oui IE is not set but OUIs are present */
	if (!(whitelist->ie_bitmap_6 & VENDOR_SPECIFIC_IE_BITMAP) &&
	    (qdf_str_len(cfg_get(psoc, CFG_PROBE_REQ_OUI)) > 0))
		return false;

	return true;
}

static void
fwol_init_ie_whiltelist_in_cfg(struct wlan_objmgr_psoc *psoc,
			       struct wlan_fwol_ie_whitelist *whitelist)
{
	whitelist->ie_whitelist = cfg_get(psoc, CFG_PROBE_REQ_IE_WHITELIST);
	whitelist->ie_bitmap_0 = cfg_get(psoc, CFG_PROBE_REQ_IE_BIT_MAP0);
	whitelist->ie_bitmap_1 = cfg_get(psoc, CFG_PROBE_REQ_IE_BIT_MAP1);
	whitelist->ie_bitmap_2 = cfg_get(psoc, CFG_PROBE_REQ_IE_BIT_MAP2);
	whitelist->ie_bitmap_3 = cfg_get(psoc, CFG_PROBE_REQ_IE_BIT_MAP3);
	whitelist->ie_bitmap_4 = cfg_get(psoc, CFG_PROBE_REQ_IE_BIT_MAP4);
	whitelist->ie_bitmap_5 = cfg_get(psoc, CFG_PROBE_REQ_IE_BIT_MAP5);
	whitelist->ie_bitmap_6 = cfg_get(psoc, CFG_PROBE_REQ_IE_BIT_MAP6);
	whitelist->ie_bitmap_7 = cfg_get(psoc, CFG_PROBE_REQ_IE_BIT_MAP7);
	if (!fwol_validate_ie_bitmaps(psoc, whitelist))
		whitelist->ie_whitelist = false;
	fwol_parse_probe_req_ouis(psoc, whitelist);
}

/**
 * ucfg_fwol_fetch_dhcp_server_settings: Populate the enable_dhcp_server_offload
 * and dhcp_max_num_clients from cfg
 * @psoc: The global psoc handler
 * @fwol_cfg: The cfg structure
 *
 * Return: none
 */
#ifdef DHCP_SERVER_OFFLOAD
static void ucfg_fwol_fetch_dhcp_server_settings(struct wlan_objmgr_psoc *psoc,
						 struct wlan_fwol_cfg *fwol_cfg)
{
	fwol_cfg->enable_dhcp_server_offload =
			cfg_get(psoc, CFG_DHCP_SERVER_OFFLOAD_SUPPORT);
	fwol_cfg->dhcp_max_num_clients =
			cfg_get(psoc, CFG_DHCP_SERVER_OFFLOAD_NUM_CLIENT);
}
#else
static void ucfg_fwol_fetch_dhcp_server_settings(struct wlan_objmgr_psoc *psoc,
						 struct wlan_fwol_cfg *fwol_cfg)
{
}
#endif

/**
 * ucfg_fwol_fetch_tsf_gpio_pin: Populate the tsf_gpio_pin from cfg
 * @psoc: The global psoc handler
 * @fwol_cfg: The cfg structure
 *
 * Return: none
 */
#ifdef WLAN_FEATURE_TSF
static void ucfg_fwol_fetch_tsf_gpio_pin(struct wlan_objmgr_psoc *psoc,
					 struct wlan_fwol_cfg *fwol_cfg)
{
	fwol_cfg->tsf_gpio_pin = cfg_get(psoc, CFG_SET_TSF_GPIO_PIN);
}
#else
static void ucfg_fwol_fetch_tsf_gpio_pin(struct wlan_objmgr_psoc *psoc,
					 struct wlan_fwol_cfg *fwol_cfg)
{
}
#endif

/**
 * ucfg_fwol_init_tsf_ptp_options: Populate the tsf_ptp_options from cfg
 * @psoc: The global psoc handler
 * @fwol_cfg: The cfg structure
 *
 * Return: none
 */
#if defined(WLAN_FEATURE_TSF) && defined(WLAN_FEATURE_TSF_PLUS)
static void ucfg_fwol_init_tsf_ptp_options(struct wlan_objmgr_psoc *psoc,
					   struct wlan_fwol_cfg *fwol_cfg)
{
	fwol_cfg->tsf_ptp_options = cfg_get(psoc, CFG_SET_TSF_PTP_OPT);
}
#else
static void ucfg_fwol_init_tsf_ptp_options(struct wlan_objmgr_psoc *psoc,
					   struct wlan_fwol_cfg *fwol_cfg)
{
}
#endif

#ifdef WLAN_FEATURE_TSF_PLUS_EXT_GPIO_IRQ
/**
 * ucfg_fwol_fetch_tsf_irq_host_gpio_pin: Populate the
 * tsf_irq_host_gpio_pin from cfg
 * @psoc: The global psoc handler
 * @fwol_cfg: The cfg structure
 *
 * This function is used to populate the cfg value of host platform
 * gpio pin configured to receive tsf interrupt from fw.
 *
 * Return: none
 */
static void
ucfg_fwol_fetch_tsf_irq_host_gpio_pin(struct wlan_objmgr_psoc *psoc,
				      struct wlan_fwol_cfg *fwol_cfg)
{
	fwol_cfg->tsf_irq_host_gpio_pin =
		cfg_get(psoc, CFG_SET_TSF_IRQ_HOST_GPIO_PIN);
}
#else
static void
ucfg_fwol_fetch_tsf_irq_host_gpio_pin(struct wlan_objmgr_psoc *psoc,
				      struct wlan_fwol_cfg *fwol_cfg)
{
}
#endif
/**
 * ucfg_fwol_init_sae_cfg: Populate the sae control config from cfg
 * @psoc: The global psoc handler
 * @fwol_cfg: The cfg structure
 *
 * Return: none
 */
#ifdef WLAN_FEATURE_SAE
static void ucfg_fwol_init_sae_cfg(struct wlan_objmgr_psoc *psoc,
				   struct wlan_fwol_cfg *fwol_cfg)
{
	fwol_cfg->sae_enable = cfg_get(psoc, CFG_IS_SAE_ENABLED);
}
#else
static void ucfg_fwol_init_sae_cfg(struct wlan_objmgr_psoc *psoc,
				   struct wlan_fwol_cfg *fwol_cfg)
{
}
#endif

/**
 * ucfg_fwol_fetch_ra_filter: Populate the RA filter enabled or not from cfg
 * @psoc: The global psoc handler
 * @fwol_cfg: The cfg structure
 *
 * Return: none
 */
#ifdef FEATURE_WLAN_RA_FILTERING
static void ucfg_fwol_fetch_ra_filter(struct wlan_objmgr_psoc *psoc,
				      struct wlan_fwol_cfg *fwol_cfg)
{
	fwol_cfg->is_rate_limit_enabled = cfg_get(psoc, CFG_RA_FILTER_ENABLE);
}
#else
static void ucfg_fwol_fetch_ra_filter(struct wlan_objmgr_psoc *psoc,
				      struct wlan_fwol_cfg *fwol_cfg)
{
}
#endif

QDF_STATUS fwol_cfg_on_psoc_enable(struct wlan_objmgr_psoc *psoc)
{
	QDF_STATUS status = QDF_STATUS_SUCCESS;
	struct wlan_fwol_psoc_obj *fwol_obj;
	struct wlan_fwol_cfg *fwol_cfg;
	qdf_size_t enable_fw_module_log_level_num;

	fwol_obj = fwol_get_psoc_obj(psoc);
	if (!fwol_obj) {
		fwol_err("Failed to get FWOL Obj");
		return QDF_STATUS_E_FAILURE;
	}

	fwol_cfg = &fwol_obj->cfg;

	fwol_init_coex_config_in_cfg(psoc, &fwol_cfg->coex_config);
	fwol_init_thermal_temp_in_cfg(psoc, &fwol_cfg->thermal_temp_cfg);
	fwol_init_ie_whiltelist_in_cfg(psoc, &fwol_cfg->ie_whitelist_cfg);
	fwol_init_neighbor_report_cfg(psoc, &fwol_cfg->neighbor_report_cfg);
	fwol_cfg->ani_enabled = cfg_get(psoc, CFG_ENABLE_ANI);
	fwol_cfg->enable_rts_sifsbursting =
				cfg_get(psoc, CFG_SET_RTS_FOR_SIFS_BURSTING);
	fwol_cfg->max_mpdus_inampdu = cfg_get(psoc, CFG_MAX_MPDUS_IN_AMPDU);
	fwol_cfg->arp_ac_category = cfg_get(psoc, CFG_ARP_AC_CATEGORY);
	fwol_cfg->enable_phy_reg_retention = cfg_get(psoc, CFG_ENABLE_PHY_REG);
	fwol_cfg->upper_brssi_thresh = cfg_get(psoc, CFG_UPPER_BRSSI_THRESH);
	fwol_cfg->lower_brssi_thresh = cfg_get(psoc, CFG_LOWER_BRSSI_THRESH);
	fwol_cfg->enable_dtim_1chrx = cfg_get(psoc, CFG_DTIM_1CHRX_ENABLE);
	fwol_cfg->alternative_chainmask_enabled =
				cfg_get(psoc, CFG_ENABLE_COEX_ALT_CHAINMASK);
	fwol_cfg->smart_chainmask_enabled =
				cfg_get(psoc, CFG_ENABLE_SMART_CHAINMASK);
	fwol_cfg->get_rts_profile = cfg_get(psoc, CFG_ENABLE_FW_RTS_PROFILE);
	fwol_cfg->enable_fw_log_level =
				cfg_get(psoc, CFG_ENABLE_FW_DEBUG_LOG_LEVEL);
	fwol_cfg->enable_fw_log_type = cfg_get(psoc, CFG_ENABLE_FW_LOG_TYPE);
	qdf_uint8_array_parse(cfg_get(psoc, CFG_ENABLE_FW_MODULE_LOG_LEVEL),
			      fwol_cfg->enable_fw_module_log_level,
			      FW_MODULE_LOG_LEVEL_STRING_LENGTH,
			      &enable_fw_module_log_level_num);
	fwol_cfg->enable_fw_module_log_level_num =
				(uint8_t)enable_fw_module_log_level_num;
	ucfg_fwol_init_tsf_ptp_options(psoc, fwol_cfg);
	ucfg_fwol_init_sae_cfg(psoc, fwol_cfg);
	fwol_cfg->lprx_enable = cfg_get(psoc, CFG_LPRX);
	fwol_cfg->gcmp_enable = cfg_get(psoc, CFG_ENABLE_GCMP);
	fwol_cfg->enable_tx_sch_delay = cfg_get(psoc, CFG_TX_SCH_DELAY);
	fwol_cfg->enable_secondary_rate = cfg_get(psoc,
						  CFG_ENABLE_SECONDARY_RATE);
	fwol_init_adapt_dwelltime_in_cfg(psoc, &fwol_cfg->dwelltime_params);
	ucfg_fwol_fetch_ra_filter(psoc, fwol_cfg);
	ucfg_fwol_fetch_tsf_gpio_pin(psoc, fwol_cfg);
	ucfg_fwol_fetch_tsf_irq_host_gpio_pin(psoc, fwol_cfg);
	ucfg_fwol_fetch_dhcp_server_settings(psoc, fwol_cfg);

	return status;
}

QDF_STATUS fwol_cfg_on_psoc_disable(struct wlan_objmgr_psoc *psoc)
{
	/* Clear the CFG structure */
	return QDF_STATUS_SUCCESS;
}
