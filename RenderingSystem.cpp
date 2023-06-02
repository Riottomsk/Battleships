#include "RenderingSystem.h"

#include "BasePlayer.h"
//#include "Board.h"
#include "Settings.h"

#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#include <assert.h>
#include <unordered_map>

//using BoardType = std::vector<std::vector<int>>;

enum class Symbols : char
{
    horizontalBorder = '_',
    bottomBorder = static_cast<char>(205),
    verticalBorder = '|',
    ship = static_cast<char>(254),
    hit = static_cast<char>(240),
    empty = ' ',
    miss = static_cast<char>(249)
};

constexpr char spacing[] = "    ";
constexpr int hSpacing = 2;
constexpr int vSpacing = 3;
constexpr int inputRow = vSpacing + 2;
constexpr int infoRow = inputRow + 1;
constexpr int opponentActionHistoryStartRow = infoRow + 2;
constexpr int opponentHistoryLimit = 10;
constexpr int endGameMessageRow = opponentActionHistoryStartRow + opponentHistoryLimit + 2;
constexpr int messageLengthLimit = 100;

void _setCursorPosition(int x, int y);

RenderingSystem::RenderingSystem(BasePlayer* player, BasePlayer* enemy)
    : mPlayer(player)
    , mEnemy(enemy)
{
    //opponentHistory.reserve(opponentHistoryLimit);
}

void RenderingSystem::initBoards()
{
    clear();
    // TODO: move it out of here
    //constexpr char horizontalBorder = '_';
    //constexpr char bottomBorder = static_cast<char>(205);//'═';
    //constexpr char verticalBorder = '|';
    //constexpr char ship = static_cast<char>(254);
    //constexpr char hit = static_cast<char>(240);
    //const std::unordered_map<int, char> symbols = {
    //{0, ' '}, // empty/not checked
    ////{1, static_cast<char>(219)}, // '█' ship/hit
    //{-1, static_cast<char>(249)} // ' ' miss/spacing
    //};
    int boardSize = Settings::getInstance().boardSize;
    int enemyStartPos = boardSize + strlen(spacing) + 2; //fix this shit

    const Board::BoardType& pb = mPlayer->getBoard();
    const Board::BoardType& eb = mEnemy->getBoard();

    //std::cout << pb.size() << " " << eb.size() << " " << boardSize << std::endl;

    assert((pb.size() == eb.size() && eb.size() == boardSize) && "Board sizes are wrong!");

    // Top row
    _setCursorPosition(0, 0);
    std::cout << "Player";
    _setCursorPosition(0, enemyStartPos);
    std::cout << "Opponent";

    // Borders and enumeration
    for (int i = 0; i < boardSize; i++)
    {
        _setCursorPosition(vSpacing - 2, i + hSpacing);
        std::cout << i;
        _setCursorPosition(vSpacing - 1, i + hSpacing);
        std::cout << static_cast<char>(Symbols::horizontalBorder);
        _setCursorPosition(vSpacing + i, 0);
        std::cout << static_cast<char>('A' + i);
        _setCursorPosition(vSpacing + i, 1);
        std::cout << static_cast<char>(Symbols::verticalBorder);
        _setCursorPosition(vSpacing + i, boardSize + 2);
        std::cout << static_cast<char>(Symbols::verticalBorder);
        _setCursorPosition(boardSize + vSpacing, i + hSpacing);
        std::cout << static_cast<char>(Symbols::bottomBorder);

        // Enemy
        // Top enumeration
        _setCursorPosition(vSpacing - 2, enemyStartPos + i + hSpacing);
        std::cout << i;
        // Top border
        _setCursorPosition(vSpacing - 1, enemyStartPos + i + hSpacing);
        std::cout << static_cast<char>(Symbols::horizontalBorder);
        // Side enumeration
        _setCursorPosition(vSpacing + i, enemyStartPos);
        std::cout << static_cast<char>('A' + i);
        // Left border
        _setCursorPosition(vSpacing + i, enemyStartPos + 1);
        std::cout << static_cast<char>(Symbols::verticalBorder);
        // Right border
        _setCursorPosition(vSpacing + i, enemyStartPos + boardSize + hSpacing);
        std::cout << static_cast<char>(Symbols::verticalBorder);
        // Bottom border
        _setCursorPosition(boardSize + vSpacing, enemyStartPos + i + hSpacing);
        std::cout << static_cast<char>(Symbols::bottomBorder);
    }

    //auto displayBoard = [&symbols](const Board::BoardType& board, int yMargin)
    //{
    //    for (size_t r = 0; r < board.size(); r++)
    //    {
    //        for (size_t c = 0; c < board[0].size(); c++)
    //        {
    //            _setCursorPosition(r + 3, c + 2 + yMargin);

    //            auto symbol = symbols.find(board[r][c]);

    //            if (symbol != symbols.end())
    //            {
    //                std::cout << symbol->second;
    //            }

    //            if (board[r][c] > 0)
    //            {
    //                std::cout << ship;
    //            }
    //        }
    //    }
    //};

    // Player Board
    //displayBoard(pb, 0);
    _renderBoard(pb, 0);
    //for (size_t r = 0; r < pb.size(); r++)
    //{
    //    for (size_t c = 0; c < pb[0].size(); c++)
    //    {
    //        auto symbol = symbols.find(pb[r][c]);

    //        if (symbol != symbols.end())
    //        {
    //            _setCursorPosition(r + 3, c + 2);
    //            std::cout << symbol->second;
    //        }

    //        if (pb[r][c] > 0)
    //        {
    //            _setCursorPosition(r + 3, c + 2);
    //            std::cout << ship;
    //        }
    //    }
    //}

    //Enemy Board
    //displayBoard(eb, enemyStartPos);
    _renderBoard(eb, enemyStartPos);

    //_setCursorPosition(30, 0);

    //for (int i = 0; i < 255; ++i)
    //{
    //    std::cout << i << " " << static_cast<char>(i) << std::endl;
    //}

    _cleanRow(opponentActionHistoryStartRow - 1);
    std::cout << "Opponent moves history:";

    _moveCursorToActionPosition();
}

