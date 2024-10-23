#include "IA.h"
#include <limits>
#include <algorithm>

// Function to get the best move for the AI
std::pair<int, int> AI::GetBestMove(Board& board, char aiPlayer, char humanPlayer) {
    int bestScore = std::numeric_limits<int>::min();
    std::pair<int, int> bestMove = { -1, -1 };

    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            if (board.IsEmpty(row, col)) {
                board.Fill(row, col, aiPlayer);
                int score = Minimax(board, 0, false, aiPlayer, humanPlayer);
                board.Fill(row, col, EMPTY);
                if (score > bestScore) {
                    bestScore = score;
                    bestMove = { row, col };
                }
            }
        }
    }
    return bestMove;
}

// Minimax algorithm to evaluate the board state
int AI::Minimax(Board& board, int depth, bool isMaximizing, char aiPlayer, char humanPlayer) {
    if (board.IsWinner(aiPlayer)) {
        return 10 - depth;
    }
    if (board.IsWinner(humanPlayer)) {
        return depth - 10;
    }
    if (board.IsDraw()) {
        return 0;
    }

    if (isMaximizing) {
        int bestScore = std::numeric_limits<int>::min();
        for (int row = 0; row < 3; ++row) {
            for (int col = 0; col < 3; ++col) {
                if (board.IsEmpty(row, col)) {
                    board.Fill(row, col, aiPlayer);
                    int score = Minimax(board, depth + 1, false, aiPlayer, humanPlayer);
                    board.Fill(row, col, EMPTY);
                    bestScore = std::max(score, bestScore);
                }
            }
        }
        return bestScore;
    }
    else {
        int bestScore = std::numeric_limits<int>::max();
        for (int row = 0; row < 3; ++row) {
            for (int col = 0; col < 3; ++col) {
                if (board.IsEmpty(row, col)) {
                    board.Fill(row, col, humanPlayer);
                    int score = Minimax(board, depth + 1, true, aiPlayer, humanPlayer);
                    board.Fill(row, col, EMPTY);
                    bestScore = std::min(score, bestScore);
                }
            }
        }
        return bestScore;
    }
}
