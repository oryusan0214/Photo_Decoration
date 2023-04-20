/* ------------------------------------------------------------------------- */
/* DataInputer.cpp															 */
/* 入力処理																	 */
/* 装飾内容を入力															 */
/* ------------------------------------------------------------------------- */
/* 番号	更新履歴								日付		   氏名			 */
/* ------------------------------------------------------------------------- */
/* 000000	新規作成							2021/10/28     筈尾　辰也	 */
/* 000001	リファクタリング					2021/12/02	   筈尾  辰也	 */
/* ------------------------------------------------------------------------- */
/* Include File																 */
/* ------------------------------------------------------------------------- */
#include "DataInputer.h"

/* ------------------------------------------------------------------------- */
/* 関数名	: DataInputer::DataInputer										 */
/* 機能名	: コンストラクタ												 */
/* 機能概要	: データ初期化等												 */
/* 引数		: なし															 */
/* 戻り値	: void															 */
/* 作成日	: 2021/10/28		筈尾  辰也		新規作成					 */
/* ------------------------------------------------------------------------- */
DataInputer::DataInputer( void ) 
{
	/* 初期化 & DynamicMemory 確保-------------------- */
	idecorateKind	= NULL;						/* 装飾種類					 */
	idecorateSetup	= NULL;						/* 装飾設定					 */

	idecorateKind	= ( SINT* )calloc( ONE, sizeof( SINT ) );
	idecorateSetup	= ( SINT* )calloc( ONE, sizeof( SINT ) );
	/* --------------------------------------- */

	/* DM確保失敗 */
	if( idecorateKind == NULL || idecorateSetup == NULL ) {
		printf( "Get Dynamic Error In DataInputer::DataInputer\n" );
	}
	//
}

/* ------------------------------------------------------------------------- */
/* 関数名	: IndependentProcessing::~IndependentProcessing					 */
/* 機能名	: デストラクタ													 */
/* 機能概要	: 確保している領域の解放										 */
/* 引数		: なし															 */
/* 戻り値	: void															 */
/* 作成日	: 2021/10/28		筈尾  辰也		新規作成					 */
/* ------------------------------------------------------------------------- */
DataInputer::~DataInputer( void )
{

	/* DM解放--------------------------------- */

	/* 重複開放対策 */
	if ( idecorateKind != NULL && idecorateKind != idecorateSetup ) {
		free( idecorateKind );
	}
	if ( idecorateSetup != NULL ) {
		free( idecorateSetup );
	}
	/* --------------------------------------- */
}

