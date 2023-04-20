/* -------------------------------------------------------------------- */
/* �t�@�C����	:	ColorConvert.cpp									*/
/* �@�\�T�v		:	�w��J���[bit�ɕϊ�									*/
/* �쐬��		:   2020/10/22											*/
/* �ŏI�X�V��	:   2020/11/04											*/
/* �쐬��		:	�R�c���V��											*/
/* -------------------------------------------------------------------- */
#include"ColorConvert.h"	

/* -------------------------------------------------------------------- */
/* ������ public ������												    */
/* -------------------------------------------------------------------- */
/* �֐���	:	exe														*/
/* �@�\��	:	exe														*/
/* ����		:	:FileData*		:pFileData		:�t�@�C���̃f�[�^		*/
/*				:SINT			:iDecoretinfo	:�������				*/
/* �߂�l	:	:FAILE			:-1				:���s					*/
/*				:SUCCESS		:0				:����					*/
/* �쐬��	:	2021/11/03		�R�c�@���V��							*/
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
/* ������ private ������											    */
/* -------------------------------------------------------------------- */
/* �֐���	:	exe														*/
/* �@�\��	:	bit1_convert											*/
/* ����		:	:FileData*		:pFileData		:�t�@�C���̃f�[�^		*/
/* �߂�l	:	:FAILE			:-1				:���s					*/
/*				:SUCCESS		:0				:����					*/
/* �쐬��	:	2021/11/03		�R�c�@���V��							*/
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
	//�J���[�r�b�g��1bit�ɕύX
	pFileData->pInfoHData->sColor_Bit = Bit1;
	//�摜�f�[�^�̃T�C�Y�����߂�
	iImageSize = ( pFileData->pInfoHData->uiHeight ) * ( pFileData->pInfoHData->uiWidth );
	//�摜�̉����̃T�C�Y���m��
	iLineSize = ((pFileData->pInfoHData->uiWidth + 7) / 8);
	//�p�f�B���O�̒l��ێ�
	iPadding = (4 - (iLineSize % 4)) % 4;
	//pImageData�̃T�C�Y��ۑ�
	iImageDataSize = (pFileData->pInfoHData->uiHeight * iLineSize) + (iPadding * pFileData->pInfoHData->uiHeight);
	//pPaletData�̃T�C�Y��ۑ�
	iPaletDataSize = 4 * 2;
	//1bit�̎��̃p���b�g�f�[�^
	pPaletData = ( UCHR* )calloc( iPaletDataSize, sizeof(UCHR) );
	//���̃f�[�^���i�[
	pPaletData[ 4 ] = 0xff;
	pPaletData[ 5 ] = 0xff;
	pPaletData[ 6 ] = 0xff;
	//1bit�̂Ƃ��̉摜�f�[�^
	pImageData = ( UCHR* )calloc( iImageDataSize, sizeof( UCHR ) );
	//�p���b�g�f�[�^�Ɖ摜�f�[�^�����킹���f�[�^���쐬
	pPaletImageData = ( UCHR* )calloc(( iImageDataSize) + ( iPaletDataSize ), sizeof( UCHR ) );
	//�t�@�C���I�t�Z�b�g�̕ύX
	pFileData->pFileHData->uiHeader_Size_Offset = 54 + ( iPaletDataSize );
	//�O���[�X�P�[����
	for ( iCnty = 0; iCnty < iImageSize; iCnty++ )
	{
		//BGR�̍��v�����߂�
		for ( iCntx = 0; iCntx < 3; iCntx++ )
		{
			iGrayScale += pFileData->pImageData[ (iCnty * 4) + iCntx ];
		}
		//BGR�̕��ς����߂�(�O���\�X�P�[�����̔����䗦)
		iGrayScale /= 3;
		//�摜�f�[�^�ɕ��ϒl�����߂�
		for ( iCntx = 0; iCntx < 3; iCntx++ )
		{
			pFileData->pImageData[ iCnty * 4 + iCntx ] = iGrayScale;
		}
		iGrayScale = 0;
	}
	//�摜�f�[�^���i�[
	for ( iCnty = 0; iCnty < pFileData->pInfoHData->uiHeight; iCnty++ )
	{
		for ( iCntx = 0; iCntx < pFileData->pInfoHData->uiWidth; iCntx++ )
		{
			//8�񃋁[�v���I���΃J�E���g��0�ɂ��ǂ�
			if ( iCntz >= 8 )
			{
				iCntz = 0;
				iCntw++;
			}
			
			//�摜�f�[�^�̊Y���̈ʒu�Ƀr�b�g�𗧂Ă�
			if ( pFileData->pImageData[(iCnty*pFileData->pInfoHData->uiWidth * 4) + (iCntx * 4)] > 125 ) {
				printf( "���o�恁%x\n", pFileData->pImageData[(iCnty*pFileData->pInfoHData->uiWidth * 4) + (iCntx * 4)] );
				
				pImageData[(iCnty*iLineSize) + (iCnty*iPadding)] = pImageData[(iCnty*iLineSize) + (iCnty*iPadding)] | (1 << (7 - iCntz));
			}
			else
			{
				printf( "���o�恁%x\n", pFileData->pImageData[(iCnty*pFileData->pInfoHData->uiWidth * 4) + (iCntx * 4)] );
				pImageData[(iCnty*iLineSize) + (iCnty*iPadding)]=pImageData[(iCnty*iLineSize) + (iCnty*iPadding)] & (~((1 << (7 - iCntz))));
			}
			iCntz++;
		}
		iCntz = 0;
		iCntw++;
	}
	//�t�@�C���f�[�^�ɉ摜�����i�[
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
/* �֐���	:	exe														*/
/* �@�\��	:	bit8_convert											*/
/* ����		:	:FileData*		:pFileData		:�t�@�C���̃f�[�^		*/
/* �߂�l	:	:FAILE			:-1				:���s					*/
/*				:SUCCESS		:0				:����					*/
/* �쐬��	:	2021/11/03		�R�c�@���V��							*/
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
		printf("�n���ꂽ�������m�ۂł��Ă��Ȃ��\��������܂�\n" );
