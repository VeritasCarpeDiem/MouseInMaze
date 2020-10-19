#include "XY.h"
#include <Windows.h>

void XY::gotoXY(int x, int y)
{
	if (x >= 0 && y >= 0)
	{
		COORD coord;
		coord.X = x;
		coord.Y = y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	}

}
