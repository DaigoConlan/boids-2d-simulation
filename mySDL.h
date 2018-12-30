//This file contains the setup for sdl

#ifndef MYSDL_H 
#define MYSDL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#define DEFAULT_WINDOW_WIDTH 1280
#define DEFAULT_WINDOW_HEIGHT 960
#define DEFAULT_WINDOW_X 0
#define DEFAULT_WINDOW_Y 0

class mySDL{

    private:
        //Pointer to window
        SDL_Window* gWindow;

        //Pointer to renderer
        SDL_Renderer* gRenderer;
        
        //The x and y position of the window
        int windowX,windowY;

        //The width and height of the window
        int windowW,windowH;

        std::string title;

    public:

        //Constructor
        mySDL();

        //Destructor
        ~mySDL();

        //Set the name of the window
        void setTitle(std::string newTitle);

        //Set the size of the window
        void setWindowSize(int width,int height);

        //set the window position
        void setWindowPosition(int x,int y);

        //get the width of the window
        int getWindowWidth();

        //get the height of the window
        int getWindowHeight();
        
        //get Renderer
        SDL_Renderer* getRenderer();

        //Render
        void render();

        //init SDL
        bool init();

        //closes SDL
        void free();

};




#endif 