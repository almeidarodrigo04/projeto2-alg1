//Código feito por: João Pedro Daleffe Dias e Rodrigo Silva de Almeida

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "avl.h"

#define max(a, b) ((a>b)?a:b)

typedef struct _noavl NOAVL;
//Struct para os nós da árvore AVL
struct _noavl {
    int chave;
    int FB;
    int altura;
    NOAVL *esquerdo;
    NOAVL *direito;
};

//struct da arvore AVL
struct _avl {
    NOAVL *raiz;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*FUNÇÕES DEDICADAS À OPERAÇÃO DE CRIAR*/

//Função para Criar uma Árvore AVL
AVL *avl_criar(void){
    AVL *arvore = (AVL *) malloc(sizeof(AVL));
    if(arvore != NULL){
        arvore->raiz = NULL;
    }

    return(arvore);
}

//Função para Criar um Nó AVL
NOAVL *no_avl_criar(int chave){
    NOAVL *no = (NOAVL *) malloc(sizeof(NOAVL));
    if(no != NULL){
        no->FB = 0;
        no->altura = 1;
        no->direito = NULL;
        no->esquerdo = NULL;
        no->chave = chave;
    }
    return no;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*FUNÇÕES DEDICADAS À OPERAÇÃO DE PERTENCIMENTO*/

//função que busca por um nó com a chave inserida
bool no_avl_buscar(NOAVL *atual, int chave){
    //se o nó atual é vazio, retorna falso
    if(atual == NULL){
        return(false);
    }

    //se o nó atual for o buscado, retorna verdadeiro
    else if(atual->chave == chave){
        return(true);
    }
    //se a chave for menor que a do nó atual, segue a busca para o nó esquerdo
    else if(chave < atual->chave){
        if(no_avl_buscar(atual->esquerdo, chave)){
            return(true);
        }
        else{
            return(false);
        }
    }
    //se a chave for maior que a do nó atual, segue a busca para o nó direito
    else if(chave > atual->chave){
        if(no_avl_buscar(atual->direito, chave)){
            return(true);
        }
        else{
            return(false);
        }
    }
    //se não for nenhum dos casos, retorna falso
    else{
        return(false);
    }
}

//função auxiliar para verificar se um valor pertence à árvore a partir de um nó
//utiliza da função buscar. Se encontrar retorna verdadeiro, se não retorna falso
bool no_avl_pertence(NOAVL *raiz, int elemento){
    if(no_avl_buscar(raiz, elemento)){
        return(true);
    }
    else{
        return(false);
    }
}

//função para verificar se um valor pertence à árvore. Utiliza da função auxiliar de pertencimento
bool avl_pertence(AVL*T, int elemento){
    return(no_avl_pertence(T->raiz, elemento));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*FUNÇÕES DEDICADAS AO REBALANCEAMENTO DA ÁRVORE*/
/*Obs: são usadas na inserção e remoção*/

//Função para obter a altura que um nó guarda
int altura(NOAVL *raiz){
    if(raiz == NULL){
        return 0;
    }
    else{
        return(raiz->altura);
    }
}

//função para atualizar a altura de um nó recursivamente
void atualizar_altura(NOAVL *atual){
    int alt_dir = altura(atual->direito);
    int alt_esq = altura(atual->esquerdo);
    atual->altura = 1 + max(alt_esq, alt_dir);
    return;
}

//função para balancear um nó
//verifica a diferença de altura dos filhos do nó
int no_balanceamento(NOAVL *raiz){
    if(raiz == NULL){
        return(0);
    }
    int alt_esq = altura(raiz->esquerdo);
    int alt_dir = altura(raiz->direito);
    int FB = alt_esq - alt_dir;
    raiz->FB = FB;
    return(FB);
}

//função para rotação à direita
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

//função para rotação à esquerda
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

//função para rotação à esquerda e depois à direita
NOAVL *rotacao_esquerda_direita(NOAVL *no1){
    no1->esquerdo = rotacao_esquerda(no1->esquerdo);
    return(rotacao_direita(no1));
}

//função para rotação à direita e depois à esquerda
NOAVL *rotacao_direita_esquerda(NOAVL *no1){
    no1->direito = rotacao_direita(no1->direito);
    return(rotacao_esquerda(no1));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*FUNÇÕES DEDICADAS À OPERAÇÃO DE INSERÇÃO*/

//função para inserir a partir de um nó avl
//função auxiliar para inserir recursivamente
NOAVL *no_avl_inserir(NOAVL *raiz, NOAVL *novo_no){
    //se o nó é vazio, insere nele
    if(raiz == NULL){
        raiz = novo_no;
    }
    //se o nó é menor, a inserção vai para o nó esquerdo
    else if (novo_no->chave < raiz->chave){
        raiz->esquerdo = no_avl_inserir(raiz->esquerdo, novo_no);
    }
    //se o nó é maior, a inserção vai para o nó direito
    else if (novo_no->chave > raiz->chave){
        raiz->direito = no_avl_inserir(raiz->direito, novo_no);
    }
    //após inserir, atualiza a altura e o balanceamento dos nós
    atualizar_altura(raiz);
    raiz->FB = no_balanceamento(raiz);

    //se o balanceamento for -2 ou 2, faz uma das rotações especificadas anteriormente para corrigir o desbalanço
    if(raiz->FB == -2){
        if(raiz->direito->FB <= 0){
            raiz = rotacao_esquerda(raiz);
        }
        else{
            raiz = rotacao_direita_esquerda(raiz);
        }
    }

    if(raiz->FB == 2){
        if(raiz->esquerdo->FB >= 0){
            raiz = rotacao_direita(raiz);
        }
        else{
            raiz = rotacao_esquerda_direita(raiz);
        }
    }

    //retorna a raiz para que o nó anterior se conecte na subárvore corrigida
    return(raiz);
}

//função para inserir um dado em uma árvore AVL
//cria um novo nó e insere ele na árvore usando a função auxiliar para inserir a partir de um nó.
bool avl_inserir(AVL *T, int chave){
    NOAVL *novo_no = no_avl_criar(chave);
    return((T->raiz = no_avl_inserir(T->raiz, novo_no)) != NULL);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*FUNÇÕES DEDICADAS À OPERAÇÃO DE REMOÇÃO*/

//função para deletar um nó
//função auxiliar que libera um nó e o coloca como "NULL"
void no_deletar(NOAVL *raiz){
    if(raiz == NULL){
        return;
    }
    else{
        free(raiz);
        raiz = NULL;
    }
}

//função para trocar o valor máximo esquerdo
//encontra o maior filho direito de uma subárvore esquerda e substitui o nó raiz por ele
//para poder rebalancear no caso da remoção de um nó com dois filhos
void troca_max_esq (NOAVL *troca, NOAVL *raiz, NOAVL *anterior){
    //se o nó direito não é nulo, avança na recursão para o próximo nó direito
    if(troca->direito != NULL){
        troca_max_esq(troca->direito, raiz, troca);
        return;
    }
    //caso não haja mais direito, verifica se a raíz é o nó anterior,
    //se for, o filho esquerdo da raíz passa a ser o filho esquerdo do nó mais à direita
    if(raiz == anterior){
        anterior->esquerdo = troca->esquerdo;
    }
    //se não for, o filho direito do nó anterior passa a ser o filho esquerdo do nó mais à direita
    else{
        anterior->direito = troca->esquerdo;
    }
    //troca a raíz pelo nó máximo mais à direita e deleta o nó duplicado
    raiz->chave = troca->chave;
    no_deletar(troca);
}

//função para remover um nó a partir de uma raiz e uma chave
//auxiliar para remover recursivamente um nó
NOAVL *no_avl_remover(NOAVL *raiz, int chave){
    NOAVL *prov;
    //se o nó é nulo retorna nulo
    if(raiz == NULL){
        return(NULL);
    }

    //se achou um nó com a chave
    else if (chave == raiz->chave){
        //caso pelo menos um dos filhos seja nulo, substitui o removido por um dos filhos
        if(raiz->esquerdo == NULL || raiz->direito == NULL){
            prov = raiz;

            if(raiz->esquerdo == NULL){
                raiz = raiz->direito;
            }

            else{
                raiz = raiz->esquerdo;
            }

            no_deletar(prov);
        }
        //caso o nó tenha dois filhos, realiza a troca pelo máximo da subárvore esquerda
        else{
            troca_max_esq(raiz->esquerdo, raiz, raiz);
        }
    }
    //se a chave for menor que o nó atual, a remoção avança para o nó esquerdo
    else if (chave < raiz->chave){
        raiz->esquerdo = no_avl_remover(raiz->esquerdo, chave);
    }
    //se a chave for maior que o nó atual, a remoção avança para o nó direito
    else if (chave > raiz->chave){
        raiz->direito = no_avl_remover(raiz->direito, chave);
    }
    //após a remoção, na volta da recursão cada nó é atualizado e rebalanceado propriamente
    if (raiz != NULL){
        atualizar_altura(raiz);
        raiz->FB = no_balanceamento(raiz);

        if (raiz->FB == 2){
            if(raiz->esquerdo->FB >= 0){
                raiz = rotacao_direita(raiz);
            }
            else{
                raiz = rotacao_esquerda_direita(raiz);
            }
        }
        if (raiz->FB == -2){
            if(raiz->direito->FB <= 0){
                raiz = rotacao_esquerda(raiz);
            }
            else{
                raiz = rotacao_direita_esquerda(raiz);
            }
        }
    }
    //retorna o nó atual para que os próximos nós conectar as subarvores rebalanceadas corretamente
    return(raiz);
}

//função que remove um nó de uma arvore buscando pela chave correspondente à buscada
bool avl_remover(AVL*T, int chave){
    return((T->raiz = no_avl_remover(T->raiz, chave)) != NULL);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*FUNÇÕES DEDICADAS À OPERAÇÃO DE APAGAR*/


//Função para Apagar todos os nós começando por uma raiz
void no_avl_apagar(NOAVL *raiz){
    if(raiz != NULL){
        no_avl_apagar(raiz->esquerdo);
        no_avl_apagar(raiz->direito);
        free(raiz);
    }
    else{
        return;
    }
}

//Função para apagar a Árvore AVL
void avl_apagar(AVL **T){
    AVL *Tree = *T;
    if(Tree == NULL){

    }
    no_avl_apagar(Tree->raiz);
    free(*T);
    *T = NULL;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*FUNÇÕES DEDICADAS À OPERAÇÃO DE IMPRIMIR*/

//função auxiliar que imprime a arvore a partir de um nó
//visita a árvore recursivamente, imprimindo o nó atual e seguindo primeiro para a subárvore esquerda e depois para a subárvore direita
void no_imprimir(NOAVL *raiz){
    if(raiz == NULL){
        return;
    }
    no_imprimir(raiz->esquerdo);
    printf("%d, ", raiz->chave);
    no_imprimir(raiz->direito);
}

//função que imprime a árvore
void avl_imprimir(AVL *T){
    if(T == NULL){
        return;
    }
    no_imprimir(T->raiz);
    printf("\n");
    return;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*FUNÇÕES DEDICADAS A OPERAÇÃO UNIÃO*/

//função auxiliar para unir árvores
//passa recursivamente por uma árvore e insere cada nó na nova árvore (uniao)
AVL *nos_unir(AVL *uniao, NOAVL *raiz){
    if(raiz != NULL){
        avl_inserir(uniao, raiz->chave);
        nos_unir(uniao, raiz->esquerdo);
        nos_unir(uniao, raiz->direito);
    }
    return(uniao);
}

//função para unir duas árvores
//Cria uma terceira árvore com o resultado da união, de forma que as árvores originais não são alteradas
AVL *avl_uniao(AVL *T, AVL *U){
    if(U == NULL || T == NULL){
        printf("Essa operação requer dois conjutnos existentes!\n");
        return(NULL);
    }

    AVL *V = avl_criar();

    NOAVL *atualT = T->raiz;
    NOAVL *atualU = U->raiz;
    V = nos_unir(V, T->raiz);
    V = nos_unir(V, U->raiz);
    return(V);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*FUNÇÕES DEDICADAS A OPERAÇÃO INTERSECÇÃO*/

//função auxiliar para intersecção de árvores
//passa recursivamente por cada nó de uma árvore, conferindo se está presente na outra
//Se estiver, o nó é inserido na nova árvore (intersec)
AVL *nos_interseccao(AVL *intersec, NOAVL *raiz1, NOAVL *raiz2){
    if(raiz1 != NULL){
        if(no_avl_pertence(raiz2, raiz1->chave)){
            avl_inserir(intersec, raiz1->chave);
        }
        nos_interseccao(intersec, raiz1->esquerdo, raiz2);
        nos_interseccao(intersec, raiz1->direito, raiz2);
    }
    return(intersec);
}

//função para intersecção de duas árvores
//Cria uma terceira árvore para guardar o resultado da intersecção, de forma que as árvores originais não são alteradas
AVL *avl_interseccao(AVL *T, AVL *U){
    if(T == NULL || U == NULL){
        printf("Essa operação requer dois conjutnos existentes!\n");
        return(NULL);
    }
    AVL *V = avl_criar();
    V = nos_interseccao(V, T->raiz, U->raiz);
    return(V);
}