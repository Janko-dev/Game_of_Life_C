#include "game.h"

#define INDEX(x, y) (y+x*CWIDTH)

int main(int argc, char **argv){
    
    State* game = init("Game of Life", WWIDTH, WHEIGHT);

    game->cells = (Cell*)calloc(sizeof(Cell), CWIDTH * CHEIGHT);
    for (size_t i = 0; i < CWIDTH*CHEIGHT; ++i){
        // game->cells[i].isAlive = i % 3 == 1 ? 1 : 0;
        // game->cells[i].isAlive = i%CWIDTH == i ? 0 : 1; 
        
        //game->cells[i].isAlive = (int)(cos(i)+sin(i))%4 == 0 ? 1 : 0; 
        game->cells[i].isAlive = (int)(sin(i)*1000.0) % 8 == 0 ? 1 : 0; 

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