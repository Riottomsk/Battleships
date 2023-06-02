#pragma once
#include "BasePlayer.h"

class Enemy : public BasePlayer
{
public:
	//using BoardType = std::vector<std::vector<int>>;

	Enemy();
	void makeAMove(const InputSystem& inputSystem, int& row, int& col) override;
	const Board::BoardType& getBoard() override;

	//Board::BoardViewType getBoardView() override;

private:
	Board::BoardType mFoggedBoard;
};

