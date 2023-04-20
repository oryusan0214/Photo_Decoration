/* ------------------------------------------------------------------------- */
/* DecorateInfo.cpp															 */
/* �������ۑ���															 */
/* �������e�ۑ�����															 */
/* ------------------------------------------------------------------------- */
/* �ԍ�	�X�V����								���t		   ����			 */
/* ------------------------------------------------------------------------- */
/* 000000	�V�K�쐬							2021/10/25     �����@�C��	 */
/* 000001	���t�@�N�^�����O					2021/12/02	   ����  �C��	 */
/* ------------------------------------------------------------------------- */
/* Include File																 */
/* ------------------------------------------------------------------------- */
#include "DecorateInfo.h"

/* ------------------------------------------------------------------------- */
/* �֐���	: Decorateinfo::DecorateInfo									 */
/* �@�\��	: �R���X�g���N�^												 */
/* �@�\�T�v	: �f�[�^��������												 */
/* ����		: �Ȃ�															 */
/* �߂�l	: void															 */
/* �쐬��	: 2021/10/25		����  �C��		�V�K�쐬					 */
/* ------------------------------------------------------------------------- */
DecorateInfo::DecorateInfo( void )
{
	proot	= NULL;
	psearth	= NULL;
}

/* ------------------------------------------------------------------------- */
/* �֐���	: Decorateinfo::~DecorateInfo									 */
/* �@�\��	: �f�X�g���N�^													 */
/* �@�\�T�v	: �f�[�^�����													 */
/* ����		: �Ȃ�															 */
/* �߂�l	: void															 */
/* �쐬��	: 2021/10/25		����  �C��		�V�K�쐬					 */
/* ------------------------------------------------------------------------- */
DecorateInfo::~DecorateInfo( void )
{
	/* �d������h�~ */
	if ( proot != NULL && proot != psearth ) {
		free( proot );
	}
	if ( psearth != NULL ) {
		free( psearth );
	}
}

/* ------------------------------------------------------------------------- */
/* �֐���	: DecorateInfo::save											 */
/* �@�\��	: �ۑ�����														 */
/* �@�\�T�v	: ���������擾���A�ۑ�����									 */
/* ����		: DecorateList*	: proot				: �����擪�A�h[IN / OUT]	 */
/*			: DecorateList*	: psearth			: �����Q�ƃA�h[IN / OUT]	 */
/* 			: SINT*			: idecorateKind		: �������[IN]				 */
/*			: SINT*			: idecorateSetup	: �����ݒ�[IN]				 */
/* �߂�l	: SINT			:					: �G���[�`�F�b�N[OUT]		 */
/* �쐬��	: 2021/10/25		����  �C��		�V�K�쐬					 */
/* ------------------------------------------------------------------------- */
SINT DecorateInfo::save( DecorateList* &proot, DecorateList* &psearth,
						 SINT* idecorateKind, SINT* idecorateSetup )
{
	/* �����l�`�F�b�N */
	/* DM check */
	if( ( proot == NULL ) &&  ( psearth != NULL) ){
		printf( "decorateInfo Inter Check  Error DecorateInfo::save_proot\n" );
		return FAILE;
	}
	if( ( proot != NULL ) && ( psearth == NULL ) ){
		printf( "decorateInfo Inter Check  Error DecorateInfo::save_psearth\n" );
		return FAILE;
	}

	if ( idecorateKind == NULL ) {
		printf( "decorateInfo Inter Check  Error DecorateInfo::save_Kind\n" );
		return FAILE;
	}
	if ( idecorateSetup == NULL ) {
		printf( "decorateInfo Inter Check  Error DecorateInfo::save_Setup\n" );
		return FAILE;
	}
	

	/* �ϐ��錾 */
	DecorateList* ptemp = NULL;					/* �P����List�쐬�̂��߂̃e���v */

	/* DM�m�� */
	ptemp = ( DecorateList* )calloc( ONE,sizeof( DecorateList ) );

	/* DM�`�F�b�N */
	if ( ptemp == NULL ) {
		printf( "get dynamic error In ptemp\n" );
		return FAILE;
	}

	/* �ۑ���1��ڂȂ�擪�A�h�ɓ��ڈȍ~�Ȃ�O�̃A�h�̌��Ɍ��� */
	if ( proot == NULL ) {
		proot	= ptemp;
		psearth	= ptemp;
	}
	else {
		psearth->next	= ptemp;
		psearth			= ptemp;

	}
	/* �ۑ� */
	ptemp->decolateKind		= *idecorateKind;
	ptemp->decolatesetup	= *idecorateSetup;

	return SUCCESS;
}
/* ------------------------------------------------------------------------- */
/*              Copyright HAL Collage of Technology & Design                 */
/* ------------------------------------------------------------------------- */
