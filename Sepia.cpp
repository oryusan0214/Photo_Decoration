/* ------------------------------------------------------------------------- */
/* Sepia.cpp																 */
/* セピア処理																 */
/* セピア化を実行															 */
/* ------------------------------------------------------------------------- */
/* 番号	更新履歴								日付		   氏名			 */
/* ------------------------------------------------------------------------- */
/* 000000	新規作成							2021/10/15     筈尾　辰也	 */
/* 000001	リファクタリング					2021/11/25	   筈尾  辰也	 */
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
/* Include File																 */
/* ------------------------------------------------------------------------- */
#include "System.h"
#include "Sepia.h"


/* ------------------------------------------------------------------------- */
/* 関数名	: Sepia::exe													 */
/* 機能名	: セピアする													 */
/* 機能概要	: セピアを実行する												 */
/* 引数		: DecorateList*	: decorateInfo		: 装飾情報[OUT] 			 */
/*			: FileData*		: imageData			: 画像情報[OUT] 			 */
/* 戻り値	: SINT			:					: エラーチェック[IN]		 */
/* 作成日	: 2021/10/15		筈尾  辰也		新規作成					 */
/* ------------------------------------------------------------------------- */
SINT Sepia::exe( DecorateList* decorateInfo, FileData* imageData )
{
	/* 変数宣言 */
	SINT ierrorCheck = INTI;					/* エラーチェック			 */

	/* 入力値チェック------------------------- */

	/* DM */
	if ( decorateInfo == NULL ) {
		printf( "decorateInfo Inter Check  Error In Sepia::exe_decorateList\n" );
		return FAILE;
	}
	if ( imageData == NULL ) {
		printf( "decorateInfo Inter Check  Error In Sepia::exe_imageData\n" );
		return FAILE;
	}
	/* 装飾種類 */
	if ( decorateInfo->decolateKind != SEPIA ) {
		printf( "decorateInfo Inter Check  Error In Sepia::exe_Kind\n" );
		return FAILE;
	}
	/* 装飾設定 */
	if ( decorateInfo->decolatesetup < SEPIA_MIN || SEPIA_MAX < decorateInfo->decolatesetup ) {
		printf( "decorateInfo Inter Check  Error In Sepia::exe_Setup\n" );
		return FAILE;
	}
	/* 型式 */
	if ( imageData->pFileHData->sFile_Header_Name != MAGIC_NUMBER ) {
		printf( "imageData Inter Check Error In Sepia::exe_Type\n" );
		return FAILE;
	}
	/* おおきさ */
	if ( imageData->pInfoHData->uiHeight <= INTI || imageData->pInfoHData->uiWidth <= INTI ) {
		printf( "imageData Inter Check Error In Sepia::exe_Size\n" );
		return FAILE;
	}
	/* --------------------------------------- */
	/* 設定ごとに飛ばす */
	if ( decorateInfo->decolatesetup == DARK ) {
		ierrorCheck = dark( imageData );
	}
	else if ( decorateInfo->decolatesetup == NORMAL ) {
		ierrorCheck = normal( imageData );
	}
	else if ( decorateInfo->decolatesetup == DELUTE ) {
		ierrorCheck = delute( imageData );
	}
	if ( ierrorCheck == FAILE ) {
		printf( "セピア化を異常終了しました\n" );
		return FAILE;
	}
	return SUCCESS;
}
/* ------------------------------------------------------------------------- */
/* 関数名	: Sepia::dark													 */
/* 機能名	: セピアする													 */
/* 機能概要	: セピアを実行する												 */
/* 引数		: FileData*	: imageData			: 画像情報[OUT] 				 */
/* 戻り値	: SINT		:					: エラーチェック[IN]			 */
/* 作成日	: 2021/10/15		筈尾  辰也		新規作成					 */
/* ------------------------------------------------------------------------- */
SINT Sepia::dark( FileData* imageData )
{

	if ( imageData == NULL ) {
		printf( "decorateInfo Inter Check  Error In Sepia::dark_imageData\n" );
		return FAILE;
	}

	/* 変数宣言 */
	UCHR* psepia	= NULL;						/* 装飾後の画像データ		 */
	SINT ishine		= INTI;						/* 輝度合計					 */
	SINT iSP_Ver	= INTI;						/* カウント役				 */
	SINT iSP_Hor	= INTI;						/* カウント役				 */
	SINT imageSize	= INTI;						/* 画像サイズ				 */
	SINT ireference = INTI;						/* 現在参照しているバイト	 */
	UCHR iblue		= INTI;						/* 青						 */
	UCHR igreen		= INTI;						/* 緑						 */
	UCHR ired		= INTI;						/* 赤						 */

	/* 画像サイズ取得 */
	imageSize = imageData->pInfoHData->uiHeight * imageData->pInfoHData->uiWidth * BYTE4;

	/* get DM */
	psepia = ( UCHR* )calloc( imageSize, sizeof( UCHR ) );

	/* DM check */
	if ( psepia == NULL ) {
		printf( "get error\n" );
		return FAILE;
	}
	/* セピア化------------------------------- */
	for ( iSP_Ver = INTI; iSP_Ver < imageData->pInfoHData->uiHeight; iSP_Ver ++ ) {
		for ( iSP_Hor = INTI; iSP_Hor < imageData->pInfoHData->uiWidth ; iSP_Hor ++ ) {

			/* 参照値取得 */
			ireference = iSP_Ver * imageData->pInfoHData->uiWidth * BYTE4 + iSP_Hor * BYTE4;

			/* 輝度合計取得 */
			ishine = *( imageData->pImageData + ireference ) +
					 *( imageData->pImageData + ireference + BYTE1 ) +
					 *( imageData->pImageData + ireference + BYTE2 );

			/* セピア化 */
			iblue	= ishine * MAG_DA_B;
			igreen	= ishine * MAG_DA_G;
			ired	= ishine * MAG_DA_R;

			/* データ格納 */
			*( psepia + ireference )			= iblue;
			*( psepia + ireference + BYTE1 )	= igreen;
			*( psepia + ireference + BYTE2 )	= ired;
			*( psepia + ireference + BYTE3 )	= *( imageData->pImageData + ireference + BYTE3 );
		}
	}
	/* --------------------------------------- */
	/* データ更新 */
	imageData->pImageData = psepia;

	return SUCCESS;
}

