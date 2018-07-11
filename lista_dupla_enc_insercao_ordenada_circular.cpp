#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 30

//15-11-17

typedef struct Aluno{
    char nome[MAX];
    int ra;
    Aluno *prox;
    Aluno *ant;
}Aluno;

Aluno *novoElemento(){
    Aluno *novo =(Aluno*)malloc(sizeof(Aluno));
    if(novo == NULL){
        printf("\nNao ha espaco de memoria");
        exit(1);
    }
    printf("\nDigite o nome do Aluno: ");
    getchar();
    fgets(novo->nome, MAX, stdin);
    printf("Digite o RA: ");
    scanf("%d",&novo->ra);
    return novo;
}

Aluno *localizaPorNome(Aluno *inicio, char pNome[30]){
    Aluno *temp;

    if(inicio != NULL){
        if(strcmp(inicio->nome,pNome) == 0)
            return inicio;
        else{
            temp = inicio;
            do{
                temp = temp->prox;
            } while((temp != inicio) && (strcmp(temp->nome,pNome) != 0));
            if(strcmp(temp->nome,pNome) == 0)
                return temp;
        }
    }
    return NULL;
}

Aluno *insereInicio(Aluno *inicio, Aluno *fim, Aluno *novo){
    novo->prox = inicio;
    novo->ant = fim; //add circular
    inicio->ant = novo;
    fim->prox = novo; //add circular
    return novo;
}

Aluno *insereFim(Aluno *inicio, Aluno *fim, Aluno *novo){
    novo->prox = inicio; // add circular
    novo->ant = fim;
    fim->prox = novo;
    inicio->ant = novo; // add circular
    return novo;
}

void insereMeio(Aluno *temp, Aluno *novo){
    novo->prox = temp;
    novo->ant = temp->ant;
    temp->ant->prox = novo;
    temp->ant = novo;
}

int escolha(){
    int op;
    do{
        printf("\nDigite 1 - Antes ou 2 - Depois do elemento: ");
        scanf("%d", &op);
        if((op != 1) && (op != 2))
             printf("\nOpcao Invalida.");

        }while((op != 1) && (op != 2));
    return op;
}

void insere(Aluno **inicio, Aluno **fim){ // checar essa subrotina
    Aluno *novo, *enc;
    char nomeProcurado[30];
    novo = novoElemento();

    if(*inicio == NULL){
        novo->prox = novo;
        novo->ant = novo;
        *inicio = novo;
        *fim = novo;
    }

    else if(*inicio == *fim){
        if(escolha() == 1)
            *inicio = insereInicio(*inicio,*fim,novo);
        else
            *fim = insereFim(*inicio,*fim,novo);
        }

    else{
        printf("\nDigite o Nome a ser localizado para Insercao: ");
        fflush(stdin);
        fgets(nomeProcurado, 30, stdin);

        if(strcmp((*inicio)->nome,nomeProcurado) == 0){

            if(escolha() == 1)
                *inicio = insereInicio(*inicio, *fim, novo);
            else{
                enc = (*inicio)->prox;
                insereMeio(enc,novo);
            }
        }
        else if (strcmp((*fim)->nome,nomeProcurado) == 0){

            if(escolha() == 1)
                insereMeio(*fim,novo);
            else
                *fim = insereFim(*inicio,*fim,novo);
        }

        else{
            enc = localizaPorNome(*inicio,nomeProcurado);
            if(enc == NULL)
                printf("\nO Nome nao foi localizado.\n");
            else{

                if(escolha() == 2)
                    enc = enc->prox;
                }
            insereMeio(enc,novo);
            }
        }
    }


Aluno *removeInicio(Aluno *inicio, Aluno *fim){
    Aluno *temp;
    temp = inicio->prox;
    temp->ant = fim;
    fim->prox = temp;
    free(inicio);
    return temp;
}

void removeMeio(Aluno *enc){
    enc->ant->prox = enc->prox;
    enc->prox->ant = enc->ant;
    free(enc);
}

