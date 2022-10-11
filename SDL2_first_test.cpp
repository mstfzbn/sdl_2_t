/*
 * Program.cpp
 *
 *  Created on: Jul 4, 2016
 *      Author: default
 */

#include <SDL.h>
#include <SDL_render.h>
#include <cstdlib>
#include <ctime>
#include "Drawable.h"


SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
//int SCREEN_WIDTH = 1920;
//int SCREEN_HEIGHT = 1080;
//int FRAME_RATE = 1000 / 60;

//int NUMBER_OF_OBJECTS = 50;

bool init();
void close();

using namespace Implementations;
using namespace Contracts;
using namespace std;

int main(int argc, char* args[]) {
    init();
    vector<IDrawable*> objects;
    unsigned int oldTime = SDL_GetTicks();

    for (int i = 0; i < NUMBER_OF_OBJECTS; ++i) {
        objects.push_back(new Drawable({ SCREEN_WIDTH, SCREEN_HEIGHT }));
    }
    bool quit = false;
    SDL_Event e;
    SDL_Point coursor = {
        0,
        0
    };

    while (!quit)
    {
        //Handle events on queue
        while (SDL_PollEvent(&e) != 0)
        {
            //User requests quit
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            
            if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP)
            {
                SDL_GetMouseState(&coursor.x, &coursor.y);
            } 


            if(e.type == SDL_KEYDOWN)
            {
                switch(e.key.keysym.sym)
                {
                    case SDLK_k:
                        for (int i = 0; i < 100; ++i) //adds 100 of points
                        {
                                objects.push_back(new Drawable({ SCREEN_WIDTH, SCREEN_HEIGHT }));
                        }
                    break;

                    case SDLK_l:
                             objects.clear();
                    break;

                    case SDLK_q:
                             quit = true;
                    break;

                    default: break;
                }
            }         
        }

        if (SDL_GetTicks() >= oldTime + FRAME_RATE)
        {
            oldTime = SDL_GetTicks();
            //Clear screen
            SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
            SDL_RenderClear(gRenderer);
            for (auto ball : objects) {
                ball->Draw(gRenderer, objects, coursor);
                ball->Move(SCREEN_WIDTH, SCREEN_HEIGHT);
            }

            //Update screen
            SDL_RenderPresent(gRenderer);
        }
    }

    close();
    return 0;
}

bool init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        //Create window
        gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            //Create renderer for window
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if (gRenderer == NULL)
            {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);

            }
        }
    }

    srand(time(NULL));
    return success;
}

void close()
{
    //Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    SDL_Quit();
}
