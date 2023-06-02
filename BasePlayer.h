#pragma once

#include "Board.h"
#include <ranges>
#include <functional>

class InputSystem;

class BasePlayer
{
public:
	//using CrypticType = std::ranges::transform_view<Board::BoardViewType, std::function<v>;

	BasePlayer() = default;
	virtual void makeAMove(const InputSystem& inputSystem, int& row, int& col) = 0;
	int hit(int row, int col);
	virtual const Board::BoardType& getBoard();
	//virtual Board::BoardViewType getBoardView();

	std::vector<int> vec;

	//auto getTransformedBoardView() -> decltype( vec | std::ranges::views::transform);
private:
	Board mBoard;
};

