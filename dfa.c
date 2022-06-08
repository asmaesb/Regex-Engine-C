#include "prj.h"

int TAB[20][20];
int  row = -1;

int dfaNum = 0;


int dfaindex()
{
    return dfaNum ++;
}


int duplicateCheck(state **stTable, state *nfa)
{
    if(!stTable)
        return -1;
    int i = 0;
    while (stTable[i])
    {
        if (stTable[i]->index == nfa->index)
            return 1;
        i++;
    }
    return 0;
}

void e_cloture(state **stateTable, state *nfa)
{
    static int i = 0;
    state *tmp = nfa;
    if(!stateTable)
        return;
    if (duplicateCheck(stateTable, nfa) != 0)
        return;
    stateTable[i] = nfa;
    i++;
    if (nfa->etiquette[0] == 'e')
    {
        e_cloture(stateTable, nfa->st1);
    }
    if (nfa->etiquette[1] == 'e')
    {
        e_cloture(stateTable, nfa->st2);
    }
    if (stateTable[i + 1] != NULL)
        stateTable[i + 1] = NULL;
    nfa = tmp;
    return;
}


void sort(int *tab, int n)
{
    if(!tab)
        return ;
    int i, j;
    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - i - 1; j++)
            if (tab[j] > tab[j + 1])
            {
                int temp = tab[j];
                tab[j] = tab[j+1];
                tab[j+1] = temp;
            }
}

int *indtablegen(state **states)
{
    if (!states)
        return NULL;
    int *tab;
    int i = 0;
    int j =0;
    while (states[i])
        i++;
    tab = malloc((i + 1) * sizeof(int));
    while (states[j])
    {
        tab[j] = states[j]->index;
        j++;
    }
    sort(tab, i);
    tab[j] = -1;
    return tab;
}

int size(int *t)
{
    if (!t)
        return 0;
    int i=0;
    while(t[i] != -1)
        i++;
    i++;
    return i;
}


int verification(int *t, int n)
{
    if (!t)
        return -1;

    int i =0;
    while (i <= row)
    {
        int j = 0;
        while (j < n)
        {
            if(TAB[i][j] == t[j])
                j++;
            else
                break ;
        }
        if (j == n)
        {
            int x;
            while(TAB[i][x] != -1)
                x++;
            return TAB[i][x + 1];
        }
        i++;
    }
    return 0;
}

void fillTAB(int *t, int n,int index)
{
    if(verification(t,n) != 0 )
        return;
    row++;
    int i = 0;
    while (i < n)
    {
        TAB[row][i] = t[i];
        i++;
    }
    TAB[row][i]  = index;
}

int statetype(state **nfa)
{
    if(!nfa)
        return 0;
    int i =0;
    int t = 0;
    while(nfa[i])
    {
        if(nfa[i]->type == 0 && t != 1)
            t += 1;
        if(nfa[i]->type == 2 && t != 2)
            t += 2;
        i++;
    }
    return t;
}

state **grpA(state **t)
{
    int i= 0;
    int j =0;
    int x;

    state **A;
    A = malloc(20*sizeof(state *));
    while(t[i])
    {
        if(t[i]->etiquette[0] == 'a')
        {
            A[j] = t[i]->st1;
            j++;
        }
        i++;
    }
    i = 0;
    do
    {
        x = j;
        while(i < j)
        {
            if(A[i]->etiquette[0] == 'e')
            {
                A[j] = A[i]->st1;
                j++;
            }
            if(A[i]->etiquette[1] == 'e')
            {
                A[j] = A[i]->st2;
                j++;
            }
            i++;
        }
        i = j - 1;
    } while (x != j);
    A[j] = NULL;
    if (j == 0)
        return NULL;
    return A;
}

state **grpB(state **t)
{
    int i= 0;
    int j =0;
    int x;

    state **B;
    B = malloc(20*sizeof(state *));
    while(t[i])
    {
        if(t[i]->etiquette[0] == 'b')
        {
            B[j] = t[i]->st1;
            j++;
        }
        i++;
    }
    i = 0;
    do
    {
        x = j;
        while(i < j)
        {
            if(B[i]->etiquette[0] == 'e')
            {
                B[j] = B[i]->st1;
                j++;
            }
            if(B[i]->etiquette[1] == 'e')
            {
                B[j] = B[i]->st2;
                j++;
            }
            i++;
        }
        i = j -1;
    } while (x != j);
    B[j] = NULL;
    if (j == 0)
        return NULL;
    return B;
}

dfa *dmake(int i, char c)
{
    dfa *d;
    d = malloc(sizeof(dfa *)*10);
    d->index = i;
    d->etiquette[0] = c;
    d->a = NULL;
    d->b = NULL;
    return d;
}

dfa *dfagen(state **stack)
{
    if (stack == NULL)
        return NULL;

    dfa *tmp;
    tmp = malloc(sizeof(dfa));
    tmp->index = dfaindex();
    int *t = indtablegen(stack);
    fillTAB(t,size(t),tmp->index);
    tmp->type = statetype(stack);
    state **B;
    B = grpB(stack);
    int *tB = indtablegen(B);
    int z = size(tB);

    int y = verification(tB, z);
    if (y != 0)
    {
        if(B != NULL)
        {
            tmp->etiquette[1] = 'b';
            tmp->b = dmake(y, 'b');
        }
        else
            tmp->b = NULL;
    }
    else
    {
        
        tmp->etiquette[1] = 'b';
        tmp->b = dfagen(B);
    }
    state **A;
    A = grpA(stack);
    
    int *tA = indtablegen(A);
    int zz = verification(tA, size(tA));
    if ( zz != 0)
    {
        if(A != NULL)
        {
            tmp->etiquette[0] = 'a';
            //printf("next index %d\n",zz);
            tmp->a = dmake(zz, 'a');
        }
        else
            tmp->a = NULL;
    }
    else
    {
        
        tmp->etiquette[0] = 'a';
        tmp->a = dfagen(A);
    }
    free (stack);
    
    return tmp;
}

dfa *finalgrp(state *nfa)
{
    dfa *tmp;
    state **stategrp;
    tmp = malloc(sizeof(dfa));
    stategrp = malloc(sizeof(state *)*10);
    e_cloture(stategrp, nfa);
    tmp = dfagen(stategrp);
    return tmp;
}

void showcase(dfa *df)
{
    dfa *tmp = df;
    char *types[] = {"mid","initial", "final","init-final"};
    
    if (!df)
        return;

    printf("dfa : %p\n", df);
    printf("dfa num : %d\n",df->index);
    printf("etat %s\n", types[df->type]);
    for (int i = 0; i < 2; i++)
    {
        char etiq[2];
        etiq[0] = df->etiquette[i];
        etiq[1] = '\0';
        printf("etiquette%d : %s\n", i + 1,
               (df->etiquette[i] == 'a' || df->etiquette[i] == 'b')
                   ? etiq
                   : "vide");
        printf("dfa : %p\n", i == 0 ? df->a : df->b);
    }
    printf("---------\n");
    if(df->is_etoile == 1 )
        return;
    showcase(df->a);
    showcase(tmp->b);
}