/* ------------------------------------------------------------------------- */
/* 関数名	: Sepia::normal													 */
/* 機能名	: セピアする													 */
/* 機能概要	: セピアを実行する												 */
/* 引数		: FileData*	: imageData			: 画像情報[OUT] 				 */
/* 戻り値	: SINT		:					: エラーチェック[IN]			 */
/* 作成日	: 2021/10/15		筈尾  辰也		新規作成					 */
/* ------------------------------------------------------------------------- */
SINT Sepia::normal( FileData* imageData )
{
	
	if ( imageData == NULL ) {
		printf( "decorateInfo Inter Check  Error In Sepia::normal_imageData\n" );
		return FAILE;
	}

	/* 変数宣言 */
	UCHR* psepia	= NULL;						/* 装飾後の画像データ		 */
	SINT ishine		= INTI;						/* 輝度合計					 */
	SINT iSP_Ver	= INTI;						/* カウント役				 */
	SINT iSP_Hor	= INTI;						/* カウント役				 */
	SINT imageSize	= INTI;						/* 画像サイズ				 */
	SINT ireference = INTI;						/* 現在参照しているピクセル	 */
	UCHR iblue		= INTI;						/* 青						 */
	UCHR igreen		= INTI;						/* 緑						 */
	UCHR ired		= INTI;						/* 赤						 */

	/* 画像サイズ取得 */
	imageSize = imageData->pInfoHData->uiHeight * imageData->pInfoHData->uiWidth * BYTE4;

	/* get DM */
	psepia = ( UCHR* )calloc( imageSize, sizeof( UCHR ) );

	/* DM check */
	if ( psepia == NULL ) {
		printf( "get error\n" );
		return FAILE;
	}
	/* セピア化------------------------------- */
	for ( iSP_Ver = INTI; iSP_Ver < imageData->pInfoHData->uiHeight; iSP_Ver ++ ) {
		for ( iSP_Hor = INTI; iSP_Hor < imageData->pInfoHData->uiWidth ; iSP_Hor ++ ) {

			/* 参照値取得 */
			ireference = ( iSP_Ver * imageData->pInfoHData->uiWidth + iSP_Hor ) * BYTE4;

			/* 輝度合計取得 */
			ishine = *( imageData->pImageData + ireference ) +
					 *( imageData->pImageData + ireference + BYTE1 ) +
					 *( imageData->pImageData + ireference + BYTE2 );

			/* セピア化 */
			iblue	= ishine * MAG_NO_B;
			igreen	= ishine * MAG_NO_G;
			ired	= ishine * MAG_NO_R;

			/* データ格納 */
			*( psepia + ireference )			= iblue;
			*( psepia + ireference + BYTE1 )	= igreen;
			*( psepia + ireference + BYTE2 )	= ired;
			*( psepia + ireference + BYTE3 )	= *( imageData->pImageData + ireference + BYTE3 );
		}
	}
	/* --------------------------------------- */
	/* データ更新 */
	imageData->pImageData = psepia;

	return SUCCESS;
}

