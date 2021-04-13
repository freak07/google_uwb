/*
 * This file is part of the UWB stack for linux.
 *
 * Copyright (c) 2020 Qorvo US, Inc.
 *
 * This software is provided under the GNU General Public License, version 2
 * (GPLv2), as well as under a Qorvo commercial license.
 *
 * You may choose to use this software under the terms of the GPLv2 License,
 * version 2 ("GPLv2"), as published by the Free Software Foundation.
 * You should have received a copy of the GPLv2 along with this program.  If
 * not, see <http://www.gnu.org/licenses/>.
 *
 * This program is distributed under the GPLv2 in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GPLv2 for more
 * details.
 *
 * If you cannot meet the requirements of the GPLv2, you may not use this
 * software for any purpose without first obtaining a commercial license from
 * Qorvo.
 * Please contact Qorvo to inquire about licensing terms.
 */
#ifndef __DW3000_CORE_H
#define __DW3000_CORE_H

#include "dw3000.h"

#define DW3000_GPIO_COUNT 9 /* GPIO0 to GPIO8 */

/* Define DW3000 PDOA modes */
#define DW3000_PDOA_M0 0x0 /* PDOA mode is off */
#define DW3000_PDOA_M1 0x1 /* PDOA mode 1 */
#define DW3000_PDOA_M2 0x2 /* PDOA mode 2 (reserved or not supported) */
#define DW3000_PDOA_M3 0x3 /* PDOA mode 3 */
#define DW3000_PDOA_CONFIG_MASK 0x3

/* Define DW3000 STS modes */
#define DW3000_STS_MODE_OFF 0x0 /* STS is off */
#define DW3000_STS_MODE_1 0x1 /* STS mode 1 */
#define DW3000_STS_MODE_2 0x2 /* STS mode 2 */
#define DW3000_STS_MODE_ND 0x3 /* STS with no data */
#define DW3000_STS_BASIC_MODES_MASK 0x3 /* STS basic modes */
#define DW3000_STS_MODE_SDC 0x8 /* Enable Super Deterministic Codes */
#define DW3000_STS_CONFIG_MASK 0xB

/* Constants for specifying TX Preamble length in symbols */
#define DW3000_PLEN_4096 0x03 /* Standard preamble length 4096 symbols */
#define DW3000_PLEN_2048 0x0A /* Non-standard preamble length 2048 symbols */
#define DW3000_PLEN_1536 0x06 /* Non-standard preamble length 1536 symbols */
#define DW3000_PLEN_1024 0x02 /* Standard preamble length 1024 symbols */
#define DW3000_PLEN_512 0x0d /* Non-standard preamble length 512 symbols */
#define DW3000_PLEN_256 0x09 /* Non-standard preamble length 256 symbols */
#define DW3000_PLEN_128 0x05 /* Non-standard preamble length 128 symbols */
#define DW3000_PLEN_72 0x07 /* Non-standard length 72 */
#define DW3000_PLEN_32 0x04 /* Non-standard length 32 */
#define DW3000_PLEN_64 0x01 /* Standard preamble length 64 symbols */

/* Constants for specifying the (Nominal) mean Pulse Repetition Frequency
   These are defined for direct write (with a shift if necessary) to CHAN_CTRL
   and TX_FCTRL regs */
#define DW3000_PRF_16M 1 /* UWB PRF 16 MHz */
#define DW3000_PRF_64M 2 /* UWB PRF 64 MHz */
#define DW3000_PRF_SCP 3 /* SCP UWB PRF ~100 MHz */

/* Constants for specifying Start of Frame Delimiter (SFD) type */
#define DW3000_SFD_TYPE_STD 0 /* Standard short IEEE802154 SFD (8 symbols) */
#define DW3000_SFD_TYPE_DW_8 1 /* Decawave-defined 8 symbols  SFD */
#define DW3000_SFD_TYPE_DW_16 2 /* Decawave-defined 16 symbols SFD */
#define DW3000_SFD_TYPE_4Z 3 /* IEEE802154z SFD (8 symbols) */

