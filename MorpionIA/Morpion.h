#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <iostream>
#include <vector>
#include <limits>

// Constants to represent the players and empty cells
const char PLAYER_X = 'X';
const char PLAYER_O = 'O';
const char EMPTY = '-';

// Board class to manage the game board
class Board {
private:
    std::vector<std::vector<char>> board; // 2D vector to represent the board

public:
    Board();
    void Fill(int row, int col, char player);
    void Empty();
    void Display();
    bool IsEmpty(int row, int col);
    bool IsWinner(char player);
    bool IsDraw();
    std::vector<std::vector<char>> GetBoard() const;
};

// TicTacToe class to manage the game logic
class TicTacToe {
private:
    Board board; // Instance of the Board class to manage the game board
    char currentPlayer; // Current player ('X' or 'O')

public:
    TicTacToe();
    void PlayGame();
};

#endif // TICTACTOE_H
