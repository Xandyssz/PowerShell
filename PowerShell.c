#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <direct.h> // LIBRARY FOR PWD.

// FUNCTION PWD
// _getcwd: retorna o caminho absoluto do diretório atual
bool pwd_execute() {
    char directory[1024];
    if (_getcwd(directory, sizeof(directory)) != NULL) {
        printf("%s\n", directory);
        return true;
    } else {
        printf("ERROR: GETTING CURRENT DIRECTORY\n");
        return false;
    }
}

// FUNCTION CAT
bool cat_execute(const char *arq) {
    int currentChar;
    FILE *file = fopen(arq, "r");
        if (file == NULL) {
            printf("ERROR: AT OPENING FILE\n");
            return false;
        }

    while ((currentChar = fgetc(file)) != EOF) {
        putchar(currentChar);
    }
    fclose(file);
    printf("\n");
    return true;
}

