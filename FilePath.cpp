/* ------------------------------------------------------------------------- */
/* FilePath.cpp																 */
/* FilePath�֘A																 */
/* Filepath�擾����															 */
/* ------------------------------------------------------------------------- */
/* �ԍ�	�X�V����								���t		   ����			 */
/* ------------------------------------------------------------------------- */
/* 000000	�V�K�쐬							2021/10/25     �����@�C��	 */
/* 000001	���t�@�N�^�����O					2021/11/29	   ����  �C��	 */
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
/* Include File																 */
/* ------------------------------------------------------------------------- */
#include "System.h"
#include "FilePath.h"

/* ------------------------------------------------------------------------- */
/* protype																	 */
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
/* �֐���	: check_type													 */
/* �@�\��	: path�̌^�����擾����											 */
/* �@�\�T�v	: strcat�̋^����												 */
/* ����		: SCHR*			: FilePath			: path						 */
/* �߂�l	: SCHR*			: FilePath			: path						 */
/* �쐬��	: 2021/11/30		����  �C��		�V�K�쐬					 */
/* ------------------------------------------------------------------------- */
SCHR* check_type( SCHR* filePath );

/* ------------------------------------------------------------------------- */
/* �֐���	: check_path													 */
/* �@�\��	: �摜���ȊO��path���擾����									 */
/* �@�\�T�v	: strcat�̋^����												 */
/* ����		: SCHR*			: FilePath			: path						 */
/* �߂�l	: SCHR*			: FilePath			: path						 */
/* �쐬��	: 2021/11/30		����  �C��		�V�K�쐬					 */
/* ------------------------------------------------------------------------- */
SCHR* check_path( SCHR* filePath );

/* ------------------------------------------------------------------------- */
/* �֐���	: FilePath::FilePath											 */
/* �@�\��	: �R���X�g���N�^												 */
/* �@�\�T�v	: �f�[�^��������												 */
/* ����		: �Ȃ�															 */
/* �߂�l	: void															 */
/* �쐬��	: 2021/10/25		����  �C��		�V�K�쐬					 */
/* ------------------------------------------------------------------------- */
FilePath::FilePath( void )
{

	/* ������ */
	imageType			= NULL;
	orizinalImagePath	= NULL;
	secondImagePath		= NULL;
	thirdImagePath		= NULL;
	fourthImagePath		= NULL;
	/*get DM */
	imageType			= ( SCHR* )calloc( PATHLENGTH,sizeof( SCHR ) );
	orizinalImagePath	= ( SCHR* )calloc( PATHLENGTH,sizeof( SCHR ) );
	secondImagePath		= ( SCHR* )calloc( PATHLENGTH,sizeof( SCHR ) );
	thirdImagePath		= ( SCHR* )calloc( PATHLENGTH,sizeof( SCHR ) );
	fourthImagePath		= ( SCHR* )calloc( PATHLENGTH,sizeof( SCHR ) );

	/* DM Chech */
	if( orizinalImagePath == NULL || secondImagePath == NULL || thirdImagePath == NULL || fourthImagePath == NULL ){
		printf( "Get DM Error In FilePath::FilePath" );
	}

}

/* ------------------------------------------------------------------------- */
/* �֐���	: FilePath::~FilePath											 */
/* �@�\��	: �f�X�g���N�^													 */
/* �@�\�T�v	: �f�[�^�����													 */
/* ����		: �Ȃ�															 */
/* �߂�l	: void															 */
/* �쐬��	: 2021/10/25		����  �C��		�V�K�쐬					 */
/* ------------------------------------------------------------------------- */
FilePath::~FilePath( void )
{
	/* ���d�J���΍� */
	if ( imageType != NULL ) {
		free( imageType );
	}
	if ( orizinalImagePath != NULL && orizinalImagePath != secondImagePath && orizinalImagePath != thirdImagePath && orizinalImagePath != fourthImagePath ) {
		free( orizinalImagePath );
	}
	if ( secondImagePath != NULL && secondImagePath != thirdImagePath && secondImagePath != fourthImagePath ) {
		free( secondImagePath );
	}
	if ( thirdImagePath != NULL && thirdImagePath != fourthImagePath ) {
		free( thirdImagePath );
	}
	if ( fourthImagePath != NULL ) {
		free( fourthImagePath );
	}
}

