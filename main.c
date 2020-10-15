#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <time.h>

#include "menu.h"



int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    putenv("SDL_VIDEO_WINDOW_POS=center");
    SDL_WM_SetCaption("HEX!", NULL);
    SDL_Surface *ecran;
    SDL_WM_SetIcon(IMG_Load("resources/Icon.png"), NULL);

    ecran = SDL_SetVideoMode(1280, 720, 32, SDL_HWSURFACE|SDL_DOUBLEBUF); // Oppen windows

    if (ecran == NULL)
    {
        fprintf(stderr, "Impossible de charger le mode vidéo : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    mainMenu(ecran);

    SDL_Quit();
    return EXIT_SUCCESS;
}
