#pragma once

#include <vector>
#include <ranges>

#include "Utils.h"

class Ship
{
public:
	Ship(int size, int id);

	int getId() const;
	bool hit();
	bool alive() const;

	void addCoord(const Vec2& coord);
private:
	int mSize;
	int mHealth;
	int mId;

	std::vector<Vec2> mCoords;

	//static int shipNum;
public:
	auto getCoords() const -> decltype(mCoords | std::ranges::views::all);
};

