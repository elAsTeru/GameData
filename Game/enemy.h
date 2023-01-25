#pragma once

//---
//関数プロトタイプ宣言
//---
//敵機移動方法と移動
void enemyMove(int& x, int& y, int& speedX, int& speedY, const int spownPosi, int& reverse);


//---
//変数
//---
const int enemy_num_max = 4;
bool enemyAliveFlag[enemy_num_max] = { 0 };
int enemySwitchFlag[enemy_num_max] = { 0,0,0,1 };	//マップ変更時にキャラを変えるか又存在するのか	//0 = どちらにもいるので変更可//1 = 1のマップにのみ//2 = 2のマップにのみ
////画像
const float Enemy_Width[enemy_num_max] = { 25 ,75, 32, 64 };
const int Enemy_Height[enemy_num_max] = { 40,68,40,182 };
const int enemy_reverse[enemy_num_max] = { 1,0,1,1 };
const int enemy_img_brankX[enemy_num_max] = { 25,64,16,-50 };
const int enemy_img_brankY[enemy_num_max] = { 10,-20,-10,-50 };
////座標
const int spownPosi[enemy_num_max] = { 0,1,2,3 };							//湧き位置
const int Enemy_FirstX[enemy_num_max] = { 1623, 2552, 3088, 4722 };
const int Enemy_FirstY[enemy_num_max] = { 784, 560, 795, 704 };
int enemyX[enemy_num_max];
int enemyY[enemy_num_max];
int enemyXPrev[enemy_num_max];
int enemyYPrev[enemy_num_max];
////移動
const int Enemy_FirstSpeedX[enemy_num_max] = { -1,-3,-2,0 };


////画像
const int enemy_kind = 4;
int enemyImg[enemy_kind];
int mand[6];
int slim[5];
int crow[4];
int nite[6];
////移動
int enemySpeedX[enemy_num_max];
int enemySpeedY[enemy_num_max] = { 0 };
////表示
int enemyReverse[enemy_num_max];










//typedef struct tag_Enemy
//{
//	int enemyFlag;			//敵存在フラグ
//	int enemySwitchFlag;	//マップ変更時にキャラを変えるか又存在するのか
//	int img;				//画像代入用
//	int x, y;				//座標
//	int w, h;				//サイズ
//	int spownPosi;			//湧き位置
//	int speedX;				//速度
//	int howToMove;			//移動方法
//	int reverse;			//反転
//}Enemy;
//
//const int enemy_num_max = 4;
//Enemy enemy[enemy_num_max];
//
//const int enemyMap1or2[enemy_num_max] = {1,1,1,0};			//マップ1にいるのか2にいるのか又は両方にいるのかを入れる
//
//
////関数プロトタイプ宣言
//void initEnemy(Enemy* eDates, int num);
//void setEnemy(Enemy* eDates, int num);
//void moveEnemy(Enemy* eDates, int num);
//void loadEnemy(Enemy* eDates, int num);
//void drawEnemy(Enemy* eDates, int num);