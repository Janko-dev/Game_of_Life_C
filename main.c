#include "game.h"

int main(int argc, char **argv){
    
    // for (int i = 0; i < 10; ++i){
    //     printf("%d\n", rand()%50);
    // }

    State* game = init("Game of Life", WWIDTH, WHEIGHT);

    game->cells = (Cell*)malloc(sizeof(Cell) * CWIDTH * CHEIGHT);
    for (size_t i = 0; i < CWIDTH*CHEIGHT; ++i){
        game->cells[i].isAlive = i % 2;
        game->cells[i].x = i/CWIDTH;
        game->cells[i].y = i%CHEIGHT;
    }

    // 0 1 2 3 4 5 6 7 8 

    // 0 1 2 
    // 3 4 5
    // 6 7 8 

    // (0,0)  

    while (game->isRunning){
        eventHandling(game);
        update(game);
        draw(game);

        SDL_Delay(160);
    }

    quit(game);
    return 0;
}