#ifndef _SET_H
#define _SET_H

  //São as interfaces dos TADs que serão utilizados para armazenar os Dados do Set.
  #include "avl.h"       
  #include "llrbt.h" 

 typedef struct set SET;

  SET *set_criar(int tipo);
  bool set_pertence(SET *A, int elemento, int tipo);
  bool set_inserir (SET *s, int elemento, int tipo);
  bool set_remover(SET *s, int elemento, int tipo);
  void set_apagar(SET **s, int tipo);
  void set_imprimir(SET *s, int tipo);
  SET *set_uniao(SET *A, SET *B, int tipo);
  SET *set_interseccao(SET *A, SET *B, int tipo);
  
#endif