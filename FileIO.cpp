/* -------------------------------------------------------------------- */
/* ファイル名	:	FileIO.cpp											*/
/* 機能概要		:	ファイルの書き込み・読み込み						*/
/* 作成日		:   2020/10/20											*/
/* 最終更新日	:   2020/11/04											*/
/* 作成者		:	山田龍之介											*/
/* -------------------------------------------------------------------- */
#include "FileIO.h"

/* -------------------------------------------------------------------- */
/* ■■■ public ■■■												    */
/* -------------------------------------------------------------------- */
/* 関数名	:	FileIO													*/
/* 機能名	:	コンストラクタ											*/
/* 引数		:	なし													*/
/* 戻り値	:	なし													*/
/* 作成日	:	2021/11/03		山田　龍之介							*/
/* -------------------------------------------------------------------- */
FileIO::FileIO(  ) {
	memset( &stat_buff, 0, sizeof( struct stat ) );

	/* 初期化 */
	orizinalPath	= NULL;
	secondPath		= NULL;
	thirdPath		= NULL;
	fourthPath		= NULL;
	outputPath		= NULL;
	
}
/* -------------------------------------------------------------------- */
/* 関数名	:	FileIO													*/
/* 機能名	:	デストラクタ											*/
/* 引数		:	なし													*/
/* 戻り値	:	なし													*/
/* 作成日	:	2021/11/03		山田　龍之介							*/
/* -------------------------------------------------------------------- */
FileIO::~FileIO( ){
	
	/* 重複解放対策 */
	if ( orizinalPath != NULL  && orizinalPath != secondPath && orizinalPath != thirdPath &&
			orizinalPath != fourthPath && orizinalPath != outputPath ) {
		fclose( orizinalPath );
	}
	if ( secondPath != NULL && secondPath != thirdPath && secondPath != fourthPath && secondPath != outputPath ) {
		fclose( secondPath );
	}
	if ( thirdPath != NULL && thirdPath != fourthPath && thirdPath != outputPath ) {
		fclose( thirdPath );
	}
	if ( fourthPath != NULL && fourthPath != outputPath ) {
		fclose( fourthPath );
	}
	if ( outputPath != NULL ) {
		fclose( outputPath );
	}

}

