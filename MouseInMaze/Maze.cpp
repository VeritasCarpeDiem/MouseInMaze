#include "Maze.h"
#include <stdio.h> 
#include <stdlib.h> 
#include "conio.h"
#include "time.h"
Maze::Maze() //initialize variables and maze array
{
	catX = 0;
	catY = 0;
	xpos = 1;
	ypos = 1;
	direction = 1;
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 30; j++)
		{
			maze[j][i] = 0;
		}
	}
	maze[ypos][xpos] = 4;
	MouseStack.Push(ypos, xpos);
}

void Maze::LoadMaze(string file) //Loads maze from file and displays the walls, path, and exit
{
	XY xy;
	changeColor color;
	ifstream inFile;
	char c;
	inFile.open(file);
	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			inFile.get(c);
			maze[i][j] = (int)c - 48;
			xy.gotoXY(j, i);
			color.changeTextColor(7);

			if (maze[i][j] == 1)//Wall
			{
				cout << char(219);
			}
			else if (maze[i][j] == 0)//Path
			{
				cout << " ";
			}
			else if (maze[i][j] == 3) //Exit
			{
				color.changeTextColor(10);
				cout << char(176);
			}
		}
		inFile.get(c);
		cout << endl;
	}
	inFile.close();
	xy.gotoXY(xpos, ypos);
	color.changeTextColor(14);
	cout << char(255);
	xy.gotoXY(30, 30);
	cout << "Press c to add 1 cat" << endl;
}

void Maze::MoveMouse()//function to move the mouse
{
	XY xy;
	changeColor color;
	//Change direction in a clockwise motion
	//1 = Right	
	//2 = Down
	//3 = Left
	//4 = Up
	xy.gotoXY(xpos, ypos);
	cout << "-";
	MouseStack.Push(xpos, ypos);

	if (direction == 1)//move right
	{
		xpos++;
	}
	else if (direction == 2)//move down
	{
		ypos++;
	}
	else if (direction == 3)//moves left
	{
		xpos--;
	}
	else if (direction == 4)//moves up
	{
		ypos--;
	}
	xy.gotoXY(xpos, ypos);
	color.changeTextColor(14);
	cout << "M";
	if (maze[ypos][xpos] == 0) //if there is a path,set that position to visited
	{
		maze[ypos][xpos] = 4;
	}
	Sleep(50);
}

void Maze::Backtrack(int space)
{
	XY xy;
	xy.gotoXY(xpos, ypos);
	cout << " ";
	ypos = space / 100;
	xpos = space % 100;
	xy.gotoXY(xpos, ypos);
	cout << "M";
	Sleep(50);
}

void Maze::changeDirection() //function to change mouse's direction
{
	// 1 = right 2 = down 3 = left 4 = up
	if (direction == 1)
	{
		direction++;
	}
	else if (direction == 2)
	{
		direction++;
	}
	else if (direction == 3)
	{
		direction++;
	}
	else if (direction == 4)
	{
		direction = 1;
	}
}

bool Maze::checkSpaces()
{
	return (maze[ypos][xpos + 1] == 0 || maze[ypos][xpos + 1] == 3 ||
		maze[ypos - 1][xpos] == 0 || maze[ypos - 1][xpos] == 3 ||
		maze[ypos][xpos - 1] == 0 || maze[ypos][xpos - 1] == 3 ||
		maze[ypos + 1][xpos] == 0 || maze[ypos + 1][xpos] == 3);
}

bool Maze::checkNext() //0 = path 1 = wall 2 = Cat 3 = exit 4 = visited
{
	////Change direction in a clockwise motion
	////1 = Right	
	////2 = Down
	////3 = Left
	////4 = Up
	if (direction == 1)
	{
		return (maze[ypos][xpos + 1] == 0 || maze[ypos][xpos + 1] == 3 || maze[ypos][xpos + 1] == 2);
	}
	else if (direction == 2)
	{
		return (maze[ypos + 1][xpos] == 0 || maze[ypos + 1][xpos] == 3 || maze[ypos + 1][xpos] == 2);
	}
	else if (direction == 3)
	{
		return (maze[ypos][xpos - 1] == 0 || maze[ypos][xpos - 1] == 3 || maze[ypos][xpos - 1] == 2);
	}
	else if (direction == 4)
	{
		return (maze[ypos - 1][xpos] == 0 || maze[ypos - 1][xpos] == 3 || maze[ypos - 1][xpos] == 2);
	}
	return false;
}

