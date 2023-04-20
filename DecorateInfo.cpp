/* ------------------------------------------------------------------------- */
/* DecorateInfo.cpp															 */
/* 装飾情報保存部															 */
/* 装飾内容保存処理															 */
/* ------------------------------------------------------------------------- */
/* 番号	更新履歴								日付		   氏名			 */
/* ------------------------------------------------------------------------- */
/* 000000	新規作成							2021/10/25     筈尾　辰也	 */
/* 000001	リファクタリング					2021/12/02	   筈尾  辰也	 */
/* ------------------------------------------------------------------------- */
/* Include File																 */
/* ------------------------------------------------------------------------- */
#include "DecorateInfo.h"

/* ------------------------------------------------------------------------- */
/* 関数名	: Decorateinfo::DecorateInfo									 */
/* 機能名	: コンストラクタ												 */
/* 機能概要	: データ初期化等												 */
/* 引数		: なし															 */
/* 戻り値	: void															 */
/* 作成日	: 2021/10/25		筈尾  辰也		新規作成					 */
/* ------------------------------------------------------------------------- */
DecorateInfo::DecorateInfo( void )
{
	proot	= NULL;
	psearth	= NULL;
}

/* ------------------------------------------------------------------------- */
/* 関数名	: Decorateinfo::~DecorateInfo									 */
/* 機能名	: デストラクタ													 */
/* 機能概要	: データ解放等													 */
/* 引数		: なし															 */
/* 戻り値	: void															 */
/* 作成日	: 2021/10/25		筈尾  辰也		新規作成					 */
/* ------------------------------------------------------------------------- */
DecorateInfo::~DecorateInfo( void )
{
	/* 重複解放防止 */
	if ( proot != NULL && proot != psearth ) {
		free( proot );
	}
	if ( psearth != NULL ) {
		free( psearth );
	}
}

/* ------------------------------------------------------------------------- */
/* 関数名	: DecorateInfo::save											 */
/* 機能名	: 保存する														 */
/* 機能概要	: 装飾情報を取得し、保存する									 */
/* 引数		: DecorateList*	: proot				: 装飾先頭アド[IN / OUT]	 */
/*			: DecorateList*	: psearth			: 装飾参照アド[IN / OUT]	 */
/* 			: SINT*			: idecorateKind		: 装飾種類[IN]				 */
/*			: SINT*			: idecorateSetup	: 装飾設定[IN]				 */
/* 戻り値	: SINT			:					: エラーチェック[OUT]		 */
/* 作成日	: 2021/10/25		筈尾  辰也		新規作成					 */
/* ------------------------------------------------------------------------- */
SINT DecorateInfo::save( DecorateList* &proot, DecorateList* &psearth,
						 SINT* idecorateKind, SINT* idecorateSetup )
{
	/* 引数値チェック */
	/* DM check */
	if( ( proot == NULL ) &&  ( psearth != NULL) ){
		printf( "decorateInfo Inter Check  Error DecorateInfo::save_proot\n" );
		return FAILE;
	}
	if( ( proot != NULL ) && ( psearth == NULL ) ){
		printf( "decorateInfo Inter Check  Error DecorateInfo::save_psearth\n" );
		return FAILE;
	}

	if ( idecorateKind == NULL ) {
		printf( "decorateInfo Inter Check  Error DecorateInfo::save_Kind\n" );
		return FAILE;
	}
	if ( idecorateSetup == NULL ) {
		printf( "decorateInfo Inter Check  Error DecorateInfo::save_Setup\n" );
		return FAILE;
	}
	

	/* 変数宣言 */
	DecorateList* ptemp = NULL;					/* 単方向List作成のためのテンプ */

	/* DM確保 */
	ptemp = ( DecorateList* )calloc( ONE,sizeof( DecorateList ) );

	/* DMチェック */
	if ( ptemp == NULL ) {
		printf( "get dynamic error In ptemp\n" );
		return FAILE;
	}

	/* 保存回数1回目なら先頭アドに二回目以降なら前のアドの後ろに結合 */
	if ( proot == NULL ) {
		proot	= ptemp;
		psearth	= ptemp;
	}
	else {
		psearth->next	= ptemp;
		psearth			= ptemp;

	}
	/* 保存 */
	ptemp->decolateKind		= *idecorateKind;
	ptemp->decolatesetup	= *idecorateSetup;

	return SUCCESS;
}
/* ------------------------------------------------------------------------- */
/*              Copyright HAL Collage of Technology & Design                 */
/* ------------------------------------------------------------------------- */
