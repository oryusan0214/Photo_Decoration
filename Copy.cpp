/* ------------------------------------------------------------------------- */
/* Copy.cpp																	 */
/* 複製処理																	 */
/* そもそも複製を作成して装飾する仕様なので、この関数では引数チェックのみ	 */
/* ------------------------------------------------------------------------- */
/* 番号	更新履歴								日付		   氏名			 */
/* ------------------------------------------------------------------------- */
/* 000000	新規作成							2021/10/29     筈尾　辰也	 */
/* 000001	リファクタリング					2021/11/22	   筈尾  辰也	 */
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
/* Include File																 */
/* ------------------------------------------------------------------------- */
#include "System.h"
#include "Copy.h"

/* ------------------------------------------------------------------------- */
/* 関数名	: Copy::exe														 */
/* 機能名	: 実行する														 */
/* 機能概要	: 複製処理を実行する											 */
/* 引数		: DecorateList*	: decorateInfo		: 装飾情報[IN] 				 */
/*			: FileData	 	: imageData			: 画像情報[I/O] 			 */
/* 戻り値	: SINT			:					: エラーチェック[OUT]		 */
/* 作成日	: 2021/10/29		筈尾  辰也		新規作成					 */
/* ------------------------------------------------------------------------- */
SINT Copy::exe( DecorateList* decorateInfo, FileData* imageData )
{

	/* 引数値チェック------------------------- */

	/* DM */
	if ( decorateInfo == NULL ) {
		printf( "decorateInfo Inter Check  Error In Copy::exe_decorateList\n" );
		return FAILE;
	}
	if ( imageData == NULL ) {
		printf( "decorateInfo Inter Check  Error In Copy::exe_imageData\n" );
		return FAILE;
	}
	/* 装飾種類 */
	if ( decorateInfo->decolateKind != COPY ) {
		printf( "decorateInfo Inter Check  Error In KIND\n" );
		return FAILE;
	}
	/* 装飾設定 */
	if ( decorateInfo->decolatesetup != EMPTY ) {
		printf( "decorateInfo Inter Check  Error In SETUP\n" );
		return FAILE;
	}
	/* 画像型式 */
	if ( imageData->pFileHData->sFile_Header_Name != MAGIC_NUMBER ) {
		printf( "imageData Inter Check Error In Type\n" );
		return FAILE;
	}
	/* 画像サイズ */
	if ( imageData->pInfoHData->uiWidth < IMAGE_SIZE_MIN || imageData->pInfoHData->uiHeight < IMAGE_SIZE_MIN ) {
		printf( "imageData Inter Check Error In IMAGE_SIZE\n" );
		return FAILE;
	}
	/* --------------------------------------- */

	/* 何も画像データをいじらないのでそのママ返す */

	return FAILE;
}
/* ------------------------------------------------------------------------- */
/*              Copyright HAL Collage of Technology & Design                 */
/* ------------------------------------------------------------------------- */