/* -------------------------------------------------------------------- */
/* 関数名	:	FileIO													*/
/* 機能名	:	ファイルのリード										*/
/* 引数		:	:SCHR		ucFilePath 		ファイルパス(文字列)		*/
/*  			:FileData	pFileData		格納先のファイルデータ		*/
/* 戻り値	:	:FileData	NULL			失敗						*/
/*							FileData		中身を返す					*/
/*							PNG				PNGの情報を返す　　　　　　 */
/*							JPEG            JPEGの情報を返す			*/
/* 作成日	:	2021/11/03		山田　龍之介							*/
/* -------------------------------------------------------------------- */
SINT FileIO::read( SCHR *pFilePath,FileData **pFileData ) {
	SCHR Mode[] = { "rb" };
	UINT Reserved;
	UINT Test;
	if ( pFilePath==NULL )
	{
#ifdef TEST
		printf( "ファイルのPathが取得できませんでした Line=%d\n",__LINE__ );
#endif // TEST
		return FAILE;
	}
	if ( pFileData==NULL)
	{
#ifdef TEST
		printf( "ファイルの参照先のアドレスが取得できませんでした\n" );
#endif // TEST
		return FAILE;
	}
	if ( (*pFileData) == NULL )
	{
#ifdef TEST
		printf( "ファイルのDataの格納先が取得できませんでした Line=%d\n", __LINE__ );
#endif // TEST
		return FAILE;
	}
	//ファイルの情報を取得
	stat( pFilePath, &stat_buff );
	Reserved = (1024 * 1024 * 1024);
	if ( Reserved < (UINT)stat_buff.st_size  )
	{
#ifdef TEST
		printf( "1GBを超えるためファイルのreadができません\n" );
#endif // TEST
		return FAILE;
	}
	if ( (iIdetify = open( pFilePath, Mode ))==FAILE ) {
#ifdef TEST
		printf( "ファイルのopenでエラーが起きました　Line=%d\n", __LINE__ );
#endif // TEST
		return FAILE;
	}
	if ( (iIdetify = read( pFileData )) == FAILE ) {
#ifdef TEST
		printf( "ファイルのreadに失敗しました Line=%d\n", __LINE__ );
#endif // TEST
		return FAILE;
	}
	//画像データが壊れていないかを確かめる
	if ( (*pFileData)->pFileHData->sFile_Header_Name==0x4d42 )
	{
		switch ( (*pFileData)->pInfoHData->sColor_Bit )
		{
		case Bit32:
			Reserved=((*pFileData)->pInfoHData->uiWidth*(*pFileData)->pInfoHData->uiHeight) * 4;
			break;
		case Bit24:
			Reserved=(((*pFileData)->pInfoHData->uiWidth*(*pFileData)->pInfoHData->uiHeight) * 3)
				+ ((4 - (((*pFileData)->pInfoHData->uiWidth) * 3) % 4) % 4)*((*pFileData)->pInfoHData->uiHeight);
			break;
		case Bit8:
			Reserved = ((*pFileData)->pInfoHData->uiWidth*(*pFileData)->pInfoHData->uiHeight)
				+ ((4 - ((*pFileData)->pInfoHData->uiWidth) % 4) % 4)*((*pFileData)->pInfoHData->uiHeight);
			break;
		case Bit1:
			Reserved = ((((*pFileData)->pInfoHData->uiWidth+7)/8)*(*pFileData)->pInfoHData->uiHeight)
				+ ((4 - ((((*pFileData)->pInfoHData->uiWidth) + 7) / 8) % 4) % 4)*((*pFileData)->pInfoHData->uiHeight);
			break;
		default:
#ifdef TEST
			printf( "対応していないファイル形式の可能性があります\n" );
#endif // TEST
			return FAILE;
			break;
		}
		Test = (SINT)stat_buff.st_size - (*pFileData)->pFileHData->uiHeader_Size_Offset;
		if ( stat_buff.st_size - (*pFileData)->pFileHData->uiHeader_Size_Offset != Reserved 
			&& (*pFileData)->pInfoHData->sColor_Bit!=Bit32 ) {
#ifdef TEST
			printf( "ファイルのデータが破損している可能性があります\n" );
#endif // TEST
			return FAILE;
		}
		else if((*pFileData)->pInfoHData->sColor_Bit==Bit32&& Reserved > stat_buff.st_size - (*pFileData)->pFileHData->uiHeader_Size_Offset )
		{
			printf( "ファイルのデータが破損している可能性があります\n" );
			return FAILE;
		}
	}
	if ( iIdetify==PNG )
	{
		return PNG;
	}
	if ( iIdetify==JPEG )
	{
		return JPEG;
	}
	close( );
	return SUCCESS;
}

/* -------------------------------------------------------------------- */
/* ■■■ private ■■■											    */
/* -------------------------------------------------------------------- */
/* 関数名	:	write													*/
/* 機能名	:	ファイル書き込み機能									*/
/* 引数		:	:UCHR		pFilePath 		ファイルパスのアドレス		*/
/*  			:FileData	pFileData		格納先のファイルデータ		*/
/* 戻り値	:	:FileData	NULL			失敗						*/
/*							FileData		成功の時は中身を返す		*/
/* 作成日	:	2021/11/03		山田　龍之介							*/
/* -------------------------------------------------------------------- */
SINT FileIO::write( SCHR *pFilePath, FileData **pFileData ) {
	char Mode[] = { "wb" };
	iIdetify=open( pFilePath, Mode );
	if ( iIdetify==FAILE )
	{
#ifdef TEST
		printf( "ファイルのwriteメソッドでエラーが起きました　Line=%d\n", __LINE__ );
#endif // TEST
		return FAILE;
	}
	iIdetify=write( pFileData );
	if ( iIdetify==FAILE )
	{
#ifdef TEST
		printf( "ファイルの書き込みでエラーが起きました\n" );
#endif // TEST
		return FAILE;
	}
	close( );
	return SUCCESS;
}