/* Constants for selecting the bit rate for data TX (and RX)
   These are defined for write (with just a shift) the TX_FCTRL register */
#define DW3000_BR_850K 0 /* UWB bit rate 850 kbits/s */
#define DW3000_BR_6M8 1 /* UWB bit rate 6.8 Mbits/s */

/* Constants for specifying Preamble Acquisition Chunk (PAC) Size in symbols */
#define DW3000_PAC8 0 /* recommended for RX of preamble length  128 and below */
#define DW3000_PAC16 1 /* recommended for RX of preamble length 256 */
#define DW3000_PAC32 2 /* recommended for RX of preamble length 512 */
#define DW3000_PAC4 3 /* recommended for RX of preamble length < 127 */

enum spi_modes {
	DW3000_SPI_RD_BIT = 0x0000U,
	DW3000_SPI_WR_BIT = 0x8000U,
	DW3000_SPI_AND_OR_8 = 0x8001U,
	DW3000_SPI_AND_OR_16 = 0x8002U,
	DW3000_SPI_AND_OR_32 = 0x8003U,
	DW3000_SPI_AND_OR_MSK = 0x0003U,
};

/* Defined constants for "mode" bitmask parameter passed into dw3000_starttx()
   function. */
#define DW3000_START_TX_IMMEDIATE 0x00 /* Send the frame immediately */
#define DW3000_START_TX_DELAYED \
	0x01 /* Send the frame at specified time (time
					must be less that half period away) */
#define DW3000_RESPONSE_EXPECTED \
	0x02 /* Will enable the receiver after TX has
					 completed */
#define DW3000_START_TX_DLY_REF \
	0x04 /* Send the frame at specified time (time
					in DREF_TIME register + any time in
					DX_TIME register) */
#define DW3000_START_TX_DLY_RS \
	0x08 /* Send the frame at specified time (time
				       in RX_TIME_0 register + any time in
				       DX_TIME register) */
#define DW3000_START_TX_DLY_TS \
	0x10 /* Send the frame at specified time (time
				       in TX_TIME_LO register + any time in
				       DX_TIME register) */
#define DW3000_START_TX_CCA \
	0x20 /* Send the frame if no preamble detected
				    within PTO time */

/* Frame filtering configuration options */
#define DW3000_FF_ENABLE_802_15_4 0x2 /* use 802.15.4 filtering rules */
#define DW3000_FF_DISABLE 0x0 /* disable FF */
#define DW3000_FF_BEACON_EN 0x001 /* beacon frames allowed */
#define DW3000_FF_DATA_EN 0x002 /* data frames allowed */
#define DW3000_FF_ACK_EN 0x004 /* ack frames allowed */
#define DW3000_FF_MAC_EN 0x008 /* mac control frames allowed */
#define DW3000_FF_RSVD_EN 0x010 /* reserved frame types allowed */
#define DW3000_FF_MULTI_EN 0x020 /* multipurpose frames allowed */
#define DW3000_FF_FRAG_EN 0x040 /* fragmented frame types allowed */
#define DW3000_FF_EXTEND_EN 0x080 /* extended frame types allowed */
#define DW3000_FF_COORD_EN \
	0x100 /* behave as coordinator (can receive frames
				    with no dest address (need PAN ID match)) */
#define DW3000_FF_IMPBRCAST_EN 0x200 /* allow MAC implicit broadcast */

/* DW3000 soft reset options */
#define DW3000_RESET_ALL 0x00
#define DW3000_RESET_CTRX 0x0f
#define DW3000_RESET_RX 0xef
#define DW3000_RESET_CLEAR 0xff

