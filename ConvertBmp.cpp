/* -------------------------------------------------------------------- */
/* �t�@�C����	:	main.cpp											*/
/* �@�\�T�v		:	�w��t�H�[�}�b�g�ɍ��킹�邽�߂ɕʃN���X���Ăяo��	*/
/* �쐬��		:   2020/10/29											*/
/* �ŏI�X�V��	:   2020/12/09											*/
/* �쐬��		:	�R�c���V��											*/
/* -------------------------------------------------------------------- */
#include "ConvertBmp.h"
/* -------------------------------------------------------------------- */
/* ������ public ������												    */
/* -------------------------------------------------------------------- */
/* �֐���	:	exe														*/
/* �@�\��	:	exe														*/
/* ����		:	:FileData*		:pFileData		:�t�@�C���̃f�[�^		*/
/*				:SINT			:iDecoretinfo	:�������				*/
/* �߂�l	:	:FAILE			:1				:���s					*/
/*				:SUCCESS		:0				:����					*/
/* �쐬��	:	2021/11/03		�R�c�@���V��							*/
/* -------------------------------------------------------------------- */
SINT ConvertBmp::exe( FileData *pFileData,SINT iDecoretinfo ,SCHR *pFilePath ) {
	ColorConvert CC;
	SINT iIdentify;
	if ( pFileData==NULL )
	{
#ifdef TEST
		printf( "�v���O������Ŋm�ۂ��Ă���f�[�^�ɖ�肪������܂���(ConvertBmp.cpp) Line=%d\n", __LINE__ );
#endif // TEST
		return FAILE;
	}
	if ( pFilePath==NULL )
	{
#ifdef TEST
		printf( "�t�@�C���p�X���������擾�ł��܂���ł���(ConvertBmp.cpp) Line=%d\n", __LINE__ );
#endif // TEST

	}
	if ( iDecoretinfo != Bit32 && iDecoretinfo != Bit24 && iDecoretinfo != Bit8 && iDecoretinfo != Bit1 )
	{
#ifdef TEST
		printf( "�����̒l�ɖ�肪������܂���,�z�肳�������Ƃ͈Ⴂ�܂�(ConvertBmp.cpp) Line=%d\n",__LINE__ );
#endif // TEST
		return FAILE;
	}
	if ( pFileData->pInfoHData->sColor_Bit == Bit32 && iDecoretinfo == 32 ) {
		printf( "���ł�32bit�̉摜�f�[�^�ł��B" );
		return SUCCESS;
	}
	iIdentify=CC.exe( pFileData, iDecoretinfo,pFilePath );
	if ( iIdentify==FAILE )
	{
#ifdef TEST
		printf( "�t�@�C���̕ϊ��Ɏ��s���܂���\(ConvertBmp.cpp) Line=%d\n", __LINE__  );
#endif // TEST
		return FAILE;
	}
	
	return SUCCESS;
}
