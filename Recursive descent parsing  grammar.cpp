#include <stdio.h>
#include <string.h>

char input[100];
int i = 0;

// Function declarations
int E();
int EP();
int T();
int TP();
int F();

int main(){

 printf("Recursive Descent Parsing for the grammar:\n");
    printf("E  -> TE'\n");
    printf("E' -> +TE' | e\n");
    printf("T  -> FT'\n");
    printf("T' -> *FT' | e\n");
    printf("F  -> (E) | id\n");

    printf("\nEnter the string: ");
    scanf("%s", input);

    if (E() && input[i] == '\0') {
        printf("\nString is ACCEPTED\n");
    } else {
        printf("\nString is NOT ACCEPTED\n");
    }

    return 0;
}
