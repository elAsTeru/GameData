#include"move.h"

//�E�ړ�
void moveRight(int& charaX, int speedX, int& reverse)
{
	charaX += speedX;
	reverse = 0;
}
void moveLeft(int& charaX, int speedX, int& reverse)
{
	charaX -= speedX;
	reverse = 1;
}


//�G�@�ړ����@�ƈړ�
void enemyMove(int& x, int& y, int& speedX, int& speedY, const int spownPosi, int& reverse)
{

	if (spownPosi == 0)
	{
		if (x <= 1200 || x >= 1679)
		{
			if (speedX < 0)				//�E�Ɉړ����Ă�����
			{
				speedX = -speedX;
				reverse = 0;
			}
			else
			{
				speedX = -speedX;
				reverse = 1;
			}
		}
	}
	if (spownPosi == 2)
	{
		if (x <= 2832 || x >= 3525)
		{
			if (speedX < 0)				//�E�Ɉړ����Ă�����
			{
				speedX = -speedX;
				reverse = 0;
			}
			else
			{
				speedX = -speedX;
				reverse = 1;
			}
		}
	}

	x += speedX;
	y += speedY;

}