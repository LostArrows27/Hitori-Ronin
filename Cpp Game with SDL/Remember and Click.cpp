#include "Header/Common.h"
#include "Header/BaseObject.h"
#include "Header/Character.h"

using namespace std;

BaseObject g_background;

bool InitData()
{
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if(ret < 0) return false;
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(window == NULL) success = false;
    else
    {
        render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if(render == NULL) success = false;
        else
        {
            SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
            int imgFlag = IMG_INIT_PNG;
            if(!(IMG_Init(imgFlag) && imgFlag)) success = false;
        }
    }
    return success;
}

bool loadBackground()
{
    bool ret = g_background.loadImg("Image/my_bg.png", render);
    if(ret = false) return false;
    return true;
}

void close()
{
    g_background.Free();
    SDL_DestroyRenderer(render);
    render = NULL;
    SDL_DestroyWindow(window);
    window = NULL;
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* argv[])
{
    if(InitData() == false) return -1;
    if(loadBackground() == false) return -1;
    Character p_player;
    p_player.LoadImg("Character/run_right.png", render);
    p_player.Set_Clip();
    bool is_quit = false;
    while(!is_quit)
    {
        while(SDL_PollEvent(&e) != 0)
        {
            if(e.type  == SDL_QUIT) is_quit = true;
            p_player.HandleInput(e, render);
        }
        SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
        SDL_RenderClear(render);
        g_background.Render(render, NULL);
        p_player.DoPlayer();
        p_player.Show(render);
        SDL_RenderPresent(render);
    }
    close();
    return 0;
}

