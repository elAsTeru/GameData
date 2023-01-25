#pragma once

#include <DxLib.h>
#include "player.h"

int collisionBoxHandle2[3];												//�����蔻��BOX�G�̑������|���Z�ŏo��
int collisionMarker2;													//�������i�[����ϐ�
int collisionRawNum2 = 0;												//�������̓����蔻��BOX�i���o�[
int collisionColumnNum2 = 0;												//�c�����̓����蔻��BOX�i���o�[
int collisionNum2;														//�����蔻��BOX�̔ԍ�
int ci2;																	//for���J�E���^�[
int cj2;																	//for���J�E���^�[
char collisionBuffer2[10];												//������ϐ�
bool collisionEofFlag2 = false;											//eof�iend of file�j���o�t���O

struct collisionCell2														//�����蔻��BOX�p�̍\���̂����
{
	int collisionBoxHandle2;													//�����蔻��Ǘ��p�̕ϐ�
};

class Collision2																	//�w�i�����蔻��N���X�����
{
public:

	collisionCell2 collisionCell2[COLLISION_CELL_NUM_X][COLLISION_CELL_NUM_Y];	//�\���̂ɓ����蔻��BOX�̉��c���i�[����

	//---
	//�t�@�C���ǂݍ���
	//---
	Collision2()
	{
		LoadDivGraph("img/collision3.png", 3, 3, 1, 32, 32, collisionBoxHandle2);//�����蔻��`�F�b�N�p�摜
		FILE* collisionFilePointer;												//�t�@�C���̃|�C���^��錾
		fopen_s(&collisionFilePointer, "csv/map_2nd_collision.csv", "r");					//fopen_s�֐���collision.csv��ǂݎ��`���ŊJ��
		if (collisionFilePointer == NULL)										//collisionFilePointer����̏ꍇ��
		{
			DebugBreak();														//�f�o�b�O���~
		}


		memset(collisionBuffer2, 0, sizeof(collisionBuffer2));					//memset�֐��Ń�������buffer���Z�b�g���Asizeof���Z�q�ŗv�f�������߂�

		while (1)
		{
			while (1)
			{
				collisionMarker2 = fgetc(collisionFilePointer);						//fgetc�֐���filepointer���當����ǂ��characterPack�Ɋi�[
				if (collisionMarker2 == EOF)
				{
					collisionEofFlag2 = true;									//EndOfFile�����o����
					break;														//���[�v�𔲂���
				}
				if (collisionMarker2 != ',' && collisionMarker2 != '\n')			//��؂肩���s�łȂ����
				{
					strcat_s(collisionBuffer2, (const char*)&collisionMarker2);	//strcat_s�֐���buffer�ɘA�����Aconst char�֐��ŏ���������
				}
				else
				{
					collisionNum2 = atoi(collisionBuffer2);						//atoi�֐���buffer��int�^�ɒ����āA���[�J���ϐ�num�ɑ��
					collisionCell2[collisionColumnNum2][collisionRawNum2].collisionBoxHandle2 = collisionBoxHandle2[collisionNum2];		//num�Ԗڂ̃`�b�v�摜�̃n���h�����擾
					memset(collisionBuffer2, 0, sizeof(collisionBuffer2));		//buffer�����Z�b�g
					break;														//��؂肩���s�Ȃ̂Ń��[�v�𔲂���
				}
			}
			if (collisionEofFlag2)												//1�}�b�v���ɂȂ�����
			{
				break;															//���[�v�𔲂���
			}
			if (collisionMarker2 == ',')											//��؂�����o������
			{
				collisionColumnNum2++;											//��̐��𑝂₷
			}
			if (collisionMarker2 == '\n')										//���s��������
			{
				collisionRawNum2++;												//�s�𑝂₷
				collisionColumnNum2 = 0;											//���0�ɂ���
			}
		}
		fclose(collisionFilePointer);											//�t�@�C�������
	}

