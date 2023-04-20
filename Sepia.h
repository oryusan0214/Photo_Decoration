#pragma once
/* ------------------------------------------------------------------------- */
/* Sepia.h																	 */
/* �Z�s�A������																 */
/* �N���X��`�y�сA�֐��ȂǍŒ���̏��̂݋L��								 */
/* ------------------------------------------------------------------------- */
/* �ԍ�	�X�V����								���t		   ����			 */
/* 000000	�V�K�쐬							2021/10/15     �����@�C��	 */
/* 000001	���t�@�N�^�����O					2021/11/23	   ����  �C��	 */
/* ------------------------------------------------------------------------- */
/* Secure �錾																 */
/* ------------------------------------------------------------------------- */
#define  _CRT_NO_SECURE_WARNINGS
#define  _CRT_SECURE_NO_DEPRECATE

/* ------------------------------------------------------------------------- */
/* Define�錾																 */
/* ------------------------------------------------------------------------- */
#define DARK	1								/* �Â�						 */
#define NORMAL	2								/* �m�[�}��					 */
#define DELUTE	3								/* ���邢					 */

#define MAG_DA_B	72.5 / 765					/* �Â��Z�s�A�̐̔{��		 */
#define MAG_DA_G	100 / 765					/* �Â��Z�s�A�̗΂̔{��		 */
#define MAG_DA_R	120 / 765					/* �Â��Z�s�A�̐Ԃ̔{��		 */

#define MAG_NO_B	108.5 / 765					/* ���ʃZ�s�A�̐̔{��		 */
#define MAG_NO_G	150 / 765					/* ���ʃZ�s�A�̗΂̔{��		 */
#define MAG_NO_R	180 / 765					/* ���ʃZ�s�A�̐Ԃ̔{��		 */

#define MAG_DE_B	140 / 765					/* �W���Z�s�A�̐̔{��		 */
#define MAG_DE_G	200 / 765					/* �W���Z�s�A�̗΂̔{��		 */
#define MAG_DE_R	240 / 765					/* �W���Z�s�A�̐Ԃ̔{��		 */
/* ------------------------------------------------------------------------- */
/* �\���̒�`																 */
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
/* Class��`																 */
/* ------------------------------------------------------------------------- */
class Sepia
{
public:

	SINT exe( DecorateList* decorateInfo, FileData* imageData );

private:
	SINT dark( FileData* imageData );
	SINT normal( FileData* imageData );
	SINT delute( FileData* imageData );
};
/* ------------------------------------------------------------------------- */
/*              Copyright HAL Collage of Technology & Design                 */
/* ------------------------------------------------------------------------- */