
#include <linux/platform_device.h>
#include <linux/linux_pmem.h>
#include "board_base.h"

#ifdef CONFIG_JZ_MAC
#ifndef CONFIG_MDIO_GPIO
#ifdef CONFIG_JZGPIO_PHY_RESET
static struct jz_gpio_phy_reset gpio_phy_reset = {
	.port = GMAC_PHY_PORT_GPIO / 32,
	.pin = GMAC_PHY_PORT_GPIO % 32,
	.start_func = GMAC_PHY_PORT_START_FUNC,
	.end_func = GMAC_PHY_PORT_END_FUNC,
	.delaytime_usec = GMAC_PHY_DELAYTIME,
};
#endif
struct platform_device jz_mii_bus = {
	.name = "jz_mii_bus",
#ifdef CONFIG_JZGPIO_PHY_RESET
	.dev.platform_data = &gpio_phy_reset,
#endif
};
#else /* CONFIG_MDIO_GPIO */
static struct mdio_gpio_platform_data mdio_gpio_data = {
	.mdc = MDIO_MDIO_MDC_GPIO,
	.mdio = MDIO_MDIO_GPIO,
	.phy_mask = 0,
	.irqs = { 0 },
};

struct platform_device jz_mii_bus = {
	.name = "mdio-gpio",
	.dev.platform_data = &mdio_gpio_data,
};
#endif /* CONFIG_MDIO_GPIO */
struct platform_device jz_mac_device = {
	.name = "jz_mac",
	.dev.platform_data = &jz_mii_bus,
};
#endif /* CONFIG_JZ_MAC */

#ifdef CONFIG_JZ_EFUSE_V12
struct jz_efuse_platform_data jz_efuse_pdata = {
	/* supply 2.5V to VDDQ */
	.gpio_vddq_en_n = GPIO_EFUSE_VDDQ,
};
#endif

#ifdef CONFIG_CHARGER_LI_ION
/* li-ion charger */
static struct li_ion_charger_platform_data jz_li_ion_charger_pdata = {
	.gpio_charge = GPIO_LI_ION_CHARGE,
	.gpio_ac = GPIO_LI_ION_AC,
	.gpio_active_low = GPIO_ACTIVE_LOW,
};

static struct platform_device jz_li_ion_charger_device = {
	.name = "li-ion-charger",
	.dev = {
		.platform_data = &jz_li_ion_charger_pdata,
	},
};
#endif


#ifdef CONFIG_JZ_BATTERY
static struct jz_battery_info  dorado_battery_info = {
	.max_vol        = 4050,
	.min_vol        = 3600,
	.usb_max_vol    = 4100,
	.usb_min_vol    = 3760,
	.ac_max_vol     = 4100,
	.ac_min_vol     = 3760,
	.battery_max_cpt = 3000,
	.ac_chg_current = 800,
	.usb_chg_current = 400,
};
struct jz_adc_platform_data adc_platform_data = {
	battery_info = dorado_battery_info;
}
#endif

#ifdef CONFIG_LINUX_PMEM
static struct android_pmem_platform_data pmem_pdata = {
	.name = "pmem",
	.no_allocator = 0,
	.cached = 0,
};

static int __init pmem_parse(char *str)
{
	char *retptr;
	unsigned long pmem_size;
	unsigned long pmem_base = -1;

	pmem_size = memparse(str, &retptr);
	if(pmem_size < 0) {
		printk("pmem_size is error, use default !\n");
		pmem_size = 0x4000000;
	}

	if (*retptr == '@')
		pmem_base = memparse(retptr + 1, NULL);

	if(pmem_base < 0) {
		printk("pmem_base is error, use default !\n");
		pmem_base = 0xc000000;
	}

	pmem_pdata.start = pmem_base;
	pmem_pdata.size = pmem_size;

//	printk("pmem_pdata.start : %lx\n", pmem_pdata.start);
//	printk("pmem_pdata.size  : %lx\n", pmem_pdata.size);

	return 1;
}
__setup("pmem=", pmem_parse);

struct platform_device pmem_device = {
	.name = "pmem",
	.id = 0,
	.dev = {
		.platform_data = &pmem_pdata,
	},
};
#endif

#if defined(CONFIG_USB_JZ_DWC2) || defined(CONFIG_USB_DWC_OTG)
#if defined(GPIO_USB_ID) && defined(GPIO_USB_ID_LEVEL)
struct jzdwc_pin dwc2_id_pin = {
	.num = GPIO_USB_ID,
	.enable_level = GPIO_USB_ID_LEVEL,
};
#endif

#if defined(GPIO_USB_DETE) && defined(GPIO_USB_DETE_LEVEL)
struct jzdwc_pin dwc2_dete_pin = {
	.num = GPIO_USB_DETE,
	.enable_level = GPIO_USB_DETE_LEVEL,
};
#endif

#if defined(GPIO_USB_DRVVBUS) && defined(GPIO_USB_DRVVBUS_LEVEL) && !defined(USB_DWC2_DRVVBUS_FUNCTION_PIN)
struct jzdwc_pin dwc2_drvvbus_pin = {
	.num = GPIO_USB_DRVVBUS,
	.enable_level = GPIO_USB_DRVVBUS_LEVEL,
};
#endif
#endif /*CONFIG_USB_JZ_DWC2 || CONFIG_USB_DWC_OTG*/