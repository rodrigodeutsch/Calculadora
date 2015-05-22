#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FilaPilha.h"

/// prot�tipos

void conversor(fila *f, node *pilha, fila *filaTokens); //converte de infix para p�s fixada
int calculaResultado(fila *f, node *pilha); //calcula o resultado da equa��o p�s fixada

///main

int main(){
    node *pilha;
    fila *f, *filaTokens;
    int resultado = 0;

    f = inicializaFila();
    filaTokens = inicializaFila();
    pilha = inicializaPilha();

    conversor(f, pilha, filaTokens);
    resultado = calculaResultado(f, pilha);

    printf("\nO resultado eh: %d\n", resultado);

    return 0;
}

/// fun��es

void conversor(fila *f, node *pilha, fila *filaTokens){
    char token[10];
    char aux;
    int i=0, j=0, cont=0;
    char equacao[50]; //equa��o matematica
    char tokenAuxiliar[10];

    printf("\n Entre com a equacao matematica desejada(deixe um espaco entre cada caracter e feche todos parenteses):\n");
    fgets(equacao,49,stdin); //l� equa��o

    ///for que armazena cada token em uma posi��o da fila "filaTokens"
    for(i=cont;i<strlen(equacao)-1;i++){
        if(token == ' '){ //se tiver espa�o em branco, passa automaticamente pra posi��o da frente
            while(token == ' '){ //resolve o problema de espa�os consecutivos
                i++;
            }
        }
        else{
            do{
            tokenAuxiliar[j] = equacao[i];//pega o token que n�o � espa�o em branco
            j++;
            i++;
            }while(token!= ' ');

            ///tokenAuxiliar[strlen(tokenAuxiliar)+1] = '\0';
            enqueue(filaTokens, tokenAuxiliar);
        }
        j=0;
        cont=i;
    }

    while(!filaVazia(filaTokens)){
        strcpy(token, dequeue(filaTokens));
        if((token != '*' && token != '/'  && token != '+' && token != '-') && token != '(' && token != ')'){
            while(!pilhaVazia(pilha) && ((strcmp(top(pilha), '*') || strcmp(top(pilha), '/')) && (strcmp(token, '+') || strcmp(token, '-') || (strcmp(token, '*') || strcmp(token, '/'))))){
            enqueue(f, top(pilha));
            pop(pilha);
        }
        push(pilha, token);
        }
        else if((strcmp(token, '(')) == 0 || strcmp(token, ')')){
            if (strcmp(token, ')') == 0){
                while(strcmp(top(pilha), '(')){
                        enqueue(f, top(pilha));
                        pop(pilha);
                }
            pop(pilha);
            }
            else{ //� abre parenteses
                push(pilha, token);
            }
        }
        else{
            enqueue(f, token);
        }

    }
    enqueue(f, top(pilha));
    pop(pilha);
    imprimeTudo(f);
}

int calculaResultado(fila *f, node *pilha){
    char token[10];
    char aux1[10], aux2[10];
    int primeiroOperando, segundoOperando, total;
    int tamanho; //serve para verificar a ordem do n�mero
    int i=0, multiplicador=1; //contador para o for e divisor para a string
    int primeiroTotal=0, segundoTotal=0; //servem para auxiliar a convers�o das strings para n�meros inteiros
    nodeInt *pilhaInt;

    pilhaInt = inicializaPilhaInt();

    while(!filaVazia(f)){ //verifica se a fila n�o est� vazia
        strcpy(token, dequeue(f));
        if(token != '*' && token != '/'  && token != '+' && token != '-' ){
            push(pilha, token);
        }else{
            printf("entra aqui");

            if(!pilhaIntVazia(pilhaInt)){
                primeiroOperando = topInt(pilhaInt);
                }
                else{
                strcpy(aux1, top(pilha));
                tamanho = strlen(aux1);

                    for(i=tamanho; i>0; i--){
                        primeiroTotal = primeiroTotal + ((aux1[i]-48)*multiplicador);
                        multiplicador = multiplicador*10;
                    }
                    multiplicador = 1;
                    i=0;
                    primeiroOperando = primeiroTotal;
                    primeiroTotal = 0;
                    pop(pilha);
            }

            strcpy(aux2, top(pilha));
            tamanho = strlen(aux2);
                for(i=tamanho; i>0; i--){
                    segundoTotal = segundoTotal + ((aux1[i]-48)*multiplicador);
                    multiplicador = multiplicador*10;
                }
                multiplicador = 1;
                i=0;
                segundoOperando = segundoTotal;
                segundoTotal = 0;
                pop(pilha);

            if(token == '+'){
            total = segundoOperando + primeiroOperando;
            }
            else if(token == '-'){
                total = segundoOperando - primeiroOperando;     ///inverte os operandos pois � p�s fixada a nota��o
            }
            else if(token == '*'){
                total = segundoOperando * primeiroOperando;
            }
            else if(token == '/'){
                total = segundoOperando / primeiroOperando;     ///inverte os operandos pois � p�s fixada a nota��o
            }

            push(pilhaInt, total);
            total = 0;
        }
    }
    return (top(pilha));
}



