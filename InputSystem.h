#pragma once

class InputSystem
{
public:
	void begin() const;
	void getUserMove(int& _row, int& _col) const;
	void makeRandomMove(int& row, int& col) const;
};

