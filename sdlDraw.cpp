#include "Board.hpp"
#include "sdlDraw.hpp"

SDL_Rect field = {95, 39, 81, 162};

void clear(SDL_Surface* surface) {
  SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0x40, 0x40, 0x40));
}

void rect(SDL_Surface* surface, int x, int y, int w, int h, int r, int g, int b) {
  SDL_Rect rect = {x, y, w, h};
  SDL_FillRect(surface, &rect, SDL_MapRGB(surface->format, r, g, b));
}

void block(SDL_Surface* surface, int x, int y) {
  rect(surface, field.x + 1 + 8 * x, field.y + 1 + 8 * y, 7, 7, 255, 255, 255);
}

void sdlDraw(SDL_Window* window, const Board& board) {
  SDL_Surface* screen = SDL_GetWindowSurface(window);

  clear(screen);

  // Field
  rect(screen, field.x, field.y, field.w, field.h, 0, 0, 0);

  // Preview area
  rect(screen, field.x + field.w + 2 * 8, field.y + 8 * 8, 5 * 8, 5 * 8, 0, 0, 0);

  for (int x = 0; x < 10; x++) {
    for (int y = 0; y < 20; y++) {
      if ((board.field[y + 2] & (leftSide >> x)) != 0) {
        block(screen, x, y);
      }
    }
  }

  {
    auto& blocks = board.piece.Blocks();

    for (int i = 0; i < 4; i++) {
      block(screen, board.piecePos.x + blocks[i].x, board.piecePos.y + blocks[i].y - 2);
    }
  }

  {
    auto& blocks = board.nextPiece.Blocks();

    for (int i = 0; i < 4; i++) {
      block(screen, 14 + blocks[i].x, 10 + blocks[i].y);
    }
  }
}
