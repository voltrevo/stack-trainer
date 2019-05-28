#pragma once

#include "Pos.hpp"

struct OrientedPiece {
  Pos blocks[4];
};

struct Piece {
  char i;
  char iMax;
  Orientation* data;

  void rotate(char diff) { i = (i + iMax + diff) % iMax; }
  OrientedPiece& Blocks() { return data[i]; }
};

extern Piece pieces[7];