/* ------------------------------------------------------------------------- */
/* 関数名	: DataInputer::get_first										 */
/* 機能名	: 最初の装飾情報を所得する										 */
/* 機能概要	: 情報入力処理を実行する										 */
/* 引数		: SINT* 	: idecorateKind		: 装飾種類情報[I/O] 			 */
/*			: SINT* 	: idecorateSetup	: 装飾設定情報[I/O]				 */
/*			: SCHR*		: imageData			: 画像Path[IN]					 */
/*			: SCHR* 	: secondImageData	: 二枚目の装飾Path[IN] 			 */
/*			: SCHR* 	: thirdImageData	: 三枚目の装飾Path[IN] 			 */
/*			: SCHR* 	: fourthImageData	: 四枚目の装飾Path[IN]	 		 */
/* 戻り値	: SINT		:					: エラーチェック[OUT]			 */
/* 作成日	: 2021/10/29		筈尾  辰也		新規作成					 */
/* ------------------------------------------------------------------------- */
SINT DataInputer::get_first( SINT* idecorateKind, SINT* idecorateSetup, SCHR* orizinalImagePath,
							 SCHR* secondImagePath, SCHR* thirdImagePath, SCHR* fourthImagePath )
{

	/* 引数値チェック------------------------- */

	/* DM確認 */
	if ( idecorateKind == NULL ) {
		printf( "decorateInfo Inter Check  Error DecorateInputer::get_first_Kind\n" );
		return FAILE;
	}
	if ( idecorateSetup == NULL ) {
		printf( "decorateInfo Inter Check  Error DecorateInputer::get_first_Setup\n" );
		return FAILE;
	}
	if ( orizinalImagePath == NULL ) {
		printf( "decorateInfo Inter Check  Error DecorateInputer::get_first_Path\n" );
		return FAILE;
	}
	/* --------------------------------------- */

	SINT ierrorCheck = INTI;					/* エラーチェック			 */

	/* 装飾種類入力--------------------------- */
	printf( "装飾方法を入力してください\n" );
	printf( "1 画像回転,2 画像反転,3 色反転,4 セピア,5 モザイク,6 拡大・縮小\n" );
	printf( "7 色変換,8 複写,9 縦集約(2 in 1),10 横集約(2 in 1),11 集約(4 in 1),12 オーバーレイ,13 取り消し,14 終了\n" );
	rewind( stdin );
	( void )scanf( "%d", idecorateKind );

	/* 範囲外再入力 */
	while ( *idecorateKind < ROTATE || FIN < *idecorateKind ) {
		printf( "範囲外再入力\n" );
		rewind( stdin );
		( void )scanf( "%d", idecorateKind );
	}
	/* --------------------------------------- */

	/* 種類ごとの設定入力--------------------- */
	switch ( *idecorateKind ) {

	case ROTATE:								/* 回転選択時				 */

		ierrorCheck = Rotate( idecorateSetup );break;

	case IMAGEINVERT:							/* 画像反転選択時			 */

		ierrorCheck = ImageInvert( idecorateSetup ); break;

	case SEPIA:									/* セピア選択時				 */

		ierrorCheck = Sepia( idecorateSetup ); break;

	case MOSAIC:								/* モザイク選択時			 */

		ierrorCheck = Mosaic( idecorateSetup ); break;

	case MAGNIFICATION:							/* 倍率選択時				 */

		ierrorCheck = Magnification( idecorateSetup ); break;

	case COLORCONVERT:							/* 色変換選択時				 */

		ierrorCheck = ColorConvert( idecorateSetup ); break;

	case TWO_IN_ONE_VER:						/* 集約( 縦2枚 )選択時		 */

		ierrorCheck = Two_In_One_Ver( idecorateSetup, orizinalImagePath, secondImagePath );
		break;

	case TWO_IN_ONE_HOR:						/* 集約( 横2枚 )選択時		 */

		ierrorCheck = Two_In_One_Hor( idecorateSetup, orizinalImagePath, secondImagePath );
		break;

	case FOUR_IN_ONE:							/* 集約( 4枚 )選択時		 */

		ierrorCheck = Four_In_One( idecorateSetup, orizinalImagePath,
			secondImagePath, thirdImagePath, fourthImagePath );
		break;

	case OVERLAY:								/* オーバーレイ選択時		 */

		ierrorCheck = Overlay( idecorateSetup, secondImagePath ); break;

	case RESTART:

		ierrorCheck = Restart( idecorateSetup );
		break;

	case FIN:

		ierrorCheck = Fin( idecorateSetup );
		break;

	default:									/* 設定不要種類選択時		 */

		/* 設定を　ZEROにする */
		*idecorateSetup = INTI; break;
	}

	if ( ierrorCheck == FAILE ) {
		printf( "装飾情報入力処理でエラーが発生しました\n" );
		return FAILE;
	}

	return SUCCESS;
}

