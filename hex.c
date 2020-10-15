#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include <math.h>

#include "hex.h"
#include "list.h"

int inCercle(SDL_Rect *pos,Cercle cercle)                   // if a position is in the circle
{
    if (pow(pos->x-cercle.x,2)+pow(pos->y-cercle.y,2)<=pow(cercle.r,2))
        return 1;
    else return 0;
}

int pose(SDL_Rect *pos, int *u, int *v)
{
    int i,j;
    Cercle cercle;
    cercle.r = 35;

    for (i=0;i<9;i++)                           // Searching compatible compatible ligne and cologne (i,j)
        for (j=0;j<9;j++)
        {
            cercle.x = 207 + 71*j + 35.99*i;
            cercle.y = 112 + 62.4*i;
            if (inCercle(pos,cercle))
            {
                pos->x = cercle.x;
                pos->y = cercle.y;
                *u=i;   *v=j;
                return 1;
            }
        }
    return 0;
}

void print(int T[9][9],FILE* state)
{
    int i,j,k;
    for (i=0;i<9;i++)
    {
        for (k=0;k<i;k++)
            fprintf(state," ");
        for (j=0;j<9;j++)
            fprintf(state,"%d ",T[i][j]);
        fprintf(state,"\n");
    }
}

int check (int T[9][9], int p ,int i, int j)
{
    switch(abs(p-first)%2+1)
    {
    case 1:
        {
            if(i==0 && T[i][j]==p) wl=1;
            if(i==8 && T[i][j]==p) wr=1;
            if (wl==1 && wr==1) {iwin=1;    return;}


            else if (T[i][j]==p && !inListe(checked,i,j))
            {
                int boolien=0;
                insertR(checked,i,j);
                insertR(way,i,j);
                if (j>-1 && j<9 && i>-2 && i<8) if (check(T,p,i+1,j)==1)   boolien=1;
                if (j>0 && j<10 && i>-2 && i<8) if (check(T,p,i+1,j-1)==1)  boolien=1;
                if (j>-2 && j<8 && i>-1 && i<9) if (check(T,p,i,j+1)==1)    boolien=1;
                if (j>-2 && j<8 && i>0 && i<10) if (check(T,p,i-1,j+1)==1)  boolien=1;
                if (j>-1 && j<9 && i>0 && i<10) if (check(T,p,i-1,j)==1)  boolien=1;
                if (j>0 && j<10 && i>-1 && i<9) if (check(T,p,i,j-1)==1)  boolien=1;
                if (!boolien)    delR(way);
                return 1;
            }
            return 0;
            break;
        }
    case 2:
        {
            if(j==0 && T[i][j]==p) wl=1;
            if(j==8 && T[i][j]==p) wr=1;
            if (wl==1 && wr==1) {iwin=1;    return;}

            else if (T[i][j]==p && !inListe(checked,i,j))
            {
                int boolien=0;
                insertR(checked,i,j);
                insertR(way,i,j);
                if (i>-1 && i<9 && j>-2 && j<8 && check(T,p,i,j+1)==1)   boolien=1;
                if (i>0 && i<10 && j>-2 && j<8 && check(T,p,i-1,j+1)==1)  boolien=1;
                if (i>-2 && i<8 && j>-1 && j<9 && check(T,p,i+1,j)==1)    boolien=1;
                if (i>-2 && i<8 && j>0 && j<10 && check(T,p,i+1,j-1)==1)  boolien=1;
                if (i>-1 && i<9 && j>0 && j<10 && check(T,p,i,j-1)==1)  boolien=1;
                if (i>0 && i<10 && j>-1 && j<9 && check(T,p,i-1,j)==1)  boolien=1;
                if (!boolien)    delR(way);
                return 1;
            }
            return 0;
        }
    }
}

void undo(SDL_Surface* ecran,int T[9][9], List* played,int* p)
{
    SDL_Surface *Player0=IMG_Load("resources/white.png");
    SDL_Rect posPlay;
        posPlay.x = 0;
        posPlay.y = 0;
    SDL_Rect posRet;
        posRet.x=1194;
        posRet.y=651;

    int i,j,k,repeat;  // how many time we repeat undo

    switch(modePlay)
    {
    case 0:
        repeat=1;
        break;
    case 1: case 2:
        repeat=2;
        break;
    }

    for (k=0;k<repeat;k++)
    {
        Elm* pionPlayed=NULL;
        pionPlayed=delR(played);
        afficherListe(played);
        if (pionPlayed != NULL)
        {
            i=pionPlayed->i;    j=pionPlayed->j;
        }
        T[i][j]=0;
        *p=*p%2+1;
        posPlay.x = 207+j*71+i*35.99 - Player0->w/2;
        posPlay.y = 112+i*62.4 - Player0->h/2;
        SDL_BlitSurface(Player0, NULL, ecran, &posPlay);
    }
    SDL_Flip(ecran);
}
