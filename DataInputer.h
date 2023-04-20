#pragma once
/* ------------------------------------------------------------------------- */
/* DataInputer.h															 */
/* ���͏���																	 */
/* �N���X��`�y�сA�֐��ȂǍŒ���̏��̂݋L��								 */
/* ------------------------------------------------------------------------- */
/* �ԍ�	�X�V����								���t		   ����			 */
/* 000000	�V�K�쐬							2021/10/28     �����@�C��	 */
/* 000001	���t�@�N�^�����O					2021/12/02	   ����  �C��	 */
/* ------------------------------------------------------------------------- */
/* Secure �錾																 */
/* ------------------------------------------------------------------------- */
#define  _CRT_NO_SECURE_WARNINGS
#define  _CRT_SECURE_NO_DEPRECATE

/* ------------------------------------------------------------------------- */
/* Include File																 */
/* ------------------------------------------------------------------------- */
#include "System.h"

/* ------------------------------------------------------------------------- */
/* Define�錾																 */
/* ------------------------------------------------------------------------- */
#define ONE		1								/* 1�̈Ӗ�					 */
#define TWO		2								/* 1�̈Ӗ�					 */
#define FOUR	4								/* 1�̈Ӗ�					 */
#define TEN		10								/* �ݒ�l�̐ݒ莞�ɗp����	 */

/* ------------------------------------------------------------------------- */
/* �\���̒�`																 */
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
/* Class��`																 */
/* ------------------------------------------------------------------------- */
class DataInputer {
public:
	DataInputer ( void );						/* �R���X�g���N�^			 */
	~DataInputer( void );						/* �f�X�g���N�^				 */

	SINT* idecorateKind;						/* ���						 */
	SINT* idecorateSetup;						/* �ݒ�						 */


	SINT get_first( SINT* idecorateKind, SINT* idecorateSetup, SCHR* orizinalImagePath, SCHR* secondImagePath, SCHR* thirdImagePath, SCHR* fourthImagePath );
	SINT get	  ( SINT* idecorateKind, SINT* idecorateSetup, SCHR* orizinalImagePath, SCHR* secondImagePath, SCHR* thirdImagePath, SCHR* fourthImagePath );


private:
	SINT Rotate			( SINT* idecorateSetup );
	SINT ImageInvert	( SINT* idecorateSetup );
	SINT Sepia			( SINT* idecorateSetup );
	SINT Mosaic			( SINT* idecorateSetup );
	SINT Magnification	( SINT* idecorateSetup );
	SINT ColorConvert	( SINT* idecorateSetup );
	SINT Two_In_One_Ver	( SINT* idecorateSetup, SCHR* orizinalImagePath, SCHR* secondImagePath );
	SINT Two_In_One_Hor	( SINT* idecorateSetup, SCHR* orizinalImagePath, SCHR* secondImagePath );
	SINT Four_In_One	( SINT* idecorateSetup, SCHR* orizinalImagePath, SCHR* secondImagePath, SCHR* thirdImagePath, SCHR* fourthImagePath );
	SINT Overlay		( SINT* idecorateSetup, SCHR* secondImagePath );
	SINT Restart		( SINT* idecorateSetup );
	SINT Fin			( SINT* idecorateSetup );

};
/* ------------------------------------------------------------------------- */
/*              Copyright HAL Collage of Technology & Design                 */
/* ------------------------------------------------------------------------- */