/* ------------------------------------------------------------------------- */
/* 関数名	: DataInputer::get												 */
/* 機能名	: 装飾情報を所得する											 */
/* 機能概要	: 情報入力処理を実行する										 */
/* 引数		: SINT* 	: idecorateKind		: 装飾種類情報[I/O]				 */
/*			: SINT*		: idecorateSetup	: 装飾設定情報[I/O]				 */
/*			: SCHR* 	: imagePath			: 画像Path[IN] 					 */
/*			: SCHR* 	: secondImagePath	: 二枚目の装飾Path[IN]	 		 */
/*			: SCHR* 	: thirdImagePath	: 三枚目の装飾Path[IN]			 */
/*			: SCHR* 	: fourthImagePath	: 四枚目の装飾Path[IN] 			 */
/* 戻り値	: SINT		:					: エラーチェック[OUT]			 */
/* 作成日	: 2021/10/29		筈尾  辰也		新規作成					 */
/* ------------------------------------------------------------------------- */
SINT DataInputer::get( SINT* idecorateKind, SINT* idecorateSetup, SCHR* orizinalImagePath,
					   SCHR* secondImagePath, SCHR* thirdImagePath, SCHR* fourthImagePath ) {

	/* 引数値チェック------------------------- */

	/* DM確認 */
	if ( idecorateKind == NULL) {
		printf("decorateInfo Inter Check  Error DecorateInputer::get_Kind\n");
		return FAILE;
	}
	if ( idecorateSetup == NULL ) {
		printf( "decorateInfo Inter Check  Error DecorateInputer::get_Setup\n" );
		return FAILE;
	}
	if ( orizinalImagePath == NULL ) {
		printf( "decorateInfo Inter Check  Error DecorateInputer::get_Path\n" );
		return FAILE;
	}
	/* --------------------------------------- */

	SINT ierrorCheck = INTI;					/* エラーチェック			 */

	/* 装飾種類入力--------------------------- */
	printf( "装飾方法を入力してください\n" );
	printf( "1 画像回転,2 画像反転,3 色反転,4 セピア,5 モザイク,6 拡大・縮小\n" );
	printf( "7 色変換,8 取消,9 終了\n" );
	rewind( stdin );
	( void )scanf( "%d", idecorateKind );

	/* 範囲外再入力 */
	/* 二回目以降は単独処理がなくなるので、単独初めのCOPYが終了 */
	while ( *idecorateKind < ROTATE || TWO_IN_ONE_VER < *idecorateKind ) {
		printf( "範囲外再入力\n" );
		rewind( stdin );
		( void )scanf( "%d", idecorateKind );
	}

	/* --------------------------------------- */

	/* 種類ごとの設定入力--------------------- */
	switch ( *idecorateKind ) {

	case ROTATE:								/* 回転選択時				 */

		ierrorCheck = Rotate( idecorateSetup ); break;

	case IMAGEINVERT:							/* 画像反転選択時			 */
		
		ierrorCheck = ImageInvert( idecorateSetup ); break;

	case SEPIA:									/* セピア選択時				 */
		
		ierrorCheck = Sepia( idecorateSetup ); break;

	case MOSAIC:								/* モザイク選択時			 */
		
		ierrorCheck = Mosaic( idecorateSetup ); break;

	case MAGNIFICATION:							/* 拡大縮小選択時			 */
		
		ierrorCheck = Magnification( idecorateSetup ); break;

	case COLORCONVERT:							/* 色変換選択時				 */
		
		ierrorCheck = ColorConvert( idecorateSetup ); break;

	case COPY:									/* 取消処理 */

		ierrorCheck = Restart( idecorateSetup );break;

	case TWO_IN_ONE_VER:						/* 終了処理 */

		ierrorCheck = Fin( idecorateSetup );break;

	default:									/* 設定不要種類選択時		 */
		
		/* 設定を　ZEROにする */
		*idecorateSetup = INTI; break;
	}
	if ( ierrorCheck == FAILE ) {
		printf( "装飾情報入力処理でエラーが発生しました\n" );
		return FAILE;
	}

	return SUCCESS;
}

/* ------------------------------------------------------------------------- */
/* 関数名	: DataInputer::Rotate											 */
/* 機能名	: 装飾設定を所得する											 */
/* 機能概要	: 情報入力処理を実行する										 */
/* 引数		: SINT* 	: idecorateSetup	: 装飾設定情報[I/O]				 */
/* 戻り値	: SINT		:					: エラーチェック[OUT]			 */
/* 作成日	: 2021/10/29		筈尾  辰也		新規作成					 */
/* ------------------------------------------------------------------------- */