Aluno *removeFim(Aluno *inicio, Aluno *fim){
    Aluno *temp;
    temp = fim->ant;
    temp->prox = inicio;
    inicio->ant = temp;
    free(fim);
    return temp;
}

void remover(Aluno **inicio, Aluno **fim){
    char nomeProcurado[MAX];
    Aluno *enc;

    if(*inicio == NULL)
        printf("\nLista Vazia!\n");
    else{

        if(*inicio == *fim){
            printf("\n\nRemovendo... RA: %d \tNome: %s", (*inicio)->ra, (*inicio)->nome);
            free(*inicio);
            *inicio = NULL;
        }

        else{
            printf("\nDigite o nome a ser procurado: ");
            fflush(stdin);
            fgets(nomeProcurado, MAX, stdin);
            if(strcmp((*inicio)->nome,nomeProcurado) == 0){
                printf("\n\nRemovendo... RA: %d \tNome: %s", (*inicio)->ra, (*inicio)->nome);
                *inicio = removeInicio(*inicio, *fim);
            }
            else if (strcmp((*fim)->nome,nomeProcurado) == 0){
                printf("\n\nRemovendo... RA: %d \tNome: %s", (*fim)->ra, (*fim)->nome);
                *fim = removeFim(*inicio, *fim);
            }
            else{
                enc = localizaPorNome(*inicio,nomeProcurado);
                if(enc == NULL)
                    printf("\nO nome nao foi localizado para ser removido\n");
                else{
                    printf("\n\nRemovendo... RA: %d \tNome: %s", enc->ra, enc->nome);
                    removeMeio(enc);
                }
            }
        }
    }
}

void listar(Aluno *inicio, Aluno *fim, int op){
   Aluno *temp;
    if(inicio == NULL)
        printf("\nERRO: Esta lista não possuem elementos para serem listados.\n");
    else{
        if(op == 7){
            temp = inicio;
            do{
                printf("\nRA: %d \nNome: %s", temp->ra, temp->nome);
                temp = temp->prox;
                }while(temp != inicio);
            }
        else if (op == 8){
            temp = fim;
            do{
               printf("\nRA: %d \nNome: %s", temp->ra, temp->nome);
               temp = temp->ant;
                }while(temp != fim);
        }
    }
}


void esvaziar(Aluno **I){
     Aluno *temp, *temp2;

     if(*I != NULL){
        temp2 = *I;
        do{
            temp = (*I)->prox;
            free(*I);
            *I = temp;
            printf("deletou um \n");
            } while (*I != temp2);
            *I = NULL;
     }
}

int main(){
    Aluno *inicio = NULL, *fim;
    int op, i;

    do{
        printf("\nEscolha uma das opcoes:\n1 - Inserir\n2 - Remover\n3 - Listar\n4 - Esvaziar\n5 - Sair\nQual eh a opcao desejada: ");

        scanf("%d", &op);
            switch (op){
                case 1:
                    insere(&inicio,&fim);
                    //listar(inicio,fim,'I');
                    break;
                case 2:
                    remover(&inicio,&fim);
                    listar(inicio,fim,7);
                    break;
                case 3:
                    if(inicio != NULL){
                        do{
                            printf("\nDigite 7 para listar crescente e 8 para listar descrescente");
                            scanf("%d", &i);
                            if(i != 7 && i != 8)
                                printf("\nERRO: Valor Invalido");
                            }while (i != 7 && i != 8);
                        listar(inicio,fim,i);
                    }else
                          printf("\nERRO: Lista Vazia.\n");
                    break;
                case 4:
                    esvaziar(&inicio);
                    printf("\nLista completamente Removida\n");
                    break;
                case 5:
                    printf("\nExecutando procedimento de limpeza de dados antes de sair\n");
                    esvaziar(&inicio);
                    break;
                //case 'C':
                  //  system("CLS");
                    //break;

                default:
                    printf("\nERRO:Opcao Invalida.\n");
            }
        }while (op != 5);
return 0;
}
