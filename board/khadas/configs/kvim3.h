/* SPDX-License-Identifier: (GPL-2.0+ OR MIT) */
/*
 * board/khadas/configs/kvim3.h
 *
 * Copyright (C) 2023 Khadas Technology Co.,Ltd. All rights reserved.
 *
 */

#ifndef __KVIM3_H__
#define __KVIM3_H__

#include <asm/arch/cpu.h>

#define CONFIG_SYS_GENERIC_BOARD  1
#ifndef CONFIG_AML_MESON
#warning "include warning"
#endif

/*
 * platform power init config
 */
#define CONFIG_PLATFORM_POWER_INIT
#define CONFIG_VCCK_INIT_VOLTAGE	800		// VCCK power up voltage
#define CONFIG_VDDEE_INIT_VOLTAGE	880		// VDDEE power up voltage
#define CONFIG_VDDEE_SLEEP_VOLTAGE	770		// VDDEE suspend voltage

/* Khadas commands */
#define CONFIG_KHADAS_KBI 1
#define CONFIG_KHADAS_CFGLOAD 1
#define CONFIG_KHADAS_SCRIPT 1

#define CONFIG_TCA6408 1
#define CONFIG_POWER_FUSB302 1

/* configs for CEC */
#ifndef CONFIG_CEC_OSD_NAME
#undef CONFIG_CEC_OSD_NAME
#define CONFIG_CEC_OSD_NAME		"KVIM3"
#endif
#define CONFIG_CEC_WAKEUP
/*if use bt-wakeup,open it*/
#define CONFIG_BT_WAKEUP
/* SMP Definitions */
#define CPU_RELEASE_ADDR		secondary_boot_func

/* config saradc*/
#define CONFIG_CMD_SARADC 1
#define CONFIG_SARADC_CH  2

/* Bootloader Control Block function
 * That is used for recovery and the bootloader to talk to each other
 */
#define CONFIG_BOOTLOADER_CONTROL_BLOCK

#define CONFIG_CMD_BOOTCTOL_AVB
#define CONFIG_AML_FACTORY_PROVISION 1

/* Serial config */
#define CONFIG_CONS_INDEX 2
#define CONFIG_BAUDRATE  115200
#define CONFIG_AML_MESON_SERIAL   1
#define CONFIG_SERIAL_MULTI		1

/*Enable ir remote wake up for bl30*/
#define CONFIG_IR_REMOTE_POWER_UP_KEY_VAL1 0xeb14ff00 //khadas ir --- power
#define CONFIG_IR_REMOTE_POWER_UP_KEY_VAL2 0XBB44FB04 //amlogic tv ir --- ch+
#define CONFIG_IR_REMOTE_POWER_UP_KEY_VAL3 0xF20DFE01 //amlogic tv ir --- ch-
#define CONFIG_IR_REMOTE_POWER_UP_KEY_VAL4 0XBA45BD02 //amlogic small ir--- power
#define CONFIG_IR_REMOTE_POWER_UP_KEY_VAL5 0xe51afb04
#define CONFIG_IR_REMOTE_POWER_UP_KEY_VAL6 0xFFFFFFFF
#define CONFIG_IR_REMOTE_POWER_UP_KEY_VAL7 0xFFFFFFFF
#define CONFIG_IR_REMOTE_POWER_UP_KEY_VAL8 0xFFFFFFFF
#define CONFIG_IR_REMOTE_POWER_UP_KEY_VAL9 0xFFFFFFFF

/*config the default parameters for adc power key*/
#define CONFIG_ADC_POWER_KEY_CHAN   2  /*channel range: 0-7*/
#define CONFIG_ADC_POWER_KEY_VAL	0  /*sample value range: 0-1023*/

#ifdef DTB_BIND_KERNEL    //load dtb from kernel, such as boot partition
#define CONFIG_DTB_LOAD  "imgread dtb ${boot_part} ${dtb_mem_addr}"
#else
#define CONFIG_DTB_LOAD  "store dtb read $dtb_mem_addr || " \
                         "if test ${boot_source} = emmc; then "\
                             "echo Load dtb/${fdtfile} from eMMC (1:1) ...;" \
                             "load mmc 1:1 ${dtb_mem_addr} dtb/${fdtfile};" \
                         "else if test ${boot_source} = sd; then "\
                             "echo Load dtb/${fdtfile} from SD (0:1) ...;" \
                             "load mmc 0:1 ${dtb_mem_addr} dtb/${fdtfile};" \
                         "fi;fi;"
#endif

/* args/envs */
#define CONFIG_SYS_MAXARGS  64

#define CONFIG_SYS_ARCH_TIMER  1

//Boot commands
#define CONFIG_CMD_BOOTI  1
#define CONFIG_CMD_BOOTD  1
#define CONFIG_CMD_BOOTM  1

#define CONFIG_SUPPORT_RAW_INITRD  1
#define CONFIG_MISC_INIT_R  1

#define CONFIG_CMD_USB  1
#define CONFIG_CMD_MMC  1
#define CONFIG_CMD_DHCP 1
#define CONFIG_CMD_PXE  1
#define CONFIG_MENU	 1
#define CONFIG_DOS_PARTITION 1
#define CONFIG_ISO_PARTITION 1
#define CONFIG_AML_PARTITION 1
#define CONFIG_EFI_PARTITION 1
#define CONFIG_PTBL_MBR	(1)

