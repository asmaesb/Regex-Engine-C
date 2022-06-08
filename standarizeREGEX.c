#include "prj.h"

char *standarize(char *regex)
{
    char *res;
    int i = 0;
    int j = 0;
    int count = 0;
    int n = strlen(regex);
    while (i < n - 1)
    {
        if ((regex[i] == 'a' || regex[i] == 'b' || regex[i] == 'e' || regex[i] == ')') && (regex[i + 1] == 'a' || regex[i + 1] == 'b' || regex[i] == 'e' || regex[i + 1] == '('))
            count++;
        i++;
    }
    res = malloc(n + count + 1);
    i = 0;
    while (i < n - 1)
    {
        if ((regex[i] == 'a' || regex[i] == 'b' || regex[i] == 'e' || regex[i] == ')') && (regex[i + 1] == 'a' || regex[i + 1] == 'b' || regex[i] == 'e' || regex[i + 1] == '('))
        {
            res[j++] = regex[i++];
            res[j++] = '.';
        }
        else
            res[j++] = regex[i++];
    }
    res[j++] = regex[i];
    res[j] = '\0';
    free(regex);
    return (res);
}
