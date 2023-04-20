/* ------------------------------------------------------------------------- */
/* DataInputer.cpp															 */
/* ���͏���																	 */
/* �������e�����															 */
/* ------------------------------------------------------------------------- */
/* �ԍ�	�X�V����								���t		   ����			 */
/* ------------------------------------------------------------------------- */
/* 000000	�V�K�쐬							2021/10/28     �����@�C��	 */
/* 000001	���t�@�N�^�����O					2021/12/02	   ����  �C��	 */
/* ------------------------------------------------------------------------- */
/* Include File																 */
/* ------------------------------------------------------------------------- */
#include "DataInputer.h"

/* ------------------------------------------------------------------------- */
/* �֐���	: DataInputer::DataInputer										 */
/* �@�\��	: �R���X�g���N�^												 */
/* �@�\�T�v	: �f�[�^��������												 */
/* ����		: �Ȃ�															 */
/* �߂�l	: void															 */
/* �쐬��	: 2021/10/28		����  �C��		�V�K�쐬					 */
/* ------------------------------------------------------------------------- */
DataInputer::DataInputer( void ) 
{
	/* ������ & DynamicMemory �m��-------------------- */
	idecorateKind	= NULL;						/* �������					 */
	idecorateSetup	= NULL;						/* �����ݒ�					 */

	idecorateKind	= ( SINT* )calloc( ONE, sizeof( SINT ) );
	idecorateSetup	= ( SINT* )calloc( ONE, sizeof( SINT ) );
	/* --------------------------------------- */

	/* DM�m�ێ��s */
	if( idecorateKind == NULL || idecorateSetup == NULL ) {
		printf( "Get Dynamic Error In DataInputer::DataInputer\n" );
	}
	//
}

/* ------------------------------------------------------------------------- */
/* �֐���	: IndependentProcessing::~IndependentProcessing					 */
/* �@�\��	: �f�X�g���N�^													 */
/* �@�\�T�v	: �m�ۂ��Ă���̈�̉��										 */
/* ����		: �Ȃ�															 */
/* �߂�l	: void															 */
/* �쐬��	: 2021/10/28		����  �C��		�V�K�쐬					 */
/* ------------------------------------------------------------------------- */
DataInputer::~DataInputer( void )
{

	/* DM���--------------------------------- */

	/* �d���J���΍� */
	if ( idecorateKind != NULL && idecorateKind != idecorateSetup ) {
		free( idecorateKind );
	}
	if ( idecorateSetup != NULL ) {
		free( idecorateSetup );
	}
	/* --------------------------------------- */
}

