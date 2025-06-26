/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-06-12     liuxin       the first version
 */
#include "drv_fal.h"

/* Flash 地址范围 */
#define FLASH_START_ADDR 0x08000000U
#define FLASH_END_ADDR   0x08300000U

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
#define ADDR_FMC_SECTOR_23      ((uint32_t)0x081E0000U) /*!< base address of sector 23,128 kbytes */

static const struct
{
    uint32_t address; /* 扇区起始地址 */
    uint32_t number; /* 扇区编号 */
} sector_info[] = { { ADDR_FMC_SECTOR_0, CTL_SECTOR_NUMBER_0 }, /* 0x08000000, 0   */
{ ADDR_FMC_SECTOR_1, CTL_SECTOR_NUMBER_1 }, /* 0x08004000, 8   */
{ ADDR_FMC_SECTOR_2, CTL_SECTOR_NUMBER_2 }, /* 0x08008000, 16  */
{ ADDR_FMC_SECTOR_3, CTL_SECTOR_NUMBER_3 }, /* 0x0800C000, 24  */
{ ADDR_FMC_SECTOR_4, CTL_SECTOR_NUMBER_4 }, /* 0x08010000, 32  */
{ ADDR_FMC_SECTOR_5, CTL_SECTOR_NUMBER_5 }, /* 0x08020000, 40  */
{ ADDR_FMC_SECTOR_6, CTL_SECTOR_NUMBER_6 }, /* 0x08040000, 48  */
{ ADDR_FMC_SECTOR_7, CTL_SECTOR_NUMBER_7 }, /* 0x08060000, 56  */
{ ADDR_FMC_SECTOR_8, CTL_SECTOR_NUMBER_8 }, /* 0x08080000, 64  */
{ ADDR_FMC_SECTOR_9, CTL_SECTOR_NUMBER_9 }, /* 0x080A0000, 72  */
{ ADDR_FMC_SECTOR_10, CTL_SECTOR_NUMBER_10 }, /* 0x080C0000, 80  */
{ ADDR_FMC_SECTOR_11, CTL_SECTOR_NUMBER_11 }, /* 0x080E0000, 88  */
{ ADDR_FMC_SECTOR_12, CTL_SECTOR_NUMBER_12 }, /* 0x08100000, 128 */
{ ADDR_FMC_SECTOR_13, CTL_SECTOR_NUMBER_13 }, /* 0x08104000, 136 */
{ ADDR_FMC_SECTOR_14, CTL_SECTOR_NUMBER_14 }, /* 0x08108000, 144 */
{ ADDR_FMC_SECTOR_15, CTL_SECTOR_NUMBER_15 }, /* 0x0810C000, 152 */
{ ADDR_FMC_SECTOR_16, CTL_SECTOR_NUMBER_16 }, /* 0x08110000, 160 */
{ ADDR_FMC_SECTOR_17, CTL_SECTOR_NUMBER_17 }, /* 0x08120000, 168 */
{ ADDR_FMC_SECTOR_18, CTL_SECTOR_NUMBER_18 }, /* 0x08140000, 176 */
{ ADDR_FMC_SECTOR_19, CTL_SECTOR_NUMBER_19 }, /* 0x08160000, 184 */
{ ADDR_FMC_SECTOR_20, CTL_SECTOR_NUMBER_20 }, /* 0x08180000, 192 */
{ ADDR_FMC_SECTOR_21, CTL_SECTOR_NUMBER_21 }, /* 0x081A0000, 200 */
{ ADDR_FMC_SECTOR_22, CTL_SECTOR_NUMBER_22 }, /* 0x081C0000, 208 */
{ ADDR_FMC_SECTOR_23, CTL_SECTOR_NUMBER_23 }, /* 0x081E0000, 216 */
};

#define SECTOR_COUNT (sizeof(sector_info) / sizeof(sector_info[0]))

/*!
 \brief      gets the sector of a given address
 \param[in]  addr: a given address(0x08000000~0x08300000)
 \param[out] none
 \retval     the sector of a given address
 */
static int fmc_sector_get(uint32_t addr)
{

    for (size_t i = 0; i < SECTOR_COUNT - 1; i++)
    {
        if (addr >= sector_info[i].address && addr < sector_info[i + 1].address)
        {
            return i;
        }
    }
    if (addr >= sector_info[SECTOR_COUNT - 1].address)
    {
        return SECTOR_COUNT - 1;
    }
    return -1; /* 无效地址 */
}

