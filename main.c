#include "set.h"
#include <stdio.h>

int main(void){
    SET *A, *B, *C;
    C = NULL;
    int n_a, n_b, elemento;
    int operacao;
    int tipo;


    scanf("%d", &tipo);
    /*Quando tipo == 0, usamos uma árvore AVL
      Quando tipo == 1, usamos uma árvore LLRBT*/

    A = set_criar(tipo);
    B = set_criar(tipo);
    /*Cria dois conjuntos do tipo definido*/
    
    scanf("%d %d", &n_a, &n_b);
    /*Leitura da quantidade de elemento em cada conjunto*/

    for(int i=0; i<n_a; i++){
        scanf("%d",&elemento);
        set_inserir(A, elemento, tipo);
        /*preenchendo com os elementos do conjunto A*/
    }

    for(int i=0; i<n_b; i++){
        scanf("%d",&elemento);
        set_inserir(B, elemento, tipo);
        /*preenchendo com os elementos do conjunto B*/
    }

    scanf("%d", &operacao);
    /*Leitura da operação*/

    switch(operacao){
        case 1:{/*pertence*/
            scanf("%d", &elemento);
            if(set_pertence(A, elemento, tipo)){
                printf("Pertence.\n");
            }
            else{
                printf("Nao pertence.\n");
            }
            break;
        }
        case 2:{/*união*/
            C = set_uniao(A, B, tipo);
            set_imprimir(C, tipo);
            break;
        }
        case 3:{/*intersecção*/
            C = set_interseccao(A, B, tipo);
            set_imprimir(C, tipo);
            break;
        }
        case 4:{/*remoção*/
            scanf("%d", &elemento);
            set_remover(A, elemento, tipo);
            set_imprimir(A, tipo);
            break;
        }
    }

    set_apagar(&A, tipo);
    set_apagar(&B, tipo);
    if(C){
        set_apagar(&C, tipo);
    }
    
    return 0;
}