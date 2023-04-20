/* ------------------------------------------------------------------------- */
/* ImageInvert.cpp															 */
/* 画像反転処理																 */
/* 画像を反転する処理														 */
/* ------------------------------------------------------------------------- */
/* 番号	更新履歴								日付		   氏名			 */
/* ------------------------------------------------------------------------- */
/* 000000	新規作成							2021/10/27     筈尾　辰也	 */
/* 000001	リファクタリング					2021/11/27	   筈尾  辰也	 */
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
/* Include File																 */
/* ------------------------------------------------------------------------- */
#include "System.h"
#include "ImageInvert.h"


/* ------------------------------------------------------------------------- */
/* 関数名	: ImageImvert::exe												 */
/* 機能名	: 実行する														 */
/* 機能概要	: 画像反転処理を実行する										 */
/* 引数		: DecorateList*	: decorateInfo		: 装飾情報[IN]				 */
/*			: FileData* 	: imageData			: 画像情報[I/O] 			 */
/* 戻り値	: SINT			:					: エラーチェック[OUT]		 */
/* 作成日	: 2021/10/27		筈尾  辰也		新規作成					 */
/* ------------------------------------------------------------------------- */
SINT ImageInvert::exe( DecorateList* decorateInfo, FileData* imageData )
{

	/* 変数宣言 */
	SINT iRT_Ver		= INTI;					/* 高さのカウント役			 */
	SINT iRT_Hor		= INTI;					/* 幅のカウント役			 */
	SINT ierrorCheck	= INTI;					/* エラーチェック			 */
	rgb* Color			= NULL;					/* 1ピクセルあたりの輝度格納 */
	SINT imageSize		= INTI;					/* 画像のピクセル数			 */
	SINT ireference		= INTI;					/* 参照先 WARNING回避		 */

	/* 入力値チェック */
	
	/* DM */
	if ( decorateInfo == NULL ) {
		printf( "decorateInfo Inter Check  Error ImageInvert::exe_decorateList\n" );
		return FAILE;
	}
	if ( imageData == NULL ) {
		printf( "decorateInfo Inter Check  Error In ImageInvert::exe_imageData\n" );
		return FAILE;
	}
	/* 装飾種類 */
	if ( decorateInfo->decolateKind != IMAGEINVERT ) {
		printf( "decorateInfo Inter Check  Error In ImageInvert::exe_Kind\n" );
		return FAILE;
	}
	/* 装飾設定 */
	if ( decorateInfo->decolatesetup < IMAGE_INVERT_MIN || IMAGE_INVERT_MAX < decorateInfo->decolatesetup ) {
		printf( "decorateInfo Inter Check  Error In ImageInvert::exe_Setup\n" );
		return FAILE;
	}
	/* 型式 */
	if ( imageData->pFileHData->sFile_Header_Name != MAGIC_NUMBER ) {
		printf( "imageData Inter Check Error In ImageInvert::exe_Type\n" );
		return FAILE;
	}
	/* 大きさ */
	if ( imageData->pInfoHData->uiWidth <= INTI || imageData->pInfoHData->uiHeight <= INTI ) {
		printf( "imageData Inter Check Error In ImageInvert:exe_Size\n" );
		return FAILE;
	}
	/* サイズ取得 */
	imageSize = imageData->pInfoHData->uiWidth * imageData->pInfoHData->uiHeight;

	/* get DM */
	Color = ( rgb* )calloc(imageSize, sizeof( rgb ) );

	/* DM check */
	if ( Color == NULL ) {
		printf( "get dynamic error In ImageInvert\n" );
		return FAILE;
	}

	/* 
	imageData->colordata

	255 255 255 0 125 125 125 0 10 20 30 0....

	Color
	r 255 125 10 
	g 255 125 20
	b 255 125 30...

	→座標的な考えで反転処理を行うので1ピクセルあたりの輝度をまとめて格納
	*/
	for ( iRT_Ver = INTI; iRT_Ver < imageData->pInfoHData->uiHeight; iRT_Ver ++ ) {
		/* 参照値取得 */
		ireference = iRT_Ver * imageData->pInfoHData->uiWidth;

		for ( iRT_Hor = INTI; iRT_Hor < imageData->pInfoHData->uiWidth; iRT_Hor ++ ) {

			( Color + ireference + iRT_Hor )->b = *imageData->pImageData;
			imageData->pImageData ++;
			( Color + ireference + iRT_Hor )->g = *imageData->pImageData;
			imageData->pImageData ++;
			( Color + ireference + iRT_Hor )->r = *imageData->pImageData;
			imageData->pImageData ++;
			( Color + ireference + iRT_Hor )->a = *imageData->pImageData;
			imageData->pImageData ++;
		}
	}
	/* 設定に合わせて処理関数に飛ばす */
	if ( decorateInfo->decolatesetup == HL_INVERT ) {
		ierrorCheck = hl_invert( Color, imageData );
	} else if ( decorateInfo->decolatesetup == RL_INVERT ) {
		ierrorCheck  = rl_invert( Color, imageData );
	}

	if ( ierrorCheck == FAILE ) {
		printf( "画像反転処理に失敗しました\n" );
		return FAILE;
	}

	return SUCCESS;
}
/* ------------------------------------------------------------------------- */
/* 関数名	: ImageImvert::hl_invert										 */
/* 機能名	: 実行する														 */
/* 機能概要	: 上下反転処理を実行する										 */
/* 引数		: rgb*			: Color				: ピクセル情報[IN]			 */
/*			: FileData* 	: imageData			: 画像情報[I/O] 			 */
/* 戻り値	: SINT			:					: エラーチェック[OUT]		 */
/* 作成日	: 2021/10/27		筈尾  辰也		新規作成					 */
/* ------------------------------------------------------------------------- */
SINT ImageInvert::hl_invert( rgb* Color, FileData* imageData )
{

	/* DM */
	if ( Color == NULL ) {
		printf( "decorateInfo Inter Check  Error In ImageInvert::hl_Color\n" );
		return FAILE;
	}
	if ( imageData == NULL ) {
		printf( "decorateInfo Inter Check  Error ImageInvert::hl_imageData\n" );
		return FAILE;
	}
	
	/* 変数宣言 */
	UCHR* protate		= NULL;					/* 装飾後のデータ格納庫		 */
	SINT iver			= INTI;					/* 縦カウント				 */
	SINT ihor			= INTI;					/* 横カウント				 */
	SINT imageSize		= INTI;					/* 画像のバイト数			 */
	SINT ireferenceBfr	= INTI;					/* 変化前の参照数 WARNING回避*/
	SINT ireferenceAft	= INTI;					/* 変化後の参照数 WARNING回避*/

	/* サイズ取得 */
	imageSize = imageData->pInfoHData->uiWidth * imageData->pInfoHData->uiHeight * BYTE4;

	/* get DM */
	protate = ( UCHR* )calloc( imageSize, sizeof( UCHR ) );

	/* DM check */
	if ( protate == NULL ) {
		printf( "get dynamic error In hlInvert\n" );
		return FAILE;
	}
	/*
		10 11 12  Ⅰ
		7  8  9	  Ⅱ
		4  5  6   Ⅲ
		1  2  3   Ⅳ

		① ② ③

		元々このようにピクセルデータが格納されているのが、

		1  2  3   Ⅳ 
		4  5  6   Ⅲ
		7  8  9   Ⅱ
		10 11 12  Ⅰ

		① ② ③
		
		このようになるので
		元の座標を　( hor , ver ) とすると装飾後の座標は( hor ,imageData->Ver - ver )となるのでこの理論を用いる

	*/
	/* 装飾処理 */
	for ( iver = INTI; iver < imageData->pInfoHData->uiHeight; iver ++ ) {
		/* 参照数取得 */
		ireferenceAft = iver * imageData->pInfoHData->uiWidth;

		for ( ihor = INTI; ihor < imageData->pInfoHData->uiWidth; ihor ++ ) {

			/* 参照数取得 */
			ireferenceBfr = ( ( imageData->pInfoHData->uiHeight - BYTE1 - iver ) * imageData->pInfoHData->uiWidth * BYTE4 ) + ihor * BYTE4;

			/* b情報格納 */
			*( protate + ireferenceBfr)			= ( Color + ireferenceAft + ihor )->b;
			/* g情報格納 */
			*( protate + ireferenceBfr + BYTE1 )	= ( Color + ireferenceAft + ihor )->g;
			/* r情報格納 */
			*( protate + ireferenceBfr + BYTE2 )	= ( Color + ireferenceAft + ihor )->r;
			/* α情報格納 */
			*( protate + ireferenceBfr + BYTE3 )	= ( Color + ireferenceAft + ihor )->a;
		}
	}
	/* 画像情報更新 */
	imageData->pImageData = protate;

	return SUCCESS;
}

