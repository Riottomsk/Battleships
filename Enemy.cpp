#include "Enemy.h"

#include "InputSystem.h"
#include <ranges>

Enemy::Enemy()
    : mFoggedBoard(BasePlayer::getBoard().size(), std::vector<int>(BasePlayer::getBoard().size(), 0))
{
}

void Enemy::makeAMove(const InputSystem& inputSystem, int& row, int& col)
{
    inputSystem.makeRandomMove(row, col);
}

const Board::BoardType& Enemy::getBoard()
{
    //printf("Enemy:getBoard is called");

    //auto& board = BasePlayer::getBoard();

    //auto foggedBoard = board | std::ranges::views::transform([](int i) { return i > 0 ? 0 : i; });

    //auto foggedBoard = board | std::views::transform([](const std::vector<int>& row) { return std::views::transform([](int i) { return i > 0 ? 0 : i; }); });

    //return foggedBoard;

    //return BasePlayer::getBoard();

    auto& mainBoard = BasePlayer::getBoard();
    //memcpy(mFoggedBoard.data(), mainBoard.data(), mainBoard.size() * sizeof(mainBoard[0]));

    //for (auto&& row : mainBoard)
    for (size_t r = 0; r < mainBoard.size(); ++r)
    {
        //for (auto&& spot : row)
        for(size_t c = 0; c < mainBoard.size(); ++c)
        {
            //if (mainBoard[r][c] == mFoggedBoard[r][c])
            //{
            //    continue;
            //}

            mFoggedBoard[r][c] = mainBoard[r][c];

            if (mainBoard[r][c] > 0)
            {
                mFoggedBoard[r][c] = 0; // hide standing ship from the view
            }

            //if (mainBoard[r][c] > -2)
            //{
            //    mFoggedBoard[r][c] = 1; // for better representation
            //}

            //if (spot > 0)
            //{
            //    spot = 0; // hide standing ship from the view
            //    continue;
            //}

            //if (spot == -2)
            //{
            //    spot = 1; // for better representation
            //}
        }
    }

    return mFoggedBoard;
}

//Board::BoardViewType Enemy::getBoardView()
//{
//    using namespace std::ranges::views;
//    //auto tr = transform([](int i) { return i > 0 ? 0 : i; });
//    auto tr_view = BasePlayer::getBoardView() | transform([](auto row) { return row | transform([](int i) { return i > 0 ? 0 : i; }); });
//
//    std::ranges::ref_view view = { tr_view };
//
//    return view;
//}
