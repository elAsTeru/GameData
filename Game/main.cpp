#include"DxLib.h"
#include"setting.h"
#include"map.h"
#include"map2.h"
#include"collision.h"
#include"collision2.h"
#include"function.h"
#include"player.h"
#include"enemy.h"
#include"characterfunction.h"
#include"move.h"
#include"enemy.h"

#define NULL 0

void runLauncher(const char* path)
{

	char fullPathexe[512];
#pragma warning (disable:4996)
	sprintf(fullPathexe, "%s%s", path, "Launcher.exe");

	// プロセス起動準備
	PROCESS_INFORMATION pi = { 0 };
	STARTUPINFO si = { 0 };
	si.cb = sizeof(STARTUPINFO);

	CreateProcess(fullPathexe, (LPSTR)"", NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, path, &si, &pi);
}


//---
//確認モード変更
//---
bool checkFlag = FALSE;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLin, int nCmdShoww)
{
	//---
	//基本設定
	//---
	ChangeWindowMode(checkFlag);										//画面モード
	if (DxLib_Init() == -1)return-1;
	SetDrawScreen(DX_SCREEN_BACK);									//裏焼き
	SetGraphMode(Window_Width, Window_Height, Color_Depth);


	//---
	//パッド対応(構造体読み込み)
	//---
	XINPUT_STATE input;


	//---
	//画像データ取り込み
	//---
	int titleImg = LoadGraph("img/t.png");
	int overImg = LoadGraph("img/o.png");
	int backgroundImg = LoadGraph("img/Field.jpg");
	int backgroundImg2 = LoadGraph("img/desert.jpg");
	int controllImg = LoadGraph("img/controll.png");

	int playerMapChangeImg = LoadGraph("img/change.png");
	LoadDivGraph("img/idle3.png", 2, 2, 1, 64, 64, playerIdle);					//待機モーション画像分割プリロード
	LoadDivGraph("img/pAnime3.png", 7, 7, 1, 64, 64, playerRun);					//ランアニメ画像分割プリロード
	LoadDivGraph("img/jump3.png", 6, 6, 1, 64, 64, playerJump);					//ランアニメ画像分割プリロード
	LoadDivGraph("img/playerDamaged3.png", 2, 2, 1, 64, 64, playerDamaged);	//ダメージ画像分割プリロード
	LoadDivGraph("img/Ring.png", 10, 10, 1, 16, 16, ring);
	hpGaugeImg = LoadGraph("img/gauge.png");
	ConfusionImg = LoadGraph("img/confusion.png");

	LoadDivGraph("img/Mandragora.png", 6, 6, 1, 40, 50, mand);	//敵機0画像読み込み
	LoadDivGraph("img/slime.png", 5, 5, 1, 32, 40, slim);
	LoadDivGraph("img/crow.png", 4, 4, 1, 75, 68, crow);
	LoadDivGraph("img/nite.png", 6, 6, 1, 128, 128, nite);


	//---
	//サウンドデータ読み込み
	//--- 
	int titleBgm = LoadSoundMem("sound/itazuracat.mp3");
	int playBgm = LoadSoundMem("sound/rogue.mp3");			//ゲームメイン
	int clearBgm = LoadSoundMem("sound/deepsea.mp3");
	int overBgm = LoadSoundMem("sound/freezeheart.mp3");
	int jumpSound = LoadSoundMem("sound/jump.mp3");			//ジャンプ
	int warpSound = LoadSoundMem("sound/warp3.wav");		//マップ変更


	//---
	//マップタイル読み込み
	//---
	//NULLを代入
	Map* map = NULL;
	Map2* map2 = NULL;
	Collision* collision = NULL;
	Collision2* collision2 = NULL;

	map = new Map();										//タイルマップ関数を読み込む
	map2 = new Map2();
	collision = new Collision();						//タイルとの当たり判定関数を読み込む
	collision2 = new Collision2();


	//---
	//ゲーム開始
	//---
	while (1)
	{
		//---
		//ゲームタイトル
		//---
		//BGM
		PlaySoundMem(titleBgm, DX_PLAYTYPE_LOOP);
		while (!ProcessMessage() && gameStatus == TITLE)			//もしエラーがでずゲーム状態がTITLEなら
		{
			//bgm停止
			StopSoundMem(clearBgm);
			StopSoundMem(overBgm);

			//パッド入力読み込み
			GetJoypadXInputState(DX_INPUT_PAD1, &input);


			ClearDrawScreen();


			DrawGraph(0, 0, titleImg, TRUE);
			
			////タイトル表示
			SetFontSize(128);										//文字サイズ設定
			DrawString(704, 400, "R I N G", GetColor(0, 255, 0));
			SetFontSize(64);
			DrawString(400, 600, "STARTを押したらゲームはじまります！", GetColor(0, 255, 0));
			////表示セッティング
			SetFontSize(16);
			DrawString(1500, 970, "Press To S : ", GetColor(255, 0, 0));
			if (!controllDontShowFlag)
			{
				DrawString(1500, 1000, "操作方法を表示します。", GetColor(255, 0, 0));
			}
			else
			{
				DrawString(1500, 1000, "操作方法を表示しません。", GetColor(255, 0, 0));
			}

			if (CheckHitKey(KEY_INPUT_S) == 1)
			{
				while (1)
				{
			
					if (CheckHitKey(KEY_INPUT_S) == 0)
					{
						if (!controllDontShowFlag)
						{
							controllDontShowFlag = TRUE;
						}
						else
						{
							controllDontShowFlag = FALSE;
						}

						break;
					}
				}
			}
			


			//制作用
			if (checkFlag)
			{
				DrawString(704, 600, "確認モードです\npで始まります", GetColor(255, 0, 0));
			}


			ScreenFlip();


			//ゲームを始める
			if (CheckHitKey(KEY_INPUT_SPACE) == 1 || input.Buttons[4] == 1)
			{
				gameStatus = INIT;									//ゲームの状態を初期化にする
			}
			//終了する
			if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
			{
				gameStatus = END;
			}


			//開発用
			if (checkFlag)
			{
				stateChange();
			}
		}
		WaitTimer(100);


		//---
		//ゲームの初期化
		//---
		while (!ProcessMessage() && gameStatus == INIT)			//もしエラーがでずゲーム状態がINITなら
		{
			//BGM等停止
			StopSoundMem(titleBgm);
			StopSoundMem(playBgm);
			StopSoundMem(clearBgm);
			StopSoundMem(overBgm);


			//環境変数初期化
			saidDark = 0;
			noActionCounter = 0;
			time = 0;
			gravity = GRAVITY;

			////マップ初期化
			//表示
			mapChangeFlag = FALSE;
			//移動
			scrollFlag == FALSE;
			backgroundSpeed = 0;
			//座標
			backgroundX = 0;
			secondBackgroundX = Second_Background_X;
			backgroundY = 0;
			mapProceedX = 0;
			//mapProceedXPrev = 0;


			////自機初期化
			if (playerFlag == FALSE)			//プレイヤーが無効なら
			{
				playerFlag = TRUE;
			}
			if (playerFlag == TRUE)
			{
				jumpFlag = FALSE;
				//ステータス
				playerHP = PlayerHP_First;
				//画像
				playerImg = playerIdle[frameCounter2];
				//座標
				playerX = Player_First_X;
				playerY = Player_First_Y;
				playerXPrev = playerX;
				playerYPrev = playerY;
				//移動
				playerRightSpeed = Player_RightSpeed;
				playerLeftSpeed = Player_LeftSpeed;
				//表示
				playerReverse = FALSE;
				playerBackX = 0;
				//playerBackXTemp = 0;
				//イベント
				playerConfusionFlag = FALSE;
				canNotControllCount = 0;



				////敵機初期化
				for (int i = 0; i < enemy_num_max; i++)
				{
					//移動
					enemySpeedX[i] = Enemy_FirstSpeedX[i];
					//座標
					enemyX[i] = Enemy_FirstX[i];
					enemyY[i] = Enemy_FirstY[i];
					//表示
					enemyReverse[i] = enemy_reverse[i];
				}



				//BGM
				PlaySoundMem(playBgm, DX_PLAYTYPE_LOOP);

				gameStatus = PLAY;
			}
		}
		WaitTimer(100);


		//---
		//ゲームメイン
		//---
		while (!ProcessMessage() && gameStatus == PLAY)
		{
			//時間計算開始
			noActionCounter++;
			time++;

			//パッド入力読み込み
			GetJoypadXInputState(DX_INPUT_PAD1, &input);

			//文字表示サイズ変更
			SetFontSize(16);

			//---
			//描画初期化
			//---
			ClearDrawScreen();

			playerImg = playerIdle[frameCounter2];

			//自機右移動定義・背景左移動定義
			int playerVX = playerX - playerXPrev;
			if ((CheckHitKey(KEY_INPUT_RIGHT) == 1 || input.Buttons[3] == 1)&& !playerConfusionFlag)						//右を押したら
			{
				noActionCounter = 0;
				playerXPrev = playerX;									//前回座標に現在座標を保存する
				moveRight(playerX, playerRightSpeed, playerReverse);	//右に移動関数

				playerImg = playerRun[frameCounter7];					//自機表示をランにする

				if (scrollFlag == TRUE)									//背景の移動が許可されていれば
				{
					backgroundSpeed = Background_FirstSpeed;			//背景に移動速度をつける
				}
				if (playerVX == 0 || scrollFlag == FALSE)				//プレイヤーが壁などに当たって移動していない　又は　スクロールが許可されていなければ
				{
					backgroundSpeed = 0;								//背景の移動を止める	
				}

				backgroundX -= backgroundSpeed;							//背景を移動する
				secondBackgroundX -= backgroundSpeed;					//繋ぎの背景を移動する
			}

			//自機左移動定義
			if ((CheckHitKey(KEY_INPUT_LEFT) == 1 || input.Buttons[2] == 1)&& !playerConfusionFlag)						//左を押したら
			{
				noActionCounter = 0;
				playerXPrev = playerX;									//前回座標に現在座標を保存する
				moveLeft(playerX, playerLeftSpeed, playerReverse);

				playerImg = playerRun[frameCounter7];					//自機表示をランにする

				if (scrollFlag == TRUE)									//背景の移動が許可されていれば
				{
					backgroundSpeed = -Background_FirstSpeed;			//背景に移動速度をつける
				}
				if (playerVX == 0 || scrollFlag == FALSE)				//プレイヤーが壁などに当たって移動していない　又は　スクロールが許可されていなければ
				{
					backgroundSpeed = 0;								//背景の移動を止める	
				}

				backgroundX -= backgroundSpeed;							//背景を移動する
				secondBackgroundX -= backgroundSpeed;					//繋ぎの背景を移動する
			}

			//ジャンプ処理
			if ((CheckHitKey(KEY_INPUT_SPACE) == 1|| input.Buttons[12] == 1) && jumpFlag == false && !playerConfusionFlag)								//Bボタンが押されたら
			{
				noActionCounter = 0;
				jumpFlag = true;																//ジャンプ可能にする
				PlaySoundMem(jumpSound, DX_PLAYTYPE_BACK);
				playerYPrev = playerY;															//前回座標に現在座標を保存する
				playerY -= JumpPower;															//ジャンプ力で座標移動する
			}
			if (jumpFlag == true || playerConfusionFlag == TRUE && jumpFlag == true)																//ジャンプ可能ならば
			{
				if (!playerConfusionFlag)
				{
					playerImg = playerJump[frameCounter6];					//自機表示をジャンプにする
				}
				playerYTemp = playerY;															//現在のy座標を一時保存する
				playerSpeedY = (playerY - playerYPrev) + gravity;                                         // y方向の速度求める
				playerSpeedY = (playerSpeedY > MaxVy) ? MaxVy : playerSpeedY;

				playerY += playerSpeedY;			                                 						//現在のy座標を前回y座標との差分だけ足して重力値を引く
				playerYPrev = playerYTemp;
				//前回の座標として一時保存の座標を保存する				
			}



			//---
			//敵機フラグ
			//---
			for (int i = 0; i < enemy_num_max; i++)
			{
				if (enemyAliveFlag[i] == FALSE)
				{
					enemyX[i] = Enemy_FirstX[i];
				}
				if ((playerX - Player_StopPosition_X) - Enemy_Width[i] < enemyX[i] && enemyX[i] < 1920 + (playerX - Player_StopPosition_X))		//もし敵が画面内に入ったら	//敵サイズ分は余裕を持たせる
				{
					if (enemyX[i] < (playerX - Player_StopPosition_X - Enemy_Width[i]) || enemyX[i] > 1920 + (playerX - Player_StopPosition_X) - Enemy_Width[i])
					{
						enemyAliveFlag[i] = TRUE;
					}
				}
				else
				{
					enemyAliveFlag[i] = FALSE;			//画面外なら消す
				}
			}
			////敵機　マップによる湧き制限
			for (int i = 0; i < enemy_num_max; i++)
			{
				if (enemySwitchFlag[i] == 1 && mapChangeFlag)		//マップ1のみで湧くものがマップ2の時
				{
					enemyAliveFlag[i] = FALSE;
				}
			}
			//---
			//敵機移動
			//---

			for (int i = 0; i < enemy_num_max; i++)								//敵が画面内に入ったら動くようにする
			{
				if (enemyAliveFlag[i] == TRUE)
				{
					enemyMove(enemyX[i], enemyY[i], enemySpeedX[i], enemySpeedY[i], spownPosi[i], enemyReverse[i]);
				}
			}
			//---
			//敵機と自機　当たり判定・マップダメージ
			//---
			for (int i = 0; i < enemy_num_max; i++)
			{
				if (!playerConfusionFlag && !playerInvincibleFlag && enemyAliveFlag[i])						//もしプレイヤーがやられ状態,無敵状態でなく当たり判定の対象となる敵が存在すれば
				{
					//キャラ用当たり判定関数
					if (characterCollision(enemyX[i] - enemy_img_brankX[i], enemyY[i] + enemy_img_brankY[i] , Enemy_Width[i], Enemy_Height[i],
						playerX, playerY, Player_Width - Img_BlankX, Player_Height))
					{
						playerConfusionFlag = TRUE;
						jumpFlag == true;
						playerHP-=20;
					}
				}
			}
			if (!playerConfusionFlag && !playerInvincibleFlag)
			{
				//---
				//マップイベント
				//---
				if (!mapChangeFlag)
				{
					//マップダメージ（当たった時の処理は上と同じ）
					if (characterCollision(3776 - Img_BlankX, 800, 96 + 32, 32,
						playerX, playerY, Player_Width - Img_BlankX, Player_Height))
					{
						playerConfusionFlag = TRUE;
						jumpFlag == true;
						playerHP-=20;
					}

					//マップ強制横移動//マップ1の下の左移動
					if (characterCollision(576 - Img_BlankX, 960, 1152 + 32, 96,
						playerX, playerY, Player_Width - Img_BlankX, Player_Height))
					{
						playerRightSpeed = 0;
						playerX -= 6;
					}
					else
					{
						playerRightSpeed = Player_RightSpeed;
					}
				}
				//960, 1728 - playerBackX, 1056
			}

			if (playerConfusionFlag == TRUE)
			{
				playerImg = playerDamaged[frameCounter2];					//自機表示を被弾にする
				if (!playerReverse)											//敵機に対して当たった方向の逆に移動する（跳ね返り）
				{
					playerX -= 1;											//左に跳ね返り
				}
				else
				{
					playerX += 1;											//右に跳ね返り
				}
				playerY += 1;												//どっちから当たっても下に落ちる

				canNotControllCount++;													//操作不可能時間用カウント
				if (canNotControllCount >= 25)
				{
					playerConfusionFlag = FALSE;							//操作不可能時間のカウントが終わったらやられ状態をもどして
					playerInvincibleFlag = TRUE;							//プレイヤーを無敵にする。
					canNotControllCount = 0;
				}
			}
			if (playerInvincibleFlag)									//プレイヤーが無敵中なら
			{
				canNotControllCount++;													//無敵時間を終了するためにカウントする
				if (canNotControllCount >= 50)											//カウントが50になったら
				{
					playerInvincibleFlag = FALSE;							//無敵を無効にし
					canNotControllCount = 0;												//カウントを無効にする
				}
			}
			//---
			//タイルとの当たり判定
			//---
			if (!mapChangeFlag)
			{
				collision->ColAll();			//タイルとの当たり判定
			}
			else
			{
				collision2->ColAll2();
			}
			//---
			//画面左当たり判定
			//---
			if (playerX - Img_BlankX <= mapProceedX)							//画面左と当たっていたら
			{
				playerLeftSpeed = 0;					//左移動をできなくする
				if (playerX < mapProceedX && playerX > -Img_BlankX)		//めり込んでいたら戻す
				{
					playerX = mapProceedX;
				}
			}
			else										//そうで無ければ左移動速度を元に戻す
			{
				playerLeftSpeed = Player_FirstSpeed;
			}
			//---
			//画面下ゲームオーバー判定
			//---
			if (playerY >= 1200)
			{
				playerFlag = false;						//プレイヤーを無効化する
			}

			//---
			//スクロール関係・自機描画位置定義		//タイルとの当たり判定後に定義する必要がある
			//---
			//開始から画面中央までのスクロールなしの部分
			if (0 <= playerX && playerX < Player_StopPosition_X)
			{
				playerBackX = 0;
				scrollFlag = FALSE;
			}
			else if (Scroll_Stop_Position <= playerX)		//マップ一番右に来たら
			{
				playerBackX = Scroll_Stop_Position - Player_StopPosition_X;		//自機を画面表示停止位置から右に行けるようにする
				scrollFlag = FALSE;												//背景のスクロールを停止する
			}
			else											//通常移動
			{
				playerBackX = playerX - Player_StopPosition_X;			//自機移動を停止したように見せ			////プレイヤーの描画位置を引いて停止位置に来るようにする
				//playerBackXTemp = playerBackX;							//自機描画時の画面上座標を一時的に記憶
				mapProceedX = playerBackX;								//マップの描画位置変更にもプレイヤー描画位置変更を入れる
				//mapProceedXPrev = playerBackX;							//マップの描画位置変更を記憶する
				scrollFlag = TRUE;										//スクロールを開始する
			}


			//---
			//マップ変更処理
			//---
			if (CheckHitKey(KEY_INPUT_R) == 0 && input.Buttons[15] == 0)		//もしRキーが押されてなければ押せるようにする
			{
				rKeyFlag = FALSE;
			}
			////マップ変更不可位置定義
			if ((playerX >= 2560 && playerX <= 2752 && playerY >= 640 && playerY <= 832)||
				(playerX >= 2752 && playerX <= 2816 && playerY >= 770 && playerY <= 832)||
				(playerX >= 4896 && playerX <= 5000))
			{
				rKeyFlag = TRUE;
			}
			if ((CheckHitKey(KEY_INPUT_R) == 1 || input.Buttons[15] == 1) && !rKeyFlag && !playerConfusionFlag && !jumpFlag)	//Rキーフラグが無効かつRキーが押されプレイヤーが混乱、ジャンプ中でなければ
			{
				rKeyFlag = TRUE;				//Rキーフラグを有効にして
				//マップ変更定義
				if (!mapChangeFlag)				//マップ変更フラグが無効なら
				{
					mapChangeFlag = TRUE;
				}
				else
				{
					mapChangeFlag = FALSE;
				}
				//---
				//マップ変更処理（後回し・マップ変更のフェードイン・フェードアウト）
				//---
				PlaySoundMem(warpSound, DX_PLAYTYPE_BACK);
				const int First_Light = 255;
				const int First_Deep = 0;
				for (int deep = First_Deep; deep <= 255; deep += 3)					//deepで画像を濃ゆくしていく
				{
					//lightで画像を薄くしていく
					ClearDrawScreen();
					

					if (!mapChangeFlag)
					{
						//画像１濃ゆく
						enemyAliveFlag[3] = 1;
						SetDrawBlendMode(DX_BLENDMODE_ALPHA, deep);
						DrawGraph(backgroundX, backgroundY, backgroundImg, FALSE);
						DrawGraph(secondBackgroundX, backgroundY, backgroundImg, FALSE);
						map->All();
						//画像２薄く
						SetDrawBlendMode(DX_BLENDMODE_ALPHA, First_Light - deep);
						DrawGraph(backgroundX, backgroundY, backgroundImg2, FALSE);
						DrawGraph(secondBackgroundX, backgroundY, backgroundImg2, FALSE);
						map2->All2();;

					}
					else
					{
						//画像2濃ゆく
						SetDrawBlendMode(DX_BLENDMODE_ALPHA, deep);
						DrawGraph(backgroundX, backgroundY, backgroundImg2, FALSE);
						DrawGraph(secondBackgroundX, backgroundY, backgroundImg2, FALSE);
						map2->All2();;
						//画像１薄く
						SetDrawBlendMode(DX_BLENDMODE_ALPHA, First_Light - deep);
						DrawGraph(backgroundX, backgroundY, backgroundImg, FALSE);
						DrawGraph(secondBackgroundX, backgroundY, backgroundImg, FALSE);
						map->All();;

					}

					//自機描画
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
					DrawRotaGraph(playerX - playerBackX, playerY, 2.0f, 0, playerMapChangeImg, TRUE, FALSE);			//自機描画
					DrawRotaGraph(playerX - playerBackX + 32, playerY - 16, 2.5f, 0, ring[deep % 10], TRUE, 0);


					ScreenFlip();
				}
				StopSoundMem(warpSound);
			}


			//---
			//描画処理
			//---
			timeCounter = GetNowCount();
			frameCounter = timeCounter % 8;
			frameCounter2 = timeCounter / 250 % 2;
			frameCounter4 = timeCounter / 125 % 4;
			frameCounter5 = timeCounter / 125 % 5;
			frameCounter6 = timeCounter / 125 % 6;
			frameCounter7 = timeCounter / 125 % 7;
			frameCounter8 = timeCounter / 125 % 8;
			frameCounter10 = timeCounter / 125 % 10;
			frameCounter10Fast = timeCounter / 60 % 10;


			//背景画像スクロールのループ処理
			if (secondBackgroundX <= 0)								//もし2つ目の背景が画面左端に来たら
			{
				backgroundX = 0;									//背景の位置を初期位置に戻す
				secondBackgroundX = Second_Background_X;
			}
			if (backgroundX > 0)										//もし1つ目の背景が右に移動したら
			{
				secondBackgroundX = -1920;
				backgroundX = 0;
			}
			if (!mapChangeFlag)								//マップ描画
			{
				DrawGraph(backgroundX, backgroundY, backgroundImg, FALSE);
				DrawGraph(secondBackgroundX, backgroundY, backgroundImg, FALSE);
				//map3->All3();
				map->All();
			}
			else
			{
				DrawGraph(backgroundX, backgroundY, backgroundImg2, FALSE);
				DrawGraph(secondBackgroundX, backgroundY, backgroundImg2, FALSE);
				map2->All2();
			}


			//---
			//自機描画
			//---
			if (!playerInvincibleFlag)		//もし無敵状態でなければ普通に表示する
			{
				DrawRotaGraph(playerX - playerBackX, playerY, 2.0f, 0, playerImg, TRUE, playerReverse);			//自機描画
			}
			else							//そうで無ければ
			{
				if (timeCounter % 2 == 0)	//タイムカウンタが偶数の時プレイヤーを表示する
				{
					DrawRotaGraph(playerX - playerBackX, playerY, 2.0f, 0, playerImg, TRUE, playerReverse);
				}
			}
			if (playerConfusionFlag == TRUE)
			{
				DrawRotaGraph(playerX - playerBackX, playerY - 32, 2.0f, 0, ConfusionImg, TRUE);		//自機混乱画像
			}


			//---
			//リング描画
			//---
			if (!playerReverse)
			{
				DrawRotaGraph(playerX - playerBackX - 32, playerY - 16, 2.5f, 0, ring[frameCounter10Fast], TRUE, 0);
			}
			else
			{
				DrawRotaGraph(playerX + Player_Width - playerBackX + 8, playerY - 16, 2.5f, 0, ring[frameCounter10Fast], TRUE, 1);
			}
		


			//---
			//敵機描画
			//---
			if (!mapChangeFlag)
			{
				enemyImg[0] = mand[frameCounter6];
				enemyImg[1] = mand[frameCounter6];
				enemyImg[2] = crow[frameCounter4];
				enemyImg[3] = nite[frameCounter6];
			}
			else
			{
				enemyImg[0] = slim[frameCounter5];
				enemyImg[1] = slim[frameCounter5];
				enemyImg[2] = crow[frameCounter4];
				enemyImg[3] = nite[frameCounter6];
			}

			if (enemyAliveFlag[0])
				DrawRotaGraph(enemyX[0] - playerBackX, enemyY[0], 2.0f, 0, enemyImg[0], TRUE, enemyReverse[0]);
			if (enemyAliveFlag[1])
				DrawRotaGraph(enemyX[1] - playerBackX, enemyY[1], 1.5f, 0, enemyImg[2], TRUE, enemyReverse[1]);
			if (enemyAliveFlag[2])
				DrawRotaGraph(enemyX[2] - playerBackX, enemyY[2], 2.0f, 0, enemyImg[1], TRUE, enemyReverse[2]);
			if (enemyAliveFlag[3])
				DrawRotaGraph(enemyX[3] - playerBackX, enemyY[3], 2.0f, 0, enemyImg[3], TRUE, enemyReverse[3]);



			//---
			//文字表示
			//---
			SetFontSize(32);
			DrawFormatString(1800, 40, GetColor(255, 255, 255), "%d", countDown = count_down_first - time / 60);

			////体力ゲージ表示
			DrawBox(810, 30, 810 + playerHP * 3, 77, GetColor(0, 255, 0), TRUE);
			DrawGraph(810, 30, hpGaugeImg, TRUE);
			SetFontSize(16);
			DrawFormatString(945, 45, GetColor(255, 255, 255), "%d", playerHP);
			////操作方法表示
			if (!controllDontShowFlag)
			{
				if (noActionCounter >= controllSaidTime)
				{
					if (saidDark <= 200)
					{
						saidDark += 5;
					}
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, saidDark);		//表示する画像を濃ゆくする
					DrawGraph(0, 1080 - 124, controllImg, TRUE);
				}
				else
				{
					saidDark = 0;

					SetDrawBlendMode(DX_BLENDMODE_ALPHA, saidDark);		//表示する画像を濃ゆくする
					DrawGraph(0, 1080 - 124, controllImg, TRUE);
				}
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);				//このままだと他の表示が薄くなるのでリセットする、操作方法には影響しない
			}


			//---
			//ゲーム状態判定
			//---
			//ゲームオーバー判定
			if (playerFlag == FALSE || playerHP <= 0 || countDown <= 0)
			{
				gameStatus = OVER;
				//BGM
				PlaySoundMem(overBgm, DX_PLAYTYPE_LOOP);
			}
			//---
			//クリア判定
			//---
			if (playerX >= Player_EndPosition_X && mapChangeFlag == TRUE)
			{
				gameStatus = CLEAR;
				//BGM
				PlaySoundMem(clearBgm, DX_PLAYTYPE_LOOP);
			}


			//---
			//確認用
			//---
			if (checkFlag)
			{
				////自機
				//左上　右下　当たり位置確認
				int left = playerX - Img_BlankX - playerBackX;
				int right = playerX + Player_Width - Img_BlankX - playerBackX;
				int over = playerY - Img_BlankY;
				int under = playerY + Player_Height;
				int circleSize = 5;

				//左・右
				DrawCircle(left, playerY, circleSize, GetColor(255, 0, 0));
				DrawCircle(right, playerY, circleSize, GetColor(255, 0, 0));
				//四角表示
				DrawLine(left, over, left, under, GetColor(0, 0, 255));		//左
				DrawLine(right, over, right, under, GetColor(0, 0, 255));	//右
				DrawLine(left, over, right, over, GetColor(0, 0, 255));		//上
				DrawLine(left, under, right, under, GetColor(0, 0, 255));	//下


				////敵機
				DrawFormatString(enemyX[0] - playerBackX, enemyY[0] - 32, GetColor(255, 0, 0), "(X:%d,Y:%d,SpownPosi:%d)", enemyX[0], enemyY[0], spownPosi[0]);
				for (int i = 0; i < enemy_num_max; i++)
				{
					if (enemyAliveFlag[i] == 1)
					{
						DrawBox((enemyX[i] - enemy_img_brankX[i]) - playerBackX, (enemyY[i] + enemy_img_brankY[i]),
							(enemyX[i] - enemy_img_brankX[i]) + Enemy_Width[i] - playerBackX, (enemyY[i] + enemy_img_brankY[i]) + Enemy_Height[i], GetColor(255, 0, 0), TRUE);
					}
				}


				//---
				//マップイベント位置を箱で表示
				//---
				////マップダメージ
				if (!mapChangeFlag)
				{
					DrawBox(3776 - playerBackX, 800, 3776 + 96 - playerBackX, 832, GetColor(255, 0, 0), TRUE);
				}
				////マップ強制横移動
				if (!mapChangeFlag)
				{
					DrawBox(576 - playerBackX, 960, 1728 - playerBackX, 1056, GetColor(255, 0, 0), TRUE);
				}
				//DrawBox(0, 0, 1980, 128, GetColor(255, 255, 255), TRUE);
				////マップ変更禁止位置
				DrawBox(2560 - playerBackX, 640, 2752 - playerBackX, 832, GetColor(0, 255, 0), TRUE);
				DrawBox(2752 - playerBackX, 770, 2816 - playerBackX, 832, GetColor(0, 255, 0), TRUE);
				DrawBox(4896 - playerBackX, 0, 5536 - playerBackX, 1080, GetColor(0, 255, 0), TRUE);

				//実行中確認用
				DrawString(100, 30, "確認用", playerX, GetColor(255, 0, 0));
				DrawFormatString(playerX - playerBackX - 130, playerY - 50, GetColor(255, 0, 0), "(X:%d,Y:%d)", playerX, playerY);
				DrawFormatString(100, 50, GetColor(255, 0, 0), "X(描画) : %d", playerX - playerBackX);
				DrawFormatString(100, 70, GetColor(255, 0, 0), "playerReverse : %d", playerReverse);
				DrawFormatString(100, 90, GetColor(255, 0, 0), "jumpFlag : %d", jumpFlag);
			}


			ScreenFlip();


			if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
			{
				gameStatus = END;
			}

			//開発用
			if (checkFlag)
			{
				stateChange();
			}
		}
		WaitTimer(100);


		//---
		//ゲームオーバー
		//---
		while (!ProcessMessage() && gameStatus == OVER)
		{
			//BGM停止
			StopSoundMem(playBgm);
	

			//パッド入力読み込み
			GetJoypadXInputState(DX_INPUT_PAD1, &input);

			ClearDrawScreen();

			StopSoundMem(playBgm);

			DrawGraph(0, 0, overImg, FALSE);

			SetFontSize(128);
			DrawString(550, 400, "ゲームオーバー", GetColor(0, 255, 0));
			//SetFontSize(32);
			//DrawString(700, 550, "今日はつかれたから家に帰ろっかな", GetColor(0, 255, 0));
			SetFontSize(64);
			DrawString(700, 600, "STARTでタイトルに!", GetColor(0, 255, 0));
	
			ScreenFlip();
			
			if (CheckHitKey(KEY_INPUT_SPACE) == 1 || input.Buttons[4] == 1)
			{
				gameStatus = TITLE;
			}
			if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
			{
				gameStatus = END;
			}

			//開発用
			if (checkFlag)
			{
				stateChange();
			}
		}
		WaitTimer(100);


		//---
		//クリア
		//---
		while (!ProcessMessage() && gameStatus == CLEAR)
		{
			//BGM停止
			StopSoundMem(playBgm);


			//パッド入力読み込み
			GetJoypadXInputState(DX_INPUT_PAD1, &input);

			StopSoundMem(playBgm);

			ClearDrawScreen();

			DrawGraph(0, 0, backgroundImg2, TRUE);
			mapProceedX = 3500;
			map2->All2();
			SetFontSize(128);
			DrawString(750, 400,"クリア", GetColor(0, 0, 255));
			SetFontSize(64);
			DrawFormatString(730, 535, GetColor(0, 0, 255), "SCORE : %d", (playerHP / 20 * 5000) + (countDown * 500));
			DrawString(700, 600, "STARTでタイトルに", GetColor(0, 0, 255));
			

			ScreenFlip();

			if (CheckHitKey(KEY_INPUT_SPACE) == 1 || input.Buttons[4] == 1)
			{
				gameStatus = TITLE;
			}
			if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
			{
				gameStatus = END;
			}

			//開発用
			if (checkFlag)
			{
				stateChange();
			}
		}
		WaitTimer(100);


		//---
		//ループ終了
		//---
		while (!ProcessMessage() && gameStatus == END)
		{
			//BGM停止
			StopSoundMem(titleBgm);
			StopSoundMem(playBgm);
			StopSoundMem(clearBgm);
			StopSoundMem(overBgm);


			//---
			//マップタイル解放
			//---
			delete map;
			delete map2;
			delete collision;
			delete collision2;
			//delete map3;

			//NULL代入
			map = NULL;
			map2 = NULL;
			collision = NULL;
			collision2 = NULL;

			break;						//ループから抜ける
		}

		if (gameStatus == END)			//ゲーム状態がENDなら終了する
		{
			break;
		}

	}


	DxLib_End();		//終了

	runLauncher("../../");

	return 0;
}

//4600