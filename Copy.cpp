/* ------------------------------------------------------------------------- */
/* Copy.cpp																	 */
/* ��������																	 */
/* ���������������쐬���đ�������d�l�Ȃ̂ŁA���̊֐��ł͈����`�F�b�N�̂�	 */
/* ------------------------------------------------------------------------- */
/* �ԍ�	�X�V����								���t		   ����			 */
/* ------------------------------------------------------------------------- */
/* 000000	�V�K�쐬							2021/10/29     �����@�C��	 */
/* 000001	���t�@�N�^�����O					2021/11/22	   ����  �C��	 */
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
/* Include File																 */
/* ------------------------------------------------------------------------- */
#include "System.h"
#include "Copy.h"

/* ------------------------------------------------------------------------- */
/* �֐���	: Copy::exe														 */
/* �@�\��	: ���s����														 */
/* �@�\�T�v	: �������������s����											 */
/* ����		: DecorateList*	: decorateInfo		: �������[IN] 				 */
/*			: FileData	 	: imageData			: �摜���[I/O] 			 */
/* �߂�l	: SINT			:					: �G���[�`�F�b�N[OUT]		 */
/* �쐬��	: 2021/10/29		����  �C��		�V�K�쐬					 */
/* ------------------------------------------------------------------------- */
SINT Copy::exe( DecorateList* decorateInfo, FileData* imageData )
{

	/* �����l�`�F�b�N------------------------- */

	/* DM */
	if ( decorateInfo == NULL ) {
		printf( "decorateInfo Inter Check  Error In Copy::exe_decorateList\n" );
		return FAILE;
	}
	if ( imageData == NULL ) {
		printf( "decorateInfo Inter Check  Error In Copy::exe_imageData\n" );
		return FAILE;
	}
	/* ������� */
	if ( decorateInfo->decolateKind != COPY ) {
		printf( "decorateInfo Inter Check  Error In KIND\n" );
		return FAILE;
	}
	/* �����ݒ� */
	if ( decorateInfo->decolatesetup != EMPTY ) {
		printf( "decorateInfo Inter Check  Error In SETUP\n" );
		return FAILE;
	}
	/* �摜�^�� */
	if ( imageData->pFileHData->sFile_Header_Name != MAGIC_NUMBER ) {
		printf( "imageData Inter Check Error In Type\n" );
		return FAILE;
	}
	/* �摜�T�C�Y */
	if ( imageData->pInfoHData->uiWidth < IMAGE_SIZE_MIN || imageData->pInfoHData->uiHeight < IMAGE_SIZE_MIN ) {
		printf( "imageData Inter Check Error In IMAGE_SIZE\n" );
		return FAILE;
	}
	/* --------------------------------------- */

	/* �����摜�f�[�^��������Ȃ��̂ł��̃}�}�Ԃ� */

	return FAILE;
}
/* ------------------------------------------------------------------------- */
/*              Copyright HAL Collage of Technology & Design                 */
/* ------------------------------------------------------------------------- */
