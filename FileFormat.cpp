/* ------------------------------------------------------------------------- */
/* FileFormat.cpp															 */
/* FileFormat関連															 */
/* FileFormat,保存先取得処理												 */
/* ------------------------------------------------------------------------- */
/* 番号	更新履歴								日付		   氏名			 */
/* ------------------------------------------------------------------------- */
/* 000000	新規作成							2021/10/25     筈尾　辰也	 */
/* 000001	リファクタリング					2021/11/29	   筈尾  辰也	 */
/* ------------------------------------------------------------------------- */
/* Include File																 */
/* ------------------------------------------------------------------------- */
#include "System.h"
#include "FileFormat.h"

/* ------------------------------------------------------------------------- */
/* 関数名	: FileFormat::FileFormat										 */
/* 機能名	: コンストラクタ												 */
/* 機能概要	: データ初期化等												 */
/* 引数		: なし															 */
/* 戻り値	: void															 */
/* 作成日	: 2021/10/25		筈尾  辰也		新規作成					 */
/* ------------------------------------------------------------------------- */
FileFormat::FileFormat( void )
{
	/* 初期化 & get DM */
	saveFileName	= NULL;
	saveFileName	= ( SCHR* )calloc( PATHLENGTH , sizeof( SCHR ) );

	/* Check DM */
	if ( saveFileName == NULL ) {
		printf( "Get DM error in FileFormat::FileFormat\n" );
	}
}

/* ------------------------------------------------------------------------- */
/* 関数名	: FileFormat::~FileFormat										 */
/* 機能名	: デストラクタ													 */
/* 機能概要	: データ解放等													 */
/* 引数		: なし															 */
/* 戻り値	: void															 */
/* 作成日	: 2021/10/25		筈尾  辰也		新規作成					 */
/* ------------------------------------------------------------------------- */
FileFormat::~FileFormat( void )
{
	/* 解放 */
	if ( saveFileName != NULL ) {
		free( saveFileName );
	}
}

/* ------------------------------------------------------------------------- */
/* 関数名	: FileFormat::get												 */
/* 機能名	: 取得する														 */
/* 機能概要	: 保存File名を取得する											 */
/* 引数		: SCHR*	 	: saveFileName		: 保存File名[I/O]				 */
/*			: SCHR*	 	: bmpOutPath		: 画像出力Path[IN]				 */
/*			: SCHR*	 	: imageType			: 出力画像Type[IN]				 */
/* 戻り値	: SINT		:					: エラーチェック[OUT]			 */
/* 作成日	: 2021/10/25		筈尾  辰也		新規作成					 */
/* ------------------------------------------------------------------------- */
SINT FileFormat::get( SCHR* saveFileName,SCHR* bmpOutPath,SCHR* imageType )
{
	SINT ierrorCheck = INTI;					/* scnafのエラーチェック	 */

	/* 引数値チェック */
	/* DM check */
	if ( saveFileName == NULL ) {
		printf( "decorateInfo Inter Check  FileFormat::get_saveFileName\n" );
		return FAILE;
	}
	if ( bmpOutPath == NULL ) {
		printf( "decorateInfo Inter Check  FileFormat::get_bmpOutPath\n" );
		return FAILE;
	}
	if ( imageType == NULL ) {
		printf( "decorateInfo Inter Check  FileFormat::get_imageType\n" );
		return FAILE;
	}

	/* 入力処理------------------------------- */
	while( TRUE ){
		printf( "保存File名を入力してください\n" );
		rewind( stdin );

		ierrorCheck = scanf( "%s", saveFileName );

		if ( ierrorCheck == NULL ) {
			continue;
		}
		strcat(saveFileName, ".");
		strcat( saveFileName,imageType );

		/* かぶりチェック */
		ierrorCheck = check( saveFileName,bmpOutPath );

		if ( ierrorCheck == FAILE ) {
			continue;
		}
		break;
	
	/* --------------------------------------- */
	}
	return SUCCESS;
}

/* ------------------------------------------------------------------------- */
/* 関数名	: FileFormat::check												 */
/* 機能名	: 比較する														 */
/* 機能概要	: bmpOutのFolderにsaveFileNameと同一のFileがないか確認する		 */
/* 引数		: SCHR*	 	: saveFileName		: 保存File名[I/O]				 */
/*			: SCHR*	 	: bmpOutPath		: 画像出力Path[IN]				 */
/* 戻り値	: SINT		:					: エラーチェック[OUT]			 */
/* 作成日	: 2021/12/02		筈尾  辰也		新規作成					 */
/* ------------------------------------------------------------------------- */
SINT FileFormat::check( SCHR* saveFileName,SCHR* bmpOutPath ) {

	HANDLE			Hdl			= NULL;			/* FindFolderのアドレス格納庫 */
	WIN32_FIND_DATA Hdl_Buff	= { NULL };		/* FindFolderの情報格納庫 */

	SCHR*			bmpPathCpy;					/* 捜索先のpath格納庫 */

	bmpPathCpy = ( SCHR* )calloc( PATHLENGTH, sizeof( SCHR ) );

	if ( bmpPathCpy == NULL ) {
		printf( "Get DM Error In check\n" );
		return FAILE;
	}

	/* FIRST FIND */
	sprintf( bmpPathCpy, "%s\\*.*", bmpOutPath );	/* *.*は残ってほしくないのでcpyの方に */
	Hdl = FindFirstFile( bmpPathCpy, &Hdl_Buff );

	/* 捜索エラー(*.*の重複などが原因) */
	if ( Hdl == INVALID_HANDLE_VALUE ) {
		printf( "INVALID HANDLE VALUE ERROR\n" );
		system( "pause" );
		return FAILE;								/* 強制終了 */
	}

	/* チェック処理 */
	do {
		/* 捜索先のpathをcpyに格納 */
		sprintf( bmpPathCpy, "%s\\%s", bmpOutPath, Hdl_Buff.cFileName );

		/* 親、子のthrough処理 */
		if ( strcmp( ".", Hdl_Buff.cFileName ) == STR_OK || strcmp( "..", Hdl_Buff.cFileName ) == STR_OK ) {
			continue;
		}
		
		/* 名前比較	 */
		if( strcmp( saveFileName,Hdl_Buff.cFileName ) == STR_OK ){
			printf( "同一File名が登録されています、別の名前を入力してください\n" );
			return FAILE;
		}

		/* 次のFILE探索をして空ならループ抜ける */
	} while ( FindNextFile( Hdl, &Hdl_Buff ) != NULL );

	/* Close */
	FindClose( Hdl );
	return SUCCESS;
}
/* ------------------------------------------------------------------------- */
/*              Copyright HAL Collage of Technology & Design                 */
/* ------------------------------------------------------------------------- */
