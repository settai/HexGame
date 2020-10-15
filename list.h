#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

typedef struct Element Elm;
struct Element
{
    int i;
    int j;
    Elm* next;
    Elm* prev;
};

typedef struct List List;
struct List
{
    int len;
    Elm *first;
    Elm *last;
};

List* init(void);

List* way;
List* checked;
int wl, wr,iwin;

void insertR(List *liste, int i, int j);
void insertL(List *liste, int i, int j);
Elm* delR(List* liste);
void delL(List* liste);

int inListe(List* liste,int i,int j);
void afficherListe(List *liste);

#endif
