/*
 * Copyright (c) 2012-2019 The Linux Foundation. All rights reserved.
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
 * DOC: This file contains centralized definitions of converged configuration.
 */

#ifndef __CFG_MLME_GENERIC_H
#define __CFG_MLME_GENERIC_H

#ifdef WLAN_FEATURE_11W
#define CFG_PMF_SA_QUERY_MAX_RETRIES_TYPE	CFG_INI_UINT
#define CFG_PMF_SA_QUERY_RETRY_INTERVAL_TYPE	CFG_INI_UINT
#else
#define CFG_PMF_SA_QUERY_MAX_RETRIES_TYPE	CFG_UINT
#define CFG_PMF_SA_QUERY_RETRY_INTERVAL_TYPE	CFG_UINT
#endif /*WLAN_FEATURE_11W*/

/*
 * pmfSaQueryMaxRetries - Control PMF SA query retries for SAP
 * @Min: 0
 * @Max: 20
 * @Default: 5
 *
 * This ini to set the number of PMF SA query retries for SAP
 *
 * Related: None.
 *
 * Supported Feature: PMF(11W)
 *
 */
#define CFG_PMF_SA_QUERY_MAX_RETRIES CFG_PMF_SA_QUERY_MAX_RETRIES_TYPE( \
		"pmfSaQueryMaxRetries", \
		0, \
		20, \
		5, \
		CFG_VALUE_OR_DEFAULT, \
		"PMF SA query retries for SAP")
/*
 * pmfSaQueryRetryInterval - Control PMF SA query retry interval
 * for SAP in ms
 * @Min: 10
 * @Max: 2000
 * @Default: 200
 *
 * This ini to set the PMF SA query retry interval for SAP in ms
 *
 * Related: None.
 *
 * Supported Feature: PMF(11W)
 *
 */
#define CFG_PMF_SA_QUERY_RETRY_INTERVAL CFG_PMF_SA_QUERY_RETRY_INTERVAL_TYPE( \
		"pmfSaQueryRetryInterval", \
		10, \
		2000, \
		200, \
		CFG_VALUE_OR_DEFAULT, \
		"PMF SA query retry interval for SAP")

/*
 * <ini>
 * enable_rtt_mac_randomization - Enable/Disable rtt mac randomization
 * @Min: 0
 * @Max: 1
 * @Default: 0
 *
 * Usage: External
 *
 * </ini>
 */
#define CFG_ENABLE_RTT_MAC_RANDOMIZATION CFG_INI_BOOL( \
	"enable_rtt_mac_randomization", \
	0, \
	"Enable RTT MAC randomization")

#define CFG_RTT3_ENABLE CFG_BOOL( \
		"rtt3_enabled", \
		1, \
		"RTT3 enable/disable info")

/*
 * <ini>
 * g11hSupportEnabled - Enable 11h support
 * @Min: 0
 * @Max: 1
 * @Default: 1
 *
 * This ini is used to set 11h support flag
 *
 * Related: None
 *
 * Supported Feature: STA
 *
 * Usage: Internal/External
 *
 * </ini>
 */
#define CFG_11H_SUPPORT_ENABLED CFG_INI_BOOL( \
		"g11hSupportEnabled", \
		1, \
		"11h Enable Flag")

/*
 * <ini>
 * g11dSupportEnabled - Enable 11d support
 * @Min: 0
 * @Max: 1
 * @Default: 1
 *
 * This ini is used to set 11d support flag
 *
 * Related: None
 *
 * Supported Feature: STA
 *
 * Usage: Internal/External
 *
 * </ini>
 */
#define CFG_11D_SUPPORT_ENABLED CFG_INI_BOOL( \
		"g11dSupportEnabled", \
		1, \
		"11d Enable Flag")

