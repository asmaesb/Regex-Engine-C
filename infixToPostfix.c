#include "prj.h"

char stack[100];
int top = -1;

void push(char x)
{
    stack[++top] = x;
}

char pop()
{
    if(top == -1)
        return -1;
    else
        return stack[top--];
}

int priority(char x)
{
    if(x == '(')
        return 0;
    if(x == '|')
        return 1;
    if(x == '.')
        return 2;
    if(x == '*')
        return 3;
    return 0;
}

int parenth(char *r)
{
    int i=0;
    int count = 0;
    while(r[i])
    {
        if(r[i] == '(' || r[i] == ')')
            count++;
        i++;
    }
    return count;
}

char *postfix(char *r)
{
    char *pst;
    char x;
    int j = 0;
    int i = 0;
    
    pst = malloc(strlen(r) - parenth(r) + 1);
    while(r[i] != '\0')
    {
        if(r[i] == 'a' || r[i] == 'b' || r[i] == 'e')
            pst[j++] = r[i];
        else if(r[i] == '(')
            push(r[i]);
        else if(r[i] == ')')
        {
            while((x = pop()) != '(')
                pst[j++] = x;
        }
        else
        {
            while(priority(stack[top]) >= priority(r[i]))
                pst[j++] = pop();
            push(r[i]);
        }
        i++;
    }
    
    while(top != -1)
    {
        pst[j++] = pop();
    }
    pst[j] = '\0';
    return pst;
}

// int main()
// {
//     char *r="ab|b(a|b*)";

//     r = standarize(r);
//     printf("%s",postfix(r));
// }