/* ------------------------------------------------------------------------- */
/* 関数名	: Sepia::delute													 */
/* 機能名	: セピアする													 */
/* 機能概要	: セピアを実行する												 */
/* 引数		: FileData*	: imageData			: 画像情報[OUT] 				 */
/* 戻り値	: SINT		:					: エラーチェック[IN]			 */
/* 作成日	: 2021/10/15		筈尾  辰也		新規作成					 */
/* ------------------------------------------------------------------------- */

SINT Sepia::delute(FileData* imageData)
{

	if ( imageData == NULL ) {
		printf( "decorateInfo Inter Check  Error In Sepia::delute_imageData\n" );
		return FAILE;
	}
	
	/* 変数宣言 */
	UCHR* psepia	= NULL;						/* 装飾後の画像データ		 */
	SINT ishine		= INTI;						/* 輝度合計					 */
	SINT iSP_Ver	= INTI;						/* カウント役				 */
	SINT iSP_Hor	= INTI;						/* カウント役				 */
	SINT imageSize	= INTI;						/* 画像サイズ				 */
	SINT ireference = INTI;						/* 現在参照しているピクセル	 */
	UCHR iblue		= INTI;						/* 青						 */
	UCHR igreen		= INTI;						/* 緑						 */
	UCHR ired		= INTI;						/* 赤						 */

	/* 画像サイズ取得 */
	imageSize = imageData->pInfoHData->uiHeight * imageData->pInfoHData->uiWidth * BYTE4;

	/* get DM */
	psepia = ( UCHR* )calloc( imageSize, sizeof( UCHR ) );

	/* DM check */
	if ( psepia == NULL ) {
		printf( "get error\n" );
		return FAILE;
	}
	/* セピア化------------------------------- */
	for ( iSP_Ver = INTI; iSP_Ver < imageData->pInfoHData->uiHeight; iSP_Ver ++ ) {
		for ( iSP_Hor = INTI; iSP_Hor < imageData->pInfoHData->uiWidth ; iSP_Hor ++ ) {

			/* 参照値取得 */
			ireference = iSP_Ver * imageData->pInfoHData->uiWidth * BYTE4 + iSP_Hor * BYTE4;

			/* 輝度合計取得 */
			ishine = *( imageData->pImageData + ireference ) +
					 *( imageData->pImageData + ireference + BYTE1 ) +
					 *( imageData->pImageData + ireference + BYTE2 );

			/* セピア化 */
			iblue	= ishine * MAG_DE_B;
			igreen	= ishine * MAG_DE_G;
			ired	= ishine * MAG_DE_R;

			/* データ格納 */
			*( psepia + ireference )			= iblue;
			*( psepia + ireference + BYTE1 )	= igreen;
			*( psepia + ireference + BYTE2 )	= ired;
			*( psepia + ireference + BYTE3 )	= *( imageData->pImageData + ireference + BYTE3 );
		}
	}
	/* --------------------------------------- */
	/* データ更新 */
	imageData->pImageData = psepia;

	return SUCCESS;
}

/* ------------------------------------------------------------------------- */
/*              Copyright HAL Collage of Technology & Design                 */
/* ------------------------------------------------------------------------- */
