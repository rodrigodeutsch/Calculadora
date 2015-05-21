#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FilaPilha.h"

/// protótipos

void conversor(fila *f, node *pilha, fila *filaTokens); //converte de infix para pós fixada
int calculaResultado(fila *f, node *pilha); //calcula o resultado da equação pós fixada

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

/// funções

void conversor(fila *f, node *pilha, fila *filaTokens){
    char token[10];
    char aux;
    int i=0, j=0, cont=0;
    char equacao[50]; //equação matematica
    char tokenAuxiliar[10];

    printf("\n Entre com a equacao matematica desejada(deixe um espaco entre cada caracter e feche todos parenteses):\n");
    fgets(equacao,49,stdin); //lê equação

    ///for que armazena cada token em uma posição da fila "filaTokens"
    for(i=cont;i<strlen(equacao)-1;i++){
        if(token == ' '){ //se tiver espaço em branco, passa automaticamente pra posição da frente
            while(token == ' '){ //resolve o problema de espaços consecutivos
                i++;
            }
        }
        else{
            do{
            tokenAuxiliar[j] = equacao[i];//pega o token que não é espaço em branco
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
            else{ //é abre parenteses
                push(pilha, token);
            }
        }
        else{
            enqueue(f, token);
        }

    }
    enqueue(f, top(pilha));
    pop(pilha);







    /*for(i=0;i<strlen(equacao)-1;i++){
    token = equacao[i]; //pega caracter por carater como token
        if(token == ' '){ //se tiver espaço em branco, passa automaticamente pra posição da frente
            while(token == ' '){ //resolve o problema de espaços consecutivos
                i++;
                token  = equacao[i];//pega o token que não é espaço em branco
            }
        }
        if(((token == '*' || token == '/') || (token == '+' || token == '-')) && (token != '(' || token != ')')){
            while(!pilhaVazia(pilha) && ((top(pilha) == '*' || top(pilha) == '/') && ((token == '+' || token == '-') || (token == '*' || token == '/')))){
                aux = 0; //atribui NULL ao auxiliar
                aux = top(pilha); //passa topo da pilha para aux
                pop(pilha); //tira topo da pilha
                enqueue(f, aux); //coloca aux na fila
            }
            push(pilha, token); //coloca na pilha o token que não caiu no if
        }
        else if(token == '(' || token == ')'){ //verifica parenteses
                if(token == '('){
                    while(top(pilha) != ')'){ //nao para até chegar no fim do parenteses
                        aux = 0; //atribui NULL a aux
                        aux = top(pilha); //atribui o topo da pilha a aux
                        pop(pilha); //tira o topo da pilha
                        enqueue(f, aux); //coloca aux na fila
                    }
                pop(pilha); // quando achar o fecha parenteses, tira ele da pilha
                }
                else{
                    push(pilha, token);
                }
        }
        else{
            enqueue(f, token); //coloca token que não cai em nenhum if na fila
        }
    }
    enqueue(f, top(pilha)); //coloca na fila o topo da pilha
    //imprime(f);
    pop(pilha);*/
    imprimeTudo(f);
}

int calculaResultado(fila *f, node *pilha){
    char token[10];
    char aux1[10], aux2[10];
    int primeiroOperando, segundoOperando, total;

    while(!filaVazia(f)){ //verifica se a fila não está vazia
        strcpy(token, dequeue(f));
        if( token != '*' && token != '/'  && token != '+' && token != '-' ){
            push(pilha, token);
        }else{
            printf("entra aqui");
            strcpy(aux1, top(pilha));
            primeiroOperando = aux1 - 48;
            pop(pilha);

            strcpy(aux2, top(pilha));
            segundoOperando = aux2 - 48;
            pop(pilha);

            if(token == '+'){
            total = segundoOperando + primeiroOperando;
            }
            else if(token == '-'){
                total = segundoOperando - primeiroOperando;     ///inverte os operandos pois é pós fixada a notação
            }
            else if(token == '*'){
                total = segundoOperando * primeiroOperando;
            }
            else if(token == '/'){
                total = segundoOperando / primeiroOperando;     ///inverte os operandos pois é pós fixada a notação
            }
            aux1 = total = total + '0';
            push(pilha, aux1);
        }
    }
    }
    return top(pilha)-48;
}


