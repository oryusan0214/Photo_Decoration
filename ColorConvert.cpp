/* -------------------------------------------------------------------- */
/* ファイル名	:	ColorConvert.cpp									*/
/* 機能概要		:	指定カラーbitに変換									*/
/* 作成日		:   2020/10/22											*/
/* 最終更新日	:   2020/11/04											*/
/* 作成者		:	山田龍之介											*/
/* -------------------------------------------------------------------- */
#include"ColorConvert.h"	

/* -------------------------------------------------------------------- */
/* ■■■ public ■■■												    */
/* -------------------------------------------------------------------- */
/* 関数名	:	exe														*/
/* 機能名	:	exe														*/
/* 引数		:	:FileData*		:pFileData		:ファイルのデータ		*/
/*				:SINT			:iDecoretinfo	:装飾情報				*/
/* 戻り値	:	:FAILE			:-1				:失敗					*/
/*				:SUCCESS		:0				:成功					*/
/* 作成日	:	2021/11/03		山田　龍之介							*/
/* -------------------------------------------------------------------- */
SINT ColorConvert::exe( FileData *pFileData,SINT iDecoretInfo ,SCHR *pFilePath) {
	
	switch ( iDecoretInfo )
	{
	case 1:
		ColorConvert::bit1_convert( pFileData );
		break;
	case 8:
		ColorConvert::bit8_convert( pFileData );
		break;
	case 24:
		ColorConvert::bit24_convert( pFileData );
		break;
	case 32:
		ColorConvert::bit32_convert( pFileData , pFilePath);
		break;
			
	default:
		return FAILE;
		break;
	}
}

