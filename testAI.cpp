#include "AI.hpp"

#include <iostream>

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
  Board board(0);
  print(board);

  int count = 0;

  while (!board.gameOver) {
    findAndLock(board);
    count++;
    print(board);
  }

  std::cout << "Score: " << board.score << " (" << (int)(board.score * 25670) << ")" << std::endl;
  std::cout << "Score/line: " << board.score / board.linesCleared << std::endl;

  return 0;
}
