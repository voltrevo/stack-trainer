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
  int gravity = 5;
  int gravityProgress = 0;
  int direction = 0;
  int das = 6;
  int dasProgress = 0;
  auto lastFrame = SDL_GetTicks();
  SDL_Event e;

  while (true) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        return;
      }

      if (e.type == SDL_KEYDOWN && !e.key.repeat) {
        switch(e.key.keysym.sym) {
          case SDLK_w:
          break;

          case SDLK_s:
            board.down();
          break;

          case SDLK_a:
            direction = -1;
            dasProgress = 0;
            board.moveX(-1);
          break;

          case SDLK_d:
            direction = 1;
            dasProgress = 0;
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

      if (e.type == SDL_KEYUP) {
        switch(e.key.keysym.sym) {
          case SDLK_a:
          case SDLK_d:
            direction = 0;
            dasProgress = 0;
          break;
        }
      }
    }

    auto time = SDL_GetTicks();

    if (time - lastFrame >= 17) {
      lastFrame = time;

      gravityProgress++;

      if (gravityProgress >= gravity) {
        board.down();
        gravityProgress = 0;
      }

      dasProgress++;

      if (dasProgress >= das) {
        board.moveX(direction);
        dasProgress = 0;
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
