/* ------------------------------------------------------------------------- */
/* Main.cpp																	 */
/* 画像装飾システム															 */
/* 主な流れを記載											 				 */
/* ------------------------------------------------------------------------- */
/* 	番号	更新内容								更新日		名前		 */
/* ------------------------------------------------------------------------- */
/* 000000	新規作成								2021/10/15	筈尾  辰也	 */
/* 000001	新規作成								2021/11/22  筈尾　辰也 */
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
/* includeファイル															 */
/* ------------------------------------------------------------------------- */
#include "Decorate.h"							/* 装飾クラス				 */
#include "Interface.h"							/* インターフェースクラス	 */
#include "ImageOutputer.h"						/* イメージアウトプットクラス*/
#include "ImageInputer.h"						/* イメージインプットクラス	 */
#include "DataInputer.h"						/* 入力クラス				 */

/* ------------------------------------------------------------------------- */
/* 定数定義																	 */
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
/* グローバル変数															 */
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
/* プロトタイプ宣言															 */
/* ------------------------------------------------------------------------- */
SINT white( FileData* baseData,FileData* copyData );

/* ------------------------------------------------------------------------- */
/* 関数名	: main															 */
/* 機能名	: メイン関数													 */
/* 機能概要	: 主な流れを記載												 */
/* 引数		: なし															 */
/* 戻り値	: SINT		:		: システムへの返り値						 */
/* 作成日	: 2021/10/15		筈尾  辰也		新規作成					 */
/* ------------------------------------------------------------------------- */

