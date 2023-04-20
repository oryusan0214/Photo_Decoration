/* ------------------------------------------------------------------------- */
/* Intensive.cpp															 */
/* 集約																		 */
/* 集約を行う																 */
/* ------------------------------------------------------------------------- */
/* 番号	更新履歴								日付		   氏名			 */
/* ------------------------------------------------------------------------- */
/* 000000	新規作成							2021/10/23     筈尾　辰也	 */
/* 000001	リファクタリング					2021/11/28	   筈尾  辰也	 */
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
/* Include File																 */
/* ------------------------------------------------------------------------- */
#include "System.h"
#include "Intensive.h"

/* ------------------------------------------------------------------------- */
/* protype																	 */
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
/* 関数名	: senteling														 */
/* 機能名	: センタリングする												 */
/* 機能概要	: 画像をセンタリングして白つめする								 */
/* 引数		: FileData*	: data				: 画像情報[I/O] 				 */
/*			: SINT	 	: hor				: 幅[IN]						 */
/*			: SINT	 	: ver				: 高さ[IN]	 					 */
/* 戻り値	: SINT		:					: エラーチェック[OUT]			 */
/* 作成日	: 2021/10/23		筈尾  辰也		新規作成					 */
/* ------------------------------------------------------------------------- */
SINT senteling( FileData* data, SINT hor, SINT ver );

/* ------------------------------------------------------------------------- */
/* 関数名	: Intensive::exe												 */
/* 機能名	: 実行する														 */
/* 機能概要	: 集約を実行する												 */
/* 引数		: DecorateList* : decorateInfo		: 装飾情報[IN] 				 */
/*			: FileData* 	: imageData			: 画像情報[I/O] 			 */
/*			: FileData*		: secondImageData	: 二枚目の装飾情報[IN]	 	 */
/*			: FileData*		: thirdImageData	: 三枚目の装飾情報[IN]		 */
/*			: FileData*		: fourthImageData	: 四枚目の装飾情報[IN]		 */
/* 戻り値	: SINT			:					: エラーチェック[OUT]		 */
/* 作成日	: 2021/10/23		筈尾  辰也		新規作成					 */
/* ------------------------------------------------------------------------- */
SINT Intensive::exe( DecorateList* decorateInfo, FileData* imageData,
					 FileData* secondImageData, FileData* thirdImageData, FileData* fourthImageData )
{

	SINT ierrorCheck = INTI;					/* エラーチェック			 */

	/* 入力値チェック */

	/* DM */
	if ( decorateInfo == NULL ) {
		printf( "decorateInfo Inter Check  Error In Intensive::exe_decorateList\n" );
		return FAILE;
	}
	if ( imageData == NULL || secondImageData == NULL ) {
		printf( "decorateInfo Inter Check  Error In Intensive::exe_imageData\n" );
		return FAILE;
	}
	/* 装飾種類 */
	if ( !( decorateInfo->decolateKind == TWO_IN_ONE_VER || decorateInfo->decolateKind 
			== TWO_IN_ONE_HOR || decorateInfo->decolateKind == FOUR_IN_ONE ) ) {
		printf( "decorateInfo Inter Check  Error In Intensive::exe_Kind\n" );
		return FAILE;
	}
	/* 装飾設定 */
	if ( decorateInfo->decolatesetup < INTENSIVE_T_MIN || INTENSIVE_F_MAX < decorateInfo->decolatesetup ) {
		printf( "decorateInfo Inter Check  Error In Intensive::exe_Setup\n" );
		return FAILE;
	}
	/* 型式 */
	if ( imageData->pFileHData->sFile_Header_Name != MAGIC_NUMBER || secondImageData->pFileHData->sFile_Header_Name != MAGIC_NUMBER ) {
		printf( "imageData Inter Check Error In Intensive::exe_Type\n" );
		return FAILE;
	}
	/* 大きさ */
	if ( imageData->pInfoHData->uiHeight <= INTI || imageData->pInfoHData->uiWidth <= INTI 
		|| secondImageData->pInfoHData->uiHeight <= INTI || secondImageData->pInfoHData->uiWidth <= INTI ) {
		printf( "imageData Inter Check Error In Intensive::exe_Size\n" );
		return FAILE;
	}

	/* 設定内容に合わせて飛ばす */
	if ( decorateInfo->decolateKind == FOUR_IN_ONE ) {

		ierrorCheck = four_in_one( decorateInfo, imageData, secondImageData, thirdImageData, fourthImageData );
		

	} else if( decorateInfo->decolateKind == TWO_IN_ONE_HOR ) {

		ierrorCheck = two_in_one_hor( decorateInfo, imageData, secondImageData );
	

	}else if( decorateInfo->decolateKind == TWO_IN_ONE_VER ) {

		ierrorCheck = two_in_one_ver( decorateInfo, imageData, secondImageData );

	}
	/*  異常終了*/
	if ( ierrorCheck == FAILE ) {
		printf( "集約処理に失敗しました\n" );
		return FAILE;
	}

	return SUCCESS;
}

