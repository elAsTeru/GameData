#pragma once

#include <DxLib.h>
#include "player.h"

#define COLLISION_CELL_WIDTH 32											//�����蔻��BOX�̕�
#define COLLISION_CELL_HEIGHT 32										//�����蔻��BOX�̍���
#define COLLISION_CELL_NUM_X 180										//�����蔻��BOX�̉������̐�
#define COLLISION_CELL_NUM_Y 60											//�����蔻��BOX�̏c�����̐�
#define COLLISION_WINDOW_X 1920											//�E�B���h�E�̕�
#define COLLISION_WINDOW_Y 1080											//�E�B���h�E�̍���

int collisionBoxHandle[3];												//�����蔻��BOX�G�̑������|���Z�ŏo��
int collisionMarker;													//�������i�[����ϐ�
int collisionRawNum = 0;												//�������̓����蔻��BOX�i���o�[
int collisionColumnNum = 0;												//�c�����̓����蔻��BOX�i���o�[
int collisionNum;														//�����蔻��BOX�̔ԍ�
int ci;																	//for���J�E���^�[
int cj;																	//for���J�E���^�[
char collisionBuffer[10];												//������ϐ�
bool collisionEofFlag = false;											//eof�iend of file�j���o�t���O

struct collisionCell														//�����蔻��BOX�p�̍\���̂����
{
	int collisionBoxHandle;													//�����蔻��Ǘ��p�̕ϐ�
};

class Collision																	//�w�i�����蔻��N���X�����
{
public:

	collisionCell collisionCell[COLLISION_CELL_NUM_X][COLLISION_CELL_NUM_Y];	//�\���̂ɓ����蔻��BOX�̉��c���i�[����

	//---
	//�t�@�C���ǂݍ���
	//---
	Collision()
	{
		LoadDivGraph("img/collision3.png", 3, 3, 1, 32, 32, collisionBoxHandle);//�����蔻��`�F�b�N�p�摜
		FILE* collisionFilePointer;												//�t�@�C���̃|�C���^��錾
		fopen_s(&collisionFilePointer, "csv/map_1st_collision.csv", "r");					//fopen_s�֐���collision.csv��ǂݎ��`���ŊJ��
		if (collisionFilePointer == NULL)										//collisionFilePointer����̏ꍇ��
		{
			DebugBreak();														//�f�o�b�O���~
		}


		memset(collisionBuffer, 0, sizeof(collisionBuffer));					//memset�֐��Ń�������buffer���Z�b�g���Asizeof���Z�q�ŗv�f�������߂�

		while (1)
		{
			while (1)
			{
				collisionMarker = fgetc(collisionFilePointer);						//fgetc�֐���filepointer���當����ǂ��characterPack�Ɋi�[
				if (collisionMarker == EOF)
				{
					collisionEofFlag = true;									//EndOfFile�����o����
					break;														//���[�v�𔲂���
				}
				if (collisionMarker != ',' && collisionMarker != '\n')			//��؂肩���s�łȂ����
				{
					strcat_s(collisionBuffer, (const char*)&collisionMarker);	//strcat_s�֐���buffer�ɘA�����Aconst char�֐��ŏ���������
				}
				else
				{
					collisionNum = atoi(collisionBuffer);						//atoi�֐���buffer��int�^�ɒ����āA���[�J���ϐ�num�ɑ��
					collisionCell[collisionColumnNum][collisionRawNum].collisionBoxHandle = collisionBoxHandle[collisionNum];		//num�Ԗڂ̃`�b�v�摜�̃n���h�����擾
					memset(collisionBuffer, 0, sizeof(collisionBuffer));		//buffer�����Z�b�g
					break;														//��؂肩���s�Ȃ̂Ń��[�v�𔲂���
				}
			}
			if (collisionEofFlag)												//1�}�b�v���ɂȂ�����
			{
				break;															//���[�v�𔲂���
			}
			if (collisionMarker == ',')											//��؂�����o������
			{
				collisionColumnNum++;											//��̐��𑝂₷
			}
			if (collisionMarker == '\n')										//���s��������
			{
				collisionRawNum++;												//�s�𑝂₷
				collisionColumnNum = 0;											//���0�ɂ���
			}
		}
		fclose(collisionFilePointer);											//�t�@�C�������
	}

