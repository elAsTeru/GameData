#pragma once

#include <DxLib.h>
#include "player.h"

#define COLLISION_CELL_WIDTH 32											//当たり判定BOXの幅
#define COLLISION_CELL_HEIGHT 32										//当たり判定BOXの高さ
#define COLLISION_CELL_NUM_X 180										//当たり判定BOXの横方向の数
#define COLLISION_CELL_NUM_Y 60											//当たり判定BOXの縦方向の数
#define COLLISION_WINDOW_X 1920											//ウィンドウの幅
#define COLLISION_WINDOW_Y 1080											//ウィンドウの高さ

int collisionBoxHandle[3];												//当たり判定BOX絵の総数を掛け算で出す
int collisionMarker;													//文字を格納する変数
int collisionRawNum = 0;												//横方向の当たり判定BOXナンバー
int collisionColumnNum = 0;												//縦方向の当たり判定BOXナンバー
int collisionNum;														//当たり判定BOXの番号
int ci;																	//for文カウンター
int cj;																	//for文カウンター
char collisionBuffer[10];												//文字列変数
bool collisionEofFlag = false;											//eof（end of file）検出フラグ

struct collisionCell														//当たり判定BOX用の構造体を作る
{
	int collisionBoxHandle;													//当たり判定管理用の変数
};

class Collision																	//背景当たり判定クラスを作る
{
public:

	collisionCell collisionCell[COLLISION_CELL_NUM_X][COLLISION_CELL_NUM_Y];	//構造体に当たり判定BOXの横縦を格納する

	//---
	//ファイル読み込み
	//---
	Collision()
	{
		LoadDivGraph("img/collision3.png", 3, 3, 1, 32, 32, collisionBoxHandle);//当たり判定チェック用画像
		FILE* collisionFilePointer;												//ファイルのポインタを宣言
		fopen_s(&collisionFilePointer, "csv/map_1st_collision.csv", "r");					//fopen_s関数でcollision.csvを読み取り形式で開く
		if (collisionFilePointer == NULL)										//collisionFilePointerが空の場合は
		{
			DebugBreak();														//デバッグ中止
		}


		memset(collisionBuffer, 0, sizeof(collisionBuffer));					//memset関数でメモリにbufferをセットし、sizeof演算子で要素数を決める

		while (1)
		{
			while (1)
			{
				collisionMarker = fgetc(collisionFilePointer);						//fgetc関数でfilepointerから文字を読んでcharacterPackに格納
				if (collisionMarker == EOF)
				{
					collisionEofFlag = true;									//EndOfFileを検出して
					break;														//ループを抜ける
				}
				if (collisionMarker != ',' && collisionMarker != '\n')			//区切りか改行でなければ
				{
					strcat_s(collisionBuffer, (const char*)&collisionMarker);	//strcat_s関数でbufferに連結し、const char関数で書き換える
				}
				else
				{
					collisionNum = atoi(collisionBuffer);						//atoi関数でbufferをint型に直して、ローカル変数numに代入
					collisionCell[collisionColumnNum][collisionRawNum].collisionBoxHandle = collisionBoxHandle[collisionNum];		//num番目のチップ画像のハンドルを取得
					memset(collisionBuffer, 0, sizeof(collisionBuffer));		//bufferをリセット
					break;														//区切りか改行なのでループを抜ける
				}
			}
			if (collisionEofFlag)												//1マップ分になったら
			{
				break;															//ループを抜ける
			}
			if (collisionMarker == ',')											//区切りを検出したら
			{
				collisionColumnNum++;											//列の数を増やす
			}
			if (collisionMarker == '\n')										//改行だったら
			{
				collisionRawNum++;												//行を増やす
				collisionColumnNum = 0;											//列を0にする
			}
		}
		fclose(collisionFilePointer);											//ファイルを閉じる
	}