/* ------------------------------------------------------------------------- */
/* 関数名	: Intensive::four_in_one										 */
/* 機能名	: 集約する														 */
/* 機能概要	: 四枚の画像を一枚にまとめる									 */
/* 引数		: DecorateList* : decorateInfo		: 装飾情報[IN] 				 */
/*			: FileData* 	: imageData			: 画像情報[I/O] 			 */
/*			: FileData*		: secondImageData	: 二枚目の装飾情報[IN]	 	 */
/*			: FileData*		: thirdImageData	: 三枚目の装飾情報[IN]		 */
/*			: FileData*		: fourthImageData	: 四枚目の装飾情報[IN]		 */
/* 戻り値	: SINT			:					: エラーチェック[OUT]		 */
/* 作成日	: 2021/10/23		筈尾  辰也		新規作成					 */
/* ------------------------------------------------------------------------- */
SINT Intensive::four_in_one( DecorateList* decorateInfo, FileData* imageData,
							 FileData* secondImageData, FileData* thirdImageData, FileData* fourthImageData )
{
	/* 入力値チェック */

	/* DM */
	if ( decorateInfo == NULL ) {
		printf( "decorateInfo Inter Check  Error In Intensive::FIO_decorateList\n" );
		return FAILE;
	}
	if ( imageData == NULL || secondImageData == NULL ) {
		printf( "decorateInfo Inter Check  Error In Intensive::FIO_imageData\n" );
		return FAILE;
	}
	/* 装飾種類 */
	if ( decorateInfo->decolateKind != FOUR_IN_ONE ) {
		printf( "decorateInfo Inter Check  Error In Intensive::TIOV_Kind\n" );
		return FAILE;
	}
	/* 設定値 */
	if ( decorateInfo->decolatesetup < INTENSIVE_F_MIN || INTENSIVE_F_MAX < decorateInfo->decolatesetup ) {
		printf( "decorateInfo Inter Check  Error In Intensive::FIO_Setup\n" );
		return FAILE;
	}
	/* DM */
	if ( thirdImageData == NULL || fourthImageData == NULL ) {
		printf( "decorateInfo Inter Check  Error In Intensive::FIO_imageData\n" );
		return FAILE;
	}
	/* 型式 */
	if ( thirdImageData->pFileHData->sFile_Header_Name != MAGIC_NUMBER || fourthImageData->pFileHData->sFile_Header_Name != MAGIC_NUMBER ) {
		printf( "imageData Inter Check Error In Intensive::FIO_Type\n" );
		return FAILE;
	}
	/* 大きさ */
	if ( thirdImageData->pInfoHData->uiHeight <= INTI || thirdImageData->pInfoHData->uiWidth <= INTI 
		|| fourthImageData->pInfoHData->uiHeight <= INTI || fourthImageData->pInfoHData->uiWidth <= INTI ) {
		printf( "imageData Inter Check Error In Intensive::FIO_Size\n" );
		return FAILE;
	}

	/* 変数宣言 */
	UCHR* pintensive	= NULL;					/* 装飾後の画像データ		 */
	SINT icnt_Ver		= INTI;					/* カウント役				 */
	SINT icnt_Hor		= INTI;					/* カウント役				 */
	SINT idispute[FOUR]	= { INTI,INTI,INTI,INTI };	/* 描写位置				 */
	SINT iver			= INTI;					/* 高さ						 */
	SINT ihor			= INTI;					/* 幅						 */
	SINT ierrorCheck	= INTI;					/* エラーチェック			 */
	SINT imageSize		= INTI;					/* 画像サイズ				 */
	SINT ireference		= INTI;					/* 参照用					 */


	/* 四枚の縦横を比較して最大縦横得る */
	ihor = imageData->pInfoHData->uiWidth;
	iver = imageData->pInfoHData->uiHeight;

	if ( ihor < secondImageData->pInfoHData->uiWidth ) {
		ihor = secondImageData->pInfoHData->uiWidth;
	}
	if ( ihor < thirdImageData->pInfoHData->uiWidth ) {
		ihor = thirdImageData->pInfoHData->uiWidth;
	}
	if ( ihor < fourthImageData->pInfoHData->uiWidth ) {
		ihor = fourthImageData->pInfoHData->uiWidth;
	}

	if ( iver < secondImageData->pInfoHData->uiHeight ) {
		iver = secondImageData->pInfoHData->uiHeight;
	}
	if ( iver < thirdImageData->pInfoHData->uiHeight ) {
		iver = thirdImageData->pInfoHData->uiHeight;
	}
	if ( iver < fourthImageData->pInfoHData->uiHeight ) {
		iver = fourthImageData->pInfoHData->uiHeight;
	}

	/* 画像サイズ取得 */
	imageSize = imageData->pInfoHData->uiHeight * imageData->pInfoHData->uiResolution_Wid * BYTE4 * FOUR;

	/* dynamic memory */
	/* FOUR 追加 */
	pintensive = ( UCHR* )calloc( imageSize , sizeof( UCHR ) );
	/* DM check */
	if ( pintensive == NULL ) {
		printf( "get dynamic error In FIO\n" );
		return FAILE;
	}

	/* 四枚セントリング */
	ierrorCheck = senteling( imageData, ihor, iver );

	/*  異常終了*/
	if (ierrorCheck == FAILE) {
		printf("集約処理に失敗しました\n");
		return FAILE;
	}

	ierrorCheck = senteling( secondImageData, ihor, iver );

	/*  異常終了*/
	if (ierrorCheck == FAILE) {
		printf("集約処理に失敗しました\n");
		return FAILE;
	}

	ierrorCheck = senteling( thirdImageData, ihor, iver );

	/*  異常終了*/
	if (ierrorCheck == FAILE) {
		printf("集約処理に失敗しました\n");
		return FAILE;
	}

	ierrorCheck = senteling( fourthImageData, ihor, iver );
	
	/*  異常終了*/
	if ( ierrorCheck == FAILE ) {
		printf( "集約処理に失敗しました\n" );
		return FAILE;
	}

	/* 描写位置 */
	/*
	decorateInfo->decorateSetup = 1234;
	→idispute[0] = 1
	  idispute[1] = 2
	  idispute[2] = 3
	  idispute[3] = 4 

	  を格納する
	*/
	imageData->pInfoHData->uiHeight = iver;
	imageData->pInfoHData->uiWidth	= ihor;

	/* Setup値を10割りしてあまりをidisputeに入れる */
	for ( icnt_Hor = THIRD; icnt_Hor >= INTI; icnt_Hor -- ) {
		idispute[icnt_Hor]			= decorateInfo->decolatesetup % GET_NUM;
		decorateInfo->decolatesetup	= decorateInfo->decolatesetup / GET_NUM;
	}
	ierrorCheck		= idispute[INTI];
	idispute[INTI]	= idispute[TWO];
	idispute[TWO]	= ierrorCheck;

	ierrorCheck		= idispute[ONE];
	idispute[ONE]	= idispute[THIRD];
	idispute[THIRD] = ierrorCheck;


	/* 集約処理------------------------------- */
	for ( icnt_Ver = INTI; icnt_Ver < imageData->pInfoHData->uiHeight * TWO; icnt_Ver ++ ) {
		
		/* 参照値取得 */
		ireference = icnt_Ver * ( imageData->pInfoHData->uiWidth * TWO * BYTE4 );

		for ( icnt_Hor = INTI; icnt_Hor < imageData->pInfoHData->uiWidth * TWO * BYTE4; icnt_Hor ++ ) {
			
			/* ①②③④の位置に対応した値を入れる */
			decorateInfo->decolatesetup = idispute[( SINT )( icnt_Hor / ( imageData->pInfoHData->uiWidth * BYTE4  ) ) + ( SINT )( icnt_Ver / imageData->pInfoHData->uiHeight ) * TWO ];
			/*
			*	|---------------|
			*	|	①	|	②	|
			*	|		|		|
			*	|---------------|
			*	|	③	|	④	|
			*	|		|		|
			*	|---------------|
			* ①icnt_Hor < imageData->hor * 4 || icnt_Ver < imageData->ver
			* ②icnt_Hor > imageData->hor * 4 || icnt_Ver < imageData->ver
			* ③icnt_Hor < imageData->hor * 4 || icnt_Ver > imageData->ver
			* ④icnt_Hor > imageData->hor * 4 || icnt_Ver > imageData->ver
			*	の４通りに場合分け
			*/
			/* アルファチャンネル飛ばし */
			if ( ( icnt_Hor + BYTE1 ) % BYTE4 == INTI ) {
				/* 各場所対応の画像のPathを進める */
				switch ( decorateInfo->decolatesetup ) {
				case ONE:		imageData->pImageData ++;		break;		/* ① */
				case TWO:		secondImageData->pImageData++;	break;		/* ② */
				case THIRD:		thirdImageData->pImageData ++;	break;		/* ③ */
				case FOUR:		fourthImageData->pImageData ++;	break;		/* ④ */
				default:										break;
				}
				continue;
			}

			/* 各場所対応の画像のデータを格納してPathを進める */
			switch ( decorateInfo->decolatesetup ) {
			case ONE:							/* ① */
				*( pintensive + ireference + icnt_Hor ) = *imageData->pImageData;
				imageData->pImageData ++;
				break;

			case TWO:							/* ② */
				*( pintensive + ireference + icnt_Hor ) = *secondImageData->pImageData;
				secondImageData->pImageData ++;
				break;

			case THIRD:							/* ③ */
				*( pintensive + ireference + icnt_Hor ) = *thirdImageData->pImageData;
				thirdImageData->pImageData ++;
				break;

			case FOUR:							/* ④ */
				*( pintensive + ireference + icnt_Hor ) = *fourthImageData->pImageData;
				fourthImageData->pImageData ++;
				break;		

			default:
				break;
			}			
		}
	}
	/* --------------------------------------- */

	/* 大きさ変更 */
	imageData->pInfoHData->uiWidth			= imageData->pInfoHData->uiWidth  * TWO;
	imageData->pInfoHData->uiHeight			= imageData->pInfoHData->uiHeight * TWO;
	imageData->pImageData	= pintensive;
	return SUCCESS;
}
/* ------------------------------------------------------------------------- */
/* 関数名	: Intensive::two_in_one_ver										 */
/* 機能名	: 集約する														 */
/* 機能概要	: 二枚の画像を一枚にまとめる									 */
/* 引数		: DecorateList* : decorateInfo		: 装飾情報[IN] 				 */
/*			: FileData* 	: imageData			: 画像情報[I/O] 			 */
/*			: FileData*		: secondImageData	: 二枚目の装飾情報[IN]	 	 */
/* 戻り値	: SINT			:					: エラーチェック[OUT]		 */
/* 作成日	: 2021/10/23		筈尾  辰也		新規作成					 */
/* ------------------------------------------------------------------------- */

