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
int sao_iguais(No *arvore1, No *arvore2);
No* reconstruir_arvore(int* pre_ordem, int* em_ordem, int inicio, int fim, int* indice);
void obter_percurso_pos_ordem(int* pre_ordem, int* em_ordem, int tamanho);
void percurso_pos_ordem(No* raiz);
void percurso_em_ordem(No *raiz);
int calcular_fator_balanceamento(No *raiz);

int main(){
    
   No *raiz2 = criar_no(5,criar_no(4, NULL, NULL), criar_no(6, NULL, 
                                                criar_no(10,criar_no(9, NULL, NULL), criar_no(15, NULL, NULL))));

    No *raiz1 = criar_no(5,criar_no(4, NULL, NULL), criar_no(6, NULL, NULL));

    int fator_de_balanceamento1 = calcular_fator_balanceamento(raiz1);
    int fator_de_balanceamento2 = calcular_fator_balanceamento(raiz2);

    printf("\nFator de balanceamento da arvore 1 eh: %d\n", fator_de_balanceamento1);
    printf("Fator de balanceamento da arvore 2 eh: %d\n", fator_de_balanceamento2);


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

int sao_iguais(No *arvore1, No *arvore2) {
    if (arvore1 == NULL && arvore2 == NULL)
        return 1;
    
    if (arvore1 == NULL || arvore2 == NULL)
        return 0;
    
    if (arvore1->dado != arvore2->dado)
        return 0;
    
    int iguais_esquerda = sao_iguais(arvore1->esquerda, arvore2->esquerda);
    int iguais_direita = sao_iguais(arvore1->direita, arvore2->direita);
    
    return iguais_esquerda && iguais_direita;
}

No* reconstruir_arvore(int* pre_ordem, int* em_ordem, int inicio, int fim, int* indice) {
    if (inicio > fim)
        return NULL;
    
    //o próximo nó da pré-ordem é o nó atual
    No* no = criar_no(pre_ordem[*indice], NULL, NULL);
    (*indice)++;
    
    //se o nó não tem filhos, retornamos o nó
    if (inicio == fim)
        return no;
    
    //encontrar a posição do nó atual no percurso em-ordem
    int posicao = -1;
    for (int i = inicio; i <= fim; i++) {
        if (em_ordem[i] == no->dado) {
            posicao = i;
            break;
        }
    }
    
    //reconstruir a subárvore esquerda
    no->esquerda = reconstruir_arvore(pre_ordem, em_ordem, inicio, posicao - 1, indice);
    
    //reconstruir a subárvore direita
    no->direita = reconstruir_arvore(pre_ordem, em_ordem, posicao + 1, fim, indice);
    
    return no;
}

void percurso_pos_ordem(No* raiz) {
    if (raiz == NULL)
        return;
    
    //percorre a subárvore esquerda
    percurso_pos_ordem(raiz->esquerda);
    
    //percorre a subárvore direita
    percurso_pos_ordem(raiz->direita);
    
    //visita o nó atual
    printf("%d ", raiz->dado);
}

void obter_percurso_pos_ordem(int* pre_ordem, int* em_ordem, int tamanho) {
    int indice = 0;
    No* raiz = reconstruir_arvore(pre_ordem, em_ordem, 0, tamanho - 1, &indice);
    
    printf("Percurso pos-ordem: ");
    percurso_pos_ordem(raiz);
    printf("\n");
    
    destruir_arvore(&raiz);
}

void percurso_em_ordem(No *raiz) {
    if (raiz == NULL)
        return;
    percurso_em_ordem(raiz->esquerda); //percorre a subárvore esquerda
    printf("%d ", raiz->dado); //imprime o nó atual
    percurso_em_ordem(raiz->direita); //percorre a subárvore direita
}

int calcular_fator_balanceamento(No *raiz) {//deve ser árvore AVL
    if (raiz == NULL)
        return 0;
    return altura(raiz->esquerda) - altura(raiz->direita);
}