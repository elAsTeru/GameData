#pragma once

//---
//�֐��v���g�^�C�v�錾
//---
//�G�@�ړ����@�ƈړ�
void enemyMove(int& x, int& y, int& speedX, int& speedY, const int spownPosi, int& reverse);


//---
//�ϐ�
//---
const int enemy_num_max = 4;
bool enemyAliveFlag[enemy_num_max] = { 0 };
int enemySwitchFlag[enemy_num_max] = { 0,0,0,1 };	//�}�b�v�ύX���ɃL������ς��邩�����݂���̂�	//0 = �ǂ���ɂ�����̂ŕύX��//1 = 1�̃}�b�v�ɂ̂�//2 = 2�̃}�b�v�ɂ̂�
////�摜
const float Enemy_Width[enemy_num_max] = { 25 ,75, 32, 64 };
const int Enemy_Height[enemy_num_max] = { 40,68,40,182 };
const int enemy_reverse[enemy_num_max] = { 1,0,1,1 };
const int enemy_img_brankX[enemy_num_max] = { 25,64,16,-50 };
const int enemy_img_brankY[enemy_num_max] = { 10,-20,-10,-50 };
////���W
const int spownPosi[enemy_num_max] = { 0,1,2,3 };							//�N���ʒu
const int Enemy_FirstX[enemy_num_max] = { 1623, 2552, 3088, 4722 };
const int Enemy_FirstY[enemy_num_max] = { 784, 560, 795, 704 };
int enemyX[enemy_num_max];
int enemyY[enemy_num_max];
int enemyXPrev[enemy_num_max];
int enemyYPrev[enemy_num_max];
////�ړ�
const int Enemy_FirstSpeedX[enemy_num_max] = { -1,-3,-2,0 };


////�摜
const int enemy_kind = 4;
int enemyImg[enemy_kind];
int mand[6];
int slim[5];
int crow[4];
int nite[6];
////�ړ�
int enemySpeedX[enemy_num_max];
int enemySpeedY[enemy_num_max] = { 0 };
////�\��
int enemyReverse[enemy_num_max];










//typedef struct tag_Enemy
//{
//	int enemyFlag;			//�G���݃t���O
//	int enemySwitchFlag;	//�}�b�v�ύX���ɃL������ς��邩�����݂���̂�
//	int img;				//�摜����p
//	int x, y;				//���W
//	int w, h;				//�T�C�Y
//	int spownPosi;			//�N���ʒu
//	int speedX;				//���x
//	int howToMove;			//�ړ����@
//	int reverse;			//���]
//}Enemy;
//
//const int enemy_num_max = 4;
//Enemy enemy[enemy_num_max];
//
//const int enemyMap1or2[enemy_num_max] = {1,1,1,0};			//�}�b�v1�ɂ���̂�2�ɂ���̂����͗����ɂ���̂�������
//
//
////�֐��v���g�^�C�v�錾
//void initEnemy(Enemy* eDates, int num);
//void setEnemy(Enemy* eDates, int num);
//void moveEnemy(Enemy* eDates, int num);
//void loadEnemy(Enemy* eDates, int num);
//void drawEnemy(Enemy* eDates, int num);