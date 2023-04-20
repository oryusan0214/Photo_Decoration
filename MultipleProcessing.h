#pragma once
/* ------------------------------------------------------------------------- */
/* mautiProcessing.h														 */
/* 複数処理																	 */
/* クラス定義及び、関数など最低限の情報のみ記載								 */
/* ------------------------------------------------------------------------- */
/* 番号	更新履歴								日付		   氏名			 */
/* 000000	新規作成							2021/10/15     筈尾　辰也	 */
/* 000001	リファクタリング					2021/11/27	   筈尾  辰也	 */
/* ------------------------------------------------------------------------- */
/* Secure 宣言																 */
/* ------------------------------------------------------------------------- */
#define  _CRT_NO_SECURE_WARNINGS
#define  _CRT_SECURE_NO_DEPRECATE

/* ------------------------------------------------------------------------- */
/* Include File																 */
/* ------------------------------------------------------------------------- */
#include "Rotate.h"
#include "ImageInvert.h"
#include "ColorInversion.h"
#include "Sepia.h"
#include "Mosaic.h"
#include "Magnification.h"

/* ------------------------------------------------------------------------- */
/* Define宣言																 */
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
/* 構造体定義																 */
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
/* Class定義																 */
/* ------------------------------------------------------------------------- */
class MultipleProcessing
{
public:
	void exe( DecorateList* decorateInfo, FileData* imageData );
};
/* ------------------------------------------------------------------------- */
/*              Copyright HAL Collage of Technology & Design                 */
/* ------------------------------------------------------------------------- */
