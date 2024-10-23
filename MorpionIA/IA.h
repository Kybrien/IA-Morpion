#pragma once

#include "Morpion.h"
#include <utility>
#include <limits>

// AI class to manage AI decision making
class AI {
public:
    std::pair<int, int> GetBestMove(Board& board, char aiPlayer, char humanPlayer);

private:
    int Minimax(Board& board, int depth, bool isMaximizing, char aiPlayer, char humanPlayer);
};