/* -------------------------------------------------------------------- */
/* ■■■ private ■■■											    */
/* -------------------------------------------------------------------- */
/* 関数名	:	exe														*/
/* 機能名	:	bit1_convert											*/
/* 引数		:	:FileData*		:pFileData		:ファイルのデータ		*/
/* 戻り値	:	:FAILE			:-1				:失敗					*/
/*				:SUCCESS		:0				:成功					*/
/* 作成日	:	2021/11/03		山田　龍之介							*/
/* -------------------------------------------------------------------- */
SINT ColorConvert::bit1_convert( FileData *pFileData ) {

	SINT iCntx;
	SINT iCnty;
	SINT iCntz = 0;
	SINT iCntw = 0;
	SINT iLineSize;
	SINT iImageSize;
	SINT iGrayScale=0;
	SINT iPadding;
	SINT iImageDataSize;
	SINT iPaletDataSize;
	UCHR cRestore;
	UCHR cCopy;
	UCHR c;
	UCHR *pImageData;
	UCHR *pPaletData;
	UCHR *pPaletImageData;

	if ( pFileData==NULL )
	{
		return FAILE;
	}
	//カラービットを1bitに変更
	pFileData->pInfoHData->sColor_Bit = Bit1;
	//画像データのサイズを求める
	iImageSize = ( pFileData->pInfoHData->uiHeight ) * ( pFileData->pInfoHData->uiWidth );
	//画像の横幅のサイズを確保
	iLineSize = ((pFileData->pInfoHData->uiWidth + 7) / 8);
	//パディングの値を保持
	iPadding = (4 - (iLineSize % 4)) % 4;
	//pImageDataのサイズを保存
	iImageDataSize = (pFileData->pInfoHData->uiHeight * iLineSize) + (iPadding * pFileData->pInfoHData->uiHeight);
	//pPaletDataのサイズを保存
	iPaletDataSize = 4 * 2;
	//1bitの時のパレットデータ
	pPaletData = ( UCHR* )calloc( iPaletDataSize, sizeof(UCHR) );
	//白のデータを格納
	pPaletData[ 4 ] = 0xff;
	pPaletData[ 5 ] = 0xff;
	pPaletData[ 6 ] = 0xff;
	//1bitのときの画像データ
	pImageData = ( UCHR* )calloc( iImageDataSize, sizeof( UCHR ) );
	//パレットデータと画像データを合わせたデータを作成
	pPaletImageData = ( UCHR* )calloc(( iImageDataSize) + ( iPaletDataSize ), sizeof( UCHR ) );
	//ファイルオフセットの変更
	pFileData->pFileHData->uiHeader_Size_Offset = 54 + ( iPaletDataSize );
	//グレースケール化
	for ( iCnty = 0; iCnty < iImageSize; iCnty++ )
	{
		//BGRの合計を求める
		for ( iCntx = 0; iCntx < 3; iCntx++ )
		{
			iGrayScale += pFileData->pImageData[ (iCnty * 4) + iCntx ];
		}
		//BGRの平均を求める(グレ―スケール時の白黒比率)
		iGrayScale /= 3;
		//画像データに平均値を求める
		for ( iCntx = 0; iCntx < 3; iCntx++ )
		{
			pFileData->pImageData[ iCnty * 4 + iCntx ] = iGrayScale;
		}
		iGrayScale = 0;
	}
	//画像データを格納
	for ( iCnty = 0; iCnty < pFileData->pInfoHData->uiHeight; iCnty++ )
	{
		for ( iCntx = 0; iCntx < pFileData->pInfoHData->uiWidth; iCntx++ )
		{
			//8回ループが終わればカウントを0にもどす
			if ( iCntz >= 8 )
			{
				iCntz = 0;
				iCntw++;
			}
			
			//画像データの該当の位置にビットを立てる
			if ( pFileData->pImageData[(iCnty*pFileData->pInfoHData->uiWidth * 4) + (iCntx * 4)] > 125 ) {
				printf( "中出先＝%x\n", pFileData->pImageData[(iCnty*pFileData->pInfoHData->uiWidth * 4) + (iCntx * 4)] );
				
				pImageData[(iCnty*iLineSize) + (iCnty*iPadding)] = pImageData[(iCnty*iLineSize) + (iCnty*iPadding)] | (1 << (7 - iCntz));
			}
			else
			{
				printf( "中出先＝%x\n", pFileData->pImageData[(iCnty*pFileData->pInfoHData->uiWidth * 4) + (iCntx * 4)] );
				pImageData[(iCnty*iLineSize) + (iCnty*iPadding)]=pImageData[(iCnty*iLineSize) + (iCnty*iPadding)] & (~((1 << (7 - iCntz))));
			}
			iCntz++;
		}
		iCntz = 0;
		iCntw++;
	}
	//ファイルデータに画像情報を格納
	for ( iCnty = 0; iCnty < ( iPaletDataSize ); iCnty++ )
	{
		pPaletImageData [iCnty ] = pPaletData[ iCnty ];
	}
	for ( iCnty = 0; iCnty < ( iImageDataSize ); iCnty++ )
	{
		pPaletImageData[ ( iPaletDataSize ) + iCnty ] = pImageData[ iCnty ];
	}
	free( pFileData->pImageData );
	pFileData->pImageData = pPaletImageData;
	pFileData->pInfoHData->sColor_Bit = 1;
	pFileData->pFileHData->uiHeader_Size_Offset = pFileData->pInfoHData->uiInfo_HeaderSize + sizeof( FileHeader ) + (2 * 4);
	return SUCCESS;
}