/* ------------------------------------------------------------------------- */
/* 関数名	: ImageImvert::rl_invert										 */
/* 機能名	: 実行する														 */
/* 機能概要	: 左右反転処理を実行する										 */
/* 引数		: rgb*			: Color				: ピクセル情報[IN]			 */
/*			: FileData* 	: imageData			: 画像情報[I/O] 			 */
/* 戻り値	: SINT			:					: エラーチェック[OUT]		 */
/* 作成日	: 2021/10/27		筈尾  辰也		新規作成					 */
/* ------------------------------------------------------------------------- */
SINT ImageInvert::rl_invert( rgb* Color, FileData* imageData )
{

	/* DM */
	if ( Color == NULL ) {
		printf( "decorateInfo Inter Check  Error In Invert::rl_Color\n" );
		return FAILE;
	}
	if ( imageData == NULL ) {
		printf( "decorateInfo Inter Check  Error In Invert::rl_imageData\n" );
		return FAILE;
	}

	/* 変数宣言 */
	UCHR* protate		= NULL;					/* 装飾後のデータ格納庫		 */
	SINT iver			= INTI;					/* 縦カウント				 */
	SINT ihor			= INTI;					/* 横カウント				 */
	SINT imageSize		= INTI;					/* 画像のバイト数			 */
	SINT ireferenceBfr	= INTI;					/* 変化前の参照数 WARNING回避*/
	SINT ireferenceAft	= INTI;					/* 変化後の参照数 WARNING回避*/

	/* サイズ取得 */
	imageSize = imageData->pInfoHData->uiWidth * imageData->pInfoHData->uiHeight * BYTE4;

	/* get DM */
	protate = ( UCHR* )calloc( imageSize ,sizeof( UCHR ) );

	/* DM check */
	if ( protate == NULL ) {
		printf( "get dynamic error In rlInvert\n" );
		return FAILE;
	}

	/*
		10 11 12  Ⅰ
		7  8  9	  Ⅱ
		4  5  6   Ⅲ
		1  2  3   Ⅳ

		① ② ③

		元々このようにピクセルデータが格納されているのが、

		12 11 10 Ⅰ
		9  8  7	 Ⅱ
		6  5  4	 Ⅲ
		3  2  1  Ⅳ

		③ ② ①

		このようになるので
		元の座標を　( hor , ver ) とすると装飾後の座標は( imageData->Hor - hor , ver )となるのでこの理論を用いる

	*/

	/* 装飾処理 */
	for ( iver = INTI; iver < imageData->pInfoHData->uiHeight; iver ++ ) {
		/* 参照数取得 */
		ireferenceAft = iver * imageData->pInfoHData->uiWidth;

		for ( ihor = INTI; ihor < imageData->pInfoHData->uiWidth; ihor ++ ) {
			/* 参照数取得 */
			ireferenceBfr = (iver * imageData->pInfoHData->uiWidth * BYTE4) + (imageData->pInfoHData->uiWidth - BYTE1 - ihor) * BYTE4;

			/* b情報格納 */
			*( protate + ireferenceBfr )			= ( Color + ireferenceAft + ihor )->b;
			/* g情報格納 */
			*( protate + ireferenceBfr + BYTE1 )	= ( Color + ireferenceAft + ihor )->g;
			/* r情報格納 */
			*( protate + ireferenceBfr + BYTE2 )	= ( Color + ireferenceAft + ihor )->r;
			/* α情報格納 */
			*( protate + ireferenceBfr + BYTE3 )	= ( Color + ireferenceAft + ihor )->a;

		}
	}
	/* 画像情報更新 */
	imageData->pImageData = protate;

	return SUCCESS;

}

/* ------------------------------------------------------------------------- */
/*              Copyright HAL Collage of Technology & Design                 */
/* ------------------------------------------------------------------------- */
