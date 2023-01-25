#pragma once
#include <DxLib.h>

//2つ目以降用

int rawNum3 = 0;														//横方向のタイルナンバー
int columnNum3 = 0;														//縦方向のタイルナンバー
bool eofFlag3 = false;													//eof（end of file）検出フラグ

struct Cell3																//タイル用の構造体を作る
{
	int graphicHandle;													//画像操作用の変数
};

class Map3																												//mapクラスを作る
{
public:

	Cell3 cell[CELL_NUM_X][CELL_NUM_Y];																					//構造体にタイルの横縦を格納する

	Map3()
	{
		LoadDivGraph("img/fit.png", (MAPCHIP_IMG_WIDTH / CELL_WIDTH) * (MAPCHIP_IMG_HEIGHT / CELL_HEIGHT), MAPCHIP_IMG_WIDTH / CELL_WIDTH, MAPCHIP_IMG_HEIGHT / CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT, chipgraphicHandle);			//タイル画像を読み込む
		FILE* filePointer;																								//ファイルのポインタを宣言
		fopen_s(&filePointer, "csv/map_Background1.csv", "r");																	//fopen_s関数でmap.csvを読み取り形式で開く
		if (filePointer == NULL)																						//filePointerが空の場合は
		{
			DebugBreak();																								//デバッグ中止
		}

		memset(buffer, 0, sizeof(buffer));																				//memset関数でメモリにbufferをセットし、sizeof演算子で要素数を決める

		while (1)
		{
			while (1)
			{
				characterPack = fgetc(filePointer);										//fgetc関数でfilepointerから文字を読んでcharacterPackに格納
				if (characterPack == EOF)
				{
					eofFlag3 = true;														//EndOfFileを検出して
					break;																//ループを抜ける
				}
				if (characterPack != ',' && characterPack != '\n')						//区切りか改行でなければ
				{
					strcat_s(buffer, (const char*)&characterPack);						//strcat_s関数でbufferに連結し、const char関数で書き換える
				}
				else
				{
					num = atoi(buffer);													//atoi関数でbufferをint型に直して、ローカル変数numに代入
					cell[columnNum3][rawNum3].graphicHandle = chipgraphicHandle[num];		//num番目のチップ画像のハンドルを取得
					memset(buffer, 0, sizeof(buffer));									//bufferをリセット
					break;																//区切りか改行なのでループを抜ける
				}
			}
			if (eofFlag3)																//1マップ分になったら
			{
				break;																	//ループを抜ける
			}
			if (characterPack == ',')													//区切りを検出したら
			{
				columnNum3++;															//列の数を増やす
			}
			if (characterPack == '\n')													//改行だったら
			{
				rawNum3++;																//行を増やす
				columnNum3 = 0;															//列を0にする
			}
		}
		fclose(filePointer);															//ファイルを閉じる
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