/* ------------------------------------------------------------------------- */
/* �֐���	: FilePath::get													 */
/* �@�\��	: �擾����														 */
/* �@�\�T�v	: �x�[�X�̉摜��Path������										 */
/* ����		: SCHR* 	: orizinalImagePath	: �摜Path���[IN / OUT] 		 */
/* �߂�l	: SINT		:					: �G���[�`�F�b�N[OUT]			 */
/* �쐬��	: 2021/10/25		����  �C��		�V�K�쐬					 */
/* ------------------------------------------------------------------------- */
SINT FilePath::get( SCHR* orizinalImagePath )
{
	if ( orizinalImagePath == NULL ) {
		printf( "OrizinalImagePath Inter Check In FilePath::get" );
		return FAILE;
	}

	SINT  ierrorCheck	= INTI;					/* �G���[�`�F�b�N			 */
	SINT  icnt			= INTI;					/* �J�E���g��				 */
	SCHR* decoy			= NULL;					/* ��						 */
	SCHR* pathCpy		= NULL;					/* Path�̃R�s�[				 */
	SCHR* type			= NULL;					/* �^��						 */
	SCHR* path			= NULL;					/* Folder�܂ł�Path			 */
	SCHR  inPutPath[PATHLENGTH];				/* BMP_IN��PATH				 */

	/* Path get------------------------------- */
	while ( TRUE ) {
		/* ������ */
		memset( inPutPath,INTI,PATHLENGTH );
		decoy		= ( SCHR* )calloc( PATHLENGTH, sizeof( SCHR ) );
		pathCpy		= ( SCHR* )calloc( PATHLENGTH, sizeof( SCHR ) );
		path		= ( SCHR* )calloc( PATHLENGTH, sizeof( SCHR ) );
		type		= ( SCHR* )calloc( PATHLENGTH, sizeof( SCHR ) );
		strcpy( inPutPath,"C:\\Decorate_System\\BMP_IN\\" );


		/* Check*/
		if ( decoy == NULL || pathCpy == NULL || path == NULL || type == NULL ) {
			printf( "Dynamic Memory Get Error In FilePath::get\n" );
			return FAILE;
		}

		printf( "Please drag & drop file you want Decorate Image\n���l�߉摜����]����ۂ� e ����͂��Ă�������( �W��񖇖ڈȍ~�̉摜���� )\n" );
		rewind( stdin );
		ierrorCheck = scanf( "%s", orizinalImagePath );

		if ( ierrorCheck == NULL ) {
			printf( "scanf error in FilePath::get\n" );
			return FAILE;
		}



		if ( *orizinalImagePath == 'e') {
			return SUCCESS;
		}

		/* Type test------------------- */

		/* copy & get type */
		strcpy( pathCpy, orizinalImagePath );

		/* strcat�̉��� */
		decoy = check_type( pathCpy );
		
		while ( decoy != NULL ) {
			/*
			strcat( path, type );
			strcat( path, "." );
			*/
			strcpy( type, decoy );

			decoy = check_type( NULL );

		}
		/* �������ϊ� */
		for (icnt = INTI; icnt < BYTE4; icnt ++ ) {
			if(  'A' <= *(type + icnt ) && *(type + icnt ) <= 'Z' ){
				*(type + icnt ) = *( type + icnt ) + ( 'a' - 'A' );
			}
		}

		/* �͈͊O error */
		if ( !( strcmp( type,"jpeg" ) == STR_OK || strcmp( type,"jpg" ) == STR_OK || strcmp( type,"ping" ) == STR_OK 
			 || strcmp( type,"png" ) == STR_OK || strcmp( type,"bmp" ) == STR_OK ) ) {

			printf("�Ή��O�̊g���q�ł��B�ēx�قȂ�摜����͂��Ă��������B\n");
			strcpy( path, "" );
			strcpy( type, "" );

			continue;
		}
		/* ---------------------------- */

		/* �^���ۑ� */
		strcpy( imageType,type );

		/* Path check------------------ */

		/* ������ */
		strcpy( path, "" );
		strcpy( type, "" );
		decoy	= ( SCHR* )calloc( PATHLENGTH, sizeof( SCHR ) );
		pathCpy = ( SCHR* )calloc( PATHLENGTH, sizeof( SCHR ) );
		/* Check*/
		if ( pathCpy == NULL || decoy == NULL ) {
			printf( "Dynamic Memory Get Error In FilePath::get\n" );
			return FAILE;
		}


		strcpy( pathCpy, orizinalImagePath );

		/* strcat�̉��� */
		decoy = check_path( pathCpy );
		
		while ( decoy != NULL ) {
			
			strcat( path, type );
			strcat( path, "\\" );
			
			strcpy( type, decoy );

			decoy = check_path( NULL );

		}
		/* \\ ���ŏ��ɂɂ��̂�++ */
		path ++;

		/* �͈͊O error */
		if ( strcmp( path,inPutPath ) != STR_OK ) {

			printf("�Ή��O��Path�ł��B�ēx�قȂ�摜����͂��Ă��������B\n");
			strcpy( path, "" );
			strcpy( type, "" );

			continue;
		}

		/* ---------------------------- */
		/* ���펞������ */
		break;
	}

	/* --------------------------------------- */

	return SUCCESS;
}

