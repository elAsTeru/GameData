#include"function.h"


void stateChange()
{
	//ÉQÅ[ÉÄèÛë‘ïœçX
	if (CheckHitKey(KEY_INPUT_T) == 1)
	{
		gameStatus = TITLE;
	}
	if (CheckHitKey(KEY_INPUT_I) == 1)
	{
		gameStatus = INIT;
	}
	if (CheckHitKey(KEY_INPUT_O) == 1)
	{
		gameStatus = OVER;
	}
	if (CheckHitKey(KEY_INPUT_C) == 1)
	{
		gameStatus = CLEAR;
	}
	if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
	{
		gameStatus = END;
	}
}