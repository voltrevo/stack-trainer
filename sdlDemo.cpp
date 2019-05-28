#include "Board.hpp"
#include "sdlDraw.hpp"

#include <SDL.h>

#include <iostream>
#include <string>

const int SCREEN_WIDTH = 256;
const int SCREEN_HEIGHT = 224;

bool init();
void close();
SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;

bool init() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
    return false;
  }

  gWindow = SDL_CreateWindow(
    "Stack Trainer",
    SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED,
    SCREEN_WIDTH,
    SCREEN_HEIGHT,
    SDL_WINDOW_SHOWN
  );

  if (gWindow == NULL) {
    std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
    return false;
  }

  gScreenSurface = SDL_GetWindowSurface(gWindow);

  return true;
}

void close() {
  SDL_DestroyWindow(gWindow);
  gWindow = NULL;

  SDL_Quit();
}

void run() {
  Board board(0);
  SDL_Event e;

  while (true) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        return;
      }

      if (e.type == SDL_KEYDOWN) {
        switch(e.key.keysym.sym) {
          case SDLK_w:
          break;

          case SDLK_s:
            board.down();
          break;

          case SDLK_a:
            board.moveX(-1);
          break;

          case SDLK_d:
            board.moveX(1);
          break;

          case SDLK_LEFTBRACKET:
            board.rotate(-1);
          break;

          case SDLK_RIGHTBRACKET:
            board.rotate(1);
          break;

          case SDLK_ESCAPE:
            return;
          break;

          default:
          break;
        }
      }
    }

    sdlDraw(gWindow, board);

    SDL_UpdateWindowSurface(gWindow);
  }
}

int main(int argc, char* args[]) {
  if (!init()) {
    std::cout << "Failed to initialize!" << std::endl;
    close();
    return 1;
  }

  if (argc >= 2 && std::string(args[1]) == "--fullscreen") {
    SDL_SetWindowFullscreen(gWindow, SDL_WINDOW_FULLSCREEN);
  }

  run();
  close();

  return 0;
}
