/* ------------------------------------------------------------------------- */
/* Sepia.cpp																 */
/* �Z�s�A����																 */
/* �Z�s�A�������s															 */
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
#include "Sepia.h"


/* ------------------------------------------------------------------------- */
/* �֐���	: Sepia::exe													 */
/* �@�\��	: �Z�s�A����													 */
/* �@�\�T�v	: �Z�s�A�����s����												 */
/* ����		: DecorateList*	: decorateInfo		: �������[OUT] 			 */
/*			: FileData*		: imageData			: �摜���[OUT] 			 */
/* �߂�l	: SINT			:					: �G���[�`�F�b�N[IN]		 */
/* �쐬��	: 2021/10/15		����  �C��		�V�K�쐬					 */
/* ------------------------------------------------------------------------- */
SINT Sepia::exe( DecorateList* decorateInfo, FileData* imageData )
{
	/* �ϐ��錾 */
	SINT ierrorCheck = INTI;					/* �G���[�`�F�b�N			 */

	/* ���͒l�`�F�b�N------------------------- */

	/* DM */
	if ( decorateInfo == NULL ) {
		printf( "decorateInfo Inter Check  Error In Sepia::exe_decorateList\n" );
		return FAILE;
	}
	if ( imageData == NULL ) {
		printf( "decorateInfo Inter Check  Error In Sepia::exe_imageData\n" );
		return FAILE;
	}
	/* ������� */
	if ( decorateInfo->decolateKind != SEPIA ) {
		printf( "decorateInfo Inter Check  Error In Sepia::exe_Kind\n" );
		return FAILE;
	}
	/* �����ݒ� */
	if ( decorateInfo->decolatesetup < SEPIA_MIN || SEPIA_MAX < decorateInfo->decolatesetup ) {
		printf( "decorateInfo Inter Check  Error In Sepia::exe_Setup\n" );
		return FAILE;
	}
	/* �^�� */
	if ( imageData->pFileHData->sFile_Header_Name != MAGIC_NUMBER ) {
		printf( "imageData Inter Check Error In Sepia::exe_Type\n" );
		return FAILE;
	}
	/* �������� */
	if ( imageData->pInfoHData->uiHeight <= INTI || imageData->pInfoHData->uiWidth <= INTI ) {
		printf( "imageData Inter Check Error In Sepia::exe_Size\n" );
		return FAILE;
	}
	/* --------------------------------------- */
	/* �ݒ育�Ƃɔ�΂� */
	if ( decorateInfo->decolatesetup == DARK ) {
		ierrorCheck = dark( imageData );
	}
	else if ( decorateInfo->decolatesetup == NORMAL ) {
		ierrorCheck = normal( imageData );
	}
	else if ( decorateInfo->decolatesetup == DELUTE ) {
		ierrorCheck = delute( imageData );
	}
	if ( ierrorCheck == FAILE ) {
		printf( "�Z�s�A�����ُ�I�����܂���\n" );
		return FAILE;
	}
	return SUCCESS;
}
/* ------------------------------------------------------------------------- */
/* �֐���	: Sepia::dark													 */
/* �@�\��	: �Z�s�A����													 */
/* �@�\�T�v	: �Z�s�A�����s����												 */
/* ����		: FileData*	: imageData			: �摜���[OUT] 				 */
/* �߂�l	: SINT		:					: �G���[�`�F�b�N[IN]			 */
/* �쐬��	: 2021/10/15		����  �C��		�V�K�쐬					 */
/* ------------------------------------------------------------------------- */
SINT Sepia::dark( FileData* imageData )
{

	if ( imageData == NULL ) {
		printf( "decorateInfo Inter Check  Error In Sepia::dark_imageData\n" );
		return FAILE;
	}

	/* �ϐ��錾 */
	UCHR* psepia	= NULL;						/* ������̉摜�f�[�^		 */
	SINT ishine		= INTI;						/* �P�x���v					 */
	SINT iSP_Ver	= INTI;						/* �J�E���g��				 */
	SINT iSP_Hor	= INTI;						/* �J�E���g��				 */
	SINT imageSize	= INTI;						/* �摜�T�C�Y				 */
	SINT ireference = INTI;						/* ���ݎQ�Ƃ��Ă���o�C�g	 */
	UCHR iblue		= INTI;						/* ��						 */
	UCHR igreen		= INTI;						/* ��						 */
	UCHR ired		= INTI;						/* ��						 */

	/* �摜�T�C�Y�擾 */
	imageSize = imageData->pInfoHData->uiHeight * imageData->pInfoHData->uiWidth * BYTE4;

	/* get DM */
	psepia = ( UCHR* )calloc( imageSize, sizeof( UCHR ) );

	/* DM check */
	if ( psepia == NULL ) {
		printf( "get error\n" );
		return FAILE;
	}
	/* �Z�s�A��------------------------------- */
	for ( iSP_Ver = INTI; iSP_Ver < imageData->pInfoHData->uiHeight; iSP_Ver ++ ) {
		for ( iSP_Hor = INTI; iSP_Hor < imageData->pInfoHData->uiWidth ; iSP_Hor ++ ) {

			/* �Q�ƒl�擾 */
			ireference = iSP_Ver * imageData->pInfoHData->uiWidth * BYTE4 + iSP_Hor * BYTE4;

			/* �P�x���v�擾 */
			ishine = *( imageData->pImageData + ireference ) +
					 *( imageData->pImageData + ireference + BYTE1 ) +
					 *( imageData->pImageData + ireference + BYTE2 );

			/* �Z�s�A�� */
			iblue	= ishine * MAG_DA_B;
			igreen	= ishine * MAG_DA_G;
			ired	= ishine * MAG_DA_R;

			/* �f�[�^�i�[ */
			*( psepia + ireference )			= iblue;
			*( psepia + ireference + BYTE1 )	= igreen;
			*( psepia + ireference + BYTE2 )	= ired;
			*( psepia + ireference + BYTE3 )	= *( imageData->pImageData + ireference + BYTE3 );
		}
	}
	/* --------------------------------------- */
	/* �f�[�^�X�V */
	imageData->pImageData = psepia;

	return SUCCESS;
}

