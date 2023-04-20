/* --------------------------------------------------------------------- */
/* ファイル名	:	FileIO.h											 */
/* 機能概要		:														 */
/* 作成日		:   2021/10/21											 */
/* 最終更新日	:   2021/11/03											 */
/* 作成者		:	山田龍之介											 */
/* --------------------------------------------------------------------- */
#pragma once

/* --------------------------------------------------------------------- */
/* includeファイル														 */
/* --------------------------------------------------------------------- */
#include"System.h"

/* --------------------------------------------------------------------- */
/* 定数定義																 */
/* --------------------------------------------------------------------- */

//Pathの最大の長さ
#define PathLength 200

//bitの定義
#define Bit32 0x0020 
#define Bit24 0x0018
#define Bit8 0x0008
#define Bit1 0x0001

//

//戻り値
#define FAILE -1
#define SUCCESS 0

//デバッグ用
#define TEST

/* --------------------------------------------------------------------- */
/* クラス定義                                                            */
/* --------------------------------------------------------------------- */
class FileIO
{
public:
	FileIO( );
	 ~FileIO( );

	 FILE* orizinalPath;							/* 1枚目のPath				 */
	 FILE* secondPath;							/* 2枚目のPath				 */
	 FILE* thirdPath;							/* 3枚目のPath				 */
	 FILE* fourthPath;							/* 4枚目のPath				 */
	 FILE* outputPath;							/* 出力のPath				 */


	SINT read( SCHR* , FileData** );
	SINT write( SCHR*, FileData** );
private:
	FILE *pFP;
	struct stat stat_buff ;
	SINT iIdetify;
	SINT open( SCHR* ,SCHR*);
	SINT read(  FileData** );
	SINT write( FileData** );
	void close(  );
};




