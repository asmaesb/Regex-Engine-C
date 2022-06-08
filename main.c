#include "prj.h"

int main()
{
    char *s;
    s = malloc(10);
    printf("veuillez saisir le regex : ");
    scanf("%s", s);
    char *r;
    r = postfix(standarize(s));
    printf("post %s\n", r);
    dfa *d;
    d = finalgrp(nfagen(r));
    whole(d);
    showcase(d);
    printf("---DFA created---\n");
    char c;
    do
    {
        // fflush(stdin);
        dfa *tmp = d;
        int err = 0;
        char *w;
        w = malloc(10);
        printf("saisir le mot a verifier : ");
        scanf("%s", w);
        //printf("---> |%s|\n", w);
        int i =0;
        while(w[i])
        {
            if (w[i] == 'a' && d->a != NULL)
                d = d->a;
            else if ( w[i] == 'b' && d->b != NULL)
                d = d->b;
            else
            {
                err = 1;
                break ;
            }
            i++;
        }
        //printf("curr index %d\n",d->index);
        if (w[i] == '\0' && err == 0 && (d->type == 2 || d->type == 3))
            printf("\nMOT ACCEPTE\n");
        else
            printf("MOT NON ACCEPTE\n");
        d = tmp;
        free (w);
        printf("voulez vous essayer un autre mot ? [y/n] ");
        //fflush(stdin);
        scanf("%c",&c);
        scanf("%c",&c);
    } while (c == 'y');
    
}