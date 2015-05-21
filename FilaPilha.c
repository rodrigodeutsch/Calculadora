#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FilaPilha.h"

//Structs


typedef struct Node{
    char dado[10];
    struct Node *prox;
}node;


typedef struct Fila{
    node *ini;
    node *fim;
}fila;

node* inicializaPilha(){
    node *p;

    p = (node*)malloc(sizeof(node));
    if(!p){
        return 0;
    }
    p->prox = NULL;
    return p;
}

int pilhaVazia(node *pilha){
    if(pilha == NULL)
         return 1;
    else
        return 0;
}

void push(node *p, char elemento[10]){
    node *novo;
    novo = (node *)malloc(sizeof(node));

    strcpy(novo->dado, elemento);
    novo->prox = NULL;

    if(p->prox == NULL){
        p->prox = novo;
        return;
    }
    novo->prox = p->prox;
    p->prox = novo;
    return;
}

void pop(node *p){
    if(p->prox == NULL){
        printf("\n A lista esta vazia!\n");
        return;
    }
    node *temp1, *temp2;
    char conteudo;
    temp1 = p->prox;
    conteudo = p->dado;
    temp2 = temp1->prox;
    free(temp1);
    p->prox = temp2;
}

char top(node *p){
    if(!p){
        printf("\nPilha nao existe!\n");
        return;
    }
    return p->prox->dado;
}


fila* inicializaFila(){
    fila *f;
    f = (fila *)malloc(sizeof(fila));
    if(!f){
        return 0;
    }

    f->ini = NULL;
    f->fim = NULL;
    return f;
}

int filaVazia(fila *f){
if(f->ini == NULL )
    return 1;
else
    return 0;
}

void enqueue(fila *f, char elemento[10]){
    node *novo;
    novo = (node*)malloc(sizeof(node));

    strcpy(novo->dado, elemento);
    novo->prox = NULL;
    if(f->ini == NULL){ //verifica se a lista não estava vazia antes
        f->ini = novo;
    }
    else{
        f->fim->prox = novo;
    }
    f->fim = novo;
}

char dequeue(fila *f){
    char i;
    node *r;


    if(f->ini == NULL){
        printf("\n A lista esta vazia!\n");
        exit(1);
    }
    i = f->ini->dado;
    r = f->ini->prox;

    free(f->ini);
    f->ini = r;

    if(f->ini == NULL){//se a fila ficou vazia
        f->fim = NULL;
    }
    return  i;
}

void limpaFila(fila *f){
    node *temp, *temp1;
    temp = f->ini;

    while(temp != NULL){
        temp1 = temp->prox;
        free(temp);
        temp = temp1;
    }
    free(f);
}

void imprime(fila *f){
    if(f->ini != NULL){
        printf("\nPrimeiro da fila: %d\n", f->ini->dado);
    }
    else{
        printf("\n\tLista vazia!\n");
    }
}

void imprimeTudo(fila* f){
    node *q;
    for (q=f->ini; q!=NULL; q=q->prox)
    printf("%c",q->dado);
}