#endif // TEST
		return FAILE;
	}
	//�J���[�r�b�g�̕ύX
	pFileData->pInfoHData->sColor_Bit = Bit8;
	//�摜�S�̂̃T�C�Y�����߂�
	iImageSize = ( pFileData->pInfoHData->uiHeight ) * ( pFileData->pInfoHData->uiWidth );
	//�p�f�B���O�̒l��ێ�
	iPadding = (4-pFileData->pInfoHData->uiWidth%4)%4;
	//pImagaData�̃T�C�Y��ێ�
	iImageDataSize = ((pFileData->pInfoHData->uiHeight)*(pFileData->pInfoHData->uiWidth)) + (iPadding*pFileData->pInfoHData->uiHeight);
	//pPaletData�̃T�C�Y��ێ�
	iPaletDataSize = 256 * 4;
	//�J���[�p���b�g���܂߂��摜�f�[�^���쐬
	pPaletImageData = ( UCHR* )calloc( (iPaletDataSize) + (iImageDataSize), sizeof( UCHR ) );
	//�t�@�C���I�t�Z�b�g�̕ύX
	pFileData->pFileHData->uiHeader_Size_Offset = 54 + (iPaletDataSize);
	
	//�O���[�X�P�[���J���[�p���b�g���쐬
	for ( iCnty = 0; iCnty < 256; iCnty++ )
	{
		for ( iCntx = 0; iCntx < 3; iCntx++ )
		{
			pPaletImageData[iCnty * 4 + iCntx] = iCnty;
		}
	}
	//�摜���O���[�X�P�[��������(8bit�̉摜�f�[�^�ɂ����
	for ( iCnty = 0; iCnty < pFileData->pInfoHData->uiHeight; iCnty++ )
	{
		for ( iCntx = 0; iCntx < pFileData->pInfoHData->uiWidth; iCntx++ )
		{
			iGrayScale += pFileData->pImageData[((iCnty*pFileData->pInfoHData->uiWidth*4) ) + (iCntx * 4)] ;
			iGrayScale += pFileData->pImageData[((iCnty*pFileData->pInfoHData->uiWidth*4) ) + (iCntx * 4 + 1)];
			iGrayScale += pFileData->pImageData[((iCnty*pFileData->pInfoHData->uiWidth*4) ) + (iCntx * 4 + 2)];
			//�O���[�X�P�[���̒l�����߂�
			iGrayScale /= 3;
			pPaletImageData[(iPaletDataSize) + (iCnty*pFileData->pInfoHData->uiWidth) + (iCntx) + (iCnty*iPadding)] = iGrayScale;
			iGrayScale = 0;
		}
	}
	//�p���b�g�f�[�^�ƃC���[�W�f�[�^�̕����f�[�^���t�@�C���f�[�^�ɓ���ւ���
	free( pFileData->pImageData );
	pFileData->pImageData = pPaletImageData;
	pFileData->pInfoHData->sColor_Bit = 8;
	//�J���[�p���b�g���t�@�C���f�[�^�I�t�Z�b�g�ɑ������킹��
	pFileData->pFileHData->uiHeader_Size_Offset = sizeof( FileHeader ) + pFileData->pInfoHData->uiInfo_HeaderSize + iPaletDataSize;
	return SUCCESS;
}

