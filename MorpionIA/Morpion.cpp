#include "Morpion.h"
#include "IA.h"
#include <iostream>
#include <vector>
#include <limits>
#ifdef _WIN32
#include <windows.h>
#endif

// Implementation of Board class
Board::Board() : board(3, std::vector<char>(3, EMPTY)) {}

void Board::Fill(int row, int col, char player) {
    board[row][col] = player;
}

void Board::Empty() {
    board = std::vector<std::vector<char>>(3, std::vector<char>(3, EMPTY));
}

void Board::Display() {
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
#endif
    // Display column numbers
    std::cout << "    0   1   2" << std::endl;
    std::cout << "  -------------" << std::endl;
    for (int row = 0; row < 3; ++row) {
        std::cout << row << " | ";
        for (int col = 0; col < 3; ++col) {
            char cell = board[row][col];
#ifdef _WIN32
            if (cell == PLAYER_X) {
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
            }
            else if (cell == PLAYER_O) {
                SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            }
            else {
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }
#endif
            std::cout << cell;
#ifdef _WIN32
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
#endif
            if (col < 2) {
                std::cout << " | ";
            }
        }
        std::cout << " |" << std::endl;
        if (row < 2) {
            std::cout << "  -------------" << std::endl;
        }
    }
    std::cout << "  -------------" << std::endl;
}

bool Board::IsEmpty(int row, int col) {
    return board[row][col] == EMPTY;
}

bool Board::IsWinner(char player) {
    // Check rows and columns for a winning line
    for (int i = 0; i < 3; ++i) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
            return true;
        }
    }
    // Check diagonals for a winning line
    return (board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player);
}

bool Board::IsDraw() {
    for (const auto& row : board) {
        for (const auto& cell : row) {
            if (cell == EMPTY) {
                return false;
            }
        }
    }
    return true;
}

std::vector<std::vector<char>> Board::GetBoard() const {
    return board;
}

// Implementation of TicTacToe class
TicTacToe::TicTacToe() : currentPlayer(PLAYER_X) {}

void TicTacToe::PlayGame() {
    int row, col;
    while (true) {
        board.Display();
        if (currentPlayer == PLAYER_X) {
            // Human player input
            std::cout << "Joueur " << currentPlayer << ", jouez donc votre coup (ligne colonne): ";
            std::cin >> row >> col;
        }
        else {
            // AI makes a move
            AI ai;
            std::pair<int, int> bestMove = ai.GetBestMove(board, PLAYER_O, PLAYER_X);
            row = bestMove.first;
            col = bestMove.second;
            std::cout << "L'IA joue : " << row << " " << col << std::endl;
        }
        // Check if the move is valid
        if (row >= 0 && row < 3 && col >= 0 && col < 3 && board.IsEmpty(row, col)) {
            // Make the move
            board.Fill(row, col, currentPlayer);
            // Check if the current player has won
            if (board.IsWinner(currentPlayer)) {
                board.Display();
                std::cout << "Joueur " << currentPlayer << " a gagne !" << std::endl;
                break;
            }
            // Check if the game is a draw
            else if (board.IsDraw()) {
                board.Display();
                std::cout << "Dommage ! Egalite parfaite !" << std::endl;
                break;
            }
            // Switch to the other player
            currentPlayer = (currentPlayer == PLAYER_X) ? PLAYER_O : PLAYER_X;
        }
        else {
            // Invalid move, prompt the player to try again
            std::cout << "Pas possible, ressayez !" << std::endl;
        }
    }
}
