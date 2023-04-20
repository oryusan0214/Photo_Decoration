/* ------------------------------------------------------------------------- */
/* IndependentProcessing.cpp												 */
/* 単独処理																	 */
/* 初期化、解放のみ記載( exeは置物 )										 */
/* ------------------------------------------------------------------------- */
/* 番号	更新履歴								日付		   氏名			 */
/* ------------------------------------------------------------------------- */
/* 000000	新規作成							2021/10/15     筈尾　辰也	 */
/* 000001	リファクタリング					2021/11/22	   筈尾  辰也	 */
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
/* Include																	 */
/* ------------------------------------------------------------------------- */
#include "IndependentProcessing.h"


/* ------------------------------------------------------------------------- */
/* 関数名	: IndependentProcessing::IndependentProcessing					 */
/* 機能名	: コンストラクタ												 */
/* 機能概要	: データ初期化等												 */
/* 引数		: なし															 */
/* 戻り値	: void															 */
/* 作成日	: 2021/10/15		筈尾  辰也		新規作成					 */
/* ------------------------------------------------------------------------- */
IndependentProcessing::IndependentProcessing( void )
{
	/* 初期化 & get DM */
	secondImageData	=	NULL;
	thirdImageData	=	NULL;
	fourthImageData	=	NULL;

	secondImageData	= ( FileData* )calloc( sizeof( FileData ), sizeof( UCHR ) );
	thirdImageData	= ( FileData* )calloc( sizeof( FileData ), sizeof( UCHR ) );
	fourthImageData	= ( FileData* )calloc( sizeof( FileData ), sizeof( UCHR ) );

	/* DM Get Error */
	if ( secondImageData == NULL || thirdImageData == NULL || fourthImageData == NULL ) {
		printf( "DM Get Error In IndependentProcessing::IndependentProcessing\n" );
	}
	
}

/* ------------------------------------------------------------------------- */
/* 関数名	: IndependentProcessing::~IndependentProcessing					 */
/* 機能名	: デストラクタ													 */
/* 機能概要	: 確保している領域の解放										 */
/* 引数		: なし															 */
/* 戻り値	: void															 */
/* 作成日	: 2021/10/15		筈尾  辰也		新規作成					 */
/* ------------------------------------------------------------------------- */
IndependentProcessing::~IndependentProcessing( void )
{
	/* 多重開放防止 */
	if ( secondImageData != NULL && secondImageData != thirdImageData && secondImageData != fourthImageData ) {
		free( secondImageData );
	}
	if ( thirdImageData != NULL && thirdImageData != fourthImageData ) {
		free( thirdImageData );
	}
	if ( fourthImageData != NULL ) {
		free( fourthImageData );
	}

}
/* ------------------------------------------------------------------------- */
/* 関数名	: IndependentProcessing::exe									 */
/* 機能名	: 実行する														 */
/* 機能概要	: 単独処理を実行する											 */
/* 引数		: DecorateList* : decorateInfo		: 装飾情報[IN] 				 */
/*			: FileData	 	: imageData			: 画像情報[I/O] 			 */
/*			: FileData		: secondImageData	: 二枚目の装飾情報[IN] 		 */
/*			: FileData		: thirdImageData	: 三枚目の装飾情報[IN] 		 */
/*			: FileData	 	: fourthImageData	: 四枚目の装飾情報[IN] 		 */
/* 戻り値	: SINT			:					: エラーチェック[OUT]		 */
/* 作成日	: 2021/10/15		筈尾  辰也		新規作成					 */
/* ------------------------------------------------------------------------- */
void IndependentProcessing::exe( DecorateList* decorateInfo, FileData* imageData,
								 FileData* secondImageData, FileData* thirdImageData, FileData* fourthImageData )
{

}
/* ------------------------------------------------------------------------- */
/*              Copyright HAL Collage of Technology & Design                 */
/* ------------------------------------------------------------------------- */
