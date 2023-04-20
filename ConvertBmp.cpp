/* -------------------------------------------------------------------- */
/* ファイル名	:	main.cpp											*/
/* 機能概要		:	指定フォーマットに合わせるために別クラスを呼び出す	*/
/* 作成日		:   2020/10/29											*/
/* 最終更新日	:   2020/12/09											*/
/* 作成者		:	山田龍之介											*/
/* -------------------------------------------------------------------- */
#include "ConvertBmp.h"
/* -------------------------------------------------------------------- */
/* ■■■ public ■■■												    */
/* -------------------------------------------------------------------- */
/* 関数名	:	exe														*/
/* 機能名	:	exe														*/
/* 引数		:	:FileData*		:pFileData		:ファイルのデータ		*/
/*				:SINT			:iDecoretinfo	:装飾情報				*/
/* 戻り値	:	:FAILE			:1				:失敗					*/
/*				:SUCCESS		:0				:成功					*/
/* 作成日	:	2021/11/03		山田　龍之介							*/
/* -------------------------------------------------------------------- */
SINT ConvertBmp::exe( FileData *pFileData,SINT iDecoretinfo ,SCHR *pFilePath ) {
	ColorConvert CC;
	SINT iIdentify;
	if ( pFileData==NULL )
	{
#ifdef TEST
		printf( "プログラム上で確保しているデータに問題が見つかりました(ConvertBmp.cpp) Line=%d\n", __LINE__ );
#endif // TEST
		return FAILE;
	}
	if ( pFilePath==NULL )
	{
#ifdef TEST
		printf( "ファイルパスが正しく取得できませんでした(ConvertBmp.cpp) Line=%d\n", __LINE__ );
#endif // TEST

	}
	if ( iDecoretinfo != Bit32 && iDecoretinfo != Bit24 && iDecoretinfo != Bit8 && iDecoretinfo != Bit1 )
	{
#ifdef TEST
		printf( "引数の値に問題が見つかりました,想定される引数とは違います(ConvertBmp.cpp) Line=%d\n",__LINE__ );
#endif // TEST
		return FAILE;
	}
	if ( pFileData->pInfoHData->sColor_Bit == Bit32 && iDecoretinfo == 32 ) {
		printf( "すでに32bitの画像データです。" );
		return SUCCESS;
	}
	iIdentify=CC.exe( pFileData, iDecoretinfo,pFilePath );
	if ( iIdentify==FAILE )
	{
#ifdef TEST
		printf( "ファイルの変換に失敗しました\(ConvertBmp.cpp) Line=%d\n", __LINE__  );
#endif // TEST
		return FAILE;
	}
	
	return SUCCESS;
}
