#include<iostream>
#include<SDL.h>

//using namespace std;

enum KeyPressSurfaces
{
    KEY_PRESS_SURFACE_DEFAULT, //0
    KEY_PRESS_SURFACE_UP,      //1
    KEY_PRESS_SURFACE_DOWN,    //2
    KEY_PRESS_SURFACE_LEFT,    //3
    KEY_PRESS_SURFACE_RIGHT,   //4
    KEY_PRESS_SURFACE_TOTAL    //5
};

const int SCREEN_HEIGHT = 480;
const int SCREEN_WIDTH = 640;
SDL_Window* window = NULL;
SDL_Surface* surface = NULL;
SDL_Surface* keypresssurface[KEY_PRESS_SURFACE_TOTAL];
// tao surface cho tung phim
// de in tung anh tuong ung voi tung phim
SDL_Surface* current = NULL;

SDL_Surface* loadSurface(std::string path)
{
    SDL_Surface* temp = SDL_LoadBMP(path.c_str());
    return temp;
}

void close()
{
    SDL_FreeSurface(current);
    current = NULL;
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argc, char* args[])
{
    window = SDL_CreateWindow("Testing", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    surface = SDL_GetWindowSurface(window);
    bool quit = false;
    SDL_Event e;
    keypresssurface[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("3rd_lesson_image/press.bmp");
    keypresssurface[KEY_PRESS_SURFACE_UP] = loadSurface("3rd_lesson_image/up.bmp");
    keypresssurface[KEY_PRESS_SURFACE_DOWN] = loadSurface("3rd_lesson_image/down.bmp");
    keypresssurface[KEY_PRESS_SURFACE_LEFT] = loadSurface("3rd_lesson_image/left.bmp");
    keypresssurface[KEY_PRESS_SURFACE_RIGHT] = loadSurface("3rd_lesson_image/right.bmp");
    current = keypresssurface[KEY_PRESS_SURFACE_DEFAULT];
    while(!quit)
    {
        while(SDL_PollEvent(&e) != 0)
        {
            if(e.type == SDL_QUIT) quit =true;
            else if(e.type = SDL_KEYDOWN)
            {
                switch(e.key.keysym.sym)
                {
                    case SDLK_UP:
                    current = keypresssurface[KEY_PRESS_SURFACE_UP];
                    break;
                    case SDLK_DOWN:
                    current = keypresssurface[KEY_PRESS_SURFACE_DOWN];
                    break;
                    case SDLK_RIGHT:
                    current = keypresssurface[KEY_PRESS_SURFACE_RIGHT];
                    break;
                    case SDLK_LEFT:
                    current = keypresssurface[KEY_PRESS_SURFACE_LEFT];
                    break;
                    default:
                    current = keypresssurface[KEY_PRESS_SURFACE_DEFAULT];
                    break;
                }
            }
            SDL_BlitSurface(current, NULL, surface, NULL);
            SDL_UpdateWindowSurface(window);
        }
    }
    close();
    return 0;
}