/* ------------------------------------------------------------------------- */
/* �֐���	: DataInputer::get_first										 */
/* �@�\��	: �ŏ��̑���������������										 */
/* �@�\�T�v	: �����͏��������s����										 */
/* ����		: SINT* 	: idecorateKind		: ������ޏ��[I/O] 			 */
/*			: SINT* 	: idecorateSetup	: �����ݒ���[I/O]				 */
/*			: SCHR*		: imageData			: �摜Path[IN]					 */
/*			: SCHR* 	: secondImageData	: �񖇖ڂ̑���Path[IN] 			 */
/*			: SCHR* 	: thirdImageData	: �O���ڂ̑���Path[IN] 			 */
/*			: SCHR* 	: fourthImageData	: �l���ڂ̑���Path[IN]	 		 */
/* �߂�l	: SINT		:					: �G���[�`�F�b�N[OUT]			 */
/* �쐬��	: 2021/10/29		����  �C��		�V�K�쐬					 */
/* ------------------------------------------------------------------------- */
SINT DataInputer::get_first( SINT* idecorateKind, SINT* idecorateSetup, SCHR* orizinalImagePath,
							 SCHR* secondImagePath, SCHR* thirdImagePath, SCHR* fourthImagePath )
{

	/* �����l�`�F�b�N------------------------- */

	/* DM�m�F */
	if ( idecorateKind == NULL ) {
		printf( "decorateInfo Inter Check  Error DecorateInputer::get_first_Kind\n" );
		return FAILE;
	}
	if ( idecorateSetup == NULL ) {
		printf( "decorateInfo Inter Check  Error DecorateInputer::get_first_Setup\n" );
		return FAILE;
	}
	if ( orizinalImagePath == NULL ) {
		printf( "decorateInfo Inter Check  Error DecorateInputer::get_first_Path\n" );
		return FAILE;
	}
	/* --------------------------------------- */

	SINT ierrorCheck = INTI;					/* �G���[�`�F�b�N			 */

	/* ������ޓ���--------------------------- */
	printf( "�������@����͂��Ă�������\n" );
	printf( "1 �摜��],2 �摜���],3 �F���],4 �Z�s�A,5 ���U�C�N,6 �g��E�k��\n" );
	printf( "7 �F�ϊ�,8 ����,9 �c�W��(2 in 1),10 ���W��(2 in 1),11 �W��(4 in 1),12 �I�[�o�[���C,13 ������,14 �I��\n" );
	rewind( stdin );
	( void )scanf( "%d", idecorateKind );

	/* �͈͊O�ē��� */
	while ( *idecorateKind < ROTATE || FIN < *idecorateKind ) {
		printf( "�͈͊O�ē���\n" );
		rewind( stdin );
		( void )scanf( "%d", idecorateKind );
	}
	/* --------------------------------------- */

	/* ��ނ��Ƃ̐ݒ����--------------------- */
	switch ( *idecorateKind ) {

	case ROTATE:								/* ��]�I����				 */

		ierrorCheck = Rotate( idecorateSetup );break;

	case IMAGEINVERT:							/* �摜���]�I����			 */

		ierrorCheck = ImageInvert( idecorateSetup ); break;

	case SEPIA:									/* �Z�s�A�I����				 */

		ierrorCheck = Sepia( idecorateSetup ); break;

	case MOSAIC:								/* ���U�C�N�I����			 */

		ierrorCheck = Mosaic( idecorateSetup ); break;

	case MAGNIFICATION:							/* �{���I����				 */

		ierrorCheck = Magnification( idecorateSetup ); break;

	case COLORCONVERT:							/* �F�ϊ��I����				 */

		ierrorCheck = ColorConvert( idecorateSetup ); break;

	case TWO_IN_ONE_VER:						/* �W��( �c2�� )�I����		 */

		ierrorCheck = Two_In_One_Ver( idecorateSetup, orizinalImagePath, secondImagePath );
		break;

	case TWO_IN_ONE_HOR:						/* �W��( ��2�� )�I����		 */

		ierrorCheck = Two_In_One_Hor( idecorateSetup, orizinalImagePath, secondImagePath );
		break;

	case FOUR_IN_ONE:							/* �W��( 4�� )�I����		 */

		ierrorCheck = Four_In_One( idecorateSetup, orizinalImagePath,
			secondImagePath, thirdImagePath, fourthImagePath );
		break;

	case OVERLAY:								/* �I�[�o�[���C�I����		 */

		ierrorCheck = Overlay( idecorateSetup, secondImagePath ); break;

	case RESTART:

		ierrorCheck = Restart( idecorateSetup );
		break;

	case FIN:

		ierrorCheck = Fin( idecorateSetup );
		break;

	default:									/* �ݒ�s�v��ޑI����		 */

		/* �ݒ���@ZERO�ɂ��� */
		*idecorateSetup = INTI; break;
	}

	if ( ierrorCheck == FAILE ) {
		printf( "���������͏����ŃG���[���������܂���\n" );
		return FAILE;
	}

	return SUCCESS;
}