/* Fast commands */
/* Turn off TX or RX, clear any TX/RX events and put DW3000 into IDLE */
#define DW3000_CMD_TXRXOFF 0x0
/* Start TX */
#define DW3000_CMD_TX 0x1
/* Enable RX */
#define DW3000_CMD_RX 0x2
/* Start delayed TX (RMARKER will be @ time set in DX_TIME register) */
#define DW3000_CMD_DTX 0x3
/* Enable RX @ time specified in DX_TIME register */
#define DW3000_CMD_DRX 0x4
/* Start delayed TX (RMARKER will be @ time = TX_TIME + DX_TIME) */
#define DW3000_CMD_DTX_TS 0x5
/* Enable RX @ time = TX_TIME + DX_TIME */
#define DW3000_CMD_DRX_TS 0x6
/* Start delayed TX (RMARKER will be @ time = RX_TIME + DX_TIME) */
#define DW3000_CMD_DTX_RS 0x7
/* Enable RX @ time = RX_TIME + DX_TIME */
#define DW3000_CMD_DRX_RS 0x8
/* Start delayed TX (RMARKER will be @ time = DREF_TIME + DX_TIME) */
#define DW3000_CMD_DTX_REF 0x9
/* Enable RX @ time = DREF_TIME + DX_TIME */
#define DW3000_CMD_DRX_REF 0xa
/* Start delayed TX (as DTX below), enable RX when TX done */
#define DW3000_CMD_DTX_W4R 0xd
/* Start TX (as below), enable RX when TX done */
#define DW3000_CMD_TX_W4R 0xc
/* Toggle double buffer pointer */
#define DW3000_CMD_DB_TOGGLE 0x13
/* Write to the Semaphore and try to reserve access (if it hasn't already been
   reserved by the other master) */
#define DW3000_CMD_SEMA_REQ 0x14
/* Release the semaphore if it is currently reserved by this master. */
#define DW3000_CMD_SEMA_REL 0x15
/* Only SPI 2 can issue this command. Force access regardless of current
   semaphore value. */
#define DW3000_CMD_SEMA_FORCE 0x16
/* Global digital reset including of the semaphore */
#define DW3000_CMD_SEMA_RESET 0x18
/* Global digital reset without reset of the semaphore */
#define DW3000_CMD_SEMA_RESET_NO_SEM 0x19
/* Enters sleep/deep sleep according to ANA_CFG - DEEPSLEEP_EN */
#define DW3000_CMD_ENTER_SLEEP 0x1A

/* Size of RX LUT configuration tables */
#define DW3000_CONFIGMRXLUT_MAX 7
#define DW3000_DGC_CFG 0x32
#define DW3000_DGC_CFG0 0x10000240
#define DW3000_DGC_CFG1 0x1b6da489
/* DW3000 SLEEP and WAKEUP configuration parameters */
#define DW3000_PGFCAL 0x0800
#define DW3000_GOTORX 0x0200
#define DW3000_GOTOIDLE 0x0100
#define DW3000_SEL_GEAR3 0x00C0
#define DW3000_SEL_GEAR2 0x0080 /* Short gear table */
#define DW3000_SEL_GEAR1 0x0040 /* SCP */
#define DW3000_SEL_GEAR0 0x0000 /* Long gear table */
#define DW3000_ALT_GEAR 0x0020
#define DW3000_LOADLDO 0x0010
#define DW3000_LOADDGC 0x0008
#define DW3000_LOADBIAS 0x0004
#define DW3000_RUNSAR 0x0002

/* OTP addresses definitions */
#define DW3000_LDOTUNELO_ADDRESS (0x04)
#define DW3000_LDOTUNEHI_ADDRESS (0x05)
#define DW3000_PARTID_ADDRESS (0x06)
#define DW3000_LOTID_ADDRESS (0x07)
#define DW3000_VBAT_ADDRESS (0x08)
#define DW3000_VTEMP_ADDRESS (0x09)
#define DW3000_XTRIM_ADDRESS (0x1E)
#define DW3000_OTPREV_ADDRESS (0x1F)
#define DW3000_BIAS_TUNE_ADDRESS (0xA)
#define DW3000_DGC_TUNE_ADDRESS (0x20)

#define DW3000_GPIO0_FUNC_MASK 0x0000007
#define DW3000_GPIO1_FUNC_MASK 0x0000038
#define DW3000_GPIO2_FUNC_MASK 0x00001c0
#define DW3000_GPIO3_FUNC_MASK 0x0000e00
#define DW3000_GPIO4_FUNC_MASK 0x0007000
#define DW3000_GPIO5_FUNC_MASK 0x0038000
#define DW3000_GPIO6_FUNC_MASK 0x01c0000
#define DW3000_GPIO7_FUNC_MASK 0x0e00000
#define DW3000_GPIO8_FUNC_MASK 0x7000000

