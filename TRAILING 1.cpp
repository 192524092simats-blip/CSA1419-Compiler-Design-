#include <stdio.h>

/* Table: [Non-terminal, Terminal, Flag] */
char arr[18][3] = {
    {'E','+','F'}, {'E','*','F'}, {'E','(','F'}, {'E',')','F'}, {'E','i','F'}, {'E','$','F'},
    {'F','+','F'}, {'F','*','F'}, {'F','(','F'}, {'F',')','F'}, {'F','i','F'}, {'F','$','F'},
    {'T','+','F'}, {'T','*','F'}, {'T','(','F'}, {'T',')','F'}, {'T','i','F'}, {'T','$','F'}
};

/* Productions */
char prod[] = "EETTFF";

/* RHS rules */
char res[6][3] = {
    {'E','+','T'},   // E ? E+T
    {'T','\0','\0'}, // E ? T
    {'T','*','F'},   // T ? T*F
    {'F','\0','\0'}, // T ? F
    {'(','E',')'},   // F ? (E)
    {'i','\0','\0'}  // F ? i
};

/* Stack */
char stack[100][2];
int top = -1;

/* Install function */
void install(char pro, char re)
{
    int i;

    for (i = 0; i < 18; i++)
    {
        if (arr[i][0] == pro && arr[i][1] == re)
        {
            if (arr[i][2] == 'T') return;  // avoid duplicates

            arr[i][2] = 'T';

            if (top < 99)   // prevent overflow
            {
                top++;
                stack[top][0] = pro;
                stack[top][1] = re;
            }
            return;
        }
    }
}

/* Check terminal */
int isTerminal(char c)
{
    return (c=='+' || c=='*' || c=='(' || c==')' || c=='i' || c=='$');
}

/* Main */
int main()
{
    int i, j;
    char pro, re, prev = '\0';

    /* Step 1: Initial marking (from right side) */
    for (i = 0; i < 6; i++)
    {
        for (j = 2; j >= 0; j--)
        {
            if (isTerminal(res[i][j]))
            {
                install(prod[i], res[i][j]);
                break;
            }
            else if (res[i][j] >= 'A' && res[i][j] <= 'Z')
            {
                if (j-1 >= 0 && isTerminal(res[i][j-1]))
                {
                    install(prod[i], res[i][j-1]);
                    break;
                }
            }
        }
    }

    /* Step 2: Propagation */
    while (top >= 0)
    {
        pro = stack[top][0];
        re  = stack[top][1];
        top--;

        for (i = 0; i < 6; i++)
        {
            if (res[i][0] == pro && prod[i] != pro)
            {
                install(prod[i], re);
            }
        }
    }

    /* Step 3: Print table */
    printf("\n");
    for (i = 0; i < 18; i++)
    {
        printf("\t%c\t%c\t%c\n", arr[i][0], arr[i][1], arr[i][2]);
    }

    /* Step 4: Print TRAILING sets */
    printf("\n");

    for (i = 0; i < 18; i++)
    {
        if (arr[i][0] != prev)
        {
            prev = arr[i][0];
            printf("\n%c -> ", prev);
        }

        if (arr[i][2] == 'T' && arr[i][1] != '(' && arr[i][1] != '$')
        {
            printf("%c ", arr[i][1]);
        }
    }

    printf("\n");
    return 0;
}