void RenderingSystem::clear() const
{
	system("CLS");
}

void RenderingSystem::renderBoards()
{
    //// TODO: move it out of here
    //constexpr char spacing[] = "    ";
    //constexpr char horizontalBorder = '—';
    //constexpr char verticalBorder = '|';

    //const std::unordered_map<int, char> symbols = {
    //    {0, ' '}, // empty/not checked
    //    {1, 'X'}, // hit
    //    {-1, '•'} // miss/spacing
    //};

    const BoardType& pb = mPlayer->getBoard();
    const BoardType& eb = mEnemy->getBoard();

    assert((pb.size() == eb.size() && eb.size() == Settings::getInstance().boardSize) && "Board sizes are wrong!");

    int enemyStartPos = pb[0].size() + strlen(spacing) + 2; //fix this shit


    _renderBoard(pb, 0);
    _renderBoard(eb, enemyStartPos);

    _moveCursorToActionPosition();
}

void RenderingSystem::welcome() const
{
    std::cout << "  _____ _                       _     _____                 \n"
                 " / ____| |                     | |   / ____|                \n"
                 "| |    | |__   ___  _   _ _ __ | |_ | |     ___  _ __  ___ \n"
                 "| |    | '_ \\ / _ \\| | | | '_ \\| __|| |    / _ \\| '_ \\/ __|\n"
                 "| |____| | | | (_) | |_| | | | | |_ | |___| (_) | | | \\__ \\\n"
                 " \\_____|_| |_|\\___/ \\__,_|_| |_|\\__| \\_____\\___/|_| |_|___/\n"
                 "                                                              \n"
                 "Welcome to Battleship!\n\n"
                 "In this game, you will be competing against an opponent to sink each other's ships. Your goal is to strategically place your ships on the board and then take turns firing missiles to try and hit your opponent's ships.\n\n"
                 "To win the game, you must sink all of your opponent's ships before they sink yours.\n\n"
                 "Good luck, and may the best strategist win!\n\n"
                 "Press any button to begin";
}

//void RenderingSystem::displayMove(int row, int col) const
//{
//    char colChar = 'A' + col;
//    std::cout << colChar << row << std::endl;
//}

void RenderingSystem::miss(bool player, int row, int col)
{
    constexpr char msg[] = "Miss!";
    _displayMove(msg, player, row, col);

    //if (player)
    //{
    //    //_cleanRow(infoRow);
    //    //std::cout << "Miss!" << std::endl;
    //    _playerMove(msg);
    //}
    //else
    //{
    //    _opponentMove(msg, row, col);
    //}
    
}

