#include "LaberinthApp.h"
#include <random>

LaberinthApp::LaberinthApp(int w, int h)
{
	sAppName = "LaberinthSim";
	xCells = w / Cell::_cellWidth;
	yCells = h / Cell::_cellWidth;
	
}

bool LaberinthApp::OnUserCreate()
{
	FillRect(0, 0, ScreenWidth(), ScreenHeight(), olc::WHITE);
	for (int i = 0; i < xCells; i++)
	{
		for (int j = 0; j < yCells; j++)
		{
			_cells.push_back(Cell(i,j));
		}
	}
	_extendingCells.push_back(&_cells[0]);
	_cells[0]._explored = true;
	return true;
}

bool LaberinthApp::OnUserUpdate(float fElapsedTime)
{
	FillRect(0, 0, ScreenWidth(), ScreenHeight(), olc::BLACK);
	UpdateLaberinth();
	DrawLaberinth();
	DrawRect(0, 0, ScreenWidth(), ScreenHeight(), olc::BLACK);
	return true;
}

void LaberinthApp::DrawLaberinth() 
{
	for (Cell& cell : _cells)
	{
		cell.DrawCell(this);
	}
}

void LaberinthApp::UpdateLaberinth() 
{
	std::random_device rd;
	std::mt19937 gen(rd());
	if (_extendingCells.size() == 0) return;
	std::uniform_int_distribution<> tCellRange(0, _extendingCells.size() - 1);
	Cell *currentCell = _extendingCells[tCellRange(gen)];
	if (!currentCell->IsExtendible()) {
		_extendingCells.erase(std::remove_if(_extendingCells.begin(), _extendingCells.end(), [currentCell](Cell* cell) {return currentCell == cell; }));
		std::cout << "Removed cell" << std::endl;
		return;
	}
	int x = currentCell->_xPos;
	int y = currentCell->_yPos;
	std::uniform_int_distribution<> directionsRange(0, 3);
	Cell *targetCell;
	switch (Directions(directionsRange(gen)))
	{
	case Directions::UP:
		std::cout << "UP" << std::endl;
		if (currentCell->_paintDirs[Directions::UP]) return;
		currentCell->SetDirection(Directions::UP, false);
		if (y <= 0) return;
		targetCell = &_cells[x * yCells + (y - 1)];
		if (targetCell->_explored) return;
		currentCell->SetDirection(Directions::UP, true);
		targetCell->SetDirection(Directions::DOWN,true);
		break;
	case Directions::DOWN:
		std::cout << "DOWN" << std::endl;
		if (currentCell->_paintDirs[Directions::DOWN]) return;
		currentCell->SetDirection(Directions::DOWN,false);
		if (y >= yCells - 1) return;
		targetCell = &_cells[x * yCells + (y + 1)];
		if (targetCell->_explored) return;
		currentCell->SetDirection(Directions::DOWN, true);
		targetCell->SetDirection(Directions::UP,true);
		break;
	case Directions::LEFT:
		if (currentCell->_paintDirs[Directions::LEFT]) return;
		currentCell->SetDirection(Directions::LEFT,false);
		std::cout << "LEFT" << std::endl;
		if (x <= 0) return;
		targetCell = &_cells[(x - 1) * yCells + y];
		if (targetCell->_explored) return;
		currentCell->SetDirection(Directions::LEFT, true);
		targetCell->SetDirection(Directions::RIGHT,true);
		break;
	case Directions::RIGHT:
		if (currentCell->_paintDirs[Directions::RIGHT]) return;
		currentCell->SetDirection(Directions::RIGHT,false);
		std::cout << "RIGHT" << std::endl;
		if (x >= xCells - 1) return;
		targetCell = &_cells[(x + 1) * yCells + y];
		if (targetCell->_explored) return;
		currentCell->SetDirection(Directions::RIGHT, true);
		targetCell->SetDirection(Directions::LEFT,true);
		break;
	default:
		std::cout << "NOTHING" << std::endl;
		return;
		break;
	}
	_extendingCells.push_back(targetCell);
	targetCell->_explored = true;

	std::this_thread::sleep_for(std::chrono::milliseconds(10));
}
