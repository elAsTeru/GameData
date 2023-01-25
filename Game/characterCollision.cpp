#include"characterCollision.h"

//ƒLƒƒƒ‰‚Q‘Ì‚Ì“–‚½‚è”»’è
int characterCollision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
{
	if (((x1 > x2&& x1 < x2 + w2) ||
		(x2 > x1&& x2 < x1 + w1)) &&
		((y1 > y2&& y1 < y2 + h2) ||
		(y2 > y1&& y2 < y1 + h1)))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}