/* -------------------------------------------------------------------- */
/* 関数名	:	exe														*/
/* 機能名	:	bit8_convert											*/
/* 引数		:	:FileData*		:pFileData		:ファイルのデータ		*/
/* 戻り値	:	:FAILE			:-1				:失敗					*/
/*				:SUCCESS		:0				:成功					*/
/* 作成日	:	2021/11/03		山田　龍之介							*/
/* -------------------------------------------------------------------- */
SINT ColorConvert::bit8_convert(FileData *pFileData) {
	SINT iCntx;
	SINT iCnty;
	SINT iImageSize;
	SINT iPadding;
	SINT iLineSize;
	SINT iImageDataSize;
	SINT iPaletDataSize;
	SINT iGrayScale=0;
	UCHR *pImageData;
	UCHR *pPaletData;
	UCHR *pPaletImageData;
	if ( pFileData==NULL )
	{
#ifdef TEST
		printf("渡された引数が確保できていない可能性があります\n" );
#endif // TEST
		return FAILE;
	}
	//カラービットの変更
	pFileData->pInfoHData->sColor_Bit = Bit8;
	//画像全体のサイズを求める
	iImageSize = ( pFileData->pInfoHData->uiHeight ) * ( pFileData->pInfoHData->uiWidth );
	//パディングの値を保持
	iPadding = (4-pFileData->pInfoHData->uiWidth%4)%4;
	//pImagaDataのサイズを保持
	iImageDataSize = ((pFileData->pInfoHData->uiHeight)*(pFileData->pInfoHData->uiWidth)) + (iPadding*pFileData->pInfoHData->uiHeight);
	//pPaletDataのサイズを保持
	iPaletDataSize = 256 * 4;
	//カラーパレットも含めた画像データを作成
	pPaletImageData = ( UCHR* )calloc( (iPaletDataSize) + (iImageDataSize), sizeof( UCHR ) );
	//ファイルオフセットの変更
	pFileData->pFileHData->uiHeader_Size_Offset = 54 + (iPaletDataSize);
	
	//グレースケールカラーパレットを作成
	for ( iCnty = 0; iCnty < 256; iCnty++ )
	{
		for ( iCntx = 0; iCntx < 3; iCntx++ )
		{
			pPaletImageData[iCnty * 4 + iCntx] = iCnty;
		}
	}
	//画像をグレースケール化する(8bitの画像データにいれる
	for ( iCnty = 0; iCnty < pFileData->pInfoHData->uiHeight; iCnty++ )
	{
		for ( iCntx = 0; iCntx < pFileData->pInfoHData->uiWidth; iCntx++ )
		{
			iGrayScale += pFileData->pImageData[((iCnty*pFileData->pInfoHData->uiWidth*4) ) + (iCntx * 4)] ;
			iGrayScale += pFileData->pImageData[((iCnty*pFileData->pInfoHData->uiWidth*4) ) + (iCntx * 4 + 1)];
			iGrayScale += pFileData->pImageData[((iCnty*pFileData->pInfoHData->uiWidth*4) ) + (iCntx * 4 + 2)];
			//グレースケールの値を求める
			iGrayScale /= 3;
			pPaletImageData[(iPaletDataSize) + (iCnty*pFileData->pInfoHData->uiWidth) + (iCntx) + (iCnty*iPadding)] = iGrayScale;
			iGrayScale = 0;
		}
	}
	//パレットデータとイメージデータの複合データをファイルデータに入れ替える
	free( pFileData->pImageData );
	pFileData->pImageData = pPaletImageData;
	pFileData->pInfoHData->sColor_Bit = 8;
	//カラーパレット分ファイルデータオフセットに足し合わせる
	pFileData->pFileHData->uiHeader_Size_Offset = sizeof( FileHeader ) + pFileData->pInfoHData->uiInfo_HeaderSize + iPaletDataSize;
	return SUCCESS;
}

/* -------------------------------------------------------------------- */
/* 関数名	:	exe														*/
/* 機能名	:	bit24_convert											*/
/* 引数		:	:FileData*		:pFileData		:ファイルのデータ		*/
/* 戻り値	:	:FAILE			:-1				:失敗					*/
/*				:SUCCESS		:0				:成功					*/
/* 作成日	:	2021/11/03		山田　龍之介							*/
/* -------------------------------------------------------------------- */