#define CONFIG_CMD_NET 1
#define CONFIG_CMD_TFTPBOOT 1
#define CONFIG_NET_TFTP_VARS 1
#define CONFIG_CMD_FAT 1
#define CONFIG_HAVE_BLOCK_DEVICE 1

#ifdef CONFIG_CMD_USB
#define BOOT_TARGET_DEVICES_USB(func) func(USB, usb, 0)
#else
#define BOOT_TARGET_DEVICES_USB(func)
#endif

#ifndef BOOT_TARGET_DEVICES
#define BOOT_TARGET_DEVICES(func) \
	BOOT_TARGET_DEVICES_USB(func) \
	func(MMC, mmc, 0) \
	func(MMC, mmc, 1) \
	func(PXE, pxe, na) \
	func(DHCP, dhcp, na)
#endif

#include <config_distro_bootcmd.h>

#ifndef CONFIG_BOOTCOMMAND
#define CONFIG_BOOTCOMMAND "run bootcmd"
#endif

/*smc*/
#define CONFIG_ARM_SMCCC       1

#define CONFIG_EXTRA_ENV_SETTINGS \
		"firstboot=1\0"\
		"upgrade_step=0\0"\
		"loadaddr=0x00020000\0"\
		"dv_fw_addr=0xa00000\0"\
		"panel_type=mipi_0\0" \
		"fdt_addr_r=0x20000000\0"\
		"fdtoverlay_addr_r=0x00a00000\0"\
		"fdtaddr=0x020000000\0"\
		"kernel_addr_r=0x01080000\0"\
		"scriptaddr=0x00010000\0" \
		"pxefile_addr_r=0x00010000\0"\
		"ramdisk_addr_r=0x10000000\0"\
		"kernel_comp_addr_r=0x1080000\0"\
		"kernel_comp_size=0x2000000\0"\
		"pxeuuid=00000000-0000-0000-0000-000000000000\0"\
		"bootfile=\0"\
		"fdtfile=amlogic/kvim3.dtb\0" \
		"silent=1\0"\
		"lcd_ctrl=0x00000000\0" \
		"outputmode=1080p60hz\0" \
		"vout_init=enable\0" \
		"hdmimode=1080p60hz\0" \
		"colorattribute=444,8bit\0"\
		"cvbsmode=576cvbs\0" \
		"display_width=1920\0" \
		"display_height=1080\0" \
		"display_bpp=24\0" \
		"display_color_index=24\0" \
		"display_layer=osd0\0" \
		"display_color_fg=0xffff\0" \
		"display_color_bg=0\0" \
		"dtb_mem_addr=0x1000000\0" \
		"fb_addr=0x3d800000\0" \
		"fb_width=1920\0" \
		"fb_height=1080\0" \
		"frac_rate_policy=1\0" \
		"hdr_policy=0\0" \
		"hdmi_read_edid=1\0" \
		"hdmichecksum=0x00000000\0" \
		"dolby_status=0\0" \
		"dolby_vision_on=0\0" \
		"dv_fw_dir_odm_ext=/odm_ext/firmware/dovi_fw.bin\0" \
		"dv_fw_dir_vendor=/vendor/firmware/dovi_fw.bin\0" \
		"dv_fw_dir=/reserved/firmware/dovi_fw.bin\0" \
		"usb_burning=update 1000\0" \
		"otg_device=1\0"\
		"fdt_high=0x20000000\0"\
		"try_auto_burn=update 700 750;\0"\
		"sdcburncfg=aml_sdc_burn.ini\0"\
		"sdc_burning=sdc_burn ${sdcburncfg}\0"\
		"wipe_data=successful\0"\
		"wipe_cache=successful\0"\
		"EnableSelinux=enforcing\0" \
		"recovery_part=recovery\0"\
		"recovery_offset=0\0"\
		"cvbs_drv=0\0"\
		"lock=10101000\0"\
		"osd_reverse=0\0"\
		"video_reverse=0\0"\
		"active_slot=normal\0"\
		"boot_part=boot\0"\
		"boot_flag=0\0"\
		"Irq_check_en=0\0"\
		"reboot_mode_android=""normal""\0"\
		"tftp_kernel_path=boot/Image \0" \
		"tftp_dtb_path=boot/dtb/ \0" \
		"tftp_initrd_path=boot/initrd.img \0" \
		"nfsroot_path= \0" \
		"initargs="\
			"rootflags=data=writeback rw rootfstype=ext4 loglevel=4 " \
			"no_console_suspend " \
			"earlycon=aml-uart,0xff803000 ramoops.pstore_en=1 " \
			"ramoops.record_size=0x8000 ramoops.console_size=0x4000 "\
			"scsi_mod.scan=async xhci_hcd.quirks=0x800000 gamma=0 "\
			"\0"\
		"nfs_boot="\
			"dhcp;"\
			"setenv nfs_para root=/dev/nfs rw "\
				"nfsroot=${serverip}:${nfsroot_path} ip=:::::eth0:on;"\
			"printenv nfs_para;"\
			"setenv bootargs ${bootargs} ${nfs_para};"\
			"tftp ${dtb_mem_addr} ${tftp_dtb_path}${fdtfile};"\
			"tftp ${loadaddr_kernel} ${tftp_kernel_path};"\
			"tftp ${ramdisk_addr_r} ${tftp_initrd_path};"\
			"setenv ramdisk_size ${filesize};"\
			"echo ramdisk_size=${ramdisk_size};"\
			"booti ${loadaddr_kernel} ${ramdisk_addr_r}:${ramdisk_size} "\
					" ${dtb_mem_addr};"\
			"\0"\
		"upgrade_check="\
			"echo upgrade_step=${upgrade_step}; "\
			"if itest ${upgrade_step} == 3; then "\
				"run init_display; run update;"\
			"else fi;"\
			"\0"\
		"storeargs="\
			"get_bootloaderversion;" \
			"if test ${lcd_exist} != 1; then "\
				"setenv vout2_args ;"\
			"else "\
				"setenv vout2_args vout2=${outputmode2},enable;"\
			"fi;"\
			"setenv bootargs ${initargs} hdr_policy=${hdr_policy} "\
			"hdr_priority=${hdr_priority} "\
			"otg_device=${otg_device} reboot_mode_android=${reboot_mode_android} "\
			"logo=${display_layer},loaded,${fb_addr} "\
			"fb_width=${fb_width} fb_height=${fb_height} display_bpp=${display_bpp} "\
			"outputmode=${outputmode} ${vout2_args} "\
			"vout=${outputmode},${vout_init} "\
			"panel_type=${panel_type} lcd_ctrl=${lcd_ctrl} lcd_debug=${lcd_debug} "\
			"hdmitx=${cecconfig},${colorattribute} hdmimode=${hdmimode} "\
			"hdmichecksum=${hdmichecksum} dolby_vision_on=${dolby_vision_on} "\
			"frac_rate_policy=${frac_rate_policy} hdmi_read_edid=${hdmi_read_edid} "\
			"cvbsmode=${cvbsmode} osd_reverse=${osd_reverse} video_reverse=${video_reverse} "\
			"irq_check_en=${Irq_check_en}  androidboot.selinux=${EnableSelinux} "\
			"androidboot.firstboot=${firstboot} jtag=${jtag}; "\
			"setenv bootargs ${bootargs} androidboot.hardware=amlogic "\
				"androidboot.bootloader=${bootloader_version} "\
				"androidboot.build.expect.baseband=N/A boot_source=${boot_source} "\
                "ddr_size=${ddr_size} reboot_mode=${reboot_mode};"\
			"run cmdline_keys;"\
			"\0"\
		"legacyboot="\
			"kbi resetflag 0;"\
			"boot_cooling;"\
			"\0"\
		"storeboot="\
			"if load mmc 0:1 1020000 s905_autoscript || load mmc 1:1 1020000 s905_autoscript || load mmc 1:5 1020000 /boot/s905_autoscript; then autoscr 1020000; fi;"\
			"ext4load mmc 1:5 1080000 zImage;ext4load mmc 1:5 10000000 uInitrd;ext4load mmc 1:5 20000000 dtb.img;booti 1080000 10000000 20000000;"\
			"for p in 1 2 3 4 5 6 7 8 9 A B C D E F 10 11 12 13 14 15 16 17 18; do if fatload mmc 1:${p} ${loadaddr} aml_autoscript; then autoscr ${loadaddr}; fi; done;"\
			"run update;"\
			"\0"\
		"factory_reset_poweroff_protect="\
			"echo wipe_data=${wipe_data}; echo wipe_cache=${wipe_cache};"\
			"if test ${wipe_data} = failed; then "\
				"run init_display;"\
				"if mmcinfo; then "\
					"run recovery_from_sdcard;"\
				"fi;"\
				"if usb start 0; then "\
					"run recovery_from_udisk;"\
				"fi;"\
				"run recovery_from_flash;"\
			"fi; "\
			"if test ${wipe_cache} = failed; then "\
				"run init_display;"\
				"if mmcinfo; then "\
					"run recovery_from_sdcard;"\
				"fi;"\
				"if usb start 0; then "\
					"run recovery_from_udisk;"\
				"fi;"\
				"run recovery_from_flash;"\
			"fi; \0" \
		 "update="\
			/*first usb burning, second sdc_burn, third ext-sd autoscr/recovery, last udisk autoscr/recovery*/\
            "kbi lcd_reset; "\
			"run usb_burning; "\
			"run sdc_burning; "\
			"if mmcinfo; then "\
				"run recovery_from_sdcard;"\
			"fi;"\
			"if usb start 0; then "\
				"run recovery_from_udisk;"\
			"fi;"\
			"run recovery_from_flash;"\
			"\0"\
		"recovery_from_sdcard="\
			"if fatload mmc 0 ${loadaddr} aml_autoscript; then autoscr ${loadaddr}; fi;"\
			"if fatload mmc 0 ${loadaddr} recovery.img; then "\
					"if fatload mmc 0 ${dtb_mem_addr} dtb.img; then echo sd dtb.img loaded; fi;"\
					"wipeisb; "\
					"bootm ${loadaddr};fi;"\
			"\0"\
		"recovery_from_udisk="\
			"if fatload usb 0 ${loadaddr} aml_autoscript; then autoscr ${loadaddr}; fi;"\
			"if fatload usb 0 ${loadaddr} recovery.img; then "\
				"if fatload usb 0 ${dtb_mem_addr} dtb.img; then echo udisk dtb.img loaded; fi;"\
				"wipeisb; "\
				"bootm ${loadaddr};fi;"\
			"\0"\
		"recovery_from_flash="\
			"get_valid_slot;"\
			"echo active_slot: ${active_slot};"\
			"if test ${active_slot} = normal; then "\
				"setenv bootargs ${bootargs} aml_dt=${aml_dt} recovery_part={recovery_part} recovery_offset={recovery_offset};"\
				"if imgread kernel ${recovery_part} ${loadaddr} ${recovery_offset}; then wipeisb; bootm ${loadaddr}; fi;"\
			"else "\
				"setenv bootargs ${bootargs} aml_dt=${aml_dt} recovery_part=${boot_part} recovery_offset=${recovery_offset};"\
				"if imgread kernel ${boot_part} ${loadaddr}; then bootm ${loadaddr}; fi;"\
			"fi;"\
			"\0"\
		"load_bmp_logo="\
			"if load mmc 1:5 ${loadaddr} /usr/share/fenix/logo/logo.bmp || load mmc 1:2 ${loadaddr} /usr/share/fenix/logo/logo.bmp || load mmc 0:2 ${loadaddr} /usr/share/fenix/logo/logo.bmp; then "\
				"bmp display ${loadaddr};"\
				"bmp scale;"\
			"fi;"\
			"\0"\
		"init_display="\
			"get_rebootmode;"\
			"echo reboot_mode:::: ${reboot_mode};"\
			"if test ${reboot_mode} = quiescent; then "\
					"setenv reboot_mode_android ""quiescent"";"\
					"setenv dolby_status 0;"\
					"setenv dolby_vision_on 0;"\
					"run storeargs;"\
					"setenv bootargs ${bootargs} androidboot.quiescent=1;"\
					"osd open;osd clear;"\
			"else if test ${reboot_mode} = recovery_quiescent; then "\
					"setenv reboot_mode_android ""quiescent"";"\
					"setenv dolby_status 0;"\
					"setenv dolby_vision_on 0;"\
					"run storeargs;"\
					"setenv bootargs ${bootargs} androidboot.quiescent=1;"\
					"osd open;osd clear;"\
			"else "\
				"setenv reboot_mode_android ""normal"";"\
				"run storeargs;"\
				"hdmitx hpd;hdmitx get_parse_edid;"\
				"dovi process;osd dual_logo;"\
				"dovi set;dovi pkg;vpp hdrpkt;"\
			"fi;fi;"\
			"\0"\
        "wol_init="\
            "kbi init;"\
            "kbi powerstate;"\
            "kbi trigger wol r;"\
            "setenv bootargs ${bootargs} wol_enable=${wol_enable};"\
            "if test ${power_state} = 1; then "\
                "kbi poweroff;"\
            "else "\
                "kbi wolreset;"\
            "fi;"\
            "\0"\
		"port_mode_change="\
			"fdt addr ${dtb_mem_addr}; "\
            "kbi portmode r;"\
            "if test ${port_mode} = 0; then "\
                "fdt set /usb3phy@ffe09080 status okay;"\
                "fdt set /pcieA@fc000000 status disable;"\
            "else "\
                "fdt set /usb3phy@ffe09080 status disable;"\
                "fdt set /pcieA@fc000000 status okay;"\
            "fi;"\
            "\0"\
        "cmdline_keys="\
            "if keyman init 0x1234; then "\
                "if keyman read usid ${loadaddr} str; then "\
                    "setenv bootargs ${bootargs} androidboot.serialno=${usid};"\
                    "setenv serial ${usid};"\
                "else "\
                    "setenv bootargs ${bootargs} androidboot.serialno=1234567890;"\
                    "setenv serial 1234567890;"\
                "fi;"\
                "kbi ethmac;"\
                "setenv bootargs ${bootargs} mac=${eth_mac} androidboot.mac=${eth_mac};"\
                "if keyman read deviceid ${loadaddr} str; then "\
                    "setenv bootargs ${bootargs} androidboot.deviceid=${deviceid};"\
                "fi;"\
            "fi;"\
			"\0"\
		"upgrade_key="\
            "if gpio input GPIOAO_7; then "\
                "echo detect upgrade key;"\
                "gpio set GPIOAO_4;"\
                "run fan_stop;"\
                "run update;"\
			"fi;"\
			"\0"\
		"irremote_update="\
			"if irkey 2500000 0xe31cfb04 0xb748fb04; then "\
				"echo read irkey ok!; " \
				"if itest ${irkey_value} == 0xe31cfb04; then " \
					"run update;" \
				"else if itest ${irkey_value} == 0xb748fb04; then " \
					"run update;\n" \
				"fi;fi;" \
			"fi;\0" \
        "updateu="\
            "if tftp 1080000 u-boot.bin; then "\
                "mmc dev 1;"\
                "store rom_write 1080000 0 ${filesize}; " \
            "fi;"\
            "\0" \
        "vim3_check="\
            "kbi hwver; "\
            "echo Hardware version: ${hwver};" \
            "setenv bootargs ${bootargs} hwver=${hwver};"\
            "\0"\
        "fan_stop=" \
            "i2c mw 0x18 0x88 0" \
            "\0"\
		BOOTENV\
		"pxe_boot=dhcp; pxe get && pxe boot\0"\
		"bootcmd_spi="\
			"saradc open 2 && saradc getval && saradc close; "\
		        "if test ${saradc_val} -lt 0x100; then "\
				"setenv orig_source ${boot_source}; setenv boot_source spi; setenv devtype spi; setenv devnum 0; "\
				"sf probe && sf read $loadaddr 0x160000 0x8000 && script $loadaddr - 0 1; "\
				"setenv boot_source ${orig_source}; "\
			"fi\0"\
		"bootcmd_legacy=run legacyboot\0"\
		"bootcmd_storeboot=run storeboot\0"\
		"boot_targets=spi legacy usb0 mmc0 mmc1 storeboot pxe dhcp\0"