/* ------------------------------------------------------------------------- */
/* �֐���	: Sepia::normal													 */
/* �@�\��	: �Z�s�A����													 */
/* �@�\�T�v	: �Z�s�A�����s����												 */
/* ����		: FileData*	: imageData			: �摜���[OUT] 				 */
/* �߂�l	: SINT		:					: �G���[�`�F�b�N[IN]			 */
/* �쐬��	: 2021/10/15		����  �C��		�V�K�쐬					 */
/* ------------------------------------------------------------------------- */
SINT Sepia::normal( FileData* imageData )
{
	
	if ( imageData == NULL ) {
		printf( "decorateInfo Inter Check  Error In Sepia::normal_imageData\n" );
		return FAILE;
	}

	/* �ϐ��錾 */
	UCHR* psepia	= NULL;						/* ������̉摜�f�[�^		 */
	SINT ishine		= INTI;						/* �P�x���v					 */
	SINT iSP_Ver	= INTI;						/* �J�E���g��				 */
	SINT iSP_Hor	= INTI;						/* �J�E���g��				 */
	SINT imageSize	= INTI;						/* �摜�T�C�Y				 */
	SINT ireference = INTI;						/* ���ݎQ�Ƃ��Ă���s�N�Z��	 */
	UCHR iblue		= INTI;						/* ��						 */
	UCHR igreen		= INTI;						/* ��						 */
	UCHR ired		= INTI;						/* ��						 */

	/* �摜�T�C�Y�擾 */
	imageSize = imageData->pInfoHData->uiHeight * imageData->pInfoHData->uiWidth * BYTE4;

	/* get DM */
	psepia = ( UCHR* )calloc( imageSize, sizeof( UCHR ) );

	/* DM check */
	if ( psepia == NULL ) {
		printf( "get error\n" );
		return FAILE;
	}
	/* �Z�s�A��------------------------------- */
	for ( iSP_Ver = INTI; iSP_Ver < imageData->pInfoHData->uiHeight; iSP_Ver ++ ) {
		for ( iSP_Hor = INTI; iSP_Hor < imageData->pInfoHData->uiWidth ; iSP_Hor ++ ) {

			/* �Q�ƒl�擾 */
			ireference = ( iSP_Ver * imageData->pInfoHData->uiWidth + iSP_Hor ) * BYTE4;

			/* �P�x���v�擾 */
			ishine = *( imageData->pImageData + ireference ) +
					 *( imageData->pImageData + ireference + BYTE1 ) +
					 *( imageData->pImageData + ireference + BYTE2 );

			/* �Z�s�A�� */
			iblue	= ishine * MAG_NO_B;
			igreen	= ishine * MAG_NO_G;
			ired	= ishine * MAG_NO_R;

			/* �f�[�^�i�[ */
			*( psepia + ireference )			= iblue;
			*( psepia + ireference + BYTE1 )	= igreen;
			*( psepia + ireference + BYTE2 )	= ired;
			*( psepia + ireference + BYTE3 )	= *( imageData->pImageData + ireference + BYTE3 );
		}
	}
	/* --------------------------------------- */
	/* �f�[�^�X�V */
	imageData->pImageData = psepia;

	return SUCCESS;
}

