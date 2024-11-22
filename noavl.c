#include "noavl.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#define max(a, b) (a>b)?a:b

struct _noavl {
    int chave;
    int FB;
    int altura;
    NOAVL *esquerdo;
    NOAVL *direito;
}

NOAVL *no_criar(int chave){
    NOAVL *NO = (NOAVL*) malloc(sizeof(NOAVL));
    NO->chave = chave;
    NO->FB = 0;
    NO->altura = 1;
    NO->esquerdo = NULL;
    NO->direito = NULL;
    return(NO);
}

int altura(NOAVL *atual){
    if(atual == NULL){
        return(-1);
    }
    return(atual->altura);
}

void atualizar_altura(NOAVL *atual){
    int alt_dir = altura(atual->direito);
    int alt_esq = altura(atual->esquerdo);
    atual->altura = 1 + max(alt_esq, alt_dir);
    return;
}

void apagar_nos(NOAVL* raiz){
    if(raiz != NULL){
        apagar_nos(raiz->esquerdo);
        apagar_nos(raiz->direito);
        free(raiz);
    }
    return;
}

NOAVL *rotacao_direita(NOAVL *no1){
    NOAVL *no2 = no1->esquerdo;
    no1->esquerdo = no2->direito;
    no2->direito = no1;

    no1->FB = 0;
    no2->FB = 0;

    atualizar_altura(no1);
    atualizar_altura(no2);

    return(no2);
}

NOAVL *rotacao_esquerda(NOAVL *no1){
    NOAVL *no2 = no1->direito;
    no1->direito = no2->esquerdo;
    no2->esquerdo = no1;

    no1->FB = 0;
    no2->FB = 0;

    atualizar_altura(no1);
    atualizar_altura(no2);

    return(no2);
}

NOAVL *rotacao_esquerda_direita(NOAVL *no1){
    no1->esquerdo = rotacao_esquerda(no1->esquerdo);
    return(rotacao_direita(no1));
}

NOAVL *rotacao_direita_esquerda(NOAVL *no1){
    no1->direito = rotacao_direita(no1->direito);
    return(rotacao_esquerda(no1));
}

int no_balanceamento(NOAVL *raiz){
    int alt_esq = raiz->esquerdo->altura;
    int alt_dir = raiz->direito->altura;
    int FB = alt_esq - alt_dir;
    raiz->FB = FB;
    return(FB);
}

NOAVL *no_avl_inserir(NOAVL *atual, NOAVL *novo_no){
    if(atual == NULL){
        if(atual = novo_no){
            return(atual);
        }
        return;
    }

    else if(novo_no->chave == atual->chave){
        return;
    }

    else if(novo_no->chave < atual->chave){
        if(!no_avl_inserir(atual->esquerdo, novo_no)){
            return;
        }
    }

    else if(novo_no->chave > atual->chave){
        if(!no_avl_inserir(atual->direito, novo_no)){
            return;
        }
    }

    atualizar_altura(atual);
    no_balanceamento(atual);

    if(atual->FB == 2){
        if(atual->direito->FB <= 0){
            atual = rotacao_esquerda(atual);
        }
        else{
            atual = rotacao_direita_esquerda(atual);
        }
    }
    else if(atual->FB == -2){
        if(atual->esquerdo->FB >= 0){
            atual = rotacao_direita(atual);
        }
        else{
            atual = rotacao_esquerda_direita(atual);
        }
    }
    return(atual);
}

void no_remover(NOAVL *no_removido){
    free(no_removido);
    no_removido = NULL;
    return;
}

void trocar_max_esq(NOAVL *troca, NOAVL *raiz, NOAVL *ant){
    if(troca->dir != NULL){
        troca_max_esq(troca->direito, raiz, troca);
        return;
    }

    if(raiz == ant){
        ant->esquerdo = troca->esquerdo;
    }
    else{
        ant->direito = troca->esquerdo;
    }

    raiz->chave = troca->chave
    no_remover(troca);
    return;
}

NOAVL *no_avl_remover(NOAVL *atual, int chave){
    if(atual == NULL){
        return(atual);
    }

    else if(chave == atual->chave){
        if(atual->esquerdo == NULL || atual->direito == NULL){
            NOAVL *prov = atual;
            if(atual->esquerdo == NULL){
                atual = atual->direito;
            }
            else{
                atual = atual->esquerdo;
            }
            no_remover(prov);
        }

        else{
            trocar_max_esq(atual->esquerdo, atual, atual);
        }
    }

    else if(chave < atual->chave){
        no_avl_remover(atual->esquerdo, chave);
    }
    else if(chave > atual->chave){
        no_avl_remover(atual->direito, chave);
    }
    if(atual != NULL){
        atualizar_altura(atual);
        no_balanceamento(atual);
        if(atual->FB == 2){
            if(atual->esquerdo->FB >= 0){
                atual = rotacao_direita(atual);
            }
            else{
                atual = rotacao_esquerda_direita(atual);
            }
        }
        else if(atual->FB == -2){
            if(atual->direito->FB <= 0){
                atual = rotacao_esquerda(atual);
            }
            else{
                atual = rotacao_direita_esquerda(atual);
            }
        }
    }
    return(atual);
}

void printar_nivel(NOAVL *raiz, int nivel, int espaco){
    if(raiz == NULL){
        return;
    }

    if(nivel == 1){
        printf("%*d ", espaco, raiz->chave);
    }

    else if(nivel > 1){
        printar_nivel(raiz->esquerdo, nivel - 1, int espaco);
        printar_nivel(raiz->direito, nivel - 1, int espaco);
    }
}

void no_imprimir(NOAVL *raiz, int altura_max){
    if(raiz == NULL){
        printf(" ");
        return;
    }
    int espaco = (1 << altura_max) - 1;

    for(int i = 1; i <= altura_max; i++){
        printar_nivel(raiz, i, espaco);
        espaco = espaco / 2;
        printf("\n");
    }
}

bool no_avl_buscar(NOAVL *atual, int chave){
    if(atual == NULL){
        return(false);
    }

    else if(atual->chave == chave){
        return(true);
    }

    else if(chave < atual->chave){
        if(no_avl_buscar(atual->esquerdo, chave)){
            return(true);
        }
        else{
            return(false);
        }
    }

    else if(chave > atual->chave){
        if(no_avl_buscar(atual->direito, chave)){
            return(true);
        }
        else{
            return(false);
        }
    }

    else{
        return(false);
    }
}

NOAVL *no_copiar(NOAVL *original){
    NOAVL *novo = no_criar(original->chave);
    return(novo);
}