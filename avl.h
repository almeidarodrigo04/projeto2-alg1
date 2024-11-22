#ifndef _AVL_H
#define _AVL_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include "noavl.h"

    typedef struct _avl AVL;

    AVL *avl_criar(void);
    bool avl_pertence(AVL *T, int elemento);
    bool avl_inserir(AVL *T, int elemento);
    bool avl_remover(AVL *T, int elemento);
    void avl_apagar(AVL **T);
    void avl_imprimir(AVL *T);
    AVL *avl_uniao(AVL *T, AVL *U);
    AVL *avl_interseccao(AVl *T, AVL* U);


#endif