void RenderingSystem::hit(bool player, int row, int col)
{
    constexpr char msg[] = "Hit!";
    _displayMove(msg, player, row, col);
    //_cleanRow(infoRow);
    //std::cout << "Hit!" << std::endl;
}

void RenderingSystem::kill(bool player, int row, int col)
{
    constexpr char msg[] = "Kill! One down!";
    _displayMove(msg, player, row, col);
    //_cleanRow(infoRow);
    //std::cout << "Kill! One down!" << std::endl;
}

void RenderingSystem::victory() const
{
    int bs = Settings::getInstance().boardSize;
    //_setCursorPosition(bs + 4, 0);
    _setCursorPosition(endGameMessageRow + bs, 0);

    std::cout << "Victory!" << std::endl;
}

void RenderingSystem::defeat() const
{
    int bs = Settings::getInstance().boardSize;
    _setCursorPosition(endGameMessageRow + bs, 0);
    //int bs = Settings::getInstance().boardSize;
    //_setCursorPosition(0, bs + 4);
    std::cout << "Defeat! Better luck next time! ;)" << std::endl;
}

void RenderingSystem::wrongMove() const
{
    _cleanRow(infoRow);
    std::cout << "Bad move. Don't do that next time!" << std::endl;
}

void RenderingSystem::error() const
{
    _cleanRow(infoRow);
    std::cout << "ERROR!!!" << std::endl;
}

void RenderingSystem::displayErrorMessage(const char* msg) const
{
    _cleanRow(infoRow);
    //int boardSize = Settings::getInstance().boardSize;
    //_setCursorPosition(vSpacing + boardSize + 3, 0); // TODO: Rework
    std::cout << msg;
}

void RenderingSystem::_renderBoard(const BoardType& board, int yMargin) const
{
    for (size_t r = 0; r < board.size(); r++)
    {
        for (size_t c = 0; c < board[0].size(); c++)
        {
            _setCursorPosition(r + 3, c + 2 + yMargin);

            switch (board[r][c])
            {
            case -2:
                std::cout << static_cast<char>(Symbols::hit);
                break;
            case -1:
                std::cout << static_cast<char>(Symbols::miss);
                break;
            case 0:
                std::cout << static_cast<char>(Symbols::empty);
                break;
            default:
                std::cout << static_cast<char>(Symbols::ship);
                //std::cout << board[r][c];
                break;
            }

            //auto symbol = symbols.find(board[r][c]);

            //if (symbol != symbols.end())
            //{
            //    std::cout << symbol->second;
            //}

            //if (board[r][c] > 0)
            //{
            //    std::cout << ship;
            //}
        }
    }
}

void RenderingSystem::_moveCursorToActionPosition() const
{
    _cleanRow(inputRow);
    constexpr char msg[] = "Your move: ";
    std::cout << msg;
}

void RenderingSystem::_moveCursorToInfo() const
{
    _cleanRow(infoRow);
}

void RenderingSystem::_cleanRow(int row) const
{
    int bs = Settings::getInstance().boardSize; // TODO: fix
    _setCursorPosition(row + bs, 0);
    for (size_t i = 0; i < messageLengthLimit; ++i)
    {
        std::cout << ' '; // cleaning
    }
    _setCursorPosition(row + bs, 0);
}

void RenderingSystem::_displayMove(std::string_view msg, bool player, int row, int col)
{
    if (player)
    {
        _playerMove(msg);
    }
    else
    {
        _opponentMove(msg, row, col);
    }
}

void RenderingSystem::_playerMove(std::string_view str) const
{
    _cleanRow(infoRow);
    std::cout << str << std::endl;
}

void RenderingSystem::_opponentMove(std::string_view str, int row, int col)
{
    std::string move = { static_cast<char>('A' + row), static_cast<char>('0' + col), ' ' };
    move += str;

    if (opponentHistory.size() >= opponentHistoryLimit)
    {
        opponentHistory.pop_front();
    }

    opponentHistory.push_back(std::move(move));

    for (int i = 0; i < opponentHistory.size(); ++i)
    {
        _cleanRow(opponentActionHistoryStartRow + i);
        std::cout << opponentHistory[i] << std::endl;
    }

}



//void RenderingSystem::_setCursorPosition(int x, int y) const
void _setCursorPosition(int x, int y)
{
    COORD pos = { y, x };
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output, pos);
}
