/* -------------------------------------------------------------------- */
/* ファイル名	:	ImageInputer.cpp									*/
/* 機能概要		:	メインにファイルフォーマットに合わせた形で渡す		*/
/* 作成日		:   2021/11/03											*/
/* 最終更新日	:   2021/11/04											*/
/* 作成者		:	山田龍之介											*/
/* -------------------------------------------------------------------- */
#include "ImageInputer.h"

/* -------------------------------------------------------------------- */
/* ■■■ public ■■■												    */
/* -------------------------------------------------------------------- */
/* 関数名	:	exe														*/
/* 機能名	:	ファイル書き込み機能									*/
/* 引数		:	:UCHR		pFilePath 		ファイルパスのアドレス		*/
/*  			:FileData	pFileData		格納先のファイルデータ		*/
/* 戻り値	:	:SINT		FAILE			失敗						*/
/*							SUCCESS			成功						*/
/* 作成日	:	2021/11/03		山田　龍之介							*/
/* -------------------------------------------------------------------- */
SINT ImageInputer::exe( FileData* pFileData,SCHR* pFilePath ) {
	SINT iIdentify;
	SINT iIdentifyPng;
	SINT iIdentifyJpg;
	SINT iCnt;
	SCHR *cpFilePathByte;
	SCHR cFileFormat[5];

	Conversion Conversion;
	FileIO FileIO;
	if ( pFilePath == NULL )
	{
		printf( "ファイルのPathの値が正常に参照できませんでした(ImageInputer) Line=%d \n", __LINE__ );
		return FAILE;
	}
	if (( cpFilePathByte = strrchr( pFilePath, '.' ) )==NULL) {
		printf( "対応していないファイルの形式の可能性があります(ImageInputer) Line=%d \n", __LINE__ );
		return FAILE;
	}
	strcpy( cFileFormat, cpFilePathByte );
	if ( (strcmp( cFileFormat,".jpg" ) ) != NULL &&
	( strcmp( cFileFormat, ".jpeg" ) ) != NULL &&
	( strcmp( cFileFormat, ".png" ) ) != NULL &&
	( strcmp( cFileFormat, ".bmp" ) ) != NULL )
	{
		printf( "対応していないファイルの可能性があります(ImageInputer) Line=%d \n",__LINE__ );
		return FAILE;
	}
	iIdentify = FileIO.read( pFilePath, &pFileData );
	

	switch (iIdentify)
	{
	////ファイルがBMPの場合は読み込みに成功した場合
	case SUCCESS:
		if ( pFileData->pInfoHData->sColor_Bit==Bit24 )
		{
			iIdentify = Conversion.exe( pFileData, Bit24 ,pFilePath);
			if ( iIdentify==FAILE )
			{
				printf( "ファイルの変換に失敗しました(ImageInputer) Line=%d \n",__LINE__ );
				return FAILE;
			}
		}
		if ( pFileData->pInfoHData->sColor_Bit == Bit8 )
		{
			iIdentify = Conversion.exe( pFileData, Bit8 ,pFilePath);
			if ( iIdentify == FAILE )
			{
				printf( "ファイルの変換に失敗しました(ImageInputer) Line=%d \n", __LINE__ );
				return FAILE;
			}
		}
		if ( pFileData->pInfoHData->sColor_Bit == Bit1 )
		{
			iIdentify = Conversion.exe( pFileData, Bit1 ,pFilePath);
			if ( iIdentify == FAILE )
			{
				printf( "ファイルの変換に失敗しました(ImageInputer) Line=%d \n", __LINE__ );
				return FAILE;
			}
		}
		break;
	//ファイルがPNGの時	
	case PNG:
		iIdentifyPng=Conversion.exe(pFileData, PNG,pFilePath);
		if (iIdentifyPng == FAILE)
		{
			return FAILE;
		}
		break;
	//ファイルがJPEGの時
	case JPEG:
		iIdentifyJpg=Conversion.exe(pFileData, JPEG,pFilePath);
		if (iIdentifyJpg == FAILE)
		{
			return FAILE;
		}
		
		break;
	//ファイルがBMPの場合で読み込みに失敗した場合
	default:
		printf( "規定外の数値が検出されました (ImageInputer) Line=%d \n", __LINE__ );
		return FAILE;
		break;
	}
	if ( pFileData->pInfoHData->uiWidth==NULL )
	{
		return FAILE;
	}
	if ( pFileData->pInfoHData->uiHeight == NULL )
	{
		return FAILE;
	}
	if ( pFileData->pInfoHData->sColor_Bit == NULL )
	{
		return FAILE;
	}
	if ( pFileData->pFileHData->sFile_Header_Name==0x4d42 )
	{

	}
	return SUCCESS;
}