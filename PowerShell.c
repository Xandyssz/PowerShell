#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/stat.h>

// --- ESTRUTURAS DO SISTEMA DE ARQUIVOS ---
typedef struct {
    int block_size;             // Tamanho de cada bloco de dados.
    int partition_size;         // Tamanho total da partição.
    int num_blocks;             // Total de blocos - [partition_size / block_size].
    int num_inodes;             // Número máximo de arquivos/diretórios que o sistema suporta.
    int max_filename;           // Comprimento máximo para nomes de arquivos.
} FileSystemConfig;

typedef struct {
    char type;                  // Tipo da entrada ('f': arquivo, 'd': diretório).
    int size;                   // Tamanho do arquivo.
    int direct_blocks[10];      // Limita o tamanho máximo do arquivo em - [10 * block_size].
} Inode;

typedef struct {
    char name[15];              // Reservado 15 para ter espaço para o [\0]
    int inode_number;           // É o índice do inode correspondente na tabela de inodes (inodes.dat).
} DirectoryEntry;

// Prepara a estrutura de pastas inicial do sistema de arquivos.
void create_base_structure() {
    mkdir("fs");      // - Cria o diretório raiz 'fs'.
    mkdir("fs/blocks"); // - Cria o diretório para os blocos de dados.

    FILE *mickey_file = fopen("fs/.mickey.txt", "w"); // -- Cria o arquivo de verificação .mickey.txt com a assinatura "Disney".
    fprintf(mickey_file, "Disney");
    fclose(mickey_file);
}

void fs_write_superblock(FileSystemConfig* config) {
    // Define os valores na struct antes de salvar
    config->block_size = 128;
    config->partition_size = 10240;
    config->num_inodes = 32;
    config->max_filename = 14;

    FILE *sb_file = fopen("fs/superblock.dat", "w");

    // Escreve os dados da configuração no arquivo.
    fprintf(sb_file, "filesystem=kleberfs\n");
    fprintf(sb_file, "blocksize=%d\n", config->block_size);
    fprintf(sb_file, "partitionsize=%d\n", config->partition_size);

    fclose(sb_file);
}

bool initialize_config (FileSystemConfig* config) {
    char line[100];
    bool flag_BlockSizeFound = false;
    bool flagPartitionSizeFound = false;
    FILE *file_superblock = fopen("fs/superblock.dat", "r");

    if (file_superblock == NULL) {
        perror("FATAL: Nao foi possivel abrir o superblock.dat");
        exit(1);
    }

    while(fgets(line, sizeof(line), file_superblock)) {
        if (sscanf(line, "blocksize=%d", &config->block_size) == 1) {
            flag_BlockSizeFound = true;
        }
        else if (sscanf(line, "partitionsize=%d", &config->partition_size) == 1) {
            flagPartitionSizeFound = true;
        }
    }
    fclose(file_superblock);

    if (!flag_BlockSizeFound || !flagPartitionSizeFound) {
        printf("FATAL: O arquivo 'superblock.dat' esta mal formatado ou incompleto. 'blocksize' ou 'partitionsize' nao encontrado.\n");
        exit(1);
    }

    config->num_blocks = config->partition_size / config->block_size;
    config->num_inodes = 32;
    config->max_filename = 14;

    printf("Configuracao carregada: block_size=%d, num_blocks=%d\n",
        config->block_size, config->num_blocks);
    return true;
}

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

bool command_execute(const char *linha) {
    char command_name[20], command_parameters[256];
    int command_code = 0;
    int items_parsed = sscanf(linha, "%15s %255s", command_name, command_parameters);

    if (items_parsed < 1) {
        return false;
    }

    for (int i = 0; command_name[i]; i++) {
        command_name[i] = toupper(command_name[i]);
    }

    if (strcmp(command_name, "MKDIR") == 0) {
        command_code = 1;
    } else if (strcmp(command_name, "CD") == 0) {
        command_code = 2;
    } else if (strcmp(command_name, "PWD") == 0) {
        command_code = 3;
    } else if (strcmp(command_name, "TOUCH") == 0) {
        command_code = 4;
    } else if (strcmp(command_name, "CAT") == 0) {
        command_code = 5;
    } else if (strcmp(command_name, "DIR") == 0) { // DIR > LS
        command_code = 6;
    } else if (strcmp(command_name, "RM") == 0) {
        command_code = 7;
    } else if (strcmp(command_name, "STAT") == 0) {
        command_code = 8;
    } else {
        printf("unrecognized command_name: %s\n", command_name);
        return false;
    }

    switch (command_code) {
        case 1: // MKDIR
            break;

        case 2: // CD
            break;

        case 3: // PWD
            pwd_execute();
            break;

        case 4: // TOUCH
            break;

        case 5: // CAT
            if (items_parsed < 2) {
            printf("Error: missing file name.\n Correct use of the command: CAT <file_name>\n");                    return false;
            } else {
                cat_execute(command_parameters);
            }
            break;

        case 6: // DIR
            break;

        case 7: // RM
            break;

        case 8: // STAT
            break;
    }
    return true;
}

