#pragma once


//---
//自機変数
//---
bool playerFlag = FALSE;					//プレイヤー管理フラグ


////画像
//画像サイズ
const int Player_Width = 32;
const int Player_Height = 48;
const int Img_BlankX = 16;					//画像空白部分
const int Img_BlankY = 16;
//画像挿入
int playerImg;								//自機状態画像挿入用変数
int playerIdle[2];
int playerRun[8];
int playerJump[8];
int playerDamaged[2];
int ring[10];
int hpGaugeImg;								//体力枠画像
int ConfusionImg;							//混乱時画像
//画像向き
int playerReverse;


////座標
const int Player_First_X = 100;
const int Player_First_Y = 784;
int playerX;
int playerY;
int playerXPrev, playerYPrev;				//一つ前の高さ


////移動
//横移動
const int Player_StopPosition_X = 760;					//画面移動と交代位置
const int Scroll_Stop_Position = 4600;
const int Player_EndPosition_X = 4960;					//ゲーム終了位置
const int Player_FirstSpeed = 8;						//初期速度
const int Player_LeftSpeed = -Player_FirstSpeed;		//自機左移動速度
const int Player_RightSpeed = Player_FirstSpeed;		//自機右移動速度
//縦移動
const int JumpPower = 19;								//ジャンプ力
const int MaxVy = 16;									//最大ジャンプ
bool jumpFlag;											//ジャンプフラグ
int playerYTemp;										//ジャンプ始め高さ
////移動
int playerRightSpeed;
int playerLeftSpeed;
int playerSpeedY;


////表示
int playerBackX;				//自機描画時の位置戻し変数
bool playerConfusionFlag;			//自機が混乱しているかどうか
bool playerInvincibleFlag;			//自機が無敵状態かどうか


////ステータス
const int PlayerHP_First = 100;							//体力設定
int playerHP;											//体力


int canNotControllCount;								//操作不可能時間カウント用


//画像読込