/*
 * <ini>
 * BandCapability - Preferred band (0: Both,  1: 2.4G only,  2: 5G only)
 * @Min: 0
 * @Max: 2
 * @Default: 0
 *
 * This ini is used to set default band capability
 * (0: Both, 1: 2.4G only, 2: 5G only)
 *
 * Related: None
 *
 * Supported Feature: STA
 *
 * Usage: Internal/External
 *
 * </ini>
 */
#define CFG_BAND_CAPABILITY CFG_INI_UINT( \
	"BandCapability", \
	0, \
	2, \
	0, \
	CFG_VALUE_OR_DEFAULT, \
	"Band Capability")

/*
 * <ini>
 * gPreventLinkDown - Enable to prevent bus link from going down
 * @Min: 0
 * @Max: 1
 * @Default: 0
 *
 * Enable to prevent bus link from going down. Useful for platforms that do not
 * (yet) support link down suspend cases.
 *
 * Related: N/A
 *
 * Supported Feature: Suspend/Resume
 *
 * Usage: Internal
 *
 * </ini>
 */
#if defined(QCA_WIFI_NAPIER_EMULATION) || defined(QCA_WIFI_QCA6290)
#define CFG_PREVENT_LINK_DOWN CFG_INI_BOOL( \
	"gPreventLinkDown", \
	1, \
	"Prevent Bus Link Down")
#else
#define CFG_PREVENT_LINK_DOWN CFG_INI_BOOL( \
	"gPreventLinkDown", \
	0, \
	"Prevent Bus Link Down")
#endif /* QCA_WIFI_NAPIER_EMULATION */

/*
 * <ini>
 * gSelect5GHzMargin - Sets RSSI preference for 5GHz over 2.4GHz AP.
 * @Min: 0
 * @Max: 60
 * @Default: 0
 *
 * Prefer connecting to 5G AP even if its RSSI is lower by gSelect5GHzMargin
 * dBm than 2.4G AP. This feature requires the dependent cfg.ini
 * "gRoamPrefer5GHz" set to 1
 *
 * Related: gRoamPrefer5GHz
 *
 * Supported Feature: Roaming
 *
 * Usage: External
 *
 * </ini>
 */
#define CFG_SELECT_5GHZ_MARGIN CFG_INI_UINT( \
	"gSelect5GHzMargin", \
	0, \
	60, \
	0, \
	CFG_VALUE_OR_DEFAULT, \
	"Select 5Ghz Margin")

/*
 * <ini>
 * gEnableMemDeepSleep - Sets Memory Deep Sleep on/off.
 * @Min: 0
 * @Max: 1
 * @Default: 1
 *
 * This option enables/disables memory deep sleep.
 * Related: None
 *
 * Supported Feature: General
 *
 * Usage: External
 *
 * </ini>
 */
#define CFG_ENABLE_MEM_DEEP_SLEEP CFG_INI_BOOL( \
	"gEnableMemDeepSleep", \
	1, \
	"Enable Memory Deep Sleep")

/*
 * <ini>
 *
 * gEnableCckTxFirOverride - Enable/disable CCK TxFIR Override
 * @Min: 0 (disabled)
 * @Max: 1 (enabled)
 * @Default: 0 (disabled)
 *
 * When operating in an 802.11b mode, this configuration item forces a 2x2 radio
 * configuration into 1x for Tx and 2x for Rx (ie 1x2) for regulatory compliance
 * reasons.
 *
 * Related: enable2x2
 *
 * Supported Feature: 802.11b, 2x2
 *
 * Usage: Internal/External
 *
 * </ini>
 */
#define CFG_ENABLE_CCK_TX_FIR_OVERRIDE CFG_INI_BOOL( \
	"gEnableCckTxFirOverride", \
	0, \
	"Enable CCK TX FIR Override")

/*
 * <ini>
 *
 * gEnableForceTargetAssert - Enable/disable SSR
 * @Min: 0 (disabled)
 * @Max: 1 (enabled)
 * @Default: 0 (disabled)
 *
 * This INI item is used to control subsystem restart(SSR) test framework
 * Set it's value to 1 to enable APPS trigerred SSR testing
 *
 * Related: None
 *
 * Supported Feature: General
 *
 * Usage: Internal/External
 *
 * </ini>
 */
