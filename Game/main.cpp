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

	// �v���Z�X�N������
	PROCESS_INFORMATION pi = { 0 };
	STARTUPINFO si = { 0 };
	si.cb = sizeof(STARTUPINFO);

	CreateProcess(fullPathexe, (LPSTR)"", NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, path, &si, &pi);
}


//---
//�m�F���[�h�ύX
//---
bool checkFlag = FALSE;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLin, int nCmdShoww)
{
	//---
	//��{�ݒ�
	//---
	ChangeWindowMode(checkFlag);										//��ʃ��[�h
	if (DxLib_Init() == -1)return-1;
	SetDrawScreen(DX_SCREEN_BACK);									//���Ă�
	SetGraphMode(Window_Width, Window_Height, Color_Depth);


	//---
	//�p�b�h�Ή�(�\���̓ǂݍ���)
	//---
	XINPUT_STATE input;


	//---
	//�摜�f�[�^��荞��
	//---
	int titleImg = LoadGraph("img/t.png");
	int overImg = LoadGraph("img/o.png");
	int backgroundImg = LoadGraph("img/Field.jpg");
	int backgroundImg2 = LoadGraph("img/desert.jpg");
	int controllImg = LoadGraph("img/controll.png");

	int playerMapChangeImg = LoadGraph("img/change.png");
	LoadDivGraph("img/idle3.png", 2, 2, 1, 64, 64, playerIdle);					//�ҋ@���[�V�����摜�����v�����[�h
	LoadDivGraph("img/pAnime3.png", 7, 7, 1, 64, 64, playerRun);					//�����A�j���摜�����v�����[�h
	LoadDivGraph("img/jump3.png", 6, 6, 1, 64, 64, playerJump);					//�����A�j���摜�����v�����[�h
	LoadDivGraph("img/playerDamaged3.png", 2, 2, 1, 64, 64, playerDamaged);	//�_���[�W�摜�����v�����[�h
	LoadDivGraph("img/Ring.png", 10, 10, 1, 16, 16, ring);
	hpGaugeImg = LoadGraph("img/gauge.png");
	ConfusionImg = LoadGraph("img/confusion.png");

	LoadDivGraph("img/Mandragora.png", 6, 6, 1, 40, 50, mand);	//�G�@0�摜�ǂݍ���
	LoadDivGraph("img/slime.png", 5, 5, 1, 32, 40, slim);
	LoadDivGraph("img/crow.png", 4, 4, 1, 75, 68, crow);
	LoadDivGraph("img/nite.png", 6, 6, 1, 128, 128, nite);


	//---
	//�T�E���h�f�[�^�ǂݍ���
	//--- 
	int titleBgm = LoadSoundMem("sound/itazuracat.mp3");
	int playBgm = LoadSoundMem("sound/rogue.mp3");			//�Q�[�����C��
	int clearBgm = LoadSoundMem("sound/deepsea.mp3");
	int overBgm = LoadSoundMem("sound/freezeheart.mp3");
	int jumpSound = LoadSoundMem("sound/jump.mp3");			//�W�����v
	int warpSound = LoadSoundMem("sound/warp3.wav");		//�}�b�v�ύX


	//---
	//�}�b�v�^�C���ǂݍ���
	//---
	//NULL����
	Map* map = NULL;
	Map2* map2 = NULL;
	Collision* collision = NULL;
	Collision2* collision2 = NULL;

	map = new Map();										//�^�C���}�b�v�֐���ǂݍ���
	map2 = new Map2();
	collision = new Collision();						//�^�C���Ƃ̓����蔻��֐���ǂݍ���
	collision2 = new Collision2();


	//---
	//�Q�[���J�n
	//---
	while (1)
	{
		//---
		//�Q�[���^�C�g��
		//---
		//BGM
		PlaySoundMem(titleBgm, DX_PLAYTYPE_LOOP);
		while (!ProcessMessage() && gameStatus == TITLE)			//�����G���[���ł��Q�[����Ԃ�TITLE�Ȃ�
		{
			//bgm��~
			StopSoundMem(clearBgm);
			StopSoundMem(overBgm);

			//�p�b�h���͓ǂݍ���
			GetJoypadXInputState(DX_INPUT_PAD1, &input);


			ClearDrawScreen();


			DrawGraph(0, 0, titleImg, TRUE);
			
			////�^�C�g���\��
			SetFontSize(128);										//�����T�C�Y�ݒ�
			DrawString(704, 400, "R I N G", GetColor(0, 255, 0));
			SetFontSize(64);
			DrawString(400, 600, "START����������Q�[���͂��܂�܂��I", GetColor(0, 255, 0));
			////�\���Z�b�e�B���O
			SetFontSize(16);
			DrawString(1500, 970, "Press To S : ", GetColor(255, 0, 0));
			if (!controllDontShowFlag)
			{
				DrawString(1500, 1000, "������@��\�����܂��B", GetColor(255, 0, 0));
			}
			else
			{
				DrawString(1500, 1000, "������@��\�����܂���B", GetColor(255, 0, 0));
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
			


			//����p
			if (checkFlag)
			{
				DrawString(704, 600, "�m�F���[�h�ł�\np�Ŏn�܂�܂�", GetColor(255, 0, 0));
			}


			ScreenFlip();


			//�Q�[�����n�߂�
			if (CheckHitKey(KEY_INPUT_SPACE) == 1 || input.Buttons[4] == 1)
			{
				gameStatus = INIT;									//�Q�[���̏�Ԃ��������ɂ���
			}
			//�I������
			if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
			{
				gameStatus = END;
			}


			//�J���p
			if (checkFlag)
			{
				stateChange();
			}
		}
		WaitTimer(100);


		//---
		//�Q�[���̏�����
		//---
		while (!ProcessMessage() && gameStatus == INIT)			//�����G���[���ł��Q�[����Ԃ�INIT�Ȃ�
		{
			//BGM����~
			StopSoundMem(titleBgm);
			StopSoundMem(playBgm);
			StopSoundMem(clearBgm);
			StopSoundMem(overBgm);


			//���ϐ�������
			saidDark = 0;
			noActionCounter = 0;
			time = 0;
			gravity = GRAVITY;

			////�}�b�v������
			//�\��
			mapChangeFlag = FALSE;
			//�ړ�
			scrollFlag == FALSE;
			backgroundSpeed = 0;
			//���W
			backgroundX = 0;
			secondBackgroundX = Second_Background_X;
			backgroundY = 0;
			mapProceedX = 0;
			//mapProceedXPrev = 0;


			////���@������
			if (playerFlag == FALSE)			//�v���C���[�������Ȃ�
			{
				playerFlag = TRUE;
			}
			if (playerFlag == TRUE)
			{
				jumpFlag = FALSE;
				//�X�e�[�^�X
				playerHP = PlayerHP_First;
				//�摜
				playerImg = playerIdle[frameCounter2];
				//���W
				playerX = Player_First_X;
				playerY = Player_First_Y;
				playerXPrev = playerX;
				playerYPrev = playerY;
				//�ړ�
				playerRightSpeed = Player_RightSpeed;
				playerLeftSpeed = Player_LeftSpeed;
				//�\��
				playerReverse = FALSE;
				playerBackX = 0;
				//playerBackXTemp = 0;
				//�C�x���g
				playerConfusionFlag = FALSE;
				canNotControllCount = 0;



				////�G�@������
				for (int i = 0; i < enemy_num_max; i++)
				{
					//�ړ�
					enemySpeedX[i] = Enemy_FirstSpeedX[i];
					//���W
					enemyX[i] = Enemy_FirstX[i];
					enemyY[i] = Enemy_FirstY[i];
					//�\��
					enemyReverse[i] = enemy_reverse[i];
				}



				//BGM
				PlaySoundMem(playBgm, DX_PLAYTYPE_LOOP);

				gameStatus = PLAY;
			}
		}
		WaitTimer(100);


		//---
		//�Q�[�����C��
		//---
		while (!ProcessMessage() && gameStatus == PLAY)
		{
			//���Ԍv�Z�J�n
			noActionCounter++;
			time++;

			//�p�b�h���͓ǂݍ���
			GetJoypadXInputState(DX_INPUT_PAD1, &input);

			//�����\���T�C�Y�ύX
			SetFontSize(16);

			//---
			//�`�揉����
			//---
			ClearDrawScreen();

			playerImg = playerIdle[frameCounter2];

			//���@�E�ړ���`�E�w�i���ړ���`
			int playerVX = playerX - playerXPrev;
			if ((CheckHitKey(KEY_INPUT_RIGHT) == 1 || input.Buttons[3] == 1)&& !playerConfusionFlag)						//�E����������
			{
				noActionCounter = 0;
				playerXPrev = playerX;									//�O����W�Ɍ��ݍ��W��ۑ�����
				moveRight(playerX, playerRightSpeed, playerReverse);	//�E�Ɉړ��֐�

				playerImg = playerRun[frameCounter7];					//���@�\���������ɂ���

				if (scrollFlag == TRUE)									//�w�i�̈ړ���������Ă����
				{
					backgroundSpeed = Background_FirstSpeed;			//�w�i�Ɉړ����x������
				}
				if (playerVX == 0 || scrollFlag == FALSE)				//�v���C���[���ǂȂǂɓ������Ĉړ����Ă��Ȃ��@���́@�X�N���[����������Ă��Ȃ����
				{
					backgroundSpeed = 0;								//�w�i�̈ړ����~�߂�	
				}

				backgroundX -= backgroundSpeed;							//�w�i���ړ�����
				secondBackgroundX -= backgroundSpeed;					//�q���̔w�i���ړ�����
			}

			//���@���ړ���`
			if ((CheckHitKey(KEY_INPUT_LEFT) == 1 || input.Buttons[2] == 1)&& !playerConfusionFlag)						//������������
			{
				noActionCounter = 0;
				playerXPrev = playerX;									//�O����W�Ɍ��ݍ��W��ۑ�����
				moveLeft(playerX, playerLeftSpeed, playerReverse);

				playerImg = playerRun[frameCounter7];					//���@�\���������ɂ���

				if (scrollFlag == TRUE)									//�w�i�̈ړ���������Ă����
				{
					backgroundSpeed = -Background_FirstSpeed;			//�w�i�Ɉړ����x������
				}
				if (playerVX == 0 || scrollFlag == FALSE)				//�v���C���[���ǂȂǂɓ������Ĉړ����Ă��Ȃ��@���́@�X�N���[����������Ă��Ȃ����
				{
					backgroundSpeed = 0;								//�w�i�̈ړ����~�߂�	
				}

				backgroundX -= backgroundSpeed;							//�w�i���ړ�����
				secondBackgroundX -= backgroundSpeed;					//�q���̔w�i���ړ�����
			}

			//�W�����v����
			if ((CheckHitKey(KEY_INPUT_SPACE) == 1|| input.Buttons[12] == 1) && jumpFlag == false && !playerConfusionFlag)								//B�{�^���������ꂽ��
			{
				noActionCounter = 0;
				jumpFlag = true;																//�W�����v�\�ɂ���
				PlaySoundMem(jumpSound, DX_PLAYTYPE_BACK);
				playerYPrev = playerY;															//�O����W�Ɍ��ݍ��W��ۑ�����
				playerY -= JumpPower;															//�W�����v�͂ō��W�ړ�����
			}
			if (jumpFlag == true || playerConfusionFlag == TRUE && jumpFlag == true)																//�W�����v�\�Ȃ��
			{
				if (!playerConfusionFlag)
				{
					playerImg = playerJump[frameCounter6];					//���@�\�����W�����v�ɂ���
				}
				playerYTemp = playerY;															//���݂�y���W���ꎞ�ۑ�����
				playerSpeedY = (playerY - playerYPrev) + gravity;                                         // y�����̑��x���߂�
				playerSpeedY = (playerSpeedY > MaxVy) ? MaxVy : playerSpeedY;

				playerY += playerSpeedY;			                                 						//���݂�y���W��O��y���W�Ƃ̍������������ďd�͒l������
				playerYPrev = playerYTemp;
				//�O��̍��W�Ƃ��Ĉꎞ�ۑ��̍��W��ۑ�����				
			}



			//---
			//�G�@�t���O
			//---
			for (int i = 0; i < enemy_num_max; i++)
			{
				if (enemyAliveFlag[i] == FALSE)
				{
					enemyX[i] = Enemy_FirstX[i];
				}
				if ((playerX - Player_StopPosition_X) - Enemy_Width[i] < enemyX[i] && enemyX[i] < 1920 + (playerX - Player_StopPosition_X))		//�����G����ʓ��ɓ�������	//�G�T�C�Y���͗]�T����������
				{
					if (enemyX[i] < (playerX - Player_StopPosition_X - Enemy_Width[i]) || enemyX[i] > 1920 + (playerX - Player_StopPosition_X) - Enemy_Width[i])
					{
						enemyAliveFlag[i] = TRUE;
					}
				}
				else
				{
					enemyAliveFlag[i] = FALSE;			//��ʊO�Ȃ����
				}
			}
			////�G�@�@�}�b�v�ɂ��N������
			for (int i = 0; i < enemy_num_max; i++)
			{
				if (enemySwitchFlag[i] == 1 && mapChangeFlag)		//�}�b�v1�݂̂ŗN�����̂��}�b�v2�̎�
				{
					enemyAliveFlag[i] = FALSE;
				}
			}
			//---
			//�G�@�ړ�
			//---

			for (int i = 0; i < enemy_num_max; i++)								//�G����ʓ��ɓ������瓮���悤�ɂ���
			{
				if (enemyAliveFlag[i] == TRUE)
				{
					enemyMove(enemyX[i], enemyY[i], enemySpeedX[i], enemySpeedY[i], spownPosi[i], enemyReverse[i]);
				}
			}
			//---
			//�G�@�Ǝ��@�@�����蔻��E�}�b�v�_���[�W
			//---
			for (int i = 0; i < enemy_num_max; i++)
			{
				if (!playerConfusionFlag && !playerInvincibleFlag && enemyAliveFlag[i])						//�����v���C���[��������,���G��ԂłȂ������蔻��̑ΏۂƂȂ�G�����݂����
				{
					//�L�����p�����蔻��֐�
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
				//�}�b�v�C�x���g
				//---
				if (!mapChangeFlag)
				{
					//�}�b�v�_���[�W�i�����������̏����͏�Ɠ����j
					if (characterCollision(3776 - Img_BlankX, 800, 96 + 32, 32,
						playerX, playerY, Player_Width - Img_BlankX, Player_Height))
					{
						playerConfusionFlag = TRUE;
						jumpFlag == true;
						playerHP-=20;
					}

					//�}�b�v�������ړ�//�}�b�v1�̉��̍��ړ�
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
				playerImg = playerDamaged[frameCounter2];					//���@�\�����e�ɂ���
				if (!playerReverse)											//�G�@�ɑ΂��ē������������̋t�Ɉړ�����i���˕Ԃ�j
				{
					playerX -= 1;											//���ɒ��˕Ԃ�
				}
				else
				{
					playerX += 1;											//�E�ɒ��˕Ԃ�
				}
				playerY += 1;												//�ǂ������瓖�����Ă����ɗ�����

				canNotControllCount++;													//����s�\���ԗp�J�E���g
				if (canNotControllCount >= 25)
				{
					playerConfusionFlag = FALSE;							//����s�\���Ԃ̃J�E���g���I�����������Ԃ����ǂ���
					playerInvincibleFlag = TRUE;							//�v���C���[�𖳓G�ɂ���B
					canNotControllCount = 0;
				}
			}
			if (playerInvincibleFlag)									//�v���C���[�����G���Ȃ�
			{
				canNotControllCount++;													//���G���Ԃ��I�����邽�߂ɃJ�E���g����
				if (canNotControllCount >= 50)											//�J�E���g��50�ɂȂ�����
				{
					playerInvincibleFlag = FALSE;							//���G�𖳌��ɂ�
					canNotControllCount = 0;												//�J�E���g�𖳌��ɂ���
				}
			}
			//---
			//�^�C���Ƃ̓����蔻��
			//---
			if (!mapChangeFlag)
			{
				collision->ColAll();			//�^�C���Ƃ̓����蔻��
			}
			else
			{
				collision2->ColAll2();
			}
			//---
			//��ʍ������蔻��
			//---
			if (playerX - Img_BlankX <= mapProceedX)							//��ʍ��Ɠ������Ă�����
			{
				playerLeftSpeed = 0;					//���ړ����ł��Ȃ�����
				if (playerX < mapProceedX && playerX > -Img_BlankX)		//�߂荞��ł�����߂�
				{
					playerX = mapProceedX;
				}
			}
			else										//�����Ŗ�����΍��ړ����x�����ɖ߂�
			{
				playerLeftSpeed = Player_FirstSpeed;
			}
			//---
			//��ʉ��Q�[���I�[�o�[����
			//---
			if (playerY >= 1200)
			{
				playerFlag = false;						//�v���C���[�𖳌�������
			}

			//---
			//�X�N���[���֌W�E���@�`��ʒu��`		//�^�C���Ƃ̓����蔻���ɒ�`����K�v������
			//---
			//�J�n�����ʒ����܂ł̃X�N���[���Ȃ��̕���
			if (0 <= playerX && playerX < Player_StopPosition_X)
			{
				playerBackX = 0;
				scrollFlag = FALSE;
			}
			else if (Scroll_Stop_Position <= playerX)		//�}�b�v��ԉE�ɗ�����
			{
				playerBackX = Scroll_Stop_Position - Player_StopPosition_X;		//���@����ʕ\����~�ʒu����E�ɍs����悤�ɂ���
				scrollFlag = FALSE;												//�w�i�̃X�N���[�����~����
			}
			else											//�ʏ�ړ�
			{
				playerBackX = playerX - Player_StopPosition_X;			//���@�ړ����~�����悤�Ɍ���			////�v���C���[�̕`��ʒu�������Ē�~�ʒu�ɗ���悤�ɂ���
				//playerBackXTemp = playerBackX;							//���@�`�掞�̉�ʏ���W���ꎞ�I�ɋL��
				mapProceedX = playerBackX;								//�}�b�v�̕`��ʒu�ύX�ɂ��v���C���[�`��ʒu�ύX������
				//mapProceedXPrev = playerBackX;							//�}�b�v�̕`��ʒu�ύX���L������
				scrollFlag = TRUE;										//�X�N���[�����J�n����
			}


			//---
			//�}�b�v�ύX����
			//---
			if (CheckHitKey(KEY_INPUT_R) == 0 && input.Buttons[15] == 0)		//����R�L�[��������ĂȂ���Ή�����悤�ɂ���
			{
				rKeyFlag = FALSE;
			}
			////�}�b�v�ύX�s�ʒu��`
			if ((playerX >= 2560 && playerX <= 2752 && playerY >= 640 && playerY <= 832)||
				(playerX >= 2752 && playerX <= 2816 && playerY >= 770 && playerY <= 832)||
				(playerX >= 4896 && playerX <= 5000))
			{
				rKeyFlag = TRUE;
			}
			if ((CheckHitKey(KEY_INPUT_R) == 1 || input.Buttons[15] == 1) && !rKeyFlag && !playerConfusionFlag && !jumpFlag)	//R�L�[�t���O����������R�L�[��������v���C���[�������A�W�����v���łȂ����
			{
				rKeyFlag = TRUE;				//R�L�[�t���O��L���ɂ���
				//�}�b�v�ύX��`
				if (!mapChangeFlag)				//�}�b�v�ύX�t���O�������Ȃ�
				{
					mapChangeFlag = TRUE;
				}
				else
				{
					mapChangeFlag = FALSE;
				}
				//---
				//�}�b�v�ύX�����i��񂵁E�}�b�v�ύX�̃t�F�[�h�C���E�t�F�[�h�A�E�g�j
				//---
				PlaySoundMem(warpSound, DX_PLAYTYPE_BACK);
				const int First_Light = 255;
				const int First_Deep = 0;
				for (int deep = First_Deep; deep <= 255; deep += 3)					//deep�ŉ摜��Z�䂭���Ă���
				{
					//light�ŉ摜�𔖂����Ă���
					ClearDrawScreen();
					

					if (!mapChangeFlag)
					{
						//�摜�P�Z�䂭
						enemyAliveFlag[3] = 1;
						SetDrawBlendMode(DX_BLENDMODE_ALPHA, deep);
						DrawGraph(backgroundX, backgroundY, backgroundImg, FALSE);
						DrawGraph(secondBackgroundX, backgroundY, backgroundImg, FALSE);
						map->All();
						//�摜�Q����
						SetDrawBlendMode(DX_BLENDMODE_ALPHA, First_Light - deep);
						DrawGraph(backgroundX, backgroundY, backgroundImg2, FALSE);
						DrawGraph(secondBackgroundX, backgroundY, backgroundImg2, FALSE);
						map2->All2();;

					}
					else
					{
						//�摜2�Z�䂭
						SetDrawBlendMode(DX_BLENDMODE_ALPHA, deep);
						DrawGraph(backgroundX, backgroundY, backgroundImg2, FALSE);
						DrawGraph(secondBackgroundX, backgroundY, backgroundImg2, FALSE);
						map2->All2();;
						//�摜�P����
						SetDrawBlendMode(DX_BLENDMODE_ALPHA, First_Light - deep);
						DrawGraph(backgroundX, backgroundY, backgroundImg, FALSE);
						DrawGraph(secondBackgroundX, backgroundY, backgroundImg, FALSE);
						map->All();;

					}

					//���@�`��
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
					DrawRotaGraph(playerX - playerBackX, playerY, 2.0f, 0, playerMapChangeImg, TRUE, FALSE);			//���@�`��
					DrawRotaGraph(playerX - playerBackX + 32, playerY - 16, 2.5f, 0, ring[deep % 10], TRUE, 0);


					ScreenFlip();
				}
				StopSoundMem(warpSound);
			}


			//---
			//�`�揈��
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


			//�w�i�摜�X�N���[���̃��[�v����
			if (secondBackgroundX <= 0)								//����2�ڂ̔w�i����ʍ��[�ɗ�����
			{
				backgroundX = 0;									//�w�i�̈ʒu�������ʒu�ɖ߂�
				secondBackgroundX = Second_Background_X;
			}
			if (backgroundX > 0)										//����1�ڂ̔w�i���E�Ɉړ�������
			{
				secondBackgroundX = -1920;
				backgroundX = 0;
			}
			if (!mapChangeFlag)								//�}�b�v�`��
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
			//���@�`��
			//---
			if (!playerInvincibleFlag)		//�������G��ԂłȂ���Ε��ʂɕ\������
			{
				DrawRotaGraph(playerX - playerBackX, playerY, 2.0f, 0, playerImg, TRUE, playerReverse);			//���@�`��
			}
			else							//�����Ŗ������
			{
				if (timeCounter % 2 == 0)	//�^�C���J�E���^�������̎��v���C���[��\������
				{
					DrawRotaGraph(playerX - playerBackX, playerY, 2.0f, 0, playerImg, TRUE, playerReverse);
				}
			}
			if (playerConfusionFlag == TRUE)
			{
				DrawRotaGraph(playerX - playerBackX, playerY - 32, 2.0f, 0, ConfusionImg, TRUE);		//���@�����摜
			}


			//---
			//�����O�`��
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
			//�G�@�`��
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
			//�����\��
			//---
			SetFontSize(32);
			DrawFormatString(1800, 40, GetColor(255, 255, 255), "%d", countDown = count_down_first - time / 60);

			////�̗̓Q�[�W�\��
			DrawBox(810, 30, 810 + playerHP * 3, 77, GetColor(0, 255, 0), TRUE);
			DrawGraph(810, 30, hpGaugeImg, TRUE);
			SetFontSize(16);
			DrawFormatString(945, 45, GetColor(255, 255, 255), "%d", playerHP);
			////������@�\��
			if (!controllDontShowFlag)
			{
				if (noActionCounter >= controllSaidTime)
				{
					if (saidDark <= 200)
					{
						saidDark += 5;
					}
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, saidDark);		//�\������摜��Z�䂭����
					DrawGraph(0, 1080 - 124, controllImg, TRUE);
				}
				else
				{
					saidDark = 0;

					SetDrawBlendMode(DX_BLENDMODE_ALPHA, saidDark);		//�\������摜��Z�䂭����
					DrawGraph(0, 1080 - 124, controllImg, TRUE);
				}
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);				//���̂܂܂��Ƒ��̕\���������Ȃ�̂Ń��Z�b�g����A������@�ɂ͉e�����Ȃ�
			}


			//---
			//�Q�[����Ԕ���
			//---
			//�Q�[���I�[�o�[����
			if (playerFlag == FALSE || playerHP <= 0 || countDown <= 0)
			{
				gameStatus = OVER;
				//BGM
				PlaySoundMem(overBgm, DX_PLAYTYPE_LOOP);
			}
			//---
			//�N���A����
			//---
			if (playerX >= Player_EndPosition_X && mapChangeFlag == TRUE)
			{
				gameStatus = CLEAR;
				//BGM
				PlaySoundMem(clearBgm, DX_PLAYTYPE_LOOP);
			}


			//---
			//�m�F�p
			//---
			if (checkFlag)
			{
				////���@
				//����@�E���@������ʒu�m�F
				int left = playerX - Img_BlankX - playerBackX;
				int right = playerX + Player_Width - Img_BlankX - playerBackX;
				int over = playerY - Img_BlankY;
				int under = playerY + Player_Height;
				int circleSize = 5;

				//���E�E
				DrawCircle(left, playerY, circleSize, GetColor(255, 0, 0));
				DrawCircle(right, playerY, circleSize, GetColor(255, 0, 0));
				//�l�p�\��
				DrawLine(left, over, left, under, GetColor(0, 0, 255));		//��
				DrawLine(right, over, right, under, GetColor(0, 0, 255));	//�E
				DrawLine(left, over, right, over, GetColor(0, 0, 255));		//��
				DrawLine(left, under, right, under, GetColor(0, 0, 255));	//��


				////�G�@
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
				//�}�b�v�C�x���g�ʒu�𔠂ŕ\��
				//---
				////�}�b�v�_���[�W
				if (!mapChangeFlag)
				{
					DrawBox(3776 - playerBackX, 800, 3776 + 96 - playerBackX, 832, GetColor(255, 0, 0), TRUE);
				}
				////�}�b�v�������ړ�
				if (!mapChangeFlag)
				{
					DrawBox(576 - playerBackX, 960, 1728 - playerBackX, 1056, GetColor(255, 0, 0), TRUE);
				}
				//DrawBox(0, 0, 1980, 128, GetColor(255, 255, 255), TRUE);
				////�}�b�v�ύX�֎~�ʒu
				DrawBox(2560 - playerBackX, 640, 2752 - playerBackX, 832, GetColor(0, 255, 0), TRUE);
				DrawBox(2752 - playerBackX, 770, 2816 - playerBackX, 832, GetColor(0, 255, 0), TRUE);
				DrawBox(4896 - playerBackX, 0, 5536 - playerBackX, 1080, GetColor(0, 255, 0), TRUE);

				//���s���m�F�p
				DrawString(100, 30, "�m�F�p", playerX, GetColor(255, 0, 0));
				DrawFormatString(playerX - playerBackX - 130, playerY - 50, GetColor(255, 0, 0), "(X:%d,Y:%d)", playerX, playerY);
				DrawFormatString(100, 50, GetColor(255, 0, 0), "X(�`��) : %d", playerX - playerBackX);
				DrawFormatString(100, 70, GetColor(255, 0, 0), "playerReverse : %d", playerReverse);
				DrawFormatString(100, 90, GetColor(255, 0, 0), "jumpFlag : %d", jumpFlag);
			}


			ScreenFlip();


			if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
			{
				gameStatus = END;
			}

			//�J���p
			if (checkFlag)
			{
				stateChange();
			}
		}
		WaitTimer(100);


		//---
		//�Q�[���I�[�o�[
		//---
		while (!ProcessMessage() && gameStatus == OVER)
		{
			//BGM��~
			StopSoundMem(playBgm);
	

			//�p�b�h���͓ǂݍ���
			GetJoypadXInputState(DX_INPUT_PAD1, &input);

			ClearDrawScreen();

			StopSoundMem(playBgm);

			DrawGraph(0, 0, overImg, FALSE);

			SetFontSize(128);
			DrawString(550, 400, "�Q�[���I�[�o�[", GetColor(0, 255, 0));
			//SetFontSize(32);
			//DrawString(700, 550, "�����͂��ꂽ����ƂɋA�������", GetColor(0, 255, 0));
			SetFontSize(64);
			DrawString(700, 600, "START�Ń^�C�g����!", GetColor(0, 255, 0));
	
			ScreenFlip();
			
			if (CheckHitKey(KEY_INPUT_SPACE) == 1 || input.Buttons[4] == 1)
			{
				gameStatus = TITLE;
			}
			if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
			{
				gameStatus = END;
			}

			//�J���p
			if (checkFlag)
			{
				stateChange();
			}
		}
		WaitTimer(100);


		//---
		//�N���A
		//---
		while (!ProcessMessage() && gameStatus == CLEAR)
		{
			//BGM��~
			StopSoundMem(playBgm);


			//�p�b�h���͓ǂݍ���
			GetJoypadXInputState(DX_INPUT_PAD1, &input);

			StopSoundMem(playBgm);

			ClearDrawScreen();

			DrawGraph(0, 0, backgroundImg2, TRUE);
			mapProceedX = 3500;
			map2->All2();
			SetFontSize(128);
			DrawString(750, 400,"�N���A", GetColor(0, 0, 255));
			SetFontSize(64);
			DrawFormatString(730, 535, GetColor(0, 0, 255), "SCORE : %d", (playerHP / 20 * 5000) + (countDown * 500));
			DrawString(700, 600, "START�Ń^�C�g����", GetColor(0, 0, 255));
			

			ScreenFlip();

			if (CheckHitKey(KEY_INPUT_SPACE) == 1 || input.Buttons[4] == 1)
			{
				gameStatus = TITLE;
			}
			if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
			{
				gameStatus = END;
			}

			//�J���p
			if (checkFlag)
			{
				stateChange();
			}
		}
		WaitTimer(100);


		//---
		//���[�v�I��
		//---
		while (!ProcessMessage() && gameStatus == END)
		{
			//BGM��~
			StopSoundMem(titleBgm);
			StopSoundMem(playBgm);
			StopSoundMem(clearBgm);
			StopSoundMem(overBgm);


			//---
			//�}�b�v�^�C�����
			//---
			delete map;
			delete map2;
			delete collision;
			delete collision2;
			//delete map3;

			//NULL���
			map = NULL;
			map2 = NULL;
			collision = NULL;
			collision2 = NULL;

			break;						//���[�v���甲����
		}

		if (gameStatus == END)			//�Q�[����Ԃ�END�Ȃ�I������
		{
			break;
		}

	}


	DxLib_End();		//�I��

	runLauncher("../../");

	return 0;
}

//4600