#pragma once

//---
//画面設定
//---
const int Window_Width = 1920;							//画面横サイズ
const int Window_Height = 1080;							//画面縦サイズ
const int Color_Depth = 32;								//色の奥行


//---
//タイム系
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
//環境変数
//---
const int GRAVITY = 1;				//重力初期値
int gravity;						//重力

const int count_down_first = 100;
int countDown;						//ゲームカウントダウン用
int time;							//ゲームが始まったら時間を数える

//---
//マップ変数
//---
////座標
const int Second_Background_X = 1920;
int backgroundX;
int secondBackgroundX;
int backgroundY;
//const int Background1_Down = 200;		//背景１のY座標を下げる
////移動					
const int Background_FirstSpeed = 4;
int backgroundSpeed;
//int mapProceedXPrev;				//マップ進行時に画面左端になる部分の座標を記録
////マップ
bool rKeyFlag = 0;
bool mapChangeFlag = 0;										//マップ変更フラグ
bool scrollFlag;												//背景を進める用フラグ
////表示
int mapProceedX;					//マップを進めるよう変数
bool controllDontShowFlag = 0;			//タイトルで操作方法を示すか決める
int noActionCounter;				//無操作状態の時間をカウント
const int controllSaidTime = 10;	//無操作時間が5になったら表示に使う
int saidDark;						//表示濃ゆく


//---
//イベント
//---
bool gameStartFlag;
int gameStatus;											//ゲームの状態
enum { TITLE, INIT, OPEN, PLAY, CLEAR, OVER, END};					//ゲームの状態管理
int gameStage;
enum { first, second };									//ステージの状態管理