	//---
	//�����蔻��ݒu
	//---
	void ColBox2()
	{
		const int playerW = Player_Width;
		const int playerH = Player_Height;

		int playerLX = playerX - Img_BlankX;				//��X
		int playerLOY = playerY - Img_BlankY;				//����Y
		int playerLUY = playerY + playerH;					//����Y
		int playerRX = playerX + playerW - Img_BlankX;		//�EX
		int playerROY = playerY - Img_BlankY;				//�E��Y 
		int playerRUY = playerY + playerH;					//�E��Y

		int playerVX = playerX - playerXPrev;
		int playerVY = playerY - playerYPrev;

		int idLX = playerLX / COLLISION_CELL_WIDTH;		//��X�Y����
		int idLOY = playerLOY / COLLISION_CELL_HEIGHT;	//����Y�Y����
		int idLUY = playerLUY / COLLISION_CELL_HEIGHT;	////�����Y����
		int idROY = playerROY / COLLISION_CELL_WIDTH;	////�E��Y����
		int idRX = playerRX / COLLISION_CELL_WIDTH;		//�EX�Y����
		int idRUY = playerRUY / COLLISION_CELL_HEIGHT;	//�E��Y�Y����

		int blkLX;
		int blkLOY;
		int blkLUY;
		int blkROY;
		int blkRX;
		int blkRUY;

		if (idLOY < 0 || idRUY < 0)
		{
			return;
		}

		for (int iy = idLOY; iy < idRUY + 1; iy++)				//iy�͌J��Ԃ���i��y����
		{
			for (int ix = idLX; ix < idRX + 1; ix++)
			{
				// �����̓u���b�N���H
				if (collisionCell2[ix][iy].collisionBoxHandle2 == collisionBoxHandle2[1])
				{
					//�u���b�N���㉺�A�E�㉺���W
					blkLX = ix * COLLISION_CELL_WIDTH;
					blkLOY = iy * COLLISION_CELL_HEIGHT;
					blkLUY = iy * COLLISION_CELL_HEIGHT;
					blkROY = iy * COLLISION_CELL_HEIGHT;
					blkRX = blkLX + COLLISION_CELL_WIDTH;
					blkRUY = blkLOY + COLLISION_CELL_HEIGHT;

					//�{���ɓ������Ă��邩�H
					if (((playerLX >= blkLX && playerLX <= blkRX) ||
						(blkLX >= playerLX && blkLX <= playerRX)) &&
						(playerLOY >= blkLOY && playerLOY <= playerRUY) ||
						(blkLOY >= playerLOY && blkLOY <= playerRUY))
					{
						// �Փ˂����̂ł߂荞�݂�߂��i���A�N�V�����j
						//�u���b�N�̏�[�ƂԂ�����
						if ((playerRUY - blkLOY > 0) &&
							(playerRUY - blkLOY <= 16) &&
							(collisionCell2[ix][iy - 1].collisionBoxHandle2 == collisionBoxHandle2[0]) &&
							(playerVY > 0))
						{
							playerY = blkLOY - playerH;
							playerYPrev = playerY;
							jumpFlag = false;
						}
						//�u���b�N�̍��[�ƂԂ�����
						if ((playerRX - blkLX > 0) &&		//+�ł���΂߂荞��ł���
							(playerRX - blkLX <= 16) &&
							(collisionCell2[ix - 1][iy].collisionBoxHandle2 == collisionBoxHandle2[0]) &&
							(playerVX > 0))
						{
							playerX = blkLX - playerW + Img_BlankX - 1;
							playerXPrev = playerX;
						}
						//�u���b�N�̉E�[�ƂԂ�����
						if ((blkRX - playerLX > 0) &&		//-�ł���΂߂荞��ł���
							(blkRX - playerLX <= 16) &&	//�u���b�N�ƃv���C���[�̎w��ʒu�̋�����16�ɂȂ�����
							(collisionCell2[ix + 1][iy].collisionBoxHandle2 == collisionBoxHandle2[0]) &&
							(-playerVX > 0))
						{
							playerX = blkRX + Img_BlankX;
							playerXPrev = playerX;
						}
					}
				}
				// �����̓u���b�N���H	(�u���b�N�S����������)	
				if (collisionCell2[ix][iy].collisionBoxHandle2 == collisionBoxHandle2[2])
				{
					//�u���b�N���㉺�A�E�������W
					blkLX = ix * COLLISION_CELL_WIDTH;
					blkLOY = iy * COLLISION_CELL_HEIGHT;
					blkLUY = iy * COLLISION_CELL_HEIGHT;
					blkROY = iy * COLLISION_CELL_HEIGHT;
					blkRX = blkLX + COLLISION_CELL_WIDTH;
					blkRUY = blkLOY + COLLISION_CELL_HEIGHT;

					//�{���ɓ������Ă��邩�H
					if (((playerLX >= blkLX && playerLX <= blkRX) ||
						(blkLX >= playerLX && blkLX <= playerRX)) &&
						(playerLOY >= blkLOY && playerLOY <= playerRUY) ||
						(blkLOY >= playerLOY && blkLOY <= playerRUY))
					{
						// �Փ˂����̂ł߂荞�݂�߂��i���A�N�V�����j
						//�u���b�N�̏�[�ƂԂ�����
						if ((playerRUY - blkLOY > 0) &&
							(playerRUY - blkLOY <= 16) &&
							(collisionCell2[ix][iy - 1].collisionBoxHandle2 == collisionBoxHandle2[0]) &&
							(playerVY > 0))
						{
							playerY = blkLOY - playerH;
							playerYPrev = playerY;
							jumpFlag = false;
						}
						//�u���b�N�̍��[�ƂԂ�����
						if ((playerRX - blkLX > 0) &&		//+�ł���΂߂荞��ł���
							(playerRX - blkLX <= 16) &&
							(collisionCell2[ix - 1][iy].collisionBoxHandle2 == collisionBoxHandle2[0]) &&
							(playerVX > 0))
						{
							playerX = blkLX - playerW + Img_BlankX - 1;
							playerXPrev = playerX;
						}
						//�u���b�N�̉E�[�ƂԂ�����
						if ((blkRX - playerLX > 0) &&		//-�ł���΂߂荞��ł���
							(blkRX - playerLX <= 16) &&	//�u���b�N�ƃv���C���[�̎w��ʒu�̋�����16�ɂȂ�����
							(collisionCell2[ix + 1][iy].collisionBoxHandle2 == collisionBoxHandle2[0]) &&
							(-playerVX > 0))				//�ړ����x��1�ȏ�Ȃ�
						{
							playerX = blkRX + Img_BlankX;
							playerXPrev = playerX;
						}
						//�u���b�N�̉��[�ƂԂ�����
						if ((blkRUY - playerLOY > 0) &&
							(blkRUY - playerLOY <= 32) &&
							(collisionCell2[ix][iy + 1].collisionBoxHandle2 == collisionBoxHandle2[0]) &&
							(-playerVY > 0))
						{
							playerY = blkLUY + 64;
							playerYPrev = playerY;
						}
					}
				}
			}
		}

		// �����𒲂ׂ�
		idRUY = (playerY + playerH) / COLLISION_CELL_HEIGHT;
		//�W�����v���łȂ��̂ɁA�����Ƃ��󒆂ɂ��Ȃ����H
		if (!jumpFlag &&
			(collisionCell2[idLX][idRUY].collisionBoxHandle2 == collisionBoxHandle2[0]) &&
			(collisionCell2[idRX][idRUY].collisionBoxHandle2 == collisionBoxHandle2[0]))
		{
			jumpFlag = true;
		}


	}
	void ColAll2()
	{
		ColBox2();
	}

};