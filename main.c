#include "game.h"

int main(int argc, char **argv){
    
    State* game = init("Game of Life", WWIDTH, WHEIGHT);

    game->cells = (Cell*)calloc(sizeof(Cell), CWIDTH * CHEIGHT);
    for (size_t i = 0; i < CWIDTH*CHEIGHT; ++i){
        game->cells[i].isAlive = i % 5 == 1 ? 1 : 0;

        game->cells[i].x = i/CWIDTH;
        game->cells[i].y = i%CHEIGHT;
    }

    while (game->isRunning){
        eventHandling(game);
        update(game);
        draw(game);
        SDL_Delay(1000/10);
    }

    quit(game);
    return 0;
}