#define DW3000_GPIO0_DIR_OUT_MASK 0x0000001
#define DW3000_GPIO1_DIR_OUT_MASK 0x0000002
#define DW3000_GPIO2_DIR_OUT_MASK 0x0000004
#define DW3000_GPIO3_DIR_OUT_MASK 0x0000008
#define DW3000_GPIO4_DIR_OUT_MASK 0x0000010
#define DW3000_GPIO5_DIR_OUT_MASK 0x0000020
#define DW3000_GPIO6_DIR_OUT_MASK 0x0000040
#define DW3000_GPIO7_DIR_OUT_MASK 0x0000080
#define DW3000_GPIO8_DIR_OUT_MASK 0x0000100

void dw3000_init_config(struct dw3000 *dw);

int dw3000_init(struct dw3000 *dw);
void dw3000_remove(struct dw3000 *dw);

int dw3000_transfers_init(struct dw3000 *dw);
void dw3000_transfers_free(struct dw3000 *dw);

void dw3000_spitests(struct dw3000 *dw);

int dw3000_hardreset(struct dw3000 *dw);
int dw3000_softreset(struct dw3000 *dw);

int dw3000_setup_regulators(struct dw3000 *dw);
int dw3000_setup_reset_gpio(struct dw3000 *dw);
int dw3000_setup_irq(struct dw3000 *dw);

int dw3000_reg_read32(struct dw3000 *dw, u32 reg_fileid, u16 reg_offset,
		      u32 *val);
int dw3000_reg_read16(struct dw3000 *dw, u32 reg_fileid, u16 reg_offset,
		      u16 *val);
int dw3000_reg_read8(struct dw3000 *dw, u32 reg_fileid, u16 reg_offset,
		     u8 *val);
int dw3000_reg_write32(struct dw3000 *dw, u32 reg_fileid, u16 reg_offset,
		       u32 val);
int dw3000_reg_write16(struct dw3000 *dw, u32 reg_fileid, u16 reg_offset,
		       u16 val);
int dw3000_reg_write8(struct dw3000 *dw, u32 reg_fileid, u16 reg_offset,
		      u8 val);
int dw3000_reg_modify32(struct dw3000 *dw, u32 reg_fileid, u16 reg_offset,
			u32 _and, u32 _or);
int dw3000_reg_modify16(struct dw3000 *dw, u32 reg_fileid, u16 reg_offset,
			u16 _and, u16 _or);
int dw3000_reg_modify8(struct dw3000 *dw, u32 reg_fileid, u16 reg_offset,
		       u8 _and, u8 _or);

int dw3000_write_fastcmd(struct dw3000 *dw, u32 cmd);

int dw3000_xfer(struct dw3000 *dw, u32 reg_fileid, u16 reg_offset, u16 length,
		void *buffer, enum spi_modes mode);
#define dw3000_reg_or8(dw, addr, offset, or_val) \
	dw3000_reg_modify8(dw, addr, offset, -1, or_val)
#define dw3000_reg_and8(dw, addr, offset, and_val) \
	dw3000_reg_modify8(dw, addr, offset, and_val, 0)

#define dw3000_reg_or16(dw, addr, offset, or_val) \
	dw3000_reg_modify16(dw, addr, offset, -1, or_val)
#define dw3000_reg_and16(dw, addr, offset, and_val) \
	dw3000_reg_modify16(dw, addr, offset, and_val, 0)

#define dw3000_reg_or32(dw, addr, offset, or_val) \
	dw3000_reg_modify32(dw, addr, offset, -1, or_val)
#define dw3000_reg_and32(dw, addr, offset, and_val) \
	dw3000_reg_modify32(dw, addr, offset, and_val, 0)

int dw3000_enable(struct dw3000 *dw);
int dw3000_disable(struct dw3000 *dw);

int dw3000_configure_chan(struct dw3000 *dw);