SINT ColorConvert::bit24_convert( FileData *pFileData ) {
	SINT iCntx;
	SINT iCnty;
	SINT iCntz = 0;
	SINT iImageSize;
	SINT iPadding;
	SINT iLineSize;
	UCHR *pImageData;
	
	if ( pFileData==NULL )
	{
		printf( "pFileDataがNULLでした。値が確保できていない可能性があります。\n" );
		return FAILE;
	}
	//カラービットの変更
	pFileData->pInfoHData->sColor_Bit = Bit24;
	//画像全体のサイズを確保
	iImageSize = ( pFileData->pInfoHData->uiHeight ) * ( pFileData->pInfoHData->uiWidth );
	// パディング無し幅の値を求める
	iLineSize = pFileData->pInfoHData->uiWidth * 3;
	//パディングの値を保持
	iPadding = ( ( ( pFileData->pInfoHData->uiWidth ) * 4 ) - iLineSize ) % 4;
	//24bit用の画像データをダイナミックメモリに確保
	pImageData = (UCHR*)calloc( ((iImageSize) * 3) + (iPadding * (pFileData->pInfoHData->uiHeight)), sizeof( UCHR ) );
	for ( iCnty = 0; iCnty < pFileData->pInfoHData->uiHeight; iCnty++ )
	{
		for (  iCntx = 0; iCntx < pFileData->pInfoHData->uiWidth; iCntx++ )
		{
			pImageData[(iCnty*pFileData->pInfoHData->uiWidth *3) + (iCntx*3) + iCnty * iPadding]
				= pFileData->pImageData[iCnty*pFileData->pInfoHData->uiWidth * 4 + (iCntx * 4)];
			pImageData[(iCnty*pFileData->pInfoHData->uiWidth*3) + (iCntx*3+ 1) + iCnty * iPadding]
				= pFileData->pImageData[iCnty*pFileData->pInfoHData->uiWidth * 4 + (iCntx * 4 + 1)];
			pImageData[(iCnty*pFileData->pInfoHData->uiWidth*3) + (iCntx*3 +2) + iCnty * iPadding]
				= pFileData->pImageData[iCnty*pFileData->pInfoHData->uiWidth * 4 + (iCntx * 4 + 2)];
		}

	}
	//画像データを入れ替える
	free( pFileData->pImageData );
	pFileData->pImageData = pImageData;
	pFileData->pInfoHData->sColor_Bit = 24;
	return SUCCESS;
}

