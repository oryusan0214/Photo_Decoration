/* ------------------------------------------------------------------------- */
/* Rotate.cpp																 */
/* ��]����																	 */
/* ��]���鏈��																 */
/* ------------------------------------------------------------------------- */
/* �ԍ�	�X�V����								���t		   ����			 */
/* ------------------------------------------------------------------------- */
/* 000000	�V�K�쐬							2021/10/15     �����@�C��	 */
/* 000001	���t�@�N�^�����O					2021/11/25	   ����  �C��	 */
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
/* Include File																 */
/* ------------------------------------------------------------------------- */
#include "System.h"
#include "Rotate.h"


/* ------------------------------------------------------------------------- */
/* �֐���	: Rotate::exe													 */
/* �@�\��	: ��]����														 */
/* �@�\�T�v	: ��]���鏈�������s����										 */
/* ����		: decorateInfo*	: decorateInfo	: �������[OUT] 				 */
/*			: FileData* 	: imageData		: �摜���[OUT] 				 */
/* �߂�l	: SINT		:					: �G���[�`�F�b�N[IN]			 */
/* �쐬��	: 2021/10/28		����  �C��		�V�K�쐬					 */
/* ------------------------------------------------------------------------- */
SINT Rotate::exe( DecorateList* decorateInfo, FileData* imageData )
{
	/* �ϐ��錾 */
	SINT iRT_Ver		= INTI;					/* �J�E���g��				 */
	SINT iRT_Hor		= INTI;					/* �J�E���g��				 */
	SINT ierrorCheck	= INTI;					/* �G���[�`�F�b�N			 */
	SINT ipixelSize		= INTI;					/* �摜�̃s�N�Z����			 */
	SINT ireferenceVer	= INTI;					/* Warning���p			 */
	SINT ireference		= INTI;					/* Warning���p			 */
	rgb* Color			= NULL;					/* 1�s�N�Z��������̃f�[�^�i�[�z�� */

	/* ���͒l�`�F�b�N------------------------- */

	/* DM */
	if ( decorateInfo == NULL ) {
		printf( "decorateInfo Inter Check  Error In Rotate::exe_decorateList\n" );
		return FAILE;
	}
	if ( imageData == NULL ) {
		printf( "decorateInfo Inter Check  Error In Rotate:exe_imageData\n" );
		return FAILE;
	}
	/* ������� */
	if ( decorateInfo->decolateKind != ROTATE ) {
		printf( "decorateInfo Inter Check  Error In Rotate::exe_Kind\n" );
		return FAILE;
	}
	/* �����ݒ� */
	if ( decorateInfo->decolatesetup < ROTATE_MIN || ROTATE_MAX < decorateInfo->decolatesetup ) {
		printf( "decorateInfo Inter Check  Error In Rotate::exe_Setup\n" );
		return FAILE;
	}
	/* �^�� */
	if ( imageData->pFileHData->sFile_Header_Name != MAGIC_NUMBER ) {
		printf( "imageData Inter Check Error In Rotate::exe_Type\n" );
		return FAILE;
	}
	/* �傫�� */
	if ( imageData->pInfoHData->uiWidth <= INTI || imageData->pInfoHData->uiHeight <= INTI ) {
		printf( "imageData Inter Check Error In Rotate::exe_Size\n" );
		return FAILE;
	}

	/* Get Pixel */
	ipixelSize = imageData->pInfoHData->uiHeight * imageData->pInfoHData->uiWidth;

	/* get DM */
	Color = ( rgb* )calloc( ipixelSize, sizeof( rgb ) );

	/* DM check */
	if ( Color == NULL ) {
		printf( "get DM error_Rotate_Color\n" );
		return FAILE;
	}

	/* Color�Ƀf�[�^���� */
	for ( iRT_Ver = INTI; iRT_Ver < imageData->pInfoHData->uiHeight; iRT_Ver ++ ) {
		for ( iRT_Hor = INTI; iRT_Hor < imageData->pInfoHData->uiWidth; iRT_Hor ++ ) {

			/* Warning����̂��߂̒��Ԋ֐� */
			ireferenceVer	= iRT_Ver * imageData->pInfoHData->uiWidth;
			ireference		= ( iRT_Ver * imageData->pInfoHData->uiWidth + iRT_Hor ) * BYTE4 ;

			( Color + ireferenceVer + iRT_Hor )->b = *( imageData->pImageData + ireference );
			( Color + ireferenceVer + iRT_Hor )->g = *( imageData->pImageData + ireference + BYTE1 );
			( Color + ireferenceVer + iRT_Hor )->r = *( imageData->pImageData + ireference + BYTE2 );
			( Color + ireferenceVer + iRT_Hor )->a = *( imageData->pImageData + ireference + BYTE3 );
		}
	}
	
	/* �ݒ�ɂ���΂� */
	if ( decorateInfo->decolatesetup		== ONE_PUARTER ) {
		ierrorCheck = one_quarter( Color, imageData );
	}
	else if ( decorateInfo->decolatesetup	== TWO_PUARTER ) {
		ierrorCheck = two_quarter( Color, imageData );
	}
	else if ( decorateInfo->decolatesetup	== THREE_PUARTER ) {
		ierrorCheck = three_quarter( Color, imageData );
	}
	else if ( decorateInfo->decolatesetup	== FOUR_PUARTER ) {
	}

	if ( ierrorCheck == FAILE ) {
		printf( "��]�����Ɏ��s���܂���\n" );
		return FAILE;
	}
	return SUCCESS;
}

