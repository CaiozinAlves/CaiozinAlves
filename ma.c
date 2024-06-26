#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 100


typedef struct {
    char nome[MAX_LEN];
    char telefone[MAX_LEN];
    char curso[MAX_LEN];
    float nota1;
    float nota2;
} Aluno;


float calcularMedia(float nota1, float nota2) {
    return (nota1 + nota2) / 2.0;
}


const char* determinarSituacao(float media) {
    if (media >= 7.0) {
        return "APROVADO";
    } else {
        return "REPROVADO";
    }
}

int main() {
    FILE *entrada = fopen("DadosEntrada.csv", "r");
    FILE *saida = fopen("SituacaoFinal.csv", "w");

    if (entrada == NULL || saida == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    
    char linha[MAX_LEN];
    while (fgets(linha, MAX_LEN, entrada) != NULL) {
        // Separar os dados usando a vírgula como delimitador
        char *token = strtok(linha, ",");
        Aluno aluno;
        strcpy(aluno.nome, token);
        token = strtok(NULL, ",");
        strcpy(aluno.telefone, token);
        token = strtok(NULL, ",");
        strcpy(aluno.curso, token);
        token = strtok(NULL, ",");
        aluno.nota1 = atof(token);
        token = strtok(NULL, ",");
        aluno.nota2 = atof(token);

        
        float media = calcularMedia(aluno.nota1, aluno.nota2);

       
        const char* situacao = determinarSituacao(media);

        
        fprintf(saida, "%s, %.2f, %s\n", aluno.nome, media, situacao);
    }

    fclose(entrada);
    fclose(saida);

    printf("Processamento concluído. Verifique o arquivo SituacaoFinal.csv\n");

    return 0;
}
