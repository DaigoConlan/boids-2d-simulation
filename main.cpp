#include <iostream>
#include <SDL2/SDL.h>
#include "mySDL.h"
#include "Boids.h"

int main(){

    mySDL sdl;
    Boids boids;

    //initialize sdl
    sdl.setTitle("Boids");
    sdl.setWindowSize(1920,1080);
    sdl.setWindowPosition(0,0);
    sdl.init();

    //initialize boids
    boids.setTexture(sdl.getRenderer(),"./smallTriangle.png");
    boids.setBoidsSize(20,20);
    boids.setBoundary(200,200,sdl.getWindowWidth()-200,sdl.getWindowHeight()-200);
    boids.init(20);

    bool quit = false;
    SDL_Event e;

    while(!quit){

        while(SDL_PollEvent(&e)!=0){

            if(e.type == SDL_QUIT){

                quit = true;
            }
        }
        
        boids.update();
        boids.draw(sdl.getRenderer());
        sdl.render();
        SDL_Delay(100);
    }

    boids.free();
    sdl.free();


    return 0;
}