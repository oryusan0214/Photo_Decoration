#pragma once
/* ------------------------------------------------------------------------- */
/* ColorInversion.h															 */
/* �F���]																	 */
/* �N���X��`�y�сA�֐��ȂǍŒ���̏��̂݋L��								 */
/* ------------------------------------------------------------------------- */
/* �ԍ�	�X�V����								���t		   ����			 */
/* 000000	�V�K�쐬							2021/10/23     �����@�C��	 */
/* 000001	���t�@�N�^�����O					2021/12/03	   ����  �C��	 */
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
#define COLORMAX 255								/* �P�x�̃}�b�N�X			 */

/* ------------------------------------------------------------------------- */
/* �\���̒�`																 */
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
/* Class��`																 */
/* ------------------------------------------------------------------------- */
class ColorInversion
{
public:
	SINT exe( DecorateList* decorateInfo, FileData* imageData );
};
/* ------------------------------------------------------------------------- */
/*              Copyright HAL Collage of Technology & Design                 */
/* ------------------------------------------------------------------------- */