#define CONFIG_PREBOOT  \
			"run upgrade_check;"\
			"run init_display;"\
			"run storeargs;"\
			"run upgrade_key;"\
			"run vim3_check;" \
			"run wol_init;"\
			"run port_mode_change;"\
			"forceupdate;" \
			"run fan_stop;"

/*
 * logo image path: device/amlogic/$(proj_name)/logo_img_files/
 *
 * dual logo config macro
 * logo1: bootup.bmp/bootup_rotate.bmp (or find env "board_defined_bootup" first in uboot)
 * logo2: bootup_rotate_secondary.bmp (for portrait screen)
 */
#define CONFIG_DUAL_LOGO \
	"setenv outputmode panel;setenv display_layer osd0;"\
	"if test ${lcd_exist} = 1; then "\
		"if test ${panel_type} = mipi_2; then "\
			"setenv fb_width 1920;"\
			"setenv fb_height 1200;"\
		"else "\
			"setenv fb_width 1080;"\
			"setenv fb_height 1920;"\
		"fi;"\
	"else "\
		"setenv fb_width 1920; setenv fb_height 1080;" \
	"fi; "\
	"vout output ${outputmode};osd open;osd clear;run load_bmp_logo;"\
	"setenv outputmode2 ${hdmimode};setenv display_layer viu2_osd0;"\
	"vout2 prepare ${outputmode2};"\
	"vout2 output ${outputmode2};osd open;osd clear;"\
	"run load_bmp_logo;bmp scale;"\
	"\0"\

