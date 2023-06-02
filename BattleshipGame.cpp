#include "BattleshipGame.h"

#include "Enemy.h"
#include "InputSystem.h"
#include "Player.h"
#include "RenderingSystem.h"

BattleshipGame::BattleshipGame()
	: mInputSystem(std::make_unique<InputSystem>(InputSystem()))
	, mPlayer(std::make_unique<Player>(Player()))
	, mEnemy(std::make_unique<Enemy>(Enemy()))
	, mRenderingSystem(std::make_unique<RenderingSystem>(RenderingSystem(mPlayer.get(), mEnemy.get())))
{
}

BattleshipGame::~BattleshipGame() = default;


void BattleshipGame::start()
{
	// main loop

	mRenderingSystem->welcome();
	mInputSystem->begin();
	mRenderingSystem->initBoards();
	//mInputSystem->begin();

	BasePlayer* player1 = mPlayer.get();
	BasePlayer* player2 = mEnemy.get();

	bool end = false;

	while (!end)
	{
		//mRenderingSystem->clear();
		mRenderingSystem->renderBoards();

		int row;
		int col;

		try
		{
			player1->makeAMove(*mInputSystem, row, col);
		}
		catch (const std::exception& e)
		{
			mRenderingSystem->displayErrorMessage(e.what());
		}
		
		int result = player2->hit(row, col);

		//mRenderingSystem->clear();
		mRenderingSystem->renderBoards();

		bool endTurn = false;
		bool playerTurn = player1 == mPlayer.get();

		switch (result)
		{
		case 0:
			mRenderingSystem->miss(playerTurn, row, col);
			endTurn = true;
			break;
		case 1:
			mRenderingSystem->hit(playerTurn, row, col);
			break;
		case 2:
			mRenderingSystem->kill(playerTurn, row, col);
			break;
		case 3:
			//mRenderingSystem->victory();
			end = true;
			break;
		case -1:
			if (playerTurn)
			{
				mRenderingSystem->wrongMove();
			}
			break;
		default:
			mRenderingSystem->error();
			break;
		}

		if (endTurn)
		{
			BasePlayer* tmp = player1;
			player1 = player2;
			player2 = tmp;
		}
	}

	if (player1 == mPlayer.get())
	{
		mRenderingSystem->victory();
	}
	else
	{
		mRenderingSystem->defeat();
	}
}
