/* ------------------------------------------------------------------------- */
/* Magnification.cpp														 */
/* 拡大縮小処理																 */
/* 画像の拡大縮小を行う														 */
/* ------------------------------------------------------------------------- */
/* 番号	更新履歴								日付		   氏名			 */
/* ------------------------------------------------------------------------- */
/* 000000	新規作成							2021/10/28     筈尾　辰也	 */
/* 000001	リファクタリング					2021/11/27	   筈尾  辰也	 */
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
/* Include File																 */
/* ------------------------------------------------------------------------- */
#include "System.h"
#include "Magnification.h"


/* ------------------------------------------------------------------------- */
/* 関数名	: Magnification::exe											 */
/* 機能名	: 実行する														 */
/* 機能概要	: 拡大縮小処理を実行する										 */
/* 引数		: DecorateList* : decorateInfo		: 装飾情報[IN]	 			 */
/*			: FileData* 	: imageData			: 画像情報[I/O] 			 */
/* 戻り値	: SINT		:					: エラーチェック[OUT]			 */
/* 作成日	: 2021/10/28		筈尾  辰也		新規作成					 */
/* ------------------------------------------------------------------------- */
SINT Magnification::exe( DecorateList* decorateInfo, FileData* imageData )
{

	/* 入力値チェック------------------------- */

	/* DM */
	if ( decorateInfo == NULL ) {
		printf( "decorateInfo Inter Check  Error In Magn::exe_decorateList\n" );
		return FAILE;
	}
	if ( imageData == NULL ) {
		printf( "decorateInfo Inter Check  Error In Magn::exe_imageData\n" );
		return FAILE;
	}
	/* 装飾種類 */
	if ( decorateInfo->decolateKind != MAGNIFICATION ) {
		printf( "decorateInfo Inter Check  Error In Magnification::exe_Kind\n" );
		return FAILE;
	}
	/* 装飾設定 */
	if ( decorateInfo->decolatesetup < MAGN_MIN || MAGN_MAX < decorateInfo->decolatesetup ) {
		printf( "decorateInfo Inter Check  Error In Magnification::exe_Setup\n" );
		return FAILE;
	}
	/* 型式 */
	if ( imageData->pFileHData->sFile_Header_Name != MAGIC_NUMBER ) {
		printf( "imageData Inter Check Error In Magnification_Type\n" );
		return FAILE;
	}
	/* 大きさ */
	if ( imageData->pInfoHData->uiWidth <= INTI || imageData->pInfoHData->uiHeight <= INTI ) {
		printf( "imageData Inter Check Error In Magnification::exe_Size\n" );
		return FAILE;
	}

	/* 変数宣言 */
	UCHR* pmag			= NULL;					/* 装飾後の画像のデータ		 */
	SINT ibaseVer		= INTI;					/* 元画像の高さ				 */
	SINT ibaseHor		= INTI;					/* 元画像の幅				 */
	SINT iMG_Cnt		= INTI;					/* カウント役				 */
	SINT iMG_Ver		= INTI;					/* カウント役				 */
	SINT iMG_Hor		= INTI;					/* カウント役				 */
	SINT iloop_Ver		= INTI;					/* 縦ループ数				 */
	SINT iloop_Hor		= INTI;					/* 幅ループ数				 */
	SINT iloop_Ver_Cnt	= INTI;					/* カウント役				 */
	SINT iloop_Hor_Cnt	= INTI;					/* カウント役				 */
	FLOT fmag			= INTI;					/* 現在の必要ループ			 */
	FLOT fcnt_Ver		= INTI;					/* カウント役				 */
	FLOT fcnt_Hor		= INTI;					/* カウント役				 */
	SINT imageSize		= INTI;					/* 画像のピクセル数			 */
	SINT ireference_Ver = INTI;					/* 縦の参照数 WARNING回避	 */
	SINT ireference_Hor = INTI;					/* 横の参照数 WARNING回避	 */


	/* 縦横の値複製 */
	ibaseVer = imageData->pInfoHData->uiHeight;
	ibaseHor = imageData->pInfoHData->uiWidth;

	/* --------------------------------------- */
	/* 倍率取得(Setupは十倍の値になっているので) */
	fmag = decorateInfo->decolatesetup / GET_MAG;

	/* 画像サイズ取得 */
	imageSize = imageData->pInfoHData->uiWidth * imageData->pInfoHData->uiHeight * BYTE4 * fmag;


	/* 大きさ変更 */
	imageData->pInfoHData->uiWidth	= imageData->pInfoHData->uiWidth	* fmag / EXC_MAG;
	imageData->pInfoHData->uiHeight	= imageData->pInfoHData->uiHeight	* fmag / EXC_MAG;

	/* ipixel以下回避 */
	if( imageSize < BYTE1 ){
		imageData->pInfoHData->uiWidth	= BYTE1;
		imageData->pInfoHData->uiHeight	= BYTE1;
		imageSize						= BYTE1;
	}
	/* get DM */
	pmag = ( UCHR* )calloc( imageSize , sizeof( UCHR ) );

	/* DM check */
	if ( pmag == NULL ) {
		printf( "get dynamic error In Magnification\n" );
		return FAILE;
	}	
	/* 
	* 最近傍観法を利用
	* 
	* 1  2  3  4  
	* 5  6  7  8  
	* 9  10 11 12 
	* 13 14 15 16 
	* 
	* →200%
	* 
	* 1  .  2  .  3  .  4  . 
	* .  .  .  .  .  .  .  .
	* 5  .  6  .  7  .  8  .
	* .  .  .  .  .  .  .  .
	* 9  .  10 .  11 .  12 .
	* .  .  .  .  .  .  .  . 
	* 13 .  14 .  15 .  16 .
	* 
	* →　. の位置の必要な情報、なので . の位置から
	*       最も近いところにある色情報がそこの情報とみなす
	* 
	* →考え方
	*	134%の拡大であれば、3回に1回だけ2回ループ
	* 例
	* 1   2   3		1   .2  . 3
	* 
	* 
	* 
	* 4   5   6 →	.   .   .
	*				4    5    6
	* 
	* 
	* 7   8   9		.   .   .
	*
	*				7    8    9 
	* 
	* 10  11  12	.   .   .
	* 
	* 
	*				10   .11  . 12
	* 
	* 
	* 
	*	なので、ループごとに倍率値を足して、100で引いた値数ループする
	*	つまり
	*	
	*	倍率134%
	*			sum		
	*	1回目   0 + 134	 134 - 100 = 34	→1ループ	
	*	2回目   34+ 134	 168 - 100 = 68	→1ループ   
	*	3回目   68+ 134	 202 - 200 = 2	→2ループ
	*	4回目   2 + 134	 136 - 100 = 36	→1ループ
	* 
	* という考えでループ数を考える
	* 
	*/

	/* 装飾処理------------------------------- */

	/* 1pixel */
	if( imageSize == BYTE1 ){
		/* Warning回避 */
		ireference_Ver = ( ibaseHor / BYTE2 ) + ( ibaseVer * ibaseHor / BYTE2 ) * BYTE4;

		/* 1BYTEなら真ん中決め打ち */
		*pmag = *( imageData->pImageData + ireference_Ver );

		/* データの更新 */
		imageData->pImageData = pmag;

		return SUCCESS;
	}

	/* 縦カウント( 元画像の高さ分 ) */
	for ( iMG_Ver = INTI; iMG_Ver < ibaseVer; iMG_Ver ++ ) {

		/* ループ数算出 */
		fcnt_Ver = fcnt_Ver + fmag;
		while ( GET_LOOP <= fcnt_Ver ) {
			fcnt_Ver = fcnt_Ver - GET_LOOP;
			iloop_Ver ++;
		}

		/* 参照数取得 */
		ireference_Ver = iMG_Ver * ibaseHor * BYTE4;

		/* 縦ループ */
		for ( iloop_Ver_Cnt = INTI; iloop_Ver_Cnt < iloop_Ver; iloop_Ver_Cnt ++ ) {

				/* 横カウント( 元画像の幅 ) */
			for ( iMG_Hor = INTI; iMG_Hor < ibaseHor; iMG_Hor ++ ) {

				/* ループ数算出 */
				fcnt_Hor = fcnt_Hor + fmag;
				while ( GET_LOOP <= fcnt_Hor ) {
					fcnt_Hor = fcnt_Hor - GET_LOOP;
					iloop_Hor ++;
				}
				/* 参照数取得 */
				ireference_Hor = iMG_Hor * BYTE4;

				/* 横ループ */
				for (iloop_Hor_Cnt = INTI; iloop_Hor_Cnt < iloop_Hor; iloop_Hor_Cnt ++ ) {

					/* 1ピクセル書き込み---------------- */
					/* ibasever をibasehorに変更 */
					*( pmag + iMG_Cnt ) = *( imageData->pImageData + ireference_Ver + ireference_Hor);
					iMG_Cnt ++;
					*( pmag + iMG_Cnt ) = *( imageData->pImageData + ireference_Ver + ireference_Hor + BYTE1 );
					iMG_Cnt ++;
					*( pmag + iMG_Cnt ) = *( imageData->pImageData + ireference_Ver + ireference_Hor + BYTE2 );
					iMG_Cnt ++;
					*( pmag + iMG_Cnt ) = *( imageData->pImageData + ireference_Ver + ireference_Hor + BYTE3 );
					iMG_Cnt ++;
					/* --------------------------------- */
				}
				/* ループ値の初期化 */
				iloop_Hor = INTI;
			}
		}
		/* ループ値の初期化 */
		iloop_Ver = INTI;
	}
	/* --------------------------------------- */
	
	/* データの更新 */
	imageData->pImageData = pmag;

	return SUCCESS;
}
/* ------------------------------------------------------------------------- */
/*              Copyright HAL Collage of Technology & Design                 */
/* ------------------------------------------------------------------------- */
