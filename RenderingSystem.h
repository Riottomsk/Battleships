#pragma once

#include <vector>
#include <deque>
#include <string>

class BasePlayer;

//constexpr int opponentHistoryLimit = 10;

class RenderingSystem
{
public:

	RenderingSystem(BasePlayer* player, BasePlayer* enemy);

	void initBoards();
	
	void clear() const; // shall it be const? For now they merely invoke console commands but an advanced system may possess something...
	void renderBoards();
	void welcome() const;
	//void displayMove(int row, int col) const;
	void miss(bool player, int row, int col);
	void hit(bool player, int row, int col);
	void kill(bool player, int row, int col);
	void victory() const;
	void defeat() const;
	void wrongMove() const;
	void error() const;
	void displayErrorMessage(const char* msg) const;

private:
	using BoardType = std::vector<std::vector<int>>;
	//void _setCursorPosition(int x, int y) const;

	void _renderBoard(const BoardType& board, int yMargin) const;
	void _moveCursorToActionPosition() const;
	void _moveCursorToInfo() const;
	void _cleanRow(int row) const;
	void _displayMove(std::string_view msg, bool player, int row, int col);
	void _playerMove(std::string_view str) const;
	void _opponentMove(std::string_view str, int row, int col);

	std::vector<std::vector<char>> mPreviousFrame;
	std::deque<std::string> opponentHistory;
	// TODO: Replace with BasePlayer pointers/references to Player and Enemy
	//const Board& mPlayerBoard;
	//const Board& mEnemyBoard;
	BasePlayer* mPlayer;
	BasePlayer* mEnemy;

};
