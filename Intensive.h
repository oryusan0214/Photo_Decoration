#pragma once
/* ------------------------------------------------------------------------- */
/* Intensive.h																 */
/* 集約																		 */
/* クラス定義及び、関数など最低限の情報のみ記載								 */
/* ------------------------------------------------------------------------- */
/* 番号	更新履歴								日付		   氏名			 */
/* ------------------------------------------------------------------------- */
/* 000000	新規作成							2021/10/24     筈尾　辰也	 */
/* 000001	リファクタリング					2021/11/28	   筈尾  辰也	 */
/* ------------------------------------------------------------------------- */
/* Secure 宣言																 */
/* ------------------------------------------------------------------------- */
#define  _CRT_NO_SECURE_WARNINGS
#define  _CRT_SECURE_NO_DEPRECATE

/* ------------------------------------------------------------------------- */
/* Define宣言																 */
/* ------------------------------------------------------------------------- */
#define ONE		1								/* 1の意味					 */
#define TWO		2								/* 2の意味					 */
#define THIRD	3								/* FIOで使う 3の意味		 */
#define FOUR	4								/* FIOで使う 4の意味		 */
#define GET_NUM	10								/* 描写位置首都気に使う定数	 */
#define WHITE	255								/* 白の輝度					 */

/* ------------------------------------------------------------------------- */
/* 構造体定義																 */
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
/* Class定義																 */
/* ------------------------------------------------------------------------- */
class Intensive
{
public:
	SINT exe( DecorateList* decorateInfo, FileData* imageData, FileData* secondImageData, FileData* thirdImageData, FileData* fourthImageData );

private:
	SINT four_in_one( DecorateList* decorateInfo, FileData* imageData, FileData* secondImageData, FileData* thirdImageData, FileData* fourthImageData );
	SINT two_in_one_ver( DecorateList* decorateInfo, FileData* imageData, FileData* secondImageData );
	SINT two_in_one_hor( DecorateList* decorateInfo, FileData* imageData, FileData* secondImageData );

};
/* ------------------------------------------------------------------------- */
/*              Copyright HAL Collage of Technology & Design                 */
/* ------------------------------------------------------------------------- */