/* -------------------------------------------------------------------- */
/* 関数名	:	exe														*/
/* 機能名	:	bit32_convert											*/
/* 引数		:	:FileData*		:pFileData		:ファイルのデータ		*/
/* 戻り値	:	:FAILE			:-1				:失敗					*/
/*				:SUCCESS		:0				:成功					*/
/* 作成日	:	2021/11/03		山田　龍之介							*/
/* -------------------------------------------------------------------- */
SINT ColorConvert::bit32_convert( FileData *pFileData,SCHR *pFilePath ) {
	SINT iCntx;
	SINT iCnty;
	SINT iCntz = 0;
	SINT iCntw = 0;
	SINT iImageSize;
	SINT iGrayScale;
	SINT iPadding;
	SINT iLineSize;
	UCHR cRestore;
	UCHR cCopy;
	UCHR *pPaletData=NULL;
	UCHR *pPaletImageData=NULL;
	struct stat stat_buff;
	FILE *pFP;
	if ( (pFP = fopen( pFilePath, "rb+" )) == NULL ) {
#ifdef TEST
		printf( "パレットデータを読み込むときのファイルオープンで失敗しました\n" );
#endif // TEST
		return FAILE;
	}
	//画像データのデータをstat_buffに格納
	stat( pFilePath, &stat_buff );
	//画像全体のサイズを確保
	iImageSize = ( pFileData->pInfoHData->uiHeight ) * ( pFileData->pInfoHData->uiWidth );
	//32bit画像データを格納する
	pPaletImageData = ( UCHR* )calloc( iImageSize * 4, sizeof( UCHR ) );
	/*--------------------------------------------------------------------------------*/
	if ( pFileData->pInfoHData->sColor_Bit == Bit1 )
	{
		//パレットデータを確保
		pPaletData = ( UCHR* )calloc( pFileData->pFileHData->uiHeader_Size_Offset - ( sizeof( FileHeader ) + sizeof( InformationHeader ) ), sizeof (UCHR ) );
		//パレットデータの取得
		fseek( pFP, sizeof( FileHeader ) + pFileData->pInfoHData->uiInfo_HeaderSize, SEEK_SET );
		if ( NULL == (fread( pPaletData, 
			stat_buff.st_size - ((stat_buff.st_size - pFileData->pFileHData->uiHeader_Size_Offset) + (sizeof( FileHeader ) + pFileData->pInfoHData->uiInfo_HeaderSize)), 1, pFP )) ) {
#ifdef TEST
			printf( "パレットデータの読み込みに失敗しました\n" );
#endif // TEST
			return FAILE;
		}
		//画像の横幅のサイズを確保
		iLineSize = ((pFileData->pInfoHData->uiWidth + 7) / 8);
		//パディングの値を保持
		iPadding = (4 - (iLineSize % 4)) % 4;
		//画像データに入っているパレットの番号を取得する
		for (  iCnty = 0; iCnty < pFileData->pInfoHData->uiHeight; iCnty++ )
		{
			for (  iCntx = 0; iCntx < pFileData->pInfoHData->uiWidth; iCntx++ )
			{
				//8回ループが終わればカウントを0にもどす
				if ( iCntz >= 8 )
				{
					iCntz = 0;
				}
				//コピー先のデータを取得
				if ( iCntz==0 )
				{
					cRestore = pFileData->pImageData[(iCnty*(iLineSize)) + (iCntw) + (iCnty*iPadding)];
					iCntw++;
				}
				//データをコピー先に映す
				cCopy = cRestore;
				if ( (cCopy >> (7-iCntz)) & 0x01 )
				{
					pPaletImageData[(iCnty*pFileData->pInfoHData->uiWidth * 4) + (iCntx * 4)] = 0xFF;
					pPaletImageData[(iCnty*pFileData->pInfoHData->uiWidth * 4) + ((iCntx * 4) + 1)] = 0xFF;
					pPaletImageData[(iCnty*pFileData->pInfoHData->uiWidth * 4) + ((iCntx * 4) + 2)] = 0xFF;
				}
				else
				{
					pPaletImageData[(iCnty*pFileData->pInfoHData->uiWidth * 4) + (iCntx * 4)] = 0x00;
					pPaletImageData[(iCnty*pFileData->pInfoHData->uiWidth * 4) + ((iCntx * 4) + 1)] = 0x00;
					pPaletImageData[(iCnty*pFileData->pInfoHData->uiWidth * 4) + ((iCntx * 4) + 2)] = 0x00;
				}
				iCntz++;
			}
			iCntz = 0;
			iCntw = 0;
		}
	}
	/*------------------------------------------------------------------------------*/
	if ( pFileData->pInfoHData->sColor_Bit == Bit8 )
	{
		//パレットデータを確保
		pPaletData = (UCHR*)calloc( (256 * 4), sizeof( UCHR ) );
		//パレットデータの取得
		fseek( pFP, sizeof( FileHeader ) + pFileData->pInfoHData->uiInfo_HeaderSize, SEEK_SET );
		if ( NULL == (fread( pPaletData, pFileData->pFileHData->uiHeader_Size_Offset - (sizeof( FileHeader ) + pFileData->pInfoHData->uiInfo_HeaderSize), 1, pFP )) ) {
#ifdef TEST
			printf( "パレットデータの読み込みに失敗しました\n" );
#endif // TEST
			return FAILE;
		}
		//パディングの値を保持
		iPadding = (4 - ((pFileData->pInfoHData->uiWidth) % 4)) % 4;
		//画像データに入っているパレットの番号を取得する
		for ( iCnty = 0; iCnty < pFileData->pInfoHData->uiHeight ; iCnty++ )
		{
				//取得した値の場所から3byte分の色情報を取得
				for ( iCntx = 0; iCntx < pFileData->pInfoHData->uiWidth; iCntx++ )
				{
#ifdef TEST
					printf( "画像データの内容＝%d\n", pFileData->pImageData[(iCnty*pFileData->pInfoHData->uiWidth)+iCntx + (iCnty * iPadding)] );	
					printf( "元＝%d\n", pPaletData[((pFileData->pImageData[(iCnty*pFileData->pInfoHData->uiWidth)+ iCntx + (iCnty * iPadding)] ) * 4) + 0] );
#endif // TEST
					pPaletImageData[(iCnty*pFileData->pInfoHData->uiWidth * 4) + ((iCntx * 4))]
						= pPaletData[((pFileData->pImageData[(iCnty*pFileData->pInfoHData->uiWidth) + iCntx + (iCnty * iPadding)]) * 4) + 0];
					pPaletImageData[(iCnty*pFileData->pInfoHData->uiWidth * 4) + ((iCntx * 4) + 1)]
						= pPaletData[((pFileData->pImageData[(iCnty*pFileData->pInfoHData->uiWidth) + iCntx + (iCnty * iPadding)]) * 4) + 1];
					pPaletImageData[(iCnty*pFileData->pInfoHData->uiWidth * 4) + ((iCntx * 4) + 2)]
						= pPaletData[((pFileData->pImageData[(iCnty*pFileData->pInfoHData->uiWidth) + iCntx + (iCnty * iPadding)]) * 4) + 2];
#ifdef TEST
					printf( "先＝%d\n", pPaletImageData[(iCnty*pFileData->pInfoHData->uiWidth * 4) + ((iCntx * 4)) + 0] );
#endif // TEST
				}

		}
	}
	/*------------------------------------------------------------------------------*/
	if ( pFileData->pInfoHData->sColor_Bit == Bit24 )
	{
		// パディング無し幅の値を求める
		iLineSize = pFileData->pInfoHData->uiWidth * 3;
		//パディングの値を保持
		iPadding = (((pFileData->pInfoHData->uiWidth) * 4) - iLineSize) % 4;
		//24bitの画像から32bitの画像データに格納しなおす
		for ( iCnty = 0; iCnty < pFileData->pInfoHData->uiHeight; iCnty++ )
		{
			for ( iCntx = 0; iCntx < pFileData->pInfoHData->uiWidth; iCntx++ )
			{
				pPaletImageData[(iCnty*pFileData->pInfoHData->uiWidth *4) + ((iCntx * 4) )]
					= pFileData->pImageData[iCnty*pFileData->pInfoHData->uiWidth * 3 + ((iCntx*3)) + (iCnty*iPadding)];
				pPaletImageData[(iCnty*pFileData->pInfoHData->uiWidth *4) + ((iCntx * 4) + 1)]
					= pFileData->pImageData[iCnty*pFileData->pInfoHData->uiWidth * 3 + ((iCntx*3) + 1) + (iCnty * iPadding)];
				pPaletImageData[(iCnty*pFileData->pInfoHData->uiWidth *4) + ((iCntx * 4) + 2)]
					= pFileData->pImageData[iCnty*pFileData->pInfoHData->uiWidth * 3 + ((iCntx*3) + 2) + (iCnty * iPadding)];
			}
		}
	}
	pFileData->pInfoHData->sColor_Bit = Bit32;
	pFileData->pFileHData->uiHeader_Size_Offset = pFileData->pInfoHData->uiInfo_HeaderSize + sizeof( FileHeader );
	free( pPaletData );
	free( pFileData->pImageData );
	pFileData->pImageData = pPaletImageData;
	fclose( pFP );
	return SUCCESS;
}