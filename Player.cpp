#include "Player.h"

#include "InputSystem.h"

void Player::makeAMove(const InputSystem& inputSystem, int& row, int& col)
{
	inputSystem.getUserMove(row, col);
}

const Board::BoardType& Player::getBoard() 
{
	return BasePlayer::getBoard();
}
