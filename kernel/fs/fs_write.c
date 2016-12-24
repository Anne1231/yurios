#include "../../include/kernel.h"
#include "../../include/yrfs.h"
#include "../../include/ata.h"

/*
 *=======================================================================================
 *yrws_write関数
 *補助記憶装置に書き込むそこそこ高レイヤーな関数
 *=======================================================================================
 */
u32_t yrfs_write(u32_t fd, char *buffer, u32_t bytes){

	struct i_node *inode = (struct i_node *)memory_alloc(memman, sizeof(struct i_node));
	iread(inode, fd);
	
	write_ata_sector(&ATA_DEVICE0, inode->seek_address.sector, buffer, byte2sectors(bytes));
	mark_used_sign(inode->begin_address.sector, inode->begin_address.sector+byte2sectors(bytes));

	memory_free(memman, (u32_t)inode, sizeof(struct i_node));

	return byte2sectors(bytes);
}
