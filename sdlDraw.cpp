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

  rect(screen, field.x, field.y, field.w, field.h, 0, 0, 0);


  block(screen, 0, 0);
  block(screen, 9, 19);

  block(screen, 3, 4);
  block(screen, 4, 4);
  block(screen, 5, 4);
  block(screen, 4, 5);

  rect(screen, field.x + field.w + 2 * 8, field.y + 8 * 8, 4 * 8, 4 * 8, 0, 0, 0);

  block(screen, 12, 8);
  block(screen, 15, 11);
}
