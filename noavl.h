#ifndef _NOAVL_H
#define _NOAVL_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>

    typedef struct _noavl NOAVL;

    NOAVL *no_criar(int chave);
    bool no_avl_buscar(NOAVL *atual, int chave);
    int no_balanceamento(NOAVL *atual);
    bool no_avl_inserir(NOAVL *atual, NOAVL *novo_no);
    bool no_avl_remover(NOAVL *atual, int chave);
    void printar_nivel(NOAVL *raiz, int nivel, int espaco);
    void no_imprimir(NOAVL *raiz, int altura_max);

#endif