int dw3000_seteui64(struct dw3000 *dw, __le64 val);
int dw3000_setpanid(struct dw3000 *dw, __le16 val);
int dw3000_setshortaddr(struct dw3000 *dw, __le16 val);
int dw3000_setpancoord(struct dw3000 *dw, bool active);
int dw3000_setpdoa(struct dw3000 *dw, u8 mode);
int dw3000_setsts(struct dw3000 *dw, u8 mode, enum dw3000_sts_lengths len);
int dw3000_setpromiscuous(struct dw3000 *dw, bool on);

int dw3000_clear_sys_status(struct dw3000 *dw, u32 clear_bits);
int dw3000_clear_dss_status(struct dw3000 *dw, u8 clear_bits);
int dw3000_clear_spi_collision_status(struct dw3000 *dw, u8 clear_bits);
int dw3000_read_rx_timestamp(struct dw3000 *dw, u64 *rx_ts);
int dw3000_read_rdb_status(struct dw3000 *dw, u8 *status);
int dw3000_read_sys_status(struct dw3000 *dw, u32 *status);
int dw3000_read_sys_time(struct dw3000 *dw, u32 *sys_time);

int dw3000_poweron(struct dw3000 *dw);
int dw3000_poweroff(struct dw3000 *dw);

int dw3000_rx_enable(struct dw3000 *dw, bool rx_delayed, u32 date_dtu,
		     u32 timeout_pac);
int dw3000_rx_disable(struct dw3000 *dw);
int dw3000_rx_stats_enable(struct dw3000 *dw, bool on);
void dw3000_rx_stats_clear(struct dw3000 *dw);

int dw3000_enable_autoack(struct dw3000 *dw, bool force);
int dw3000_disable_autoack(struct dw3000 *dw, bool force);

int dw3000_tx_frame(struct dw3000 *dw, struct sk_buff *skb, bool tx_delayed,
		    u32 tx_date_dtu, int rx_delay_dly, u32 rx_timeout_pac);
int dw3000_tx_setcwtone(struct dw3000 *dw, bool on);

int dw3000_config_antenna_gpios(struct dw3000 *dw);
int dw3000_set_tx_antenna(struct dw3000 *dw, int antidx);
int dw3000_set_rx_antennas(struct dw3000 *dw, int antpairidx);

s16 dw3000_readpdoa(struct dw3000 *dw);

int dw3000_set_gpio_mode(struct dw3000 *dw, u32 mask, u32 mode);
int dw3000_set_gpio_dir(struct dw3000 *dw, u16 mask, u16 dir);
int dw3000_set_gpio_out(struct dw3000 *dw, u16 reset, u16 set);

int dw3000_otp_read32(struct dw3000 *dw, u16 addr, u32 *val);
int dw3000_otp_write32(struct dw3000 *dw, u16 addr, u32 data);

void dw3000_sysfs_init(struct dw3000 *dw);
void dw3000_sysfs_remove(struct dw3000 *dw);

void dw3000_isr(struct dw3000 *dw);

/* Preamble length related information. */
struct dw3000_plen_info {
	/* Preamble length in symbols. */
	int symb;
	/* PAC size in symbols. */
	int pac_symb;
	/* Register value for this preamble length. */
	uint8_t dw_reg;
	/* Register value for PAC size. */
	uint8_t dw_pac_reg;
};
extern const struct dw3000_plen_info _plen_info[];

/* Bitrate related information. */
struct dw3000_bitrate_info {
	/* Standard and Decawave non standard SFD length in symbols. */
	int sfd_symb[2];
	/* Chips per symbol for PHR. */
	int phr_chip_per_symb;
	/* Chips per symbol for data part. */
	int data_chip_per_symb;
};
extern const struct dw3000_bitrate_info _bitrate_info[];

/* PRF related information. */
struct dw3000_prf_info {
	/* Number of chips per symbol. */
	int chip_per_symb;
};
extern const struct dw3000_prf_info _prf_info[];

