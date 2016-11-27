#ifndef __YRFS_H__
#define __YRFS_H__

#include "types.h"

/*
 *=======================================================================================
 *ファイルがファイルシステムのどこに位置するかを保持する構造体
 *=======================================================================================
 */
struct fs_address {
	u32_t sector;
	u32_t offset;
};

/*
 *=======================================================================================
 *inode構造体
 *=======================================================================================
 */
struct i_node {
	struct fs_address address;
	u32_t size;
	char file_name[256];
};

#endif