	//---
	//当たり判定設置
	//---
	void ColBox()
	{
		const int playerW = Player_Width;
		const int playerH = Player_Height;

		int playerLX = playerX - Img_BlankX;			//左X
		int playerLOY = playerY - Img_BlankY;			//左上Y
		int playerLUY = playerY + playerH;				//左下Y
		int playerRX = playerX + playerW - Img_BlankX;	//右X
		int playerROY = playerY - Img_BlankY;			//右上Y 
		int playerRUY = playerY + playerH;				//右下Y

		int playerVX = playerX - playerXPrev;
		int playerVY = playerY - playerYPrev;

		int idLX = playerLX / COLLISION_CELL_WIDTH;		//左X添え字
		int idLOY = playerLOY / COLLISION_CELL_HEIGHT;	//左上Y添え字
		int idLUY = playerLUY / COLLISION_CELL_HEIGHT;	////左下添え字
		int idROY = playerROY / COLLISION_CELL_WIDTH;	////右上添え字
		int idRX = playerRX / COLLISION_CELL_WIDTH;		//右X添え字
		int idRUY = playerRUY / COLLISION_CELL_HEIGHT;	//右下Y添え字

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

		for (int iy = idLOY; iy < idRUY + 1; iy++)				//iyは繰り返しのiとy方向
		{
			for (int ix = idLX; ix < idRX + 1; ix++)
			{
				// そこはブロックか？	(ブロック下端貫通)	
				if (collisionCell[ix][iy].collisionBoxHandle == collisionBoxHandle[1])
				{
					//ブロック左上下、右上下座標
					blkLX = ix * COLLISION_CELL_WIDTH;
					blkLOY = iy * COLLISION_CELL_HEIGHT;
					blkLUY = iy * COLLISION_CELL_HEIGHT;
					blkROY = iy * COLLISION_CELL_HEIGHT;
					blkRX = blkLX + COLLISION_CELL_WIDTH;
					blkRUY = blkLOY + COLLISION_CELL_HEIGHT;

					//本当に当たっているか？
					if (((playerLX >= blkLX && playerLX <= blkRX) ||
						(blkLX >= playerLX && blkLX <= playerRX)) &&
						(playerLOY >= blkLOY && playerLOY <= playerRUY) ||
						(blkLOY >= playerLOY && blkLOY <= playerRUY))
					{
						// 衝突したのでめり込みを戻す（リアクション）
						//ブロックの上端とぶつかった
						if ((playerRUY - blkLOY > 0) &&
							(playerRUY - blkLOY <= 16) &&
							(collisionCell[ix][iy - 1].collisionBoxHandle == collisionBoxHandle[0]) &&
							(playerVY > 0))
						{
							playerY = blkLOY - playerH;
							playerYPrev = playerY;
							jumpFlag = false;
						}
						//ブロックの左端とぶつかった
						if ((playerRX - blkLX > 0) &&		//+であればめり込んでいる
							(playerRX - blkLX <= 16) &&
							(collisionCell[ix - 1][iy].collisionBoxHandle == collisionBoxHandle[0]) &&
							(playerVX > 0))
						{
							playerX = blkLX - playerW + Img_BlankX - 1;
							playerXPrev = playerX;
						}
						//ブロックの右端とぶつかった
						if ((blkRX - playerLX > 0) &&		//-であればめり込んでいる
							(blkRX - playerLX <= 16) &&	//ブロックとプレイヤーの指定位置の距離が16になったら
							(collisionCell[ix + 1][iy].collisionBoxHandle == collisionBoxHandle[0]) &&
							(-playerVX > 0))				//移動速度が1以上なら
						{
							playerX = blkRX + Img_BlankX;
							playerXPrev = playerX;
						}
					}
				}
				// そこはブロックか？	(ブロック全方向当たり)	
				if (collisionCell[ix][iy].collisionBoxHandle == collisionBoxHandle[2])			
				{
					//ブロック左上下、右下下座標
					blkLX = ix * COLLISION_CELL_WIDTH;
					blkLOY = iy * COLLISION_CELL_HEIGHT;
					blkLUY = iy * COLLISION_CELL_HEIGHT;
					blkROY = iy * COLLISION_CELL_HEIGHT;
					blkRX = blkLX + COLLISION_CELL_WIDTH;
					blkRUY = blkLOY + COLLISION_CELL_HEIGHT;

					//本当に当たっているか？
					if (((playerLX >= blkLX && playerLX <= blkRX) ||
						(blkLX >= playerLX && blkLX <= playerRX)) &&
						(playerLOY >= blkLOY && playerLOY <= playerRUY) ||
						(blkLOY >= playerLOY && blkLOY <= playerRUY))
					{
						// 衝突したのでめり込みを戻す（リアクション）
						//ブロックの上端とぶつかった
						if ((playerRUY - blkLOY > 0) &&
							(playerRUY - blkLOY <= 16) &&
							(collisionCell[ix][iy - 1].collisionBoxHandle == collisionBoxHandle[0]) &&
							(playerVY > 0))
						{
							playerY = blkLOY - playerH;
							playerYPrev = playerY;
							jumpFlag = false;
						}
						//ブロックの左端とぶつかった
						if ((playerRX - blkLX > 0) &&		//+であればめり込んでいる
							(playerRX - blkLX <= 16) &&
							(collisionCell[ix - 1][iy].collisionBoxHandle == collisionBoxHandle[0]) &&
							(playerVX > 0))
						{
							playerX = blkLX - playerW + Img_BlankX - 1;
							playerXPrev = playerX;
						}
						//ブロックの右端とぶつかった
						if ((blkRX - playerLX > 0) &&		//-であればめり込んでいる
							(blkRX - playerLX <= 16) &&	//ブロックとプレイヤーの指定位置の距離が16になったら
							(collisionCell[ix + 1][iy].collisionBoxHandle == collisionBoxHandle[0]) &&
							(-playerVX > 0))				//移動速度が1以上なら
						{
							playerX = blkRX + Img_BlankX;
							playerXPrev = playerX;
						}
						//ブロックの下端とぶつかった
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

		// 足元を調べる
		idRUY = (playerY + playerH) / COLLISION_CELL_HEIGHT;
		//ジャンプ中でないのに、両足とも空中にいないか？
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