	//---
	//�����蔻��ݒu
	//---
	void ColBox()
	{
		const int playerW = Player_Width;
		const int playerH = Player_Height;

		int playerLX = playerX - Img_BlankX;			//��X
		int playerLOY = playerY - Img_BlankY;			//����Y
		int playerLUY = playerY + playerH;				//����Y
		int playerRX = playerX + playerW - Img_BlankX;	//�EX
		int playerROY = playerY - Img_BlankY;			//�E��Y 
		int playerRUY = playerY + playerH;				//�E��Y

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
				// �����̓u���b�N���H	(�u���b�N���[�ђ�)	
				if (collisionCell[ix][iy].collisionBoxHandle == collisionBoxHandle[1])
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
							(collisionCell[ix][iy - 1].collisionBoxHandle == collisionBoxHandle[0]) &&
							(playerVY > 0))
						{
							playerY = blkLOY - playerH;
							playerYPrev = playerY;
							jumpFlag = false;
						}
						//�u���b�N�̍��[�ƂԂ�����
						if ((playerRX - blkLX > 0) &&		//+�ł���΂߂荞��ł���
							(playerRX - blkLX <= 16) &&
							(collisionCell[ix - 1][iy].collisionBoxHandle == collisionBoxHandle[0]) &&
							(playerVX > 0))
						{
							playerX = blkLX - playerW + Img_BlankX - 1;
							playerXPrev = playerX;
						}
						//�u���b�N�̉E�[�ƂԂ�����
						if ((blkRX - playerLX > 0) &&		//-�ł���΂߂荞��ł���
							(blkRX - playerLX <= 16) &&	//�u���b�N�ƃv���C���[�̎w��ʒu�̋�����16�ɂȂ�����
							(collisionCell[ix + 1][iy].collisionBoxHandle == collisionBoxHandle[0]) &&
							(-playerVX > 0))				//�ړ����x��1�ȏ�Ȃ�
						{
							playerX = blkRX + Img_BlankX;
							playerXPrev = playerX;
						}
					}
				}
				// �����̓u���b�N���H	(�u���b�N�S����������)	
				if (collisionCell[ix][iy].collisionBoxHandle == collisionBoxHandle[2])			
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
							(collisionCell[ix][iy - 1].collisionBoxHandle == collisionBoxHandle[0]) &&
							(playerVY > 0))
						{
							playerY = blkLOY - playerH;
							playerYPrev = playerY;
							jumpFlag = false;
						}
						//�u���b�N�̍��[�ƂԂ�����
						if ((playerRX - blkLX > 0) &&		//+�ł���΂߂荞��ł���
							(playerRX - blkLX <= 16) &&
							(collisionCell[ix - 1][iy].collisionBoxHandle == collisionBoxHandle[0]) &&
							(playerVX > 0))
						{
							playerX = blkLX - playerW + Img_BlankX - 1;
							playerXPrev = playerX;
						}
						//�u���b�N�̉E�[�ƂԂ�����
						if ((blkRX - playerLX > 0) &&		//-�ł���΂߂荞��ł���
							(blkRX - playerLX <= 16) &&	//�u���b�N�ƃv���C���[�̎w��ʒu�̋�����16�ɂȂ�����
							(collisionCell[ix + 1][iy].collisionBoxHandle == collisionBoxHandle[0]) &&
							(-playerVX > 0))				//�ړ����x��1�ȏ�Ȃ�
						{
							playerX = blkRX + Img_BlankX;
							playerXPrev = playerX;
						}
						//�u���b�N�̉��[�ƂԂ�����
						if ((blkRUY - playerLOY > 0) &&
							(blkRUY - playerLOY <= 32) &&
							(collisionCell[ix][iy + 1].collisionBoxHandle == collisionBoxHandle[0]) &&
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
			(collisionCell[idLX][idRUY].collisionBoxHandle == collisionBoxHandle[0]) &&
			(collisionCell[idRX][idRUY].collisionBoxHandle == collisionBoxHandle[0]))
		{
			jumpFlag = true;
		}


	}
	void ColAll()
	{
		ColBox();
	}

};