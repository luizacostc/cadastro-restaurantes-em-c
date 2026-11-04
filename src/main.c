#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct restaurante {

    char nome[50];
    char endereco[100];
    char tipo_comida[50];
    float nota;

    struct restaurante *proximo;
} restaurante;

void lerTexto(char *texto, int tamanho);
restaurante *criarRestaurante(void);
void adicionarFim(restaurante **cabeca, restaurante *novo);
void inserirRestaurante(restaurante **cabeca);
void mostrarRestaurante(restaurante *r);
void listarRestaurantes(restaurante *cabeca);
void listarPorNota(restaurante *cabeca);
void listarPorTipo(restaurante *cabeca);
void gravarRegistro(FILE *fp, restaurante *r);
void gravarArquivo(restaurante *cabeca);
int lerRegistro(FILE *fp, restaurante *r);
void lerArquivo(restaurante **cabeca);
void liberarLista(restaurante *cabeca);

int main(void) {

    restaurante *cabeca = NULL;
    int opcao;

    do {
        printf("\n\tMENU\n");
        printf("1- Inserir restaurante\n");
        printf("2- Ler arquivo\n");
        printf("3- Gravar arquivo\n");
        printf("4- Listar todos\n");
        printf("5- Listar por nota\n");
        printf("6- Listar por tipo de comida\n");
        printf("7- Sair\n\n");
        printf("Opcao: ");
        
        if (scanf("%d", &opcao) != 1) {
            break;
        }

        while (getchar() != '\n');

        switch(opcao) {

            case 1:
                inserirRestaurante(&cabeca);
                break;

            case 2:
                lerArquivo(&cabeca);
                break;

            case 3:
                gravarArquivo(cabeca);
                break;

            case 4:
                listarRestaurantes(cabeca);
                break;
            
            case 5:
                listarPorNota(cabeca);
                break;
            
            case 6:
                listarPorTipo(cabeca);
                break;
            
            case 7:
                printf("Encerrando...\n");
                break;
            
            default:
                printf("Opcao invalida.\n");
                
        }

    } while (opcao != 7);

     liberarLista(cabeca);

    return 0;
}

void lerTexto(char *texto, int tamanho) {

    if (fgets(texto, tamanho, stdin) != NULL) {
        
        texto[strcspn(texto, "\n")] = '\0';
    }
    else {

        texto[0] = '\0';

    }
}

restaurante *criarRestaurante(void) {

    restaurante *novo;
    char entrada[20];

    novo = malloc(sizeof(*novo));

    if (novo == NULL) {

        printf("Erro de alocacao de memoria.\n");
        return NULL;

    }

    printf("Nome: ");
    lerTexto(novo->nome, 50);

    printf("Endereco: ");
    lerTexto(novo->endereco, 100);

    printf("Tipo de comida: ");
    lerTexto(novo->tipo_comida, 50);

    printf("Nota (0 a 5): ");
    lerTexto(entrada, 20);

    while (sscanf(entrada, "%f", &novo->nota) != 1 ||
        !(novo->nota >= 0 && novo->nota <= 5)) {

        printf("Nota invalida. Digite novamente: ");
        lerTexto(entrada, 20);
    }

    novo->proximo = NULL;

    return novo;
}

void adicionarFim(restaurante **cabeca, restaurante *novo) {

    restaurante *atual;

    novo->proximo = NULL;

    if (*cabeca == NULL) {

        *cabeca = novo;

    }
    else {

        atual = *cabeca;

        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }

        atual->proximo = novo;
    }

}

void inserirRestaurante(restaurante **cabeca) {

    restaurante *novo = criarRestaurante();

    if (novo == NULL) {

        return;
    }

    adicionarFim(cabeca, novo);

    printf("Restaurante inserido!\n");

}

void mostrarRestaurante(restaurante *r) {

    printf("\nNome: %s\n", r->nome);
    printf("Endereco: %s\n", r->endereco);
    printf("Tipo: %s\n", r->tipo_comida);
    printf("Nota: %.2f\n\n", r->nota);

}

