#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
// #include "screens/start.h"

typedef struct
{
  int x, y;
  short life;
  char *name;
} Player;

int processEvents(SDL_Window *window, Player *player)
{
  SDL_Event event;
  int done = 0;

  while (SDL_PollEvent(&event))
  {
    switch (event.type)
    {
    case SDL_WINDOWEVENT_CLOSE:
    {
      if (window)
      {
        SDL_DestroyWindow(window);
        window = NULL;
        done = 1;
      }
    }
    break;
    case SDL_KEYDOWN:
    {
      switch (event.key.keysym.sym)
      {
      case SDLK_ESCAPE:
        done = 1;
      }
      break;
    }
    break;
    case SDL_QUIT:
    {
      done = 1;
    }
    break;
    }
  }

  const Uint8 *state = SDL_GetKeyboardState(NULL);
  if (state[SDL_SCANCODE_LEFT])
  {
    player->x--;
  }
  if (state[SDL_SCANCODE_RIGHT])
  {
    player->x++;
  }
  if (state[SDL_SCANCODE_UP])
  {
    player->y--;
  }
  if (state[SDL_SCANCODE_DOWN])
  {
    player->y++;
  }

  return done;
}

void doRender(SDL_Renderer *renderer, Player *player)
{
  SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // blue
  SDL_RenderClear(renderer);

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // white
  SDL_Rect rect = {player->x, player->y, 20, 20};
  SDL_RenderFillRect(renderer, &rect);

  SDL_RenderPresent(renderer);
}

int main(int argc, char *argv[])
{
  SDL_Init(SDL_INIT_VIDEO);

  Player player;
  player.x = 320;
  player.y = 240;

  SDL_Window *window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 768, SDL_WINDOW_SHOWN);
  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  int done = 0;

  while (!done)
  {
    done = processEvents(window, &player);

    doRender(renderer, &player);

    SDL_Delay(10);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  SDL_Quit();
  return 0;
}
