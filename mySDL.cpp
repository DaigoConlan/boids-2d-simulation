//This file contains the setup for sdl

#include "mySDL.h"

//The constructor
mySDL::mySDL(){

    //Set title to mySDL and the other values to 0
    gWindow = NULL;
    gRenderer = NULL;
    windowW= DEFAULT_WINDOW_WIDTH;
    windowH= DEFAULT_WINDOW_HEIGHT;
    windowX= DEFAULT_WINDOW_X;
    windowY= DEFAULT_WINDOW_Y;
    std::string title = "MySDL";

    //Clear the renderer  with white
    SDL_SetRenderDrawColor(gRenderer,0xFF,0xFF,0xFF,0xFF);
    SDL_RenderClear(gRenderer);
    

}

//free all allocated memory
mySDL::~mySDL(){

    free();
}

//Set the size of the window
void mySDL::setWindowSize(int width = DEFAULT_WINDOW_WIDTH,int height=DEFAULT_WINDOW_HEIGHT){

    windowW = width;
    windowH = height;

}

//set the position of the window
void mySDL::setWindowPosition(int x = DEFAULT_WINDOW_X, int y = DEFAULT_WINDOW_Y){

    windowX = x;
    windowY = y;
}

//get the width of the window
int mySDL::getWindowWidth(){

    return windowW;
}

//get the height of the window
int mySDL::getWindowHeight(){

    return windowH;
}

//Set the title of the window
void mySDL::setTitle(std::string newTitle){

    title = newTitle;

}

SDL_Renderer* mySDL::getRenderer(){

    return gRenderer;
}

//Render
void mySDL::render(){

    SDL_RenderPresent(gRenderer);

    //Clear with white
    SDL_SetRenderDrawColor(gRenderer,0xFF,0xFF,0xFF,0xFF);
    SDL_RenderClear(gRenderer);
}

//Initialize SDL,IMG, create window and renderer
bool mySDL::init(){

    bool success = true;

    //Initialize SDL and SDL_IMG
    if(SDL_Init(SDL_INIT_VIDEO)<0){

        success = false;
        printf("Failed to init SDL. Error: %s\n",SDL_GetError());
    
    }else{

        if(IMG_Init(IMG_INIT_PNG)!=IMG_INIT_PNG){

            success = false;
            printf("Failed to init SDL_img. Error: %s\n",IMG_GetError());
        
        }
    }

    //If SDL and SDL_IMG were successfully initialized
    //Create window and renderer
    if(success){

        gWindow = SDL_CreateWindow(title.c_str(),windowX,windowY,windowW,windowH,SDL_WINDOW_SHOWN);
            
        if(gWindow == NULL){

            success = false;
            printf("Failed to create window. Error: %s\n",SDL_GetError());

        }else{

            gRenderer = SDL_CreateRenderer(gWindow,-1,SDL_RENDERER_ACCELERATED);

            if(gRenderer == NULL){

                success = false;
                printf("Failed to create renderer. Error: %s\n",SDL_GetError());
            }
        }
    }

    return success;
}

void mySDL::free(){

    //Free window and rendrer
    SDL_DestroyWindow(gWindow);
    SDL_DestroyRenderer(gRenderer);
    
    //Set all values to 0
    gWindow = NULL;
    gRenderer = NULL;

}
