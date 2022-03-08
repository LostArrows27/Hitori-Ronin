#include<iostream>
#include<SDL.h>

using namespace std;

const int SCREEN_HEIGHT = 600;
const int SCREEN_WIDTH = 600;
//khai bao kich thuoc cua so

bool init();
//khoi dong SDL va render window

bool loadMedia();
//loads Media;

void close();
//Giai phong media va tat SDL

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gHelloWorld = NULL;
// khoi tao window, surface of window va loading area of image

bool init()
{
    bool success = true;
    // bool se tra ve false neu chuong trinh co loi
    if(SDL_Init(SDL_INIT_VIDEO)<0)
    {
        cout << "SDL could not intialize! SDL_Error: " << SDL_GetError();
        success = false;
    }
    else
    {
        gWindow = SDL_CreateWindow("Getting an image on the screen", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(gWindow == NULL)
        {
            cout << "Window could not be created! SDL_Error: " << SDL_GetError();
            success = false;
        }
        else
        {
            gScreenSurface = SDL_GetWindowSurface(gWindow);
            return success;
        }
    }
}

bool loadMedia()
{
    bool success = true;
    gHelloWorld = SDL_LoadBMP("2nd_lesson_image/testing_02.bmp");
    if(gHelloWorld == NULL){
        cout << "Unable to load image! SDL_Error: " << SDL_GetError();
        success = false;
    }
    return success;
}

void close()
{
    SDL_FreeSurface(gHelloWorld);
    gHelloWorld = NULL;
    // Giai phong image khoi surface
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
}

int main(int argc, char* args[]){
    if(!init())
    {
        cout << "Failed to intitalize!" << endl;
    }else
    {
        if(!loadMedia())
        {
            cout << "Failed to load media" << endl;
        }
        else
        {
            SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);
            // in anh len man hinh
            SDL_UpdateWindowSurface(gWindow);
            //update anh len man hinh sau khi da in
            SDL_Delay(2000);
        }
    }
    close();
    return 0;
}
