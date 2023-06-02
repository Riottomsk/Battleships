#include "BasePlayer.h"

int BasePlayer::hit(int row, int col)
{
	return mBoard.hit(row, col);
}

const Board::BoardType& BasePlayer::getBoard()
{
	return mBoard.getBoard();
}

//Board::BoardViewType BasePlayer::getBoardView()
//{
//	return mBoard.getBoardView();
//}
