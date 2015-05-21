#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FilaPilha.h"

/// prot�tipos

void conversor(fila *f, node *pilha); //converte de infix para p�s fixada
int calculaResultado(fila *f, node *pilha); //calcula o resultado da equa��o p�s fixada

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

/// fun��es

void conversor(fila *f, node *pilha){
    char token;
    char aux;
    int i=0;
    char equacao[50]; //equa��o matematica

    printf("\n Entre com a equacao matematica desejada(deixe um espaco entre cada caracter e feche todos parenteses):\n");
    fgets(equacao,49,stdin); //l� equa��o

    for(i=0;i<strlen(equacao)-1;i++){
    token = equacao[i]; //pega caracter por carater como token
        if(token == ' '){ //se tiver espa�o em branco, passa automaticamente pra posi��o da frente
            while(token == ' '){ //resolve o problema de espa�os consecutivos
                i++;
                token  = equacao[i];//pega o token que n�o � espa�o em branco
            }
        }
        if(((token == '*' || token == '/') || (token == '+' || token == '-')) && (token != '(' || token != ')')){
            while(!pilhaVazia(pilha) && ((top(pilha) == '*' || top(pilha) == '/') && ((token == '+' || token == '-') || (token == '*' || token == '/')))){
                aux = 0; //atribui NULL ao auxiliar
                aux = top(pilha); //passa topo da pilha para aux
                pop(pilha); //tira topo da pilha
                enqueue(f, aux); //coloca aux na fila
            }
            push(pilha, token); //coloca na pilha o token que n�o caiu no if
        }
        else if(token == '(' || token == ')'){ //verifica parenteses
                if(token == '('){
                    while(top(pilha) != ')'){ //nao para at� chegar no fim do parenteses
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
            enqueue(f, token); //coloca token que n�o cai em nenhum if na fila
        }
    }
    enqueue(f, top(pilha)); //coloca na fila o topo da pilha
    //imprime(f);
    pop(pilha);
    imprimeTudo(f);
}

int calculaResultado(fila *f, node *pilha){
    char token;
    char aux1, aux2;
    int primeiroOperando, segundoOperando, total;

    while(!filaVazia(f)){ //verifica se a fila n�o est� vazia
        token = dequeue(f);
        if( token != '*' && token != '/'  && token != '+' && token != '-' ){
            push(pilha, token);
        }else{
            printf("entra aqui");
            aux1 = top(pilha);
            primeiroOperando = aux1 - 48;
            pop(pilha);

            aux2 = top(pilha);
            segundoOperando = aux2 - 48;
            pop(pilha);

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

            /*if(token == '+'){
                printf("%c", token);
                total = segundoOperando + primeiroOperando;
            }
            else if(token == '-'){
                total = segundoOperando - primeiroOperando;
            }
            else if(token == '*'){
                total = segundoOperando * primeiroOperando;
            }
            else if(token == '/'){
                total = segundoOperando / primeiroOperando;
            }*/
            aux1 = total = total + '0';
            push(pilha, aux1);
        }
    }
    }
    return top(pilha)-48;
}


