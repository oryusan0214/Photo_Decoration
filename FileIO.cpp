/* -------------------------------------------------------------------- */
/* �t�@�C����	:	FileIO.cpp											*/
/* �@�\�T�v		:	�t�@�C���̏������݁E�ǂݍ���						*/
/* �쐬��		:   2020/10/20											*/
/* �ŏI�X�V��	:   2020/11/04											*/
/* �쐬��		:	�R�c���V��											*/
/* -------------------------------------------------------------------- */
#include "FileIO.h"

/* -------------------------------------------------------------------- */
/* ������ public ������												    */
/* -------------------------------------------------------------------- */
/* �֐���	:	FileIO													*/
/* �@�\��	:	�R���X�g���N�^											*/
/* ����		:	�Ȃ�													*/
/* �߂�l	:	�Ȃ�													*/
/* �쐬��	:	2021/11/03		�R�c�@���V��							*/
/* -------------------------------------------------------------------- */
FileIO::FileIO(  ) {
	memset( &stat_buff, 0, sizeof( struct stat ) );

	/* ������ */
	orizinalPath	= NULL;
	secondPath		= NULL;
	thirdPath		= NULL;
	fourthPath		= NULL;
	outputPath		= NULL;
	
}
/* -------------------------------------------------------------------- */
/* �֐���	:	FileIO													*/
/* �@�\��	:	�f�X�g���N�^											*/
/* ����		:	�Ȃ�													*/
/* �߂�l	:	�Ȃ�													*/
/* �쐬��	:	2021/11/03		�R�c�@���V��							*/
/* -------------------------------------------------------------------- */
FileIO::~FileIO( ){
	
	/* �d������΍� */
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
/* �֐���	:	FileIO													*/
/* �@�\��	:	�t�@�C���̃��[�h										*/
/* ����		:	:SCHR		ucFilePath 		�t�@�C���p�X(������)		*/
/*  			:FileData	pFileData		�i�[��̃t�@�C���f�[�^		*/
/* �߂�l	:	:FileData	NULL			���s						*/
/*							FileData		���g��Ԃ�					*/
/*							PNG				PNG�̏���Ԃ��@�@�@�@�@�@ */
/*							JPEG            JPEG�̏���Ԃ�			*/
/* �쐬��	:	2021/11/03		�R�c�@���V��							*/
/* -------------------------------------------------------------------- */
SINT FileIO::read( SCHR *pFilePath,FileData **pFileData ) {
	SCHR Mode[] = { "rb" };
	UINT Reserved;
	UINT Test;
	if ( pFilePath==NULL )
	{
#ifdef TEST
		printf( "�t�@�C����Path���擾�ł��܂���ł��� Line=%d\n",__LINE__ );
#endif // TEST
		return FAILE;
	}
	if ( pFileData==NULL)
	{
#ifdef TEST
		printf( "�t�@�C���̎Q�Ɛ�̃A�h���X���擾�ł��܂���ł���\n" );
#endif // TEST
		return FAILE;
	}
	if ( (*pFileData) == NULL )
	{
#ifdef TEST
		printf( "�t�@�C����Data�̊i�[�悪�擾�ł��܂���ł��� Line=%d\n", __LINE__ );
#endif // TEST
		return FAILE;
	}
	//�t�@�C���̏����擾
	stat( pFilePath, &stat_buff );
	Reserved = (1024 * 1024 * 1024);
	if ( Reserved < (UINT)stat_buff.st_size  )
	{
#ifdef TEST
		printf( "1GB�𒴂��邽�߃t�@�C����read���ł��܂���\n" );
#endif // TEST
		return FAILE;
	}
	if ( (iIdetify = open( pFilePath, Mode ))==FAILE ) {
#ifdef TEST
		printf( "�t�@�C����open�ŃG���[���N���܂����@Line=%d\n", __LINE__ );
#endif // TEST
		return FAILE;
	}
	if ( (iIdetify = read( pFileData )) == FAILE ) {
#ifdef TEST
		printf( "�t�@�C����read�Ɏ��s���܂��� Line=%d\n", __LINE__ );
#endif // TEST
		return FAILE;
	}
	//�摜�f�[�^�����Ă��Ȃ������m���߂�
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
			printf( "�Ή����Ă��Ȃ��t�@�C���`���̉\��������܂�\n" );
#endif // TEST
			return FAILE;
			break;
		}
		Test = (SINT)stat_buff.st_size - (*pFileData)->pFileHData->uiHeader_Size_Offset;
		if ( stat_buff.st_size - (*pFileData)->pFileHData->uiHeader_Size_Offset != Reserved 
			&& (*pFileData)->pInfoHData->sColor_Bit!=Bit32 ) {
#ifdef TEST
			printf( "�t�@�C���̃f�[�^���j�����Ă���\��������܂�\n" );
#endif // TEST
			return FAILE;
		}
		else if((*pFileData)->pInfoHData->sColor_Bit==Bit32&& Reserved > stat_buff.st_size - (*pFileData)->pFileHData->uiHeader_Size_Offset )
		{
			printf( "�t�@�C���̃f�[�^���j�����Ă���\��������܂�\n" );
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
/* ������ private ������											    */
/* -------------------------------------------------------------------- */
/* �֐���	:	write													*/
/* �@�\��	:	�t�@�C���������݋@�\									*/
/* ����		:	:UCHR		pFilePath 		�t�@�C���p�X�̃A�h���X		*/
/*  			:FileData	pFileData		�i�[��̃t�@�C���f�[�^		*/
/* �߂�l	:	:FileData	NULL			���s						*/
/*							FileData		�����̎��͒��g��Ԃ�		*/
/* �쐬��	:	2021/11/03		�R�c�@���V��							*/
/* -------------------------------------------------------------------- */
SINT FileIO::write( SCHR *pFilePath, FileData **pFileData ) {
	char Mode[] = { "wb" };
	iIdetify=open( pFilePath, Mode );
	if ( iIdetify==FAILE )
	{
#ifdef TEST
		printf( "�t�@�C����write���\�b�h�ŃG���[���N���܂����@Line=%d\n", __LINE__ );
#endif // TEST
		return FAILE;
	}
	iIdetify=write( pFileData );
	if ( iIdetify==FAILE )
	{
#ifdef TEST
		printf( "�t�@�C���̏������݂ŃG���[���N���܂���\n" );
#endif // TEST
		return FAILE;
	}
	close( );
	return SUCCESS;
}

/* -------------------------------------------------------------------- */
/* ������ private ������											    */
/* -------------------------------------------------------------------- */
/* �֐���	:	write													*/
/* �@�\��	:	�t�@�C���������݋@�\									*/
/* ����		:	:UCHR		pFilePath 		�t�@�C���p�X�̃A�h���X		*/
/*  			:FileData	pFileData		�i�[��̃t�@�C���f�[�^		*/
/* �߂�l	:	:FileData	NULL			���s						*/
/*							FileData		�����̎��͒��g��Ԃ�		*/
/* �쐬��	:	2021/11/03		�R�c�@���V��							*/
/* -------------------------------------------------------------------- */
SINT FileIO::open( SCHR *pFilePath, SCHR *pMode ) {
	if ( ( ( pFP ) = fopen( pFilePath, pMode ) ) == NULL ) {
#ifdef TEST
		printf("FileIO�@open���\�b�h�@�t�@�C���̃I�[�v���Ɏ��s���܂����@Line=%d\n",__LINE__);
#endif // TEST
		return FAILE;
	}
	return SUCCESS;
}

/* -------------------------------------------------------------------- */
/* �֐���	:	write													*/
/* �@�\��	:	�t�@�C���������݋@�\									*/
/* ����		:	:UCHR		pFilePath 		�t�@�C���p�X�̃A�h���X		*/
/*  			:FileData	pFileData		�i�[��̃t�@�C���f�[�^		*/
/* �߂�l	:	:FileData	NULL			���s						*/
/*							FileData		�����̎��͒��g��Ԃ�		*/
/* �쐬��	:	2021/11/03		�R�c�@���V��							*/
/* -------------------------------------------------------------------- */
SINT FileIO::read( FileData **pFileData ) {
	if ( ((*pFileData)->pFileHData = (FileHeader*)calloc( 1, sizeof( FileHeader ) )) == NULL ) {
#ifdef TEST
		printf( "�_�C�i�~�b�N�������̊m�ۂɎ��s���܂���  Line=%d \n", __LINE__ );
#endif // TEST
		return FAILE;
	}

	if ( ((*pFileData)->pInfoHData = (InformationHeader*)calloc( 1, sizeof( InformationHeader ) )) == NULL ) {
#ifdef TEST
		printf( "�_�C�i�~�b�N�������̊m�ۂɎ��s���܂��� Line=%d \n", __LINE__ );
#endif // TEST
		return FAILE;
	}
	if ( ((*pFileData)->pImageData = (UCHR*)calloc( (stat_buff.st_size - (*pFileData)->pFileHData->uiHeader_Size_Offset), sizeof( UCHR )) )==NULL )
	{
#ifdef TEST
		printf( "�_�C�i�~�b�N�������̊m�ۂɎ��s���܂��� Line=%d \n",__LINE__ );
#endif // TEST
		return FAILE;
	}
#pragma pack( 2 )
	if ( fread( (*pFileData)->pFileHData, sizeof( FileHeader ), 1, pFP ) == NULL )
	{
#ifdef TEST
		printf( "�w�b�_�[�t�@�C���̓ǂݍ��݂����s���܂���  Line=%d \n", __LINE__ );
#endif // TEST
		return FAILE;
	}
	if ( (*pFileData)->pFileHData->sFile_Header_Name!=0x4d42 )
	{
#ifdef TEST
		printf( "BMP�ȊO�̉\��..." );
#endif // TEST
		if ( (*pFileData)->pFileHData->sFile_Header_Name == 0x5089 )
		{
#ifdef TEST
			printf( "PNG�ł���\n" );
#endif // TEST
			return PNG;
		}
		if ( (*pFileData)->pFileHData->sFile_Header_Name == 0xD8FF )
		{
#ifdef TEST
			printf( "JPEG�ł���\n" );
#endif // TEST
			return JPEG;
		}
		else
		{
#ifdef TEST
			printf( "�f�[�^�����Ă���\���������̓f�[�^���Ή����Ă��Ȃ��t�@�C���̉\��������܂�\n" );
#endif // TEST
			return FAILE;
		}
	}
	
#pragma pack( )
	fseek( pFP, sizeof( FileHeader ), SEEK_SET );
	if ( fread( (*pFileData)->pInfoHData, sizeof( InformationHeader ), 1, pFP ) == NULL) {
#ifdef TEST
		printf( "���w�b�_�t�@�C���̓ǂݍ��݂����s���܂��� Line=%d \n",__LINE__ );
#endif // TEST
		return FAILE;
	}
	fseek( pFP, (*pFileData)->pFileHData->uiHeader_Size_Offset, SEEK_SET );
	if ( fread( (*pFileData)->pImageData, stat_buff.st_size-(*pFileData)->pFileHData->uiHeader_Size_Offset, 1, pFP ) == NULL) {
#ifdef TEST
		printf( "�摜�t�@�C���̓ǂݍ��݂����s���܂��� Line=%d \n",__LINE__ );
#endif // TEST
		return FAILE;
	}
	return SUCCESS;
}

/* -------------------------------------------------------------------- */
/* �֐���	:	write													*/
/* �@�\��	:	�t�@�C���������݋@�\									*/
/* ����		:	:UCHR		pFilePath 		�t�@�C���p�X�̃A�h���X		*/
/*  			:FileData	pFileData		�i�[��̃t�@�C���f�[�^		*/
/* �߂�l	:	:FileData	NULL			���s						*/
/*							FileData		�����̎��͒��g��Ԃ�		*/
/* �쐬��	:	2021/11/03		�R�c�@���V��							*/
/* -------------------------------------------------------------------- */
SINT FileIO::write( FileData **pFileData ) {
	//�p�f�B���O�̒l��ێ�
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
		printf( "�Ή����Ă��Ȃ��t�@�C���t�H�[�}�b�g�ł�\n" );
		return FAILE;
		break;
	}
	
	return SUCCESS;
}

/* -------------------------------------------------------------------- */
/* �֐���	:	close													*/
/* �@�\��	:	�t�@�C���̃N���[�Y�@�\									*/
/* �쐬��	:	2021/11/03		�R�c�@���V��							*/
/* -------------------------------------------------------------------- */
void FileIO::close( ) {

	fclose( pFP );
}