/* for portrait panel, recovery always displays on panel */
#define CONFIG_RECOVERY_DUAL_LOGO \
	"setenv outputmode panel;setenv display_layer osd0;"\
	"if test ${lcd_exist} = 1; then "\
		"if test ${panel_type} = mipi_2; then "\
			"setenv fb_width 1920;"\
			"setenv fb_height 1200;"\
		"else "\
			"setenv fb_width 1080;"\
			"setenv fb_height 1920;"\
		"fi;"\
	"else "\
		"setenv fb_width 1920; setenv fb_height 1080;" \
	"fi; "\
	"vout output $outputmode;osd open;osd clear;imgread pic logo bootup_rotate $loadaddr;"\
	"bmp display $bootup_rotate_offset;bmp scale;"\
	"setenv outputmode2 1080p60hz;setenv display_layer viu2_osd0;"\
	"vout2 prepare $outputmode2;vout2 output $outputmode2;osd open;osd clear;"\
	"imgread pic logo bootup $loadaddr;bmp display $bootup_offset;bmp scale;"\
	"\0"\
/* single logo */
#define CONFIG_SINGLE_LOGO \
	"if test ${lcd_exist} = 1; then "\
		"if test ${panel_type} = mipi_2; then "\
			"setenv fb_width 1920;"\
			"setenv fb_height 1200;"\
		"else "\
			"setenv fb_width 1080;"\
			"setenv fb_height 1920;"\
		"fi;"\
	"else "\
		"setenv fb_width 1920; setenv fb_height 1080;" \
	"fi; "\
	"setenv display_layer osd0;osd open;osd clear;"\
	"run load_bmp_logo;bmp scale;vout output ${outputmode};"\
	"\0"

