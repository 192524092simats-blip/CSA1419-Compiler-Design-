#include <stdio.h>
#include <string.h>

#define MAX 10
#define SIZE 50

int main() {
    int n;
    char prod[MAX][SIZE];

    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Enter productions (e.g., L->L,S|S):\n");
    for (int i = 0; i < n; i++) {
        scanf("%s", prod[i]);
    }

    for (int i = 0; i < n; i++) {
        char A = prod[i][0];  // Non-terminal
        char alpha[SIZE] = "", beta[SIZE] = "";
        int isLeftRec = 0;

        // Split RHS
        char *rhs = strstr(prod[i], "->") + 2;
        char *token = strtok(rhs, "|");

        while (token != NULL) {
            if (token[0] == A) {
                isLeftRec = 1;
                strcat(alpha, token + 1);
                strcat(alpha, "|");
            } else {
                strcat(beta, token);
                strcat(beta, "|");
            }
            token = strtok(NULL, "|");
        }

        printf("\nGRAMMAR: %c->%s\n", A, rhs);

        if (isLeftRec) {
            printf("Left recursion detected.\n");

            // Remove last '|'
            alpha[strlen(alpha) - 1] = '\0';
            beta[strlen(beta) - 1] = '\0';

            printf("After removing left recursion:\n");

            printf("%c -> %s%c'\n", A, beta, A);
            printf("%c' -> %s%c' | e\n", A, alpha, A);

        } else {
            printf("No left recursion.\n");
        }
    }

    return 0;
}
