/* -------------------------------------------------------------------- */
/* ファイル名	:	Conversion.cpp										*/
/* 機能概要		:	画像データを指定フォーマットになおし書き込みに渡す	*/
/* 作成日		:   2020/10/21											*/
/* 最終更新日	:   2020/11/04											*/
/* 作成者		:	山田龍之介											*/
/* -------------------------------------------------------------------- */
#include"Conversion.h"

/* -------------------------------------------------------------------- */
/* ■■■ public ■■■												    */
/* -------------------------------------------------------------------- */
/* 関数名	:	exe														*/
/* 機能名	:	指定フォーマットに変換前のファイルのフォーマット統一	*/
/* 引数		:	:FIleData		pFileData 		ファイルのデータ		*/
/*  			:SINT			iDecoratinfo	デコレーションの情報	*/
/* 戻り値	:	:SINT			NULL			失敗					*/
/*								SUCCESS			成功の時は中身を返す	*/
/* 作成日	:	2021/11/03		山田　龍之介							*/
/* -------------------------------------------------------------------- */
SINT Conversion::exe( FileData *pFileData, SINT iDecoratInfo ,SCHR *pFilePath) {
	SINT iIdetify;
	ConvertBmp ConversionBmp;
	iIdetify=Check( 'P', pFileData );
	if ( iIdetify==FAILE )
	{
#ifdef TEST
		printf( "ファイルのデータの取得に失敗しています(Conversion.cpp) Line=%d\n", __LINE__ );
#endif // TEST
		return FAILE;
	}
	iIdetify = Check( 'I', iDecoratInfo );
	if ( iIdetify == FAILE )
	{
#ifdef TEST
		printf( "引数に問題がある可能性があります(Conversion.cpp) Line=%d\n", __LINE__ );
#endif // TEST
		return FAILE;
	}
	iIdetify = Check( 'C', pFilePath );
	if ( iIdetify == FAILE )
	{
#ifdef TEST
		printf( "ファイルのpathが取得できません(Conversion.cpp) Line=%d\n", __LINE__ );
#endif // TEST
		return FAILE;
	}
	switch ( iDecoratInfo )
	{
	case Bit32:
		iIdetify = ConversionBmp.exe( pFileData, iDecoratInfo, pFilePath );
		break;
	case Bit24:
		iIdetify = ConversionBmp.exe( pFileData, iDecoratInfo, pFilePath );
		break;
	case Bit8:
		iIdetify = ConversionBmp.exe( pFileData, iDecoratInfo, pFilePath );
		break;
	case Bit1:
		iIdetify = ConversionBmp.exe( pFileData, iDecoratInfo, pFilePath );
		break;
	
	default:
#ifdef TEST
		printf( "値に問題がある可能性があります(Conversion.cpp) Line=%d\n", __LINE__ );
#endif // TEST
		return FAILE;
		break;
	}
	/*変換後のエラーチェック----------------------------------------------------------------------*/
	if ( iIdetify==FAILE )
	{
#ifdef TEST
		printf( "変換処理に失敗しました(Conversion.cpp) Line=%d\n", __LINE__ );
#endif // TEST
		return FAILE;
	}
	iIdetify = Check( 'F', pFileData->pFileHData );
	if ( iIdetify == FAILE )
	{
#ifdef TEST
		printf( "ファイルの情報に問題が出ました(Conversion.cpp) Line=%d\n", __LINE__ );
#endif // TEST
		return FAILE;
	}
	iIdetify = Check( 'N', pFileData->pInfoHData );
	if ( iIdetify == FAILE )
	{
#ifdef TEST
		printf( "ファイルの情報に問題が出ました(Conversion.cpp) Line=%d\n", __LINE__ );
#endif // TEST
		return FAILE;
	}
	iIdetify = Check( 'C', pFileData->pImageData );
	if ( iIdetify == FAILE )
	{
#ifdef TEST
		printf( "ファイルの情報に問題が出ました(Conversion.cpp) Line=%d\n", __LINE__ );
#endif // TEST
		return FAILE;
	}
	return SUCCESS;
}

SINT Conversion::Check( char checker, ... ) {
	SINT iChecker;
	SCHR *cpChecker;
	SSHT sChecker;
	FileHeader *fChecker;
	InformationHeader *nChecker;
	FileData *pfChecker = NULL;
	va_list args;
	va_start( args, checker );
	switch ( checker )
	{
	case 'P':
		pfChecker = va_arg( args, FileData* );
		if ( pfChecker == NULL )
		{
			return FAILE;
		}
		break;
	case 'F':
		fChecker = va_arg( args, FileHeader* );
		if ( fChecker == NULL )
		{
			return FAILE;
		}
		break;
	case 'I':
		iChecker = va_arg( args, SINT );
		if ( iChecker == NULL )
		{
			return FAILE;
		}
		else if ( iChecker != Bit32 && iChecker != Bit24 && iChecker != Bit8 && iChecker != Bit1
			&& iChecker != PNG && iChecker != JPEG )
		{
			return FAILE;
		}
		break;
	case 'C':
		cpChecker = va_arg( args, SCHR* );
		if ( cpChecker == NULL )
		{
			return FAILE;
		}

		break;
	case 'S':
		sChecker = va_arg( args, SSHT );
		if ( sChecker == NULL )
		{
			return FAILE;
		}
		break;
	case 'N':
		nChecker = va_arg( args, InformationHeader* );
		if ( pfChecker == NULL )
		{
			return FAILE;
		}
		break;
	default:
		printf( "規定外の引数です。" );
		return FAILE;
		break;
	}
	return SUCCESS;
}