int init()
{
    return RT_EOK;
}

 int fal_read(long offset, uint8_t *buf, size_t size)
{
    for (int i = 0; i < size; i++, buf++)
    {
        *buf = *(uint8_t*) (offset + i);
    }
    return size;
}

 int fal_write(long offset, const uint8_t *buf, size_t size)
{
    fmc_unlock();
    fmc_flag_clear(FMC_FLAG_END | FMC_FLAG_OPERR | FMC_FLAG_WPERR | FMC_FLAG_PGMERR | FMC_FLAG_PGSERR);
    for (int i = 0; i < size; i++)
    {
        fmc_byte_program(offset + i, *(buf + i));
    }
    fmc_lock();
    return size;
}

int erase(long offset, size_t size)
{

    fmc_unlock();
    fmc_flag_clear(FMC_FLAG_END | FMC_FLAG_OPERR | FMC_FLAG_WPERR | FMC_FLAG_PGMERR | FMC_FLAG_PGSERR);
    int cur_index = fmc_sector_get(offset);
    int next_index = fmc_sector_get(offset + size - 1);
    if (cur_index < 0 || next_index < 0)
    {
        fmc_lock();
        return RT_ERROR; /* 无效扇区 */
    }
    for (; cur_index <= next_index; cur_index++)
    {
        while (fmc_state_get() != FMC_READY)
        {
        };
        fmc_sector_erase(sector_info[cur_index].number);
    }
    fmc_lock();
    return size;
}

static int fal_flash_read_16k(long offset, rt_uint8_t *buf, size_t size);
static int fal_flash_read_64k(long offset, rt_uint8_t *buf, size_t size);
static int fal_flash_read_128k(long offset, rt_uint8_t *buf, size_t size);

static int fal_flash_write_16k(long offset, const rt_uint8_t *buf, size_t size);
static int fal_flash_write_64k(long offset, const rt_uint8_t *buf, size_t size);
static int fal_flash_write_128k(long offset, const rt_uint8_t *buf, size_t size);

static int fal_flash_erase_16k(long offset, size_t size);
static int fal_flash_erase_64k(long offset, size_t size);
static int fal_flash_erase_128k(long offset, size_t size);

const struct fal_flash_dev gd32_flash_16 = { "16", ADDR_FMC_SECTOR_0, 64 * 1024, 16 * 1024, { init, fal_flash_read_16k,
        fal_flash_write_16k, fal_flash_erase_16k }, 8 };
const struct fal_flash_dev gd32_flash_64 = { "64", ADDR_FMC_SECTOR_4, 64 * 1024, 64 * 1024, { init, fal_flash_read_64k,
        fal_flash_write_64k, fal_flash_erase_64k }, 8 };
const struct fal_flash_dev gd32_flash_128 = { "128", ADDR_FMC_SECTOR_5, 128 * 1024 * 7, 128 * 1024, { init,
        fal_flash_read_128k, fal_flash_write_128k, fal_flash_erase_128k }, 8 };

static int fal_flash_read_16k(long offset, rt_uint8_t *buf, size_t size)
{
    return fal_read(gd32_flash_16.addr + offset, buf, size);
}
static int fal_flash_read_64k(long offset, rt_uint8_t *buf, size_t size)
{
    return fal_read(gd32_flash_64.addr + offset, buf, size);
}
static int fal_flash_read_128k(long offset, rt_uint8_t *buf, size_t size)
{
    return fal_read(gd32_flash_128.addr + offset, buf, size);
}

static int fal_flash_write_16k(long offset, const rt_uint8_t *buf, size_t size)
{
    return fal_write(gd32_flash_16.addr + offset, buf, size);
}
static int fal_flash_write_64k(long offset, const rt_uint8_t *buf, size_t size)
{
    return fal_write(gd32_flash_64.addr + offset, buf, size);
}
static int fal_flash_write_128k(long offset, const rt_uint8_t *buf, size_t size)
{
    return fal_write(gd32_flash_128.addr + offset, buf, size);
}

static int fal_flash_erase_16k(long offset, size_t size)
{
    return erase(gd32_flash_16.addr + offset, size);
}
static int fal_flash_erase_64k(long offset, size_t size)
{
    return erase(gd32_flash_64.addr + offset, size);
}
static int fal_flash_erase_128k(long offset, size_t size)
{
    return erase(gd32_flash_128.addr + offset, size);
}

