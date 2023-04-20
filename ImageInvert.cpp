/* ------------------------------------------------------------------------- */
/* ImageInvert.cpp															 */
/* �摜���]����																 */
/* �摜�𔽓]���鏈��														 */
/* ------------------------------------------------------------------------- */
/* �ԍ�	�X�V����								���t		   ����			 */
/* ------------------------------------------------------------------------- */
/* 000000	�V�K�쐬							2021/10/27     �����@�C��	 */
/* 000001	���t�@�N�^�����O					2021/11/27	   ����  �C��	 */
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
/* Include File																 */
/* ------------------------------------------------------------------------- */
#include "System.h"
#include "ImageInvert.h"


/* ------------------------------------------------------------------------- */
/* �֐���	: ImageImvert::exe												 */
/* �@�\��	: ���s����														 */
/* �@�\�T�v	: �摜���]���������s����										 */
/* ����		: DecorateList*	: decorateInfo		: �������[IN]				 */
/*			: FileData* 	: imageData			: �摜���[I/O] 			 */
/* �߂�l	: SINT			:					: �G���[�`�F�b�N[OUT]		 */
/* �쐬��	: 2021/10/27		����  �C��		�V�K�쐬					 */
/* ------------------------------------------------------------------------- */
SINT ImageInvert::exe( DecorateList* decorateInfo, FileData* imageData )
{

	/* �ϐ��錾 */
	SINT iRT_Ver		= INTI;					/* �����̃J�E���g��			 */
	SINT iRT_Hor		= INTI;					/* ���̃J�E���g��			 */
	SINT ierrorCheck	= INTI;					/* �G���[�`�F�b�N			 */
	rgb* Color			= NULL;					/* 1�s�N�Z��������̋P�x�i�[ */
	SINT imageSize		= INTI;					/* �摜�̃s�N�Z����			 */
	SINT ireference		= INTI;					/* �Q�Ɛ� WARNING���		 */

	/* ���͒l�`�F�b�N */
	
	/* DM */
	if ( decorateInfo == NULL ) {
		printf( "decorateInfo Inter Check  Error ImageInvert::exe_decorateList\n" );
		return FAILE;
	}
	if ( imageData == NULL ) {
		printf( "decorateInfo Inter Check  Error In ImageInvert::exe_imageData\n" );
		return FAILE;
	}
	/* ������� */
	if ( decorateInfo->decolateKind != IMAGEINVERT ) {
		printf( "decorateInfo Inter Check  Error In ImageInvert::exe_Kind\n" );
		return FAILE;
	}
	/* �����ݒ� */
	if ( decorateInfo->decolatesetup < IMAGE_INVERT_MIN || IMAGE_INVERT_MAX < decorateInfo->decolatesetup ) {
		printf( "decorateInfo Inter Check  Error In ImageInvert::exe_Setup\n" );
		return FAILE;
	}
	/* �^�� */
	if ( imageData->pFileHData->sFile_Header_Name != MAGIC_NUMBER ) {
		printf( "imageData Inter Check Error In ImageInvert::exe_Type\n" );
		return FAILE;
	}
	/* �傫�� */
	if ( imageData->pInfoHData->uiWidth <= INTI || imageData->pInfoHData->uiHeight <= INTI ) {
		printf( "imageData Inter Check Error In ImageInvert:exe_Size\n" );
		return FAILE;
	}
	/* �T�C�Y�擾 */
	imageSize = imageData->pInfoHData->uiWidth * imageData->pInfoHData->uiHeight;

	/* get DM */
	Color = ( rgb* )calloc(imageSize, sizeof( rgb ) );

	/* DM check */
	if ( Color == NULL ) {
		printf( "get dynamic error In ImageInvert\n" );
		return FAILE;
	}

	/* 
	imageData->colordata

	255 255 255 0 125 125 125 0 10 20 30 0....

	Color
	r 255 125 10 
	g 255 125 20
	b 255 125 30...

	�����W�I�ȍl���Ŕ��]�������s���̂�1�s�N�Z��������̋P�x���܂Ƃ߂Ċi�[
	*/
	for ( iRT_Ver = INTI; iRT_Ver < imageData->pInfoHData->uiHeight; iRT_Ver ++ ) {
		/* �Q�ƒl�擾 */
		ireference = iRT_Ver * imageData->pInfoHData->uiWidth;

		for ( iRT_Hor = INTI; iRT_Hor < imageData->pInfoHData->uiWidth; iRT_Hor ++ ) {

			( Color + ireference + iRT_Hor )->b = *imageData->pImageData;
			imageData->pImageData ++;
			( Color + ireference + iRT_Hor )->g = *imageData->pImageData;
			imageData->pImageData ++;
			( Color + ireference + iRT_Hor )->r = *imageData->pImageData;
			imageData->pImageData ++;
			( Color + ireference + iRT_Hor )->a = *imageData->pImageData;
			imageData->pImageData ++;
		}
	}
	/* �ݒ�ɍ��킹�ď����֐��ɔ�΂� */
	if ( decorateInfo->decolatesetup == HL_INVERT ) {
		ierrorCheck = hl_invert( Color, imageData );
	} else if ( decorateInfo->decolatesetup == RL_INVERT ) {
		ierrorCheck  = rl_invert( Color, imageData );
	}

	if ( ierrorCheck == FAILE ) {
		printf( "�摜���]�����Ɏ��s���܂���\n" );
		return FAILE;
	}

	return SUCCESS;
}
/* ------------------------------------------------------------------------- */
/* �֐���	: ImageImvert::hl_invert										 */
/* �@�\��	: ���s����														 */
/* �@�\�T�v	: �㉺���]���������s����										 */
/* ����		: rgb*			: Color				: �s�N�Z�����[IN]			 */
/*			: FileData* 	: imageData			: �摜���[I/O] 			 */
/* �߂�l	: SINT			:					: �G���[�`�F�b�N[OUT]		 */
/* �쐬��	: 2021/10/27		����  �C��		�V�K�쐬					 */
/* ------------------------------------------------------------------------- */
SINT ImageInvert::hl_invert( rgb* Color, FileData* imageData )
{

	/* DM */
	if ( Color == NULL ) {
		printf( "decorateInfo Inter Check  Error In ImageInvert::hl_Color\n" );
		return FAILE;
	}
	if ( imageData == NULL ) {
		printf( "decorateInfo Inter Check  Error ImageInvert::hl_imageData\n" );
		return FAILE;
	}
	
	/* �ϐ��錾 */
	UCHR* protate		= NULL;					/* ������̃f�[�^�i�[��		 */
	SINT iver			= INTI;					/* �c�J�E���g				 */
	SINT ihor			= INTI;					/* ���J�E���g				 */
	SINT imageSize		= INTI;					/* �摜�̃o�C�g��			 */
	SINT ireferenceBfr	= INTI;					/* �ω��O�̎Q�Ɛ� WARNING���*/
	SINT ireferenceAft	= INTI;					/* �ω���̎Q�Ɛ� WARNING���*/

	/* �T�C�Y�擾 */
	imageSize = imageData->pInfoHData->uiWidth * imageData->pInfoHData->uiHeight * BYTE4;

	/* get DM */
	protate = ( UCHR* )calloc( imageSize, sizeof( UCHR ) );

	/* DM check */
	if ( protate == NULL ) {
		printf( "get dynamic error In hlInvert\n" );
		return FAILE;
	}
	/*
		10 11 12  �T
		7  8  9	  �U
		4  5  6   �V
		1  2  3   �W

		�@ �A �B

		���X���̂悤�Ƀs�N�Z���f�[�^���i�[����Ă���̂��A

		1  2  3   �W 
		4  5  6   �V
		7  8  9   �U
		10 11 12  �T

		�@ �A �B
		
		���̂悤�ɂȂ�̂�
		���̍��W���@( hor , ver ) �Ƃ���Ƒ�����̍��W��( hor ,imageData->Ver - ver )�ƂȂ�̂ł��̗��_��p����

	*/
	/* �������� */
	for ( iver = INTI; iver < imageData->pInfoHData->uiHeight; iver ++ ) {
		/* �Q�Ɛ��擾 */
		ireferenceAft = iver * imageData->pInfoHData->uiWidth;

		for ( ihor = INTI; ihor < imageData->pInfoHData->uiWidth; ihor ++ ) {

			/* �Q�Ɛ��擾 */
			ireferenceBfr = ( ( imageData->pInfoHData->uiHeight - BYTE1 - iver ) * imageData->pInfoHData->uiWidth * BYTE4 ) + ihor * BYTE4;

			/* b���i�[ */
			*( protate + ireferenceBfr)			= ( Color + ireferenceAft + ihor )->b;
			/* g���i�[ */
			*( protate + ireferenceBfr + BYTE1 )	= ( Color + ireferenceAft + ihor )->g;
			/* r���i�[ */
			*( protate + ireferenceBfr + BYTE2 )	= ( Color + ireferenceAft + ihor )->r;
			/* �����i�[ */
			*( protate + ireferenceBfr + BYTE3 )	= ( Color + ireferenceAft + ihor )->a;
		}
	}
	/* �摜���X�V */
	imageData->pImageData = protate;

	return SUCCESS;
}

