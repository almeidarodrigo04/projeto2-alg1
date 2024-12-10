#ifndef LLRBT_H
#define LLRBT_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>

    typedef struct _llrbt LLRBT;

    //função que cria uma árvore LLRBT
    LLRBT *llrbt_criar(void);
    
    //Função que verifica se um elemento está na árvore
    bool llrbt_pertence(LLRBT *T, int elemento);

    //função que insere o elemento na árvore
    bool llrbt_inserir(LLRBT *T, int elemento);

    //função que remove um elemento da arvore
    bool llrbt_remover(LLRBT *T, int elemento);

    //função que apaga a árvore toda
    void llrbt_apagar(LLRBT **T);

    //função que imprime a árvore toda
    void llrbt_imprimir(LLRBT *T);

    //função que que recebe duas árvores e cria uma terceira baseada na união delas
    LLRBT *llrbt_uniao(LLRBT *T, LLRBT *U);

    //função que que recebe duas árvores e cria uma terceira baseada na intersecção delas
    LLRBT *llrbt_interseccao(LLRBT *T, LLRBT *U);


#endif