#pragma once
/* ------------------------------------------------------------------------- */
/* System.h																	 */
/* システムヘッダ															 */
/* ------------------------------------------------------------------------- */
/* 番号	更新履歴								日付		   氏名			 */
/* ------------------------------------------------------------------------- */
/* 000000	新規作成							2021/10/15     筈尾　辰也	 */
/* 000001	リファクタリング					2021/11/22	   筈尾  辰也	 */
/* ------------------------------------------------------------------------- */
/* Secure宣言																 */
/* ------------------------------------------------------------------------- */
#define  _CRT_NO_SECURE_WARNINGS
#define  _CRT_SECURE_NO_DEPRECATE

/* ------------------------------------------------------------------------- */
/* Include																	 */
/* ------------------------------------------------------------------------- */
#include <stdio.h>								/* 標準ＩＯ					 */
#include <stdlib.h>								/* 標準ライブラリ			 */
#include <string.h>								/* 文字列制御				 */
#include <Windows.h>							/* Windows関連				 */
#include <time.h>								/* タイマーやクロック関数	 */
#include <sys/stat.h>							/* ファイルオープン			 */
#include <stdarg.h>								/* 可変個因数で使う			 */
#include <direct.h>								/* File名比較で使う			 */


/* ------------------------------------------------------------------------- */
/* 共通typedef宣言															 */
/* ------------------------------------------------------------------------- */
typedef char			SCHR;					/*	char型					 */
typedef unsigned char	UCHR;					/*	unsigned char型			 */
typedef short			SSHT;					/*	short型					 */
typedef unsigned short	USHT;					/*	unsigned short型		 */
typedef long			SLNG;					/*	long型					 */
typedef unsigned long	ULNG;					/*	unsigned long型			 */
typedef int				SINT;					/*	int型					 */
typedef unsigned int	UINT;					/*	unsigned int型			 */
typedef	float			FLOT;					/*	float型					 */
typedef	double			DBLE;					/*	double型				 */

/* ------------------------------------------------------------------------- */
/* 共通define宣言															 */
/* ------------------------------------------------------------------------- */
#define FAILE						-1				/* 異常時の戻り値		 */
#define SUCCESS						0				/* 正常値の戻り値		 */
#define STR_OK						0				/* srtcmpの正常時の戻り値*/
#define SCANF_ERROR					0				/* scanfのエラーチェック */
#define BIT1						0x0001			/* Bit定義				 */
#define BIT8						0x0008			/* Bit定義				 */
#define BIT24						0x0018			/* Bit定義				 */
#define BIT32						0x0020			/* Bit定義				 */
#define PATHLENGTH					200				/* Pathの最大長			 */
#define MAGIC_NUMBER				0x4D42			/* BMの文字コード		 */
#define ONCE						1				/* 関数の引数で1を使う時 */
#define PNG							10				/* pngの判定地			 */
#define JPEG						20				/* jpegの判定地			 */

#define BYTE1						1				/* データの読込サイズ	 */
#define BYTE2						2				/* データの読込サイズ	 */
#define BYTE3						3				/* データの読込サイズ	 */
#define BYTE4						4				/* データの読込サイズ	 */
#define HEADER_SIZE					14				/* HeaderFileのサイズ	 */
#define INFO_SIZE					40				/* InfoFileの大きさ		 */

#define INTI						0				/* 初期値				 */
#define IMAGE_SIZE_MIN				1				/* 画像データの最低の長さ*/


#define ROTATE						1				/* 回転のID				 */
#define IMAGEINVERT					2				/* 画像反転のID			 */
#define COLORINVERT					3				/* 色反転のID			 */
#define SEPIA						4				/* セピアのID			 */
#define MOSAIC						5				/* モザイクのID			 */
#define MAGNIFICATION				6				/* 拡大縮小ID			 */
#define COLORCONVERT				7				/* 色変換のID			 */
#define COPY						8				/* 複写のID				 */
#define TWO_IN_ONE_VER				9				/* 縦集約のID			 */
#define TWO_IN_ONE_HOR				10				/* 横集約のID			 */
#define FOUR_IN_ONE					11				/* 4 in 1のID			 */
#define OVERLAY						12				/* オーバーレイのID		 */
#define RESTART						13				/* 再入力のID			 */
#define FIN							14				/* 終了のID				 */