void Maze::SolveMaze()
{
	XY xy;
	changeColor color;
	int totalCats = 0;
	while (maze[ypos][xpos] != 3 && maze[ypos][xpos] != 2)
	{
		//PlaySound(TEXT("BGmusic.wav"), NULL, SND_ASYNC | SND_LOOP);
		if (_kbhit())
		{
			char input = _getch();
			if (totalCats < 10 && (input == 'C' || input == 'c'))//create a cat if there are less than 10 total Cats
			{
				totalCats++;
				addCat();
			}
		}
		if (checkNext())
		{
			MoveMouse();
			if (totalCats > 0)
			{
				//MoveCat(totalCats);
			}
		}
		else if (checkSpaces())
		{
			changeDirection();
		}
		else
		{
			/*for (int i = 0; i < totalCats; i++)
			{
				CatBacktrack(CatStack[i].Pop());
			}*/
			Backtrack(MouseStack.Pop());
		}
	}
	if (maze[ypos][xpos] == 2) //ends game if mouse encounters Cat
	{
		system("cls");
		system("Color CE");
		xy.gotoXY(0, 0);
		for (int i = 0; i < 30; i++)
		{
			for (int j = 0; j < 100; j++)
			{
				cout << char(219);
			}
		}
		color.changeTextColor(12);
		xy.gotoXY(57, 10);

		xy.gotoXY(44, 12);
		cout << "You got caught by a cat!";
		PlaySound(TEXT("deathSound.wav"), NULL, SND_SYNC);
	}
	if (maze[ypos][xpos] == 3) //ends game with victory if maze solved with errors
	{
		system("cls");
		color.changeTextColor(Colors::GREEN);
		xy.gotoXY(50, 10);
		cout << "You did it!";
		PlaySound(TEXT("victory.wav"), NULL, SND_SYNC);
	}
}

void Maze::addCat()
{
	XY xy;
	changeColor color;
	do
	{
		//assign random coordinates to the cat
		srand((unsigned int)time(NULL));
		catY = rand() % 30;
		catX = rand() % 100;

	} while (maze[catY][catX] != 0 && maze[catY][catX] != 4 && maze[catY][catX] != maze[ypos][xpos]);
	//if there is an empty spot AND if its a spot the mouse didn't visit AND if its a position the mouse isn't at currently, add a Cat

	xy.gotoXY(catX, catY);
	maze[catY][catX] = 2;
	color.changeTextColor(Colors::RED);
	cout << "C";
	color.changeTextColor(14);
}

void Maze::MoveCat(int totalCats)
{
	XY xy;
	changeColor color;
	//Change direction in a clockwise motion
	//1 = Right	
	//2 = Down
	//3 = Left
	//4 = Up
	xy.gotoXY(catX, catY);

	for (int i = 0; i < totalCats; i++) //loop thru the Cat stack array
	{
		CatStack[i].Push(catX, catY);
	}

	if (direction == 1)//move right
	{
		catX++;
	}
	else if (direction == 2)//move down
	{
		catY++;
	}
	else if (direction == 3)//moves left
	{
		catX--;
	}
	else if (direction == 4)//moves up
	{
		catY--;
	}
	xy.gotoXY(catX, catY);
	color.changeTextColor(Colors::RED);
	cout << "C";
	if (maze[catY][catX] == 0) //if there is a path,set that position to visited
	{
		maze[catY][catX] = 4;
	}
	Sleep(50);
	color.changeTextColor(14);
}

bool Maze::CatcheckNext()//0 = path 1 = wall 2 = Cat 3 = exit 4 = visited
{
	////Change direction in a clockwise motion
	////1 = Right	
	////2 = Down
	////3 = Left
	////4 = Up
	if (direction == 1)
	{
		return (maze[catY][catX + 1] == 0 || maze[catY][catX + 1] == 3 || maze[catY][catX + 1] == 2);
	}
	else if (direction == 2)
	{
		return (maze[catY + 1][catX] == 0 || maze[catY + 1][catX] == 3 || maze[catY + 1][catX] == 2);
	}
	else if (direction == 3)
	{
		return (maze[catY][catX - 1] == 0 || maze[catY][catX - 1] == 3 || maze[catY][catX - 1] == 2);
	}
	else if (direction == 4)
	{
		return (maze[catY - 1][catX] == 0 || maze[catY - 1][catX] == 3 || maze[catY - 1][catX] == 2);
	}
	return false;
}

bool Maze::CatcheckSpaces()
{
	return (maze[catY][catX + 1] == 0 || maze[catY][catX + 1] == 3 ||
		maze[catY - 1][catX] == 0 || maze[catY - 1][catX] == 3 ||
		maze[catY][catX - 1] == 0 || maze[catY][catX - 1] == 3 ||
		maze[catY + 1][catX] == 0 || maze[catY + 1][catX] == 3);
}

void Maze::CatBacktrack(int space)
{
	XY xy;
	xy.gotoXY(catX, catY);
	cout << " ";
	catY = space / 100;
	catX = space % 100;
	xy.gotoXY(catX, catY);
	cout << "C";
	Sleep(50);
}

