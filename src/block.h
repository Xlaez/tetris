#pragma once
#include <vector>
#include <map>
#include "position.h"
#include "colors.h"

class Block
{
public:
    int id;
    Block();
    void Draw();
    void Rotate();
    void UndoRotation();
    void Move(int rows, int columns);
    std::vector<Position> GetCellPositions();
    std::map<int, std::vector<Position>> cells;

private:
    int cellSize;
    int rotationState;
    int rowOffset;
    int colOffset;
    std::vector<Color> colors;
};