#include <iostream>
#include <Windows.h>
#include <fstream>
#include <string>
#include "conio.h"
#include "Maze.h"
#include "Stack.h"
#include "changeColor.h"
#include "XY.h"
#pragma comment(lib, "winmm.lib")

using namespace std;

int main()
{
	changeColor color;
	XY xy;
	Maze M;

	color.changeTextColor(7);
	
	M.LoadMaze("maze.txt");
	M.SolveMaze();
	xy.gotoXY(0,24);
	color.changeTextColor(7);
	
	return 0;
}