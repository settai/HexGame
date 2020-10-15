#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "menu.h"


void mainMenu(SDL_Surface* ecran)
{
    SDL_Surface *MainMenu = NULL;
    SDL_Surface *playButton = NULL, *helpButton = NULL , *settingButton = NULL;

    MainMenu = IMG_Load("resources/MainMenu.jpg");
    playButton = IMG_Load("resources/playButton.png");
    helpButton = IMG_Load("resources/helpButton.png");
    settingButton = IMG_Load("resources/settingButton.png");
    SDL_BlitSurface(MainMenu, NULL, ecran, NULL);
    SDL_Flip(ecran);
    SDL_Event event;

    SDL_Rect posPlay;
    posPlay.x=792;
    posPlay.y=372;
    SDL_Rect posHelp;
    posHelp.x=1026;
    posHelp.y=532;
    SDL_Rect posSetting;
    posSetting.x=0;
    posSetting.y=528;

    int continuer=0;
    while (!continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer=1;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    continuer=1;
                break;
            case SDL_MOUSEMOTION:
                SDL_BlitSurface(MainMenu, NULL, ecran, NULL);

                if (event.button.x>897 && event.button.x<1029 && event.button.y>486 && event.button.y<600)
                    SDL_BlitSurface(playButton, NULL, ecran, &posPlay);
                else if (event.button.x>1122 && event.button.x<1233 && event.button.y>615 && event.button.y<720)
                    SDL_BlitSurface(helpButton, NULL, ecran, &posHelp);
                else if (event.button.x>31 && event.button.x<146 && event.button.y>615 && event.button.y<720)
                    SDL_BlitSurface(settingButton, NULL, ecran, &posSetting);
                SDL_Flip(ecran);
                break;

            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    if (event.button.x>915 && event.button.x<1011 && event.button.y>508 && event.button.y<579)
                        modeMenu(ecran);
                    else if (event.button.x>1122 && event.button.x<1233 && event.button.y>615 && event.button.y<720)
                        HowTo(ecran);
                }
                break;
        }
    }
    SDL_FreeSurface(MainMenu);
}

void modeMenu(SDL_Surface* ecran)
{
    SDL_Surface *selectMenu = NULL;
    selectMenu = IMG_Load("resources/selectMenu.jpg");
    SDL_BlitSurface(selectMenu, NULL, ecran, NULL);
    SDL_Flip(ecran);

    SDL_Event event;
    int continuer=0;
    while (!continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                exit(0);
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    exit(0);
                break;

            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    if (event.button.x>230 && event.button.x<1008 && event.button.y>180 && event.button.y<300)
                      {  modePlay=0;    continuer=1; }
                    else if (event.button.x>230 && event.button.x<1008 && event.button.y>340 && event.button.y<450)
                      {  modePlay=1;    continuer=1; }
                    else if (event.button.x>230 && event.button.x<1008 && event.button.y>483 && event.button.y<610)
                      {  modePlay=2;    continuer=1; }
                }
                break;
        }
    }
    play(ecran);
}

void HowTo(SDL_Surface* ecran)
{
    SDL_Surface *HTP = IMG_Load("resources/HowToPlay.png");
    SDL_BlitSurface(HTP, NULL, ecran, NULL);
    SDL_Flip(ecran);
    SDL_Event event;

    int continuer=0;
    while (!continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                exit(0);
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    exit(0);
                break;

            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    if (event.button.x>880 && event.button.x<951 && event.button.y>514 && event.button.y<600)
                        modeMenu(ecran);
                }
                break;
        }
    }
}

void win(SDL_Surface* ecran,int p)
{
    SDL_Surface *Win=IMG_Load("resources/Win.png");
    SDL_Surface *player1, *player2;
    SDL_Color whiteColor = {255, 255, 255};
    SDL_BlitSurface(Win, NULL, ecran, NULL);

    SDL_Rect posWin;
    posWin.x = 415;
    posWin.y = 155;

    TTF_Init();
    TTF_Font *police = TTF_OpenFont("resources/hex.ttf", 42);
    player1 = TTF_RenderText_Blended(police, "Player 1 Win!", whiteColor);
    switch(modePlay)
    {
    case 0:
        player2 = TTF_RenderText_Blended(police, "Player 2 Win!", whiteColor);
        break;
    case 1: case 2:
        player2 = TTF_RenderText_Blended(police, "CPU Win!", whiteColor);
    }
    player2 = TTF_RenderText_Blended(police, "Player 2 Win!", whiteColor);

    switch(p)
    {
    case 1:
        SDL_BlitSurface(player1, NULL, ecran, &posWin);
        break;
    case 2:
        SDL_BlitSurface(player2, NULL, ecran, &posWin);
    }
    SDL_Flip(ecran);
    SDL_Event event;

    int continuer=0;
    while (!continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                exit(0);
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    exit(0);
                break;

            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    if (event.button.x>406 && event.button.x<846 && event.button.y>279 && event.button.y<354)
                        play(ecran);
                    else if (event.button.x>406 && event.button.x<846 && event.button.y>423 && event.button.y<504)
                        mainMenu(ecran);
                }
                break;
        }
    }
}