SINT main( void )
{

	/* クラス宣言 */
	ColorInversion CI;							/* 色反転					 */
	Copy CP;									/* 複写						 */
	DataInputer DIp;							/* 入力						 */
	DecorateInfo DIf;							/* 装飾情報					 */
	FileFormat FF;								/* ファイルフォーマット		 */
	FileIO FIO;									/* ファイル入出力			 */
	FilePath FP;								/* ファイルパス				 */
	ImageInputer IIp;							/* 画像入力					 */
	ImageOutputer IOp;							/* 画像出力					 */
	IndependentProcessing IP;					/* 単独処理					 */
	Intensive IS;								/* 集約						 */
	Interface IF;								/* インターフェース			 */
	Overlay OL;									/* オーバーレイ				 */
	Mosaic MSC;									/* モザイク					 */
	Rotate RT;									/* 回転						 */
	ImageInvert IIv;							/* 画像反転					 */
	Sepia SP;									/* セピア					 */
	Magnification MG;							/* 拡大縮小					 */
	ColorConvert CC;


	SINT ierrorCheck = INTI;					/* エラーチェック			 */

	/* 構造体宣言 & DM確保 */
	
	FileData* imageData = NULL;
	imageData = ( FileData* )calloc( sizeof( FileData ), sizeof( SCHR ) );
	
	/* DM Check */
	
	if ( imageData == NULL ) {
		printf( "get dynamic error\n" );
		return FAILE;
	}
	

	/* 複合テストまで放置、各クラスのテスト場 */
	printf("画像装飾システムへようこそ\n");

	/* 一枚目の画像の取得 */
	/* 再入力数が不明のためwhile */
	while( *FP.orizinalImagePath == NULL || *FP.orizinalImagePath == 'e' ){
		ierrorCheck = FP.get( FP.orizinalImagePath );

		if ( ierrorCheck == FAILE ) {
			printf( "システムを異常終了します\n" );
			return 0;
		}
	}
	/* 画像読込 */
	ierrorCheck = FIO.read( FP.orizinalImagePath,&imageData );

	if ( ierrorCheck == FAILE ) {
		printf( "システムを異常終了します\n" );
		return 0;
	}

	ierrorCheck = IIp.exe( imageData,FP.orizinalImagePath );

	if ( ierrorCheck == FAILE ) {
		printf( "システムを異常終了します\n" );
		return 0;
	}

	
	/* 装飾情報の入力 */
	ierrorCheck = DIp.get_first( DIp.idecorateKind, DIp.idecorateSetup, FP.orizinalImagePath, FP.secondImagePath, FP.thirdImagePath, FP.fourthImagePath );

	if ( ierrorCheck == FAILE ) {
		printf( "システムを異常終了します\n" );
		return 0;
	}

	ierrorCheck = DIf.save( DIf.proot, DIf.psearth, DIp.idecorateKind, DIp.idecorateSetup );

	if ( ierrorCheck == FAILE ) {
		printf( "システムを異常終了します\n" );
		return 0;
	}


	if ( *DIp.idecorateKind == COPY ) {
		*DIp.idecorateKind = *DIp.idecorateKind + ONE;
	}
	if ( *DIp.idecorateKind == RESTART ) {
		*DIp.idecorateKind	= INTI;
		DIf.proot			= NULL;
		DIf.psearth			= NULL;
	}

	while ( *DIp.idecorateKind < TWO_IN_ONE_VER ) {
		ierrorCheck = DIp.get( DIp.idecorateKind, DIp.idecorateSetup, FP.orizinalImagePath, FP.secondImagePath, FP.thirdImagePath, FP.fourthImagePath );

		if ( ierrorCheck == FAILE ) {
			printf( "システムを異常終了します\n" );
			return 0;
		}

		ierrorCheck = DIf.save( DIf.proot, DIf.psearth, DIp.idecorateKind, DIp.idecorateSetup );

		if ( ierrorCheck == FAILE ) {
			printf( "システムを異常終了します\n" );
			return 0;
		}

		if ( *DIp.idecorateKind == COPY ) {
			*DIp.idecorateKind	= INTI;
			DIf.proot			= NULL;
			DIf.psearth			= NULL;
		}

		if ( *DIp.idecorateKind == TWO_IN_ONE_VER ) {
			DIf.psearth->decolateKind = FIN;
		}
	}

	/* 装飾処理 */
	DIf.psearth = DIf.proot;

	/* 装飾数がわからないのでwhile */
	while ( true ) {

		switch ( DIf.psearth->decolateKind ) {

		case ROTATE:

			ierrorCheck = RT.exe( DIf.psearth, imageData );break;

			if ( ierrorCheck == FAILE ) {
				printf( "システムを異常終了します\n" );
				return 0;
			}

		case IMAGEINVERT:

			ierrorCheck = IIv.exe( DIf.psearth, imageData );break;

			if ( ierrorCheck == FAILE ) {
				printf( "システムを異常終了します\n" );
				return 0;
			}

		case COLORINVERT:

			ierrorCheck = CI.exe( DIf.psearth, imageData );break;

			if ( ierrorCheck == FAILE ) {
				printf( "システムを異常終了します\n" );
				return 0;
			}


		case SEPIA:

			ierrorCheck = SP.exe( DIf.psearth, imageData );break;

			if ( ierrorCheck == FAILE ) {
				printf( "システムを異常終了します\n" );
				return 0;
			}

		case MOSAIC:

			ierrorCheck = MSC.exe( DIf.psearth, imageData );break;

			if ( ierrorCheck == FAILE ) {
				printf( "システムを異常終了します\n" );
				return 0;
			}

		case MAGNIFICATION:

			ierrorCheck = MG.exe( DIf.psearth, imageData );break;

			if ( ierrorCheck == FAILE ) {
				printf( "システムを異常終了します\n" );
				return 0;
			}

		case COLORCONVERT:

			ierrorCheck = CC.exe( imageData,DIf.psearth->decolatesetup,FP.orizinalImagePath );

			if ( ierrorCheck == FAILE ) {
				printf( "システムを異常終了します\n" );
				return 0;
			}

		case COPY:

			ierrorCheck = CP.exe( DIf.psearth, imageData );break;

			if ( ierrorCheck == FAILE ) {
				printf( "システムを異常終了します\n" );
				return 0;
			}



		case TWO_IN_ONE_VER:

			ierrorCheck = FP.get( FP.secondImagePath );

			if ( ierrorCheck == FAILE ) {
				printf( "システムを異常終了します\n" );
				return 0;
			}

			if( *FP.secondImagePath != 'e') {
				ierrorCheck = FIO.read( FP.secondImagePath, &IP.secondImageData );

				if ( ierrorCheck == FAILE ) {
					printf( "システムを異常終了します\n" );
					return 0;
				}

				ierrorCheck = IIp.exe( IP.secondImageData, FP.secondImagePath );

				if ( ierrorCheck == FAILE ) {
					printf( "システムを異常終了します\n" );
					return 0;
				}

			}
			else {
				ierrorCheck = white( imageData,IP.secondImageData );

				if ( ierrorCheck == FAILE ) {
					printf( "システムを異常終了します\n" );
					return 0;
				}
			}

			ierrorCheck = IS.exe( DIf.psearth, imageData, IP.secondImageData, IP.thirdImageData, IP.fourthImageData );

			if ( ierrorCheck == FAILE ) {
				printf( "システムを異常終了します\n" );
				return 0;
			}

			break;

		case TWO_IN_ONE_HOR:

			ierrorCheck = FP.get( FP.secondImagePath );

			if ( ierrorCheck == FAILE ) {
				printf( "システムを異常終了します\n" );
				return 0;
			}

			if ( *FP.secondImagePath != 'e' ) {
				ierrorCheck = FIO.read( FP.secondImagePath, &IP.secondImageData );

				if ( ierrorCheck == FAILE ) {
					printf( "システムを異常終了します\n" );
					return 0;
				}

				ierrorCheck = IIp.exe( IP.secondImageData, FP.secondImagePath );

				if ( ierrorCheck == FAILE ) {
					printf( "システムを異常終了します\n" );
					return 0;
				}

			}
			else {
				ierrorCheck = white( imageData, IP.secondImageData );

				if ( ierrorCheck == FAILE ) {
					printf( "システムを異常終了します\n" );
					return 0;
				}
			}
			ierrorCheck = IS.exe( DIf.psearth, imageData, IP.secondImageData, IP.thirdImageData, IP.fourthImageData );

			if ( ierrorCheck == FAILE ) {
				printf( "システムを異常終了します\n" );
				return 0;
			}

			break;

		case FOUR_IN_ONE:

			ierrorCheck = FP.get( FP.secondImagePath );

			if ( ierrorCheck == FAILE ) {
				printf( "システムを異常終了します\n" );
				return 0;
			}

			if ( *FP.secondImagePath != 'e' ) {
				ierrorCheck = FIO.read( FP.secondImagePath, &IP.secondImageData );

				if ( ierrorCheck == FAILE ) {
					printf( "システムを異常終了します\n" );
					return 0;
				}

				ierrorCheck = IIp.exe( IP.secondImageData, FP.secondImagePath );

				if ( ierrorCheck == FAILE ) {
					printf( "システムを異常終了します\n" );
					return 0;
				}

			}
			else {
				ierrorCheck = white( imageData, IP.secondImageData );

				if ( ierrorCheck == FAILE ) {
					printf( "システムを異常終了します\n" );
					return 0;
				}
			}

			FP.get( FP.thirdImagePath );

			if ( ierrorCheck == FAILE ) {
				printf( "システムを異常終了します\n" );
				return 0;
			}

			if ( *FP.thirdImagePath != 'e' ) {
				ierrorCheck = FIO.read( FP.thirdImagePath, &IP.thirdImageData );

				if ( ierrorCheck == FAILE ) {
					printf( "システムを異常終了します\n" );
					return 0;
				}

				ierrorCheck = IIp.exe( IP.thirdImageData, FP.thirdImagePath );

				if ( ierrorCheck == FAILE ) {
					printf( "システムを異常終了します\n" );
					return 0;
				}

			}
			else {
				ierrorCheck = white( imageData, IP.thirdImageData );

				if ( ierrorCheck == FAILE ) {
					printf( "システムを異常終了します\n" );
					return 0;
				}
			}


			ierrorCheck = FP.get( FP.fourthImagePath );

			if ( ierrorCheck == FAILE ) {
				printf( "システムを異常終了します\n" );
				return 0;
			}

			if ( *FP.fourthImagePath != 'e' ) {
				ierrorCheck = FIO.read( FP.fourthImagePath, &IP.fourthImageData );

				if ( ierrorCheck == FAILE ) {
					printf( "システムを異常終了します\n" );
					return 0;
				}

				ierrorCheck = IIp.exe( IP.fourthImageData, FP.fourthImagePath );

				if ( ierrorCheck == FAILE ) {
					printf( "システムを異常終了します\n" );
					return 0;
				}
			}
			else {
				ierrorCheck = white( imageData, IP.fourthImageData );

				if ( ierrorCheck == FAILE ) {
					printf( "システムを異常終了します\n" );
					return 0;
				}
			}
			ierrorCheck = IS.exe( DIf.psearth, imageData, IP.secondImageData, IP.thirdImageData, IP.fourthImageData );

			if ( ierrorCheck == FAILE ) {
				printf( "システムを異常終了します\n" );
				return 0;
			}
			break;

		case OVERLAY:

			ierrorCheck = FP.get( FP.secondImagePath );

			if ( ierrorCheck == FAILE ) {
				printf( "システムを異常終了します\n" );
				return 0;
			}

			ierrorCheck = FIO.read( FP.secondImagePath, &IP.secondImageData );

			if ( ierrorCheck == FAILE ) {
				printf( "システムを異常終了します\n" );
				return 0;
			}

			ierrorCheck = OL.exe( DIf.psearth, imageData, IP.secondImageData);

			if ( ierrorCheck == FAILE ) {
				printf( "システムを異常終了します\n" );
				return 0;
			}
			break;

		default :
			break;
		}
		if ( DIf.psearth->next == NULL ) {
			break;
		}

		DIf.psearth = DIf.psearth->next;
	}
	/* 出力 */
	strcpy( IOp.bmpOutPath, "C:\\Decorate_System\\BMP_OUT\\" );
	ierrorCheck = FF.get( FF.saveFileName, IOp.bmpOutPath, FP.imageType );

	if ( ierrorCheck == FAILE ) {
		printf( "システムを異常終了します\n" );
		return 0;
	}

	strcat( IOp.bmpOutPath, FF.saveFileName );

	ierrorCheck = FIO.write( IOp.bmpOutPath,&imageData );

	if ( ierrorCheck == FAILE ) {
		printf( "システムを異常終了します\n" );
		return 0;
	}


	return SUCCESS;
}

