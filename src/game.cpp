#include "game.h"
#include <random>

Game::Game()
{

    grid = Grid();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    gameOver = false;
}

Block Game::GetRandomBlock()
{

    if (blocks.empty())
    {
        GetAllBlocks();
    }

    int randomIndex = rand() % blocks.size();
    Block block = blocks[randomIndex];
    blocks.erase(blocks.begin() + randomIndex);
    return block;
}

std::vector<Block> Game::GetAllBlocks()
{
    return {IBlock(), JBlock(), ZBlock(), SBlock(), TBlock(), OBlock(), LBlock()};
}

void Game::Draw()
{
    grid.Draw();
    currentBlock.Draw();
}

void Game::HandleInput()
{
    int keyPressed = GetKeyPressed();
    if (gameOver && keyPressed != 0)
    {
        gameOver = false;
        ResetGame();
    }
    switch (keyPressed)
    {
    case KEY_LEFT:
        MoveBlockLeft();
        break;
    case KEY_RIGHT:
        MoveBlockRIght();
    case KEY_DOWN:
        MoveBlockDown();
        break;
    case KEY_UP:
        RotateBlock();
        break;
    }
}

void Game::MoveBlockLeft()
{
    if (!gameOver)
    {
        currentBlock.Move(0, -1);
        if (this->IsBlockOutside() || !BlockFits())
        {
            this->MoveBlockRIght();
        }
    }
}

void Game::MoveBlockRIght()
{
    if (!gameOver)
    {
        currentBlock.Move(0, 1);
        if (this->IsBlockOutside() || !BlockFits())
        {
            this->MoveBlockLeft();
        }
    }
}

void Game::MoveBlockDown()
{
    if (!gameOver)
    {
        currentBlock.Move(1, 0);
        if (this->IsBlockOutside() || !BlockFits())
        {
            currentBlock.Move(-1, 0);
            LockBlock();
        }
    }
}

bool Game::IsBlockOutside()
{
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position item : tiles)
    {
        if (grid.IsCellOutside(item.row, item.column))
        {
            return true;
        }
    }
    return false;
}

void Game::RotateBlock()
{
    if (!gameOver)
    {
        currentBlock.Rotate();
        if (IsBlockOutside() || !BlockFits())
        {
            currentBlock.UndoRotation();
        }
    }
}

void Game::LockBlock()
{
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position item : tiles)
    {
        grid.grid[item.row][item.column] = currentBlock.id;
    }
    currentBlock = nextBlock;

    if (!BlockFits())
    {
        gameOver = true;
    }

    nextBlock = GetRandomBlock();
    grid.ClearFullRows();
}

bool Game::BlockFits()
{
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position item : tiles)
    {
        if (grid.IsCellEmpty(item.row, item.column) == false)
        {
            return false;
        }
    }

    return true;
}

void Game::ResetGame()
{
    grid.Init();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
}