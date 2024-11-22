#include "avl.h"
#include "noavl.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct _avl {
    int tamanho;
    int altura_max;
    NOAVL *raiz;
}

AVL *avl_criar(void){
    AVL *T = (AVL*) malloc(sizeof(AVL));
    T->tamanho = 0;
    T->altura_max = 0;
    T->raiz = NULL;
    return(T);
}

bool avl_pertence(AVL *T, int elemento){
    NOAVL *atual = T->raiz;
    if(no_avl_buscar(atual, elemento)){
        return(true);
    }
    else{
        return(false);
    }
}

bool avl_inserir(AVL *T, int elemento){
    if(T == NULL){
        return(false);
    }
    NOAVL *atual = T->raiz;
    NOAVL *novo_no = no_criar(elemento);
    if(no_avl_inserir(atual, novo_no)){
        T->tamanho += 1;
        T->altura_max = T->raiz->altura;
        return(true);
    }

    else{
        return(false);
    }
}

bool avl_remover(AVL *T, int elemento){
    if(T = NULL){
        return(false);
    }

    NOAVL *atual = T->raiz;
    if(no_avl_remover(atual, elemento)){
        T->tamanho -= 1;
        T->altura_max = T->raiz->altura;
        return(true);
    }
    else{
        return(false);
    }
    
}

void avl_apagar(AVL **T){
    AVL *Tree = *T;
    if(Tree == NULL){
        return;
    }
    NOAVL *raiz = Tree->raiz;
    apagar_nos(raiz);
    free(Tree);
    return;
}

void avl_imprimir(AVL *T){
    if(T == NULL){
        return;
    }
    no_imprimir(T->raiz, T->altura_max);
    return;
}

NOAVL *nos_unir(AVL *uniao, NOAVL *raiz){
    if(raiz != NULL){
        avl_inserir(uniao, raiz->chave);
        nos_unir(uniao, raiz->esquerdo);
        nos_unir(uniao, raiz->direito);
    }
    return(uniao);
}

NOAVL *nos_interseccao(AVL *intersec, NOAVL *raiz1, NOAVL *raiz2){
    if(raiz1 != NULL){
        if(no_pertence(raiz2, raiz1->chave)){
            avl_inserir(intersec, raiz1->chave);
        }
        nos_interseccao(intersec, raiz1->esquerdo, raiz2);
        nos_interseccao(intersec, raiz1->direito, raiz2);
    }
    return(intersec);
}

AVL *avl_uniao(AVL *T, AVL *U){
    if(U == NULL){
        return(T);
    }
    if(T == NULL){
        return(U);
    }
    AVL *V = avl_criar();
    
    NOAVL *atualT = T->raiz;
    NAOVL *atualU = U->raiz;
    V = nos_unir(V, T->raiz);
    V = nos_unir(V, U->raiz);
    return(V);
}

AVL *avl_interseccao(AVL *T, AVL *U){
    if(T == NULL || U == NULL){
        return(NULL);
    }
    AVL *V = avl_criar();
    V = nos_interseccao(V, T->raiz, U->raiz);
    return(V);
}