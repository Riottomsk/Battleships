#include "Board.h"

#include <assert.h>
#include "Settings.h"
//#include "Ship.h"
#include <random>
#include "Utils.h"

#include <iostream>
#include <format>

Board::Board()
	: mBoard(std::vector<std::vector<int>>(Settings::getInstance().boardSize, std::vector<int>(Settings::getInstance().boardSize,0)))
{
    _placeShipsRandomly();
}

int Board::hit(int row, int col)
{
    if (row < 0 || col < 0 || row >= mBoard.size() || col >= mBoard[0].size() || mBoard[row][col] < 0)
    {
        return -1; // bad move
    }

    if (mBoard[row][col] > 0)
    {
        int shipId = mBoard[row][col];
        
        if (shipId > Settings::getInstance().numShips)
        {
            throw "Unexpected ShipId";
        }

        bool isStillAlive = mShips[shipId - 1]->hit();

        mBoard[row][col] = -2; // hit

        if (_finished())
        {
            return 3; // victory
        }

        if (isStillAlive)
        {
            return 1; // hit
        }

        _putSpacingAroundKilledShip(row, col, shipId);
        return 2; // kill
    }

    mBoard[row][col] = -1;

    return 0; // miss

}

const Board::BoardType& Board::getBoard() const
{
    return mBoard;
}

//auto Board::getBoardView() -> decltype(mBoard | std::views::all) {
//    return mBoard | std::views::all;
//}

bool Board::_placeHere(int size, int row, int col, bool isHorizontal)
{
    for (int i = 0; i < size; i++) {
        int r = row + (isHorizontal ? 0 : i);
        int c = col + (isHorizontal ? i : 0);
        if (r < 0 || 
            r >= mBoard.size() || 
            c < 0 || 
            c >= mBoard[0].size() || 
            mBoard[r][c] == 1 || 
            mBoard[r][c] == -1 ||
            (r > 0 && mBoard[r - 1][c] == -1) ||
            (r < mBoard.size() - 1 && mBoard[r+1][c] == -1) ||
            (c > 0 && mBoard[r][c - 1] == -1) ||
            (c < mBoard[0].size() - 1 && mBoard[r][c + 1] == -1)
            ) {
            return false;
        }

        if (r > 0 && mBoard[r - 1][c] == -1)
        {
            return false;
        }
    }

    int ship_id = mShips.size() + 1;
    mShips.emplace_back(std::make_unique<Ship>(size, ship_id));

    //int ship_id = mShips.back()->getId();


    // place the ship on the board
    for (int i = 0; i < size; i++) {
        int r = row + (isHorizontal ? 0 : i);
        int c = col + (isHorizontal ? i : 0);
        mBoard[r][c] = ship_id;
        mShips.back()->addCoord({ r, c });

        auto putSpacing = [&mBoard = mBoard](int r, int c)
        {
            if (r < 0 || r >= mBoard.size() || c < 0 || c >= mBoard[0].size())
            {
                return;
            }

            mBoard[r][c] = -1;
        };

        if (isHorizontal)
        {
            putSpacing(r - 1, c);
            putSpacing(r + 1, c);

            if (i == 0)
            {
                putSpacing(r - 1, c - 1);
                putSpacing(r, c - 1);
                putSpacing(r + 1, c - 1);
            }

            if (i == size - 1)
            {
                putSpacing(r - 1, c + 1);
                putSpacing(r, c + 1);
                putSpacing(r + 1, c + 1);
            }
        }
        else
        {
            putSpacing(r, c - 1);
            putSpacing(r, c + 1);

            if (i == 0)
            {
                putSpacing(r - 1, c - 1);
                putSpacing(r - 1, c);
                putSpacing(r - 1, c + 1);
            }

            if (i == size - 1)
            {
                putSpacing(r + 1, c - 1);
                putSpacing(r + 1, c);
                putSpacing(r + 1, c + 1);
            }
        }
    }

    return true;
}

