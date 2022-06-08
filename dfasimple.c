#include "prj.h"

dfa *BB[20];
int i = -1;

dfa *DFA[20];
int j =0;

void fill(dfa *d)
{
    if (!d)
        return;
        i++;
    BB[i] = d;
    
    fill(d->a);
    fill(d->b);
    if (BB[i + 1] != NULL)
        BB[i + 1] = NULL;
}

void nodub()
{
    DFA[j] = BB[0];
    j++;
    int x = 1;
    while(BB[x])
    {
        for(int k = 0; k<x;k++)
        {
            
            if(BB[x]->index == DFA[k]->index)
                break;
        }
        DFA[j] = BB[x];
        j++;
        x++;
    }
    DFA[j] = NULL;
}

int dfaCompare(dfa *d)
{
    int ind = 0;
    if(!d)
        return -1;
    while(DFA[ind])
    {
        if (d->index == DFA[ind]->index)
            return ind;
        ind++;  
    }
    return -1;
}




void finalDFA()
{

    int inde = 0;

    while(DFA[inde])
    {
        dfa *st11 = DFA[inde]->a;

        int plca = dfaCompare(st11);
        if(plca != -1 && st11 != NULL && st11 != DFA[plca])
        {
            //printf("in a\n");
            DFA[inde]->is_etoile = 1;
            DFA[inde]->a = DFA[plca];
        }
        dfa *st12 = DFA[inde]->b;
        int plcb = dfaCompare(st12);
        if(plcb != -1 && st12 != NULL && st12 != DFA[plcb])
        {
            //printf("in b\n");
            DFA[inde]->is_etoile = 1;
            DFA[inde]->b = DFA[plcb];
        }
        inde++;

    }
}


void whole(dfa *d)
{
    fill(d);
    nodub();
    //pri();
    finalDFA();
}

// int main()
// {
//      state *nfa;
//     nfa = malloc(sizeof(state));
//     nfa = nfagen("ba*.");
//     dfa *A;
//     A = finalgrp(nfa);
//     showcase(A);
//     printf("++++++++\n");
//     whole(A);
    
//     showcase(A);
//     return 0;
// }