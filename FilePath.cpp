/* ------------------------------------------------------------------------- */
/* FilePath.cpp																 */
/* FilePath関連																 */
/* Filepath取得処理															 */
/* ------------------------------------------------------------------------- */
/* 番号	更新履歴								日付		   氏名			 */
/* ------------------------------------------------------------------------- */
/* 000000	新規作成							2021/10/25     筈尾　辰也	 */
/* 000001	リファクタリング					2021/11/29	   筈尾  辰也	 */
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
/* Include File																 */
/* ------------------------------------------------------------------------- */
#include "System.h"
#include "FilePath.h"

/* ------------------------------------------------------------------------- */
/* protype																	 */
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
/* 関数名	: check_type													 */
/* 機能名	: pathの型式を取得する											 */
/* 機能概要	: strcatの疑似版												 */
/* 引数		: SCHR*			: FilePath			: path						 */
/* 戻り値	: SCHR*			: FilePath			: path						 */
/* 作成日	: 2021/11/30		筈尾  辰也		新規作成					 */
/* ------------------------------------------------------------------------- */
SCHR* check_type( SCHR* filePath );

/* ------------------------------------------------------------------------- */
/* 関数名	: check_path													 */
/* 機能名	: 画像名以外のpathを取得する									 */
/* 機能概要	: strcatの疑似版												 */
/* 引数		: SCHR*			: FilePath			: path						 */
/* 戻り値	: SCHR*			: FilePath			: path						 */
/* 作成日	: 2021/11/30		筈尾  辰也		新規作成					 */
/* ------------------------------------------------------------------------- */
SCHR* check_path( SCHR* filePath );

/* ------------------------------------------------------------------------- */
/* 関数名	: FilePath::FilePath											 */
/* 機能名	: コンストラクタ												 */
/* 機能概要	: データ初期化等												 */
/* 引数		: なし															 */
/* 戻り値	: void															 */
/* 作成日	: 2021/10/25		筈尾  辰也		新規作成					 */
/* ------------------------------------------------------------------------- */
FilePath::FilePath( void )
{

	/* 初期化 */
	imageType			= NULL;
	orizinalImagePath	= NULL;
	secondImagePath		= NULL;
	thirdImagePath		= NULL;
	fourthImagePath		= NULL;
	/*get DM */
	imageType			= ( SCHR* )calloc( PATHLENGTH,sizeof( SCHR ) );
	orizinalImagePath	= ( SCHR* )calloc( PATHLENGTH,sizeof( SCHR ) );
	secondImagePath		= ( SCHR* )calloc( PATHLENGTH,sizeof( SCHR ) );
	thirdImagePath		= ( SCHR* )calloc( PATHLENGTH,sizeof( SCHR ) );
	fourthImagePath		= ( SCHR* )calloc( PATHLENGTH,sizeof( SCHR ) );

	/* DM Chech */
	if( orizinalImagePath == NULL || secondImagePath == NULL || thirdImagePath == NULL || fourthImagePath == NULL ){
		printf( "Get DM Error In FilePath::FilePath" );
	}

}

/* ------------------------------------------------------------------------- */
/* 関数名	: FilePath::~FilePath											 */
/* 機能名	: デストラクタ													 */
/* 機能概要	: データ解放等													 */
/* 引数		: なし															 */
/* 戻り値	: void															 */
/* 作成日	: 2021/10/25		筈尾  辰也		新規作成					 */
/* ------------------------------------------------------------------------- */
FilePath::~FilePath( void )
{
	/* 多重開放対策 */
	if ( imageType != NULL ) {
		free( imageType );
	}
	if ( orizinalImagePath != NULL && orizinalImagePath != secondImagePath && orizinalImagePath != thirdImagePath && orizinalImagePath != fourthImagePath ) {
		free( orizinalImagePath );
	}
	if ( secondImagePath != NULL && secondImagePath != thirdImagePath && secondImagePath != fourthImagePath ) {
		free( secondImagePath );
	}
	if ( thirdImagePath != NULL && thirdImagePath != fourthImagePath ) {
		free( thirdImagePath );
	}
	if ( fourthImagePath != NULL ) {
		free( fourthImagePath );
	}
}

