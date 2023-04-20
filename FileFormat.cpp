/* ------------------------------------------------------------------------- */
/* FileFormat.cpp															 */
/* FileFormat�֘A															 */
/* FileFormat,�ۑ���擾����												 */
/* ------------------------------------------------------------------------- */
/* �ԍ�	�X�V����								���t		   ����			 */
/* ------------------------------------------------------------------------- */
/* 000000	�V�K�쐬							2021/10/25     �����@�C��	 */
/* 000001	���t�@�N�^�����O					2021/11/29	   ����  �C��	 */
/* ------------------------------------------------------------------------- */
/* Include File																 */
/* ------------------------------------------------------------------------- */
#include "System.h"
#include "FileFormat.h"

/* ------------------------------------------------------------------------- */
/* �֐���	: FileFormat::FileFormat										 */
/* �@�\��	: �R���X�g���N�^												 */
/* �@�\�T�v	: �f�[�^��������												 */
/* ����		: �Ȃ�															 */
/* �߂�l	: void															 */
/* �쐬��	: 2021/10/25		����  �C��		�V�K�쐬					 */
/* ------------------------------------------------------------------------- */
FileFormat::FileFormat( void )
{
	/* ������ & get DM */
	saveFileName	= NULL;
	saveFileName	= ( SCHR* )calloc( PATHLENGTH , sizeof( SCHR ) );

	/* Check DM */
	if ( saveFileName == NULL ) {
		printf( "Get DM error in FileFormat::FileFormat\n" );
	}
}

/* ------------------------------------------------------------------------- */
/* �֐���	: FileFormat::~FileFormat										 */
/* �@�\��	: �f�X�g���N�^													 */
/* �@�\�T�v	: �f�[�^�����													 */
/* ����		: �Ȃ�															 */
/* �߂�l	: void															 */
/* �쐬��	: 2021/10/25		����  �C��		�V�K�쐬					 */
/* ------------------------------------------------------------------------- */
FileFormat::~FileFormat( void )
{
	/* ��� */
	if ( saveFileName != NULL ) {
		free( saveFileName );
	}
}

/* ------------------------------------------------------------------------- */
/* �֐���	: FileFormat::get												 */
/* �@�\��	: �擾����														 */
/* �@�\�T�v	: �ۑ�File�����擾����											 */
/* ����		: SCHR*	 	: saveFileName		: �ۑ�File��[I/O]				 */
/*			: SCHR*	 	: bmpOutPath		: �摜�o��Path[IN]				 */
/*			: SCHR*	 	: imageType			: �o�͉摜Type[IN]				 */
/* �߂�l	: SINT		:					: �G���[�`�F�b�N[OUT]			 */
/* �쐬��	: 2021/10/25		����  �C��		�V�K�쐬					 */
/* ------------------------------------------------------------------------- */
SINT FileFormat::get( SCHR* saveFileName,SCHR* bmpOutPath,SCHR* imageType )
{
	SINT ierrorCheck = INTI;					/* scnaf�̃G���[�`�F�b�N	 */

	/* �����l�`�F�b�N */
	/* DM check */
	if ( saveFileName == NULL ) {
		printf( "decorateInfo Inter Check  FileFormat::get_saveFileName\n" );
		return FAILE;
	}
	if ( bmpOutPath == NULL ) {
		printf( "decorateInfo Inter Check  FileFormat::get_bmpOutPath\n" );
		return FAILE;
	}
	if ( imageType == NULL ) {
		printf( "decorateInfo Inter Check  FileFormat::get_imageType\n" );
		return FAILE;
	}

	/* ���͏���------------------------------- */
	while( TRUE ){
		printf( "�ۑ�File������͂��Ă�������\n" );
		rewind( stdin );

		ierrorCheck = scanf( "%s", saveFileName );

		if ( ierrorCheck == NULL ) {
			continue;
		}
		strcat(saveFileName, ".");
		strcat( saveFileName,imageType );

		/* ���Ԃ�`�F�b�N */
		ierrorCheck = check( saveFileName,bmpOutPath );

		if ( ierrorCheck == FAILE ) {
			continue;
		}
		break;
	
	/* --------------------------------------- */
	}
	return SUCCESS;
}

/* ------------------------------------------------------------------------- */
/* �֐���	: FileFormat::check												 */
/* �@�\��	: ��r����														 */
/* �@�\�T�v	: bmpOut��Folder��saveFileName�Ɠ����File���Ȃ����m�F����		 */
/* ����		: SCHR*	 	: saveFileName		: �ۑ�File��[I/O]				 */
/*			: SCHR*	 	: bmpOutPath		: �摜�o��Path[IN]				 */
/* �߂�l	: SINT		:					: �G���[�`�F�b�N[OUT]			 */
/* �쐬��	: 2021/12/02		����  �C��		�V�K�쐬					 */
/* ------------------------------------------------------------------------- */
SINT FileFormat::check( SCHR* saveFileName,SCHR* bmpOutPath ) {

	HANDLE			Hdl			= NULL;			/* FindFolder�̃A�h���X�i�[�� */
	WIN32_FIND_DATA Hdl_Buff	= { NULL };		/* FindFolder�̏��i�[�� */

	SCHR*			bmpPathCpy;					/* �{�����path�i�[�� */

	bmpPathCpy = ( SCHR* )calloc( PATHLENGTH, sizeof( SCHR ) );

	if ( bmpPathCpy == NULL ) {
		printf( "Get DM Error In check\n" );
		return FAILE;
	}

	/* FIRST FIND */
	sprintf( bmpPathCpy, "%s\\*.*", bmpOutPath );	/* *.*�͎c���Ăق����Ȃ��̂�cpy�̕��� */
	Hdl = FindFirstFile( bmpPathCpy, &Hdl_Buff );

	/* �{���G���[(*.*�̏d���Ȃǂ�����) */
	if ( Hdl == INVALID_HANDLE_VALUE ) {
		printf( "INVALID HANDLE VALUE ERROR\n" );
		system( "pause" );
		return FAILE;								/* �����I�� */
	}

	/* �`�F�b�N���� */
	do {
		/* �{�����path��cpy�Ɋi�[ */
		sprintf( bmpPathCpy, "%s\\%s", bmpOutPath, Hdl_Buff.cFileName );

		/* �e�A�q��through���� */
		if ( strcmp( ".", Hdl_Buff.cFileName ) == STR_OK || strcmp( "..", Hdl_Buff.cFileName ) == STR_OK ) {
			continue;
		}
		
		/* ���O��r	 */
		if( strcmp( saveFileName,Hdl_Buff.cFileName ) == STR_OK ){
			printf( "����File�����o�^����Ă��܂��A�ʂ̖��O����͂��Ă�������\n" );
			return FAILE;
		}

		/* ����FILE�T�������ċ�Ȃ烋�[�v������ */
	} while ( FindNextFile( Hdl, &Hdl_Buff ) != NULL );

	/* Close */
	FindClose( Hdl );
	return SUCCESS;
}
/* ------------------------------------------------------------------------- */
/*              Copyright HAL Collage of Technology & Design                 */
/* ------------------------------------------------------------------------- */
