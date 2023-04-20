/* ------------------------------------------------------------------------- */
/* Overlay.cpp																 */
/* オーバーレイ																 */
/* 二枚の画像をオーバーレイする												 */
/* ------------------------------------------------------------------------- */
/* 番号	更新履歴								日付		   氏名			 */
/* ------------------------------------------------------------------------- */
/* 000000	新規作成							2021/10/17     筈尾　辰也	 */
/* 000001	リファクタリング					2021/11/25	   筈尾  辰也	 */
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
/* Include File																 */
/* ------------------------------------------------------------------------- */
#include "System.h"
#include "Overlay.h"

/* ------------------------------------------------------------------------- */
/* 関数名	: Overlay::exe													 */
/* 機能名	: 実行する														 */
/* 機能概要	: オーバーレイを実行する										 */
/* 引数		: DecorateList*	: decorateInfo		: 装飾情報[OUT] 			 */
/*			: FileData* 	: imageData			: 画像情報[OUT] 			 */
/*			: FileData* 	: secondImageData	: 二枚目の装飾情報[OUT] 	 */
/* 戻り値	: SINT		:					: エラーチェック[IN]			 */
/* 作成日	: 2021/10/17		筈尾  辰也		新規作成					 */
/* ------------------------------------------------------------------------- */
SINT Overlay::exe( DecorateList* decorateInfo, FileData* imageData, FileData* secondImageData )
{

	/* 変数宣言 */
	UCHR* poverlay		= NULL;					/* 装飾後の画像データ		 */
	SINT iverLonger		= INTI;					/* 高さの最大値				 */
	SINT ihorLonger		= INTI;					/* 幅の最大値				 */
	SINT ishelterBox	= INTI;					/* 空箱						 */
	SINT imag			= INTI;					/* 透過率					 */
	SINT iverCnt		= INTI;					/* カウント役				 */
	SINT ihorCnt		= INTI;					/* カウント役				 */
	SINT imageSize		= INTI;					/* 画像サイズ				 */
	SINT ispaceTop		= INTI;					/* 縦幅の上部判定数			 */
	SINT ispaceBottum	= INTI;					/* 縦幅の下部判定数			 */
	SINT ispaceLeft		= INTI;					/* 横幅の左部判定数			 */
	SINT ispaceRight	= INTI;					/* 横幅の右部判定数			 */
	SINT iescapeOver	= INTI;					/* Overflow Warning回避		 */


	/* 入力値チェック------------------------- */

	/* DM */
	if ( decorateInfo == NULL ) {
		printf( "decorateInfo Inter Check  Error In Overlay::exe_decorateList\n" );
		return FAILE;
	}
	if ( imageData == NULL || secondImageData == NULL ) {
		printf( "decorateInfo Inter Check  Error In Overlay::exe_imageData\n" );
		return FAILE;
	}
	/* 装飾種類 */
	if ( decorateInfo->decolateKind != OVERLAY ) {
		printf( "decorateInfo Inter Check  Error In Overlay::exe_Kind\n" );
		return FAILE;
	}
	/* 装飾設定 */
	if ( decorateInfo->decolatesetup < OVERLAY_MIN || OVERLAY_MAX < decorateInfo->decolatesetup ) {
		printf( "decorateInfo Inter Check  Error In Overlay::exe_Setup\n" );
		return FAILE;
	}
	/* 型式 */
	if ( imageData->pFileHData->sFile_Header_Name != MAGIC_NUMBER || secondImageData->pFileHData->sFile_Header_Name != MAGIC_NUMBER ) {
		printf( "imageData Inter Check Error In Overlay::exe_Type\n" );
		return FAILE;
	}
	/* 大きさ */
	if ( imageData->pInfoHData->uiWidth <= INTI || imageData->pInfoHData->uiHeight <= INTI ||
		 secondImageData->pInfoHData->uiWidth <= INTI || secondImageData->pInfoHData->uiHeight <= INTI ) {
		printf( "imageData Inter Check Error In Overlay::exe_Size\n" );
		return FAILE;
	}
	/* --------------------------------------- */
	
	/* 作成画像の縦横設定 */
	/* 長辺をimageDataに短辺をsecondeに格納 */
	if ( imageData->pInfoHData->uiHeight < secondImageData->pInfoHData->uiHeight ) {
		ishelterBox								= imageData->pInfoHData->uiHeight;
		imageData->pInfoHData->uiHeight			= secondImageData->pInfoHData->uiHeight;
		secondImageData->pInfoHData->uiHeight	= ishelterBox;
		iverLonger								= LONGER_TWO;
	}
	if ( imageData->pInfoHData->uiWidth < secondImageData->pInfoHData->uiWidth ) {
		ishelterBox								= imageData->pInfoHData->uiWidth;
		imageData->pInfoHData->uiWidth			= secondImageData->pInfoHData->uiWidth;
		secondImageData->pInfoHData->uiWidth	= ishelterBox;
		ihorLonger								= LONGER_TWO;
	}

	/* 画像サイズ取得 */
	imageSize = imageData->pInfoHData->uiHeight * imageData->pInfoHData->uiWidth * BYTE4;

	/* 場所位置取得 */
	ispaceTop		= ( ( imageData->pInfoHData->uiHeight - secondImageData->pInfoHData->uiHeight ) / TWO );
	ispaceBottum	= ( ( imageData->pInfoHData->uiHeight + secondImageData->pInfoHData->uiHeight ) / TWO );
	ispaceLeft		= ( ( imageData->pInfoHData->uiWidth  - secondImageData->pInfoHData->uiWidth  ) / TWO ) * BYTE4;
	ispaceRight		= ( ( imageData->pInfoHData->uiWidth  + secondImageData->pInfoHData->uiWidth  ) / TWO ) * BYTE4;

	/* DM get */
	poverlay = ( UCHR* )calloc( imageSize, sizeof( UCHR ) );
	/* DM check */
	if ( poverlay == NULL ) {
		printf( "get DM error_In Overlay::exe_pover\n" );
		return SUCCESS;
	}

	/* 倍率コピー */
	imag = ( SINT )decorateInfo->decolatesetup;

	/* オーバーレイ処理----------------------- */

	/* 縦横の長辺の一致確認 */
	if ( iverLonger == ihorLonger ) {
		/* 一致時 = 空白位置なし
		* |---------------------|
		* |	画像１				|
		* |		|-------|		|
		* |		|画像２	|		|
		* |		|-------|		|
		* |						|
		* |---------------------| 
		* →このように大きい画像が小さい画像をすべて包み込むので
		* 　二枚とも重なる部分と大きい一枚のみの部分の2通りしかない
		*/
		for ( iverCnt = INTI; iverCnt < imageData->pInfoHData->uiHeight; iverCnt ++ ) {
			for ( ihorCnt = INTI; ihorCnt < ( imageData->pInfoHData->uiWidth * BYTE4 ); ihorCnt ++ ) {
				/*
				* |---------------------| -
				* |	画像１				| 1⃣(imageData->ver - secondImageData->ver) / 2
				* |		|-------|		| -
				* |		|画像２	|		| 2⃣(secondImageData->ver)
				* |		|-------|		| -
				* |						| 3⃣(imageData->ver - secondImageData->ver -  1) / 2
				* |---------------------| -
				* 
				* |	①	|	②	|	③	|
				* 
				* ①(imageData->hor - secondImageData->hor) / 2
				* ②(secondImageData->hor)
				* ③(imageData->hor - secondImageData->hor -  1) / 2
				* 
				* →2⃣②の部分とそれ以外に場合分け
				*/

				/* アルファチャンネル飛ばし */
				if ( ( ihorCnt + BYTE1 ) % BYTE4 == INTI ) {

					if ( ispaceTop <= iverCnt && iverCnt < ispaceBottum ) {
						if ( ispaceLeft <= ihorCnt && ihorCnt < ispaceRight ) {

							imageData->pImageData ++;
							secondImageData->pImageData ++;
							continue;
						}
					}
					if ( iverLonger == INTI ) {
						imageData->pImageData ++;
					}else if ( iverLonger == LONGER_TWO ) {
						secondImageData->pImageData ++;
					}
					continue;
				}
				/* 値取得 */
				iescapeOver = iverCnt * ( imageData->pInfoHData->uiWidth * BYTE4 );

				/* 二枚重なる部分の処理 */
				/* 後ろ <= を < に */
				if ( ispaceTop <= iverCnt && iverCnt < ispaceBottum ) {

					if ( ispaceLeft <= ihorCnt && ihorCnt < ispaceRight ) {

						/* 重複部分の輝度計算 */
						ishelterBox = ( SINT )( *( imageData->pImageData ) * imag / HUNDRED + ( SINT )( *( secondImageData->pImageData ) ) * ( HUNDRED - imag ) / HUNDRED );
						/* 書き込み */
						*( poverlay + iescapeOver + ihorCnt ) = ( UCHR )ishelterBox;
						imageData->pImageData ++;
						secondImageData->pImageData ++;
						continue;
					}
				}
				if ( iverLonger == INTI ) {		/* 一枚のみかつ、一枚目の画像が大きい時 */
					*( poverlay + iescapeOver + ihorCnt ) = *imageData->pImageData;
					imageData->pImageData ++;
				}
				else if ( iverLonger == LONGER_TWO ) {	/* 一枚のみかつ、二枚目の画像が大きい時 */
					*( poverlay + iescapeOver + ihorCnt ) = ( *( secondImageData->pImageData ) * ( HUNDRED - imag) / HUNDRED );
					secondImageData->pImageData ++;
				}
			}
		}

	} else {
		/* 不一致時 = 空白位置あり
		*		|-------|
		*	①	|画像１	|
		*		|	②	|
		* |---------------------|
		* |	画像２	④		③	|
		* |---------------------|
		*		|		|
		*		|		|
		*		|-------|
		* →このように交差する形となるので
		* 　①空白部分
		* 　②画像１の1枚のみ
		* 　③画像２の1枚のみ
		* 　④二枚重なる
		* 　の４通りに分けられる
		*/

		for ( iverCnt = INTI; iverCnt < imageData->pInfoHData->uiHeight; iverCnt ++ ) {
			for ( ihorCnt = INTI; ihorCnt < ( imageData->pInfoHData->uiWidth * BYTE4 ); ihorCnt ++ ) {
				/*
				*		|-------|			-
				*	①	|画像１	|			1⃣(imageData->ver - secondImageData->ver) / 2
				*		|	②	|
				* |---------------------|	-
				* |	画像２	④		③	|	2⃣(secondImageData->ver)
				* |---------------------|	-
				*		|		|
				*		|		|			3⃣(imageData->ver - secondImageData->ver -  1) / 2
				*		|-------|			-
				* 
				* |	１	|	２	|	３	|
				*
				* １(imageData->hor - secondImageData->hor) / 2
				* ２(secondImageData->hor)
				* ３(imageData->hor - secondImageData->hor -  1) / 2
				*/
				/* アルファチャンネル飛ばし */
				if ( ( ihorCnt + BYTE1 ) % BYTE4 == INTI ) {
					if ( ispaceTop <= iverCnt && iverCnt < ispaceBottum ) {
						/* 真ん中 */
						if ( ispaceLeft <= ihorCnt && ihorCnt < ispaceRight ) {
							imageData->pImageData ++;
							secondImageData->pImageData ++;
						}/* 中左右 */
						else if ( ihorLonger == INTI ) {
							imageData->pImageData ++;
						}else if ( ihorLonger == LONGER_TWO ) {
							secondImageData->pImageData ++;
						}
					}else if( ispaceLeft <= ihorCnt && ihorCnt < ispaceRight ) {
						/* 中上下 */
						if ( iverLonger == INTI ) {
							imageData->pImageData ++;
						}else if ( iverLonger == LONGER_TWO ) {
							secondImageData->pImageData ++;
						}
					}
					/* 外上下 */
					continue;
				}
				/* 値取得 */
				iescapeOver = iverCnt * ( imageData->pInfoHData->uiWidth * BYTE4 );

				if ( ispaceTop <= iverCnt && iverCnt < ispaceBottum ) {
					/* 横長が範囲内 2⃣ */
					if ( ispaceLeft <= ihorCnt && ihorCnt < ispaceRight ) {
						/* 縦長が範囲内２ */
						/* →④　二枚重なり */

						/* 重複部分の輝度計算 */
						ishelterBox = ( SINT )( *( imageData->pImageData ) * imag / HUNDRED + ( SINT )( *( secondImageData->pImageData ) ) * ( HUNDRED - imag ) / HUNDRED );
						/* 書き込み */
						*( poverlay + iescapeOver + ihorCnt ) = ( UCHR )ishelterBox;

						imageData->pImageData ++;
						secondImageData->pImageData ++;
					}
					/* 縦長が範囲外１，３ */
					/* →③　横長1枚のみ */

					/* 一枚のみかつ、一枚目の画像が大きい時 */
					else if ( ihorLonger == INTI ) {
						*( poverlay + iescapeOver + ihorCnt ) = *imageData->pImageData;
						imageData->pImageData ++;
					}
					/* 一枚のみかつ、二枚目の画像が大きい時 */
					else if ( ihorLonger == LONGER_TWO ) {
						*( poverlay + iescapeOver + ihorCnt ) = ( *( secondImageData->pImageData ) * ( HUNDRED - imag ) / HUNDRED );
						secondImageData->pImageData ++;
					}
				} else {
					/* 横長が範囲外1⃣3⃣ */
					if ( ispaceLeft <= ihorCnt && ihorCnt < ispaceRight ) {
						/* 縦長が範囲内２ */
						/* →②　縦長1枚のみ */
						if ( iverLonger == INTI ) {
							/* 一枚のみかつ、一枚目の画像が大きい時 */
							*( poverlay + iescapeOver + ihorCnt ) = *imageData->pImageData;
							imageData->pImageData ++;

						} else if ( iverLonger == LONGER_TWO ) {
							/* 一枚のみかつ、二枚目の画像が大きい時 */
							*( poverlay + iescapeOver + ihorCnt ) = ( *( secondImageData->pImageData ) * ( HUNDRED - imag ) / HUNDRED );
							secondImageData->pImageData ++;
						}
					} else {
						/* 縦長が範囲外 */
						/* →①　空白 */
						*( poverlay + iescapeOver + ihorCnt ) = WHITE;
					}
				}
			}
		}
	}
	/* ----------------------------------- */
	/* データ更新 */
	imageData->pImageData = poverlay;

	return SUCCESS;
}