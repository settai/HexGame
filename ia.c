#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "IA.h"
#include "play.h"
#include "hex.h"


void playCPUeasy(SDL_Surface* ecran, int T[9][9], List* played,int p)
{
    SDL_Surface *Player1=IMG_Load("resources/blue.png"), *Player2=IMG_Load("resources/red.png");
    SDL_Rect posPlay;
    int i,j;
    srand(time(NULL));
    do  {i=rand()%9; j=rand()%9;}
    while(T[i][j]);

    T[i][j]=p;
    insertR(played,i,j);
    posPlay.x = 207+j*71+i*35.99 - Player1->w/2;
    posPlay.y = 112+i*62.4 - Player1->h/2;

    switch(abs(p-first)%2+1)
    {
    case 1:
        SDL_BlitSurface(Player1, NULL, ecran, &posPlay);
        break;
    case 2:
        SDL_BlitSurface(Player2, NULL, ecran, &posPlay);
        break;
    }
    SDL_Flip(ecran);
}

void playCPUmeduim(SDL_Surface* ecran, int T[9][9], List* played,int p)
{
    int i,j;
    SDL_Surface *Player2=IMG_Load("resources/red.png"), *Player1=IMG_Load("resources/blue.png");
    SDL_Rect posPlay;

    if(played->len=0)
    {
        srand(time(NULL));
        i=rand()%4+3; j=rand()%4+3;
    }
    else
    {
        int eval[9][9] = {{0}};
        evalution(T,eval,p);
        maxEv(eval,&i,&j);
    }

    T[i][j]=p;
    insertR(played,i,j);
    posPlay.x = 207+j*71+i*35.99 - Player1->w/2;
    posPlay.y = 112+i*62.4 - Player1->h/2;

    switch(abs(p-first)%2+1)
    {
    case 1:
        SDL_BlitSurface(Player1, NULL, ecran, &posPlay);
        break;
    case 2:
        SDL_BlitSurface(Player2, NULL, ecran, &posPlay);
        break;
    }
    SDL_Flip(ecran);
}

void evalution(int T[9][9],int eval[9][9], int p)
{
    int i,j,k;
    int pa=p%2+1;

    FILE* state = NULL;
    state = fopen("state.txt","a+");

    for (i=0;i<9;i++)
        for (j=0;j<9;j++)
            if (T[i][j]==0)
                eval[i][j]=1;

    for (k=0;k<2;k++)
    for (i=0;i<9;i++)
        for (j=0;j<9;j++)
        {
            //test 1:
            if (i<8 && j>0&&j<8 && T[i][j]==pa && T[i][j+1]==0 && T[i][j-1]==0 && T[i+1][j]==0 && T[i+1][j-1]==0)
                if(eval[i+1][j]>4)  eval[i+1][j]=4;

            //test 2:
            if (i<8 && j>0 && T[i][j]==pa)
                {
                    if(T[i+1][j]==p && T[i+1][j-1]==0)
                        if(eval[i+1][j-1]<5) eval[i+1][j-1]=5;
                    else if (T[i+1][j-1]==p && T[i+1][j]==0)
                        if(eval[i+1][j]=5)  eval[i+1][j]=5;
                }

            //test 4:
                //centrer
/*          if (i<7 && j>0 && T[i][j]==pa && ((j<8&&T[i][j+1]==p) || T[i][j-1]==p) && T[i+2][j-1]==0 && T[i+1][j]==0 && T[i+1][j-1]==0)
                if(eval[i+2][j-1]<6) eval[i+2][j-1]=6;

                //left
            if (i<8 && j>1 && T[i][j]==p && T[i+1][j-2]==0 && T[i][j-1]==0 && T[i+1][j-1]==0)
                if(eval[i+1][j-2]<3)   eval[i+1][j-2]=3;

                //right
            if (i<8 && j<8 && T[i][j]==p && T[i+1][j+1]==0 && T[i][j+1]==0 && T[i+1][j]==0)
                if(eval[i+1][j+1]<3)    eval[i+1][j+1]=3;
*/

            //test 6:
                //centrer
            if (i<7 && j>0 && T[i][j]==p && T[i+2][j-1]==p && T[i+1][j]==0 && T[i+1][j-1]==0)
                {
                    if(eval[i+1][j]<2)      eval[i+1][j]=2;
                    if(eval[i+1][j-1]<2)    eval[i+1][j-1]=2;
                }

                //left
            if (i<8 && j>1 && T[i][j]==pa && T[i+1][j-2]==0 && T[i][j-1]==0 && T[i+1][j-1]==0)
                {
                    if(eval[i][j-1]<2)      eval[i][j-1]=2;
                    if(eval[i+1][j-1]<2)    eval[i+1][j-1]=2;
                }

                //right
            if (i<8 && j<8 && T[i][j]==pa && T[i+1][j+1]==0 && T[i][j+1]==0 && T[i+1][j]==0)
                {
                    if(eval[i][j+1]<2) eval[i][j+1]=2;
                    if(eval[i+1][j]<2) eval[i+1][j]=2;
                }


            //test 7:
                //centrer
            if (i<7 && j>0 && T[i][j]==p && T[i+2][j-1]==p)
                {
                    if(T[i+1][j]==pa && T[i+1][j-1]==0)
                        eval[i+1][j-1]=7;
                    else if (T[i+1][j-1]==pa && T[i+1][j]==0)
                        eval[i+1][j]=7;
                }

                //left
            if (i<8 && j>1 && T[i][j]==p && T[i+1][j-2]==p)
                {
                    if(T[i][j-1]==pa && T[i+1][j-1]==0)
                        eval[i+1][j-1]=7;
                    else if (T[i+1][j-1]==pa && T[i][j-1]==0)
                        eval[i+1][j-1]=7;
                }

                //right
            if (i<8 && j<8 && T[i][j]==p && T[i+1][j+1]==p)
                {
                    if(T[i][j+1]==pa && T[i+1][j]==0)
                        eval[i+1][j]=8;
                    else if (T[i+1][j]==pa && T[i][j+1]==0)
                        eval[i][j+1]=8;
                }

                switchBoard(T);
                switchBoard(eval);
    }

    print(T,state);
    print(eval,state);
}

void switchBoard(int T[9][9])   // flip board 180°
{
    int temp[9][9];
    int i,j;

    for(i=0;i<9;i++)
        for(j=0;j<9;j++)
            temp[i][j]=T[i][j];

    for(i=0;i<9;i++)
        for(j=0;j<9;j++)
            T[i][j]=temp[8-i][8-j];

}

void flipBoard(int T[9][9])
{
    int temp[9][9];
    int i,j;

    for(i=0;i<9;i++)
        for(j=0;j<9;j++)
            temp[i][j]=T[i][j];

    for(i=0;i<9;i++)
        for(j=0;j<9;j++)
            T[i][j]=temp[j][i];
}

void maxEv(int eval[9][9], int *u, int *v)
{
    int i=0,j=0;
    int temp=0;
    *u=i; *v=j;

    for (i=0;i<9;i++)
        for (j=0;j<9;j++)
            if(temp<eval[i][j])
            {
              temp=eval[i][j];
              *u=i; *v=j;
            }
}
