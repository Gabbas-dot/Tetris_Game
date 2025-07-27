#pragma once

#include <vector>
#include <map>
#include "position.h"
#include "colors.h"

class Block{
  public:

    Block();
    void Draw(int offsetx, int offsety);
    void Move(int rows, int columns);                    
    std::vector<Position> GetCellPositions();
    void Rotate();
    void UndoRotation();
    int id;
    std::map<int, std::vector<Position>> cells;
  
  private: 
  int cellsize;
  int rotationState;
  std::vector<Color> colors;
  int rowOffset;
  int columnOffset;

};