void Board::_addShipRandomly(int size)
{
    // That's good only for dev. Throw instead?
    assert(size <= Settings::getInstance().boardSize);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> rowDist(0, mBoard.size() - 1);
    std::uniform_int_distribution<int> colDist(0, mBoard[0].size() - 1);

    int row, col;
    bool isHorizontal;
    bool isOverlap;

    do {
        // randomly select starting position and orientation of the ship
        row = rowDist(gen);
        col = colDist(gen);
        isHorizontal = (gen() % 2 == 0);

        // check if ship would overlap with any existing ships on the board
        isOverlap = !_placeHere(size, row, col, isHorizontal);
    } while (isOverlap);
}

void Board::_placeShipsRandomly()
{
    for (auto&& size : Settings::getInstance().shipSizes)
    {
        _addShipRandomly(size);
    }

    _cleanSpacing();
}

bool Board::_finished() const
{
    //// Bad way
    //for (auto&& row : board)
    //{
    //    for (auto&& v : row)
    //    {
    //        if (v == 1)
    //            return false;
    //    }
    //}

    // Better way
    for (auto&& ship : mShips)
    {
        if (ship->alive())
        {
            return false;
        }
    }

    return true;
}

void Board::_cleanSpacing()
{
    for (auto&& row : mBoard)
    {
        for (auto&& cell : row)
        {
            if (cell == -1)
            {
                cell = 0;
            }
        }
    }
}

void Board::_putSpacingAroundKilledShip(int row, int col, int shipId)
{
    auto putSpacing = [&board = mBoard](const Vec2& coord)
    {
        if (coord.x < 0 || coord.x >= board.size() || coord.y < 0 || coord.y >= board[0].size() || board[coord.x][coord.y] == -2)
        {
            return;
        }

        board[coord.x][coord.y] = -1;
    };

    auto putSpacingAround = [&putSpacing](const Vec2& coord)
    {
        putSpacing({ coord.x - 1, coord.y - 1 });
        putSpacing({ coord.x - 1, coord.y });
        putSpacing({ coord.x - 1, coord.y + 1 });

        putSpacing({ coord.x, coord.y - 1 });
        putSpacing({ coord.x, coord.y + 1 });

        putSpacing({ coord.x + 1, coord.y - 1 });
        putSpacing({ coord.x + 1, coord.y });
        putSpacing({ coord.x + 1, coord.y + 1 });
    };

    for (auto&& coord : mShips[shipId - 1]->getCoords())
    {
        //std::cout << std::endl <<std::format("{} {} {} {}", shipId, coord.x, coord.y, mBoard[coord.x][coord.y]);
        assert(mBoard[coord.x][coord.y] == -2);
        putSpacingAround(coord);
    }




    //assert(mBoard[row][col] == -2);

    //auto putSpacing = [&board = mBoard](int row, int col, int& nextRow, int& nextCol)
    //{
    //    if (row < 0 || row > board.size() || col < 0 || col > board[0].size())
    //    {
    //        return;
    //    }

    //    if (board[row][col] == -2)
    //    {
    //        nextRow = row;
    //        nextCol = col;
    //        return;
    //    }

    //    board[row][col] = -1;
    //};

    //auto putSpacingFindNext = [&board = mBoard, &putSpacing](int row, int col, int& nextRow, int& nextCol)
    //{
    //    //Vec2 next = { row, col };
    //    //int nextRow = row;
    //    //int nextCol = col;

    //    putSpacing(row - 1, col - 1, nextRow, nextCol);
    //    putSpacing(row - 1, col, nextRow, nextCol);
    //    putSpacing(row - 1, col + 1, nextRow, nextCol);

    //    putSpacing(row, col - 1, nextRow, nextCol);
    //    putSpacing(row, col + 1, nextRow, nextCol);

    //    putSpacing(row + 1, col - 1, nextRow, nextCol);
    //    putSpacing(row + 1, col, nextRow, nextCol);
    //    putSpacing(row + 1, col + 1, nextRow, nextCol);
    //};

    //int nextRow = row;
    //int nextCol = col;

    //do
    //{
    //    putSpacingFindNext(nextRow, nextCol, nextRow, nextCol);

    //} while (nextRow != row && nextCol != col);
}