void listarRestaurantes(restaurante *cabeca) {

    restaurante *atual = cabeca;

    while (atual != NULL) {

        mostrarRestaurante(atual);
        atual = atual->proximo;

    }

}

void listarPorNota(restaurante *cabeca) {

    restaurante *atual = cabeca;
    float nota;
    char entrada[20];

    printf("Nota de referencia: ");
    lerTexto(entrada, 20);

    if (sscanf(entrada, "%f", &nota) != 1 ||
        nota < 0 || nota > 5) {

        printf("Nota invalida.\n");
        return;
    }

    while (atual != NULL) {

        if (atual->nota > nota) {
            mostrarRestaurante(atual);
        }

        atual = atual->proximo;
    }
}

void listarPorTipo(restaurante *cabeca) {

    restaurante *atual = cabeca;
    char tipo[50];

    printf("Tipo de comida: ");
    lerTexto(tipo, 50);

    while (atual != NULL) {

        if (strcmp(atual->tipo_comida, tipo) == 0) {
            mostrarRestaurante(atual);
        }

        atual = atual->proximo;
    }
}

void gravarRegistro(FILE *fp, restaurante *r) {

    fprintf(fp, "%s\n", r->nome);
    fprintf(fp, "%s\n", r->endereco);
    fprintf(fp, "%s\n", r->tipo_comida);
    fprintf(fp, "%.2f\n", r->nota);

}

void gravarArquivo(restaurante *cabeca) {

    FILE *fp;
    restaurante *atual = cabeca;

    fp = fopen("restaurantes.txt", "w");

    if (fp == NULL) {
        
        printf("Erro ao abrir o arquivo.\n");
        return;

    }

    while (atual != NULL) {

        gravarRegistro(fp, atual);
        atual = atual->proximo;

    }

    fclose(fp);

    system("notepad restaurantes.txt");

}

int lerRegistro(FILE *fp, restaurante *r) {

    char nota[10];
    
    if (fgets(r->nome, sizeof(r->nome), fp) == NULL ||
        fgets(r->endereco, sizeof(r->endereco), fp) == NULL ||
        fgets(r->tipo_comida, sizeof(r->tipo_comida), fp) == NULL ||
        fgets(nota, sizeof(nota), fp) == NULL ||
        sscanf(nota, "%f", &r->nota) != 1) {

            return 0;

    }

    r->nome[strcspn(r->nome, "\n")] = '\0';
    r->endereco[strcspn(r->endereco, "\n")] = '\0';
    r->tipo_comida[strcspn(r->tipo_comida, "\n")] = '\0';

    return 1;    
}

void lerArquivo(restaurante **cabeca) {

    FILE *fp;
    restaurante *novo;
    restaurante *nova_lista = NULL;
    int erro = 0;

    fp = fopen("restaurantes.txt", "r");

    if (fp == NULL) {

        printf("Erro ao abrir o arquivo.\n");
        return;

    }

    while (1) {

        novo = malloc(sizeof(*novo));

        if (novo == NULL) {

            printf("Erro de alocacao.\n");
            erro = 1;
            break;

        }

        if (lerRegistro(fp, novo) == 0) {

            free(novo);
            break;

        }

        adicionarFim(&nova_lista, novo);
    }

    if (ferror(fp)) {

        erro = 1;

    }
    fclose(fp);

    if (erro) {

        liberarLista(nova_lista);
        printf("Erro ao carregar arquivo.\n");
        return;

    }

    liberarLista(*cabeca);
    *cabeca = nova_lista;

    printf("Arquivo carregado!\n");

}

void liberarLista(restaurante *cabeca) {

    restaurante *atual = cabeca;
    restaurante *proximo;

    while (atual != NULL) {

        proximo = atual->proximo;
        free(atual);
        atual = proximo;

    }
}
