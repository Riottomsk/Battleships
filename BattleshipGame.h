#pragma once

#include <memory>

class BasePlayer;
class InputSystem;
class RenderingSystem;

class BattleshipGame
{
public:
	BattleshipGame();
	~BattleshipGame();

	void start();

private:

	std::unique_ptr<InputSystem> mInputSystem;
	std::unique_ptr<BasePlayer> mPlayer;
	std::unique_ptr<BasePlayer> mEnemy;
	std::unique_ptr<RenderingSystem> mRenderingSystem;
};

