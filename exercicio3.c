#include <stdlib.h>
#include <stdio.h>

typedef struct noh {
    int dado;
    struct noh *esquerda, *direita; // *pai
}No;

void imprimir_arvore (No *raiz);
No* procurar_no (No *raiz, int x);
int numero_nos (No *raiz);
int altura (No *raiz);
No* criar_no (int x, No*l, No*r);
void destruir_arvore(No **raiz);
int numero_folhas(No*raiz);

int main(){
    No *raiz1 = criar_no(5,criar_no(4, NULL, NULL), criar_no(6, NULL, NULL));
    No *raiz2 = criar_no(5,criar_no(4, NULL, NULL), criar_no(6, NULL, 
                                                criar_no(10,criar_no(9, NULL, NULL), criar_no(15, NULL, NULL))));
                

   
    int num1 = numero_folhas(raiz1);
    printf("Numero de folhas da arvore 1: %d\n", num1);

    int num2 = numero_folhas(raiz2);
    printf("Numero de folhas da arvore 2: %d\n", num2);

    destruir_arvore(&raiz1);
    destruir_arvore(&raiz2);


return 0;
}

No* criar_no (int x, No *l, No *r) {
    No *no = (No*) malloc(sizeof (No));
    no->dado = x;
    no->esquerda = l;
    no->direita = r;
    return no;
}

void destruir_arvore (No **raiz){//função recursiva
    if (*raiz == NULL) return;  
    destruir_arvore (&((*raiz)->esquerda)); 
    destruir_arvore (&((*raiz)->direita)); 
    free (*raiz);
    *raiz = NULL;
}

void printnode (int x, int h){
    int i;
    for (i = 0; i < h; i++){
        printf("-"); 
        printf("%2d\n", x);
    }
}
    
void print (No *p, int h){
    if (p == NULL) 
        return;
     print (p->direita, h+1); 
     printnode (p->dado, h); 
     print (p->esquerda, h+1); 
}

void imprimir_arvore (No *raiz) { 
    print (raiz, 0); 
}

No* procurar_no (No *raiz, int x) {
    if (raiz == NULL || raiz->dado == x)
        return raiz;
    No *esquerda = procurar_no (raiz->esquerda, x);
    if (esquerda!= NULL)
        return esquerda;
    return procurar_no(raiz->direita, x);
}

int numero_nos(No*raiz){
    if (raiz == NULL)
        return 0;
    return numero_nos(raiz->esquerda) + numero_nos(raiz->direita)+1;
}

int altura(No *raiz){
    int h_esquerda, h_direita;
    if (raiz== NULL )
        return 0;
    h_esquerda = altura(raiz->esquerda);
    h_direita = altura(raiz->direita);
    return( h_esquerda>h_direita ? h_esquerda:h_direita)+1;
}

int numero_folhas(No *raiz) {
    if (raiz == NULL)
        return 0;
    if (raiz->esquerda == NULL && raiz->direita == NULL) // Nó folha
        return 1;
    int folhas_esquerda = numero_folhas(raiz->esquerda);
    int folhas_direita = numero_folhas(raiz->direita);
    return folhas_esquerda + folhas_direita;
}