/* -------------------------------------------------------------------- */
/* ■■■ private ■■■											    */
/* -------------------------------------------------------------------- */
/* 関数名	:	write													*/
/* 機能名	:	ファイル書き込み機能									*/
/* 引数		:	:UCHR		pFilePath 		ファイルパスのアドレス		*/
/*  			:FileData	pFileData		格納先のファイルデータ		*/
/* 戻り値	:	:FileData	NULL			失敗						*/
/*							FileData		成功の時は中身を返す		*/
/* 作成日	:	2021/11/03		山田　龍之介							*/
/* -------------------------------------------------------------------- */
SINT FileIO::open( SCHR *pFilePath, SCHR *pMode ) {
	if ( ( ( pFP ) = fopen( pFilePath, pMode ) ) == NULL ) {
#ifdef TEST
		printf("FileIO　openメソッド　ファイルのオープンに失敗しました　Line=%d\n",__LINE__);
#endif // TEST
		return FAILE;
	}
	return SUCCESS;
}

/* -------------------------------------------------------------------- */
/* 関数名	:	write													*/
/* 機能名	:	ファイル書き込み機能									*/
/* 引数		:	:UCHR		pFilePath 		ファイルパスのアドレス		*/
/*  			:FileData	pFileData		格納先のファイルデータ		*/
/* 戻り値	:	:FileData	NULL			失敗						*/
/*							FileData		成功の時は中身を返す		*/
/* 作成日	:	2021/11/03		山田　龍之介							*/
/* -------------------------------------------------------------------- */
SINT FileIO::read( FileData **pFileData ) {
	if ( ((*pFileData)->pFileHData = (FileHeader*)calloc( 1, sizeof( FileHeader ) )) == NULL ) {
#ifdef TEST
		printf( "ダイナミックメモリの確保に失敗しました  Line=%d \n", __LINE__ );
#endif // TEST
		return FAILE;
	}

	if ( ((*pFileData)->pInfoHData = (InformationHeader*)calloc( 1, sizeof( InformationHeader ) )) == NULL ) {
#ifdef TEST
		printf( "ダイナミックメモリの確保に失敗しました Line=%d \n", __LINE__ );
#endif // TEST
		return FAILE;
	}
	if ( ((*pFileData)->pImageData = (UCHR*)calloc( (stat_buff.st_size - (*pFileData)->pFileHData->uiHeader_Size_Offset), sizeof( UCHR )) )==NULL )
	{
#ifdef TEST
		printf( "ダイナミックメモリの確保に失敗しました Line=%d \n",__LINE__ );
#endif // TEST
		return FAILE;
	}
#pragma pack( 2 )
	if ( fread( (*pFileData)->pFileHData, sizeof( FileHeader ), 1, pFP ) == NULL )
	{
#ifdef TEST
		printf( "ヘッダーファイルの読み込みが失敗しました  Line=%d \n", __LINE__ );
#endif // TEST
		return FAILE;
	}
	if ( (*pFileData)->pFileHData->sFile_Header_Name!=0x4d42 )
	{
#ifdef TEST
		printf( "BMP以外の可能性..." );
#endif // TEST
		if ( (*pFileData)->pFileHData->sFile_Header_Name == 0x5089 )
		{
#ifdef TEST
			printf( "PNGでした\n" );
#endif // TEST
			return PNG;
		}
		if ( (*pFileData)->pFileHData->sFile_Header_Name == 0xD8FF )
		{
#ifdef TEST
			printf( "JPEGでした\n" );
#endif // TEST
			return JPEG;
		}
		else
		{
#ifdef TEST
			printf( "データが壊れている可能性もしくはデータが対応していないファイルの可能性があります\n" );
#endif // TEST
			return FAILE;
		}
	}
	
#pragma pack( )
	fseek( pFP, sizeof( FileHeader ), SEEK_SET );
	if ( fread( (*pFileData)->pInfoHData, sizeof( InformationHeader ), 1, pFP ) == NULL) {
#ifdef TEST
		printf( "情報ヘッダファイルの読み込みが失敗しました Line=%d \n",__LINE__ );
#endif // TEST
		return FAILE;
	}
	fseek( pFP, (*pFileData)->pFileHData->uiHeader_Size_Offset, SEEK_SET );
	if ( fread( (*pFileData)->pImageData, stat_buff.st_size-(*pFileData)->pFileHData->uiHeader_Size_Offset, 1, pFP ) == NULL) {
#ifdef TEST
		printf( "画像ファイルの読み込みが失敗しました Line=%d \n",__LINE__ );
#endif // TEST
		return FAILE;
	}
	return SUCCESS;
}

