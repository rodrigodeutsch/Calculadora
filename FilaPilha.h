/// estruturas

typedef struct Node node;
typedef struct Fila fila;
typedef struct Nodeint nodeInt;

///fun��es

 //pilha
node* inicializaPilha();
int pilhaVazia(node *pilha);
void push(node *p, char elemento);
void pop(node *p);
char top(node *p);

 //fila
fila* inicializaFila();
int filaVazia(fila *f);
void enqueue(fila *f, char elemento);
char dequeue(fila *f);
void limpaFila(fila *f);
void imprime(fila *f);
void imprimeTudo(fila* f);

//pilha de inteiros

nodeInt* inicializaPilhaInt();
int pilhaIntVazia(nodeInt *pilha);
void pushInt(nodeInt *p, int elemento);
void popInt(nodeInt *p);
int topInt(nodeInt *p);
