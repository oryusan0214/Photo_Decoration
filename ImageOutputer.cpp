/* -------------------------------------------------------------------- */
/* �t�@�C����	:	ImageOutputer.cpp									*/
/* �@�\�T�v		:	�w�肳�ꂽ�t�H�[�}�b�g�ɕϊ��������ď�������		*/
/* �쐬��		:   2021/11/03											*/
/* �ŏI�X�V��	:   2021/11/04											*/
/* �쐬��		:	�R�c���V��											*/
/* -------------------------------------------------------------------- */
#include "ImageOutputer.h"

/* ------------------------------------------------------------------------- */
/* �֐���	: ImageOutputer::ImageOutputer									 */
/* �@�\��	: �R���X�g���N�^												 */
/* �@�\�T�v	: �f�[�^��������												 */
/* ����		: �Ȃ�															 */
/* �߂�l	: void															 */
/* �쐬��	: 2021/10/25		����  �C��		�V�K�쐬					 */
/* ------------------------------------------------------------------------- */
ImageOutputer::ImageOutputer( void )
{
	/* ������ & DM Get */
	bmpOutPath = NULL;
	bmpOutPath = ( SCHR* )calloc( PATHLENGTH, sizeof( SCHR ) );
}

/* ------------------------------------------------------------------------- */
/* �֐���	: ImageOutputer::~ImageOutputer									 */
/* �@�\��	: �f�X�g���N�^													 */
/* �@�\�T�v	: �f�[�^�����													 */
/* ����		: �Ȃ�															 */
/* �߂�l	: void															 */
/* �쐬��	: 2021/10/25		����  �C��		�V�K�쐬					 */
/* ------------------------------------------------------------------------- */

ImageOutputer::~ImageOutputer( void )
{
	
	/* ��� */
	if ( *bmpOutPath != NULL ) {
		free( bmpOutPath );
	}
}

/* -------------------------------------------------------------------- */
/* ������ public ������												    */
/* -------------------------------------------------------------------- */
/* �֐���	:	exe														*/
/* �@�\��	:	�t�@�C���ǂݍ��݋@�\									*/
/* ����		:	:FileData		pFileData 		�i�[��̃t�@�C���p�X	*/
/*  			:UCHR			pFilePath		�i�[��̃t�@�C���f�[�^	*/
/* �߂�l	:	:FileData	NULL			���s						*/
/*							SUCCESS			����						*/
/* �쐬��	:	2021/11/03		�R�c�@���V��							*/
/* -------------------------------------------------------------------- */
SINT ImageOutputer::exe(FileData* pFileData,SCHR* pFilePath ) {

	return SUCCESS;
}