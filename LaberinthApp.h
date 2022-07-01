#pragma once
#include <vector>
#include "olcPixelGameEngine.h"
#include "Cells/Cell.h"

class LaberinthApp : public olc::PixelGameEngine
{
private:
	int xCells;
	int yCells;
	std::vector<Cell> _cells;
	std::vector<Cell *> _extendingCells;
public:
	LaberinthApp(int, int);
public:
	bool OnUserCreate() override;

	bool OnUserUpdate(float fElapsedTime) override;

	void DrawLaberinth();

	void UpdateLaberinth();
};

