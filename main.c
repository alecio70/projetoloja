#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct cadastro
{
    char nome[30];
    int anoNascimento;
    double gastosMes;
    struct cadastro *proximo;
} CADASTRO;

void incluirCliente(CADASTRO **cabeca);
void listar (CADASTRO *cabeca);
CADASTRO* removerCliente(CADASTRO *lista);
void melhorComprador(CADASTRO *noAtual);

int main()
{
    setlocale(LC_ALL, "Portuguese");
    int op;
    char nome[30];
    CADASTRO *cabeca = NULL;
    CADASTRO *noAtual;

    do {
        printf("============ MENU ============\n");
        printf("Digite opção abaixo\n");
        printf("1 - Incluir um novo cliente\n2 - Excluir cliente\n3 - Atualizar os montantes do mês corrente\n4 - Zerar todos os montantes\n5 - Listar o cliente melhor comprador\n6 - Exibir um montante de compras de um cliente\n7 - Sair.\n");
        scanf("%d", &op);

        switch(op) {
            case 1:

                incluirCliente(&cabeca);
                break;

            case 2:
                removerCliente(cabeca);

                break;
            case 3:
                atualizarMontante(cabeca);

                break;
            case 4:
                proximoMes(cabeca);
                break;
            case 5:
                melhorComprador(cabeca);
                break;
            case 6:
                exibeMontante(cabeca);

                break;
            case 7:
                printf("Programa finalizado\n");
                break;
            default:
                printf("\n\nValor digitado incorreto por favor digite novamente!\n\n");

        }
        fflush(stdin);
    }while(op != 7);

    noAtual = cabeca;
    while(noAtual != NULL) {
        cabeca = noAtual->proximo;
        free(noAtual);
        noAtual = cabeca;
    }
    return 0;
}

void listar (CADASTRO *noAtual) {
    int i=0;
    while(noAtual != NULL) {
        i++;
        printf("\n\nId: %d\nNome do Cliente: %s\nAno de Nascimento: %d\nGastos do Cliente: %.2f\n",
               i, noAtual->nome, noAtual->anoNascimento, noAtual->gastosMes);
        noAtual = noAtual->proximo;
    }
}



void incluirCliente(CADASTRO **cabeca) {
    CADASTRO *noAtual, *novoNo;
    char nome[30];
    int anoNascimento;
    double gastosMes;

    printf("Digite o nome do cliente: ");
    scanf("%s", nome);
    printf("digite o ano de nascimento: ");
    scanf("%d", &anoNascimento);

    printf("Digite o montante de gastos: ");
    scanf("%lf", &gastosMes);

    if(*cabeca == NULL) {
        *cabeca = (CADASTRO *) malloc(sizeof(CADASTRO));
        strcpy((*cabeca)->nome, nome);
        (*cabeca)->anoNascimento = anoNascimento;
        (*cabeca)->gastosMes = gastosMes;
        (*cabeca)->proximo = NULL;
    } else {
        noAtual = *cabeca;
        while(noAtual->proximo != NULL) {
            noAtual = noAtual->proximo;
        }
        novoNo = (CADASTRO *) malloc(sizeof(CADASTRO));
        strcpy(novoNo->nome, nome);
        novoNo->anoNascimento = anoNascimento;
        novoNo->gastosMes = gastosMes;
        novoNo->proximo = NULL;
        noAtual->proximo = novoNo;
    }
}

CADASTRO* removerCliente(CADASTRO *lista) {

    CADASTRO *ant = NULL;
    CADASTRO *p = lista;

    char nome[30], nome2[30];
    printf("\nDigite o nome do cliente que desejar remover: ");
    scanf("%s", &nome);
    strlwr(nome);

    while(p != NULL) {
        strcpy(nome2, p->nome);
        strlwr(nome2);

        if(strcmp(nome, nome2) == 0)
            break;
        ant = p;
        p = p->proximo;
    }

    if(p == NULL) {
        printf("\n\nLista não encontrado\n\n");
        return lista;
    }
    if(ant == NULL) {

        p->proximo = lista->proximo;
        printf("\n\nCliente removido com sucesso\n\n");
    } else {
        printf("\n\nCliente removido com sucesso\n\n");
        ant->proximo = p->proximo;
    }

    free(p);
    return lista;

}

void atualizarMontante(CADASTRO *noAtual) {
    CADASTRO* p = noAtual;

    char nome[30], nome2[30];
    double montante;

    printf("\n\nDigite o nome do cliente que deseja atualizar o montante: ");
    scanf("%s", &nome);
    strlwr(nome);


    while(p != NULL) {
        strcpy(nome2, p->nome);
        strlwr(nome2);

        if(strcmp(nome, nome2) == 0) {
            printf("Digite o montante atualizado do no mês corrente: ");
            scanf("%lf", &montante);
            p->gastosMes = montante;
            printf("\n\nMontante atualizado com sucesso\n\n");
            break;
        }


        p = p->proximo;
    }
    if(strcmp(nome, nome2) != 0) {
        printf("\n\nNome do cliente não encontrado\n\n");
    }

}

void exibeMontante(CADASTRO *lista) {
    CADASTRO* p = lista;

    char nome[30], nome2[30];

    printf("\n\nDigite o nome do cliente que desejar exibe o montante: ");
    scanf("%s", nome);
    strlwr(nome);

    while(p != NULL) {
        strcpy(nome2, p->nome);
        strlwr(nome2);

        if(strcmp(nome, nome2) == 0) {
            printf("\n\nNome do Cliente: %s\nMontante: %.2f\n\n", p->nome, p->gastosMes);
        }
        p = p->proximo;
    }

    if(strcmp(nome, nome2) != 0) {
        printf("\n\nNome do cliente não encontrado\n\n");
    }
}

void proximoMes(CADASTRO *noAtual) {
    if(noAtual == NULL) {
        printf("\n\nNenhum cliente encontrado\n\n");
    } else {
        printf("\n\nTodos os montantes zerado com sucesso!\n\n");
    }
    while(noAtual != NULL) {
        noAtual->gastosMes = 0;
        noAtual = noAtual->proximo;

    }
}

void melhorComprador(CADASTRO *noAtual) {
    CADASTRO *p, *ant;
    double auxGasto;
    int auxAno;
    char auxNome[30];
    if(noAtual == NULL) {
        printf("\n\nNão Tem cliente\n\n");
    }
    for(ant=noAtual; ant!=NULL; ant=ant->proximo) {
        for(p=ant->proximo; p!=NULL; p=p->proximo) {
            if(ant->gastosMes < p->gastosMes) {
                strcpy(auxNome, ant->nome);
                strcpy(ant->nome, p->nome);
                strcpy(p->nome, auxNome);

                auxAno = ant->anoNascimento;
                ant->anoNascimento = p->anoNascimento;
                p->anoNascimento = auxAno;

                auxGasto = ant->gastosMes;
                ant->gastosMes = p->gastosMes;
                p->gastosMes = auxGasto;
            }
        }
    }

    if(noAtual != NULL) {
        printf("\n\nNome do Cliente: %s\nAno de Nascimento: %d\nGastos do Cliente: %.2f\n\n",
                   noAtual->nome, noAtual->anoNascimento, noAtual->gastosMes);
    }
}






