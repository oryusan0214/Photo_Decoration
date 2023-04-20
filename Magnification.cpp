/* ------------------------------------------------------------------------- */
/* Magnification.cpp														 */
/* �g��k������																 */
/* �摜�̊g��k�����s��														 */
/* ------------------------------------------------------------------------- */
/* �ԍ�	�X�V����								���t		   ����			 */
/* ------------------------------------------------------------------------- */
/* 000000	�V�K�쐬							2021/10/28     �����@�C��	 */
/* 000001	���t�@�N�^�����O					2021/11/27	   ����  �C��	 */
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
/* Include File																 */
/* ------------------------------------------------------------------------- */
#include "System.h"
#include "Magnification.h"


/* ------------------------------------------------------------------------- */
/* �֐���	: Magnification::exe											 */
/* �@�\��	: ���s����														 */
/* �@�\�T�v	: �g��k�����������s����										 */
/* ����		: DecorateList* : decorateInfo		: �������[IN]	 			 */
/*			: FileData* 	: imageData			: �摜���[I/O] 			 */
/* �߂�l	: SINT		:					: �G���[�`�F�b�N[OUT]			 */
/* �쐬��	: 2021/10/28		����  �C��		�V�K�쐬					 */
/* ------------------------------------------------------------------------- */
SINT Magnification::exe( DecorateList* decorateInfo, FileData* imageData )
{

	/* ���͒l�`�F�b�N------------------------- */

	/* DM */
	if ( decorateInfo == NULL ) {
		printf( "decorateInfo Inter Check  Error In Magn::exe_decorateList\n" );
		return FAILE;
	}
	if ( imageData == NULL ) {
		printf( "decorateInfo Inter Check  Error In Magn::exe_imageData\n" );
		return FAILE;
	}
	/* ������� */
	if ( decorateInfo->decolateKind != MAGNIFICATION ) {
		printf( "decorateInfo Inter Check  Error In Magnification::exe_Kind\n" );
		return FAILE;
	}
	/* �����ݒ� */
	if ( decorateInfo->decolatesetup < MAGN_MIN || MAGN_MAX < decorateInfo->decolatesetup ) {
		printf( "decorateInfo Inter Check  Error In Magnification::exe_Setup\n" );
		return FAILE;
	}
	/* �^�� */
	if ( imageData->pFileHData->sFile_Header_Name != MAGIC_NUMBER ) {
		printf( "imageData Inter Check Error In Magnification_Type\n" );
		return FAILE;
	}
	/* �傫�� */
	if ( imageData->pInfoHData->uiWidth <= INTI || imageData->pInfoHData->uiHeight <= INTI ) {
		printf( "imageData Inter Check Error In Magnification::exe_Size\n" );
		return FAILE;
	}

	/* �ϐ��錾 */
	UCHR* pmag			= NULL;					/* ������̉摜�̃f�[�^		 */
	SINT ibaseVer		= INTI;					/* ���摜�̍���				 */
	SINT ibaseHor		= INTI;					/* ���摜�̕�				 */
	SINT iMG_Cnt		= INTI;					/* �J�E���g��				 */
	SINT iMG_Ver		= INTI;					/* �J�E���g��				 */
	SINT iMG_Hor		= INTI;					/* �J�E���g��				 */
	SINT iloop_Ver		= INTI;					/* �c���[�v��				 */
	SINT iloop_Hor		= INTI;					/* �����[�v��				 */
	SINT iloop_Ver_Cnt	= INTI;					/* �J�E���g��				 */
	SINT iloop_Hor_Cnt	= INTI;					/* �J�E���g��				 */
	FLOT fmag			= INTI;					/* ���݂̕K�v���[�v			 */
	FLOT fcnt_Ver		= INTI;					/* �J�E���g��				 */
	FLOT fcnt_Hor		= INTI;					/* �J�E���g��				 */
	SINT imageSize		= INTI;					/* �摜�̃s�N�Z����			 */
	SINT ireference_Ver = INTI;					/* �c�̎Q�Ɛ� WARNING���	 */
	SINT ireference_Hor = INTI;					/* ���̎Q�Ɛ� WARNING���	 */


	/* �c���̒l���� */
	ibaseVer = imageData->pInfoHData->uiHeight;
	ibaseHor = imageData->pInfoHData->uiWidth;

	/* --------------------------------------- */
	/* �{���擾(Setup�͏\�{�̒l�ɂȂ��Ă���̂�) */
	fmag = decorateInfo->decolatesetup / GET_MAG;

	/* �摜�T�C�Y�擾 */
	imageSize = imageData->pInfoHData->uiWidth * imageData->pInfoHData->uiHeight * BYTE4 * fmag;


	/* �傫���ύX */
	imageData->pInfoHData->uiWidth	= imageData->pInfoHData->uiWidth	* fmag / EXC_MAG;
	imageData->pInfoHData->uiHeight	= imageData->pInfoHData->uiHeight	* fmag / EXC_MAG;

	/* ipixel�ȉ���� */
	if( imageSize < BYTE1 ){
		imageData->pInfoHData->uiWidth	= BYTE1;
		imageData->pInfoHData->uiHeight	= BYTE1;
		imageSize						= BYTE1;
	}
	/* get DM */
	pmag = ( UCHR* )calloc( imageSize , sizeof( UCHR ) );

	/* DM check */
	if ( pmag == NULL ) {
		printf( "get dynamic error In Magnification\n" );
		return FAILE;
	}	
	/* 
	* �ŋߖT�ϖ@�𗘗p
	* 
	* 1  2  3  4  
	* 5  6  7  8  
	* 9  10 11 12 
	* 13 14 15 16 
	* 
	* ��200%
	* 
	* 1  .  2  .  3  .  4  . 
	* .  .  .  .  .  .  .  .
	* 5  .  6  .  7  .  8  .
	* .  .  .  .  .  .  .  .
	* 9  .  10 .  11 .  12 .
	* .  .  .  .  .  .  .  . 
	* 13 .  14 .  15 .  16 .
	* 
	* ���@. �̈ʒu�̕K�v�ȏ��A�Ȃ̂� . �̈ʒu����
	*       �ł��߂��Ƃ���ɂ���F��񂪂����̏��Ƃ݂Ȃ�
	* 
	* ���l����
	*	134%�̊g��ł���΁A3���1�񂾂�2�񃋁[�v
	* ��
	* 1   2   3		1   .2  . 3
	* 
	* 
	* 
	* 4   5   6 ��	.   .   .
	*				4    5    6
	* 
	* 
	* 7   8   9		.   .   .
	*
	*				7    8    9 
	* 
	* 10  11  12	.   .   .
	* 
	* 
	*				10   .11  . 12
	* 
	* 
	* 
	*	�Ȃ̂ŁA���[�v���Ƃɔ{���l�𑫂��āA100�ň������l�����[�v����
	*	�܂�
	*	
	*	�{��134%
	*			sum		
	*	1���   0 + 134	 134 - 100 = 34	��1���[�v	
	*	2���   34+ 134	 168 - 100 = 68	��1���[�v   
	*	3���   68+ 134	 202 - 200 = 2	��2���[�v
	*	4���   2 + 134	 136 - 100 = 36	��1���[�v
	* 
	* �Ƃ����l���Ń��[�v�����l����
	* 
	*/

	/* ��������------------------------------- */

	/* 1pixel */
	if( imageSize == BYTE1 ){
		/* Warning��� */
		ireference_Ver = ( ibaseHor / BYTE2 ) + ( ibaseVer * ibaseHor / BYTE2 ) * BYTE4;

		/* 1BYTE�Ȃ�^�񒆌��ߑł� */
		*pmag = *( imageData->pImageData + ireference_Ver );

		/* �f�[�^�̍X�V */
		imageData->pImageData = pmag;

		return SUCCESS;
	}

	/* �c�J�E���g( ���摜�̍����� ) */
	for ( iMG_Ver = INTI; iMG_Ver < ibaseVer; iMG_Ver ++ ) {

		/* ���[�v���Z�o */
		fcnt_Ver = fcnt_Ver + fmag;
		while ( GET_LOOP <= fcnt_Ver ) {
			fcnt_Ver = fcnt_Ver - GET_LOOP;
			iloop_Ver ++;
		}

		/* �Q�Ɛ��擾 */
		ireference_Ver = iMG_Ver * ibaseHor * BYTE4;

		/* �c���[�v */
		for ( iloop_Ver_Cnt = INTI; iloop_Ver_Cnt < iloop_Ver; iloop_Ver_Cnt ++ ) {

				/* ���J�E���g( ���摜�̕� ) */
			for ( iMG_Hor = INTI; iMG_Hor < ibaseHor; iMG_Hor ++ ) {

				/* ���[�v���Z�o */
				fcnt_Hor = fcnt_Hor + fmag;
				while ( GET_LOOP <= fcnt_Hor ) {
					fcnt_Hor = fcnt_Hor - GET_LOOP;
					iloop_Hor ++;
				}
				/* �Q�Ɛ��擾 */
				ireference_Hor = iMG_Hor * BYTE4;

				/* �����[�v */
				for (iloop_Hor_Cnt = INTI; iloop_Hor_Cnt < iloop_Hor; iloop_Hor_Cnt ++ ) {

					/* 1�s�N�Z����������---------------- */
					/* ibasever ��ibasehor�ɕύX */
					*( pmag + iMG_Cnt ) = *( imageData->pImageData + ireference_Ver + ireference_Hor);
					iMG_Cnt ++;
					*( pmag + iMG_Cnt ) = *( imageData->pImageData + ireference_Ver + ireference_Hor + BYTE1 );
					iMG_Cnt ++;
					*( pmag + iMG_Cnt ) = *( imageData->pImageData + ireference_Ver + ireference_Hor + BYTE2 );
					iMG_Cnt ++;
					*( pmag + iMG_Cnt ) = *( imageData->pImageData + ireference_Ver + ireference_Hor + BYTE3 );
					iMG_Cnt ++;
					/* --------------------------------- */
				}
				/* ���[�v�l�̏����� */
				iloop_Hor = INTI;
			}
		}
		/* ���[�v�l�̏����� */
		iloop_Ver = INTI;
	}
	/* --------------------------------------- */
	
	/* �f�[�^�̍X�V */
	imageData->pImageData = pmag;

	return SUCCESS;
}
/* ------------------------------------------------------------------------- */
/*              Copyright HAL Collage of Technology & Design                 */
/* ------------------------------------------------------------------------- */
