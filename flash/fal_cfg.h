#ifndef __FAL_CFG_H
#define __FAL_CFG_H

#include "rtconfig.h"
#include "board.h"

extern const struct fal_flash_dev gd32_flash_16;
extern const struct fal_flash_dev gd32_flash_64;
extern const struct fal_flash_dev gd32_flash_128;

extern const struct fal_flash_dev gd32_flash_slow_16;
extern const struct fal_flash_dev gd32_flash_slow_64;
extern const struct fal_flash_dev gd32_flash_slow_128;
extern const struct fal_flash_dev gd32_flash_slow_256;

#define FAL_FLASH_DEV_TABLE \
{														\
	&gd32_flash_16, 					\
	&gd32_flash_64,						\
	&gd32_flash_128,						\
	&gd32_flash_slow_16,			\
	&gd32_flash_slow_64,			\
	&gd32_flash_slow_128,			\
	&gd32_flash_slow_256			\
}

#define FAL_PART_TABLE 						\
{																	\
	{FAL_PART_MAGIC_WORD,"bootloader1","16",0,64*1024,0},\
	{FAL_PART_MAGIC_WORD,"bootloader2","64",0,64*1024,0},\
	{FAL_PART_MAGIC_WORD,"bootloader3","128",0,128*1024,0},\
	{FAL_PART_MAGIC_WORD,"app","128",128*1024,2*128*1024,0},\
	{FAL_PART_MAGIC_WORD,"factory","128",128*1024 * 3,2*128*1024,0},\
	{FAL_PART_MAGIC_WORD,"download","128",128*1024 * 5,2*128*1024,0},\
	{FAL_PART_MAGIC_WORD,"s_16","slow_16",0,64*1024,0},\
	{FAL_PART_MAGIC_WORD,"s_64","slow_64",0,64*1024,0},\
	{FAL_PART_MAGIC_WORD,"s_128","slow_128",0,128*1024*7,0},\
	{FAL_PART_MAGIC_WORD,"s_256","slow_256",0,256*1024*4,0}\
}
#endif
