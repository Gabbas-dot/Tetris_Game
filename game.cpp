#include "game.h"
#include <random>

Game::Game(){

  grid = Grid();
blocks = GetAllBlocks();
currentBlock = GetRandomBlock();
nextBlock = GetRandomBlock();
gameOver = false;
score = 0;

}

Block Game::GetRandomBlock(){

  if (blocks.empty()){
blocks = GetAllBlocks();
  }
  int randomIndex = rand() % blocks.size();
  Block block = blocks[randomIndex];
  blocks.erase(blocks.begin() + randomIndex);
  return block;
}

std::vector<Block> Game::GetAllBlocks(){

  return {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
}
void Game::Draw() {
  grid.Draw();
  currentBlock.Draw(11, 11);  // Draw current block in main grid

  // Default preview location
  int previewX = 255;
  int previewY = 280;

  // Offset adjustments for better centering in preview box
  switch (nextBlock.id) {
    case 0:  // I block
      previewX = 240;
      previewY = 260;
      break;
    case 1:  // J block
      previewX = 250;
      previewY = 270;
      break;
    case 2:  // L block
      previewX = 250;
      previewY = 270;
      break;
    case 3:  // O block
      previewX = 260;
      previewY = 300;
      break;
    case 4:  // S block
      previewX = 250;
      previewY = 280;
      break;
    case 5:  // T block
      previewX = 255;
      previewY = 275;
      break;
    case 6:  // Z block
      previewX = 250;
      previewY = 280;
      break;
  }

  nextBlock.Draw(previewX, previewY);  // Draw only once
}

void Game::HandleInput(){

int Keypressed = GetKeyPressed();
if(gameOver && Keypressed != 0){
  gameOver = false;
  Reset();
}
switch(Keypressed){
  case KEY_LEFT:
MoveBlockLeft();
break;
  case KEY_RIGHT:
MoveBlockRight();
break;
  case KEY_DOWN:
MoveBlockDown();
break;
  case KEY_UP:
RotateBlock();
break;
}
}

void Game::MoveBlockLeft(){
  if (!gameOver){
currentBlock.Move(0, -1);
if(IsBlockOutside()){
  currentBlock.Move(0, 1);
}
}
}
void Game::MoveBlockRight(){
  if (!gameOver){
currentBlock.Move(0, 1);
if (IsBlockOutside() || BlockFits() == false){
currentBlock.Move(0, -1);
}
}
}
void Game::MoveBlockDown(){
  if (!gameOver){
currentBlock.Move(1, 0);
if (IsBlockOutside() || BlockFits() == false){
  currentBlock.Move(-1, 0);
LockBlock();
}
}
}
bool Game::IsBlockOutside(){
  std::vector<Position> tiles = currentBlock.GetCellPositions();
for(Position item: tiles){
if (grid.IsCellOutside(item.row, item.column)){
  return true;
}
}return false;
}

void Game::RotateBlock(){
if (!gameOver){
currentBlock.Rotate();
if(IsBlockOutside() || BlockFits() == false){
currentBlock.UndoRotation();
}
}
}
void Game::LockBlock(){
  std::vector<Position> tiles = currentBlock.GetCellPositions();
for(Position item: tiles){
  grid.grid[item.row][item.column] = currentBlock.id;
  Updatescore(0, 1); 


}
currentBlock = nextBlock;
if(BlockFits() == false){
  gameOver = true;
}
nextBlock = GetRandomBlock();
int rowsCleared = grid.ClearfullRows();
Updatescore(rowsCleared, 0);
}
bool Game::BlockFits(){
  std::vector<Position> tiles = currentBlock.GetCellPositions();
for(Position item: tiles){
if(grid.IsCellEmpty(item.row, item.column) == false){
  return false;
}
}
return true;
}

void Game::Reset(){
grid.Initialize();
blocks = GetAllBlocks();
currentBlock = GetRandomBlock();
nextBlock = GetRandomBlock();
score = 0;
}
void Game::Updatescore(int linesCleared, int moveDownPoints){
switch(linesCleared){
	case 1:
		score += 100;
		break;

	case 2:
		score += 300;
		break;

	case 3:
		score += 500;
		break;
	default:
		break;
}

score += moveDownPoints;
}