//#define CONFIG_ENV_IS_NOWHERE  1
#define CONFIG_ENV_SIZE   (64 * 1024)
#define CONFIG_FIT 1
#define CONFIG_OF_LIBFDT 1
#define CONFIG_ANDROID_BOOT_IMAGE 1
#define CONFIG_ANDROID_IMG 1
#define CONFIG_SYS_BOOTM_LEN (64 << 20) /* Increase max gunzip size*/

/* cpu */
#define CONFIG_CPU_CLK 1200 //MHz. Range: 360-2000, should be multiple of 24

/* ATTENTION */
/* DDR configs move to board/amlogic/[board]/firmware/timing.c */

#define CONFIG_NR_DRAM_BANKS			1
/* ddr functions */
#define CONFIG_DDR_FULL_TEST			0 //0:disable, 1:enable. ddr full test
#define CONFIG_CMD_DDR_D2PLL			0 //0:disable, 1:enable. d2pll cmd
#define CONFIG_CMD_DDR_TEST				0 //0:disable, 1:enable. ddrtest cmd
#define CONFIG_CMD_DDR_TEST_G12			1 //0:disable, 1:enable. G12 ddrtest cmd
#define CONFIG_DDR_LOW_POWER			0 //0:disable, 1:enable. ddr clk gate for lp
#define CONFIG_DDR_ZQ_PD				0 //0:disable, 1:enable. ddr zq power down
#define CONFIG_DDR_USE_EXT_VREF			0 //0:disable, 1:enable. ddr use external vref
#define CONFIG_DDR4_TIMING_TEST			0 //0:disable, 1:enable. ddr4 timing test function
#define CONFIG_DDR_PLL_BYPASS			0 //0:disable, 1:enable. ddr pll bypass function
#define CONFIG_DDR_NONSEC_SCRAMBLE		0 //0:disable, 1:enable. non-sec region scramble function

