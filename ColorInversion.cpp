/* ------------------------------------------------------------------------- */
/* ColorInversion.cpp														 */
/* 色反転																	 */
/* 画像の輝度を反転させるプログラム											 */
/* ------------------------------------------------------------------------- */
/* 番号	更新履歴								日付		   氏名			 */
/* ------------------------------------------------------------------------- */
/* 000000	新規作成							2021/10/23     筈尾　辰也	 */
/* 000001	リファクタリング					2021/12/03	   筈尾  辰也	 */
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
/* Include File																 */
/* ------------------------------------------------------------------------- */
#include "ColorInversion.h"

/* ------------------------------------------------------------------------- */
/* 関数名	: ColorInversion::exe											 */
/* 機能名	: 実行する														 */
/* 機能概要	: 色反転を実行する												 */
/* 引数		: DecorateList*	: decorateInfo		: 装飾情報[IN]	 			 */
/*			: FileData* 	: imageData			: 画像情報[I/O] 			 */
/* 戻り値	: SINT			:					: エラーチェック[OUT]		 */
/* 作成日	: 2021/10/23		筈尾  辰也		新規作成					 */
/* ------------------------------------------------------------------------- */
SINT ColorInversion::exe( DecorateList* decorateInfo, FileData* imageData )
{


	/* 引数値チェック------------------------- */

	/* DM */
	if ( decorateInfo == NULL ) {
		printf( "decorateInfo Inter Check  Error In ColorInvert::exe_decorateList\n" );
		return FAILE;
	}
	if ( imageData == NULL ) {
		printf( "decorateInfo Inter Check  Error In ColorInvert::exe_imageData\n" );
		return FAILE;
	}
	/* 装飾種類 */
	if ( decorateInfo->decolateKind != COLORINVERT ) {
		printf( "decorateInfo Inter Check  Error In ColorInversion::exe_Kind\n" );
		return FAILE;
	}
	/* 装飾設定 */
	if ( ( decorateInfo->decolatesetup ) != INTI ) {
		printf( "decorateInfo Inter Check  Error In ColorInversion::exe_setup\n" );
		return FAILE;
	}
	/* 画像型式 */
	if ( imageData->pFileHData->sFile_Header_Name != MAGIC_NUMBER ) {
		printf( "imageData Inter Check Error In ColorInversion::exe_Type\n" );
		return FAILE;
	}
	/* 画像サイズ */
	if ( ( imageData->pInfoHData->uiWidth ) <= INTI || ( imageData->pInfoHData->uiHeight ) <= INTI ) {
		printf( "imageData Inter Check Error In ColorInversion::exe_Size\n" );
		return FAILE;
	}
	/* --------------------------------------- */

	/* 初期化 & 初期値代入-------------------- */
	SINT icountCIv	= INTI;						/* カウント役				 */
	SINT idataSize	= INTI;						/* ループ回数取得			 */

	/* 画像の縦横 * 1ピクセルあたりのbit = ループ数 */
	idataSize = ( imageData->pInfoHData->uiWidth ) * ( imageData->pInfoHData->uiHeight ) * BYTE4;
	/* --------------------------------------- */

	/* 色反転処理----------------------------- */

	/* 画像データのbit数分ループ */
	for ( icountCIv = INTI; icountCIv < idataSize; icountCIv ++ ) {

		/* αチャンネルは処理をせずに飛ばす */
		if ( ( icountCIv + BYTE1 ) % BYTE4 == INTI ) {
			continue;
		}
		/* rgbチャンネルは輝度反転 */
		*( imageData->pImageData + icountCIv ) = 
			COLORMAX - *( imageData->pImageData + icountCIv );
	}
	/* --------------------------------------- */

	return SUCCESS;
}
/* ------------------------------------------------------------------------- */
/*              Copyright HAL Collage of Technology & Design                 */
/* ------------------------------------------------------------------------- */
