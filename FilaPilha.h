/// estruturas

typedef struct Node node;
typedef struct Fila fila;

///funções

 //pilha
node* inicializaPilha();
int pilhaVazia(node *pilha);
void push(node *p, char elemento[10]);
void pop(node *p);
char top(node *p);

 //fila
fila* inicializaFila();
int filaVazia(fila *f);
void enqueue(fila *f, char elemento[10]);
char dequeue(fila *f);
void limpaFila(fila *f);
void imprime(fila *f);
void imprimeTudo(fila* f);
