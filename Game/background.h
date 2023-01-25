#pragma once
#include <DxLib.h>

//2�ڈȍ~�p

int rawNum3 = 0;														//�������̃^�C���i���o�[
int columnNum3 = 0;														//�c�����̃^�C���i���o�[
bool eofFlag3 = false;													//eof�iend of file�j���o�t���O

struct Cell3																//�^�C���p�̍\���̂����
{
	int graphicHandle;													//�摜����p�̕ϐ�
};

class Map3																												//map�N���X�����
{
public:

	Cell3 cell[CELL_NUM_X][CELL_NUM_Y];																					//�\���̂Ƀ^�C���̉��c���i�[����

	Map3()
	{
		LoadDivGraph("img/fit.png", (MAPCHIP_IMG_WIDTH / CELL_WIDTH) * (MAPCHIP_IMG_HEIGHT / CELL_HEIGHT), MAPCHIP_IMG_WIDTH / CELL_WIDTH, MAPCHIP_IMG_HEIGHT / CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT, chipgraphicHandle);			//�^�C���摜��ǂݍ���
		FILE* filePointer;																								//�t�@�C���̃|�C���^��錾
		fopen_s(&filePointer, "csv/map_Background1.csv", "r");																	//fopen_s�֐���map.csv��ǂݎ��`���ŊJ��
		if (filePointer == NULL)																						//filePointer����̏ꍇ��
		{
			DebugBreak();																								//�f�o�b�O���~
		}

		memset(buffer, 0, sizeof(buffer));																				//memset�֐��Ń�������buffer���Z�b�g���Asizeof���Z�q�ŗv�f�������߂�

		while (1)
		{
			while (1)
			{
				characterPack = fgetc(filePointer);										//fgetc�֐���filepointer���當����ǂ��characterPack�Ɋi�[
				if (characterPack == EOF)
				{
					eofFlag3 = true;														//EndOfFile�����o����
					break;																//���[�v�𔲂���
				}
				if (characterPack != ',' && characterPack != '\n')						//��؂肩���s�łȂ����
				{
					strcat_s(buffer, (const char*)&characterPack);						//strcat_s�֐���buffer�ɘA�����Aconst char�֐��ŏ���������
				}
				else
				{
					num = atoi(buffer);													//atoi�֐���buffer��int�^�ɒ����āA���[�J���ϐ�num�ɑ��
					cell[columnNum3][rawNum3].graphicHandle = chipgraphicHandle[num];		//num�Ԗڂ̃`�b�v�摜�̃n���h�����擾
					memset(buffer, 0, sizeof(buffer));									//buffer�����Z�b�g
					break;																//��؂肩���s�Ȃ̂Ń��[�v�𔲂���
				}
			}
			if (eofFlag3)																//1�}�b�v���ɂȂ�����
			{
				break;																	//���[�v�𔲂���
			}
			if (characterPack == ',')													//��؂�����o������
			{
				columnNum3++;															//��̐��𑝂₷
			}
			if (characterPack == '\n')													//���s��������
			{
				rawNum3++;																//�s�𑝂₷
				columnNum3 = 0;															//���0�ɂ���
			}
		}
		fclose(filePointer);															//�t�@�C�������
	}

	void View3()
	{
		for (i = 0; i < CELL_NUM_X; i++)
		{
			for (j = 0; j < CELL_NUM_Y; j++)
			{
				if (playerX >= Player_StopPosition_X)
				{
					DrawExtendGraph(i * CELL_WIDTH - mapProceedX/*(playerX - Player_StopPosition_X)*/, j * CELL_HEIGHT, (i + 1) * CELL_WIDTH - mapProceedX/*(playerX - Player_StopPosition_X)*/, (j + 1) * CELL_HEIGHT, cell[i][j].graphicHandle, TRUE);
				}
				else
				{
					DrawExtendGraph(i * CELL_WIDTH, j * CELL_HEIGHT, (i + 1) * CELL_WIDTH, (j + 1) * CELL_HEIGHT, cell[i][j].graphicHandle, TRUE);
				}
			}
		}
	}

	void All3()
	{
		View3();
	}

};