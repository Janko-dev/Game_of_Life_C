#ifndef GAME_OF_LIFE
#define GAME_OF_LIFE

#include <SDL2/SDL.h>
#include <math.h>

#define CWIDTH 100
#define CHEIGHT 100

#define WWIDTH 800
#define WHEIGHT 800

typedef struct {
    int x, y;
    char isAlive;
} Cell;

typedef struct {
    SDL_Window* window;
    SDL_Renderer* rend;
    char isRunning;
    Cell* cells;
} State;

State* init(const char* title, int width, int height);
void draw(State* state);
void update(State* state);
void eventHandling(State* state);
void quit(State* state);

#endif