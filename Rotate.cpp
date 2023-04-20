/* ------------------------------------------------------------------------- */
/* Rotate.cpp																 */
/* 回転処理																	 */
/* 回転する処理																 */
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
#include "Rotate.h"


/* ------------------------------------------------------------------------- */
/* 関数名	: Rotate::exe													 */
/* 機能名	: 回転する														 */
/* 機能概要	: 回転する処理を実行する										 */
/* 引数		: decorateInfo*	: decorateInfo	: 装飾情報[OUT] 				 */
/*			: FileData* 	: imageData		: 画像情報[OUT] 				 */
/* 戻り値	: SINT		:					: エラーチェック[IN]			 */
/* 作成日	: 2021/10/28		筈尾  辰也		新規作成					 */
/* ------------------------------------------------------------------------- */
SINT Rotate::exe( DecorateList* decorateInfo, FileData* imageData )
{
	/* 変数宣言 */
	SINT iRT_Ver		= INTI;					/* カウント役				 */
	SINT iRT_Hor		= INTI;					/* カウント役				 */
	SINT ierrorCheck	= INTI;					/* エラーチェック			 */
	SINT ipixelSize		= INTI;					/* 画像のピクセル数			 */
	SINT ireferenceVer	= INTI;					/* Warning回避用			 */
	SINT ireference		= INTI;					/* Warning回避用			 */
	rgb* Color			= NULL;					/* 1ピクセルあたりのデータ格納配列 */

	/* 入力値チェック------------------------- */

	/* DM */
	if ( decorateInfo == NULL ) {
		printf( "decorateInfo Inter Check  Error In Rotate::exe_decorateList\n" );
		return FAILE;
	}
	if ( imageData == NULL ) {
		printf( "decorateInfo Inter Check  Error In Rotate:exe_imageData\n" );
		return FAILE;
	}
	/* 装飾種類 */
	if ( decorateInfo->decolateKind != ROTATE ) {
		printf( "decorateInfo Inter Check  Error In Rotate::exe_Kind\n" );
		return FAILE;
	}
	/* 装飾設定 */
	if ( decorateInfo->decolatesetup < ROTATE_MIN || ROTATE_MAX < decorateInfo->decolatesetup ) {
		printf( "decorateInfo Inter Check  Error In Rotate::exe_Setup\n" );
		return FAILE;
	}
	/* 型式 */
	if ( imageData->pFileHData->sFile_Header_Name != MAGIC_NUMBER ) {
		printf( "imageData Inter Check Error In Rotate::exe_Type\n" );
		return FAILE;
	}
	/* 大きさ */
	if ( imageData->pInfoHData->uiWidth <= INTI || imageData->pInfoHData->uiHeight <= INTI ) {
		printf( "imageData Inter Check Error In Rotate::exe_Size\n" );
		return FAILE;
	}

	/* Get Pixel */
	ipixelSize = imageData->pInfoHData->uiHeight * imageData->pInfoHData->uiWidth;

	/* get DM */
	Color = ( rgb* )calloc( ipixelSize, sizeof( rgb ) );

	/* DM check */
	if ( Color == NULL ) {
		printf( "get DM error_Rotate_Color\n" );
		return FAILE;
	}

	/* Colorにデータ複製 */
	for ( iRT_Ver = INTI; iRT_Ver < imageData->pInfoHData->uiHeight; iRT_Ver ++ ) {
		for ( iRT_Hor = INTI; iRT_Hor < imageData->pInfoHData->uiWidth; iRT_Hor ++ ) {

			/* Warning回避のための中間関数 */
			ireferenceVer	= iRT_Ver * imageData->pInfoHData->uiWidth;
			ireference		= ( iRT_Ver * imageData->pInfoHData->uiWidth + iRT_Hor ) * BYTE4 ;

			( Color + ireferenceVer + iRT_Hor )->b = *( imageData->pImageData + ireference );
			( Color + ireferenceVer + iRT_Hor )->g = *( imageData->pImageData + ireference + BYTE1 );
			( Color + ireferenceVer + iRT_Hor )->r = *( imageData->pImageData + ireference + BYTE2 );
			( Color + ireferenceVer + iRT_Hor )->a = *( imageData->pImageData + ireference + BYTE3 );
		}
	}
	
	/* 設定により飛ばす */
	if ( decorateInfo->decolatesetup		== ONE_PUARTER ) {
		ierrorCheck = one_quarter( Color, imageData );
	}
	else if ( decorateInfo->decolatesetup	== TWO_PUARTER ) {
		ierrorCheck = two_quarter( Color, imageData );
	}
	else if ( decorateInfo->decolatesetup	== THREE_PUARTER ) {
		ierrorCheck = three_quarter( Color, imageData );
	}
	else if ( decorateInfo->decolatesetup	== FOUR_PUARTER ) {
	}

	if ( ierrorCheck == FAILE ) {
		printf( "回転処理に失敗しました\n" );
		return FAILE;
	}
	return SUCCESS;
}

