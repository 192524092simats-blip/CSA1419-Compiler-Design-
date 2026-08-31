#include<stdio.h>
#include<string.h>

#define MAX 20

int main() {
    int n;
    char production[MAX][MAX];

    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Enter productions (e.g., A->Aa|b):\n");
    for(int i = 0; i < n; i++) {
        scanf("%s", production[i]);
    }

    for(int i = 0; i < n; i++) {
        char lhs = production[i][0];   // Non-terminal
        char rhs[MAX];

        strcpy(rhs, strchr(production[i], '>') + 1);

        char alpha[MAX] = "";
        char beta[MAX] = "";

        char *token = strtok(rhs, "|");

        while(token != NULL) {
            if(token[0] == lhs) {
                strcat(alpha, token + 1);  // remove A from Aa
                strcat(alpha, "|");
            } else {
                strcat(beta, token);
                strcat(beta, "|");
            }
            token = strtok(NULL, "|");
        }

        // Remove last '|'
        if(strlen(alpha) > 0) alpha[strlen(alpha)-1] = '\0';
        if(strlen(beta) > 0) beta[strlen(beta)-1] = '\0';

        printf("\nOriginal: %s\n", production[i]);

        if(strlen(alpha) == 0) {
            printf("No left recursion.\n");
        } else {
            printf("After removing left recursion:\n");

            // A -> ßA'
            printf("%c -> ", lhs);
            char *b = strtok(beta, "|");
            while(b != NULL) {
                printf("%s%c' ", b, lhs);
                b = strtok(NULL, "|");
                if(b) printf("| ");
            }

            // A' -> aA' | e
            printf("\n%c' -> ", lhs);
            char *a = strtok(alpha, "|");
            while(a != NULL) {
                printf("%s%c' ", a, lhs);
                a = strtok(NULL, "|");
                if(a) printf("| ");
            }
            printf("| e\n");
        }
    }

    return 0;
}
