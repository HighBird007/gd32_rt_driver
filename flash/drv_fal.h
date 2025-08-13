/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-06-12     liuxin       the first version
 */
#ifndef DRIVERS_DRV_FAL_H_
#define DRIVERS_DRV_FAL_H_
#include "rtdevice.h"
#include "rtthread.h"
#include <rtconfig.h>
#include <board.h>
#include "fal.h"

#define ADDR_FMC_SECTOR_0       ((uint32_t)0x08000000U) /*!< base address of sector 0,  16 kbytes */
#define ADDR_FMC_SECTOR_1       ((uint32_t)0x08004000U) /*!< base address of sector 1,  16 kbytes */
#define ADDR_FMC_SECTOR_2       ((uint32_t)0x08008000U) /*!< base address of sector 2,  16 kbytes */
#define ADDR_FMC_SECTOR_3       ((uint32_t)0x0800C000U) /*!< base address of sector 3,  16 kbytes */
#define ADDR_FMC_SECTOR_4       ((uint32_t)0x08010000U) /*!< base address of sector 4,  64 kbytes */
#define ADDR_FMC_SECTOR_5       ((uint32_t)0x08020000U) /*!< base address of sector 5, 128 kbytes */
#define ADDR_FMC_SECTOR_6       ((uint32_t)0x08040000U) /*!< base address of sector 6, 128 kbytes */
#define ADDR_FMC_SECTOR_7       ((uint32_t)0x08060000U) /*!< base address of sector 7, 128 kbytes */
#define ADDR_FMC_SECTOR_8       ((uint32_t)0x08080000U) /*!< base address of sector 8, 128 kbytes */
#define ADDR_FMC_SECTOR_9       ((uint32_t)0x080A0000U) /*!< base address of sector 9, 128 kbytes */
#define ADDR_FMC_SECTOR_10      ((uint32_t)0x080C0000U) /*!< base address of sector 10,128 kbytes */
#define ADDR_FMC_SECTOR_11      ((uint32_t)0x080E0000U) /*!< base address of sector 11,128 kbytes */
#define ADDR_FMC_SECTOR_12      ((uint32_t)0x08100000U) /*!< base address of sector 12, 16 kbytes */
#define ADDR_FMC_SECTOR_13      ((uint32_t)0x08104000U) /*!< base address of sector 13, 16 kbytes */
#define ADDR_FMC_SECTOR_14      ((uint32_t)0x08108000U) /*!< base address of sector 14, 16 kbytes */
#define ADDR_FMC_SECTOR_15      ((uint32_t)0x0810C000U) /*!< base address of sector 15, 16 kbytes */
#define ADDR_FMC_SECTOR_16      ((uint32_t)0x08110000U) /*!< base address of sector 16, 64 kbytes */
#define ADDR_FMC_SECTOR_17      ((uint32_t)0x08120000U) /*!< base address of sector 17,128 kbytes */
#define ADDR_FMC_SECTOR_18      ((uint32_t)0x08140000U) /*!< base address of sector 18,128 kbytes */
#define ADDR_FMC_SECTOR_19      ((uint32_t)0x08160000U) /*!< base address of sector 19,128 kbytes */
#define ADDR_FMC_SECTOR_20      ((uint32_t)0x08180000U) /*!< base address of sector 20,128 kbytes */
#define ADDR_FMC_SECTOR_21      ((uint32_t)0x081A0000U) /*!< base address of sector 21,128 kbytes */
#define ADDR_FMC_SECTOR_22      ((uint32_t)0x081C0000U) /*!< base address of sector 22,128 kbytes */
#define ADDR_FMC_SECTOR_23      ((uint32_t)0x081E0000U) /*!< base address of sector 23, 128 Kbytes */

#define ADDR_FMC_SECTOR_24      ((uint32_t)(ADDR_FMC_SECTOR_23 + 128 * 1024U)) /*!< base address of sector 24, 256 Kbytes */
#define ADDR_FMC_SECTOR_25      ((uint32_t)(ADDR_FMC_SECTOR_24 + 256 * 1024U)) /*!< base address of sector 25, 256 Kbytes */
#define ADDR_FMC_SECTOR_26      ((uint32_t)(ADDR_FMC_SECTOR_25 + 256 * 1024U)) /*!< base address of sector 26, 256 Kbytes */
#define ADDR_FMC_SECTOR_27      ((uint32_t)(ADDR_FMC_SECTOR_26 + 256 * 1024U)) /*!< base address of sector 27, 256 Kbytes */


/* Flash ???? */
#define FLASH_START_ADDR 0x08000000U
#define FLASH_END_ADDR   0x08300000U

#endif /* DRIVERS_DRV_FAL_H_ */
