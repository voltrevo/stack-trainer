#pragma once

#include "Piece.hpp"
#include "Pos.hpp"

#include <random>

extern const short leftSide;

struct Board {
  short field[22];

  Piece piece;
  Pos piecePos;

  Piece nextPiece;

  int score;

  bool gameOver;
  std::minstd_rand rng;

  Board(unsigned seed):
    field{},
    rng(seed)
  {
    piece = UniformPiece();
    piecePos = {5, 2};
    nextPiece = NextPiece();
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

    for (int i = 0; i < 4; i++) {
      field[piecePos.y + blocks[i].y] |= leftSide >> (piecePos.x + blocks[i].x);
    }

    piece = nextPiece;
    piecePos = {8, 2};
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

    short fieldLine = field[pos.y];
    short blockLine = leftSide >> pos.x;

    return (fieldLine & blockLine) == 0;
  }

  bool checkPiece() {
    auto& blocks = piece.Blocks();

    for (int i = 0; i < 4; i++) {
      Pos blockPos = {
        piecePos.x + blocks[i].x,
        piecePos.y + blocks[i].y,
      };

      if (!checkPos(blockPos)) {
        return false;
      }
    }

    return true;
  }
};
