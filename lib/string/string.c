#include "../../include/types.h"
#include "../../include/kernel.h"
#include "../../include/util_macro.h"

/*
 *=======================================================================================
 *strcmp関数
 *２つの文字列を比較する関数
 *=======================================================================================
 */
int strcmp(const char *s, const char *t){
	int i;
	for(i = 0;s[i] != '\0';i++){
		if(s[i] != t[i]){
			return 0;
		}
	}
	for(i = 0;t[i] != '\0';i++){
		if(s[i] != t[i]){
			return 0;
		}
	}
	return 1;
}

/*
 *=======================================================================================
 *strlen関数
 *文字列長さを計算する関数
 *=======================================================================================
 */
int strlen(const char *str){
	u32_t count = 0;
      while(*str){
		str++;
		count++;
	}
	return count;
}

char *string_getNext(char *str, char *dst){
	int i;

	if(!*str)
		return NULL;

	for(i = 0;str[i] != ' ' && str[i] != '\0';i++){
		dst[i] = str[i];
	}
	dst[i] = '\0';

	return dst;
}

void cut_string(char *str, char *dst, int start_point){
	int i;
	for(i = 0;i < 1024 && str[i] != '\0';i++){
		dst[i] = str[i+start_point];
	}
	dst[i] = 0;
	return;
}

/*
 *=======================================================================================
 *strcpy関数
 *文字列をコピーする関数
 *=======================================================================================
 */
char *strcpy(char *dst, const char *src){
	while(*src){
		*dst = *src;
		dst++;
		src++;
	}
	*dst = '\0';
	return dst;
}

/*
 *=======================================================================================
 *strcat関数
 *文字列を連結する関数
 *=======================================================================================
 */
char *strcat(char *s1, const char *s2) {
	u32_t i = 0;

	while(*s1 != '\0')
		s1++;

	while(s2[i] != '\0'){
		s1[i] = s2[i];
		i++;
	}

	s1[i] = '\0';

	return s1;
}

/*
 *=======================================================================================
 *memcpy関数
 *指定しただけ、メモリの内容をコピーする関数
 *引数
 *void *s1
 *コピー
 *const void *s2
 *コピー先
 *size_t size
 *コピーするサイズ
 *=======================================================================================
 */
void *memcpy(void *s1, const void *s2, size_t size){
	char *ss1 = s1;
	const char *ss2 = s2;

	if(size != 0){
		register const char *t = ss2 + size;
		do{
			*ss1++ = *ss2++;
		}while (ss2 != t);
	}
	return s1;
}

/*
 *=======================================================================================
 *RemoveHeadSpaces関数
 *文字列の最初のスペースを削除する関数
 *=======================================================================================
 */
char *RemoveHeadSpaces(char *str){
	u8_t count = 0, i, length = strlen(str);
	while(str[count] == ' '){
		count++;
	}

	for(i = 0;i < length; i++){
		str[i] = str[i + count];
	}

	return str;
}

/*
 *=======================================================================================
 *SearchStringFirst関数
 *文字列中に指定したアルファベットが初めて出現する先頭からの文字数を返す関数
 *引数
 *char *str
 *文字列
 *char alphabet
 *検索するアルファベット
 *=======================================================================================
 */
i32_t SearchStringFirst(char *str, char alphabet){
	int i = 0;
	do{
		if(str[i] == alphabet)
			return i+1;
		i++;
	}while(str[i]);

	return -1;
}

/*
 *=======================================================================================
 *SearchStringTail関数
 *文字列中に指定したアルファベットが初めて出現する後方からの文字数を返す関数
 *引数
 *char *str
 *文字列
 *char alphabet
 *検索するアルファベット
 *=======================================================================================
 */
i32_t SearchStringTail(char *str, char alphabet){
	int i = 0;
	do{
		if(str[i] == alphabet)
			return i+1;
		i++;
	}while(str[i]);

	return -1;
}

/*
 *=======================================================================================
 *GetStringTail関数
 *文字列の一番うしろのアルファベットを返す関数
 *引数
 *char *str
 *=======================================================================================
 */
char GetStringTail(char *str){
	while(str[1])
		str++;
	return *str;
}

/*
 *=======================================================================================
 *Ystring_replace関数
 *文字列中の指定した文字を代わりの文字に入れ替える関数
 *引数
 *char *str
 *文字列
 *char replace
 *入れ替えさせる文字
 *char alternative
 *入れ替える文字列
 *=======================================================================================
 */
int ystring_replace_char(char *str, char replace, char alternative){
	if(!*str)
		return 0;

	do{
		if(*str == replace)
			*str = alternative;
		str++;
	}while(*str);

	return 1;
}

/*
 *=======================================================================================
 *ystring_insert関数
 *文字列中に文字列を挿入する関数
 *引数
 *char **str_pointer
 *挿入される文字列へのポインタ
 *const char *insert_str
 *挿入する文字列
 *挿入するインデックス
 *u32_t index
 *=======================================================================================
 */
i8_t ystring_insert(char **str_pointer, const char *insert_str, u32_t index){
      //変数宣言
	u32_t i, j, length, insert_length = strlen(insert_str);
	char *p, *before_str = *str_pointer;

      //新しくメモリを確保
	p = (char *)memory_alloc(memman, (length = strlen(*str_pointer) + insert_length) + 1);

      if(IS_NULLPO(p)) return FAILURE;

      /*
       *コピー作業
       */
	for(i = 0;i < index;i++)
		p[i] = before_str[i];

      for(j = 0;j < insert_length;++j)
            p[i + j] = insert_str[j];

	for(; i < length;++i)
            p[i + j] = before_str[i];

      //もともとのメモリを開放
      memory_free(memman ,(u32_t)before_str, length - insert_length);

      //挿入済みの文字列へのポインタを代入
      *str_pointer = p;

	return SUCCESS;

}
