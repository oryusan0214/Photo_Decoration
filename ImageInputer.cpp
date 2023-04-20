/* -------------------------------------------------------------------- */
/* �t�@�C����	:	ImageInputer.cpp									*/
/* �@�\�T�v		:	���C���Ƀt�@�C���t�H�[�}�b�g�ɍ��킹���`�œn��		*/
/* �쐬��		:   2021/11/03											*/
/* �ŏI�X�V��	:   2021/11/04											*/
/* �쐬��		:	�R�c���V��											*/
/* -------------------------------------------------------------------- */
#include "ImageInputer.h"

/* -------------------------------------------------------------------- */
/* ������ public ������												    */
/* -------------------------------------------------------------------- */
/* �֐���	:	exe														*/
/* �@�\��	:	�t�@�C���������݋@�\									*/
/* ����		:	:UCHR		pFilePath 		�t�@�C���p�X�̃A�h���X		*/
/*  			:FileData	pFileData		�i�[��̃t�@�C���f�[�^		*/
/* �߂�l	:	:SINT		FAILE			���s						*/
/*							SUCCESS			����						*/
/* �쐬��	:	2021/11/03		�R�c�@���V��							*/
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
		printf( "�t�@�C����Path�̒l������ɎQ�Ƃł��܂���ł���(ImageInputer) Line=%d \n", __LINE__ );
		return FAILE;
	}
	if (( cpFilePathByte = strrchr( pFilePath, '.' ) )==NULL) {
		printf( "�Ή����Ă��Ȃ��t�@�C���̌`���̉\��������܂�(ImageInputer) Line=%d \n", __LINE__ );
		return FAILE;
	}
	strcpy( cFileFormat, cpFilePathByte );
	if ( (strcmp( cFileFormat,".jpg" ) ) != NULL &&
	( strcmp( cFileFormat, ".jpeg" ) ) != NULL &&
	( strcmp( cFileFormat, ".png" ) ) != NULL &&
	( strcmp( cFileFormat, ".bmp" ) ) != NULL )
	{
		printf( "�Ή����Ă��Ȃ��t�@�C���̉\��������܂�(ImageInputer) Line=%d \n",__LINE__ );
		return FAILE;
	}
	iIdentify = FileIO.read( pFilePath, &pFileData );
	

	switch (iIdentify)
	{
	////�t�@�C����BMP�̏ꍇ�͓ǂݍ��݂ɐ��������ꍇ
	case SUCCESS:
		if ( pFileData->pInfoHData->sColor_Bit==Bit24 )
		{
			iIdentify = Conversion.exe( pFileData, Bit24 ,pFilePath);
			if ( iIdentify==FAILE )
			{
				printf( "�t�@�C���̕ϊ��Ɏ��s���܂���(ImageInputer) Line=%d \n",__LINE__ );
				return FAILE;
			}
		}
		if ( pFileData->pInfoHData->sColor_Bit == Bit8 )
		{
			iIdentify = Conversion.exe( pFileData, Bit8 ,pFilePath);
			if ( iIdentify == FAILE )
			{
				printf( "�t�@�C���̕ϊ��Ɏ��s���܂���(ImageInputer) Line=%d \n", __LINE__ );
				return FAILE;
			}
		}
		if ( pFileData->pInfoHData->sColor_Bit == Bit1 )
		{
			iIdentify = Conversion.exe( pFileData, Bit1 ,pFilePath);
			if ( iIdentify == FAILE )
			{
				printf( "�t�@�C���̕ϊ��Ɏ��s���܂���(ImageInputer) Line=%d \n", __LINE__ );
				return FAILE;
			}
		}
		break;
	//�t�@�C����PNG�̎�	
	case PNG:
		iIdentifyPng=Conversion.exe(pFileData, PNG,pFilePath);
		if (iIdentifyPng == FAILE)
		{
			return FAILE;
		}
		break;
	//�t�@�C����JPEG�̎�
	case JPEG:
		iIdentifyJpg=Conversion.exe(pFileData, JPEG,pFilePath);
		if (iIdentifyJpg == FAILE)
		{
			return FAILE;
		}
		
		break;
	//�t�@�C����BMP�̏ꍇ�œǂݍ��݂Ɏ��s�����ꍇ
	default:
		printf( "�K��O�̐��l�����o����܂��� (ImageInputer) Line=%d \n", __LINE__ );
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