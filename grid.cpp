#include "grid.h"
#include <iostream>
#include "colors.h"

Grid::Grid(){

numrows = 20;
numcolmn = 10;
cellsize = 30;
Initialize();
colors = GetCellColors();

}

void Grid::Initialize(){

for(int row = 0; row < numrows; row++){
  for(int column = 0; column < numcolmn; column++){
   
    grid[row][column] = 0;
  
  }
}

}

void Grid::Print(){
  for(int row = 0; row < numrows; row++){
for(int column = 0; column < numcolmn; column++){
  std::cout << grid[row][column]<<" ";
}

std::cout << std::endl;
  }
}


void Grid::Draw()
{
for (int row = 0; row < numrows; row++){
for (int column = 0; column < numcolmn; column++){
  int cellValue = grid[row][column];
  DrawRectangle(column * cellsize+11, row * cellsize+11, cellsize-1, cellsize-1, colors[cellValue]);
}

}

}

bool Grid::IsCellOutside(int row, int column){
if(row >= 0 && row < numrows && column >= 0 && column < numcolmn){
return false;

}
  return true;
}
bool Grid::IsCellEmpty(int row, int column){

  if(grid[row][column] == 0){
return true;
  }
  return false;
}
int Grid::ClearfullRows(){
    int completed = 0;
    for(int row = numrows - 1; row >= 0; row--){
        if(IsRowFull(row)){
            ClearRow(row);
            completed++;
            for(int r = row - 1; r >= 0; r--){
                MoveRowDown(r, 1);
            }
            row++;
        }
    }
    return completed;
}


bool Grid::IsRowFull(int row){
for(int column = 0; column < numcolmn; column++){
  if(grid[row][column] == 0){
    return false;
  }
}
return true;
}

void Grid::ClearRow(int row){
for(int column = 0; column < numcolmn; column++){
grid[row][column] = 0;
}

}
void Grid::MoveRowDown(int row, int numRows){
  if(row + numRows < numrows){
    for(int column = 0; column < numcolmn; column++){
      grid[row + numRows][column] = grid[row][column];
      grid[row][column] = 0;
    }
  }
}