/* ------------------------------------------------------------------------- */
/* �֐���	: DataInputer::get												 */
/* �@�\��	: ����������������											 */
/* �@�\�T�v	: �����͏��������s����										 */
/* ����		: SINT* 	: idecorateKind		: ������ޏ��[I/O]				 */
/*			: SINT*		: idecorateSetup	: �����ݒ���[I/O]				 */
/*			: SCHR* 	: imagePath			: �摜Path[IN] 					 */
/*			: SCHR* 	: secondImagePath	: �񖇖ڂ̑���Path[IN]	 		 */
/*			: SCHR* 	: thirdImagePath	: �O���ڂ̑���Path[IN]			 */
/*			: SCHR* 	: fourthImagePath	: �l���ڂ̑���Path[IN] 			 */
/* �߂�l	: SINT		:					: �G���[�`�F�b�N[OUT]			 */
/* �쐬��	: 2021/10/29		����  �C��		�V�K�쐬					 */
/* ------------------------------------------------------------------------- */
SINT DataInputer::get( SINT* idecorateKind, SINT* idecorateSetup, SCHR* orizinalImagePath,
					   SCHR* secondImagePath, SCHR* thirdImagePath, SCHR* fourthImagePath ) {

	/* �����l�`�F�b�N------------------------- */

	/* DM�m�F */
	if ( idecorateKind == NULL) {
		printf("decorateInfo Inter Check  Error DecorateInputer::get_Kind\n");
		return FAILE;
	}
	if ( idecorateSetup == NULL ) {
		printf( "decorateInfo Inter Check  Error DecorateInputer::get_Setup\n" );
		return FAILE;
	}
	if ( orizinalImagePath == NULL ) {
		printf( "decorateInfo Inter Check  Error DecorateInputer::get_Path\n" );
		return FAILE;
	}
	/* --------------------------------------- */

	SINT ierrorCheck = INTI;					/* �G���[�`�F�b�N			 */

	/* ������ޓ���--------------------------- */
	printf( "�������@����͂��Ă�������\n" );
	printf( "1 �摜��],2 �摜���],3 �F���],4 �Z�s�A,5 ���U�C�N,6 �g��E�k��\n" );
	printf( "7 �F�ϊ�,8 ���,9 �I��\n" );
	rewind( stdin );
	( void )scanf( "%d", idecorateKind );

	/* �͈͊O�ē��� */
	/* ���ڈȍ~�͒P�Ə������Ȃ��Ȃ�̂ŁA�P�Ə��߂�COPY���I�� */
	while ( *idecorateKind < ROTATE || TWO_IN_ONE_VER < *idecorateKind ) {
		printf( "�͈͊O�ē���\n" );
		rewind( stdin );
		( void )scanf( "%d", idecorateKind );
	}

	/* --------------------------------------- */

	/* ��ނ��Ƃ̐ݒ����--------------------- */
	switch ( *idecorateKind ) {

	case ROTATE:								/* ��]�I����				 */

		ierrorCheck = Rotate( idecorateSetup ); break;

	case IMAGEINVERT:							/* �摜���]�I����			 */
		
		ierrorCheck = ImageInvert( idecorateSetup ); break;

	case SEPIA:									/* �Z�s�A�I����				 */
		
		ierrorCheck = Sepia( idecorateSetup ); break;

	case MOSAIC:								/* ���U�C�N�I����			 */
		
		ierrorCheck = Mosaic( idecorateSetup ); break;

	case MAGNIFICATION:							/* �g��k���I����			 */
		
		ierrorCheck = Magnification( idecorateSetup ); break;

	case COLORCONVERT:							/* �F�ϊ��I����				 */
		
		ierrorCheck = ColorConvert( idecorateSetup ); break;

	case COPY:									/* ������� */

		ierrorCheck = Restart( idecorateSetup );break;

	case TWO_IN_ONE_VER:						/* �I������ */

		ierrorCheck = Fin( idecorateSetup );break;

	default:									/* �ݒ�s�v��ޑI����		 */
		
		/* �ݒ���@ZERO�ɂ��� */
		*idecorateSetup = INTI; break;
	}
	if ( ierrorCheck == FAILE ) {
		printf( "���������͏����ŃG���[���������܂���\n" );
		return FAILE;
	}

	return SUCCESS;
}

/* ------------------------------------------------------------------------- */
/* �֐���	: DataInputer::Rotate											 */
/* �@�\��	: �����ݒ����������											 */
/* �@�\�T�v	: �����͏��������s����										 */
/* ����		: SINT* 	: idecorateSetup	: �����ݒ���[I/O]				 */
/* �߂�l	: SINT		:					: �G���[�`�F�b�N[OUT]			 */
/* �쐬��	: 2021/10/29		����  �C��		�V�K�쐬					 */
/* ------------------------------------------------------------------------- */

