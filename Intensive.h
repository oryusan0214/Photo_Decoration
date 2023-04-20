#pragma once
/* ------------------------------------------------------------------------- */
/* Intensive.h																 */
/* �W��																		 */
/* �N���X��`�y�сA�֐��ȂǍŒ���̏��̂݋L��								 */
/* ------------------------------------------------------------------------- */
/* �ԍ�	�X�V����								���t		   ����			 */
/* ------------------------------------------------------------------------- */
/* 000000	�V�K�쐬							2021/10/24     �����@�C��	 */
/* 000001	���t�@�N�^�����O					2021/11/28	   ����  �C��	 */
/* ------------------------------------------------------------------------- */
/* Secure �錾																 */
/* ------------------------------------------------------------------------- */
#define  _CRT_NO_SECURE_WARNINGS
#define  _CRT_SECURE_NO_DEPRECATE

/* ------------------------------------------------------------------------- */
/* Define�錾																 */
/* ------------------------------------------------------------------------- */
#define ONE		1								/* 1�̈Ӗ�					 */
#define TWO		2								/* 2�̈Ӗ�					 */
#define THIRD	3								/* FIO�Ŏg�� 3�̈Ӗ�		 */
#define FOUR	4								/* FIO�Ŏg�� 4�̈Ӗ�		 */
#define GET_NUM	10								/* �`�ʈʒu��s�C�Ɏg���萔	 */
#define WHITE	255								/* ���̋P�x					 */

/* ------------------------------------------------------------------------- */
/* �\���̒�`																 */
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
/* Class��`																 */
/* ------------------------------------------------------------------------- */
class Intensive
{
public:
	SINT exe( DecorateList* decorateInfo, FileData* imageData, FileData* secondImageData, FileData* thirdImageData, FileData* fourthImageData );

private:
	SINT four_in_one( DecorateList* decorateInfo, FileData* imageData, FileData* secondImageData, FileData* thirdImageData, FileData* fourthImageData );
	SINT two_in_one_ver( DecorateList* decorateInfo, FileData* imageData, FileData* secondImageData );
	SINT two_in_one_hor( DecorateList* decorateInfo, FileData* imageData, FileData* secondImageData );

};
/* ------------------------------------------------------------------------- */
/*              Copyright HAL Collage of Technology & Design                 */
/* ------------------------------------------------------------------------- */
