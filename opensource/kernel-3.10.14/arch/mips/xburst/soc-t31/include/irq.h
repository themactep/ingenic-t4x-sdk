/*
 *  Copyright (C) 2010 Ingenic Semiconductor Inc.
 *
 *  Author: <zpzhong@ingenic.cn>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef __ASM_MACH_INGENIC_IRQ_H__
#define __ASM_MACH_INGENIC_IRQ_H__

/* IRQ for MIPS CPU */
#define MIPS_CPU_IRQ_BASE		0
#define IRQ_SMP_RESCHEDULE_YOURSELF	3
#define IRQ_SMP_CALL_FUNCTION		4

#define INTC_IRQ_BASE		8

enum {
#define INTC_NR_IRQS	64
	IRQ_INTC_BASE = INTC_IRQ_BASE,
	IRQ_INTC_END = IRQ_INTC_BASE + INTC_NR_IRQS - 1,

#define OST_NR_IRQS 3
	IRQ_OST_BASE,
	IRQ_OST_END = IRQ_OST_BASE + OST_NR_IRQS - 1,

#define GPIO_NR_IRQS	(32 * 3 + 16)
	IRQ_GPIO_BASE,
	IRQ_GPIO_END = IRQ_GPIO_BASE + GPIO_NR_IRQS - 1,

#define SADC_NR_IRQS	(8)
	IRQ_SADC_BASE,
	IRQ_SADC_END = IRQ_SADC_BASE + SADC_NR_IRQS - 1,

#define MCU_NR_IRQS    (5)
	IRQ_MCU_BASE,
	IRQ_MCU_END = IRQ_MCU_BASE + MCU_NR_IRQS - 1,

#define TCU_NR_IRQS	(8)
	IRQ_TCU_BASE,
	IRQ_TCU_END = IRQ_TCU_BASE + TCU_NR_IRQS - 1,

#define RESERVED_NR_IRQS	(150)
	IRQ_RESERVED_BASE,
	IRQ_RESERVED_END = IRQ_RESERVED_BASE + RESERVED_NR_IRQS - 1,
	NR_IRQS,
};

#endif