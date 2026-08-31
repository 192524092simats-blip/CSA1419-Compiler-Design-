#include<stdio.h>
#include<string.h>

char stack[20], input[20];
int top = -1, i = 0;

void reduce()
{
    int j;

    for(j = 0; j < top; j++)
    {
        if(stack[j] == 'i' && stack[j+1] == 'd')
        {
            stack[j] = 'E';
            stack[j+1] = '\0';
            top--;
            printf("Reduce: E->id\n");
        }
    }

    for(j = 0; j < top-1; j++)
    {
        if(stack[j]=='E' &&
           stack[j+1]=='+' &&
           stack[j+2]=='E')
        {
            stack[j]='E';
            top=top-2;
            stack[top+1]='\0';

            printf("Reduce: E->E+E\n");
        }
    }
}

int main()
{
    printf("Enter Expression: ");
    scanf("%s", input);

    while(input[i] != '\0')
    {
        stack[++top] = input[i];
        stack[top+1] = '\0';

        printf("Shift: %s\n", stack);

        reduce();
        i++;
    }

    if(strcmp(stack,"E")==0)
        printf("String Accepted");
    else
        printf("String Rejected");

    return 0;
}
