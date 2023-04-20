/* ------------------------------------------------------------------------- */
/* Mosaic.cpp																 */
/* モザイク処理																 */
/* 画像の粒度を落とす														 */
/* ------------------------------------------------------------------------- */
/* 番号	更新履歴								日付		   氏名			 */
/* ------------------------------------------------------------------------- */
/* 000000	新規作成							2021/10/31     筈尾　辰也	 */
/* 000001	リファクタリング					2021/11/27	   筈尾  辰也	 */
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
/* Include File																 */
/* ------------------------------------------------------------------------- */
#include "System.h"
#include "Mosaic.h"


/* ------------------------------------------------------------------------- */
/* 関数名	: Mosaic::exe													 */
/* 機能名	: 実行する														 */
/* 機能概要	: モザイクを実行する											 */
/* 引数		: DecorateList* : decorateInfo		: 装飾情報[IN]				 */
/*			: FileData* 	: imageData			: 画像情報[I/O] 			 */
/* 戻り値	: SINT		:					: エラーチェック[OUT]			 */
/* 作成日	: 2021/10/31		筈尾  辰也		新規作成					 */
/* ------------------------------------------------------------------------- */
SINT Mosaic::exe( DecorateList* decorateInfo, FileData* imageData )
{
	//
	/* 変数宣言 */
	UCHR* pmosaic		= NULL;					/* 装飾後の画像データ		 */
	SINT ired			= INTI;					/* 赤の平均値				 */
	SINT iblue			= INTI;					/* 青の平均値				 */
	SINT igreen			= INTI;					/* 緑の平均値				 */
	SINT iMSC_Ver		= INTI;					/* カウント役				 */
	SINT iMSC_Hor		= INTI;					/* カウント役				 */
	SINT iMSC_Ver_Cnt	= INTI;					/* カウント役				 */
	SINT iMSC_Hor_Cnt	= INTI;					/* カウント役				 */
	SINT iMSC_Cnt		= INTI;					/* カウント役				 */
	SINT iMSC_Ver_Max	= INTI;					/* 縦のループ最大値			 */
	SINT iMSC_Hor_Max	= INTI;					/* 横のループ最大値			 */
	SINT iLoop			= INTI;					/* ループ数					 */
	SINT imageSize		= INTI;					/* 画像のピクセル数			 */
	SINT ireference		= INTI;					/* WARNING回避用			 */

	/* 入力値チェック */

	/* DM */
	if ( decorateInfo == NULL ) {
		printf( "decorateInfo Inter Check  Error In Mosaic::exe_decorateList\n" );
		return FAILE;
	}
	if ( imageData == NULL ) {
		printf( "decorateInfo Inter Check  Error In Mosaic::exe_imageData\n" );
		return FAILE;
	}
	/* 装飾種類 */
	if ( decorateInfo->decolateKind != MOSAIC ) {
		printf( "decorateInfo Inter Check  Error In Mosaic::exe_Kind\n" );
		return FAILE;
	}
	/* 装飾設定 */
	if ( decorateInfo->decolatesetup <= INTI ) {
		printf( "decorateInfo Inter Check  Error In Mosaic::exe_Setup\n" );
		return FAILE;
	}
	/* 型式 */
	if ( imageData->pFileHData->sFile_Header_Name != MAGIC_NUMBER ) {
		printf( "imageData Inter Check Error In Mosaic::exe_Type\n" );
		return FAILE;
	}
	/* 大きさ */
	if ( imageData->pInfoHData->uiWidth <= INTI || imageData->pInfoHData->uiHeight <= INTI ) {
		printf( "imageData Inter Check Error In Mosaic::exe_Size\n" );
		return FAILE;
	}

	/* 入力値が辺より大きい場合は辺の長さに変更 */
	if ( imageData->pInfoHData->uiHeight < imageData->pInfoHData->uiWidth && imageData->pInfoHData->uiWidth < decorateInfo->decolatesetup ) {
		decorateInfo->decolatesetup = imageData->pInfoHData->uiWidth;
	}
	if ( imageData->pInfoHData->uiWidth < imageData->pInfoHData->uiHeight && imageData->pInfoHData->uiHeight < decorateInfo->decolatesetup ) {
		decorateInfo->decolatesetup = imageData->pInfoHData->uiHeight;
	}

	/* サイズ取得 */
	imageSize = imageData->pInfoHData->uiWidth * imageData->pInfoHData->uiHeight * BYTE4;

	/* Get DM */
	pmosaic = ( UCHR* )calloc( imageSize , sizeof( UCHR ) );
	
	/* DM Check */
	if ( pmosaic == NULL ) {
		printf( "get DM error In Mosaic\n" );
		return FAILE;
	}
	/* モザイク処理--------------------------- */

	/* ループ数取得 */
	iMSC_Ver_Max = ( imageData->pInfoHData->uiHeight ) / decorateInfo->decolatesetup;
	iMSC_Hor_Max = ( imageData->pInfoHData->uiWidth  )  / decorateInfo->decolatesetup;

	if( ( ( imageData->pInfoHData->uiHeight ) % decorateInfo->decolatesetup ) != INTI ){
		iMSC_Ver_Max ++;
	}
	if( ( ( imageData->pInfoHData->uiWidth ) % decorateInfo->decolatesetup ) != INTI ){
		iMSC_Hor_Max ++;
	}

	
	
	/* ループ値が不定なので無限ループ */
	while ( TRUE ) {
		/* 縦ループ */
		for ( iMSC_Ver = iMSC_Ver_Cnt * decorateInfo->decolatesetup; iMSC_Ver < (iMSC_Ver_Cnt + BYTE1 ) * decorateInfo->decolatesetup; iMSC_Ver ++ ) {

			/* 端についたらブレーク */
			/* -1を追加 */
			if ( iMSC_Ver == ( imageData->pInfoHData->uiHeight - BYTE1 ) ) {
				break;
			}
			/* 参照値取得 */
			ireference = iMSC_Ver * imageData->pInfoHData->uiWidth * BYTE4;

			/* 横ループ */
			for ( iMSC_Hor = iMSC_Hor_Cnt * BYTE4 * decorateInfo->decolatesetup; iMSC_Hor < (iMSC_Hor_Cnt + BYTE1 ) * BYTE4 * decorateInfo->decolatesetup; iMSC_Hor ++ ) {

				/* 端についたらbreak */
				/* -1を追加 */
				if ( iMSC_Hor == ( ( imageData->pInfoHData->uiWidth - BYTE1 ) * BYTE4 ) ) {
					break;
				}
				/* rgbαで場合分け */
				switch ( ( iMSC_Hor + BYTE1 ) % BYTE4 ) {
				case INTI:	/* α */
					iMSC_Cnt ++;															break;

				case BYTE1:	/* b  */
					iblue	= iblue  + *(imageData->pImageData + ireference + iMSC_Hor);	break;

				case BYTE2:	/* g  */
					igreen	= igreen + *(imageData->pImageData + ireference + iMSC_Hor);	break;

				case BYTE3	/* r  */
				:	ired	= ired   + *(imageData->pImageData + ireference + iMSC_Hor);	break;

				default:
					break;
				}
			}
		}
		
		/* 0割り対策 理論上はここ踏まない */
		if (iMSC_Cnt == INTI) {
			iMSC_Cnt = BYTE1;
		}

		/* 平均値算出 */
		iblue	= iblue		/ iMSC_Cnt;
		igreen	= igreen	/ iMSC_Cnt;
		ired	= ired		/ iMSC_Cnt;
		
		/* データ入力 */
		/* 縦ループ */
		for ( iMSC_Ver = iMSC_Ver_Cnt * decorateInfo->decolatesetup; iMSC_Ver < ( iMSC_Ver_Cnt + BYTE1 ) * decorateInfo->decolatesetup; iMSC_Ver ++ ) {

			/* 端についたらbreak */
			/* -1追加 */
			if ( iMSC_Ver == ( imageData->pInfoHData->uiHeight - BYTE1 ) ) {
				break;
			}
			/* 参照値取得 */
			ireference = iMSC_Ver * imageData->pInfoHData->uiWidth * BYTE4;

			/* 横ループ */
			for ( iMSC_Hor = iMSC_Hor_Cnt * BYTE4 * decorateInfo->decolatesetup; iMSC_Hor < ( iMSC_Hor_Cnt + BYTE1 ) * BYTE4 * decorateInfo->decolatesetup; iMSC_Hor ++ ) {
				/* 端についたらbreak */
				/* -1追加 */
				if ( iMSC_Hor == ( imageData->pInfoHData->uiWidth * BYTE4 ) ) {
					break;
				}
				/* rgbαで場合分け */
				switch ( ( iMSC_Hor + BYTE1 ) % BYTE4 ) {
				case INTI:	/* α */
					*( pmosaic + ireference + iMSC_Hor ) = ( UCHR )INTI;	break;

				case BYTE1:	/* b  */
					*( pmosaic + ireference + iMSC_Hor ) = iblue;			break;

				case BYTE2:	/* g  */
					*( pmosaic + ireference + iMSC_Hor ) = igreen;			break;

				case BYTE3:	/* r  */
					*( pmosaic + ireference + iMSC_Hor ) = ired;			break;

				default:
					break;
				}
			}
		}
		/* カウント値の++ */
		/* = に変更 */
		iMSC_Hor_Cnt ++;

		/* 横マックスの時 */
		if ( iMSC_Hor_Max == iMSC_Hor_Cnt ) {
			iMSC_Hor_Cnt = INTI;
			iMSC_Ver_Cnt ++;

			/* 縦マックスの時 */
			if ( iMSC_Ver_Max == iMSC_Ver_Cnt ) {
				break;
			}
		}
		/* 初期化 */
		iblue		= INTI;
		igreen		= INTI;
		ired		= INTI;
		iMSC_Cnt	= INTI;
		
	}
	/* deta更新 */
	imageData->pImageData = pmosaic;
	
	return SUCCESS;

}
/* ------------------------------------------------------------------------- */
/*              Copyright HAL Collage of Technology & Design                 */
/* ------------------------------------------------------------------------- */