/* ------------------------------------------------------------------------- */
/* 関数名	: FilePath::get													 */
/* 機能名	: 取得する														 */
/* 機能概要	: ベースの画像のPathをする										 */
/* 引数		: SCHR* 	: orizinalImagePath	: 画像Path情報[IN / OUT] 		 */
/* 戻り値	: SINT		:					: エラーチェック[OUT]			 */
/* 作成日	: 2021/10/25		筈尾  辰也		新規作成					 */
/* ------------------------------------------------------------------------- */
SINT FilePath::get( SCHR* orizinalImagePath )
{
	if ( orizinalImagePath == NULL ) {
		printf( "OrizinalImagePath Inter Check In FilePath::get" );
		return FAILE;
	}

	SINT  ierrorCheck	= INTI;					/* エラーチェック			 */
	SINT  icnt			= INTI;					/* カウント役				 */
	SCHR* decoy			= NULL;					/* 空箱						 */
	SCHR* pathCpy		= NULL;					/* Pathのコピー				 */
	SCHR* type			= NULL;					/* 型式						 */
	SCHR* path			= NULL;					/* FolderまでのPath			 */
	SCHR  inPutPath[PATHLENGTH];				/* BMP_INのPATH				 */

	/* Path get------------------------------- */
	while ( TRUE ) {
		/* 初期化 */
		memset( inPutPath,INTI,PATHLENGTH );
		decoy		= ( SCHR* )calloc( PATHLENGTH, sizeof( SCHR ) );
		pathCpy		= ( SCHR* )calloc( PATHLENGTH, sizeof( SCHR ) );
		path		= ( SCHR* )calloc( PATHLENGTH, sizeof( SCHR ) );
		type		= ( SCHR* )calloc( PATHLENGTH, sizeof( SCHR ) );
		strcpy( inPutPath,"C:\\Decorate_System\\BMP_IN\\" );


		/* Check*/
		if ( decoy == NULL || pathCpy == NULL || path == NULL || type == NULL ) {
			printf( "Dynamic Memory Get Error In FilePath::get\n" );
			return FAILE;
		}

		printf( "Please drag & drop file you want Decorate Image\n白詰め画像を希望する際は e を入力してください( 集約二枚目以降の画像限定 )\n" );
		rewind( stdin );
		ierrorCheck = scanf( "%s", orizinalImagePath );

		if ( ierrorCheck == NULL ) {
			printf( "scanf error in FilePath::get\n" );
			return FAILE;
		}



		if ( *orizinalImagePath == 'e') {
			return SUCCESS;
		}

		/* Type test------------------- */

		/* copy & get type */
		strcpy( pathCpy, orizinalImagePath );

		/* strcatの改造 */
		decoy = check_type( pathCpy );
		
		while ( decoy != NULL ) {
			/*
			strcat( path, type );
			strcat( path, "." );
			*/
			strcpy( type, decoy );

			decoy = check_type( NULL );

		}
		/* 小文字変換 */
		for (icnt = INTI; icnt < BYTE4; icnt ++ ) {
			if(  'A' <= *(type + icnt ) && *(type + icnt ) <= 'Z' ){
				*(type + icnt ) = *( type + icnt ) + ( 'a' - 'A' );
			}
		}

		/* 範囲外 error */
		if ( !( strcmp( type,"jpeg" ) == STR_OK || strcmp( type,"jpg" ) == STR_OK || strcmp( type,"ping" ) == STR_OK 
			 || strcmp( type,"png" ) == STR_OK || strcmp( type,"bmp" ) == STR_OK ) ) {

			printf("対応外の拡張子です。再度異なる画像を入力してください。\n");
			strcpy( path, "" );
			strcpy( type, "" );

			continue;
		}
		/* ---------------------------- */

		/* 型式保存 */
		strcpy( imageType,type );

		/* Path check------------------ */

		/* 初期化 */
		strcpy( path, "" );
		strcpy( type, "" );
		decoy	= ( SCHR* )calloc( PATHLENGTH, sizeof( SCHR ) );
		pathCpy = ( SCHR* )calloc( PATHLENGTH, sizeof( SCHR ) );
		/* Check*/
		if ( pathCpy == NULL || decoy == NULL ) {
			printf( "Dynamic Memory Get Error In FilePath::get\n" );
			return FAILE;
		}


		strcpy( pathCpy, orizinalImagePath );

		/* strcatの改造 */
		decoy = check_path( pathCpy );
		
		while ( decoy != NULL ) {
			
			strcat( path, type );
			strcat( path, "\\" );
			
			strcpy( type, decoy );

			decoy = check_path( NULL );

		}
		/* \\ が最初ににつくので++ */
		path ++;

		/* 範囲外 error */
		if ( strcmp( path,inPutPath ) != STR_OK ) {

			printf("対応外のPathです。再度異なる画像を入力してください。\n");
			strcpy( path, "" );
			strcpy( type, "" );

			continue;
		}

		/* ---------------------------- */
		/* 正常時抜ける */
		break;
	}

	/* --------------------------------------- */

	return SUCCESS;
}