#define CFG_ENABLE_CRASH_INJECT CFG_INI_BOOL( \
	"gEnableForceTargetAssert", \
	0, \
	"Enable Crash Inject")

/*
 * <ini>
 *
 * gEnableLpassSupport - Enable/disable LPASS Support
 * @Min: 0 (disabled)
 * @Max: 1 (enabled)
 * @Default: 0 (disabled)
 *
 * Related: None
 *
 * Supported Feature: General
 *
 * Usage: Internal/External
 *
 * </ini>
 */
#ifdef WLAN_FEATURE_LPSS
#define CFG_ENABLE_LPASS_SUPPORT CFG_INI_BOOL( \
	"gEnableLpassSupport", \
	0, \
	"Enable LPASS Support")
#else
#define CFG_ENABLE_LPASS_SUPPORT CFG_BOOL( \
	"gEnableLpassSupport", \
	0, \
	"Enable LPASS Support")
#endif

/*
 * <ini>
 *
 * gEnableSelfRecovery - Enable/disable Self Recovery
 * @Min: 0 (disabled)
 * @Max: 1 (enabled)
 * @Default: 0 (disabled)
 *
 * Related: None
 *
 * Supported Feature: General
 *
 * Usage: Internal/External
 *
 * </ini>
 */
#define CFG_ENABLE_SELF_RECOVERY CFG_INI_BOOL( \
	"gEnableSelfRecovery", \
	0, \
	"Enable Self Recovery")

/*
 * <ini>
 *
 * gSapDot11mc - Enable/disable SAP 802.11mc support
 * @Min: 0 (disabled)
 * @Max: 1 (enabled)
 * @Default: 0 (disabled)
 *
 * Related: None
 *
 * Supported Feature: General
 *
 * Usage: Internal/External
 *
 * </ini>
 */
#define CFG_SAP_DOT11MC CFG_INI_BOOL( \
	"gSapDot11mc", \
	0, \
	"SAP 802.11mc support")

/*
 * <ini>
 *
 * gEnableFatalEvent - Enable/Disable BUG report in case of fatal event
 * @Min: 0 (disabled)
 * @Max: 1 (enabled)
 * @Default: 1 (enabled)
 *
 * Related: None
 *
 * Supported Feature: General
 *
 * Usage: Internal/External
 *
 * </ini>
 */
#define CFG_ENABLE_FATAL_EVENT_TRIGGER CFG_INI_BOOL( \
	"gEnableFatalEvent", \
	1, \
	"Enable Fatal Event Trigger")

/*
 * <ini>
 * gSub20ChannelWidth - Control sub 20 channel width (5/10 Mhz)
 * @Min: 0
 * @Max: 2
 * @Default: 0
 *
 * This ini is used to set the sub 20 channel width.
 * gSub20ChannelWidth=0: indicates do not use Sub 20 MHz bandwidth
 * gSub20ChannelWidth=1: Bring up SAP/STA in 5 MHz bandwidth
 * gSub20ChannelWidth=2: Bring up SAP/STA in 10 MHz bandwidth
 *
 * Related: None
 *
 * Supported Feature: 5/10 Mhz channel width support
 *
 * Usage: Internal/External
 *
 * </ini>
 */
#define CFG_SUB_20_CHANNEL_WIDTH CFG_INI_UINT( \
	"gSub20ChannelWidth", \
	0, \
	2, \
	0, \
	CFG_VALUE_OR_DEFAULT, \
	"Sub 20 Channel Width")

/*
 * <ini>
 * goptimize_chan_avoid_event - Optimize channel avoidance indication
 *				coming from firmware
 * @Min: 0
 * @Max: 1
 * @Default: 0
 *
 * Related: None
 *
 * Supported Feature: General
 *
 * Usage: Internal/External
 *
 * </ini>
 */
