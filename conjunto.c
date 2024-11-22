#include "conjunto.h"
#include "avl.h"
#include "noavl.h"

struct set {
    int tipo;
    AVL *SetAVL;
    //RB *SetRBN;
}

SET *set_criar(int tipo){
    SET *conjunto = (SET *) malloc(sizeof(SET));
    if(tipo == 0){
        conjunto->tipo = 0;
        conjunto->SetAVL = avl_criar();
        //conjunto->SetRBN = NULL;
    }
    else if(tipo == 1){
        conjunto->tipo = 1;
        conjunto->SetAVL = NULL;
        //conjutno->SetRBN = rbn_criar();
    }
    return(conjunto);
}

bool set_pertence(SET *A, int elemento, int tipo){
    if(tipo == 0){
        return(avl_pertence(A->SetAVL, elemento));
    }
    //else if(tipo == 1){
    //    return(rbn_pertence(A->SetRBN, elemento));
    //}
}

bool set_inserir(SET *s, int elemento, int tipo){
    if(tipo == 0){
        return(avl_inserir(s->SetAVL, elemento));
    }
    //else if(tipo == 1){
    //    return(rbn_inserir(s->SetRBN, elemento));
    //}
}

bool set_remover(SET *s, int elemento, int tipo){
    if(tipo == 0){
        return(avl_remover(s->SetAVL, elemento));
    }
    //else if(tipo == 1){
    //    return(rbn_remover(s->SetRBN, elemento));
    //}
}

void set_apagar(SET **s, int tipo){
    if(tipo == 0){
        avl_apagar(&s->SetAVL);
        return;
    }
    //else if(tipo == 1){
    //    rbn_apagar(&s->SetRBN);
    //    return;
    //}
}

void set_imprimir(SET *s, int tipo){
    if(tipo == 0){
        avl_imprimir(s->SetAVL);
        return;
    }
    //else if(tipo == 1){
    //    rbn_imprimir(s->SetRBN);
    //    return;
    //}
}

SET *set_uniao(SET *A, SET *B, int tipo){
    SET *uniao = set_criar(tipo);
    if(tipo == 0){
        uniao->SetAVL = avl_uniao(A->SetAVL, B->SetAVL);
    }
    //else if(tipo == 1){
    //    uniao->SetRBN = rbn_criar(A->SetRBN, B->SetRBN);
    //}
    return(uniao);
}

SET *set_interseccao(SET *A, SET *B, int tipo){
    SET *interseccao = set_criar(tipo);
    if(tipo == 0){
        interseccao->SetAVL = avl_interseccao(A->SetAVL, B->SetAVL);
    }
    //else if(tipo == 1){
    //    interseccao->SetRBN = rbn_interseccao(A->SetRBN, B->SetRBN);
    //}
    return(interseccao);
}