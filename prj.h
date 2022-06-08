#ifndef PRJ_H
#define PRJ_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void push(char x);
char pop();
int priority(char x);
int parenth(char *r);
char *postfix(char *r);
//nfa 
typedef struct state
{
    int type; // 0 init , 1 mid, 2 final
    int is_etoile;
    int index;
    char etiquette[2];
    struct state *st1;
    struct state *st2;
} state;


void pushNFA(state *nfa);
state *popNFA();
int stateindex();
void mid(state **nfa);
state *finaliser(void);
state *charAFND(char c);
state *findfinal(state *nfa, state *final);
state *findfinal2(state *nfa, state *final);
state *orAFND(state *nfa1, state *nfa2);
state *concAFND(state *nfa1, state *nfa2);
state *etoileAFND(state *nfa);
state *nfagen(char *pst);

//dfa 
typedef struct dfa
{
    int type; // 0 mid, 1 init, 2 final, 3 both
    int is_etoile;
    int traiter;
    int index;
    char etiquette[2];
    struct dfa *a;
    struct dfa *b;
} dfa;

void pushDFA(state **nfa);
state **popDFA();
int dfaindex();
int duplicateCheck(state **stTable, state *nfa);
void e_cloture(state **stateTable, state *nfa);
void sort(int *tab, int n);
int *indtablegen(state **states);
int size(int *t);
int verification(int *t, int n);
void fillTAB(int *t, int n,int index);

int statetype(state **nfa);
state **grpA(state **t);
state **grpB(state **t);
dfa *dmake(int i, char c);
dfa *dfagen(state **stack);
dfa *finalgrp(state *nfa);
void showcase(dfa *df);
void show(state **e);



void nodub();
void fill(dfa *d);
int dfaCompare(dfa *d);
void finalDFA();
void whole(dfa *d);


char *standarize(char *regex);

#endif
