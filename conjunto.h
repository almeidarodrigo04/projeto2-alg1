#ifndef _SET_H
#define _SET_H

  #include "avl.h" //São as interfaces dos TADs que serão 
  #include "ED2.h" //utilizados para armazenar os Dados do Set.
                   //i.e, Set é um TAD que usa outros TADs. 
                   //Pode trocar os nomes! ;-)

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