#pragma once

#include "Piece.hpp"
#include "Pos.hpp"

#include <random>

const unsigned short leftSide  = 1 << 12;
const unsigned short fullLine  = 0b1111111111111111;
const unsigned short emptyLine = 0b1110000000000111;

struct Board {
  unsigned short field[23];

  Piece piece;
  Pos piecePos;

  Piece nextPiece;

  int linesCleared;
  double score;

  bool gameOver;
  std::minstd_rand rng;

  Board(unsigned seed):
    rng(seed)
  {
    for (int i = 0; i < 22; i++) {
      field[i] = emptyLine;
    }

    field[22] = fullLine;

    piece = UniformPiece();
    piecePos = {5, 2};
    nextPiece = NextPiece();
    linesCleared = 0;
    score = 0;
    gameOver = false;
  }

  Piece UniformPiece() {
    return pieces[rng() % 7];
  }

  Piece NextPiece() {
    auto np = UniformPiece();

    // Emit this piece if different from current piece
    if (np.data != piece.data) {
      return np;
    }

    // Retry but only once
    return UniformPiece();
  }

  void lockPiece() {
    auto& blocks = piece.Blocks();
    bool clear = false;

    for (int i = 0; i < 4; i++) {
      auto& line = field[piecePos.y + blocks[i].y];
      line |= leftSide >> (piecePos.x + blocks[i].x);
      clear |= line == fullLine;
    }

    if (clear) {
      // Here 'high' means high on the screen, which is a lower number

      int iHigh = 21;
      int iLow = 21;

      while (iHigh >= 2) {
        if (field[iHigh] == fullLine) {
          iHigh--;
        } else {
          field[iLow] = field[iHigh];
          iLow--;
          iHigh--;
        }
      }

      int lines = iLow - iHigh;
      linesCleared += lines;

      // Full 4 lines cleared is 1.0, triple is only 0.25
      score += (
        lines == 0 ?  0 :
        lines == 1 ?  1 :
        lines == 2 ?  2 :
        lines == 3 ?  6 :
                     24
      ) / 24.0;

      while (iHigh < iLow) {
        field[iLow] = 0;
        iLow--;
      }
    }

    piece = nextPiece;
    piecePos = {5, 2};
    nextPiece = NextPiece();

    if (!checkPiece()) {
      gameOver = true;
    }
  }

  bool rotate(char diff) { // cw: rotate(1), ccw: rotate(-1)
    piece.rotate(diff);

    if (!checkPiece()) {
      piece.rotate(-diff);
      return false;
    }

    return true;
  }

  bool moveX(char diff) { // left: moveX(-1), right: moveX(1)
    piecePos.x += diff;

    if (!checkPiece()) {
      piecePos.x -= diff;
      return false;
    }

    return true;
  }

  bool down() {
    piecePos.y++;

    if (!checkPiece()) {
      piecePos.y--;
      lockPiece();
      return false;
    }

    return true;
  }

  bool checkPos(const Pos& pos) {
    if (
      (pos.y < 0 || pos.y >= 22) ||
      (pos.x < 0 || pos.x >= 10)
    ) {
      return false;
    }

    unsigned short fieldLine = field[pos.y];
    unsigned short blockLine = leftSide >> pos.x;

    return (fieldLine & blockLine) == 0;
  }

  bool checkPiece() { return checkPiece(piece, piecePos); }

  bool checkPiece(const Piece& p, const Pos& pos) {
    auto& blocks = p.Blocks();

    for (int i = 0; i < 4; i++) {
      Pos blockPos = {
        pos.x + blocks[i].x,
        pos.y + blocks[i].y,
      };

      if (!checkPos(blockPos)) {
        return false;
      }
    }

    return true;
  }
};
