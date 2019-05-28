#include "AI.hpp"

#include <cmath>
#include <iostream>
#include <limits>

const double infinity = std::numeric_limits<double>::infinity();

void print(const Board& board) {
  const char* hLine = "------------";
  std::cout << hLine << std::endl;

  for (int i = 2; i < 22; i++) {
    std::cout << '|';

    for (int j = 0; j < 10; j++) {
      bool block = (board.field[i] & (leftSide >> j)) != 0;
      std::cout << (block ? '@' : ' ');
    }

    std::cout << '|' << std::endl;
  }

  std::cout << hLine << std::endl << std::endl;
}

double measure(const AIVec& weights) {
  double sum = 0;

  for (int seed = 1; seed <= 100; seed++) {
    Board board(seed);

    while (!board.gameOver) {
      findAndLock(weights, board);
    }

    sum += board.score;
  }

  return sum / 100;
}

int main() {
  AIVec weights = {-1, -1};

  for (int i = 0; i < 30; i++) {
    std::cout << weights[1] << ": " << measure(weights) << std::endl;

    weights[1] *= std::exp(-0.2);
  }

  return 0;
}
