#ifndef DEF_HEX
#define DEF_HEX

#include "list.h"
#include "menu.h"

int first;

typedef struct Cercle Cercle;
struct Cercle
{
    int x;
    int y;
    int r;
};

int inCercle(SDL_Rect *pos,Cercle cercle);
int pose(SDL_Rect *pos,int *i,int *j);
int check(int T[9][9],int p,int i,int j);
void undo(SDL_Surface *ecran,int T[9][9], List* played,int* p);

void print(int T[9][9],FILE* state);

#endif