/* ------------------------------------------------------------------------- */
/* 関数名	: Rotate::one_quarter											 */
/* 機能名	: 90度回転する													 */
/* 機能概要	: 90度回転する処理を実行する									 */
/* 引数		: rgb*			: Color			: 画像データ情報[OUT] 			 */
/*			: FileData* 	: imageData		: 画像情報[OUT] 				 */
/* 戻り値	: SINT		:					: エラーチェック[IN]			 */
/* 作成日	: 2021/10/28		筈尾  辰也		新規作成					 */
/* ------------------------------------------------------------------------- */
SINT Rotate::one_quarter( rgb* Color, FileData* imageData )
{

	/* DM */
	if ( Color == NULL ) {
		printf( "decorateInfo Inter Check  Error In Rotate::one_Color\n" );
		return FAILE;
	}
	if ( imageData == NULL ) {
		printf( "decorateInfo Inter Check  Error In Rotate:one_imageData\n" );
		return FAILE;
	}

	/* 変数宣言 */
	UCHR* protate	= NULL;						/* 装飾後の画像データ		 */
	SINT iver		= INTI;						/* 高さ						 */
	SINT ihor		= INTI;						/* 幅						 */
	SINT iverMax	= INTI;						/* 高さの最大値				 */
	SINT ihorMax	= INTI;						/* 幅の最大値				 */
	SINT ibox		= INTI;						/* 空箱						 */
	SINT imageSize	= INTI;						/* 画像サイズ				 */
	SINT ireference = INTI;						/* 参照しているバイト		 */
	SINT ireferenceVer = INTI;					/* Warning回避用			 */


	/* 画像サイズ取得 */
	imageSize = imageData->pInfoHData->uiWidth * imageData->pInfoHData->uiHeight * BYTE4;

	/* get DM */
	protate = ( UCHR* )calloc( imageSize,sizeof( UCHR ) );

	/* check DM */
	if ( protate == NULL ) {
		printf( "get dynamic error In Rotate::three_quater\n" );
		return FAILE;
	}
	/* 変化前最大値の保存 */
	iverMax = imageData->pInfoHData->uiHeight;
	ihorMax = imageData->pInfoHData->uiWidth;

	/* 縦横数値入れ替え */
	ibox							= imageData->pInfoHData->uiWidth;
	imageData->pInfoHData->uiWidth	= imageData->pInfoHData->uiHeight;
	imageData->pInfoHData->uiHeight	= ibox;

	/*
		10 11 12	 1
		7  8  9		 2
		4  5  6		 3
		1  2  3		 4

		① ② ③

		元々このようにピクセルデータが格納されているのが、

		12 9  6  3	③
		11 8  5  2	②
		10 7  4  1	①

		1  2  3  4
 
		このようになるので
		元の座標を　( hor , ver ) とすると装飾後の座標は( ver , horMax - hor )となるのでこの理論を用いる

	*/
	/* 回転処理------------------------------- */
	for ( iver = INTI; iver < iverMax; iver ++ ) {
		for (ihor = INTI; ihor < ihorMax; ihor ++ ) {

			/* 最大値は1スタート、プログラムは0スタートのため一致させるために - 1 している */
			ireference = ( iver + ( ( ihorMax - BYTE1 - ihor ) * imageData->pInfoHData->uiWidth ) ) * BYTE4;
			/* Warning回避のための中間関数 */
			ireferenceVer = iver * ihorMax;

			*( protate + ireference )			= ( Color + ireferenceVer + ihor )->b;
			*( protate + ireference + BYTE1 )	= ( Color + ireferenceVer + ihor )->g;
			*( protate + ireference + BYTE2 )	= ( Color + ireferenceVer + ihor )->r;
			*( protate + ireference + BYTE3 )	= ( Color + ireferenceVer + ihor )->a;
		}
	}
	/* --------------------------------------- */
	/* 画像データ更新 */
	imageData->pImageData = protate;

	return SUCCESS;
}

