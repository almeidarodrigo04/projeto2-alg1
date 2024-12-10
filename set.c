#include "set.h"

struct set{
    int tipo;
    AVL *SetAVL;
    LLRBT *SetRBN;
};

SET *set_criar(int tipo){
    SET *conjunto = (SET *) malloc(sizeof(SET));
    if(tipo == 0){
        conjunto->tipo = 0;
        conjunto->SetAVL = avl_criar();
        conjunto->SetRBN = NULL;
    }
    else if(tipo == 1){
        conjunto->tipo = 1;
        conjunto->SetRBN = NULL;
        conjunto->SetRBN = llrbt_criar();
    }
    return(conjunto);
}

bool set_pertence(SET *A, int elemento, int tipo){
    if(tipo == 0){
        return(avl_pertence(A->SetAVL, elemento));
    }
    else if(tipo == 1){
        return(llrbt_pertence(A->SetRBN, elemento));
    }
    return false;
}

bool set_inserir(SET *s, int elemento, int tipo){
    if(tipo == 0){
        return(avl_inserir(s->SetAVL, elemento));
    }
    else if(tipo == 1){
        return(llrbt_inserir(s->SetRBN, elemento));
    }
    return false;
}

bool set_remover(SET *s, int elemento, int tipo){
    if(tipo == 0){
        return(avl_remover(s->SetAVL, elemento));
    }
    else if(tipo == 1){
        return(llrbt_remover(s->SetRBN, elemento));
    }
    return false;
}

void set_apagar(SET **s, int tipo){
    if(tipo == 0){
        avl_apagar(&(*s)->SetAVL);
        return;
    }
    else if(tipo == 1){
        llrbt_apagar(&(*s)->SetRBN);
        return;
    }
}

void set_imprimir(SET *s, int tipo){
    if(tipo == 0){
        avl_imprimir(s->SetAVL);
        return;
    }
    else if(tipo == 1){
        llrbt_imprimir(s->SetRBN);
        return;
    }
}

SET *set_uniao(SET *A, SET *B, int tipo){
    SET *uniao = set_criar(tipo);
    if(tipo == 0){
        uniao->SetAVL = avl_uniao(A->SetAVL, B->SetAVL);
    }
    else if(tipo == 1){
        uniao->SetRBN = llrbt_uniao(A->SetRBN, B->SetRBN);
    }
    return(uniao);
}

SET *set_interseccao(SET *A, SET *B, int tipo){
    SET *interseccao = set_criar(tipo);
    if(tipo == 0){
        interseccao->SetAVL = avl_interseccao(A->SetAVL, B->SetAVL);
    }
    else if(tipo == 1){
        interseccao->SetRBN = llrbt_interseccao(A->SetRBN, B->SetRBN);
    }
    return(interseccao);
}