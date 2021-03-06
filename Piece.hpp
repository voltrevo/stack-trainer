#pragma once

#include "Pos.hpp"

typedef Pos OrientedPiece[4];

struct Piece {
  char i;
  char iMax;
  OrientedPiece* data;

  void rotate(char diff) { i = (i + iMax + diff) % iMax; }
  const OrientedPiece& Blocks() const { return data[i]; }
};

extern Piece pieces[7];
