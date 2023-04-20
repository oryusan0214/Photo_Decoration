#pragma once
/* ------------------------------------------------------------------------- */
/* DataInputer.h															 */
/* 入力処理																	 */
/* クラス定義及び、関数など最低限の情報のみ記載								 */
/* ------------------------------------------------------------------------- */
/* 番号	更新履歴								日付		   氏名			 */
/* 000000	新規作成							2021/10/28     筈尾　辰也	 */
/* 000001	リファクタリング					2021/12/02	   筈尾  辰也	 */
/* ------------------------------------------------------------------------- */
/* Secure 宣言																 */
/* ------------------------------------------------------------------------- */
#define  _CRT_NO_SECURE_WARNINGS
#define  _CRT_SECURE_NO_DEPRECATE

/* ------------------------------------------------------------------------- */
/* Include File																 */
/* ------------------------------------------------------------------------- */
#include "System.h"

/* ------------------------------------------------------------------------- */
/* Define宣言																 */
/* ------------------------------------------------------------------------- */
#define ONE		1								/* 1の意味					 */
#define TWO		2								/* 1の意味					 */
#define FOUR	4								/* 1の意味					 */
#define TEN		10								/* 設定値の設定時に用いる	 */

/* ------------------------------------------------------------------------- */
/* 構造体定義																 */
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
/* Class定義																 */
/* ------------------------------------------------------------------------- */
class DataInputer {
public:
	DataInputer ( void );						/* コンストラクタ			 */
	~DataInputer( void );						/* デストラクタ				 */

	SINT* idecorateKind;						/* 種類						 */
	SINT* idecorateSetup;						/* 設定						 */


	SINT get_first( SINT* idecorateKind, SINT* idecorateSetup, SCHR* orizinalImagePath, SCHR* secondImagePath, SCHR* thirdImagePath, SCHR* fourthImagePath );
	SINT get	  ( SINT* idecorateKind, SINT* idecorateSetup, SCHR* orizinalImagePath, SCHR* secondImagePath, SCHR* thirdImagePath, SCHR* fourthImagePath );


private:
	SINT Rotate			( SINT* idecorateSetup );
	SINT ImageInvert	( SINT* idecorateSetup );
	SINT Sepia			( SINT* idecorateSetup );
	SINT Mosaic			( SINT* idecorateSetup );
	SINT Magnification	( SINT* idecorateSetup );
	SINT ColorConvert	( SINT* idecorateSetup );
	SINT Two_In_One_Ver	( SINT* idecorateSetup, SCHR* orizinalImagePath, SCHR* secondImagePath );
	SINT Two_In_One_Hor	( SINT* idecorateSetup, SCHR* orizinalImagePath, SCHR* secondImagePath );
	SINT Four_In_One	( SINT* idecorateSetup, SCHR* orizinalImagePath, SCHR* secondImagePath, SCHR* thirdImagePath, SCHR* fourthImagePath );
	SINT Overlay		( SINT* idecorateSetup, SCHR* secondImagePath );
	SINT Restart		( SINT* idecorateSetup );
	SINT Fin			( SINT* idecorateSetup );

};
/* ------------------------------------------------------------------------- */
/*              Copyright HAL Collage of Technology & Design                 */
/* ------------------------------------------------------------------------- */
