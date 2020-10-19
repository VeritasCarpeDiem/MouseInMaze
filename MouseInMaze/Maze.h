#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include "Stack.h"
#include <mmsystem.h>
#include "changeColor.h"
#include "XY.h"

#pragma comment(lib, "Winmm.lib") //static windows library for playing .wav music files
using namespace std;

class Maze
{
private:
	const static int rows = 30;
	const static int columns = 100;
public:
	//0 = path 1 = wall 2 = Cat 3 = exit 4 = visited

	int maze[rows][columns];
	int xpos;
	int ypos;
	int catX;
	int catY;
	int direction;
	Stack MouseStack;
	Stack CatStack[10];

	Maze(); //constructor

	void LoadMaze(string file);//Loads maze from file and Displays it 
	 
	void MoveMouse(); //function to move the mouse

	void Backtrack(int space);

	void changeDirection(); //function to change mouse's direction

	bool checkSpaces(); //checks to see if there are any open spaces above, below, to the left, or to the right
	
	bool checkNext(); //checks the space in front of the mouse to see if it's free

	void SolveMaze(); //Solves the maze

	void addCat();

	void MoveCat(int totalCats);

	bool CatcheckNext();

	bool CatcheckSpaces();

	void CatBacktrack(int spaces);
};

