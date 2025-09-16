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

