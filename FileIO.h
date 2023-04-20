/* --------------------------------------------------------------------- */
/* �t�@�C����	:	FileIO.h											 */
/* �@�\�T�v		:														 */
/* �쐬��		:   2021/10/21											 */
/* �ŏI�X�V��	:   2021/11/03											 */
/* �쐬��		:	�R�c���V��											 */
/* --------------------------------------------------------------------- */
#pragma once

/* --------------------------------------------------------------------- */
/* include�t�@�C��														 */
/* --------------------------------------------------------------------- */
#include"System.h"

/* --------------------------------------------------------------------- */
/* �萔��`																 */
/* --------------------------------------------------------------------- */

//Path�̍ő�̒���
#define PathLength 200

//bit�̒�`
#define Bit32 0x0020 
#define Bit24 0x0018
#define Bit8 0x0008
#define Bit1 0x0001

//

//�߂�l
#define FAILE -1
#define SUCCESS 0

//�f�o�b�O�p
#define TEST

/* --------------------------------------------------------------------- */
/* �N���X��`                                                            */
/* --------------------------------------------------------------------- */
class FileIO
{
public:
	FileIO( );
	 ~FileIO( );

	 FILE* orizinalPath;							/* 1���ڂ�Path				 */
	 FILE* secondPath;							/* 2���ڂ�Path				 */
	 FILE* thirdPath;							/* 3���ڂ�Path				 */
	 FILE* fourthPath;							/* 4���ڂ�Path				 */
	 FILE* outputPath;							/* �o�͂�Path				 */


	SINT read( SCHR* , FileData** );
	SINT write( SCHR*, FileData** );
private:
	FILE *pFP;
	struct stat stat_buff ;
	SINT iIdetify;
	SINT open( SCHR* ,SCHR*);
	SINT read(  FileData** );
	SINT write( FileData** );
	void close(  );
};




