#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Livro {
    char nome[50];
    char autor[50];
};

struct No {
    struct Livro livro;
    struct No* proximo;
};

struct Fila {
    struct No* inicio;
    struct No* fim;
};

struct Pilha {
    struct No* topo;
};

void inicializarFila(struct Fila* fila) {
    fila->inicio = fila->fim = NULL;
}

void enfileirar(struct Fila* fila, struct Livro livro) {
    struct No* novoNo = (struct No*)malloc(sizeof(struct No));
    novoNo->livro = livro;
    novoNo->proximo = NULL;
    if (fila->fim == NULL) {
        fila->inicio = fila->fim = novoNo;
        return;
    }
    fila->fim->proximo = novoNo;
    fila->fim = novoNo;
}


void desenfileirar(struct Fila* fila) {
    if (fila->inicio == NULL) {
        printf("A fila de livros está vazia.\n");
        return;
    }
    struct No* temp = fila->inicio;
    fila->inicio = fila->inicio->proximo;
    free(temp);
}


void inicializarPilha(struct Pilha* pilha) {
    pilha->topo = NULL;
}


void empilhar(struct Pilha* pilha, struct Livro livro) {
    struct No* novoNo = (struct No*)malloc(sizeof(struct No));
    novoNo->livro = livro;
    novoNo->proximo = pilha->topo;
    pilha->topo = novoNo;
}


void desempilhar(struct Pilha* pilha) {
    if (pilha->topo == NULL) {
        printf("A pilha de livros está vazia.\n");
        return;
    }
    struct No* temp = pilha->topo;
    pilha->topo = pilha->topo->proximo;
    free(temp);
}


void mostrarFila(struct Fila fila) {
    struct No* atual = fila.inicio;
    printf("Fila de Livros:\n");
    while (atual != NULL) {
        printf("Livro: %s; Autor: %s\n", atual->livro.nome, atual->livro.autor);
        atual = atual->proximo;
    }
}


void mostrarPilha(struct Pilha pilha) {
    struct No* atual = pilha.topo;
    printf("Pilha de Livros:\n");
    while (atual != NULL) {
        printf("Livro: %s; Autor: %s\n", atual->livro.nome, atual->livro.autor);
        atual = atual->proximo;
    }
}

int main() {
  
    FILE* filaArquivo = fopen("fila_de_livros.txt", "r");
    FILE* pilhaArquivo = fopen("pilha_de_livros.txt", "r");

 
    if (filaArquivo == NULL || pilhaArquivo == NULL) {
        printf("Erro ao abrir arquivos de entrada.\n");
        return 1;
    }

  
    struct Fila fila;
    struct Pilha pilha;
    inicializarFila(&fila);
    inicializarPilha(&pilha);

  
    char linha[100];
    while (fgets(linha, sizeof(linha), filaArquivo)) {
        struct Livro livro;
        sscanf(linha, "%[^;]; %s", livro.nome, livro.autor);
        enfileirar(&fila, livro);
    }

    while (fgets(linha, sizeof(linha), pilhaArquivo)) {
        struct Livro livro;
        scanf(linha, "%[^;]; %s", livro.nome, livro.autor);
        empilhar(&pilha, livro);
    }

    int opcao;
    do {
        printf("\nMenu:\n");
        printf("1. Exibir fila de livros\n");
        printf("2. Inserir livro na fila\n");
        printf("3. Inserir livro na pilha\n");
        printf("4. Remover livro da fila\n");
        printf("5. Remover livro da pilha\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                mostrarFila(fila);
                break;
            case 2:
                {
                    struct Livro novoLivro;
                    printf("Digite o nome do livro: ");
                    scanf(" %[^\n]", novoLivro.nome);
                    printf("Digite o autor do livro: ");
                    scanf(" %[^\n]", novoLivro.autor);
                    enfileirar(&fila, novoLivro);

                  
                    FILE* filaArquivo = fopen("fila_de_livros.txt", "a");
                    fprintf(filaArquivo, "%s; %s\n", novoLivro.nome, novoLivro.autor);
                    fclose(filaArquivo);
                }
                break;
            case 3:
                {
                    struct Livro novoLivro;
                    printf("Digite o nome do livro: ");
                    scanf(" %[^\n]", novoLivro.nome);
                    printf("Digite o autor do livro: ");
                    scanf(" %[^\n]", novoLivro.autor);
                    empilhar(&pilha, novoLivro);

                  
                    FILE* pilhaArquivo = fopen("pilha_de_livros.txt", "a");
                    fprintf(pilhaArquivo, "%s; %s\n", novoLivro.nome, novoLivro.autor);
                    fclose(pilhaArquivo);
                }
                break;
            case 4:
                desenfileirar(&fila);

              
                FILE* filaArquivo = fopen("fila_de_livros.txt", "w");
                struct No* atual = fila.inicio;
                while (atual != NULL) {
                    fprintf(filaArquivo, "%s; %s\n", atual->livro.nome, atual->livro.autor);
                    atual = atual->proximo;
                }
                fclose(filaArquivo);
                break;
            case 5:
                desempilhar(&pilha);
              
               
                FILE* pilhaArquivo = fopen("pilha_de_livros.txt", "w");
                struct No* iterador_pilha = pilha.topo;

                while (atual != NULL) {
                    fprintf(pilhaArquivo, "%s; %s\n", atual->livro.nome, atual->livro.autor);
                    atual = atual->proximo;
                }
                fclose(pilhaArquivo);
                break;
        }
    } while (opcao != 0);

  
    fclose(filaArquivo);
    fclose(pilhaArquivo);

    return 0;
}