/* -------------------------------------------------------------------- */
/* �֐���	:	exe														*/
/* �@�\��	:	bit24_convert											*/
/* ����		:	:FileData*		:pFileData		:�t�@�C���̃f�[�^		*/
/* �߂�l	:	:FAILE			:-1				:���s					*/
/*				:SUCCESS		:0				:����					*/
/* �쐬��	:	2021/11/03		�R�c�@���V��							*/
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
		printf( "pFileData��NULL�ł����B�l���m�ۂł��Ă��Ȃ��\��������܂��B\n" );
		return FAILE;
	}
	//�J���[�r�b�g�̕ύX
	pFileData->pInfoHData->sColor_Bit = Bit24;
	//�摜�S�̂̃T�C�Y���m��
	iImageSize = ( pFileData->pInfoHData->uiHeight ) * ( pFileData->pInfoHData->uiWidth );
	// �p�f�B���O�������̒l�����߂�
	iLineSize = pFileData->pInfoHData->uiWidth * 3;
	//�p�f�B���O�̒l��ێ�
	iPadding = ( ( ( pFileData->pInfoHData->uiWidth ) * 4 ) - iLineSize ) % 4;
	//24bit�p�̉摜�f�[�^���_�C�i�~�b�N�������Ɋm��
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
	//�摜�f�[�^�����ւ���
	free( pFileData->pImageData );
	pFileData->pImageData = pImageData;
	pFileData->pInfoHData->sColor_Bit = 24;
	return SUCCESS;
}

/* -------------------------------------------------------------------- */
/* �֐���	:	exe														*/
/* �@�\��	:	bit32_convert											*/
/* ����		:	:FileData*		:pFileData		:�t�@�C���̃f�[�^		*/
/* �߂�l	:	:FAILE			:-1				:���s					*/
/*				:SUCCESS		:0				:����					*/
/* �쐬��	:	2021/11/03		�R�c�@���V��							*/
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
		printf( "�p���b�g�f�[�^��ǂݍ��ނƂ��̃t�@�C���I�[�v���Ŏ��s���܂���\n" );