/* ------------------------------------------------------------------------- */
/* �֐���	: check_type													 */
/* �@�\��	: path�̌^�����擾����											 */
/* �@�\�T�v	: strcat�̋^����												 */
/* ����		: SCHR*			: FilePath			: path						 */
/* �߂�l	: SCHR*			: FilePath			: path						 */
/* �쐬��	: 2021/11/30		����  �C��		�V�K�쐬					 */
/* ------------------------------------------------------------------------- */
SCHR* check_type( SCHR* filePath ) {

	static SCHR* cutPath = NULL;				/* box						 */

	/* copy ���ڂ� box �� path ����ڈȍ~�� box ���� path �� copy */
	if ( filePath != NULL ) {
		cutPath = filePath;
	}
	else {
		/* ��؂�ォ��J�n */
		filePath = cutPath;
	}
	/* fin */
	if ( filePath == NULL ) {
		return NULL;
	}
	/* check */
	while ( TRUE ) {
		/* last */
		if ( *cutPath == NULL ) {				/* �Ō�ɓ��B */
			cutPath = NULL;						/* stand fin flag */
			return filePath;
		}
		/* cut */
		if ( *cutPath == '.' ) {
			*cutPath = INTI;					/* filePath��.��0(\0)�ɕς��ċ�؂� */
			cutPath ++;							/* ����̂��߂ɐi�߂� */
			return filePath;					/* ��؂�O�܂ŕԂ� */
		}

		cutPath ++;
	}
}

/* ------------------------------------------------------------------------- */
/* �֐���	: check_path													 */
/* �@�\��	: �摜���ȊO��path���擾����									 */
/* �@�\�T�v	: strcat�̋^����												 */
/* ����		: SCHR*			: FilePath			: path						 */
/* �߂�l	: SCHR*			: FilePath			: path						 */
/* �쐬��	: 2021/11/30		����  �C��		�V�K�쐬					 */
/* ------------------------------------------------------------------------- */
SCHR* check_path( SCHR* filePath ) {

	static SCHR* cutPath = NULL;				/* box						 */

	/* copy ���ڂ�box��path����ڈȍ~��box����path��copy */
	if ( filePath != NULL ) {
		cutPath = filePath;
	}
	else {
		/* ��؂�ォ��J�n */
		filePath = cutPath;
	}
	/* fin */
	if ( filePath == NULL ) {
		return NULL;
	}
	/* check */
	while ( TRUE ) {
		/* last */
		if ( *cutPath == NULL ) {				/* �Ō�ɓ��B */
			cutPath = NULL;						/* stand fin flag */
			return filePath;
		}
		/* cut */
		if ( *cutPath == '\\' ) {
			*cutPath = INTI;					/* filePath��.��0(\0)�ɕς��ċ�؂� */
			cutPath ++;							/* ����̂��߂ɐi�߂� */
			return filePath;					/* ��؂�O�܂ŕԂ� */
		}
		cutPath ++;
	}
}

/* ------------------------------------------------------------------------- */
/*              Copyright HAL Collage of Technology & Design                 */
/* ------------------------------------------------------------------------- */
