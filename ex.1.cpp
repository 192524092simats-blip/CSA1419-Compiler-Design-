#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main() {
    FILE *fp;
    char ch;

    fp = fopen("input.txt", "r");

    if (fp == NULL) {
        printf("Cannot open file.\n");
        return 1;
    }

    while ((ch = fgetc(fp)) != EOF) {

        // Ignore spaces, tabs, and new lines
        if (ch == ' ' || ch == '\t' || ch == '\n')
            continue;

        // Ignore single-line comments
        if (ch == '/') {
            char next = fgetc(fp);

            if (next == '/') {
                while ((ch = fgetc(fp)) != '\n' && ch != EOF);
                continue;
            }

            // Ignore multi-line comments
            else if (next == '*') {
                while ((ch = fgetc(fp)) != EOF) {
                    if (ch == '*') {
                        if ((ch = fgetc(fp)) == '/')
                            break;
                    }
                }
                continue;
            }

            else {
                printf("Operator : /\n");
                fseek(fp, -1, SEEK_CUR);
                continue;
            }
        }

        // Identifier
        if (isalpha(ch) || ch == '_') {
            char str[50];
            int i = 0;

            str[i++] = ch;

            while ((ch = fgetc(fp)) != EOF &&
                  (isalnum(ch) || ch == '_')) {
                str[i++] = ch;
            }

            str[i] = '\0';

            printf("Identifier : %s\n", str);

            if (ch != EOF)
                fseek(fp, -1, SEEK_CUR);
        }

        // Constant
        else if (isdigit(ch)) {
            char num[50];
            int i = 0;

            num[i++] = ch;

            while ((ch = fgetc(fp)) != EOF &&
                  isdigit(ch)) {
                num[i++] = ch;
            }

            num[i] = '\0';

            printf("Constant : %s\n", num);

            if (ch != EOF)
                fseek(fp, -1, SEEK_CUR);
        }

        // Operators
        else if (strchr("+-*=<>!%", ch)) {
            printf("Operator : %c\n", ch);
        }
    }

    fclose(fp);

    return 0;
}
