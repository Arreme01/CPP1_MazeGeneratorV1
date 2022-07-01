#pragma once
#include "../olcPixelGameEngine.h"

enum Directions
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class Cell
{
public:
	static const int _cellWidth = 5;
	int _xPos;
	int _yPos;
	bool _explored = false;
	bool _dirs[4] = { false,false,false,false };
	bool _paintDirs[4] = { false,false,false,false };
public:
	explicit Cell(int xPos, int yPos) : _xPos(xPos), _yPos(yPos) 
	{
	}
	void DrawCell(olc::PixelGameEngine* engine);

	void SetDirection(int dir,bool paint);

	void ResetDirection(int dir);

	bool IsExtendible();
};

