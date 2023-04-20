#pragma once
/* ------------------------------------------------------------------------- */
/* System.h																	 */
/* �V�X�e���w�b�_															 */
/* ------------------------------------------------------------------------- */
/* �ԍ�	�X�V����								���t		   ����			 */
/* ------------------------------------------------------------------------- */
/* 000000	�V�K�쐬							2021/10/15     �����@�C��	 */
/* 000001	���t�@�N�^�����O					2021/11/22	   ����  �C��	 */
/* ------------------------------------------------------------------------- */
/* Secure�錾																 */
/* ------------------------------------------------------------------------- */
#define  _CRT_NO_SECURE_WARNINGS
#define  _CRT_SECURE_NO_DEPRECATE

/* ------------------------------------------------------------------------- */
/* Include																	 */
/* ------------------------------------------------------------------------- */
#include <stdio.h>								/* �W���h�n					 */
#include <stdlib.h>								/* �W�����C�u����			 */
#include <string.h>								/* �����񐧌�				 */
#include <Windows.h>							/* Windows�֘A				 */
#include <time.h>								/* �^�C�}�[��N���b�N�֐�	 */
#include <sys/stat.h>							/* �t�@�C���I�[�v��			 */
#include <stdarg.h>								/* �ό����Ŏg��			 */
#include <direct.h>								/* File����r�Ŏg��			 */


/* ------------------------------------------------------------------------- */
/* ����typedef�錾															 */
/* ------------------------------------------------------------------------- */
typedef char			SCHR;					/*	char�^					 */
typedef unsigned char	UCHR;					/*	unsigned char�^			 */
typedef short			SSHT;					/*	short�^					 */
typedef unsigned short	USHT;					/*	unsigned short�^		 */
typedef long			SLNG;					/*	long�^					 */
typedef unsigned long	ULNG;					/*	unsigned long�^			 */
typedef int				SINT;					/*	int�^					 */
typedef unsigned int	UINT;					/*	unsigned int�^			 */
typedef	float			FLOT;					/*	float�^					 */
typedef	double			DBLE;					/*	double�^				 */

/* ------------------------------------------------------------------------- */
/* ����define�錾															 */
/* ------------------------------------------------------------------------- */
#define FAILE						-1				/* �ُ펞�̖߂�l		 */
#define SUCCESS						0				/* ����l�̖߂�l		 */
#define STR_OK						0				/* srtcmp�̐��펞�̖߂�l*/
#define SCANF_ERROR					0				/* scanf�̃G���[�`�F�b�N */
#define BIT1						0x0001			/* Bit��`				 */
#define BIT8						0x0008			/* Bit��`				 */
#define BIT24						0x0018			/* Bit��`				 */
#define BIT32						0x0020			/* Bit��`				 */
#define PATHLENGTH					200				/* Path�̍ő咷			 */
#define MAGIC_NUMBER				0x4D42			/* BM�̕����R�[�h		 */
#define ONCE						1				/* �֐��̈�����1���g���� */
#define PNG							10				/* png�̔���n			 */
#define JPEG						20				/* jpeg�̔���n			 */

#define BYTE1						1				/* �f�[�^�̓Ǎ��T�C�Y	 */
#define BYTE2						2				/* �f�[�^�̓Ǎ��T�C�Y	 */
#define BYTE3						3				/* �f�[�^�̓Ǎ��T�C�Y	 */
#define BYTE4						4				/* �f�[�^�̓Ǎ��T�C�Y	 */
#define HEADER_SIZE					14				/* HeaderFile�̃T�C�Y	 */
#define INFO_SIZE					40				/* InfoFile�̑傫��		 */

#define INTI						0				/* �����l				 */
#define IMAGE_SIZE_MIN				1				/* �摜�f�[�^�̍Œ�̒���*/


#define ROTATE						1				/* ��]��ID				 */
#define IMAGEINVERT					2				/* �摜���]��ID			 */
#define COLORINVERT					3				/* �F���]��ID			 */
#define SEPIA						4				/* �Z�s�A��ID			 */
#define MOSAIC						5				/* ���U�C�N��ID			 */
#define MAGNIFICATION				6				/* �g��k��ID			 */
#define COLORCONVERT				7				/* �F�ϊ���ID			 */
#define COPY						8				/* ���ʂ�ID				 */
#define TWO_IN_ONE_VER				9				/* �c�W���ID			 */
#define TWO_IN_ONE_HOR				10				/* ���W���ID			 */
#define FOUR_IN_ONE					11				/* 4 in 1��ID			 */
#define OVERLAY						12				/* �I�[�o�[���C��ID		 */
#define RESTART						13				/* �ē��͂�ID			 */
#define FIN							14				/* �I����ID				 */

