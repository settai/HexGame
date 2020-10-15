#include <stdlib.h>
#include <stdio.h>

#include "list.h"

List* init()
{
    List* liste = (List*) malloc(sizeof(*liste));
    if (liste == NULL)  exit(EXIT_FAILURE);

    liste->first= NULL;
    liste->last = NULL;
    liste->len=0;
    return liste;
}

void insertR(List *liste, int i,int j)
{
    Elm* New = (Elm*) malloc(sizeof(*New));
    if (liste == NULL || New == NULL)   exit(EXIT_FAILURE);
    New->i = i;
    New->j= j;
    New->next = NULL;
    if (liste->last == NULL)
    {
        New->prev = NULL;
        liste->first = New;
    }
    else
    {
        New->prev = liste->last;
        liste->last->next = New;
    }
    liste->last = New;
    liste->len++;
}

void insertL(List *liste, int i,int j)
{
    Elm* New = (Elm*) malloc(sizeof(*New));
    if (liste == NULL || New == NULL)   exit(EXIT_FAILURE);
    New->i = i;
    New->j= j;
    New->prev = NULL;
    if (liste->first == NULL)
    {
        New->next = NULL;
        liste->last = New;
    }
    else
    {
        New->next = liste->first;
        liste->first->prev = New;
    }
    liste->first = New;
    liste->len++;
}

Elm* delR(List *liste)
{
    //if (liste == NULL)  return NULL;
    if (liste->last != NULL)
    {
        Elm *deleted = liste->last;
        liste->last->next = NULL;
        liste->last = liste->last->prev;
        liste->len--;
        return deleted;
    }
    else return NULL;

}

void delL(List *liste)
{
    //if (liste == NULL)  exit(EXIT_FAILURE);

    if (liste->first != NULL)
    {
        Elm *deleted = liste->first;
        liste->first->prev = NULL;
        liste->first = liste->first->next;
        free(deleted);
        liste->len--;
    }
}

void afficherListe(List *liste)
{
    FILE* test = fopen("test.txt","r+");
    //if (liste == NULL)  exit(EXIT_FAILURE);
    int i;
    Elm *actuel = liste->first;

    for (i=0;i<liste->len;i++)
    {
        fprintf(test,"(%d,%d) ->", actuel->i, actuel->j);
        actuel = actuel->next;
    }
    fprintf(test," NULL \n");
    fclose(test);
}

int inListe(List* liste,int i, int j)
{
    if (liste == NULL)   return 0;
    int k;
    Elm *actuel = liste->first;
    for (k=0;k<liste->len;k++)
    {
        if (actuel->i==i && actuel->j==j)
            return 1;
        actuel = actuel->next;
    }
    return 0;
}