/* storage: emmc/nand/sd */
#define		CONFIG_STORE_COMPATIBLE 1
#define 	CONFIG_ENV_OVERWRITE
#define 	CONFIG_CMD_SAVEENV
/* fixme, need fix*/

#if (defined(CONFIG_ENV_IS_IN_AMLNAND) || defined(CONFIG_ENV_IS_IN_MMC)) && defined(CONFIG_STORE_COMPATIBLE)
#error env in amlnand/mmc already be compatible;
#endif

/*
*				storage
*		|---------|---------|
*		|					|
*		emmc<--Compatible-->nand
*					|-------|-------|
*					|				|
*					MTD<-Exclusive->NFTL
*/
/* axg only support slc nand */
/* swither for mtd nand which is for slc only. */

#if defined(CONFIG_AML_NAND) && defined(CONFIG_AML_MTD)
#error CONFIG_AML_NAND/CONFIG_AML_MTD can not support at the sametime;
#endif

#ifdef CONFIG_AML_MTD

/* bootloader is construct by bl2 and fip
 * when DISCRETE_BOOTLOADER is enabled, bl2 & fip
 * will not be stored continuously, and nand layout
 * would be bl2|rsv|fip|normal, but not
 * bl2|fip|rsv|normal anymore
 */
#define CONFIG_DISCRETE_BOOTLOADER

#ifdef CONFIG_DISCRETE_BOOTLOADER
#define CONFIG_TPL_SIZE_PER_COPY		  0x200000
#define CONFIG_TPL_COPY_NUM			   4
#define CONFIG_TPL_PART_NAME			  "tpl"
/* for bl2, restricted by romboot */
//SKT 1024 pages only support 4 block, so 4 copies
#define CONFIG_BL2_COPY_NUM			   4
#endif /* CONFIG_DISCRETE_BOOTLOADER */

#define CONFIG_MTD_DEVICE y
/* mtd parts of ourown.*/
#define CONFIG_AML_MTDPART	1

#define CONFIG_CMD_UBI
#define CONFIG_CMD_UBIFS
#define CONFIG_RBTREE
#define CONFIG_CMD_MTDPARTS   1
#define CONFIG_MTD_PARTITIONS 1
#endif
/* endof CONFIG_AML_MTD */
#define CONFIG_AML_SD_EMMC 1
#ifdef CONFIG_AML_SD_EMMC
	#define		CONFIG_GENERIC_MMC 1
	#define		CONFIG_CMD_MMC 1
	#define		CONFIG_CMD_GPT 1
	#define		CONFIG_SYS_MMC_ENV_DEV 1
	#define		CONFIG_EMMC_DDR52_EN 0
	#define		CONFIG_EMMC_DDR52_CLK 35000000
#endif
#define		CONFIG_PARTITIONS 1
#define		CONFIG_SYS_NO_FLASH  1

/* meson SPI */
#define CONFIG_AML_SPIFC
#if defined CONFIG_AML_SPIFC || defined CONFIG_AML_SPICC
	#define CONFIG_OF_SPI
	#define CONFIG_DM_SPI
	#define CONFIG_CMD_SPI
#endif
/* SPI flash config */
#ifdef CONFIG_AML_SPIFC
	#define CONFIG_SPI_FLASH
	#define CONFIG_DM_SPI_FLASH
	#define CONFIG_CMD_SF
	/* SPI flash support list */
	#define CONFIG_SPI_FLASH_ATMEL
	#define CONFIG_SPI_FLASH_EON
	#define CONFIG_SPI_FLASH_GIGADEVICE
	#define CONFIG_SPI_FLASH_MACRONIX
	#define CONFIG_SPI_FLASH_SPANSION
	#define CONFIG_SPI_FLASH_STMICRO
	#define CONFIG_SPI_FLASH_SST
	#define CONFIG_SPI_FLASH_WINBOND
	#define CONFIG_SPI_FRAM_RAMTRON
	#define CONFIG_SPI_M95XXX
	#define CONFIG_SPI_FLASH_ESMT
	/* SPI nand flash support */
	#define CONFIG_BL2_SIZE (64 * 1024)
#endif

#if defined CONFIG_AML_MTD || defined CONFIG_SPI_NAND
	#define CONFIG_MTD_DEVICE y
	#define CONFIG_RBTREE
	#define CONFIG_CMD_MTDPARTS   1
	#define CONFIG_MTD_PARTITIONS 1
