#pragma once
/* ------------------------------------------------------------------------- */
/* FileFormat.h																 */
/* フォーマット情報部														 */
/* クラス定義及び、関数など最低限の情報のみ記載								 */
/* ------------------------------------------------------------------------- */
/* 番号	更新履歴								日付		   氏名			 */
/* 000000	新規作成							2021/10/25     筈尾　辰也	 */
/* 000001	リファクタリング					2021/11/30	   筈尾  辰也	 */
/* ------------------------------------------------------------------------- */
/* Secure 宣言																 */
/* ------------------------------------------------------------------------- */
#define  _CRT_NO_SECURE_WARNINGS
#define  _CRT_SECURE_NO_DEPRECATE

/* ------------------------------------------------------------------------- */
/* Define宣言																 */
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
/* 構造体定義																 */
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
/* Class定義																 */
/* ------------------------------------------------------------------------- */

class FileFormat {
public:
	FileFormat( void );
	~FileFormat( void );
	SCHR* saveFileName;							/* 保存名					 */

	SINT get( SCHR* saveFileName,SCHR* bmpOutPath,SCHR* imageType );

private:
	SINT check( SCHR* saveFileName,SCHR* bmpOutPath );
};
/* ------------------------------------------------------------------------- */
/*              Copyright HAL Collage of Technology & Design                 */
/* ------------------------------------------------------------------------- */
