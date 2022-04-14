#include "game.h"


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
    Cell* newcells = (Cell*)malloc(sizeof(Cell) * CWIDTH * CHEIGHT);
    for (size_t i = 0; i < CWIDTH*CHEIGHT; ++i){
        unsigned char total = 0;

        // if (i % CWIDTH == 0 | ((i >= 0) & (i < CWIDTH)) | (i+CWIDTH-1) % CWIDTH == 0 | ((i < CWIDTH*CHEIGHT) & (i >= (CWIDTH*CHEIGHT-CWIDTH)))) 
        //         continue;
        for (int x = -1; x < 2; x++){
            if ((i-CWIDTH+x < 0) | (i-CWIDTH+x > CWIDTH*CHEIGHT)) continue;
            total += state->cells[i-CWIDTH+x].isAlive;
            if (x != 0) total += state->cells[i+x].isAlive;
            total += state->cells[i+CWIDTH+x].isAlive;
        }

        if (total < 2) newcells[i].isAlive = 0;
        if (total >= 4) newcells[i].isAlive = 0;
        if ((total == 2) | (total == 3)) newcells[i].isAlive = 1;
        newcells[i].x = i/CWIDTH;
        newcells[i].y = i%CHEIGHT;
    }

    state->cells = newcells;

    // (0, 0), (1, 0), (2, 0), (0, 1), (1, 1), (2, 1)

    // 0  1  2  3  4  5  6  7 
    // 8  9  10 11 12 13 14 15
    // 16 17 18 19 20 21 22 23

    // 9-w+-1  9-w+0  9-w+1
    // 9+-1     9+0   9+1
    // 9+w+-1  9+w+0  9+w+1
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