#define EMPTY						0				/* �ݒ�l 0				 */
#define ROTATE_MIN					1				/* �摜��]�̐ݒ�l�̍Œ�*/
#define ROTATE_MAX					4				/* �摜��]�̐ݒ�l�̍ő�*/
#define IMAGE_INVERT_MIN			1				/* �摜���]�̐ݒ�l�̍Œ�*/
#define IMAGE_INVERT_MAX			2				/* �摜���]�̐ݒ�l�̍ő�*/
#define SEPIA_MIN					1				/* �Z�s�A���̐ݒ�l�̍Œ�*/
#define SEPIA_MAX					3				/* �Z�s�A���̐ݒ�l�̍ő�*/
#define MOSAIC_MIN					1				/* ���U�C�N�̐ݒ�l�̍Œ�*/
#define MAGN_MIN					1				/* �{���ύX�̐ݒ�l�̍Œ�*/
#define MAGN_MAX					10000			/* �{���ύX�̐ݒ�l�̍ő�*/
#define COLOR_CONVERT_MIN			1				/* �F�ϊ��̐ݒ�l�̍Œ�	 */
#define COLOR_CONVERT_MAX			3				/* �F�ϊ��̐ݒ�l�̍ő�	 */
#define INTENSIVE_T_MIN				12				/* 2 in 1�̐ݒ�l�̍ŏ�	 */
#define INTENSIVE_T_MAX				21				/* 2 in 1�̐ݒ�l�̍ő�	 */
#define INTENSIVE_F_MIN				1234			/* 4 in 1�̐ݒ�l�̍ŏ�	 */
#define INTENSIVE_F_MAX				4321			/* 4 in 1�̐ݒ�l�̍ő�	 */
#define OVERLAY_MIN					0				/* �I�o���C�̐ݒ�l�̍ŏ�*/
#define OVERLAY_MAX					99				/* �I�o���C�̐ݒ�l�̍ő�*/

/* ------------------------------------------------------------------------- */
/* ���ʍ\���̐錾															 */
/* ------------------------------------------------------------------------- */

/* �t�@�C���w�b�_ */
#pragma pack( 2 )
typedef struct FileHeader {
	SSHT sFile_Header_Name;						/* �^��						 */
	UINT uiFaile_Saize;							/* FileSize(���Ăɂł��Ȃ�)	 */
	SSHT sReserved1;							/* �\��̈�1				 */
	SSHT sReserved2;							/* �\��̈�2				 */
	UINT uiHeader_Size_Offset;					/* �F�f�[�^�܂ł�Offset		 */
}FileHeader;

/* ���w�b�_ */
#pragma pack(  )
typedef struct InformationHeader {
	UINT uiInfo_HeaderSize;						/* ���w�b�_�̃T�C�Y		 */
	UINT uiWidth;								/* �摜�̉���				 */
	UINT uiHeight;								/* �摜�̏c��				 */
	SSHT sPlain;								/* �v���[����				 */
	SSHT sColor_Bit;							/* �r�b�g�}�b�v�̐F��		 */
	UINT uiCompre;								/* ���k���					 */
	UINT uiImage_Size;							/* �摜�̑S�̃T�C�Y			 */
	UINT uiResolution_Wid;						/* �摜�̏c�𑜓x			 */
	UINT uiResolution_Hei;						/* �摜�̉��𑜓x			 */
	UINT uiColor_Index;							/* �p���b�g��				 */
	UINT uiColor_Key_Index;						/* �d�v�ȃp���b�g��			 */
}InformationHeader;

/* �t�@�C���f�[�^ */
typedef struct FileData {
	FileHeader*			pFileHData;				/* �t�@�C���w�b�_			 */
	InformationHeader*	pInfoHData;				/* ���w�b�_				 */
	UCHR*				pImageData;				/* �F�f�[�^					 */
}FileData;

/* �������̔z�� */
struct DecorateList {
	DecorateList*		next;					/* ���̃|�C���^				 */
	SINT				decolateKind;			/* �������					 */
	SINT				decolatesetup;			/* �����ݒ�					 */
};

/* 1�s�N�Z��������̐F��� */
struct rgb {
	UCHR r;										/* ��						 */
	UCHR g;										/* ��						 */
	UCHR b;										/* ��						 */
	UCHR a;										/* ��						 */
};

/* ------------------------------------------------------------------------- */
/*              Copyright HAL Collage of Technology & Design                 */
/* ------------------------------------------------------------------------- */