#define EMPTY						0				/* 設定値 0				 */
#define ROTATE_MIN					1				/* 画像回転の設定値の最低*/
#define ROTATE_MAX					4				/* 画像回転の設定値の最大*/
#define IMAGE_INVERT_MIN			1				/* 画像反転の設定値の最低*/
#define IMAGE_INVERT_MAX			2				/* 画像反転の設定値の最大*/
#define SEPIA_MIN					1				/* セピア化の設定値の最低*/
#define SEPIA_MAX					3				/* セピア化の設定値の最大*/
#define MOSAIC_MIN					1				/* モザイクの設定値の最低*/
#define MAGN_MIN					1				/* 倍率変更の設定値の最低*/
#define MAGN_MAX					10000			/* 倍率変更の設定値の最大*/
#define COLOR_CONVERT_MIN			1				/* 色変換の設定値の最低	 */
#define COLOR_CONVERT_MAX			3				/* 色変換の設定値の最大	 */
#define INTENSIVE_T_MIN				12				/* 2 in 1の設定値の最小	 */
#define INTENSIVE_T_MAX				21				/* 2 in 1の設定値の最大	 */
#define INTENSIVE_F_MIN				1234			/* 4 in 1の設定値の最小	 */
#define INTENSIVE_F_MAX				4321			/* 4 in 1の設定値の最大	 */
#define OVERLAY_MIN					0				/* オバレイの設定値の最小*/
#define OVERLAY_MAX					99				/* オバレイの設定値の最大*/

/* ------------------------------------------------------------------------- */
/* 共通構造体宣言															 */
/* ------------------------------------------------------------------------- */

/* ファイルヘッダ */
#pragma pack( 2 )
typedef struct FileHeader {
	SSHT sFile_Header_Name;						/* 型式						 */
	UINT uiFaile_Saize;							/* FileSize(当てにできない)	 */
	SSHT sReserved1;							/* 予約領域1				 */
	SSHT sReserved2;							/* 予約領域2				 */
	UINT uiHeader_Size_Offset;					/* 色データまでのOffset		 */
}FileHeader;

/* 情報ヘッダ */
#pragma pack(  )
typedef struct InformationHeader {
	UINT uiInfo_HeaderSize;						/* 情報ヘッダのサイズ		 */
	UINT uiWidth;								/* 画像の横幅				 */
	UINT uiHeight;								/* 画像の縦幅				 */
	SSHT sPlain;								/* プレーン数				 */
	SSHT sColor_Bit;							/* ビットマップの色数		 */
	UINT uiCompre;								/* 圧縮情報					 */
	UINT uiImage_Size;							/* 画像の全体サイズ			 */
	UINT uiResolution_Wid;						/* 画像の縦解像度			 */
	UINT uiResolution_Hei;						/* 画像の横解像度			 */
	UINT uiColor_Index;							/* パレット数				 */
	UINT uiColor_Key_Index;						/* 重要なパレット数			 */
}InformationHeader;

/* ファイルデータ */
typedef struct FileData {
	FileHeader*			pFileHData;				/* ファイルヘッダ			 */
	InformationHeader*	pInfoHData;				/* 情報ヘッダ				 */
	UCHR*				pImageData;				/* 色データ					 */
}FileData;

/* 装飾情報の配列 */
struct DecorateList {
	DecorateList*		next;					/* 次のポインタ				 */
	SINT				decolateKind;			/* 装飾種類					 */
	SINT				decolatesetup;			/* 装飾設定					 */
};

/* 1ピクセル当たりの色情報 */
struct rgb {
	UCHR r;										/* 赤						 */
	UCHR g;										/* 青						 */
	UCHR b;										/* 緑						 */
	UCHR a;										/* α						 */
};

/* ------------------------------------------------------------------------- */
/*              Copyright HAL Collage of Technology & Design                 */
/* ------------------------------------------------------------------------- */