#define CFG_OPTIMIZE_CA_EVENT CFG_INI_BOOL( \
	"goptimize_chan_avoid_event", \
	0, \
	"Optimize FW CA Event")

/*
 * <ini>
 * fw_timeout_crash - Enable/Disable BUG ON
 * @Min: 0
 * @Max: 1
 * @Default: 1
 *
 * This ini is used to Trigger host crash when firmware fails to send the
 * response to host
 * fw_timeout_crash = 0 Disabled
 * fw_timeout_crash = 1 Trigger host crash
 *
 * Related: None
 *
 * Supported Feature: SSR
 *
 * Usage: Internal/External
 *
 * </ini>
 */
#define CFG_CRASH_FW_TIMEOUT CFG_INI_BOOL( \
	"fw_timeout_crash", \
	1, \
	"Enable FW Timeout Crash")

/*
 * <ini>
 * gDroppedPktDisconnectTh - Sets dropped packet threshold in firmware
 * @Min: 0
 * @Max: 65535
 * @Default: 512
 *
 * This INI is the packet drop threshold will trigger disconnect from remote
 * peer.
 *
 * Related: None
 *
 * Supported Feature: connection
 *
 * Usage: External
 *
 * </ini>
 */
#define CFG_DROPPED_PKT_DISCONNECT_THRESHOLD CFG_INI_UINT( \
	"gDroppedPktDisconnectTh", \
	0, \
	65535, \
	512, \
	CFG_VALUE_OR_DEFAULT, \
	"Dropped Pkt Disconnect threshold")

/*
 * <ini>
 * gItoRepeatCount - sets ito repeated count
 * @Min: 0
 * @Max: 5
 * @Default: 0
 *
 * This ini sets the ito count in FW
 *
 * Usage: External
 *
 * </ini>
 */
#define CFG_ITO_REPEAT_COUNT CFG_INI_UINT( \
	"gItoRepeatCount", \
	0, \
	5, \
	0, \
	CFG_VALUE_OR_DEFAULT, \
	"ITO Repeat Count")

/*
 * <ini>
 * gEnableDeauthToDisassocMap - Enables deauth to disassoc map
 * @Min: 0
 * @Max: 1
 * @Default: 0
 *
 * This ini is used to set default  disassoc map
 *
 * Related: None
 *
 * Supported Feature: STA
 *
 * Usage: External
 *
 * </ini>
 */
#define CFG_ENABLE_DEAUTH_TO_DISASSOC_MAP CFG_INI_BOOL( \
		"gEnableDeauthToDisassocMap", \
		0, \
		"Enables deauth to disassoc map")

/*
 * <ini>
 * gEnableDebugLog - Enable/Disable the Connection related logs
 * @Min: 0
 * @Max: 0xFF
 * @Default: 0x0F
 *
 * This ini is used to enable/disable the connection related logs
 * 0x1 - Enable mgmt pkt logs (excpet probe req/rsp, beacons).
 * 0x2 - Enable EAPOL pkt logs.
 * 0x4 - Enable DHCP pkt logs.
 * 0x8 - Enable mgmt action frames logs.
 * 0x0 - Disable all the above connection related logs.
 * The default value of 0x0F will enable all the above logs
 *
 * Related: None
 *
 * Supported Feature: STA
 *
 * Usage: Internal/External
 *
 * </ini>
 */
#define CFG_ENABLE_DEBUG_PACKET_LOG CFG_INI_UINT( \
				"gEnableDebugLog", \
				0, 0xFF, 0x0F, \
				CFG_VALUE_OR_DEFAULT, \
				"Enable debug log")

