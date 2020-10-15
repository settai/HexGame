#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "play.h"
#include "menu.h"
#include "hex.h"

void play(SDL_Surface* ecran)
{
    /** load SDl Surfaces **/
    SDL_Surface *HEX=IMG_Load("resources/hexgame.jpg");
    SDL_Surface *retBlue=IMG_Load("resources/retBlue.png");
    SDL_Surface *player1, *player2;
    SDL_BlitSurface(HEX, NULL, ecran, NULL);

    TTF_Init();
    TTF_Font *police = TTF_OpenFont("resources/hex.ttf", 30);
    TTF_Font *police1 = TTF_OpenFont("resources/hex.ttf", 50);

    SDL_Color redColor = {230, 19, 19};
    SDL_Color blueColor = {41, 41, 232};

    SDL_Rect posPlayer1;
        posPlayer1.x = 1100;
        posPlayer1.y = 3;
    SDL_Rect posPlayer2;
        posPlayer2.x = 12;
        posPlayer2.y = 682;
    SDL_Rect posRet;
        posRet.x=1194;
        posRet.y=651;

    FILE* state = NULL;
    state = fopen("state.txt","a");

    srand(time(NULL));
    int i=0,j=0;
    srand(time(NULL));
    int p;
    first = rand()%2+1;

    int T[9][9]={{0}};
    iwin=0;
    List* played=init();

    if (load(played,T,ecran))   p=played->len%2+1;
    SDL_Flip(ecran);

    if (modePlay==2) first = 1;
    p=first;

    switch(p)  // attribute color to players
    {
    case 1:
        SDL_BlitSurface(retBlue, NULL, ecran, &posRet);
        player1 = TTF_RenderText_Blended(police, "player 1", blueColor);
        if (modePlay==0)
            player2 = TTF_RenderText_Blended(police, "player 2", redColor);
        else
            player2 = TTF_RenderText_Blended(police, "CPU", redColor);
        break;

     case 2:
        SDL_BlitSurface(retBlue, NULL, ecran, &posRet);
        player1 = TTF_RenderText_Blended(police, "player 1", redColor);
        if (modePlay==0)
            player2 = TTF_RenderText_Blended(police, "player 2", blueColor);
        else
            player2 = TTF_RenderText_Blended(police, "CPU", blueColor);
        break;
    }
    SDL_BlitSurface(player1, NULL, ecran, &posPlayer1);
    SDL_BlitSurface(player2, NULL, ecran, &posPlayer2);
    SDL_Flip(ecran);



    int continuer;
    int stop=0;
    while (!stop)
    {
        switch (p)
        {
        case 1:
            playHumain(ecran,T,played,&p);
            break;
        case 2:
            switch (modePlay)
            {
            case 0:
                playHumain(ecran,T,played,&p);
                break;
            case 1:
                playCPUeasy(ecran,T,played,p);
                break;
            case 2:
                playCPUmeduim(ecran,T,played,p);
                break;
            }
            break;
        }

        way = init();
        checked = init();
        wl=0;
        wr=0;

        i=played->last->i; j=played->last->j;
        check(T,p,i,j);

        if (iwin)
        { win(ecran,p); stop=1;}
        p=p%2+1;
        free(way);
        free(checked);
    }
}


void pause(SDL_Surface* ecran, List* played, int T[9][9])
{
    SDL_Surface *temp=IMG_Load("resources/hexgame.jpg");
    SDL_BlitSurface(ecran, NULL, temp, NULL);
    SDL_Surface *Win=IMG_Load("resources/Pause.png");
    SDL_BlitSurface(Win, NULL, ecran, NULL);
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
                    if (event.button.x>414 && event.button.x<500 && event.button.y>182 && event.button.y<270)
                        {
                        SDL_BlitSurface(temp, NULL, ecran, NULL);
                        return;
                        }
                    else if (event.button.x>414 && event.button.x<500 && event.button.y>300 && event.button.y<390)
                        play(ecran);
                    else if (event.button.x>414 && event.button.x<500 && event.button.y>414 && event.button.y<500)
                        save(played,T,ecran);
                    else if (event.button.x>414 && event.button.x<500 && event.button.y>520 && event.button.y<609)
                        mainMenu(ecran);
                }
                break;
        }
    }
}