/* -------------------------------------------------------------------- */
/* 関数名	:	write													*/
/* 機能名	:	ファイル書き込み機能									*/
/* 引数		:	:UCHR		pFilePath 		ファイルパスのアドレス		*/
/*  			:FileData	pFileData		格納先のファイルデータ		*/
/* 戻り値	:	:FileData	NULL			失敗						*/
/*							FileData		成功の時は中身を返す		*/
/* 作成日	:	2021/11/03		山田　龍之介							*/
/* -------------------------------------------------------------------- */
SINT FileIO::write( FileData **pFileData ) {
	//パディングの値を保持
	SINT iPadding = NULL;
#ifdef TEST
	printf( "sizeof( (*pFileData)->pfileHData )=%d\n", sizeof( FileHeader ) );
	printf( "sizeof( (*pFileData)->pInfoHData )=%d\n", sizeof( InformationHeader) );
	printf( "sizeof( (*pFileData)->pImageData )=%d\n", ((*pFileData)->pInfoHData->uiHeight* (*pFileData)->pInfoHData->uiWidth)*4 );
#endif // TEST
#pragma pack(2)
	fwrite( (*pFileData)->pFileHData, sizeof( FileHeader ), 1, pFP );
#pragma pack( )
	fwrite( (*pFileData)->pInfoHData, sizeof( InformationHeader ), 1, pFP );
	switch ( (*pFileData)->pInfoHData->sColor_Bit )
	{
	case 1:
		iPadding = (4 - ((((*pFileData)->pInfoHData->uiWidth) + 7) / 8) % 4) % 4;
		fwrite( (*pFileData)->pImageData, ((*pFileData)->pInfoHData->uiHeight* ((((*pFileData)->pInfoHData->uiWidth) + 7) / 8)) + (8) + (iPadding *(*pFileData)->pInfoHData->uiHeight), 1, pFP );
		break;
	case 8:
		iPadding = (4 - (*pFileData)->pInfoHData->uiWidth % 4) % 4;
		fwrite( (*pFileData)->pImageData, ((*pFileData)->pInfoHData->uiHeight* ((*pFileData)->pInfoHData->uiWidth)) + (256 * 4) + (iPadding *(*pFileData)->pInfoHData->uiHeight), 1, pFP );
		break;
	case 24:
		iPadding = (4 - (((*pFileData)->pInfoHData->uiWidth) * 3) % 4) % 4;
		fwrite( (*pFileData)->pImageData, (((*pFileData)->pInfoHData->uiHeight* (*pFileData)->pInfoHData->uiWidth) * 3) + (iPadding *(*pFileData)->pInfoHData->uiHeight), 1, pFP );
		break;
	case 32:
		fwrite( (*pFileData)->pImageData, ((*pFileData)->pInfoHData->uiHeight* (*pFileData)->pInfoHData->uiWidth) * 4, 1, pFP );
		break;
	default:
		printf( "対応していないファイルフォーマットです\n" );
		return FAILE;
		break;
	}
	
	return SUCCESS;
}

/* -------------------------------------------------------------------- */
/* 関数名	:	close													*/
/* 機能名	:	ファイルのクローズ機能									*/
/* 作成日	:	2021/11/03		山田　龍之介							*/
/* -------------------------------------------------------------------- */
void FileIO::close( ) {

	fclose( pFP );
}