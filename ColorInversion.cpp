/* ------------------------------------------------------------------------- */
/* ColorInversion.cpp														 */
/* �F���]																	 */
/* �摜�̋P�x�𔽓]������v���O����											 */
/* ------------------------------------------------------------------------- */
/* �ԍ�	�X�V����								���t		   ����			 */
/* ------------------------------------------------------------------------- */
/* 000000	�V�K�쐬							2021/10/23     �����@�C��	 */
/* 000001	���t�@�N�^�����O					2021/12/03	   ����  �C��	 */
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
/* Include File																 */
/* ------------------------------------------------------------------------- */
#include "ColorInversion.h"

/* ------------------------------------------------------------------------- */
/* �֐���	: ColorInversion::exe											 */
/* �@�\��	: ���s����														 */
/* �@�\�T�v	: �F���]�����s����												 */
/* ����		: DecorateList*	: decorateInfo		: �������[IN]	 			 */
/*			: FileData* 	: imageData			: �摜���[I/O] 			 */
/* �߂�l	: SINT			:					: �G���[�`�F�b�N[OUT]		 */
/* �쐬��	: 2021/10/23		����  �C��		�V�K�쐬					 */
/* ------------------------------------------------------------------------- */
SINT ColorInversion::exe( DecorateList* decorateInfo, FileData* imageData )
{


	/* �����l�`�F�b�N------------------------- */

	/* DM */
	if ( decorateInfo == NULL ) {
		printf( "decorateInfo Inter Check  Error In ColorInvert::exe_decorateList\n" );
		return FAILE;
	}
	if ( imageData == NULL ) {
		printf( "decorateInfo Inter Check  Error In ColorInvert::exe_imageData\n" );
		return FAILE;
	}
	/* ������� */
	if ( decorateInfo->decolateKind != COLORINVERT ) {
		printf( "decorateInfo Inter Check  Error In ColorInversion::exe_Kind\n" );
		return FAILE;
	}
	/* �����ݒ� */
	if ( ( decorateInfo->decolatesetup ) != INTI ) {
		printf( "decorateInfo Inter Check  Error In ColorInversion::exe_setup\n" );
		return FAILE;
	}
	/* �摜�^�� */
	if ( imageData->pFileHData->sFile_Header_Name != MAGIC_NUMBER ) {
		printf( "imageData Inter Check Error In ColorInversion::exe_Type\n" );
		return FAILE;
	}
	/* �摜�T�C�Y */
	if ( ( imageData->pInfoHData->uiWidth ) <= INTI || ( imageData->pInfoHData->uiHeight ) <= INTI ) {
		printf( "imageData Inter Check Error In ColorInversion::exe_Size\n" );
		return FAILE;
	}
	/* --------------------------------------- */

	/* ������ & �����l���-------------------- */
	SINT icountCIv	= INTI;						/* �J�E���g��				 */
	SINT idataSize	= INTI;						/* ���[�v�񐔎擾			 */

	/* �摜�̏c�� * 1�s�N�Z���������bit = ���[�v�� */
	idataSize = ( imageData->pInfoHData->uiWidth ) * ( imageData->pInfoHData->uiHeight ) * BYTE4;
	/* --------------------------------------- */

	/* �F���]����----------------------------- */

	/* �摜�f�[�^��bit�������[�v */
	for ( icountCIv = INTI; icountCIv < idataSize; icountCIv ++ ) {

		/* ���`�����l���͏����������ɔ�΂� */
		if ( ( icountCIv + BYTE1 ) % BYTE4 == INTI ) {
			continue;
		}
		/* rgb�`�����l���͋P�x���] */
		*( imageData->pImageData + icountCIv ) = 
			COLORMAX - *( imageData->pImageData + icountCIv );
	}
	/* --------------------------------------- */

	return SUCCESS;
}
/* ------------------------------------------------------------------------- */
/*              Copyright HAL Collage of Technology & Design                 */
/* ------------------------------------------------------------------------- */
