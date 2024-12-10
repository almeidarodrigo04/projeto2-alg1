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

NO_LLRBT *rotacao_esquerda(NO_LLRBT *A){
    NO_LLRBT *B = A->dir;
    A->dir = B->esq;
    B->esq = A;
    B->cor = A->cor;
    A->cor = VERMELHO;
    return B;
}

NO_LLRBT *rotacao_direita(NO_LLRBT *A){
    NO_LLRBT *B = A->esq;
    A->esq = B->dir;
    B->dir = A;
    B->cor = A->cor;
    A->cor = VERMELHO;
    return B;
}

void inverte_cor(NO_LLRBT *no){
    if(no){
        no->cor = !no->cor;
    }
    if(no->esq){
        no->esq->cor = !no->esq->cor;
    }
    if(no->dir){
        no->dir->cor = !no->dir->cor;
    }
}

bool vermelho(NO_LLRBT *no){
    if(no){
        return no->cor == VERMELHO;
    }
    return false;
}

void restaurar(NO_LLRBT *no){
    if(!vermelho(no->esq) && vermelho(no->dir)){
        no = rotacao_esquerda(no);
    }
    if(vermelho(no->esq)&& vermelho(no->esq->esq)){
        no = rotacao_direita(no);
    }
    if(vermelho(no->esq) && vermelho(no->dir)){
        inverte_cor(no);
    }
}

NO_LLRBT *no_llrbt_inserir(NO_LLRBT *no, int elemento){
    if(!no){
        no = (NO_LLRBT *) malloc(1*sizeof(NO_LLRBT));
        if(!no){
            no->chave = elemento;
            no->esq = NULL;
            no->dir = NULL;
            no->cor = VERMELHO;
        }
    }
    if(elemento < no->chave){
        no->esq = no_llrbt_inserir(no->esq, elemento);
    }
    if(elemento > no->chave){
        no->dir = no_llrbt_inserir(no->dir, elemento);
    }
    restaurar(no);

    return no;
}

bool llrbt_inserir(LLRBT *T, int elemento){
    T->raiz = no_llrbt_inserir(T->raiz, elemento);
    if(T->raiz){
        return true;
    }
    return false;
}

NO_LLRBT *propagar_vermelho_esquerda(NO_LLRBT *no){
    if(!vermelho(no->esq) && !vermelho(no->esq->esq)){
        inverte_cor(no);
        if(vermelho(no->dir->esq)){
            no->dir = rotacao_direita(no->dir);
            no = rotacao_esquerda(no);
            inverte_cor(no);
        }
    }
    return no;
}

NO_LLRBT *propagar_vermelho_direita(NO_LLRBT *no){
    if(vermelho(no->esq)){
        no = rotacao_direita(no);
    }
    if(!vermelho(no->dir) && !vermelho(no->dir->esq)){
        inverte_cor(no);
        if(vermelho(no->esq->esq)){
            no = rotacao_direita(no);
            inverte_cor(no);
        }
    }
    return no;
}

void troca_max_esq(NO_LLRBT *troca, NO_LLRBT *raiz, NO_LLRBT *ant){
    if(troca->dir){
        troca_max_esq(troca->dir, raiz, troca);
        return;
    }
    if(raiz == ant){
        ant->esq = troca->esq;
    }
    else{
        ant->dir = troca->dir;
    }
    free(troca);
    troca = NULL;
}

NO_LLRBT *no_llrbt_remover(NO_LLRBT *no, int elemento){
    if(!no){
        return NULL;
    }
    if(no->chave == elemento){
        if(no->esq == NULL || no->dir == NULL){
            NO_LLRBT *aux = no;
            no = no->esq != NULL ? no->esq : no->dir;
            free(aux);
            aux = NULL;
        }
        else{
            no = propagar_vermelho_direita(no);
            troca_max_esq(no->esq, no, no);
        }
    }
    if(no->chave < elemento){
        no = propagar_vermelho_esquerda(no);
        no->esq = no_llrbt_remover(no->esq, elemento);
    }
    else{
        no = propagar_vermelho_direita(no);
        no->dir = no_llrbt_remover(no->dir, elemento);
    }
    if(no){
        restaurar(no);
    }
    return no;
}

bool llrbt_remover(LLRBT *T, int elemento){
    T->raiz = no_llrbt_remover(T->raiz, elemento);
    if(T->raiz){
        return true;
    }
    return false;
}

void no_llrbt_apagar(NO_LLRBT **no){
    if(!no){
        return;
    }
    no_llrbt_apagar(&(*no)->esq);
    no_llrbt_apagar(&(*no)->dir);
    free(*no);
    *no = NULL;
}

void llrbt_apagar(LLRBT **T){
    no_llrbt_apagar(&(*T)->raiz);
}

void no_llrbt_imprimir(NO_LLRBT *no){
    if(!no){
        return;
    }
    no_llrbt_imprimir(no->esq);
    printf("%d, ", no->chave);
    no_llrbt_imprimir(no->dir);
}

void llrbt_imprimir(LLRBT *T){
    no_llrbt_imprimir(T->raiz);
}

void no_llrbt_unir(LLRBT *uniao, NO_LLRBT *no){
    if(no){
        llrbt_inserir(uniao, no->chave);
        no_llrbt_unir(uniao, no->esq);
        no_llrbt_unir(uniao, no->dir);
    }
}

LLRBT *llrbt_uniao(LLRBT *T, LLRBT *U){
    LLRBT *V = llrbt_criar();
    no_llrbt_unir(V, T->raiz);
    no_llrbt_unir(V, U->raiz);
    return V;
}

void no_llrbt_interseccao(LLRBT *interseccao, LLRBT *T, NO_LLRBT *no_U){
    if(no_U){
        if(llrbt_pertence(T, no_U->chave)){
            llrbt_inserir(interseccao, no_U->chave);
        }
        no_llrbt_interseccao(interseccao, T, no_U->esq);
        no_llrbt_interseccao(interseccao, T, no_U->dir);
    }
}

LLRBT *llrbt_interseccao(LLRBT *T, LLRBT *U){
    LLRBT *V = llrbt_criar();
    no_llrbt_interseccao(V, T, U->raiz);
    return V;
}