static inline int dw3000_compute_shr_dtu(struct dw3000 *dw)
{
	const struct dw3000_plen_info *plen_info =
		&_plen_info[dw->config.txPreambLength - 1];
	const int chip_per_symb =
		_prf_info[dw->config.txCode >= 9 ? DW3000_PRF_64M :
						   DW3000_PRF_16M]
			.chip_per_symb;
	const struct dw3000_bitrate_info *bitrate_info =
		&_bitrate_info[dw->config.dataRate];
	const int shr_symb =
		plen_info->symb +
		bitrate_info
			->sfd_symb[dw->config.sfdType ?
					   1 :
					   0]; /* TODO: support type 2 & 3 ? */
	return shr_symb * chip_per_symb / DW3000_CHIP_PER_DTU;
}

static inline int dw3000_compute_symbol_dtu(struct dw3000 *dw)
{
	const int chip_per_symb =
		_prf_info[dw->config.txCode >= 9 ? DW3000_PRF_64M :
						   DW3000_PRF_16M]
			.chip_per_symb;
	return chip_per_symb / DW3000_CHIP_PER_DTU;
}

static inline int dw3000_compute_chips_per_pac(struct dw3000 *dw)
{
	const int pac_symb = _plen_info[dw->config.txPreambLength - 1].pac_symb;
	const int chip_per_symb =
		_prf_info[dw->config.txCode >= 9 ? DW3000_PRF_64M :
						   DW3000_PRF_16M]
			.chip_per_symb;
	return chip_per_symb * pac_symb;
}

static inline int dw3000_compute_pre_timeout_pac(struct dw3000 *dw)
{
	/* Must be called AFTER dw->chips_per_pac initialisation */
	const int symb = _plen_info[dw->config.txPreambLength - 1].symb;
	const int pac_symb = _plen_info[dw->config.txPreambLength - 1].pac_symb;

	return (DW3000_RX_ENABLE_STARTUP_DLY * DW3000_CHIP_PER_DLY +
		dw->chips_per_pac - 1) /
		       dw->chips_per_pac +
	       symb / pac_symb + 2;
}

static inline int dw3000_payload_duration_dtu(struct dw3000 *dw,
					      int payload_bytes)
{
	const struct dw3000_prf_info *prf_info =
		&_prf_info[dw->config.txCode >= 9 ? DW3000_PRF_64M :
						    DW3000_PRF_16M];
	const struct dw3000_bitrate_info *bitrate_info =
		&_bitrate_info[dw->config.dataRate];
	/* STS part */
	const int sts_symb = dw->config.stsMode == DW3000_STS_MODE_OFF ?
				     0 :
				     8 << dw->config.stsLength;
	const int sts_chips = sts_symb * prf_info->chip_per_symb;
	/* PHR part. */
	static const int phr_tail_bits = 19 + 2;
	const int phr_chips = phr_tail_bits /* 1 bit/symbol */
			      * bitrate_info->phr_chip_per_symb;
	/* Data part, 48 Reed-Solomon bits per 330 bits. */
	const int data_bits = payload_bytes * 8;
	const int data_rs_bits = data_bits + (data_bits + 329) / 330 * 48;
	const int data_chips = data_rs_bits /* 1 bit/symbol */
			       * bitrate_info->data_chip_per_symb;
	/* Done, convert to dtu. */
	return (sts_chips + phr_chips + data_chips) / DW3000_CHIP_PER_DTU;
}

static inline void dw3000_update_timings(struct dw3000 *dw)
{
	struct mcps802154_llhw *llhw = dw->llhw;
	/* Update configuration dependent timings */
	llhw->shr_dtu = dw3000_compute_shr_dtu(dw);
	llhw->symbol_dtu = dw3000_compute_symbol_dtu(dw);
	/* The CCA detection time shall be equivalent to 40 data symbol periods,
	   Tdsym, for a nominal 850 kb/s, or equivalently, at least 8 (multiplexed)
	   preamble symbols should be captured in the CCA detection time. */
	llhw->cca_dtu = 8 * llhw->symbol_dtu;
	dw->chips_per_pac = dw3000_compute_chips_per_pac(dw);
	dw->pre_timeout_pac = dw3000_compute_pre_timeout_pac(dw);
}

#endif /* __DW3000_CORE_H */