/* ------------------------------------------------------------------------- */
/* �֐���	: ImageImvert::rl_invert										 */
/* �@�\��	: ���s����														 */
/* �@�\�T�v	: ���E���]���������s����										 */
/* ����		: rgb*			: Color				: �s�N�Z�����[IN]			 */
/*			: FileData* 	: imageData			: �摜���[I/O] 			 */
/* �߂�l	: SINT			:					: �G���[�`�F�b�N[OUT]		 */
/* �쐬��	: 2021/10/27		����  �C��		�V�K�쐬					 */
/* ------------------------------------------------------------------------- */
SINT ImageInvert::rl_invert( rgb* Color, FileData* imageData )
{

	/* DM */
	if ( Color == NULL ) {
		printf( "decorateInfo Inter Check  Error In Invert::rl_Color\n" );
		return FAILE;
	}
	if ( imageData == NULL ) {
		printf( "decorateInfo Inter Check  Error In Invert::rl_imageData\n" );
		return FAILE;
	}

	/* �ϐ��錾 */
	UCHR* protate		= NULL;					/* ������̃f�[�^�i�[��		 */
	SINT iver			= INTI;					/* �c�J�E���g				 */
	SINT ihor			= INTI;					/* ���J�E���g				 */
	SINT imageSize		= INTI;					/* �摜�̃o�C�g��			 */
	SINT ireferenceBfr	= INTI;					/* �ω��O�̎Q�Ɛ� WARNING���*/
	SINT ireferenceAft	= INTI;					/* �ω���̎Q�Ɛ� WARNING���*/

	/* �T�C�Y�擾 */
	imageSize = imageData->pInfoHData->uiWidth * imageData->pInfoHData->uiHeight * BYTE4;

	/* get DM */
	protate = ( UCHR* )calloc( imageSize ,sizeof( UCHR ) );

	/* DM check */
	if ( protate == NULL ) {
		printf( "get dynamic error In rlInvert\n" );
		return FAILE;
	}

	/*
		10 11 12  �T
		7  8  9	  �U
		4  5  6   �V
		1  2  3   �W

		�@ �A �B

		���X���̂悤�Ƀs�N�Z���f�[�^���i�[����Ă���̂��A

		12 11 10 �T
		9  8  7	 �U
		6  5  4	 �V
		3  2  1  �W

		�B �A �@

		���̂悤�ɂȂ�̂�
		���̍��W���@( hor , ver ) �Ƃ���Ƒ�����̍��W��( imageData->Hor - hor , ver )�ƂȂ�̂ł��̗��_��p����

	*/

	/* �������� */
	for ( iver = INTI; iver < imageData->pInfoHData->uiHeight; iver ++ ) {
		/* �Q�Ɛ��擾 */
		ireferenceAft = iver * imageData->pInfoHData->uiWidth;

		for ( ihor = INTI; ihor < imageData->pInfoHData->uiWidth; ihor ++ ) {
			/* �Q�Ɛ��擾 */
			ireferenceBfr = (iver * imageData->pInfoHData->uiWidth * BYTE4) + (imageData->pInfoHData->uiWidth - BYTE1 - ihor) * BYTE4;

			/* b���i�[ */
			*( protate + ireferenceBfr )			= ( Color + ireferenceAft + ihor )->b;
			/* g���i�[ */
			*( protate + ireferenceBfr + BYTE1 )	= ( Color + ireferenceAft + ihor )->g;
			/* r���i�[ */
			*( protate + ireferenceBfr + BYTE2 )	= ( Color + ireferenceAft + ihor )->r;
			/* �����i�[ */
			*( protate + ireferenceBfr + BYTE3 )	= ( Color + ireferenceAft + ihor )->a;

		}
	}
	/* �摜���X�V */
	imageData->pImageData = protate;

	return SUCCESS;

}

/* ------------------------------------------------------------------------- */
/*              Copyright HAL Collage of Technology & Design                 */
/* ------------------------------------------------------------------------- */