/* ------------------------------------------------------------------------- */
/* �֐���	: Sepia::delute													 */
/* �@�\��	: �Z�s�A����													 */
/* �@�\�T�v	: �Z�s�A�����s����												 */
/* ����		: FileData*	: imageData			: �摜���[OUT] 				 */
/* �߂�l	: SINT		:					: �G���[�`�F�b�N[IN]			 */
/* �쐬��	: 2021/10/15		����  �C��		�V�K�쐬					 */
/* ------------------------------------------------------------------------- */

SINT Sepia::delute(FileData* imageData)
{

	if ( imageData == NULL ) {
		printf( "decorateInfo Inter Check  Error In Sepia::delute_imageData\n" );
		return FAILE;
	}
	
	/* �ϐ��錾 */
	UCHR* psepia	= NULL;						/* ������̉摜�f�[�^		 */
	SINT ishine		= INTI;						/* �P�x���v					 */
	SINT iSP_Ver	= INTI;						/* �J�E���g��				 */
	SINT iSP_Hor	= INTI;						/* �J�E���g��				 */
	SINT imageSize	= INTI;						/* �摜�T�C�Y				 */
	SINT ireference = INTI;						/* ���ݎQ�Ƃ��Ă���s�N�Z��	 */
	UCHR iblue		= INTI;						/* ��						 */
	UCHR igreen		= INTI;						/* ��						 */
	UCHR ired		= INTI;						/* ��						 */

	/* �摜�T�C�Y�擾 */
	imageSize = imageData->pInfoHData->uiHeight * imageData->pInfoHData->uiWidth * BYTE4;

	/* get DM */
	psepia = ( UCHR* )calloc( imageSize, sizeof( UCHR ) );

	/* DM check */
	if ( psepia == NULL ) {
		printf( "get error\n" );
		return FAILE;
	}
	/* �Z�s�A��------------------------------- */
	for ( iSP_Ver = INTI; iSP_Ver < imageData->pInfoHData->uiHeight; iSP_Ver ++ ) {
		for ( iSP_Hor = INTI; iSP_Hor < imageData->pInfoHData->uiWidth ; iSP_Hor ++ ) {

			/* �Q�ƒl�擾 */
			ireference = iSP_Ver * imageData->pInfoHData->uiWidth * BYTE4 + iSP_Hor * BYTE4;

			/* �P�x���v�擾 */
			ishine = *( imageData->pImageData + ireference ) +
					 *( imageData->pImageData + ireference + BYTE1 ) +
					 *( imageData->pImageData + ireference + BYTE2 );

			/* �Z�s�A�� */
			iblue	= ishine * MAG_DE_B;
			igreen	= ishine * MAG_DE_G;
			ired	= ishine * MAG_DE_R;

			/* �f�[�^�i�[ */
			*( psepia + ireference )			= iblue;
			*( psepia + ireference + BYTE1 )	= igreen;
			*( psepia + ireference + BYTE2 )	= ired;
			*( psepia + ireference + BYTE3 )	= *( imageData->pImageData + ireference + BYTE3 );
		}
	}
	/* --------------------------------------- */
	/* �f�[�^�X�V */
	imageData->pImageData = psepia;

	return SUCCESS;
}

/* ------------------------------------------------------------------------- */
/*              Copyright HAL Collage of Technology & Design                 */
/* ------------------------------------------------------------------------- */
