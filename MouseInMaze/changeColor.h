#pragma once
#include <Windows.h>

enum class Colors //strongly typed class of enum colors 
{

	//Explanation: The 2 hexadecimal values Foreground_Intensity(0x0008) and Foreground_blue(0x0001) are added(the "|" or operator) and
	//				produces Blue(0x0009). The value 9 is then assigned to Blue in a enum class 

	//(copied from microsoft website)
	BLUE = FOREGROUND_INTENSITY | FOREGROUND_BLUE,
	GREEN = FOREGROUND_INTENSITY | FOREGROUND_GREEN,
	CYAN = FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE,
	RED = FOREGROUND_INTENSITY | FOREGROUND_RED,
	MAGENTA = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE,
	YELLOW = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN,
	WHITE = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
};

class changeColor
{
public:
	
	void changeTextColor(int color)//function to change text color
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color); //cast the enum to int color
	}

	//overloaded function
	//this allows me to enter a color of type Colors class for code readibility
	//ex. changeTextcolor(Colors:: WHITE);
	void changeTextColor(Colors color)
	{
		changeTextColor((int)color); //cast color to int
	}
};