/*
 * <ini>
 * enable_beacon_reception_stats - Enable disable beacon reception stats
 * @Min: 0
 * @Max: 1
 * @Default: 0
 *
 * This ini is used to enable/disable the beacon reception stats collected per
 * vdev and then sent to the driver to be displayed in sysfs
 *
 * Related: None
 *
 * Supported Feature: Stats
 *
 * Usage: External
 *
 * </ini>
 */
 #define CFG_ENABLE_BEACON_RECEPTION_STATS CFG_INI_BOOL( \
			"enable_beacon_reception_stats", \
			0, \
			"Enable disable beacon reception stats")

/*
 * <ini>
 * gRemoveTimeStampSyncCmd - Enable/Disable to remove time stamp sync cmd
 * @Min: 0
 * @Max: 1
 * @Default: 1
 *
 * This ini is used to enable/disable the removal of time stamp sync cmd
 *
 * Usage: External
 *
 * </ini>
 */
#define CFG_REMOVE_TIME_STAMP_SYNC_CMD CFG_INI_BOOL( \
	"gRemoveTimeStampSyncCmd", \
	1, \
	"Enable to remove time stamp sync cmd")

/*
 * <ini>
 * gEnableChangeChannelBandWidth  Enable/Disable change
 * channel&bandwidth in the mission mode
 * @Min: 0
 * @Max: 1
 * @Default: 0
 *
 * 0  not allow change channel&bandwidth by setMonChan
 * 1  allow change channel&bandwidth by setMonChan
 *
 * Related: None
 *
 * Supported Feature: STA
 *
 * Usage: External
 *
 * </ini>
 */
#ifdef FEATURE_MONITOR_MODE_SUPPORT
#define CFG_CHANGE_CHANNEL_BANDWIDTH_DEFAULT true
#else
#define CFG_CHANGE_CHANNEL_BANDWIDTH_DEFAULT false
#endif

#define CFG_CHANGE_CHANNEL_BANDWIDTH CFG_INI_BOOL( \
		"gEnableChangeChannelBandWidth", \
		CFG_CHANGE_CHANNEL_BANDWIDTH_DEFAULT, \
		"enable change channel bw")

#define CFG_GENERIC_ALL \
	CFG(CFG_ENABLE_DEBUG_PACKET_LOG) \
	CFG(CFG_PMF_SA_QUERY_MAX_RETRIES) \
	CFG(CFG_PMF_SA_QUERY_RETRY_INTERVAL) \
	CFG(CFG_ENABLE_RTT_MAC_RANDOMIZATION) \
	CFG(CFG_RTT3_ENABLE) \
	CFG(CFG_11H_SUPPORT_ENABLED) \
	CFG(CFG_11D_SUPPORT_ENABLED) \
	CFG(CFG_BAND_CAPABILITY) \
	CFG(CFG_PREVENT_LINK_DOWN) \
	CFG(CFG_SELECT_5GHZ_MARGIN) \
	CFG(CFG_ENABLE_MEM_DEEP_SLEEP) \
	CFG(CFG_ENABLE_CCK_TX_FIR_OVERRIDE) \
	CFG(CFG_ENABLE_CRASH_INJECT) \
	CFG(CFG_ENABLE_LPASS_SUPPORT) \
	CFG(CFG_ENABLE_SELF_RECOVERY) \
	CFG(CFG_ENABLE_DEAUTH_TO_DISASSOC_MAP) \
	CFG(CFG_SAP_DOT11MC) \
	CFG(CFG_ENABLE_FATAL_EVENT_TRIGGER) \
	CFG(CFG_SUB_20_CHANNEL_WIDTH) \
	CFG(CFG_OPTIMIZE_CA_EVENT) \
	CFG(CFG_CRASH_FW_TIMEOUT) \
	CFG(CFG_DROPPED_PKT_DISCONNECT_THRESHOLD) \
	CFG(CFG_ITO_REPEAT_COUNT) \
	CFG(CFG_ENABLE_BEACON_RECEPTION_STATS) \
	CFG(CFG_REMOVE_TIME_STAMP_SYNC_CMD) \
	CFG(CFG_CHANGE_CHANNEL_BANDWIDTH)

#endif /* __CFG_MLME_GENERIC_H */
