#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 10

char productions[MAX][10] = {
    "E=E+T",
    "E=T",
    "T=T*F",
    "T=F",
    "F=(E)",
    "F=i"
};

char leading[MAX][MAX];
int leadCount[MAX] = {0};

int isTerminal(char c) {
    return !(c >= 'A' && c <= 'Z');
}

void addToLeading(int index, char symbol) {
    for (int i = 0; i < leadCount[index]; i++) {
        if (leading[index][i] == symbol)
            return;
    }
    leading[index][leadCount[index]++] = symbol;
}

void computeLeading(char nonTerminal) {
    int i, j;
    int index = nonTerminal - 'A';

    for (i = 0; i < 6; i++) {
        if (productions[i][0] == nonTerminal) {
            // RHS starts after '='
            if (isTerminal(productions[i][2])) {
                addToLeading(index, productions[i][2]);
            }
            else {
                // If first symbol is non-terminal
                computeLeading(productions[i][2]);

                int subIndex = productions[i][2] - 'A';
                for (j = 0; j < leadCount[subIndex]; j++) {
                    addToLeading(index, leading[subIndex][j]);
                }
            }
        }
    }
}

int main() {
    int i, j;

    computeLeading('E');
    computeLeading('T');
    computeLeading('F');

    printf("\nLEADING sets:\n");

    for (i = 0; i < 3; i++) {
        printf("\n%c -> ", 'E' + i);
        for (j = 0; j < leadCount[i]; j++) {
            printf("%c ", leading[i][j]);
        }
    }

    return 0;
}