/* ------------------------------------------------------------------------- */
/* �֐���	: Rotate::one_quarter											 */
/* �@�\��	: 90�x��]����													 */
/* �@�\�T�v	: 90�x��]���鏈�������s����									 */
/* ����		: rgb*			: Color			: �摜�f�[�^���[OUT] 			 */
/*			: FileData* 	: imageData		: �摜���[OUT] 				 */
/* �߂�l	: SINT		:					: �G���[�`�F�b�N[IN]			 */
/* �쐬��	: 2021/10/28		����  �C��		�V�K�쐬					 */
/* ------------------------------------------------------------------------- */
SINT Rotate::one_quarter( rgb* Color, FileData* imageData )
{

	/* DM */
	if ( Color == NULL ) {
		printf( "decorateInfo Inter Check  Error In Rotate::one_Color\n" );
		return FAILE;
	}
	if ( imageData == NULL ) {
		printf( "decorateInfo Inter Check  Error In Rotate:one_imageData\n" );
		return FAILE;
	}

	/* �ϐ��錾 */
	UCHR* protate	= NULL;						/* ������̉摜�f�[�^		 */
	SINT iver		= INTI;						/* ����						 */
	SINT ihor		= INTI;						/* ��						 */
	SINT iverMax	= INTI;						/* �����̍ő�l				 */
	SINT ihorMax	= INTI;						/* ���̍ő�l				 */
	SINT ibox		= INTI;						/* ��						 */
	SINT imageSize	= INTI;						/* �摜�T�C�Y				 */
	SINT ireference = INTI;						/* �Q�Ƃ��Ă���o�C�g		 */
	SINT ireferenceVer = INTI;					/* Warning���p			 */


	/* �摜�T�C�Y�擾 */
	imageSize = imageData->pInfoHData->uiWidth * imageData->pInfoHData->uiHeight * BYTE4;

	/* get DM */
	protate = ( UCHR* )calloc( imageSize,sizeof( UCHR ) );

	/* check DM */
	if ( protate == NULL ) {
		printf( "get dynamic error In Rotate::three_quater\n" );
		return FAILE;
	}
	/* �ω��O�ő�l�̕ۑ� */
	iverMax = imageData->pInfoHData->uiHeight;
	ihorMax = imageData->pInfoHData->uiWidth;

	/* �c�����l����ւ� */
	ibox							= imageData->pInfoHData->uiWidth;
	imageData->pInfoHData->uiWidth	= imageData->pInfoHData->uiHeight;
	imageData->pInfoHData->uiHeight	= ibox;

	/*
		10 11 12	 1
		7  8  9		 2
		4  5  6		 3
		1  2  3		 4

		�@ �A �B

		���X���̂悤�Ƀs�N�Z���f�[�^���i�[����Ă���̂��A

		12 9  6  3	�B
		11 8  5  2	�A
		10 7  4  1	�@

		1  2  3  4
 
		���̂悤�ɂȂ�̂�
		���̍��W���@( hor , ver ) �Ƃ���Ƒ�����̍��W��( ver , horMax - hor )�ƂȂ�̂ł��̗��_��p����

	*/
	/* ��]����------------------------------- */
	for ( iver = INTI; iver < iverMax; iver ++ ) {
		for (ihor = INTI; ihor < ihorMax; ihor ++ ) {

			/* �ő�l��1�X�^�[�g�A�v���O������0�X�^�[�g�̂��߈�v�����邽�߂� - 1 ���Ă��� */
			ireference = ( iver + ( ( ihorMax - BYTE1 - ihor ) * imageData->pInfoHData->uiWidth ) ) * BYTE4;
			/* Warning����̂��߂̒��Ԋ֐� */
			ireferenceVer = iver * ihorMax;

			*( protate + ireference )			= ( Color + ireferenceVer + ihor )->b;
			*( protate + ireference + BYTE1 )	= ( Color + ireferenceVer + ihor )->g;
			*( protate + ireference + BYTE2 )	= ( Color + ireferenceVer + ihor )->r;
			*( protate + ireference + BYTE3 )	= ( Color + ireferenceVer + ihor )->a;
		}
	}
	/* --------------------------------------- */
	/* �摜�f�[�^�X�V */
	imageData->pImageData = protate;

	return SUCCESS;
}