/* ------------------------------------------------------------------------- */
/* 関数名	: Rotate::two_quarter											 */
/* 機能名	: 180度回転する													 */
/* 機能概要	: 180度回転する処理を実行する									 */
/* 引数		: rgb*			: Color			: 画像データ情報[OUT] 			 */
/*			: FileData* 	: imageData		: 画像情報[OUT] 				 */
/* 戻り値	: SINT		:					: エラーチェック[IN]			 */
/* 作成日	: 2021/10/28		筈尾  辰也		新規作成					 */
/* ------------------------------------------------------------------------- */

SINT Rotate::two_quarter( rgb* Color, FileData* imageData )
{

	/* DM */
	if ( Color == NULL ) {
		printf( "decorateInfo Inter Check  Error In Rotate::two_Color\n" );
		return FAILE;
	}
	if ( imageData == NULL ) {
		printf( "decorateInfo Inter Check  Error In Rotate:two_imageData\n" );
		return FAILE;
	}

	/* 変数宣言 */
	UCHR* protate	= NULL;						/* 装飾後の画像データ		 */
	SINT iver		= INTI;						/* 高さ						 */
	SINT ihor		= INTI;						/* 幅						 */
	SINT iverMax	= INTI;						/* 高さの最大値				 */
	SINT ihorMax	= INTI;						/* 幅の最大値				 */
	SINT ibox		= INTI;						/* 空箱						 */
	SINT imageSize	= INTI;						/* 画像サイズ				 */
	SINT ireference = INTI;						/* 参照しているバイト		 */
	SINT ireferenceVer = INTI;					/* Warning回避用			 */


	/* 画像サイズ取得 */
	imageSize = imageData->pInfoHData->uiWidth * imageData->pInfoHData->uiHeight * BYTE4;

	/* get DM */
	protate = ( UCHR* )calloc( imageSize,sizeof( UCHR ) );

	/* check DM */
	if ( protate == NULL ) {
		printf( "get dynamic error In Rotate::two_quater\n" );
		return FAILE;
	}
	/* 変化前最大値の保存 */
	iverMax = imageData->pInfoHData->uiHeight;
	ihorMax = imageData->pInfoHData->uiWidth;

	/*
		10 11 12	 1
		7  8  9		 2
		4  5  6		 3
		1  2  3		 4

		① ② ③

		元々このようにピクセルデータが格納されているのが、

		3  2  1		4
		6  5  4		3
		9  8  7		2
		12 11 10	1

		③ ② ①

		このようになるので
		元の座標を　( hor , ver ) とすると装飾後の座標は( horMax - hor , verMax - ver )となるのでこの理論を用いる

	*/
	/* 回転処理------------------------------- */
	for ( iver = INTI; iver < iverMax; iver ++ ) {
		for (ihor = INTI; ihor < ihorMax; ihor ++ ) {

			/* 最大値は1スタート、プログラムは0スタートのため一致させるために - 1 している */
			ireference = ( ( ihorMax - BYTE1 - ihor ) + ( ( iverMax - BYTE1 - iver ) * imageData->pInfoHData->uiWidth ) ) * BYTE4;
			/* Warning回避のための中間関数 */
			ireferenceVer = iver * ihorMax;

			*( protate + ireference)				= ( Color + ireferenceVer + ihor )->b;
			*( protate + ireference + BYTE1 )		= ( Color + ireferenceVer + ihor )->g;
			*( protate + ireference + BYTE2 )		= ( Color + ireferenceVer + ihor )->r;
			*( protate + ireference + BYTE3 )		= ( Color + ireferenceVer + ihor )->a;
		}
	}
	/* --------------------------------------- */
	/* 画像データ更新 */
	imageData->pImageData = protate;

	return SUCCESS;
}

