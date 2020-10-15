#ifndef PVSP_H_INCLUDED
#define PVSP_H_INCLUDED

#include "list.h"

void play(SDL_Surface* ecran);
void pause(SDL_Surface* ecran, List* played, int T[9][9]);
void save(List *liste,int T[9][9], SDL_Surface* ecran);
int load(List *liste, int T[9][9], SDL_Surface* ecran);
void playHumain(SDL_Surface* ecran,int T[9][9], List* played,int* p);

#endif // PVSP_H_INCLUDED
