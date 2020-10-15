#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "list.h"
#include "hex.h"

int modePlay;

void HowTo(SDL_Surface* ecran);
void mainMenu(SDL_Surface* ecran);
void modeMenu(SDL_Surface* ecran);
void win(SDL_Surface* ecran,int p);

#endif // MENU_H_INCLUDED