/* ------------------------------------------------------------------------- */
/* 関数名	: white															 */
/* 機能名	: 白詰め関数													 */
/* 機能概要	: 白画像を作成													 */
/* 引数		: FileData*	: baseData	: 参照する画像データ					 */
/*			: FileData*	: copyData	: 白画像を格納する						 */
/* 戻り値	: SINT		:			: システムへの返り値					 */
/* 作成日	: 2021/12/09		筈尾  辰也		新規作成					 */
/* ------------------------------------------------------------------------- */
SINT white( FileData* baseData,FileData* copyData ) 
{
	/* 引数チェック */
	if ( baseData == NULL ) {
		printf( "baseData error\n" );
		return FALSE;
	}
	if ( copyData == NULL ) {
		printf( "copyData error\n" );
		return FALSE;
	}

	SINT iverCnt	= INTI;					/* カウント役				 */	
	SINT ihorCnt	= INTI;					/* カウント役				 */
	SINT imageSize	= INTI;					/* 画像サイズ				 */
	SINT ireference = INTI;					/* 参照値					 */

	copyData->pFileHData = ( FileHeader* )calloc( sizeof( FileHeader ),ONE );
	copyData->pInfoHData = ( InformationHeader* )calloc( sizeof( InformationHeader ),ONE );

	if ( copyData->pFileHData == NULL || copyData->pInfoHData == NULL ) {
		printf( "copyDm error\n" );
		return FAILE;
	}

	/* copy */
	*copyData->pFileHData = *baseData->pFileHData;
	*copyData->pInfoHData = *baseData->pInfoHData;

	imageSize = copyData->pInfoHData->uiHeight * copyData->pInfoHData->uiWidth * BYTE4;

	copyData->pImageData = ( UCHR* )calloc( imageSize,sizeof( UCHR ) );

	if ( copyData->pImageData == NULL ) {
		printf( "copy DM error\n" );
		return FAILE;
	}


	for ( iverCnt = INTI;iverCnt < copyData->pInfoHData->uiHeight;iverCnt ++ ) {
		for ( ihorCnt = INTI; ihorCnt < copyData->pInfoHData->uiWidth;ihorCnt ++ ) {
			ireference = iverCnt * copyData->pInfoHData->uiWidth * BYTE4 + ihorCnt * BYTE4;
			*( copyData->pImageData + ireference  ) = WHITE;
			*( copyData->pImageData + ireference + BYTE1 ) = WHITE;
			*( copyData->pImageData + ireference + BYTE2 ) = WHITE;
		}
	}
	return SUCCESS;
}