SINT Intensive::two_in_one_ver( DecorateList* decorateInfo, FileData* imageData, FileData* secondImageData )
{
	/* 入力値チェック */

	/* DM */
	if ( decorateInfo == NULL ) {
		printf( "decorateInfo Inter Check  Error In Intensive::TIOV_decorateList\n" );
		return FAILE;
	}
	if ( imageData == NULL || secondImageData == NULL ) {
		printf( "decorateInfo Inter Check  Error In Intensive::TIOV_imageData\n" );
		return FAILE;
	}
	/* 装飾種類 */
	if ( decorateInfo->decolateKind != TWO_IN_ONE_VER ) {
		printf( "decorateInfo Inter Check  Error In Intensive::TIOV_Kind\n" );
		return FAILE;
	}
	/* 装飾設定 */
	if ( decorateInfo->decolatesetup < INTENSIVE_T_MIN || INTENSIVE_T_MAX < decorateInfo->decolatesetup ) {
		printf( "decorateInfo Inter Check  Error In Intensive::TIOV_Setup\n" );
		return FAILE;
	}

	/* 変数宣言 */
	UCHR* pintensive		= NULL;				/* 装飾後の画像データ		 */
	SINT icnt_Ver			= INTI;				/* カウント役				 */
	SINT icnt_Hor			= INTI;				/* カウント役				 */
	SINT idispute[TWO]		= { INTI,INTI };	/* 描写位置					 */
	SINT iver				= INTI;				/* 高さ						 */
	SINT ihor				= INTI;				/* 幅						 */
	SINT ierrorCheck		= INTI;				/* エラーチェック			 */
	SINT imageSize			= INTI;				/* 画像サイズ				 */
	SINT ireference			= INTI;				/* 参照用					 */


	/* 二枚の画像の最大縦横得る--------------- */
	ihor = imageData->pInfoHData->uiWidth;
	iver = imageData->pInfoHData->uiHeight;

	if ( ihor < secondImageData->pInfoHData->uiWidth ) {
		ihor = secondImageData->pInfoHData->uiWidth;
	}

	if ( iver < secondImageData->pInfoHData->uiHeight ) {
		iver = secondImageData->pInfoHData->uiHeight;
	}
	/* --------------------------------------- */

	/* 画像サイズ取得 */
	imageSize = iver * ihor * BYTE4 * TWO;

	/* dynamic memory */
	/* BYTE4 * を追加 */
	pintensive = ( UCHR* )calloc( imageSize , sizeof( UCHR ) );

	/* DM check */
	if ( pintensive == NULL ) {
		printf( "get dynamic error IN TIO\n" );
		return FAILE;
	}

	/* 二枚セントリング */
	ierrorCheck = senteling( imageData, ihor, iver );

	/*  異常終了*/
	if (ierrorCheck == FAILE) {
		printf("集約処理に失敗しました\n");
		return FAILE;
	}

	ierrorCheck = senteling( secondImageData, ihor, iver );

	/*  異常終了*/
	if (ierrorCheck == FAILE) {
		printf("集約処理に失敗しました\n");
		return FAILE;
	}

	
	/* 描写位置 */
	/*
	decorateInfo->decorateSetup = 12;
	→idispute[0] = 1
	  idispute[1] = 2

	  を格納する
	*/
	/* Setup値を10割りしてあまりをidisputeに入れる */
	imageData->pInfoHData->uiHeight = iver;
	imageData->pInfoHData->uiWidth	= ihor;

	for ( icnt_Hor = ONE; icnt_Hor >= INTI ; icnt_Hor -- ) {
		idispute[icnt_Hor]			= decorateInfo->decolatesetup % GET_NUM;
		decorateInfo->decolatesetup	= decorateInfo->decolatesetup / GET_NUM;
	}
	/* 集約処理------------------------------- */
	for ( icnt_Ver = INTI; icnt_Ver < imageData->pInfoHData->uiHeight * TWO; icnt_Ver ++ ) {

		/* 参照値取得 */
		ireference = icnt_Ver * ( imageData->pInfoHData->uiWidth * BYTE4 );

		for ( icnt_Hor = INTI; icnt_Hor < imageData->pInfoHData->uiWidth * BYTE4; icnt_Hor ++ ) {
			/* ①②の位置に対応した値を入れる */
			decorateInfo->decolatesetup = idispute[( SINT )( icnt_Ver / imageData->pInfoHData->uiHeight )];
			/*
			*	|-------|
			*	|	①	|
			*	|		|
			*	|-------|
			*	|	②	|
			*	|		|
			*	|-------|
			* 
			* ①icnt_Ver < imageData->ver
			* ②icnt_Ver > imageData->ver
			* →２通りに場合分け
			*/
			/* アルファチャンネル飛ばし */

			if ( ( icnt_Hor + BYTE1 ) % BYTE4 == INTI ) {
				/* 各場所対応の画像のPathを進める */
				switch ( decorateInfo->decolatesetup ) {
				case ONE:		secondImageData->pImageData ++;		break;	/* ① */
				case TWO:		imageData->pImageData ++;			break;	/* ② */
				default:											break;
				}
				continue;
			}
			switch ( decorateInfo->decolatesetup ) {
				/* 各場所対応の画像のデータを格納してPathを進める */
			case ONE:							/* ① */
				*( pintensive + ireference + icnt_Hor ) = *secondImageData->pImageData;
				secondImageData->pImageData ++;
				break;

			case TWO:							/* ② */
				*( pintensive + ireference + icnt_Hor ) = *imageData->pImageData;
				imageData->pImageData ++;
				break;

			default:
				break;
			}
		}
	}
	/* 大きさ変更 */
	imageData->pInfoHData->uiHeight			= imageData->pInfoHData->uiHeight * TWO;

	imageData->pImageData	= pintensive;

	return SUCCESS;
}
/* ------------------------------------------------------------------------- */
/* 関数名	: Intensive::two_in_one_hor										 */
/* 機能名	: 集約する														 */
/* 機能概要	: 四枚の画像を一枚にまとめる									 */
/* 引数		: DecorateList* : decorateInfo		: 装飾情報[IN] 				 */
/*			: FileData* 	: imageData			: 画像情報[I/O] 			 */
/*			: FileData*		: secondImageData	: 二枚目の装飾情報[IN]	 	 */
/* 戻り値	: SINT			:					: エラーチェック[OUT]		 */
/* 作成日	: 2021/10/23		筈尾  辰也		新規作成					 */
/* ------------------------------------------------------------------------- */
SINT Intensive::two_in_one_hor( DecorateList* decorateInfo, FileData* imageData, FileData* secondImageData )
{
	/* 入力値チェック */

	/* DM */
	if ( decorateInfo == NULL ) {
		printf( "decorateInfo Inter Check  Error In Intensive::TIOH_decorateList\n" );
		return FAILE;
	}
	if ( imageData == NULL || secondImageData == NULL ) {
		printf( "decorateInfo Inter Check  Error In Intensive::TIOH_imageData\n" );
		return FAILE;
	}
	/* 装飾種類 */
	if ( decorateInfo->decolateKind != TWO_IN_ONE_HOR ) {
		printf( "decorateInfo Inter Check  Error In Intensive::TIOH_Kind\n" );
		return FAILE;
	}
	/* 装飾設定 */
	if ( decorateInfo->decolatesetup < INTENSIVE_T_MIN || INTENSIVE_T_MAX < decorateInfo->decolatesetup ) {
		printf( "decorateInfo Inter Check  Error In Intensive::TIOH_Setup\n" );
		return FAILE;
	}

	/* 変数宣言 */
	UCHR* pintensive		= NULL;				/* 装飾後の画像データ		 */
	SINT icnt_Ver			= INTI;				/* カウント役				 */
	SINT icnt_Hor			= INTI;				/* カウント役				 */
	SINT idispute[TWO]		= { INTI,INTI };	/* 描写位置					 */
	SINT iver				= INTI;				/* 高さ						 */
	SINT ihor				= INTI;				/* 幅						 */
	SINT ierrorCheck		= INTI;				/* エラーチェック			 */
	SINT imageSize			= INTI;				/* 画像サイズ				 */
	SINT ireference			= INTI;				/* 参照用					 */


	/* 二枚の画像の最大縦横得る--------------- */
	ihor = imageData->pInfoHData->uiWidth;
	iver = imageData->pInfoHData->uiHeight;

	if ( ihor < secondImageData->pInfoHData->uiWidth ) {
		ihor = secondImageData->pInfoHData->uiWidth;
	}

	if ( iver < secondImageData->pInfoHData->uiHeight ) {
		iver = secondImageData->pInfoHData->uiHeight;
	}
	/* --------------------------------------- */

	/* 画像サイズ取得 */
	imageSize = imageData->pInfoHData->uiHeight * imageData->pInfoHData->uiWidth * TWO * BYTE4;

	/* dynamic memory */
	pintensive = ( UCHR* )calloc( imageSize ,sizeof( UCHR ) );
	/* DM check */
	if ( pintensive == NULL ) {
		printf( "get dynamic error IN TIO\n" );
		return FAILE;
	}

	/* 二枚セントリング */
	ierrorCheck = senteling( imageData, ihor, iver );

	/*  異常終了*/
	if (ierrorCheck == FAILE) {
		printf("集約処理に失敗しました\n");
		return FAILE;
	}

	ierrorCheck = senteling( secondImageData, ihor, iver );

	/*  異常終了*/
	if (ierrorCheck == FAILE) {
		printf("集約処理に失敗しました\n");
		return FAILE;
	}

	/* 描写位置 */
	/*
	decorateInfo->decorateSetup = 12;
	→idispute[0] = 1
	  idispute[1] = 2

	  を格納する
	*/
	/* Setup値を10割りしてあまりをidisputeに入れる */
	imageData->pInfoHData->uiHeight = iver;
	imageData->pInfoHData->uiWidth	= ihor;

	for ( icnt_Hor = ONE; icnt_Hor >= INTI; icnt_Hor -- ) {
		idispute[icnt_Hor]			= decorateInfo->decolatesetup % GET_NUM;
		decorateInfo->decolatesetup	= decorateInfo->decolatesetup / GET_NUM;
	}
	/* 集約処理------------------------------- */
	for ( icnt_Ver = INTI; icnt_Ver < imageData->pInfoHData->uiHeight ; icnt_Ver ++ ) {

		/* 参照値取得 */
		ireference =  icnt_Ver * ( imageData->pInfoHData->uiWidth * TWO * BYTE4 );

		for ( icnt_Hor = INTI; icnt_Hor < imageData->pInfoHData->uiWidth * TWO * BYTE4; icnt_Hor ++ ) {

			/* ①②の位置に対応した値を入れる */
			decorateInfo->decolatesetup = idispute[( SINT )( icnt_Hor / ( imageData->pInfoHData->uiWidth * FOUR ) )];
			/*
			*	|-------|-------|
			*	|	①	|	②	|
			*	|		|		|
			*	|-------|-------|
			* 
			* ①icnt_Hor < imageData->hor
			* ②icnt_Hor > imageData->hor
			* 
			* →２通りに場合分け
			*/
			/* アルファチャンネル飛ばし */
			if ( ( icnt_Hor + BYTE1 ) % BYTE4 == INTI ) {
				/* 各場所対応の画像のPathを進める */
				switch ( decorateInfo->decolatesetup ) {
				case ONE:	imageData->pImageData ++;		break;	/* ① */
				case TWO:	secondImageData->pImageData ++;	break;	/* ② */
				default:										break;
				}
				continue;
			}
			switch ( decorateInfo->decolatesetup ) {
				/* 各場所対応の画像のデータを格納してPathを進める */
			case ONE:							/* ① */
				*( pintensive + ireference + icnt_Hor ) = *imageData->pImageData;
				imageData->pImageData ++;
				break;

			case TWO:							/* ② */
				*( pintensive + ireference + icnt_Hor ) = *secondImageData->pImageData;
				secondImageData->pImageData ++;
				break;

			default:
				break;
			}
		}
	}
	/* --------------------------------------- */
	/* 大きさ変更 */
	imageData->pInfoHData->uiWidth			= imageData->pInfoHData->uiWidth * TWO;

	imageData->pImageData	= pintensive;
	return SUCCESS;
}
/* ------------------------------------------------------------------------- */
/* 関数名	: senteling														 */
/* 機能名	: センタリングする												 */
/* 機能概要	: センタリングする												 */
/* 引数		: FileData* 	: imageData			: 画像情報[I/O] 			 */
/*			: SINT		 	: ver				: 高さ			 			 */
/*			: SINT		 	: hor				: 幅			 			 */
/* 戻り値	: SINT			:					: エラーチェック[OUT]		 */
/* 作成日	: 2021/10/23		筈尾  辰也		新規作成					 */
/* ------------------------------------------------------------------------- */
//
SINT senteling(FileData* Data, SINT hor, SINT ver)
{

	/* DM */
	if ( Data == NULL ) {
		printf( "decorateInfo Inter Check  Error In Intensive::senterlong_Data\n" );
		return FAILE;
	}
	if ( hor == NULL || ver == NULL ) {
		printf( "decorateInfo Inter Check  Error In Intensive::senterling_Long\n" );
		return FAILE;
	}


	/* 変数宣言 */
	SINT iverCnt = INTI;					/* カウント役				 */
	SINT ihorCnt = INTI;					/* カウント役				 */
	UCHR* pnewData = NULL;					/* 装飾後の画像データ		 */
	SINT imageSize = INTI;					/* 画像サイズ				 */
	SINT ireference = INTI;					/* 参照用					 */
	SINT ispaceTop = INTI;					/* 縦幅の上部判定数			 */
	SINT ispaceBottum = INTI;					/* 縦幅の下部判定数			 */
	SINT ispaceLeft = INTI;					/* 横幅の左部判定数			 */
	SINT ispaceRight = INTI;					/* 横幅の右部判定数			 */

	/* 画像サイズ取得 */
	imageSize = hor * ver * BYTE4;

	/* 場所位置取得 */
	ispaceTop = ((ver - Data->pInfoHData->uiHeight) / TWO);
	ispaceBottum = ((ver + Data->pInfoHData->uiHeight) / TWO);
	ispaceLeft = ((hor - Data->pInfoHData->uiWidth) / TWO) * BYTE4;
	ispaceRight = ((hor + Data->pInfoHData->uiWidth) / TWO) * BYTE4;

	/* get DM */
	pnewData = (UCHR*)calloc(imageSize, sizeof(UCHR));
	/* dm check */
	if (pnewData == NULL) {
		printf("get dynamic error In Senterling\n");
		return FAILE;
	}


	/* 縦横最大ならセンタリング不要 */
	if (Data->pInfoHData->uiWidth == hor && Data->pInfoHData->uiHeight == ver) {
		return SUCCESS;
	}
	else {
		/* 値変更 */
		Data->pInfoHData->uiHeight = ver;
		Data->pInfoHData->uiWidth = hor;

		/* センタリング処理 */
		/*
		*	|---------------| -
		*	|				| 1⃣(ver - Data->ver) / 2
		*	|	|-------|	| -
		*	|	|		|	| 2⃣Data->ver
		*	|	|-------|	| -
		*	|				| 3⃣(ver - Data->ver - 1) / 2
		*	|---------------| -
		*
		*	|①	|	②	|③	|
		* ① (hor - Data->hor) /2
		* ② Data->hor
		* ③ (hor - Data->hor -1) / 2
		* →2⃣②のときのみData読み込み、それ以外はしろつめ
		*/

		for (iverCnt = INTI; iverCnt < ver; iverCnt++) {

			/* 参照値取得 */
			ireference = iverCnt * Data->pInfoHData->uiWidth * BYTE4;

			for (ihorCnt = INTI; ihorCnt < hor * BYTE4; ihorCnt++) {

				/* 画像位置の処理 */
				if (ispaceTop <= iverCnt && iverCnt < ispaceBottum) {
					if (ispaceLeft <= ihorCnt && ihorCnt < ispaceRight) {

						/* アルファチャンネル飛ばし */
						if ((ihorCnt + BYTE1) % BYTE4 == INTI) {
							Data->pImageData++;
							continue;
						}

						*(pnewData + ireference + ihorCnt) = *Data->pImageData;
						Data->pImageData++;
						continue;
					}
				}
				/* アルファチャンネル飛ばし */
				if ((ihorCnt + BYTE1) % BYTE4 == INTI) {
					continue;
				}
				/* 白詰め処理 */
				*(pnewData + ireference + ihorCnt) = WHITE;
			}
		}
	}
	/* 画像データ更新 */
	Data->pImageData = pnewData;

	return SUCCESS;
}
/* ------------------------------------------------------------------------- */
/*              Copyright HAL Collage of Technology & Design                 */
/* ------------------------------------------------------------------------- */
