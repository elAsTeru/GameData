#pragma once


//---
//���@�ϐ�
//---
bool playerFlag = FALSE;					//�v���C���[�Ǘ��t���O


////�摜
//�摜�T�C�Y
const int Player_Width = 32;
const int Player_Height = 48;
const int Img_BlankX = 16;					//�摜�󔒕���
const int Img_BlankY = 16;
//�摜�}��
int playerImg;								//���@��ԉ摜�}���p�ϐ�
int playerIdle[2];
int playerRun[8];
int playerJump[8];
int playerDamaged[2];
int ring[10];
int hpGaugeImg;								//�̗͘g�摜
int ConfusionImg;							//�������摜
//�摜����
int playerReverse;


////���W
const int Player_First_X = 100;
const int Player_First_Y = 784;
int playerX;
int playerY;
int playerXPrev, playerYPrev;				//��O�̍���


////�ړ�
//���ړ�
const int Player_StopPosition_X = 760;					//��ʈړ��ƌ��ʒu
const int Scroll_Stop_Position = 4600;
const int Player_EndPosition_X = 4960;					//�Q�[���I���ʒu
const int Player_FirstSpeed = 8;						//�������x
const int Player_LeftSpeed = -Player_FirstSpeed;		//���@���ړ����x
const int Player_RightSpeed = Player_FirstSpeed;		//���@�E�ړ����x
//�c�ړ�
const int JumpPower = 19;								//�W�����v��
const int MaxVy = 16;									//�ő�W�����v
bool jumpFlag;											//�W�����v�t���O
int playerYTemp;										//�W�����v�n�ߍ���
////�ړ�
int playerRightSpeed;
int playerLeftSpeed;
int playerSpeedY;


////�\��
int playerBackX;				//���@�`�掞�̈ʒu�߂��ϐ�
bool playerConfusionFlag;			//���@���������Ă��邩�ǂ���
bool playerInvincibleFlag;			//���@�����G��Ԃ��ǂ���


////�X�e�[�^�X
const int PlayerHP_First = 100;							//�̗͐ݒ�
int playerHP;											//�̗�


int canNotControllCount;								//����s�\���ԃJ�E���g�p


//�摜�Ǎ