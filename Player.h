#pragma once

#include "BasePlayer.h"

class Player : public BasePlayer
{
public:
	void makeAMove(const InputSystem& inputSystem, int& row, int& col) override;
	const Board::BoardType& getBoard() override;
};

