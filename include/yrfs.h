#ifndef __YRFS_H__
#define __YRFS_H__

#include "types.h"

/*
 *=======================================================================================
 *openシステムコールのフラグ
 *=======================================================================================
 */
#define __O_RDONLY__ 0x01
#define __O_WRONLY__ 0x02
#define __O_RDWR__   0x04
#define __O_CREAT__  0x08

/*
 *=======================================================================================
 *seekシステムコールのフラグ
 *=======================================================================================
 */
#define __SEEK_SET__ 0x00
#define __SEEK_CUR__ 0x01
#define __SEEK_END__ 0x02

#define __WRITABLE_INODE_SIZE__ 116
#define __WRITABLE_INODE_SECTORS__ 1

#define __YRFS_BLOCK_SIZE__	512

#define __UNUSED_BLOCK__ 0x00
#define __USED_BLOCK__   0x01

#define __INODE_ZONE__        0
#define __FILE_OBJECT_ZONE__ 10001
#define __INODE_LIMIT__ 10000

#define __BLOCKS_LIMIT__ 2097152


//ファイルの種類とか
#define __NORMAL_FILE__      0x01
#define __DIRECTORY_FILE__   0x02
#define __LINK_FILE__        0x04
#define __BLOCK_DEVICE__     0x08
#define __CHAR_DEVICE__      0x10
#define __PIPE_FILE__
#define __SOCKET_FILE__

/*
 *=======================================================================================
 *ブロックの情報を保持しておく構造体
 *=======================================================================================
 */
struct block_info {
	/*
	 *このブロックは空か？
	 */
	u32_t exist : 1;
};

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
	//inodeID
	u32_t id;
	//ファイルの開始アドレス
	struct fs_address begin_address;
	//ファイルの終了アドレス
	struct fs_address end_address;
	//シーク中のアドレス
	struct fs_address seek_address;
	//ファイルのサイズ
	u32_t size;
	//このファイルのパーミッション
	u32_t permission;
	//このファイルの作成日時
	u32_t cr_time;
	//このファイルに立っているフラグ
	u32_t flags;
	//このファイルの作成者
	char cr_user[64];
	//ファイル名
	char file_name[256];
};

/*
 *=======================================================================================
 *書き込み可能な形式のデータを保持する構造体
 *=======================================================================================
 */
struct writable_data {
	u32_t size;
	u32_t *data;
};



//inodeを作る関数
struct i_node icreat(char *file_name);

/*
 *=======================================================================================
 *new_wrdata関数
 *新しくwritable_data構造体を確保する関数
 *=======================================================================================
 */
void new_wrdata(struct writable_data *data, u32_t size);

/*
 *=======================================================================================
 *delete_wrdata関数
 *writable_data構造体を開放する関数
 *=======================================================================================
 */
void delete_wrdata(struct writable_data *data);

/*
 *=======================================================================================
 *iwrite関数
 *inode情報を補助記憶装置に書き込む
 *=======================================================================================
 */
u32_t iwrite(struct i_node *inode);
void iread(struct i_node *inode, u32_t index);

/*
 *=======================================================================================
 *iupdate関数
 *inodeを更新する関数
 *=======================================================================================
 */
void iupdate(struct i_node *inode);

/*
 *=======================================================================================
 *u32to4char関数
 *unsigned intの中に入った4つの文字列を取り出す関数
 *=======================================================================================
 */
void u32to4char(u32_t data, char *buffer);

/*
 *=======================================================================================
 *char4tou32関数
 *unsigned intの中に入った4つの文字列を取り出す関数
 *=======================================================================================
 */
void char4tou32(char *data, u32_t *u32);

/*
 *=======================================================================================
 *ffind関数
 *ファイルを検索する関数
 *=======================================================================================
 */
i32_t ffind(char *pathname);

/*
 *=======================================================================================
 *byte2sectors関数
 *バイト数から必要なセクタ数を計算する関数
 *=======================================================================================
 */
u32_t byte2sectors(u32_t bytes);

void filesystem_zeroclear();
void file_list(char *option);

void uchar4tou32(u8_t *data, u32_t *u32);

u32_t mark_used_sign(u32_t start, u32_t end);

/*
 *=======================================================================================
 *高レイヤーWR関数
 *=======================================================================================
 */
u32_t yrfs_write(u32_t fd, char *buffer, u32_t bytes);

/*
 *=======================================================================================
 *ファイルを削除する関数
 *=======================================================================================
 */
u8_t RemoveFile(char *file_name);

/*
 *=======================================================================================
 *extern関係
 *=======================================================================================
 */
/*
 *ブロックの情報を保持しておく
 */
extern struct block_info *blocks_info;

#endif