/* ------------------------------------------------------------------------- */
/* �֐���	: Rotate::two_quarter											 */
/* �@�\��	: 180�x��]����													 */
/* �@�\�T�v	: 180�x��]���鏈�������s����									 */
/* ����		: rgb*			: Color			: �摜�f�[�^���[OUT] 			 */
/*			: FileData* 	: imageData		: �摜���[OUT] 				 */
/* �߂�l	: SINT		:					: �G���[�`�F�b�N[IN]			 */
/* �쐬��	: 2021/10/28		����  �C��		�V�K�쐬					 */
/* ------------------------------------------------------------------------- */

SINT Rotate::two_quarter( rgb* Color, FileData* imageData )
{

	/* DM */
	if ( Color == NULL ) {
		printf( "decorateInfo Inter Check  Error In Rotate::two_Color\n" );
		return FAILE;
	}
	if ( imageData == NULL ) {
		printf( "decorateInfo Inter Check  Error In Rotate:two_imageData\n" );
		return FAILE;
	}

	/* �ϐ��錾 */
	UCHR* protate	= NULL;						/* ������̉摜�f�[�^		 */
	SINT iver		= INTI;						/* ����						 */
	SINT ihor		= INTI;						/* ��						 */
	SINT iverMax	= INTI;						/* �����̍ő�l				 */
	SINT ihorMax	= INTI;						/* ���̍ő�l				 */
	SINT ibox		= INTI;						/* ��						 */
	SINT imageSize	= INTI;						/* �摜�T�C�Y				 */
	SINT ireference = INTI;						/* �Q�Ƃ��Ă���o�C�g		 */
	SINT ireferenceVer = INTI;					/* Warning���p			 */


	/* �摜�T�C�Y�擾 */
	imageSize = imageData->pInfoHData->uiWidth * imageData->pInfoHData->uiHeight * BYTE4;

	/* get DM */
	protate = ( UCHR* )calloc( imageSize,sizeof( UCHR ) );

	/* check DM */
	if ( protate == NULL ) {
		printf( "get dynamic error In Rotate::two_quater\n" );
		return FAILE;
	}
	/* �ω��O�ő�l�̕ۑ� */
	iverMax = imageData->pInfoHData->uiHeight;
	ihorMax = imageData->pInfoHData->uiWidth;

	/*
		10 11 12	 1
		7  8  9		 2
		4  5  6		 3
		1  2  3		 4

		�@ �A �B

		���X���̂悤�Ƀs�N�Z���f�[�^���i�[����Ă���̂��A

		3  2  1		4
		6  5  4		3
		9  8  7		2
		12 11 10	1

		�B �A �@

		���̂悤�ɂȂ�̂�
		���̍��W���@( hor , ver ) �Ƃ���Ƒ�����̍��W��( horMax - hor , verMax - ver )�ƂȂ�̂ł��̗��_��p����

	*/
	/* ��]����------------------------------- */
	for ( iver = INTI; iver < iverMax; iver ++ ) {
		for (ihor = INTI; ihor < ihorMax; ihor ++ ) {

			/* �ő�l��1�X�^�[�g�A�v���O������0�X�^�[�g�̂��߈�v�����邽�߂� - 1 ���Ă��� */
			ireference = ( ( ihorMax - BYTE1 - ihor ) + ( ( iverMax - BYTE1 - iver ) * imageData->pInfoHData->uiWidth ) ) * BYTE4;
			/* Warning����̂��߂̒��Ԋ֐� */
			ireferenceVer = iver * ihorMax;

			*( protate + ireference)				= ( Color + ireferenceVer + ihor )->b;
			*( protate + ireference + BYTE1 )		= ( Color + ireferenceVer + ihor )->g;
			*( protate + ireference + BYTE2 )		= ( Color + ireferenceVer + ihor )->r;
			*( protate + ireference + BYTE3 )		= ( Color + ireferenceVer + ihor )->a;
		}
	}
	/* --------------------------------------- */
	/* �摜�f�[�^�X�V */
	imageData->pImageData = protate;

	return SUCCESS;
}