#endif // TEST
		return FAILE;
	}
	//�摜�f�[�^�̃f�[�^��stat_buff�Ɋi�[
	stat( pFilePath, &stat_buff );
	//�摜�S�̂̃T�C�Y���m��
	iImageSize = ( pFileData->pInfoHData->uiHeight ) * ( pFileData->pInfoHData->uiWidth );
	//32bit�摜�f�[�^���i�[����
	pPaletImageData = ( UCHR* )calloc( iImageSize * 4, sizeof( UCHR ) );
	/*--------------------------------------------------------------------------------*/
	if ( pFileData->pInfoHData->sColor_Bit == Bit1 )
	{
		//�p���b�g�f�[�^���m��
		pPaletData = ( UCHR* )calloc( pFileData->pFileHData->uiHeader_Size_Offset - ( sizeof( FileHeader ) + sizeof( InformationHeader ) ), sizeof (UCHR ) );
		//�p���b�g�f�[�^�̎擾
		fseek( pFP, sizeof( FileHeader ) + pFileData->pInfoHData->uiInfo_HeaderSize, SEEK_SET );
		if ( NULL == (fread( pPaletData, 
			stat_buff.st_size - ((stat_buff.st_size - pFileData->pFileHData->uiHeader_Size_Offset) + (sizeof( FileHeader ) + pFileData->pInfoHData->uiInfo_HeaderSize)), 1, pFP )) ) {
#ifdef TEST
			printf( "�p���b�g�f�[�^�̓ǂݍ��݂Ɏ��s���܂���\n" );
#endif // TEST
			return FAILE;
		}
		//�摜�̉����̃T�C�Y���m��
		iLineSize = ((pFileData->pInfoHData->uiWidth + 7) / 8);
		//�p�f�B���O�̒l��ێ�
		iPadding = (4 - (iLineSize % 4)) % 4;
		//�摜�f�[�^�ɓ����Ă���p���b�g�̔ԍ����擾����
		for (  iCnty = 0; iCnty < pFileData->pInfoHData->uiHeight; iCnty++ )
		{
			for (  iCntx = 0; iCntx < pFileData->pInfoHData->uiWidth; iCntx++ )
			{
				//8�񃋁[�v���I���΃J�E���g��0�ɂ��ǂ�
				if ( iCntz >= 8 )
				{
					iCntz = 0;
				}
				//�R�s�[��̃f�[�^���擾
				if ( iCntz==0 )
				{
					cRestore = pFileData->pImageData[(iCnty*(iLineSize)) + (iCntw) + (iCnty*iPadding)];
					iCntw++;
				}
				//�f�[�^���R�s�[��ɉf��
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
		//�p���b�g�f�[�^���m��
		pPaletData = (UCHR*)calloc( (256 * 4), sizeof( UCHR ) );
		//�p���b�g�f�[�^�̎擾
		fseek( pFP, sizeof( FileHeader ) + pFileData->pInfoHData->uiInfo_HeaderSize, SEEK_SET );
		if ( NULL == (fread( pPaletData, pFileData->pFileHData->uiHeader_Size_Offset - (sizeof( FileHeader ) + pFileData->pInfoHData->uiInfo_HeaderSize), 1, pFP )) ) {
#ifdef TEST
			printf( "�p���b�g�f�[�^�̓ǂݍ��݂Ɏ��s���܂���\n" );
#endif // TEST
			return FAILE;
		}
		//�p�f�B���O�̒l��ێ�
		iPadding = (4 - ((pFileData->pInfoHData->uiWidth) % 4)) % 4;
		//�摜�f�[�^�ɓ����Ă���p���b�g�̔ԍ����擾����
		for ( iCnty = 0; iCnty < pFileData->pInfoHData->uiHeight ; iCnty++ )
		{
				//�擾�����l�̏ꏊ����3byte���̐F�����擾
				for ( iCntx = 0; iCntx < pFileData->pInfoHData->uiWidth; iCntx++ )
				{
#ifdef TEST
					printf( "�摜�f�[�^�̓��e��%d\n", pFileData->pImageData[(iCnty*pFileData->pInfoHData->uiWidth)+iCntx + (iCnty * iPadding)] );	
					printf( "����%d\n", pPaletData[((pFileData->pImageData[(iCnty*pFileData->pInfoHData->uiWidth)+ iCntx + (iCnty * iPadding)] ) * 4) + 0] );
#endif // TEST
					pPaletImageData[(iCnty*pFileData->pInfoHData->uiWidth * 4) + ((iCntx * 4))]
						= pPaletData[((pFileData->pImageData[(iCnty*pFileData->pInfoHData->uiWidth) + iCntx + (iCnty * iPadding)]) * 4) + 0];
					pPaletImageData[(iCnty*pFileData->pInfoHData->uiWidth * 4) + ((iCntx * 4) + 1)]
						= pPaletData[((pFileData->pImageData[(iCnty*pFileData->pInfoHData->uiWidth) + iCntx + (iCnty * iPadding)]) * 4) + 1];
					pPaletImageData[(iCnty*pFileData->pInfoHData->uiWidth * 4) + ((iCntx * 4) + 2)]
						= pPaletData[((pFileData->pImageData[(iCnty*pFileData->pInfoHData->uiWidth) + iCntx + (iCnty * iPadding)]) * 4) + 2];
#ifdef TEST
					printf( "�恁%d\n", pPaletImageData[(iCnty*pFileData->pInfoHData->uiWidth * 4) + ((iCntx * 4)) + 0] );
#endif // TEST
				}

		}
	}
	/*------------------------------------------------------------------------------*/
	if ( pFileData->pInfoHData->sColor_Bit == Bit24 )
	{
		// �p�f�B���O�������̒l�����߂�
		iLineSize = pFileData->pInfoHData->uiWidth * 3;
		//�p�f�B���O�̒l��ێ�
		iPadding = (((pFileData->pInfoHData->uiWidth) * 4) - iLineSize) % 4;
		//24bit�̉摜����32bit�̉摜�f�[�^�Ɋi�[���Ȃ���
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