#include <SDL.h>

#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

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
  SDL_Event e;

  while (true) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        return;
      }

      if (e.type == SDL_KEYDOWN) {
        switch(e.key.keysym.sym) {
          case SDLK_UP:
          break;

          case SDLK_DOWN:
          break;

          case SDLK_LEFT:
          break;

          case SDLK_RIGHT:
          break;

          default:
          break;
        }
      }
    }

    // SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, NULL);

    SDL_UpdateWindowSurface(gWindow);
  }
}

int main(int argc, char* args[]) {
  if (!init()) {
    std::cout << "Failed to initialize!" << std::endl;
    close();
    return 1;
  }

  run();
  close();

  return 0;
}
