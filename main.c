#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FilaPilha.h"

/// protótipos

void conversor(fila *f, node *pilha); //converte de infix para pós fixada
int calculaResultado(fila *f, node *pilha); //calcula o resultado da equação pós fixada

///main

int main(){
    node *pilha;
    fila *f;
    int resultado = 0;

    f = inicializaFila();
    pilha = inicializaPilha();

    conversor(f, pilha);
    resultado = calculaResultado(f, pilha);

    printf("\nO resultado eh: %d\n", resultado);

    return 0;
}

/// funções

void conversor(fila *f, node *pilha){
    char token;
    char aux;
    int i=0;
    char equacao[100]; //equação matematica

    printf("\n Entre com a equacao matematica desejada(deixe um espaco entre cada caracter\n e feche todos parenteses):\n");
    fgets(equacao,99,stdin); //lê equação

    for(i=0;i<strlen(equacao)-1;i++){
    token = equacao[i]; //pega caracter por carater como token
        if(token == ' '){ //se tiver espaço em branco, passa automaticamente pra posição da frente
            while(token == ' '){ //resolve o problema de espaços consecutivos
              i++;
              token  = equacao[i];//pega o token que não é espaço em branco
            }
        }
        if(((token == '*' || token == '/') || (token == '+' || token == '-')) && (token != '(' && token != ')')){
            while(!pilhaVazia(pilha) && ((top(pilha) == '*' || top(pilha) == '/' || top(pilha) == '-' || top(pilha) == '+') && ((token == '+' || token == '-') || (token == '*' || token == '/')))){
                aux = top(pilha); //passa topo da pilha para aux
                pop(pilha); //tira topo da pilha
                enqueue(f, aux); //coloca aux na fila
            }
            push(pilha, token); //coloca na pilha o token que não caiu no if
        }
        else if(token == '(' || token == ')'){ //verifica parenteses
                if(token == ')'){
                    while(top(pilha) != '('){ //nao para até chegar no fim do parenteses
                        aux = top(pilha); //continua desempilhando até achar um abre parenteses
                        pop(pilha); //descarta topo
                        enqueue(f, aux); //coloca o elemento retirado da pilha na fila
                    }
                pop(pilha); // quando achar o abre parenteses, tira ele da pilha
                }
                else{
                    push(pilha, token); //
                }
        }
        else{
            enqueue(f, token); ///TOKEN É UM OPERANDO
        }
    }
    enqueue(f, top(pilha)); //coloca na fila o topo da pilha
    //imprime(f);
    pop(pilha);
    printf("\nEquacao pos fixada: ");
    imprimeTudo(f); // imprime a equação pós fixada
    printf("\n");
}

int calculaResultado(fila *f, node *pilha){
    char token;
    char aux1, aux2;
    int primeiroOperando, segundoOperando, total;
    nodeInt *pilhaInt; // pilha que armazena os valores transformados para inteiro

    pilhaInt = inicializaPilhaInt();

    while(!filaVazia(f)){ //verifica se a fila nãoo está vazia
        token = dequeue(f);
        if(token != '*' && token != '/'  && token != '+' && token != '-' ){
            push(pilha, token);
        }
        else{
            if(!pilhaIntVazia(pilhaInt)){ // se já tiver um número na pilha de inteiros, usar ele como primeiro operando
                primeiroOperando = topInt(pilhaInt);
            }
            else{
            aux1 = top(pilha);
            primeiroOperando = aux1 - '0'; // transforma operando em inteiro
            pop(pilha); // tira operando da pilha
            }
            aux2 = top(pilha);
            segundoOperando = aux2 - '0'; // transforma operando em inteiro
            pop(pilha);// tira operando da pilha


            if( token == '*' || token == '/' || token == '+' || token == '-' ){
                switch(token){
                    case '*':
                        total = (segundoOperando*primeiroOperando);
                        break;
                    case '/':
                        total = (segundoOperando/primeiroOperando);
                        break;
                    case '+':
                        total = (segundoOperando+primeiroOperando);
                        break;
                    case '-':
                        total = (segundoOperando-primeiroOperando);
                        break;
            }
            pushInt(pilhaInt, total);//coloca o resultado da operação em uma pilha de inteiros pra não ter problema com a range do char
            total = 0;
        }
    }
    }
    return (topInt(pilhaInt)); //retorna o resultado da equacao
}


