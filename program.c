#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void process_input(char *input) {
    char buffer[16];  // Buffer pequeno (16 bytes)

    strcpy(buffer, input);  // Vulnerabilidade: buffer overflow!

    printf("Você digitou: %s\n", buffer);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: %s <arquivo_de_entrada>\n", argv[0]);
        return 1;
    }

    //Lendo o conteúdo do arquivo ao invés de passar o nome do arquivo
    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    char input[1024];  // Buffer maior apenas para leitura (mas depois será copiado para um menor!)
    if (!fgets(input, sizeof(input), file)) {
        perror("Erro ao ler o arquivo");
        fclose(file);
        return 1;
    }
    fclose(file);

    // Chamar a função que contém a vulnerabilidade
    process_input(input);

    return 0;
}