#endif

/* vpu */
#define CONFIG_AML_VPU 1
//#define CONFIG_VPU_CLK_LEVEL_DFT 7

/* DISPLAY & HDMITX */
#define CONFIG_AML_HDMITX20 1
#if defined(CONFIG_AML_HDMITX20)
#define CONFIG_AML_DOLBY 1
#define CONFIG_CMD_INI 1
#endif
#define CONFIG_AML_CANVAS 1
#define CONFIG_AML_VOUT 1
#define CONFIG_AML_OSD 1
#define CONFIG_AML_MINUI 1
#define CONFIG_OSD_SCALE_ENABLE 1
#define CONFIG_CMD_BMP 1

#if defined(CONFIG_AML_VOUT)
#define CONFIG_AML_CVBS 1
#endif

#define CONFIG_AML_LCD	1
#define CONFIG_AML_LCD_TABLET 1
#define CONFIG_AML_LCD_EXTERN 1

/* USB
 * Enable CONFIG_MUSB_HCD for Host functionalities MSC, keyboard
 * Enable CONFIG_MUSB_UDD for Device functionalities.
 */
/* #define CONFIG_MUSB_UDC		1 */
#define CONFIG_CMD_USB 1
#if defined(CONFIG_CMD_USB)
	#define CONFIG_GXL_XHCI_BASE			0xff500000
	#define CONFIG_GXL_USB_PHY2_BASE		0xffe09000
	#define CONFIG_GXL_USB_PHY3_BASE		0xffe09080
	#define CONFIG_USB_PHY_20				0xff636000
	#define CONFIG_USB_PHY_21				0xff63A000
	#define CONFIG_USB_STORAGE	  1
	#define CONFIG_USB_XHCI		1
	#define CONFIG_USB_XHCI_AMLOGIC_V2 1
	#define CONFIG_USB_GPIO_PWR			GPIOEE(GPIOA_6)
	#define CONFIG_USB_GPIO_PWR_NAME		"GPIOA_6"
	//#define CONFIG_USB_XHCI_AMLOGIC_USB3_V2		1
#endif //#if defined(CONFIG_CMD_USB)

#define CONFIG_TXLX_USB		1
#define CONFIG_USB_DEVICE_V2	1
#define USB_PHY2_PLL_PARAMETER_1	0x09400414
#define USB_PHY2_PLL_PARAMETER_2	0x927e0000
#define USB_PHY2_PLL_PARAMETER_3	0xAC5F69E5
#define USB_G12x_PHY_PLL_SETTING_1	(0xfe18)
#define USB_G12x_PHY_PLL_SETTING_2	(0xfff)
#define USB_G12x_PHY_PLL_SETTING_3	(0x78000)
#define USB_G12x_PHY_PLL_SETTING_4	(0xe0004)
#define USB_G12x_PHY_PLL_SETTING_5	(0xe000c)

//UBOOT fastboot config
#define CONFIG_CMD_FASTBOOT 1
#define CONFIG_FASTBOOT_FLASH_MMC_DEV 1
#define CONFIG_FASTBOOT_FLASH 1
#define CONFIG_USB_GADGET 1
#define CONFIG_USBDOWNLOAD_GADGET 1
#define CONFIG_SYS_CACHELINE_SIZE 64
#define CONFIG_FASTBOOT_MAX_DOWN_SIZE	0x8000000
#define CONFIG_DEVICE_PRODUCT	"galilei"

//UBOOT Factory usb/sdcard burning config
#define CONFIG_AML_V2_FACTORY_BURN			  1	   //support factory usb burning
#define CONFIG_AML_FACTORY_BURN_LOCAL_UPGRADE   1	   //support factory sdcard burning
#define CONFIG_POWER_KEY_NOT_SUPPORTED_FOR_BURN 1	   //There isn't power-key for factory sdcard burning
#define CONFIG_SD_BURNING_SUPPORT_UI			1	   //Displaying upgrading progress bar when sdcard/udisk burning

#define CONFIG_AML_SECURITY_KEY				 1
#define CONFIG_UNIFY_KEY_MANAGE				 1

/* net */
#define CONFIG_CMD_NET   1
#if defined(CONFIG_CMD_NET)
	#define CONFIG_DESIGNWARE_ETH 1
	#define CONFIG_PHYLIB	1
	#define CONFIG_NET_MULTI 1
	#define CONFIG_CMD_PING 1
	#define CONFIG_CMD_DHCP 1
	#define CONFIG_CMD_RARP 1
	#define CONFIG_HOSTNAME        KVIM3
//	#define CONFIG_RANDOM_ETHADDR  1				   /* use random eth addr, or default */
	#define CONFIG_ETHADDR		 00 : 15 : 18 : 01 : 81 : 31   /* Ethernet address */
	#define CONFIG_IPADDR		  192.168.31.200		  /* Our ip address */
	#define CONFIG_GATEWAYIP	   192.168.31.1		   /* Our getway ip address */
	#define CONFIG_SERVERIP		192.168.31.230		 /* Tftp server ip address */
	#define CONFIG_NETMASK		 255.255.255.0