SINT DataInputer::Rotate( SINT* idecorateSetup )
{

	/* 引数値チェック */
	if ( idecorateSetup == NULL ) {
		printf( "decorateInfo Inter Check  Error DecorateInputer::Rotate_Setup\n" );
		return FAILE;
	}

	/* 画像設定入力 -------------------------- */
	printf( "画像回転が選択されました\n何度回転しますか、1 90度,2 180度,3 270度,4 360度\n" );
	rewind( stdin );
	( void )scanf( "%d", idecorateSetup );

	/* 範囲外再入力 */
	while ( *idecorateSetup < ROTATE_MIN || ROTATE_MAX < *idecorateSetup ) {
		printf( "範囲外再入力\n" );
		rewind( stdin );
		( void )scanf( "%d", idecorateSetup );
	}
	/* --------------------------------------- */
	return SUCCESS;
}
/* ------------------------------------------------------------------------- */
/* 関数名	: DataInputer::ImageInvert										 */
/* 機能名	: 装飾設定を所得する											 */
/* 機能概要	: 情報入力処理を実行する										 */
/* 引数		: SINT* 	: idecorateSetup	: 装飾設定情報[I/O]				 */
/* 戻り値	: SINT		:					: エラーチェック[OUT]			 */
/* 作成日	: 2021/10/29		筈尾  辰也		新規作成					 */
/* ------------------------------------------------------------------------- */
SINT DataInputer::ImageInvert( SINT* idecorateSetup )
{

	/* 引数値チェック */
	if ( idecorateSetup == NULL ) {
		printf( "decorateInfo Inter Check  Error DecorateInputer::ImageInvert_Setup\n" );
		return FAILE;
	}

	/* 画像設定入力 -------------------------- */
	printf( "画像反転が選択されました\nどう反転しますか、1 上下,2 左右\n" );
	rewind( stdin );
	( void )scanf( "%d", idecorateSetup );

	/* 範囲外再入力 */
	while ( *idecorateSetup < IMAGE_INVERT_MIN || IMAGE_INVERT_MAX < *idecorateSetup ) {
		printf( "範囲外再入力\n" );
		rewind( stdin );
		( void )scanf( "%d", idecorateSetup );
	}
	/* --------------------------------------- */

	return SUCCESS;
}
/* ------------------------------------------------------------------------- */
/* 関数名	: DataInputer::Sepia											 */
/* 機能名	: 装飾設定を所得する											 */
/* 機能概要	: 情報入力処理を実行する										 */
/* 引数		: SINT* 	: idecorateSetup	: 装飾設定情報[I/O]				 */
/* 戻り値	: SINT		:					: エラーチェック[OUT]			 */
/* 作成日	: 2021/10/29		筈尾  辰也		新規作成					 */
/* ------------------------------------------------------------------------- */
SINT DataInputer::Sepia( SINT* idecorateSetup )
{
	/* 引数値チェック */
	if ( idecorateSetup == NULL ) {
		printf( "decorateInfo Inter Check  Error DecorateInputer::Sepia_Setup\n" );
		return FAILE;
	}

	/* 画像設定入力 -------------------------- */
	printf( "セピアが選択されました\n濃度はどうしますか、1 濃い,2 普通,3 薄い\n" );
	rewind( stdin );
	( void )scanf( "%d", idecorateSetup );

	/* 範囲外再入力 */
	while ( *idecorateSetup < SEPIA_MIN || SEPIA_MAX < *idecorateSetup ) {
		printf( "範囲外再入力\n" );
		rewind( stdin );
		( void )scanf( "%d", idecorateSetup );
	}
	/* --------------------------------------- */

	return SUCCESS;
}
/* ------------------------------------------------------------------------- */
/* 関数名	: DataInputer::Mosaic											 */
/* 機能名	: 装飾設定を所得する											 */
/* 機能概要	: 情報入力処理を実行する										 */
/* 引数		: SINT* 	: idecorateSetup	: 装飾設定情報[I/O]				 */
/* 戻り値	: SINT		:					: エラーチェック[OUT]			 */
/* 作成日	: 2021/10/29		筈尾  辰也		新規作成					 */
/* ------------------------------------------------------------------------- */
SINT DataInputer::Mosaic( SINT* idecorateSetup )
{

	/* 引数値チェック */
	if ( idecorateSetup == NULL ) {
		printf( "decorateInfo Inter Check  Error DecorateInputer::Mosaic_Setup\n" );
		return FAILE;
	}

	/* 画像設定入力 -------------------------- */
	printf( "モザイクが選択されました\n濃度はどうしますか？ (1-辺の長さ)\n" );
	rewind( stdin );
	( void )scanf( "%d", idecorateSetup );

	/* 範囲外再入力 */
	while ( *idecorateSetup < MOSAIC_MIN ) {
		printf( "範囲外再入力\n" );
		rewind( stdin );
		( void )scanf( "%d", idecorateSetup );
	}
	/* --------------------------------------- */
	return SUCCESS;
}
/* ------------------------------------------------------------------------- */
/* 関数名	: DataInputer::Magnification									 */
/* 機能名	: 装飾設定を所得する											 */
/* 機能概要	: 情報入力処理を実行する										 */
/* 引数		: SINT* 	: idecorateSetup	: 装飾設定情報[I/O]				 */
/* 戻り値	: SINT		:					: エラーチェック[OUT]			 */
/* 作成日	: 2021/10/29		筈尾  辰也		新規作成					 */
/* ------------------------------------------------------------------------- */
SINT DataInputer::Magnification( SINT* idecorateSetup )
{
	
	/* 引数値チェック */
	if ( idecorateSetup == NULL ) {
		printf( "decorateInfo Inter Check  Error DecorateInputer::Mabnification_Setup\n" );
		return FAILE;
	}

	/* 変数宣言 */
	FLOT fdecorateSetup = INTI;					/* 設定の小数値まで取るための変数 */

	/* 画像設定入力 -------------------------- */
	/* 使用上、小数第一位までの入力が許可されているので、入力値を10倍にしてSINT型に保存 */
	printf( "倍率が選択されました\n率はどうしますか？ (0.1-1000)\n※小数点第二位以下は切り落とされます\n" );
	rewind( stdin );
	( void )scanf( "%f", &fdecorateSetup );

	/* 10倍化 */
	fdecorateSetup = ( fdecorateSetup * TEN );
	*idecorateSetup = ( SINT )fdecorateSetup;

	/* 範囲外再入力 */
	while ( *idecorateSetup < MAGN_MIN || MAGN_MAX < *idecorateSetup ) {
		printf( "範囲外再入力\n" );
		rewind( stdin );
		( void )scanf( "%d", idecorateSetup );
	}
	/* --------------------------------------- */
	return SUCCESS;
}
/* ------------------------------------------------------------------------- */
/* 関数名	: DataInputer::ColorConvert										 */
/* 機能名	: 装飾設定を所得する											 */
/* 機能概要	: 情報入力処理を実行する										 */
/* 引数		: SINT* 	: idecorateSetup	: 装飾設定情報[I/O]				 */
/* 戻り値	: SINT		:					: エラーチェック[OUT]			 */
/* 作成日	: 2021/10/29		筈尾  辰也		新規作成					 */
/* ------------------------------------------------------------------------- */
SINT DataInputer::ColorConvert( SINT* idecorateSetup )
{

	/* 引数値チェック */
	if ( idecorateSetup == NULL ) {
		printf( "decorateInfo Inter Check  Error DecorateInputer::ColorConvert_Setup\n" );
		return FAILE;
	}

	/* 画像設定入力 -------------------------- */
	printf( "色変換が選択されましたbitどうしますか？\n1 2bit,2 8bit,3 24bit\n" );
	rewind( stdin );
	( void )scanf( "%d", idecorateSetup );

	/* 範囲外再入力 */
	while ( *idecorateSetup < COLOR_CONVERT_MIN || COLOR_CONVERT_MAX < *idecorateSetup ) {
		printf( "範囲外再入力\n" );
		rewind( stdin );
		( void )scanf( "%d", idecorateSetup );
	}
	/* --------------------------------------- */
	switch (*idecorateSetup) {
	case 1: *idecorateSetup = 1; break;
	case 2: *idecorateSetup = 8; break;
	case 3: *idecorateSetup = 24; break;

	}
	return SUCCESS;
}
/* ------------------------------------------------------------------------- */
/* 関数名	: DataInputer::Two_In_One_Ver									 */
/* 機能名	: 装飾設定を所得する											 */
/* 機能概要	: 情報入力処理を実行する										 */
/* 引数		: SINT* 	: idecorateSetup	: 装飾設定情報[I/O]				 */
/*			: SCHR* 	: orizinalImagePath	: 画像Path情報[I/O]				 */
/* 			: SCHR* 	: secondImagePath	: 画像Path情報[I/O]				 */
/* 戻り値	: SINT		:					: エラーチェック[OUT]			 */
/* 作成日	: 2021/10/29		筈尾  辰也		新規作成					 */
/* ------------------------------------------------------------------------- */
SINT DataInputer::Two_In_One_Ver( SINT* idecorateSetup, SCHR* orizinalImagePath, SCHR* secondImagePath )
{

	/* 引数値チェック */
	if ( idecorateSetup == NULL ) {
		printf( "decorateInfo Inter Check  Error DecorateInputer::TIOV_SETup\n" );
		return FAILE;
	}
	if ( orizinalImagePath == NULL ) {
		printf( "decorateInfo Inter Check  Error DecorateInputer::TIOV_Path\n" );
		return FAILE;
	}

	/* 変数宣言 */
	SINT icntTIO			= INTI;				/* カウント役				 */
	SINT icntTIO_Check		= INTI;				/* カウント役				 */
	SINT iboxTIO[TWO]		= { INTI,INTI };	/* 画像位置の入力値の格納庫	 */

	/* 画像設定入力 ------------------------------------ */
	for ( icntTIO = INTI; icntTIO < TWO; icntTIO ++ ) {
		printf( "|--------------|\n" );
		printf( "|				|\n" );
		printf( "|				|\n" );
		printf( "|		①		|\n" );
		printf( "|				|\n" );
		printf( "|				|\n" );
		printf( "|--------------|\n" );
		printf( "|				|\n" );
		printf( "|				|\n" );
		printf( "|		②		|\n" );
		printf( "|				|\n" );
		printf( "|				|\n" );
		printf( "|--------------|\n ");

		printf( "%d枚目の画像をどこに配置しますか？\n", icntTIO + ONE );

		rewind( stdin );
		( void )scanf( "%d", &iboxTIO[icntTIO] );

		/* ①の画像IDを10の位、②の画像IDを1の位に格納 */

		
		for ( icntTIO_Check = icntTIO; INTI < icntTIO_Check; icntTIO_Check -- ) {
			if (iboxTIO[icntTIO] == iboxTIO[icntTIO - icntTIO_Check] ) {
				iboxTIO[icntTIO] = INTI;
			}
		}
		
		/* 入力値チェック -------------------- */
		/* 入力値が範囲外 */
		while ( iboxTIO[icntTIO] < ONE || TWO < iboxTIO[icntTIO] ) {
			printf( "範囲外再入力\n" );
			rewind( stdin );
			( void )scanf( "%d", &iboxTIO[icntTIO] );

			/* 入力値がすでに入力されている */
			
			for ( icntTIO_Check = icntTIO; INTI < icntTIO_Check; icntTIO_Check -- ) {
				if ( iboxTIO[icntTIO] == iboxTIO[icntTIO - icntTIO_Check] ) {
					iboxTIO[icntTIO] = INTI;
				}
			}
		}
		/* -------------------------------------- */
		/* --------------------------------------------- */
		*idecorateSetup = *idecorateSetup * TEN;
		*idecorateSetup = *idecorateSetup + iboxTIO[icntTIO];
	}
	return SUCCESS;
}
/* ------------------------------------------------------------------------- */
/* 関数名	: DataInputer::Two_In_One_Hor									 */
/* 機能名	: 装飾設定を所得する											 */
/* 機能概要	: 情報入力処理を実行する										 */
/* 引数		: SINT* 	: idecorateSetup	: 装飾設定情報[I/O]				 */
/*			: SCHR* 	: orizinalImagePath	: 画像Path情報[I/O]				 */
/* 			: SCHR* 	: secondImagePath	: 画像Path情報[I/O]				 */
/* 戻り値	: SINT		:					: エラーチェック[OUT]			 */
/* 作成日	: 2021/10/29		筈尾  辰也		新規作成					 */
/* ------------------------------------------------------------------------- */
SINT DataInputer::Two_In_One_Hor( SINT* idecorateSetup, SCHR* orizinalImagePath, SCHR* secondImagePath )
{

	/* 引数値チェック */
	if ( idecorateSetup == NULL ) {
		printf( "decorateInfo Inter Check  Error DecorateInputer::TIOH_Setup\n" );
		return FAILE;
	}
	if ( orizinalImagePath == NULL ) {
		printf( "decorateInfo Inter Check  Error DecorateInputer::TIOH_Path\n" );
		return FAILE;
	}

	/* 変数宣言 */
	SINT icntTIO			= INTI;				/* カウント役				 */
	SINT icntTIO_Check		= INTI;				/* カウント役				 */
	SINT iboxTIO[TWO]		= { INTI,INTI };	/* 画像位置の入力値の格納庫	 */

	/* 画像設定入力 ------------------------------------ */
	for ( icntTIO = INTI; icntTIO < TWO; icntTIO ++ ) {
		printf( "|------------------------------|\n" );
		printf( "|				|				|\n" );
		printf( "|				|				|\n" );
		printf( "|		①		|		②		|\n" );
		printf( "|				|				|\n" );
		printf( "|				|				|\n" );
		printf( "|------------------------------|\n" );

		printf( "%d枚目の画像をどこに配置しますか？\n", icntTIO + ONE );

		rewind( stdin );
		( void )scanf( "%d", &iboxTIO[icntTIO] );

		/* ①の画像IDを10の位、②の画像IDを1の位に格納 */

		
		for ( icntTIO_Check = icntTIO; INTI < icntTIO_Check; icntTIO_Check -- ) {
			if ( iboxTIO[icntTIO] == iboxTIO[icntTIO - icntTIO_Check] ) {
				iboxTIO[icntTIO] = INTI;
			}
		}

		/* 入力値チェック -------------------- */
		/* 入力値が範囲外 */
		while ( iboxTIO[icntTIO] < ONE || TWO < iboxTIO[icntTIO] ) {
			printf( "範囲外再入力\n" );
			rewind( stdin );
			( void )scanf( "%d", &iboxTIO[icntTIO] );

			/* 入力値がすでに入力されている */
			for ( icntTIO_Check = icntTIO; INTI < icntTIO_Check; icntTIO_Check -- ) {
				if (iboxTIO[icntTIO] == iboxTIO[icntTIO - icntTIO_Check] ) {
					iboxTIO[icntTIO] = INTI;
				}
			}
		}
		/* ----------------------------------- */
		/* --------------------------------------------- */
		*idecorateSetup = *idecorateSetup * TEN;
		*idecorateSetup = *idecorateSetup + iboxTIO[icntTIO];
	}
	return SUCCESS;
}
/* ------------------------------------------------------------------------- */
/* 関数名	: DataInputer::Four_In_One										 */
/* 機能名	: 装飾設定を所得する											 */
/* 機能概要	: 情報入力処理を実行する										 */
/* 引数		: SINT* 	: idecorateSetup	: 装飾設定情報[I/O]				 */
/*			: SCHR* 	: orizinalImagePath	: 画像Path情報[I/O]				 */
/* 			: SCHR* 	: secondImagePath	: 画像Path情報[I/O]				 */
/*			: SCHR* 	: thirdImagePath	: 画像Path情報[I/O]				 */
/* 			: SCHR* 	: fourthImagePath	: 画像Path情報[I/O]				 */
/* 戻り値	: SINT		:					: エラーチェック[OUT]			 */
/* 作成日	: 2021/10/29		筈尾  辰也		新規作成					 */
/* ------------------------------------------------------------------------- */
SINT DataInputer::Four_In_One( SINT* idecorateSetup, SCHR* orizinalImagePath,
							   SCHR* secondImagePath, SCHR* thirdImagePath, SCHR* fourthImagePath )
{

	/* 引数値チェック */
	if ( idecorateSetup == NULL ) {
		printf( "decorateInfo Inter Check  Error DecorateInputer::FIO_Setup\n" );
		return FAILE;
	}
	if ( orizinalImagePath == NULL ) {
		printf( "decorateInfo Inter Check  Error DecorateInputer::FIO_Path\n" );
		return FAILE;
	}

	/* 変数宣言 */
	SINT icntFIO			= INTI;				/* カウント役				 */
	SINT icntFIO_Check		= INTI;				/* カウント役				 */
	SINT iboxFIO[FOUR]		= { INTI,INTI,INTI,INTI };	/* 画像位置の入力値の格納庫 */

	/* 画像設定入力 ------------------------------------ */
	for ( icntFIO = INTI; icntFIO < FOUR; icntFIO++ ) {
		printf( "|------------------------------|\n" );
		printf( "|				|				|\n" );
		printf( "|				|				|\n" );
		printf( "|		①		|		②		|\n" );
		printf( "|				|				|\n" );
		printf( "|				|				|\n" );
		printf( "|------------------------------|\n" );
		printf( "|				|				|\n" );
		printf( "|				|				|\n" );
		printf( "|		③		|		④		|\n" );
		printf( "|				|				|\n" );
		printf( "|				|				|\n" );
		printf( "|------------------------------|\n" );
		printf( "%d枚目の画像をどこに配置しますか？\n", icntFIO + ONE );

		rewind( stdin );
		( void )scanf( "%d", &iboxFIO[icntFIO] );

		/* ①の画像IDを1000の位、②の画像IDを100の位、③の画像IDを10の位、④の画像IDを1の位に格納 */

		
		for ( icntFIO_Check = icntFIO; INTI < icntFIO_Check; icntFIO_Check -- ) {
			if (iboxFIO[icntFIO] == iboxFIO[icntFIO - icntFIO_Check] ) {
				iboxFIO[icntFIO] = INTI;
			}
		}
		

		/* 入力値チェック -------------------- */
		/* 入力値が範囲外 */
		while ( iboxFIO[icntFIO] < ONE || FOUR < iboxFIO[icntFIO] ) {
			printf( "範囲外再入力\n" );
			rewind( stdin );
			( void )scanf( "%d", &iboxFIO[icntFIO] );

			/* 入力値がすでに入力されている */
			for ( icntFIO_Check = icntFIO; INTI < icntFIO_Check; icntFIO_Check -- ) {
				if ( iboxFIO[icntFIO] == iboxFIO[icntFIO - icntFIO_Check] ) {
					iboxFIO[icntFIO] = INTI;
				}
			}
		}
		/* ----------------------------------- */
		/* --------------------------------------------- */

		*idecorateSetup = *idecorateSetup * TEN;
		*idecorateSetup = *idecorateSetup + iboxFIO[icntFIO];
	}
	return SUCCESS;
}
/* ------------------------------------------------------------------------- */
/* 関数名	: DataInputer::Overlar											 */
/* 機能名	: 装飾設定を所得する											 */
/* 機能概要	: 情報入力処理を実行する										 */
/* 引数		: SINT* 	: idecorateSetup	: 装飾設定情報[I/O]				 */
/* 			: SCHR* 	: secondImagePath	: 画像Path情報[I/O]				 */
/* 戻り値	: SINT		:					: エラーチェック[OUT]			 */
/* 作成日	: 2021/10/29		筈尾  辰也		新規作成					 */
/* ------------------------------------------------------------------------- */
SINT DataInputer::Overlay( SINT* idecorateSetup, SCHR* secondImagePath )
{

	/* 引数値チェック */
	if ( idecorateSetup == NULL ) {
		printf( "decorateInfo Inter Check  Error DecorateInputer::Overlay_Setup\n" );
		return FAILE;
	}

	/* 画像設定入力 -------------------------- */
	printf( "オーバーレイが選択されました透過率どうしますか？(0 - 99)\n" );
	rewind( stdin );
	( void )scanf( "%d", idecorateSetup );

	/* 範囲外再入力 */
	while ( *idecorateSetup < OVERLAY_MIN || OVERLAY_MAX < *idecorateSetup ) {
		printf( "範囲外再入力\n" );
		rewind( stdin );
		( void )scanf( "%d", idecorateSetup );
	}
	/* --------------------------------------- */
	return SUCCESS;
}
/* ------------------------------------------------------------------------- */
/* 関数名	: DataInputer::Restart											 */
/* 機能名	: 装飾設定を所得する											 */
/* 機能概要	: 情報入力処理を実行する										 */
/* 引数		: SINT* 	: idecorateSetup	: 装飾設定情報[I/O]				 */
/* 戻り値	: SINT		:					: エラーチェック[OUT]			 */
/* 作成日	: 2021/11/11		筈尾  辰也		新規作成					 */
/* ------------------------------------------------------------------------- */
SINT DataInputer::Restart( SINT* idecorateSetup )
{

	/* 引数値チェック */
	if ( idecorateSetup == NULL ) {
		printf( "decorateInfo Inter Check  Error DecorateInputer::Restart_Setup\n" );
		return FAILE;
	}

	/* 画像設定入力 -------------------------- */
	printf( "取り消しが選択されました\n本当に取り消しますか？\n1 はい,2 いいえ\n" );
	rewind( stdin );
	( void )scanf( "%d", idecorateSetup );

	/* 範囲外再入力 */
	while ( *idecorateSetup < ONE || TWO < *idecorateSetup ) {
		printf( "範囲外再入力\n" );
		rewind( stdin );
		( void )scanf( "%d", idecorateSetup );
	}
	/* --------------------------------------- */

	return SUCCESS;
}
/* ------------------------------------------------------------------------- */
/* 関数名	: DataInputer::Fin												 */
/* 機能名	: 装飾設定を所得する											 */
/* 機能概要	: 情報入力処理を実行する										 */
/* 引数		: SINT* 	: idecorateSetup	: 装飾設定情報[I/O]				 */
/* 戻り値	: SINT		:					: エラーチェック[OUT]			 */
/* 作成日	: 2021/11/11		筈尾  辰也		新規作成					 */
/* ------------------------------------------------------------------------- */
SINT DataInputer::Fin( SINT* idecorateSetup )
{

	/* 引数値チェック */
	if ( idecorateSetup == NULL ) {
		printf( "decorateInfo Inter Check  Error DecorateInputer::Fin_Setup\n" );
		return FAILE;
	}

	/* 画像設定入力 -------------------------- */
	printf( "終了が選択されました\n本当終了しますか？\n1 はい,2 いいえ\n" );
	rewind( stdin );
	( void )scanf( "%d", idecorateSetup );

	/* 範囲外再入力 */
	while ( *idecorateSetup < ONE || TWO < *idecorateSetup ) {
		printf( "範囲外再入力\n" );
		rewind( stdin );
		( void )scanf( "%d", idecorateSetup );
	}
	/* --------------------------------------- */

	return SUCCESS;
}

/* ------------------------------------------------------------------------- */
/*              Copyright HAL Collage of Technology & Design                 */
/* ------------------------------------------------------------------------- */
