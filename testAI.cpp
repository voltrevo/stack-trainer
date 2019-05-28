#include "AI.hpp"

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

  std::cout << hLine << std::endl;
  std::cout << Heuristic(board.field) << std::endl << std::endl;
}

int main() {
  double best = -infinity;
  double worst = infinity;
  double sum = 0;

  for (int seed = 1; seed <= 100; seed++) {
    Board board(seed);

    while (!board.gameOver) {
      findAndLock(board);
    }

    if (board.score > best) {
      best = board.score;
    }

    if (board.score < worst) {
      worst = board.score;
    }

    sum += board.score;
  }

  auto printScore = [&](const char* desc, double score) {
    std::cout << desc << ' ' << score << " (" << (int)(score * 25670) << ")" << std::endl;
  };

  printScore("Best ", best);
  printScore("Worst", worst);
  printScore("Avg  ", sum / 100);

  return 0;
}
