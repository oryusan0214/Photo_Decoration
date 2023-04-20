/* ------------------------------------------------------------------------- */
/* IndependentProcessing.cpp												 */
/* �P�Ə���																	 */
/* �������A����̂݋L��( exe�͒u�� )										 */
/* ------------------------------------------------------------------------- */
/* �ԍ�	�X�V����								���t		   ����			 */
/* ------------------------------------------------------------------------- */
/* 000000	�V�K�쐬							2021/10/15     �����@�C��	 */
/* 000001	���t�@�N�^�����O					2021/11/22	   ����  �C��	 */
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
/* Include																	 */
/* ------------------------------------------------------------------------- */
#include "IndependentProcessing.h"


/* ------------------------------------------------------------------------- */
/* �֐���	: IndependentProcessing::IndependentProcessing					 */
/* �@�\��	: �R���X�g���N�^												 */
/* �@�\�T�v	: �f�[�^��������												 */
/* ����		: �Ȃ�															 */
/* �߂�l	: void															 */
/* �쐬��	: 2021/10/15		����  �C��		�V�K�쐬					 */
/* ------------------------------------------------------------------------- */
IndependentProcessing::IndependentProcessing( void )
{
	/* ������ & get DM */
	secondImageData	=	NULL;
	thirdImageData	=	NULL;
	fourthImageData	=	NULL;

	secondImageData	= ( FileData* )calloc( sizeof( FileData ), sizeof( UCHR ) );
	thirdImageData	= ( FileData* )calloc( sizeof( FileData ), sizeof( UCHR ) );
	fourthImageData	= ( FileData* )calloc( sizeof( FileData ), sizeof( UCHR ) );

	/* DM Get Error */
	if ( secondImageData == NULL || thirdImageData == NULL || fourthImageData == NULL ) {
		printf( "DM Get Error In IndependentProcessing::IndependentProcessing\n" );
	}
	
}

/* ------------------------------------------------------------------------- */
/* �֐���	: IndependentProcessing::~IndependentProcessing					 */
/* �@�\��	: �f�X�g���N�^													 */
/* �@�\�T�v	: �m�ۂ��Ă���̈�̉��										 */
/* ����		: �Ȃ�															 */
/* �߂�l	: void															 */
/* �쐬��	: 2021/10/15		����  �C��		�V�K�쐬					 */
/* ------------------------------------------------------------------------- */
IndependentProcessing::~IndependentProcessing( void )
{
	/* ���d�J���h�~ */
	if ( secondImageData != NULL && secondImageData != thirdImageData && secondImageData != fourthImageData ) {
		free( secondImageData );
	}
	if ( thirdImageData != NULL && thirdImageData != fourthImageData ) {
		free( thirdImageData );
	}
	if ( fourthImageData != NULL ) {
		free( fourthImageData );
	}

}
/* ------------------------------------------------------------------------- */
/* �֐���	: IndependentProcessing::exe									 */
/* �@�\��	: ���s����														 */
/* �@�\�T�v	: �P�Ə��������s����											 */
/* ����		: DecorateList* : decorateInfo		: �������[IN] 				 */
/*			: FileData	 	: imageData			: �摜���[I/O] 			 */
/*			: FileData		: secondImageData	: �񖇖ڂ̑������[IN] 		 */
/*			: FileData		: thirdImageData	: �O���ڂ̑������[IN] 		 */
/*			: FileData	 	: fourthImageData	: �l���ڂ̑������[IN] 		 */
/* �߂�l	: SINT			:					: �G���[�`�F�b�N[OUT]		 */
/* �쐬��	: 2021/10/15		����  �C��		�V�K�쐬					 */
/* ------------------------------------------------------------------------- */
void IndependentProcessing::exe( DecorateList* decorateInfo, FileData* imageData,
								 FileData* secondImageData, FileData* thirdImageData, FileData* fourthImageData )
{

}
/* ------------------------------------------------------------------------- */
/*              Copyright HAL Collage of Technology & Design                 */
/* ------------------------------------------------------------------------- */