/* ------------------------------------------------------------------------- */
/* �֐���	: Rotate::three_quarter											 */
/* �@�\��	: 270�x��]����													 */
/* �@�\�T�v	: 270�x��]���鏈�������s����									 */
/* ����		: rgb*			: Color			: �摜�f�[�^���[OUT] 			 */
/*			: FileData* 	: imageData		: �摜���[OUT] 				 */
/* �߂�l	: SINT		:					: �G���[�`�F�b�N[IN]			 */
/* �쐬��	: 2021/10/28		����  �C��		�V�K�쐬					 */
/* ------------------------------------------------------------------------- */

SINT Rotate::three_quarter( rgb* Color,FileData* imageData )
{

	/* DM */
	if ( Color == NULL ) {
		printf( "decorateInfo Inter Check  Error In Rotate::three_Color\n" );
		return FAILE;
	}
	if ( imageData == NULL ) {
		printf( "decorateInfo Inter Check  Error In Rotate:three_imageData\n" );
		return FAILE;
	}

	/* �ϐ��錾 */
	UCHR* protate		= NULL;					/* ������̉摜�f�[�^		 */
	SINT iver			= INTI;					/* ����						 */
	SINT ihor			= INTI;					/* ��						 */
	SINT iverMax		= INTI;					/* �����̍ő�l				 */
	SINT ihorMax		= INTI;					/* ���̍ő�l				 */
	SINT ibox			= INTI;					/* ��						 */
	SINT imageSize		= INTI;					/* �摜�T�C�Y				 */
	SINT ireference		= INTI;					/* �Q�Ƃ��Ă���o�C�g		 */
	SINT ireferenceVer	= INTI;					/* Warning���p			 */


	/* �摜�T�C�Y�擾 */
	imageSize = imageData->pInfoHData->uiWidth * imageData->pInfoHData->uiHeight * BYTE4;

	/* get DM */
	protate = ( UCHR* )calloc( imageSize,sizeof( UCHR ) );

	/* check DM */
	if ( protate == NULL ) {
		printf( "get dynamic error In Rotate::one_quater\n" );
		return FAILE;
	}
	/* �ω��O�ő�l�̕ۑ� */
	iverMax = imageData->pInfoHData->uiHeight;
	ihorMax = imageData->pInfoHData->uiWidth;

	/* �c�����l����ւ� */
	ibox							= imageData->pInfoHData->uiWidth;
	imageData->pInfoHData->uiWidth	= imageData->pInfoHData->uiHeight;
	imageData->pInfoHData->uiHeight	= ibox;

	/*
		10 11 12	 1
		7  8  9		 2
		4  5  6		 3
		1  2  3		 4

		�@ �A �B

		���X���̂悤�Ƀs�N�Z���f�[�^���i�[����Ă���̂��A

		1  4  7  10 �@
		2  5  8  11	�A
		3  6  9  12 �B

		4�@3�@2�@1

		���̂悤�ɂȂ�̂�
		���̍��W���@( hor , ver ) �Ƃ���Ƒ�����̍��W��( verMax - ver , hor )�ƂȂ�̂ł��̗��_��p����

	*/
	/* ��]����------------------------------- */
	for ( iver = INTI; iver < iverMax; iver ++ ) {
		for (ihor = INTI; ihor < ihorMax; ihor ++ ) {

			/* �ő�l��1�X�^�[�g�A�v���O������0�X�^�[�g�̂��߈�v�����邽�߂� - 1 ���Ă��� */
			ireference = ( ( iverMax - BYTE1 - iver ) + ( ihor * imageData->pInfoHData->uiWidth ) ) * BYTE4;
			/* Warning����̂��߂̒��Ԋ֐� */
			ireferenceVer = iver * ihorMax;

			*( protate + ireference )			= ( Color + ireferenceVer + ihor )->b;
			*( protate + ireference + BYTE1 )	= ( Color + ireferenceVer + ihor )->g;
			*( protate + ireference + BYTE2 )	= ( Color + ireferenceVer + ihor )->r;
			*( protate + ireference + BYTE3 )	= ( Color + ireferenceVer + ihor )->a;
		}
	}
	/* --------------------------------------- */
	/* �摜�f�[�^�X�V */
	imageData->pImageData = protate;

	return SUCCESS;
}
/* ------------------------------------------------------------------------- */
/*              Copyright HAL Collage of Technology & Design                 */
/* ------------------------------------------------------------------------- */
