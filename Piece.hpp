#pragma once

struct Coord {
  char x;
  char y;
};

struct OrientedPiece {
  Coord coords[4];
};

struct Piece {
  char i;
  char iMax;
  Orientation* data;

  void rotateCW() { i = (i + 1) % iMax; }
  void rotateCCW() { i = (i + 3) % iMax; }
  OrientedPiece& Coords() { return data[i]; }
};

extern Piece pieces[7];
