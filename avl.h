//Código feito por: João Pedro Daleffe Dias e Rodrigo Silva de Almeida

#ifndef _AVL_H
#define _AVL_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>

    typedef struct _avl AVL;

    //função que cria uma árvore AVL
    AVL *avl_criar(void);

    //função que verifica se um elemento está na árvore
    bool avl_pertence(AVL *T, int elemento);

    //função que insere o elemento na árvore
    bool avl_inserir(AVL *T, int elemento);

    //função que remove um elemento da árvore
    bool avl_remover(AVL *T, int elemento);

    //função que apaga a árvore toda
    void avl_apagar(AVL **T);

    //função que imprime a árvore toda
    void avl_imprimir(AVL *T);

    //função que recebe duas árvores e cria uma terceira baseada na união delas
    AVL *avl_uniao(AVL *T, AVL *U);

    //função que recebe duas árvores e cria uma terceira baseada na intesecção delas
    AVL *avl_interseccao(AVL *T, AVL *U);


#endif