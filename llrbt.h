#ifndef LLRBT_H
#define LLRBT_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>

    typedef struct _llrbt LLRBT;

    LLRBT *llrbt_criar(void);
    bool llrbt_pertence(LLRBT *T, int elemento);
    bool llrbt_inserir(LLRBT *T, int elemento);
    bool llrbt_remover(LLRBT *T, int elemento);
    void llrbt_apagar(LLRBT **T);
    void llrbt_imprimir(LLRBT *T);
    LLRBT *llrbt_uniao(LLRBT *T, LLRBT *U);
    LLRBT *llrbt_interseccao(LLRBT *T, LLRBT *U);


#endif