#include "llrbt.h"

#define PRETO 0
#define VERMELHO 1

typedef struct no_llrbt NO_LLRBT;
struct no_llrbt{
    NO_LLRBT *esq;
    NO_LLRBT *dir;
    bool cor;
    int chave;
};

struct _llrbt{
    NO_LLRBT *raiz;
};

LLRBT *llrbt_criar(void){
    LLRBT *T = (LLRBT *) malloc(1*sizeof(LLRBT *));
    if(!T){
        return NULL;
    }
    T->raiz = NULL; 
    return T;
}

bool no_llrbt_pertence(NO_LLRBT *no, int elemento){
    if(!no){
        return false;
    }
    if(elemento == no->chave){
        return true;
    }
    if(elemento < no->chave){
        return no_llrbt_pertence(no->esq, elemento);
    }
    else{
        return no_llrbt_pertence(no->dir, elemento);
    }
}

bool llrbt_pertence(LLRBT *T, int elemento){
    return no_llrbt_pertence(T->raiz, elemento);
}

bool no_llrbt_inserir(NO_LLRBT *no, int elemnto){
    if()
}

bool llrbt_inserir(LLRBT *T, int elemento){
    return no_llrbt_pertence(T->raiz, elemento);
}

bool llrbt_remover(LLRBT *T, int elemento){

}

void llrbt_apagar(LLRBT **T){

}

void llrbt_imprimir(LLRBT *T){

}

LLRBT *llrbt_uniao(LLRBT *T, LLRBT *U){

}

LLRBT *llrbt_interseccao(LLRBT *T, LLRBT *U){

}