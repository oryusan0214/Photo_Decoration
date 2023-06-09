/* -------------------------------------------------------------------- */
/* ファイル名	:	ImageOutputer.cpp									*/
/* 機能概要		:	指定されたフォーマットに変換をかけて書き込む		*/
/* 作成日		:   2021/11/03											*/
/* 最終更新日	:   2021/11/04											*/
/* 作成者		:	山田龍之介											*/
/* -------------------------------------------------------------------- */
#include "ImageOutputer.h"

/* ------------------------------------------------------------------------- */
/* 関数名	: ImageOutputer::ImageOutputer									 */
/* 機能名	: コンストラクタ												 */
/* 機能概要	: データ初期化等												 */
/* 引数		: なし															 */
/* 戻り値	: void															 */
/* 作成日	: 2021/10/25		筈尾  辰也		新規作成					 */
/* ------------------------------------------------------------------------- */
ImageOutputer::ImageOutputer( void )
{
	/* 初期化 & DM Get */
	bmpOutPath = NULL;
	bmpOutPath = ( SCHR* )calloc( PATHLENGTH, sizeof( SCHR ) );
}

/* ------------------------------------------------------------------------- */
/* 関数名	: ImageOutputer::~ImageOutputer									 */
/* 機能名	: デストラクタ													 */
/* 機能概要	: データ解放等													 */
/* 引数		: なし															 */
/* 戻り値	: void															 */
/* 作成日	: 2021/10/25		筈尾  辰也		新規作成					 */
/* ------------------------------------------------------------------------- */

ImageOutputer::~ImageOutputer( void )
{
	
	/* 解放 */
	if ( *bmpOutPath != NULL ) {
		free( bmpOutPath );
	}
}

/* -------------------------------------------------------------------- */
/* ■■■ public ■■■												    */
/* -------------------------------------------------------------------- */
/* 関数名	:	exe														*/
/* 機能名	:	ファイル読み込み機能									*/
/* 引数		:	:FileData		pFileData 		格納先のファイルパス	*/
/*  			:UCHR			pFilePath		格納先のファイルデータ	*/
/* 戻り値	:	:FileData	NULL			失敗						*/
/*							SUCCESS			成功						*/
/* 作成日	:	2021/11/03		山田　龍之介							*/
/* -------------------------------------------------------------------- */
SINT ImageOutputer::exe(FileData* pFileData,SCHR* pFilePath ) {

	return SUCCESS;
}