/* ------------------------------------------------------------------------- */
/* 関数名	: check_type													 */
/* 機能名	: pathの型式を取得する											 */
/* 機能概要	: strcatの疑似版												 */
/* 引数		: SCHR*			: FilePath			: path						 */
/* 戻り値	: SCHR*			: FilePath			: path						 */
/* 作成日	: 2021/11/30		筈尾  辰也		新規作成					 */
/* ------------------------------------------------------------------------- */
SCHR* check_type( SCHR* filePath ) {

	static SCHR* cutPath = NULL;				/* box						 */

	/* copy 一回目は box に path を二回目以降は box から path に copy */
	if ( filePath != NULL ) {
		cutPath = filePath;
	}
	else {
		/* 区切り後から開始 */
		filePath = cutPath;
	}
	/* fin */
	if ( filePath == NULL ) {
		return NULL;
	}
	/* check */
	while ( TRUE ) {
		/* last */
		if ( *cutPath == NULL ) {				/* 最後に到達 */
			cutPath = NULL;						/* stand fin flag */
			return filePath;
		}
		/* cut */
		if ( *cutPath == '.' ) {
			*cutPath = INTI;					/* filePathの.を0(\0)に変えて区切る */
			cutPath ++;							/* 次回のために進める */
			return filePath;					/* 区切り前まで返る */
		}

		cutPath ++;
	}
}

/* ------------------------------------------------------------------------- */
/* 関数名	: check_path													 */
/* 機能名	: 画像名以外のpathを取得する									 */
/* 機能概要	: strcatの疑似版												 */
/* 引数		: SCHR*			: FilePath			: path						 */
/* 戻り値	: SCHR*			: FilePath			: path						 */
/* 作成日	: 2021/11/30		筈尾  辰也		新規作成					 */
/* ------------------------------------------------------------------------- */
SCHR* check_path( SCHR* filePath ) {

	static SCHR* cutPath = NULL;				/* box						 */

	/* copy 一回目はboxにpathを二回目以降はboxからpathにcopy */
	if ( filePath != NULL ) {
		cutPath = filePath;
	}
	else {
		/* 区切り後から開始 */
		filePath = cutPath;
	}
	/* fin */
	if ( filePath == NULL ) {
		return NULL;
	}
	/* check */
	while ( TRUE ) {
		/* last */
		if ( *cutPath == NULL ) {				/* 最後に到達 */
			cutPath = NULL;						/* stand fin flag */
			return filePath;
		}
		/* cut */
		if ( *cutPath == '\\' ) {
			*cutPath = INTI;					/* filePathの.を0(\0)に変えて区切る */
			cutPath ++;							/* 次回のために進める */
			return filePath;					/* 区切り前まで返る */
		}
		cutPath ++;
	}
}

/* ------------------------------------------------------------------------- */
/*              Copyright HAL Collage of Technology & Design                 */
/* ------------------------------------------------------------------------- */
