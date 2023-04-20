/* -------------------------------------------------------------------- */
/* �t�@�C����	:	Conversion.cpp										*/
/* �@�\�T�v		:	�摜�f�[�^���w��t�H�[�}�b�g�ɂȂ����������݂ɓn��	*/
/* �쐬��		:   2020/10/21											*/
/* �ŏI�X�V��	:   2020/11/04											*/
/* �쐬��		:	�R�c���V��											*/
/* -------------------------------------------------------------------- */
#include"Conversion.h"

/* -------------------------------------------------------------------- */
/* ������ public ������												    */
/* -------------------------------------------------------------------- */
/* �֐���	:	exe														*/
/* �@�\��	:	�w��t�H�[�}�b�g�ɕϊ��O�̃t�@�C���̃t�H�[�}�b�g����	*/
/* ����		:	:FIleData		pFileData 		�t�@�C���̃f�[�^		*/
/*  			:SINT			iDecoratinfo	�f�R���[�V�����̏��	*/
/* �߂�l	:	:SINT			NULL			���s					*/
/*								SUCCESS			�����̎��͒��g��Ԃ�	*/
/* �쐬��	:	2021/11/03		�R�c�@���V��							*/
/* -------------------------------------------------------------------- */
SINT Conversion::exe( FileData *pFileData, SINT iDecoratInfo ,SCHR *pFilePath) {
	SINT iIdetify;
	ConvertBmp ConversionBmp;
	iIdetify=Check( 'P', pFileData );
	if ( iIdetify==FAILE )
	{
#ifdef TEST
		printf( "�t�@�C���̃f�[�^�̎擾�Ɏ��s���Ă��܂�(Conversion.cpp) Line=%d\n", __LINE__ );
#endif // TEST
		return FAILE;
	}
	iIdetify = Check( 'I', iDecoratInfo );
	if ( iIdetify == FAILE )
	{
#ifdef TEST
		printf( "�����ɖ�肪����\��������܂�(Conversion.cpp) Line=%d\n", __LINE__ );
#endif // TEST
		return FAILE;
	}
	iIdetify = Check( 'C', pFilePath );
	if ( iIdetify == FAILE )
	{
#ifdef TEST
		printf( "�t�@�C����path���擾�ł��܂���(Conversion.cpp) Line=%d\n", __LINE__ );
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
		printf( "�l�ɖ�肪����\��������܂�(Conversion.cpp) Line=%d\n", __LINE__ );
#endif // TEST
		return FAILE;
		break;
	}
	/*�ϊ���̃G���[�`�F�b�N----------------------------------------------------------------------*/
	if ( iIdetify==FAILE )
	{
#ifdef TEST
		printf( "�ϊ������Ɏ��s���܂���(Conversion.cpp) Line=%d\n", __LINE__ );
#endif // TEST
		return FAILE;
	}
	iIdetify = Check( 'F', pFileData->pFileHData );
	if ( iIdetify == FAILE )
	{
#ifdef TEST
		printf( "�t�@�C���̏��ɖ�肪�o�܂���(Conversion.cpp) Line=%d\n", __LINE__ );
#endif // TEST
		return FAILE;
	}
	iIdetify = Check( 'N', pFileData->pInfoHData );
	if ( iIdetify == FAILE )
	{
#ifdef TEST
		printf( "�t�@�C���̏��ɖ�肪�o�܂���(Conversion.cpp) Line=%d\n", __LINE__ );
#endif // TEST
		return FAILE;
	}
	iIdetify = Check( 'C', pFileData->pImageData );
	if ( iIdetify == FAILE )
	{
#ifdef TEST
		printf( "�t�@�C���̏��ɖ�肪�o�܂���(Conversion.cpp) Line=%d\n", __LINE__ );
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
		printf( "�K��O�̈����ł��B" );
		return FAILE;
		break;
	}
	return SUCCESS;
}

