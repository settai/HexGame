#ifndef IA_H_INCLUDED
#define IA_H_INCLUDED

#include "list.h"

void playCPUeasy(SDL_Surface* ecran, int T[9][9], List* played, int p);
void playCPUmeduim(SDL_Surface* ecran, int T[9][9], List* played, int p);
void evalution(int T[9][9],int eval[9][9], int p);
void maxEv(int eval[9][9], int *u, int *v);
void switchBoard(int T[9][9]);

#endif //
