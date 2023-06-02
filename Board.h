#pragma once

#include <memory>
#include <vector>
#include <ranges>

#include "Ship.h"

//class Ship;

class Board
{
public:
	using BoardType = std::vector<std::vector<int>>;

//public:
//	BoardType mBoard; // I'm getting error C2065. For whatever reason decltype fails if identifier is placed below it.
//public:
//	using BoardViewType = decltype(mBoard | std::views::all);

	Board();

	int hit(int x, int y);
	
	const BoardType& getBoard() const;

	//BoardViewType getBoardView();// -> decltype(mBoard | std::views::all);

private:
	bool _placeHere(int size, int row, int col, bool isHorizontal);
	void _addShipRandomly(int size);
	void _placeShipsRandomly();
	bool _finished() const;
	void _cleanSpacing();
	void _putSpacingAroundKilledShip(int row, int col, int shipId);

	BoardType mBoard;
	//std::vector<std::vector<int>> mBoard;

	std::vector<std::unique_ptr<Ship>> mShips;
};

