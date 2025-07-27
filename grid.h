#pragma once
#include <vector>
#include <raylib.h>

class Grid{
  public:
    Grid(); 
    void Initialize();
    void Print();
    void Draw();
    bool IsCellOutside(int row, int column);
    bool IsCellEmpty(int row, int column);
    int ClearfullRows();
    int grid[20][10];
  private:
    bool IsRowFull(int row);
    void ClearRow(int row);
    void MoveRowDown(int row, int numRows);
    int numrows;
    int numcolmn;
    int cellsize;
    std::vector<Color> colors;

};
