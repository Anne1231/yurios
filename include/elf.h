#ifndef __ELF_H__
#define __ELF_H__

#include "types.h"

#define __ELF_HEADER_BYTES__ 16

/*
 *=======================================================================================
 *ELF解析に使う構造体
 *=======================================================================================
 */

struct Elf32_info {
	/*
	 *ELFの最初の16バイト
	 */
	u8_t e_ident[__ELF_HEADER_BYTES__];

	/*
	 *ファイルのタイプ
	 */
	u16_t e_type;

	/*
	 *マシンアーキテクチャ
	 */
	u16_t e_machine;

	/*
	 *ファイルのバージョン
	 */
	u32_t e_version;

	/*
	 *実行開始アドレス
	 */
	u32_t e_entry;

	/*
	 *プログラムヘッダテーブルまでのファイル先頭からのオフセット
	 */
	u32_t  e_phoff;

	/*
	 *セクションヘッダテーブルまでのファイル先頭からのオフセット
	 */
	u32_t  e_shoff;

	/*
	 *未使用
	 */
	u32_t e_flags;

	/*
	 *この構造体のサイズ（sizeof(struct elf_info)）
	 */
	u16_t e_ehsize;

	/*
	 *プログラムヘッダのサイズ
	 */
	u16_t e_phentsize;

	/*
	 *プログラムヘッダの個数
	 */
	u16_t e_phnum;

	/*
	 *セクションヘッダのサイズ
	 */
	u16_t e_shentsize;

	/*
	 *セクションヘッダの個数
	 */
	u16_t e_shnum;

	/*
	 *セクション名格納用のセクションのセクション番号
	 */
	u16_t e_shstrndx;
};

/*
 *=======================================================================================
 *ELFセクションヘッダ構造体
 *=======================================================================================
 */
struct Elf32_Shdr {
      u32_t sh_name;
	u32_t sh_type;
	u32_t sh_flags;
	u32_t sh_addr;
	u32_t sh_offset;
	u32_t sh_size;
	u32_t sh_link;
	u32_t sh_info;
	u32_t sh_addralign;
	u32_t sh_entsize;
};

/*
 *=======================================================================================
 *ELFプログラムヘッダ構造体
 *=======================================================================================
 */
struct Elf32_Phdr {
	u32_t p_type;
	u32_t p_offset;
	u32_t p_vaddr;
	u32_t p_paddr;
	u32_t p_filesz;
	u32_t p_memsz;
	u32_t p_flags;
	u32_t p_align;
};

#define __PF_X__ 0x01
#define __PF_W__ 0x02
#define __PF_R__ 0x04

/*
 *=======================================================================================
 *ELF解析関数のプロトタイプ宣言
 *=======================================================================================
 */
u8_t CheckELF(struct Elf32_info *elf);
u32_t GetELFEsp(struct Elf32_info *elf);
u32_t GetELFDataSize(struct Elf32_info *elf);
void CopyELFDataSe(void *DataSegment, struct Elf32_info *elf);
struct MEMMAN *GetAppMM(struct Process *proc, struct Elf32_Shdr **p_malloc_SHDR);


#endif