/* ------------------------------------------------------------------------- */
/* 関数名	: Rotate::three_quarter											 */
/* 機能名	: 270度回転する													 */
/* 機能概要	: 270度回転する処理を実行する									 */
/* 引数		: rgb*			: Color			: 画像データ情報[OUT] 			 */
/*			: FileData* 	: imageData		: 画像情報[OUT] 				 */
/* 戻り値	: SINT		:					: エラーチェック[IN]			 */
/* 作成日	: 2021/10/28		筈尾  辰也		新規作成					 */
/* ------------------------------------------------------------------------- */

SINT Rotate::three_quarter( rgb* Color,FileData* imageData )
{

	/* DM */
	if ( Color == NULL ) {
		printf( "decorateInfo Inter Check  Error In Rotate::three_Color\n" );
		return FAILE;
	}
	if ( imageData == NULL ) {
		printf( "decorateInfo Inter Check  Error In Rotate:three_imageData\n" );
		return FAILE;
	}

	/* 変数宣言 */
	UCHR* protate		= NULL;					/* 装飾後の画像データ		 */
	SINT iver			= INTI;					/* 高さ						 */
	SINT ihor			= INTI;					/* 幅						 */
	SINT iverMax		= INTI;					/* 高さの最大値				 */
	SINT ihorMax		= INTI;					/* 幅の最大値				 */
	SINT ibox			= INTI;					/* 空箱						 */
	SINT imageSize		= INTI;					/* 画像サイズ				 */
	SINT ireference		= INTI;					/* 参照しているバイト		 */
	SINT ireferenceVer	= INTI;					/* Warning回避用			 */


	/* 画像サイズ取得 */
	imageSize = imageData->pInfoHData->uiWidth * imageData->pInfoHData->uiHeight * BYTE4;

	/* get DM */
	protate = ( UCHR* )calloc( imageSize,sizeof( UCHR ) );

	/* check DM */
	if ( protate == NULL ) {
		printf( "get dynamic error In Rotate::one_quater\n" );
		return FAILE;
	}
	/* 変化前最大値の保存 */
	iverMax = imageData->pInfoHData->uiHeight;
	ihorMax = imageData->pInfoHData->uiWidth;

	/* 縦横数値入れ替え */
	ibox							= imageData->pInfoHData->uiWidth;
	imageData->pInfoHData->uiWidth	= imageData->pInfoHData->uiHeight;
	imageData->pInfoHData->uiHeight	= ibox;

	/*
		10 11 12	 1
		7  8  9		 2
		4  5  6		 3
		1  2  3		 4

		① ② ③

		元々このようにピクセルデータが格納されているのが、

		1  4  7  10 ①
		2  5  8  11	②
		3  6  9  12 ③

		4　3　2　1

		このようになるので
		元の座標を　( hor , ver ) とすると装飾後の座標は( verMax - ver , hor )となるのでこの理論を用いる

	*/
	/* 回転処理------------------------------- */
	for ( iver = INTI; iver < iverMax; iver ++ ) {
		for (ihor = INTI; ihor < ihorMax; ihor ++ ) {

			/* 最大値は1スタート、プログラムは0スタートのため一致させるために - 1 している */
			ireference = ( ( iverMax - BYTE1 - iver ) + ( ihor * imageData->pInfoHData->uiWidth ) ) * BYTE4;
			/* Warning回避のための中間関数 */
			ireferenceVer = iver * ihorMax;

			*( protate + ireference )			= ( Color + ireferenceVer + ihor )->b;
			*( protate + ireference + BYTE1 )	= ( Color + ireferenceVer + ihor )->g;
			*( protate + ireference + BYTE2 )	= ( Color + ireferenceVer + ihor )->r;
			*( protate + ireference + BYTE3 )	= ( Color + ireferenceVer + ihor )->a;
		}
	}
	/* --------------------------------------- */
	/* 画像データ更新 */
	imageData->pImageData = protate;

	return SUCCESS;
}
/* ------------------------------------------------------------------------- */
/*              Copyright HAL Collage of Technology & Design                 */
/* ------------------------------------------------------------------------- */
