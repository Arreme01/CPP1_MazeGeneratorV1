#include "Cell.h"

void Cell::DrawCell(olc::PixelGameEngine* engine) 
{
	engine->FillRect(_cellWidth*_xPos+1,_cellWidth*_yPos+1,3,3,olc::WHITE);
	if (_paintDirs[Directions::DOWN]) engine->FillRect(_cellWidth * _xPos + 1, _cellWidth * _yPos + 4, 3, 1, olc::WHITE);
	if (_paintDirs[Directions::UP]) engine->FillRect(_cellWidth * _xPos + 1, _cellWidth * _yPos, 3, 1, olc::WHITE);
	if (_paintDirs[Directions::RIGHT]) engine->FillRect(_cellWidth * _xPos + 4, _cellWidth * _yPos + 1, 1, 3, olc::WHITE);
	if (_paintDirs[Directions::LEFT]) engine->FillRect(_cellWidth * _xPos, _cellWidth * _yPos + 1, 1, 3, olc::WHITE);
}

void Cell::SetDirection(int dir,bool paint) 
{
	_dirs[dir] = true;
	_paintDirs[dir] = paint;
}

void Cell::ResetDirection(int dir)
{
	_dirs[dir] = false;
	_paintDirs[dir] = false;
}

bool Cell::IsExtendible() 
{
	for (size_t i = 0; i < 4; i++)
	{
		if (!_dirs[i]) {
			return true;
		}
	}

	return false;
}
