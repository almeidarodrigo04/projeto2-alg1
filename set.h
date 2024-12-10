#ifndef _SET_H
#define _SET_H

  //São as interfaces dos TADs que serão utilizados para armazenar os Dados do Set.
  #include "avl.h"       
  #include "llrbt.h" 

 typedef struct set SET;

  /*ATENÇÃO: o parâmetro "tipo" define a estrutura de dados que será utilizada*/

  //função que cria um conjunto
  SET *set_criar(int tipo);

  //Função que verifica se um elemento está no conjunto
  bool set_pertence(SET *A, int elemento, int tipo);

  //função que insere o elemento no conjunto
  bool set_inserir (SET *s, int elemento, int tipo);

  //função que remove um elemento do conjunto
  bool set_remover(SET *s, int elemento, int tipo);

  //função que apaga o conjunto todo
  void set_apagar(SET **s, int tipo);

  //função que imprime a árvore toda
  void set_imprimir(SET *s, int tipo);

  //função que que recebe dois conjuntos e cria um terceiro baseado na união deles
  SET *set_uniao(SET *A, SET *B, int tipo);

  //função que que recebe dois conjuntos e cria um terceiro baseada na intersecção deles
  SET *set_interseccao(SET *A, SET *B, int tipo);
  
#endif