#endif /* (CONFIG_CMD_NET) */

/* other devices */
/* I2C DM driver*/
//#define CONFIG_DM_I2C
//#define CONFIG_DM_I2C_GPIO		1
#if defined(CONFIG_DM_I2C)
#define CONFIG_SYS_I2C_MESON		1
#else
#define CONFIG_SYS_I2C_AML			1
#define CONFIG_SYS_I2C_SPEED		400000
#endif

/* PWM DM driver*/
#define CONFIG_DM_PWM
#define CONFIG_PWM_MESON

#define CONFIG_EFUSE 1

/* commands */
#define CONFIG_CMD_CACHE 1
#define CONFIG_CMD_BOOTI 1
#define CONFIG_CMD_EFUSE 1
#define CONFIG_CMD_I2C 1
#define CONFIG_CMD_MEMORY 1
#define CONFIG_CMD_FAT 1
#define CONFIG_CMD_GPIO 1
#define CONFIG_CMD_RUN
#define CONFIG_CMD_REBOOT 1
#define CONFIG_CMD_ECHO 1
#define CONFIG_CMD_JTAG	1
#define CONFIG_CMD_AUTOSCRIPT 1
#define CONFIG_CMD_MISC 1
#define CONFIG_CMD_PLLTEST 1
#define CONFIG_CMD_EXT4 1
#define CONFIG_CMD_EXT2 1
#define CONFIG_CMD_ENV_EXISTS 1
#define CONFIG_CMD_FS_GENERIC 1
#define CONFIG_CMD_PART 1

/*file system*/
#define CONFIG_DOS_PARTITION 1
#define CONFIG_EFI_PARTITION 1
#define CONFIG_AML_PARTITION 1
#define CONFIG_MMC 1
#define CONFIG_FS_FAT 1
#define CONFIG_FS_EXT4 1
#define CONFIG_LZO 1
#define CONFIG_LZMA 1

#define CONFIG_MDUMP_COMPRESS 1
#define CONFIG_EXT4_WRITE 1
#define CONFIG_CMD_UNZIP	1
#define CONFIG_LZMA		 1
#define CONFIG_FAT_WRITE	1
#define CONFIG_CMD_EXT4_WRITE	1

/* Cache Definitions */
//#define CONFIG_SYS_DCACHE_OFF
//#define CONFIG_SYS_ICACHE_OFF

/* other functions */
#define CONFIG_NEED_BL301	1
#define CONFIG_NEED_BL32	1
#define CONFIG_CMD_RSVMEM	1
#define CONFIG_FIP_IMG_SUPPORT	1
#define CONFIG_BOOTDELAY	1 //delay 1s
#define CONFIG_SYS_LONGHELP 1
#define CONFIG_CMD_MISC	 1
#define CONFIG_CMD_ITEST	1
#define CONFIG_CMD_CPU_TEMP 1
#define CONFIG_SYS_MEM_TOP_HIDE 0x08000000 //hide 128MB for kernel reserve
#define CONFIG_CMD_LOADB	1


/* debug mode defines */
//#define CONFIG_DEBUG_MODE		   1
#ifdef CONFIG_DEBUG_MODE
#define CONFIG_DDR_CLK_DEBUG		636
#define CONFIG_CPU_CLK_DEBUG		600
#endif

//Command line interface
#define CONFIG_CMDLINE			1
#define CONFIG_CMDLINE_EDITING	1
#define CONFIG_AUTO_COMPLETE	1

//Autoboot options
#define CONFIG_AUTOBOOT				1

//support secure boot
#define CONFIG_AML_SECURE_UBOOT   1

#if defined(CONFIG_AML_SECURE_UBOOT)

//unify build for generate encrypted bootloader "u-boot.bin.encrypt"
#define CONFIG_AML_CRYPTO_UBOOT   1

//unify build for generate encrypted kernel image
//SRC : "board/amlogic/(board)/boot.img"
//DST : "fip/boot.img.encrypt"
//#define CONFIG_AML_CRYPTO_IMG	   1

#endif //CONFIG_AML_SECURE_UBOOT

#define CONFIG_SECURE_STORAGE 1

#undef CONFIG_SYS_CBSIZE
#define CONFIG_SYS_CBSIZE 4096

/* support bmp display */
#define CONFIG_SYS_VIDEO_LOGO_MAX_SIZE 8192000
#define CONFIG_VIDEO_BMP_GZIP 1
//#define CONFIG_CFB_CONSOLE 1

//build with uboot auto test
//#define CONFIG_AML_UBOOT_AUTO_TEST 1

//board customer ID
//#define CONFIG_CUSTOMER_ID  (0x6472616F624C4D41)

#if defined(CONFIG_CUSTOMER_ID)
  #undef CONFIG_AML_CUSTOMER_ID
  #define CONFIG_AML_CUSTOMER_ID  CONFIG_CUSTOMER_ID
#endif

/* Choose One of Ethernet Type */
#undef CONFIG_ETHERNET_NONE
#define ETHERNET_EXTERNAL_PHY
#undef  ETHERNET_INTERNAL_PHY

#define CONFIG_HIGH_TEMP_COOL 90
#define CONFIG_AML_KASLR_SEED

#endif

