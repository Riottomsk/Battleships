#include "Ship.h"

//int Ship::shipNum = 1;

Ship::Ship(int size, int id)
	: mSize(size)
	, mHealth(size)
	, mId(id)
{
}

int Ship::getId() const
{
	return mId;
}

bool Ship::hit()
{
	--mHealth;
	return alive();
}

bool Ship::alive() const
{
	return mHealth > 0;
}

void Ship::addCoord(const Vec2& coord)
{
	mCoords.push_back(coord);
}

auto Ship::getCoords() const -> decltype(mCoords | std::ranges::views::all)
{
	return mCoords | std::ranges::views::all;
}
