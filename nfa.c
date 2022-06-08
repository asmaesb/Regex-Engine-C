#include "prj.h"

state *stack1[20];
int top1 = -1;
int stateNum = 0;

void pushNFA(state *nfa)
{
    stack1[++top1] = nfa;
}

state *popNFA()
{
    if (top1 == -1)
        return NULL;
    else
        return stack1[top1--];
}

int stateindex()
{
    return stateNum ++;
}

void mid(state **nfa)
{
    if (!*nfa)
        return;
    (*nfa)->type = 1;
}


state *finaliser(void)
{
    state *final;
    final = malloc(sizeof(state));
    
    final->type = 2;
    final->index = stateindex();
    final->st1 = NULL;
    final->st2 = NULL;
    return final;
}


state *charAFND(char c)
{
    state *nfa;
    nfa = malloc(sizeof(state));
    
    nfa->type = 0;
    nfa->index = stateindex();
    nfa->etiquette[0] = c;
    nfa->st1 = finaliser();
    nfa->st2 = NULL;
    return nfa;
}


state *findfinal(state *nfa, state *final)
{
    state *tmp = nfa;
    
    while (nfa->type != 2)
        nfa = nfa->st1;
    
    nfa->type = 1;
    nfa->etiquette[0] = 'e';
    nfa->st1 = final;
    nfa->st2 = NULL;
    
    return tmp;
}

state *findfinal2(state *nfa, state *final)
{
    state *tmp = nfa;
    
    while (nfa->type != 2)
    {
        if (nfa->st2)
            nfa = nfa->st2;
        else
            nfa = nfa->st1;
    }
    nfa->type = 1;
    nfa->etiquette[0] = 'e';
    nfa->st1 = final;
    nfa->st2 = NULL;
    
    return tmp;
}

state *orAFND(state *nfa1, state *nfa2)
{
    state *init;
    state *final = finaliser();
    init = malloc(sizeof(state));
    
    init->type = 0;
    init->index = stateindex();
    init->etiquette[0] = 'e';
    init->etiquette[1] = 'e';
    mid(&nfa1);
    mid(&nfa2);
    init->st1 = findfinal2(nfa1, final);
    init->st2 = findfinal2(nfa2, final);
    return init;
}


state *concAFND(state *nfa1, state *nfa2)
{
    state *tmp = nfa1;
 
    while (nfa1->type != 2)
        nfa1 = nfa1->st1;
 
    nfa1->type = 1;
 
    if (nfa2->etiquette[0])
    {
        nfa1->etiquette[0] = nfa2->etiquette[0];
        nfa1->st1 = nfa2->st1;
    }
    if (nfa2->etiquette[1])
    {
        nfa1->etiquette[1] = nfa2->etiquette[1];
        nfa1->st2 = nfa2->st2;
    }
    nfa2 = NULL;
    return tmp;
}

state *etoileAFND(state *nfa)
{
    state *init;
    init = malloc(sizeof(state));
    state *final = finaliser();
    init->type = 0;
    init->index = stateindex();
    init->etiquette[0] = 'e';
    init->etiquette[1] = 'e';
    init->st2 = final;
    mid(&nfa);
    init->st1 = nfa;
    while(nfa->type != 2)
        nfa = nfa->st1;
    nfa->type = 1;
    nfa->is_etoile = 1;
    nfa->etiquette[0] = 'e';
    nfa->etiquette[1] = 'e';
    nfa->st1 =init->st1;
    nfa->st2 = final;

    return init;
}


state *nfagen(char *pst)
{
    int i = 0;

    while (pst[i])
    {
        if (pst[i] == 'a' || pst[i] == 'b')
        {
            pushNFA(charAFND(pst[i]));
        }
        if (pst[i] == '|')
        {
            state *nfa2 = popNFA();
            state *nfa1 = popNFA();
            pushNFA(orAFND(nfa1, nfa2));
        }
        if (pst[i] == '.')
        {
            state *nfa2 = popNFA();
            state *nfa1 = popNFA();
            pushNFA(concAFND(nfa1, nfa2));
        }
        if (pst[i] == '*')
        {
            state *nfa = popNFA();
            pushNFA(etoileAFND(nfa));
        }
        i++;
    }
    return popNFA();
}