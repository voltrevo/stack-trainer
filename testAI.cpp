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

  for (int i = 0; i < 20; i++) {
    findAndLock(board);
    print(board);
  }
}