void playHumain(SDL_Surface* ecran,int T[9][9], List* played,int* p)
{
    SDL_Surface *pionBlue=IMG_Load("resources/blue.png"), *pionRed=IMG_Load("resources/red.png");
    SDL_Surface *retBlue=IMG_Load("resources/retBlue.png"), *retRed=IMG_Load("resources/retRed.png"), *temp;

    int i=0,j=0,continuer =0;
    SDL_Event event;
    SDL_Rect posPlay;
    SDL_Rect posRet;
        posRet.x=1194;
        posRet.y=651;

    while (!continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
        case SDL_QUIT:
            exit(0);
            break;
        case SDL_MOUSEBUTTONUP:
            {
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                if (event.button.x>1186 && event.button.x<1250 && event.button.y>643 && event.button.y<707 && played->len>0)
                    {
                    undo(ecran,T,played,&p);
                    }
                else if (event.button.x>17 && event.button.x<83 && event.button.y>10 && event.button.y<78)
                    pause(ecran,played,T);
                else
                {
                    posPlay.x = event.button.x;
                    posPlay.y = event.button.y;
                    if (pose(&posPlay,&i,&j) && T[i][j] == 0)
                    {
                        T[i][j]=*p;
                        insertR(played,i,j);
                        posPlay.x -= pionBlue->w / 2;
                        posPlay.y -= pionBlue->h / 2;
                        continuer = 1;
                    }
                }
            }
            }
        }
    }
    switch (abs(*p-first)%2+1)
    {
        case 1:
        {
            SDL_BlitSurface(retRed, NULL, ecran, &posRet);
            SDL_BlitSurface(pionBlue, NULL, ecran, &posPlay);
            SDL_Flip(ecran);
            break;
        case 2:
            SDL_BlitSurface(retBlue, NULL, ecran, &posRet);
            SDL_BlitSurface(pionRed, NULL, ecran, &posPlay);
            SDL_Flip(ecran);
            break;
        }
    }
}

void save(List *liste,int T[9][9], SDL_Surface* ecran)
{
    SDL_Surface *temp=IMG_Load("resources/hexgame.jpg"), *saved=IMG_Load("resources/save.png");
    SDL_BlitSurface(ecran, NULL, temp, NULL);
    SDL_BlitSurface(saved, NULL, ecran, NULL);
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

            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    if (event.button.x>452 && event.button.x<553 && event.button.y>409 && event.button.y<525)
                    {
                        continuer= 1;
                        break;
                    }

                    else if (event.button.x>750 && event.button.x<854 && event.button.y>409 && event.button.y<525)
                        {
                            SDL_BlitSurface(temp, NULL, ecran, NULL);
                            SDL_Flip(ecran);
                            return ;
                        }
                }
        }
    }

    FILE* savedata = fopen("save/savedata.txt","w+");
    int i,j,k;
    Elm *actuel = liste->first;
    fprintf(savedata,"%d", liste->len);
    for (k=0;k<liste->len;k++)
    {
        i=actuel->i; j=actuel->j;
        fprintf(savedata,"\n[%d,%d,%d]", i, j,T[i][j]);
        actuel = actuel->next;
    }
    fclose(savedata);
    SDL_BlitSurface(temp, NULL, ecran, NULL);
    SDL_Flip(ecran);
}

int load(List *liste, int T[9][9], SDL_Surface* ecran)
{
    SDL_Surface *temp=IMG_Load("resources/hexgame.jpg"), *load=IMG_Load("resources/load.png");
    SDL_BlitSurface(ecran, NULL, temp, NULL);
    SDL_BlitSurface(load, NULL, ecran, NULL);
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

            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    if (event.button.x>452 && event.button.x<553 && event.button.y>409 && event.button.y<525)
                    {
                        continuer= 1;
                        break;
                    }

                    else if (event.button.x>750 && event.button.x<854 && event.button.y>409 && event.button.y<525)
                    {
                        SDL_BlitSurface(temp, NULL, ecran, NULL);
                        SDL_Flip(ecran);
                        return 0;
                    }
                }
        }
    }
    liste = init();
    FILE* savedata = fopen("savedata.txt","r+");

    int k,i=0,j=0,len;
    fscanf(savedata,"%d\n",&len);
    for (k=0;k<len;k++)
    {
        fscanf(savedata,"[%d,%d,%d]\n",&i,&j,&T[i][j]);
        insertR(liste,i,j);
    }

    SDL_BlitSurface(temp, NULL, ecran, NULL);
    SDL_Surface *Player1=IMG_Load("resources/red.png"), *Player2=IMG_Load("resources/blue.png");
    Elm* actuel = liste->first;
    SDL_Rect posLoad;

    for (k=0;k<liste->len;k++)
    {
        i=actuel->i; j=actuel->j;
        printf("%d-%d",i,j);
        switch(T[i][j])
        {
        case 1:
            posLoad.x = 207+j*71+i*35.99 - Player1->w/2;
            posLoad.y = 112+i*62.4 - Player1->h/2;
            SDL_BlitSurface(Player1, NULL, ecran, &posLoad);
            break;

        case 2:
            posLoad.x = 207+j*71+i*35.99 - Player2->w/2;
            posLoad.y = 112+i*62.4 - Player2->h/2;
            SDL_BlitSurface(Player2, NULL, ecran, &posLoad);
            break;
        }
        actuel = actuel->next;
    }
    fclose(savedata);
    SDL_Flip(ecran);
    afficherListe(liste);
    return 1;
}