SINT DataInputer::Rotate( SINT* idecorateSetup )
{

	/* �����l�`�F�b�N */
	if ( idecorateSetup == NULL ) {
		printf( "decorateInfo Inter Check  Error DecorateInputer::Rotate_Setup\n" );
		return FAILE;
	}

	/* �摜�ݒ���� -------------------------- */
	printf( "�摜��]���I������܂���\n���x��]���܂����A1 90�x,2 180�x,3 270�x,4 360�x\n" );
	rewind( stdin );
	( void )scanf( "%d", idecorateSetup );

	/* �͈͊O�ē��� */
	while ( *idecorateSetup < ROTATE_MIN || ROTATE_MAX < *idecorateSetup ) {
		printf( "�͈͊O�ē���\n" );
		rewind( stdin );
		( void )scanf( "%d", idecorateSetup );
	}
	/* --------------------------------------- */
	return SUCCESS;
}
/* ------------------------------------------------------------------------- */
/* �֐���	: DataInputer::ImageInvert										 */
/* �@�\��	: �����ݒ����������											 */
/* �@�\�T�v	: �����͏��������s����										 */
/* ����		: SINT* 	: idecorateSetup	: �����ݒ���[I/O]				 */
/* �߂�l	: SINT		:					: �G���[�`�F�b�N[OUT]			 */
/* �쐬��	: 2021/10/29		����  �C��		�V�K�쐬					 */
/* ------------------------------------------------------------------------- */
SINT DataInputer::ImageInvert( SINT* idecorateSetup )
{

	/* �����l�`�F�b�N */
	if ( idecorateSetup == NULL ) {
		printf( "decorateInfo Inter Check  Error DecorateInputer::ImageInvert_Setup\n" );
		return FAILE;
	}

	/* �摜�ݒ���� -------------------------- */
	printf( "�摜���]���I������܂���\n�ǂ����]���܂����A1 �㉺,2 ���E\n" );
	rewind( stdin );
	( void )scanf( "%d", idecorateSetup );

	/* �͈͊O�ē��� */
	while ( *idecorateSetup < IMAGE_INVERT_MIN || IMAGE_INVERT_MAX < *idecorateSetup ) {
		printf( "�͈͊O�ē���\n" );
		rewind( stdin );
		( void )scanf( "%d", idecorateSetup );
	}
	/* --------------------------------------- */

	return SUCCESS;
}
/* ------------------------------------------------------------------------- */
/* �֐���	: DataInputer::Sepia											 */
/* �@�\��	: �����ݒ����������											 */
/* �@�\�T�v	: �����͏��������s����										 */
/* ����		: SINT* 	: idecorateSetup	: �����ݒ���[I/O]				 */
/* �߂�l	: SINT		:					: �G���[�`�F�b�N[OUT]			 */
/* �쐬��	: 2021/10/29		����  �C��		�V�K�쐬					 */
/* ------------------------------------------------------------------------- */
SINT DataInputer::Sepia( SINT* idecorateSetup )
{
	/* �����l�`�F�b�N */
	if ( idecorateSetup == NULL ) {
		printf( "decorateInfo Inter Check  Error DecorateInputer::Sepia_Setup\n" );
		return FAILE;
	}

	/* �摜�ݒ���� -------------------------- */
	printf( "�Z�s�A���I������܂���\n�Z�x�͂ǂ����܂����A1 �Z��,2 ����,3 ����\n" );
	rewind( stdin );
	( void )scanf( "%d", idecorateSetup );

	/* �͈͊O�ē��� */
	while ( *idecorateSetup < SEPIA_MIN || SEPIA_MAX < *idecorateSetup ) {
		printf( "�͈͊O�ē���\n" );
		rewind( stdin );
		( void )scanf( "%d", idecorateSetup );
	}
	/* --------------------------------------- */

	return SUCCESS;
}
/* ------------------------------------------------------------------------- */
/* �֐���	: DataInputer::Mosaic											 */
/* �@�\��	: �����ݒ����������											 */
/* �@�\�T�v	: �����͏��������s����										 */
/* ����		: SINT* 	: idecorateSetup	: �����ݒ���[I/O]				 */
/* �߂�l	: SINT		:					: �G���[�`�F�b�N[OUT]			 */
/* �쐬��	: 2021/10/29		����  �C��		�V�K�쐬					 */
/* ------------------------------------------------------------------------- */
SINT DataInputer::Mosaic( SINT* idecorateSetup )
{

	/* �����l�`�F�b�N */
	if ( idecorateSetup == NULL ) {
		printf( "decorateInfo Inter Check  Error DecorateInputer::Mosaic_Setup\n" );
		return FAILE;
	}

	/* �摜�ݒ���� -------------------------- */
	printf( "���U�C�N���I������܂���\n�Z�x�͂ǂ����܂����H (1-�ӂ̒���)\n" );
	rewind( stdin );
	( void )scanf( "%d", idecorateSetup );

	/* �͈͊O�ē��� */
	while ( *idecorateSetup < MOSAIC_MIN ) {
		printf( "�͈͊O�ē���\n" );
		rewind( stdin );
		( void )scanf( "%d", idecorateSetup );
	}
	/* --------------------------------------- */
	return SUCCESS;
}
/* ------------------------------------------------------------------------- */
/* �֐���	: DataInputer::Magnification									 */
/* �@�\��	: �����ݒ����������											 */
/* �@�\�T�v	: �����͏��������s����										 */
/* ����		: SINT* 	: idecorateSetup	: �����ݒ���[I/O]				 */
/* �߂�l	: SINT		:					: �G���[�`�F�b�N[OUT]			 */
/* �쐬��	: 2021/10/29		����  �C��		�V�K�쐬					 */
/* ------------------------------------------------------------------------- */
SINT DataInputer::Magnification( SINT* idecorateSetup )
{
	
	/* �����l�`�F�b�N */
	if ( idecorateSetup == NULL ) {
		printf( "decorateInfo Inter Check  Error DecorateInputer::Mabnification_Setup\n" );
		return FAILE;
	}

	/* �ϐ��錾 */
	FLOT fdecorateSetup = INTI;					/* �ݒ�̏����l�܂Ŏ�邽�߂̕ϐ� */

	/* �摜�ݒ���� -------------------------- */
	/* �g�p��A�������ʂ܂ł̓��͂�������Ă���̂ŁA���͒l��10�{�ɂ���SINT�^�ɕۑ� */
	printf( "�{�����I������܂���\n���͂ǂ����܂����H (0.1-1000)\n�������_���ʈȉ��͐؂藎�Ƃ���܂�\n" );
	rewind( stdin );
	( void )scanf( "%f", &fdecorateSetup );

	/* 10�{�� */
	fdecorateSetup = ( fdecorateSetup * TEN );
	*idecorateSetup = ( SINT )fdecorateSetup;

	/* �͈͊O�ē��� */
	while ( *idecorateSetup < MAGN_MIN || MAGN_MAX < *idecorateSetup ) {
		printf( "�͈͊O�ē���\n" );
		rewind( stdin );
		( void )scanf( "%d", idecorateSetup );
	}
	/* --------------------------------------- */
	return SUCCESS;
}
/* ------------------------------------------------------------------------- */
/* �֐���	: DataInputer::ColorConvert										 */
/* �@�\��	: �����ݒ����������											 */
/* �@�\�T�v	: �����͏��������s����										 */
/* ����		: SINT* 	: idecorateSetup	: �����ݒ���[I/O]				 */
/* �߂�l	: SINT		:					: �G���[�`�F�b�N[OUT]			 */
/* �쐬��	: 2021/10/29		����  �C��		�V�K�쐬					 */
/* ------------------------------------------------------------------------- */
SINT DataInputer::ColorConvert( SINT* idecorateSetup )
{

	/* �����l�`�F�b�N */
	if ( idecorateSetup == NULL ) {
		printf( "decorateInfo Inter Check  Error DecorateInputer::ColorConvert_Setup\n" );
		return FAILE;
	}

	/* �摜�ݒ���� -------------------------- */
	printf( "�F�ϊ����I������܂���bit�ǂ����܂����H\n1 2bit,2 8bit,3 24bit\n" );
	rewind( stdin );
	( void )scanf( "%d", idecorateSetup );

	/* �͈͊O�ē��� */
	while ( *idecorateSetup < COLOR_CONVERT_MIN || COLOR_CONVERT_MAX < *idecorateSetup ) {
		printf( "�͈͊O�ē���\n" );
		rewind( stdin );
		( void )scanf( "%d", idecorateSetup );
	}
	/* --------------------------------------- */
	switch (*idecorateSetup) {
	case 1: *idecorateSetup = 1; break;
	case 2: *idecorateSetup = 8; break;
	case 3: *idecorateSetup = 24; break;

	}
	return SUCCESS;
}
/* ------------------------------------------------------------------------- */
/* �֐���	: DataInputer::Two_In_One_Ver									 */
/* �@�\��	: �����ݒ����������											 */
/* �@�\�T�v	: �����͏��������s����										 */
/* ����		: SINT* 	: idecorateSetup	: �����ݒ���[I/O]				 */
/*			: SCHR* 	: orizinalImagePath	: �摜Path���[I/O]				 */
/* 			: SCHR* 	: secondImagePath	: �摜Path���[I/O]				 */
/* �߂�l	: SINT		:					: �G���[�`�F�b�N[OUT]			 */
/* �쐬��	: 2021/10/29		����  �C��		�V�K�쐬					 */
/* ------------------------------------------------------------------------- */
SINT DataInputer::Two_In_One_Ver( SINT* idecorateSetup, SCHR* orizinalImagePath, SCHR* secondImagePath )
{

	/* �����l�`�F�b�N */
	if ( idecorateSetup == NULL ) {
		printf( "decorateInfo Inter Check  Error DecorateInputer::TIOV_SETup\n" );
		return FAILE;
	}
	if ( orizinalImagePath == NULL ) {
		printf( "decorateInfo Inter Check  Error DecorateInputer::TIOV_Path\n" );
		return FAILE;
	}

	/* �ϐ��錾 */
	SINT icntTIO			= INTI;				/* �J�E���g��				 */
	SINT icntTIO_Check		= INTI;				/* �J�E���g��				 */
	SINT iboxTIO[TWO]		= { INTI,INTI };	/* �摜�ʒu�̓��͒l�̊i�[��	 */

	/* �摜�ݒ���� ------------------------------------ */
	for ( icntTIO = INTI; icntTIO < TWO; icntTIO ++ ) {
		printf( "|--------------|\n" );
		printf( "|				|\n" );
		printf( "|				|\n" );
		printf( "|		�@		|\n" );
		printf( "|				|\n" );
		printf( "|				|\n" );
		printf( "|--------------|\n" );
		printf( "|				|\n" );
		printf( "|				|\n" );
		printf( "|		�A		|\n" );
		printf( "|				|\n" );
		printf( "|				|\n" );
		printf( "|--------------|\n ");

		printf( "%d���ڂ̉摜���ǂ��ɔz�u���܂����H\n", icntTIO + ONE );

		rewind( stdin );
		( void )scanf( "%d", &iboxTIO[icntTIO] );

		/* �@�̉摜ID��10�̈ʁA�A�̉摜ID��1�̈ʂɊi�[ */

		
		for ( icntTIO_Check = icntTIO; INTI < icntTIO_Check; icntTIO_Check -- ) {
			if (iboxTIO[icntTIO] == iboxTIO[icntTIO - icntTIO_Check] ) {
				iboxTIO[icntTIO] = INTI;
			}
		}
		
		/* ���͒l�`�F�b�N -------------------- */
		/* ���͒l���͈͊O */
		while ( iboxTIO[icntTIO] < ONE || TWO < iboxTIO[icntTIO] ) {
			printf( "�͈͊O�ē���\n" );
			rewind( stdin );
			( void )scanf( "%d", &iboxTIO[icntTIO] );

			/* ���͒l�����łɓ��͂���Ă��� */
			
			for ( icntTIO_Check = icntTIO; INTI < icntTIO_Check; icntTIO_Check -- ) {
				if ( iboxTIO[icntTIO] == iboxTIO[icntTIO - icntTIO_Check] ) {
					iboxTIO[icntTIO] = INTI;
				}
			}
		}
		/* -------------------------------------- */
		/* --------------------------------------------- */
		*idecorateSetup = *idecorateSetup * TEN;
		*idecorateSetup = *idecorateSetup + iboxTIO[icntTIO];
	}
	return SUCCESS;
}
/* ------------------------------------------------------------------------- */
/* �֐���	: DataInputer::Two_In_One_Hor									 */
/* �@�\��	: �����ݒ����������											 */
/* �@�\�T�v	: �����͏��������s����										 */
/* ����		: SINT* 	: idecorateSetup	: �����ݒ���[I/O]				 */
/*			: SCHR* 	: orizinalImagePath	: �摜Path���[I/O]				 */
/* 			: SCHR* 	: secondImagePath	: �摜Path���[I/O]				 */
/* �߂�l	: SINT		:					: �G���[�`�F�b�N[OUT]			 */
/* �쐬��	: 2021/10/29		����  �C��		�V�K�쐬					 */
/* ------------------------------------------------------------------------- */
SINT DataInputer::Two_In_One_Hor( SINT* idecorateSetup, SCHR* orizinalImagePath, SCHR* secondImagePath )
{

	/* �����l�`�F�b�N */
	if ( idecorateSetup == NULL ) {
		printf( "decorateInfo Inter Check  Error DecorateInputer::TIOH_Setup\n" );
		return FAILE;
	}
	if ( orizinalImagePath == NULL ) {
		printf( "decorateInfo Inter Check  Error DecorateInputer::TIOH_Path\n" );
		return FAILE;
	}

	/* �ϐ��錾 */
	SINT icntTIO			= INTI;				/* �J�E���g��				 */
	SINT icntTIO_Check		= INTI;				/* �J�E���g��				 */
	SINT iboxTIO[TWO]		= { INTI,INTI };	/* �摜�ʒu�̓��͒l�̊i�[��	 */

	/* �摜�ݒ���� ------------------------------------ */
	for ( icntTIO = INTI; icntTIO < TWO; icntTIO ++ ) {
		printf( "|------------------------------|\n" );
		printf( "|				|				|\n" );
		printf( "|				|				|\n" );
		printf( "|		�@		|		�A		|\n" );
		printf( "|				|				|\n" );
		printf( "|				|				|\n" );
		printf( "|------------------------------|\n" );

		printf( "%d���ڂ̉摜���ǂ��ɔz�u���܂����H\n", icntTIO + ONE );

		rewind( stdin );
		( void )scanf( "%d", &iboxTIO[icntTIO] );

		/* �@�̉摜ID��10�̈ʁA�A�̉摜ID��1�̈ʂɊi�[ */

		
		for ( icntTIO_Check = icntTIO; INTI < icntTIO_Check; icntTIO_Check -- ) {
			if ( iboxTIO[icntTIO] == iboxTIO[icntTIO - icntTIO_Check] ) {
				iboxTIO[icntTIO] = INTI;
			}
		}

		/* ���͒l�`�F�b�N -------------------- */
		/* ���͒l���͈͊O */
		while ( iboxTIO[icntTIO] < ONE || TWO < iboxTIO[icntTIO] ) {
			printf( "�͈͊O�ē���\n" );
			rewind( stdin );
			( void )scanf( "%d", &iboxTIO[icntTIO] );

			/* ���͒l�����łɓ��͂���Ă��� */
			for ( icntTIO_Check = icntTIO; INTI < icntTIO_Check; icntTIO_Check -- ) {
				if (iboxTIO[icntTIO] == iboxTIO[icntTIO - icntTIO_Check] ) {
					iboxTIO[icntTIO] = INTI;
				}
			}
		}
		/* ----------------------------------- */
		/* --------------------------------------------- */
		*idecorateSetup = *idecorateSetup * TEN;
		*idecorateSetup = *idecorateSetup + iboxTIO[icntTIO];
	}
	return SUCCESS;
}
/* ------------------------------------------------------------------------- */
/* �֐���	: DataInputer::Four_In_One										 */
/* �@�\��	: �����ݒ����������											 */
/* �@�\�T�v	: �����͏��������s����										 */
/* ����		: SINT* 	: idecorateSetup	: �����ݒ���[I/O]				 */
/*			: SCHR* 	: orizinalImagePath	: �摜Path���[I/O]				 */
/* 			: SCHR* 	: secondImagePath	: �摜Path���[I/O]				 */
/*			: SCHR* 	: thirdImagePath	: �摜Path���[I/O]				 */
/* 			: SCHR* 	: fourthImagePath	: �摜Path���[I/O]				 */
/* �߂�l	: SINT		:					: �G���[�`�F�b�N[OUT]			 */
/* �쐬��	: 2021/10/29		����  �C��		�V�K�쐬					 */
/* ------------------------------------------------------------------------- */
SINT DataInputer::Four_In_One( SINT* idecorateSetup, SCHR* orizinalImagePath,
							   SCHR* secondImagePath, SCHR* thirdImagePath, SCHR* fourthImagePath )
{

	/* �����l�`�F�b�N */
	if ( idecorateSetup == NULL ) {
		printf( "decorateInfo Inter Check  Error DecorateInputer::FIO_Setup\n" );
		return FAILE;
	}
	if ( orizinalImagePath == NULL ) {
		printf( "decorateInfo Inter Check  Error DecorateInputer::FIO_Path\n" );
		return FAILE;
	}

	/* �ϐ��錾 */
	SINT icntFIO			= INTI;				/* �J�E���g��				 */
	SINT icntFIO_Check		= INTI;				/* �J�E���g��				 */
	SINT iboxFIO[FOUR]		= { INTI,INTI,INTI,INTI };	/* �摜�ʒu�̓��͒l�̊i�[�� */

	/* �摜�ݒ���� ------------------------------------ */
	for ( icntFIO = INTI; icntFIO < FOUR; icntFIO++ ) {
		printf( "|------------------------------|\n" );
		printf( "|				|				|\n" );
		printf( "|				|				|\n" );
		printf( "|		�@		|		�A		|\n" );
		printf( "|				|				|\n" );
		printf( "|				|				|\n" );
		printf( "|------------------------------|\n" );
		printf( "|				|				|\n" );
		printf( "|				|				|\n" );
		printf( "|		�B		|		�C		|\n" );
		printf( "|				|				|\n" );
		printf( "|				|				|\n" );
		printf( "|------------------------------|\n" );
		printf( "%d���ڂ̉摜���ǂ��ɔz�u���܂����H\n", icntFIO + ONE );

		rewind( stdin );
		( void )scanf( "%d", &iboxFIO[icntFIO] );

		/* �@�̉摜ID��1000�̈ʁA�A�̉摜ID��100�̈ʁA�B�̉摜ID��10�̈ʁA�C�̉摜ID��1�̈ʂɊi�[ */

		
		for ( icntFIO_Check = icntFIO; INTI < icntFIO_Check; icntFIO_Check -- ) {
			if (iboxFIO[icntFIO] == iboxFIO[icntFIO - icntFIO_Check] ) {
				iboxFIO[icntFIO] = INTI;
			}
		}
		

		/* ���͒l�`�F�b�N -------------------- */
		/* ���͒l���͈͊O */
		while ( iboxFIO[icntFIO] < ONE || FOUR < iboxFIO[icntFIO] ) {
			printf( "�͈͊O�ē���\n" );
			rewind( stdin );
			( void )scanf( "%d", &iboxFIO[icntFIO] );

			/* ���͒l�����łɓ��͂���Ă��� */
			for ( icntFIO_Check = icntFIO; INTI < icntFIO_Check; icntFIO_Check -- ) {
				if ( iboxFIO[icntFIO] == iboxFIO[icntFIO - icntFIO_Check] ) {
					iboxFIO[icntFIO] = INTI;
				}
			}
		}
		/* ----------------------------------- */
		/* --------------------------------------------- */

		*idecorateSetup = *idecorateSetup * TEN;
		*idecorateSetup = *idecorateSetup + iboxFIO[icntFIO];
	}
	return SUCCESS;
}
/* ------------------------------------------------------------------------- */
/* �֐���	: DataInputer::Overlar											 */
/* �@�\��	: �����ݒ����������											 */
/* �@�\�T�v	: �����͏��������s����										 */
/* ����		: SINT* 	: idecorateSetup	: �����ݒ���[I/O]				 */
/* 			: SCHR* 	: secondImagePath	: �摜Path���[I/O]				 */
/* �߂�l	: SINT		:					: �G���[�`�F�b�N[OUT]			 */
/* �쐬��	: 2021/10/29		����  �C��		�V�K�쐬					 */
/* ------------------------------------------------------------------------- */
SINT DataInputer::Overlay( SINT* idecorateSetup, SCHR* secondImagePath )
{

	/* �����l�`�F�b�N */
	if ( idecorateSetup == NULL ) {
		printf( "decorateInfo Inter Check  Error DecorateInputer::Overlay_Setup\n" );
		return FAILE;
	}

	/* �摜�ݒ���� -------------------------- */
	printf( "�I�[�o�[���C���I������܂������ߗ��ǂ����܂����H(0 - 99)\n" );
	rewind( stdin );
	( void )scanf( "%d", idecorateSetup );

	/* �͈͊O�ē��� */
	while ( *idecorateSetup < OVERLAY_MIN || OVERLAY_MAX < *idecorateSetup ) {
		printf( "�͈͊O�ē���\n" );
		rewind( stdin );
		( void )scanf( "%d", idecorateSetup );
	}
	/* --------------------------------------- */
	return SUCCESS;
}
/* ------------------------------------------------------------------------- */
/* �֐���	: DataInputer::Restart											 */
/* �@�\��	: �����ݒ����������											 */
/* �@�\�T�v	: �����͏��������s����										 */
/* ����		: SINT* 	: idecorateSetup	: �����ݒ���[I/O]				 */
/* �߂�l	: SINT		:					: �G���[�`�F�b�N[OUT]			 */
/* �쐬��	: 2021/11/11		����  �C��		�V�K�쐬					 */
/* ------------------------------------------------------------------------- */
SINT DataInputer::Restart( SINT* idecorateSetup )
{

	/* �����l�`�F�b�N */
	if ( idecorateSetup == NULL ) {
		printf( "decorateInfo Inter Check  Error DecorateInputer::Restart_Setup\n" );
		return FAILE;
	}

	/* �摜�ݒ���� -------------------------- */
	printf( "���������I������܂���\n�{���Ɏ������܂����H\n1 �͂�,2 ������\n" );
	rewind( stdin );
	( void )scanf( "%d", idecorateSetup );

	/* �͈͊O�ē��� */
	while ( *idecorateSetup < ONE || TWO < *idecorateSetup ) {
		printf( "�͈͊O�ē���\n" );
		rewind( stdin );
		( void )scanf( "%d", idecorateSetup );
	}
	/* --------------------------------------- */

	return SUCCESS;
}
/* ------------------------------------------------------------------------- */
/* �֐���	: DataInputer::Fin												 */
/* �@�\��	: �����ݒ����������											 */
/* �@�\�T�v	: �����͏��������s����										 */
/* ����		: SINT* 	: idecorateSetup	: �����ݒ���[I/O]				 */
/* �߂�l	: SINT		:					: �G���[�`�F�b�N[OUT]			 */
/* �쐬��	: 2021/11/11		����  �C��		�V�K�쐬					 */
/* ------------------------------------------------------------------------- */
SINT DataInputer::Fin( SINT* idecorateSetup )
{

	/* �����l�`�F�b�N */
	if ( idecorateSetup == NULL ) {
		printf( "decorateInfo Inter Check  Error DecorateInputer::Fin_Setup\n" );
		return FAILE;
	}

	/* �摜�ݒ���� -------------------------- */
	printf( "�I�����I������܂���\n�{���I�����܂����H\n1 �͂�,2 ������\n" );
	rewind( stdin );
	( void )scanf( "%d", idecorateSetup );

	/* �͈͊O�ē��� */
	while ( *idecorateSetup < ONE || TWO < *idecorateSetup ) {
		printf( "�͈͊O�ē���\n" );
		rewind( stdin );
		( void )scanf( "%d", idecorateSetup );
	}
	/* --------------------------------------- */

	return SUCCESS;
}

/* ------------------------------------------------------------------------- */
/*              Copyright HAL Collage of Technology & Design                 */
/* ------------------------------------------------------------------------- */
