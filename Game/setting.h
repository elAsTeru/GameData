#pragma once

//---
//��ʐݒ�
//---
const int Window_Width = 1920;							//��ʉ��T�C�Y
const int Window_Height = 1080;							//��ʏc�T�C�Y
const int Color_Depth = 32;								//�F�̉��s


//---
//�^�C���n
//---
int timeCounter;
int frameCounter;
int frameCounter2;
int frameCounter4;
int frameCounter5;
int frameCounter6;
int frameCounter7;
int frameCounter8;
int frameCounter10;
int frameCounter10Fast;


//---
//���ϐ�
//---
const int GRAVITY = 1;				//�d�͏����l
int gravity;						//�d��

const int count_down_first = 100;
int countDown;						//�Q�[���J�E���g�_�E���p
int time;							//�Q�[�����n�܂����玞�Ԃ𐔂���

//---
//�}�b�v�ϐ�
//---
////���W
const int Second_Background_X = 1920;
int backgroundX;
int secondBackgroundX;
int backgroundY;
//const int Background1_Down = 200;		//�w�i�P��Y���W��������
////�ړ�					
const int Background_FirstSpeed = 4;
int backgroundSpeed;
//int mapProceedXPrev;				//�}�b�v�i�s���ɉ�ʍ��[�ɂȂ镔���̍��W���L�^
////�}�b�v
bool rKeyFlag = 0;
bool mapChangeFlag = 0;										//�}�b�v�ύX�t���O
bool scrollFlag;												//�w�i��i�߂�p�t���O
////�\��
int mapProceedX;					//�}�b�v��i�߂�悤�ϐ�
bool controllDontShowFlag = 0;			//�^�C�g���ő�����@�����������߂�
int noActionCounter;				//�������Ԃ̎��Ԃ��J�E���g
const int controllSaidTime = 10;	//�����쎞�Ԃ�5�ɂȂ�����\���Ɏg��
int saidDark;						//�\���Z�䂭


//---
//�C�x���g
//---
bool gameStartFlag;
int gameStatus;											//�Q�[���̏��
enum { TITLE, INIT, OPEN, PLAY, CLEAR, OVER, END};					//�Q�[���̏�ԊǗ�
int gameStage;
enum { first, second };									//�X�e�[�W�̏�ԊǗ