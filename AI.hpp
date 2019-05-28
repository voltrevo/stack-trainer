#pragma once

#include "Board.hpp"

#include <array>

using AIVec = std::array<double, 2>;

bool findAndLock(const AIVec& weights, Board& board);
double Heuristic(const AIVec& weights, const unsigned short (&field)[23]);
