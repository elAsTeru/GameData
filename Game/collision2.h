#pragma once

#include <DxLib.h>
#include "player.h"

int collisionBoxHandle2[3];												//当たり判定BOX絵の総数を掛け算で出す
int collisionMarker2;													//文字を格納する変数
int collisionRawNum2 = 0;												//横方向の当たり判定BOXナンバー
int collisionColumnNum2 = 0;												//縦方向の当たり判定BOXナンバー
int collisionNum2;														//当たり判定BOXの番号
int ci2;																	//for文カウンター
int cj2;																	//for文カウンター
char collisionBuffer2[10];												//文字列変数
bool collisionEofFlag2 = false;											//eof（end of file）検出フラグ

struct collisionCell2														//当たり判定BOX用の構造体を作る
{
	int collisionBoxHandle2;													//当たり判定管理用の変数
};

class Collision2																	//背景当たり判定クラスを作る
{
public:

	collisionCell2 collisionCell2[COLLISION_CELL_NUM_X][COLLISION_CELL_NUM_Y];	//構造体に当たり判定BOXの横縦を格納する

	//---
	//ファイル読み込み
	//---
	Collision2()
	{
		LoadDivGraph("img/collision3.png", 3, 3, 1, 32, 32, collisionBoxHandle2);//当たり判定チェック用画像
		FILE* collisionFilePointer;												//ファイルのポインタを宣言
		fopen_s(&collisionFilePointer, "csv/map_2nd_collision.csv", "r");					//fopen_s関数でcollision.csvを読み取り形式で開く
		if (collisionFilePointer == NULL)										//collisionFilePointerが空の場合は
		{
			DebugBreak();														//デバッグ中止
		}


		memset(collisionBuffer2, 0, sizeof(collisionBuffer2));					//memset関数でメモリにbufferをセットし、sizeof演算子で要素数を決める

		while (1)
		{
			while (1)
			{
				collisionMarker2 = fgetc(collisionFilePointer);						//fgetc関数でfilepointerから文字を読んでcharacterPackに格納
				if (collisionMarker2 == EOF)
				{
					collisionEofFlag2 = true;									//EndOfFileを検出して
					break;														//ループを抜ける
				}
				if (collisionMarker2 != ',' && collisionMarker2 != '\n')			//区切りか改行でなければ
				{
					strcat_s(collisionBuffer2, (const char*)&collisionMarker2);	//strcat_s関数でbufferに連結し、const char関数で書き換える
				}
				else
				{
					collisionNum2 = atoi(collisionBuffer2);						//atoi関数でbufferをint型に直して、ローカル変数numに代入
					collisionCell2[collisionColumnNum2][collisionRawNum2].collisionBoxHandle2 = collisionBoxHandle2[collisionNum2];		//num番目のチップ画像のハンドルを取得
					memset(collisionBuffer2, 0, sizeof(collisionBuffer2));		//bufferをリセット
					break;														//区切りか改行なのでループを抜ける
				}
			}
			if (collisionEofFlag2)												//1マップ分になったら
			{
				break;															//ループを抜ける
			}
			if (collisionMarker2 == ',')											//区切りを検出したら
			{
				collisionColumnNum2++;											//列の数を増やす
			}
			if (collisionMarker2 == '\n')										//改行だったら
			{
				collisionRawNum2++;												//行を増やす
				collisionColumnNum2 = 0;											//列を0にする
			}
		}
		fclose(collisionFilePointer);											//ファイルを閉じる
	}

	//---
	//当たり判定設置
	//---
	void ColBox2()
	{
		const int playerW = Player_Width;
		const int playerH = Player_Height;

		int playerLX = playerX - Img_BlankX;				//左X
		int playerLOY = playerY - Img_BlankY;				//左上Y
		int playerLUY = playerY + playerH;					//左下Y
		int playerRX = playerX + playerW - Img_BlankX;		//右X
		int playerROY = playerY - Img_BlankY;				//右上Y 
		int playerRUY = playerY + playerH;					//右下Y

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
				// そこはブロックか？
				if (collisionCell2[ix][iy].collisionBoxHandle2 == collisionBoxHandle2[1])
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
							(collisionCell2[ix][iy - 1].collisionBoxHandle2 == collisionBoxHandle2[0]) &&
							(playerVY > 0))
						{
							playerY = blkLOY - playerH;
							playerYPrev = playerY;
							jumpFlag = false;
						}
						//ブロックの左端とぶつかった
						if ((playerRX - blkLX > 0) &&		//+であればめり込んでいる
							(playerRX - blkLX <= 16) &&
							(collisionCell2[ix - 1][iy].collisionBoxHandle2 == collisionBoxHandle2[0]) &&
							(playerVX > 0))
						{
							playerX = blkLX - playerW + Img_BlankX - 1;
							playerXPrev = playerX;
						}
						//ブロックの右端とぶつかった
						if ((blkRX - playerLX > 0) &&		//-であればめり込んでいる
							(blkRX - playerLX <= 16) &&	//ブロックとプレイヤーの指定位置の距離が16になったら
							(collisionCell2[ix + 1][iy].collisionBoxHandle2 == collisionBoxHandle2[0]) &&
							(-playerVX > 0))
						{
							playerX = blkRX + Img_BlankX;
							playerXPrev = playerX;
						}
					}
				}
				// そこはブロックか？	(ブロック全方向当たり)	
				if (collisionCell2[ix][iy].collisionBoxHandle2 == collisionBoxHandle2[2])
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
							(collisionCell2[ix][iy - 1].collisionBoxHandle2 == collisionBoxHandle2[0]) &&
							(playerVY > 0))
						{
							playerY = blkLOY - playerH;
							playerYPrev = playerY;
							jumpFlag = false;
						}
						//ブロックの左端とぶつかった
						if ((playerRX - blkLX > 0) &&		//+であればめり込んでいる
							(playerRX - blkLX <= 16) &&
							(collisionCell2[ix - 1][iy].collisionBoxHandle2 == collisionBoxHandle2[0]) &&
							(playerVX > 0))
						{
							playerX = blkLX - playerW + Img_BlankX - 1;
							playerXPrev = playerX;
						}
						//ブロックの右端とぶつかった
						if ((blkRX - playerLX > 0) &&		//-であればめり込んでいる
							(blkRX - playerLX <= 16) &&	//ブロックとプレイヤーの指定位置の距離が16になったら
							(collisionCell2[ix + 1][iy].collisionBoxHandle2 == collisionBoxHandle2[0]) &&
							(-playerVX > 0))				//移動速度が1以上なら
						{
							playerX = blkRX + Img_BlankX;
							playerXPrev = playerX;
						}
						//ブロックの下端とぶつかった
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

		// 足元を調べる
		idRUY = (playerY + playerH) / COLLISION_CELL_HEIGHT;
		//ジャンプ中でないのに、両足とも空中にいないか？
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