#include "game.h"

#define INDEX(x, y) ((y)+(x)*CWIDTH)

void draw(State* state){
    SDL_SetRenderDrawColor(state->rend, 255, 255, 255, 255);
    SDL_RenderClear(state->rend);

    for (size_t i = 0; i < CWIDTH*CHEIGHT; ++i){

        SDL_SetRenderDrawColor(state->rend, 0, 0, 0, 255);
        SDL_Rect r = { state->cells[i].x * (WWIDTH/CWIDTH), state->cells[i].y * (WHEIGHT/CHEIGHT), WWIDTH/CWIDTH, WHEIGHT/CHEIGHT}; 
        
        if (state->cells[i].isAlive){
            SDL_RenderDrawRect(state->rend, &r);
        } else {
            
            SDL_RenderFillRect(state->rend, &r);
        }
    }

    SDL_RenderPresent(state->rend);
}

void update(State* state){
    Cell* newcells = (Cell*)calloc(sizeof(Cell), CWIDTH * CHEIGHT);

    for (int i = 0; i < CWIDTH; ++i){
        for (int j = 0; j < CHEIGHT; ++j){
            unsigned char total = 0;
            for (int x = -1; x < 2; x++){
                for (int y = -1; y < 2; y++){
                    if ((x == 0 && y == 0) || 
                    i+x < 0 || i+x > CWIDTH-1 ||
                    j+y < 0 || j+y > CHEIGHT-1) continue;
                    
                    total += state->cells[INDEX(i+x, j+y)].isAlive;
                }
            }
            if (total < 2) newcells[INDEX(i, j)].isAlive = 0;
            if (total >= 4) newcells[INDEX(i, j)].isAlive = 0;
            if ((total == 2) || (total == 3)) newcells[INDEX(i, j)].isAlive = 1;
            newcells[INDEX(i, j)].x = i;
            newcells[INDEX(i, j)].y = j;
        }    
    }
    free(state->cells);
    state->cells = newcells;
}

void eventHandling(State* state){
    SDL_Event e;
    while (SDL_PollEvent(&e)){
        switch (e.type){
            case SDL_QUIT:
                state->isRunning = 0;
                break;
            default:
                break;
        }
    }
}

void quit(State* state) {
    SDL_DestroyWindow(state->window);
    SDL_DestroyRenderer(state->rend);
    SDL_Quit();
    free(state);
    exit(1);
}

State* init(const char* title, int width, int height){
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0){
        printf("Unable to initialize: %s\n", SDL_GetError());
        exit(1);
    }

    State* s = (State*)malloc(sizeof(State));

    s->window = SDL_CreateWindow(title, 
                    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                    width, height, 0);
    
    if (s->window == NULL){
        printf("Unable to create window: %s\n", SDL_GetError());
        SDL_DestroyWindow(s->window);
        SDL_Quit();
        free(s);
        exit(1);
    }

    s->rend = SDL_CreateRenderer(s->window, -1, SDL_RENDERER_ACCELERATED);
    if (s->rend == NULL){
        printf("Unable to create renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(s->window);
        SDL_DestroyRenderer(s->rend);
        SDL_Quit();
        free(s);
        exit(1);
    }

    s->isRunning = 1;
    return s;
}