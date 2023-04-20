/* ------------------------------------------------------------------------- */
/* Mosaic.cpp																 */
/* ���U�C�N����																 */
/* �摜�̗��x�𗎂Ƃ�														 */
/* ------------------------------------------------------------------------- */
/* �ԍ�	�X�V����								���t		   ����			 */
/* ------------------------------------------------------------------------- */
/* 000000	�V�K�쐬							2021/10/31     �����@�C��	 */
/* 000001	���t�@�N�^�����O					2021/11/27	   ����  �C��	 */
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
/* Include File																 */
/* ------------------------------------------------------------------------- */
#include "System.h"
#include "Mosaic.h"


/* ------------------------------------------------------------------------- */
/* �֐���	: Mosaic::exe													 */
/* �@�\��	: ���s����														 */
/* �@�\�T�v	: ���U�C�N�����s����											 */
/* ����		: DecorateList* : decorateInfo		: �������[IN]				 */
/*			: FileData* 	: imageData			: �摜���[I/O] 			 */
/* �߂�l	: SINT		:					: �G���[�`�F�b�N[OUT]			 */
/* �쐬��	: 2021/10/31		����  �C��		�V�K�쐬					 */
/* ------------------------------------------------------------------------- */
SINT Mosaic::exe( DecorateList* decorateInfo, FileData* imageData )
{
	//
	/* �ϐ��錾 */
	UCHR* pmosaic		= NULL;					/* ������̉摜�f�[�^		 */
	SINT ired			= INTI;					/* �Ԃ̕��ϒl				 */
	SINT iblue			= INTI;					/* �̕��ϒl				 */
	SINT igreen			= INTI;					/* �΂̕��ϒl				 */
	SINT iMSC_Ver		= INTI;					/* �J�E���g��				 */
	SINT iMSC_Hor		= INTI;					/* �J�E���g��				 */
	SINT iMSC_Ver_Cnt	= INTI;					/* �J�E���g��				 */
	SINT iMSC_Hor_Cnt	= INTI;					/* �J�E���g��				 */
	SINT iMSC_Cnt		= INTI;					/* �J�E���g��				 */
	SINT iMSC_Ver_Max	= INTI;					/* �c�̃��[�v�ő�l			 */
	SINT iMSC_Hor_Max	= INTI;					/* ���̃��[�v�ő�l			 */
	SINT iLoop			= INTI;					/* ���[�v��					 */
	SINT imageSize		= INTI;					/* �摜�̃s�N�Z����			 */
	SINT ireference		= INTI;					/* WARNING���p			 */

	/* ���͒l�`�F�b�N */

	/* DM */
	if ( decorateInfo == NULL ) {
		printf( "decorateInfo Inter Check  Error In Mosaic::exe_decorateList\n" );
		return FAILE;
	}
	if ( imageData == NULL ) {
		printf( "decorateInfo Inter Check  Error In Mosaic::exe_imageData\n" );
		return FAILE;
	}
	/* ������� */
	if ( decorateInfo->decolateKind != MOSAIC ) {
		printf( "decorateInfo Inter Check  Error In Mosaic::exe_Kind\n" );
		return FAILE;
	}
	/* �����ݒ� */
	if ( decorateInfo->decolatesetup <= INTI ) {
		printf( "decorateInfo Inter Check  Error In Mosaic::exe_Setup\n" );
		return FAILE;
	}
	/* �^�� */
	if ( imageData->pFileHData->sFile_Header_Name != MAGIC_NUMBER ) {
		printf( "imageData Inter Check Error In Mosaic::exe_Type\n" );
		return FAILE;
	}
	/* �傫�� */
	if ( imageData->pInfoHData->uiWidth <= INTI || imageData->pInfoHData->uiHeight <= INTI ) {
		printf( "imageData Inter Check Error In Mosaic::exe_Size\n" );
		return FAILE;
	}

	/* ���͒l���ӂ��傫���ꍇ�͕ӂ̒����ɕύX */
	if ( imageData->pInfoHData->uiHeight < imageData->pInfoHData->uiWidth && imageData->pInfoHData->uiWidth < decorateInfo->decolatesetup ) {
		decorateInfo->decolatesetup = imageData->pInfoHData->uiWidth;
	}
	if ( imageData->pInfoHData->uiWidth < imageData->pInfoHData->uiHeight && imageData->pInfoHData->uiHeight < decorateInfo->decolatesetup ) {
		decorateInfo->decolatesetup = imageData->pInfoHData->uiHeight;
	}

	/* �T�C�Y�擾 */
	imageSize = imageData->pInfoHData->uiWidth * imageData->pInfoHData->uiHeight * BYTE4;

	/* Get DM */
	pmosaic = ( UCHR* )calloc( imageSize , sizeof( UCHR ) );
	
	/* DM Check */
	if ( pmosaic == NULL ) {
		printf( "get DM error In Mosaic\n" );
		return FAILE;
	}
	/* ���U�C�N����--------------------------- */

	/* ���[�v���擾 */
	iMSC_Ver_Max = ( imageData->pInfoHData->uiHeight ) / decorateInfo->decolatesetup;
	iMSC_Hor_Max = ( imageData->pInfoHData->uiWidth  )  / decorateInfo->decolatesetup;

	if( ( ( imageData->pInfoHData->uiHeight ) % decorateInfo->decolatesetup ) != INTI ){
		iMSC_Ver_Max ++;
	}
	if( ( ( imageData->pInfoHData->uiWidth ) % decorateInfo->decolatesetup ) != INTI ){
		iMSC_Hor_Max ++;
	}

	
	
	/* ���[�v�l���s��Ȃ̂Ŗ������[�v */
	while ( TRUE ) {
		/* �c���[�v */
		for ( iMSC_Ver = iMSC_Ver_Cnt * decorateInfo->decolatesetup; iMSC_Ver < (iMSC_Ver_Cnt + BYTE1 ) * decorateInfo->decolatesetup; iMSC_Ver ++ ) {

			/* �[�ɂ�����u���[�N */
			/* -1��ǉ� */
			if ( iMSC_Ver == ( imageData->pInfoHData->uiHeight - BYTE1 ) ) {
				break;
			}
			/* �Q�ƒl�擾 */
			ireference = iMSC_Ver * imageData->pInfoHData->uiWidth * BYTE4;

			/* �����[�v */
			for ( iMSC_Hor = iMSC_Hor_Cnt * BYTE4 * decorateInfo->decolatesetup; iMSC_Hor < (iMSC_Hor_Cnt + BYTE1 ) * BYTE4 * decorateInfo->decolatesetup; iMSC_Hor ++ ) {

				/* �[�ɂ�����break */
				/* -1��ǉ� */
				if ( iMSC_Hor == ( ( imageData->pInfoHData->uiWidth - BYTE1 ) * BYTE4 ) ) {
					break;
				}
				/* rgb���ŏꍇ���� */
				switch ( ( iMSC_Hor + BYTE1 ) % BYTE4 ) {
				case INTI:	/* �� */
					iMSC_Cnt ++;															break;

				case BYTE1:	/* b  */
					iblue	= iblue  + *(imageData->pImageData + ireference + iMSC_Hor);	break;

				case BYTE2:	/* g  */
					igreen	= igreen + *(imageData->pImageData + ireference + iMSC_Hor);	break;

				case BYTE3	/* r  */
				:	ired	= ired   + *(imageData->pImageData + ireference + iMSC_Hor);	break;

				default:
					break;
				}
			}
		}
		
		/* 0����΍� ���_��͂������܂Ȃ� */
		if (iMSC_Cnt == INTI) {
			iMSC_Cnt = BYTE1;
		}

		/* ���ϒl�Z�o */
		iblue	= iblue		/ iMSC_Cnt;
		igreen	= igreen	/ iMSC_Cnt;
		ired	= ired		/ iMSC_Cnt;
		
		/* �f�[�^���� */
		/* �c���[�v */
		for ( iMSC_Ver = iMSC_Ver_Cnt * decorateInfo->decolatesetup; iMSC_Ver < ( iMSC_Ver_Cnt + BYTE1 ) * decorateInfo->decolatesetup; iMSC_Ver ++ ) {

			/* �[�ɂ�����break */
			/* -1�ǉ� */
			if ( iMSC_Ver == ( imageData->pInfoHData->uiHeight - BYTE1 ) ) {
				break;
			}
			/* �Q�ƒl�擾 */
			ireference = iMSC_Ver * imageData->pInfoHData->uiWidth * BYTE4;

			/* �����[�v */
			for ( iMSC_Hor = iMSC_Hor_Cnt * BYTE4 * decorateInfo->decolatesetup; iMSC_Hor < ( iMSC_Hor_Cnt + BYTE1 ) * BYTE4 * decorateInfo->decolatesetup; iMSC_Hor ++ ) {
				/* �[�ɂ�����break */
				/* -1�ǉ� */
				if ( iMSC_Hor == ( imageData->pInfoHData->uiWidth * BYTE4 ) ) {
					break;
				}
				/* rgb���ŏꍇ���� */
				switch ( ( iMSC_Hor + BYTE1 ) % BYTE4 ) {
				case INTI:	/* �� */
					*( pmosaic + ireference + iMSC_Hor ) = ( UCHR )INTI;	break;

				case BYTE1:	/* b  */
					*( pmosaic + ireference + iMSC_Hor ) = iblue;			break;

				case BYTE2:	/* g  */
					*( pmosaic + ireference + iMSC_Hor ) = igreen;			break;

				case BYTE3:	/* r  */
					*( pmosaic + ireference + iMSC_Hor ) = ired;			break;

				default:
					break;
				}
			}
		}
		/* �J�E���g�l��++ */
		/* = �ɕύX */
		iMSC_Hor_Cnt ++;

		/* ���}�b�N�X�̎� */
		if ( iMSC_Hor_Max == iMSC_Hor_Cnt ) {
			iMSC_Hor_Cnt = INTI;
			iMSC_Ver_Cnt ++;

			/* �c�}�b�N�X�̎� */
			if ( iMSC_Ver_Max == iMSC_Ver_Cnt ) {
				break;
			}
		}
		/* ������ */
		iblue		= INTI;
		igreen		= INTI;
		ired		= INTI;
		iMSC_Cnt	= INTI;
		
	}
	/* deta�X�V */
	imageData->pImageData = pmosaic;
	
	return SUCCESS;

}
/* ------------------------------------------------------------------------- */
/*              Copyright HAL Collage of Technology & Design                 */
/* ------------------------------------------------------------------------- */
