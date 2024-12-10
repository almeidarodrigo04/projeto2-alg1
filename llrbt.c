#include "llrbt.h"

#define PRETO 0
#define VERMELHO 1

typedef struct no_llrbt NO_LLRBT;
struct no_llrbt{
    NO_LLRBT *esq;
    NO_LLRBT *dir;
    bool cor;
    int chave;
};

struct _llrbt{
    NO_LLRBT *raiz;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*FUNÇão DEDICADA A CRIAR A ÁRVORE*/


LLRBT *llrbt_criar(void){
    LLRBT *T = (LLRBT *) malloc(1*sizeof(LLRBT *));
    if(!T){
        return NULL;
    }
    T->raiz = NULL; 
    return T;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*FUNÇÕES DEDICADAS A VARIFICAR A EXISTENCIA DE UM ELEMENTO NA ARVORE*/

//olha o nó (caso nã seja nulo) e, recursivamente, se move para direita ou esquerda até encontrar o nó desejado
bool no_llrbt_pertence(NO_LLRBT *no, int elemento){
    if(!no){
        return false;//nesse caso, já fomos até o "fim" da árvore e não encontramos o elemento
    }
    if(elemento == no->chave){
        return true;//se achamos, retorna verdadeiro
    }
    if(elemento < no->chave){
        return no_llrbt_pertence(no->esq, elemento);//se o elemento que buscamos é menor, vai para esquerda
    }
    else{
        return no_llrbt_pertence(no->dir, elemento);//se o elemento que buscamos é maior, vai para direira
    }
}

//função que chama a função recursiva
bool llrbt_pertence(LLRBT *T, int elemento){
    return no_llrbt_pertence(T->raiz, elemento);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*FUNÇÕES DEDICADAS A INSERÇÃO DE UM ELEMNTO NA ÁRVORE*/

//função da rotção esquerda
NO_LLRBT *rotacao_esquerda(NO_LLRBT *A){
    NO_LLRBT *B = A->dir;
    A->dir = B->esq;
    B->esq = A;
    B->cor = A->cor;
    A->cor = VERMELHO;
    return B;
}


//função da rotação direita
NO_LLRBT *rotacao_direita(NO_LLRBT *A){
    NO_LLRBT *B = A->esq;
    A->esq = B->dir;
    B->dir = A;
    B->cor = A->cor;
    A->cor = VERMELHO;
    return B;
}

//para inverter a cor, basta fazer com que ela receba ela mesma negada
void inverte_cor(NO_LLRBT *no){
    if(no){
        no->cor = !no->cor;
    }
    if(no->esq){
        no->esq->cor = !no->esq->cor;
    }
    if(no->dir){
        no->dir->cor = !no->dir->cor;
    }
}

//caso o nó não exita ou tenha cor diferente de vermelho, o consideramos preto, do contrário, vemelho
bool vermelho(NO_LLRBT *no){
    if(no){
        return no->cor == VERMELHO;
    }
    return false;
}

//função recursiva para inserir um nó
NO_LLRBT *no_llrbt_inserir(NO_LLRBT *no, int elemento){
    if(!no){
        //se chegamos num nó nulo, então criamos um novo e colocamos o valor que queríamos inserir
        no = (NO_LLRBT *) malloc(1*sizeof(NO_LLRBT));
        if(no){
            no->chave = elemento;
            no->esq = NULL;
            no->dir = NULL;
            no->cor = VERMELHO;
        }
    }
    if(elemento < no->chave){
        //se o elemento é menor que a chave do nó, vamos para a esquerda
        no->esq = no_llrbt_inserir(no->esq, elemento);
    }
    if(elemento > no->chave){
        //se o elemento é maior que a chave do nó, vamos para a direita
        no->dir = no_llrbt_inserir(no->dir, elemento);
    }
    
    //condições de rebalanceamento na volta da recursão, fazendo as rotações e inversões necessárias
    if(!vermelho(no->esq) && vermelho(no->dir)){
        no = rotacao_esquerda(no);
    }
    if(vermelho(no->esq)&& vermelho(no->esq->esq)){
        no = rotacao_direita(no);
    }
    if(vermelho(no->esq) && vermelho(no->dir)){
        inverte_cor(no);
    }

    //note que se encontramos um nó igual não fazemos nada, logo não teremos nós repetidos
    return no;
}

//função que chama a função recursiva
bool llrbt_inserir(LLRBT *T, int elemento){
    T->raiz = no_llrbt_inserir(T->raiz, elemento);
    if(T->raiz){
        return true;//se o nó retornado existir, retornamos true
    }
    return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*FUNÇÕES DEDICADAS A REMOÇÃO DE UM ELEMENTO NA ÁRVORE*/
/*Obs: utiliza algumas funções da inserção (vemelha, rotações, inverter cor)*/

//propaga o nó para esquerda
NO_LLRBT *propagar_vermelho_esquerda(NO_LLRBT *no){
    if(!vermelho(no->esq) && !vermelho(no->esq->esq)){
        inverte_cor(no);
        if(no->dir){
            if(vermelho(no->dir->esq)){
                no->dir = rotacao_direita(no->dir);
                no = rotacao_esquerda(no);
                inverte_cor(no);
            }
        }
    }
    return no;
}

//propaga o nó para a direita
NO_LLRBT *propagar_vermelho_direita(NO_LLRBT *no){
    if(vermelho(no->esq)){
        no = rotacao_direita(no);
    }
    if(!vermelho(no->dir) && !vermelho(no->dir->esq)){
        inverte_cor(no);
        if(vermelho(no->esq->esq)){
            no = rotacao_direita(no);
            inverte_cor(no);
        }
    }
    return no;
}

//função que troca o maior elemento da esquerda (subarvore com nós menores que raiz) para trocar com o elemento a ser removido, assim
//continua sendo binária de busca
void troca_max_esq(NO_LLRBT *troca, NO_LLRBT *raiz, NO_LLRBT *ant){
    if(troca->dir){
        //enquanto não encontrar o maior continua indo para a direita
        troca_max_esq(troca->dir, raiz, troca);
        return;
    }
    //caso não haja mais direito, verifica se a raiz é o nó anteriror
    if(raiz == ant){
        //se for, o filho esquerdo da raiz passa a ser o filho esquerdo do nó mais à direita
        ant->esq = troca->esq;
    }
    else{
        //se não for, o filho direito do nó anterior passa a ser o filho esquedo do nó mais à direita
        ant->dir = troca->esq;
    }

    raiz->chave = troca->chave;
    //troca a raiz pelo maior nó e deleta o nó duplicado

    free(troca);
    troca = NULL;
}

NO_LLRBT *no_llrbt_remover(NO_LLRBT *no, int elemento){
    if(!no){
        return NULL;//se não encontramos o nó, apenas retornamos nulo
    }
    if(no->chave == elemento){
        if(no->esq == NULL || no->dir == NULL){
            //se um dos filhos do nó a ser deletado for nulo, apenas trocamos o nó pelo outro filho
            NO_LLRBT *aux = no;
            no = no->esq != NULL ? no->esq : no->dir;
            free(aux);
            aux = NULL;
        }
        else{
            //se nenhum dos filhos for nulo, trocamos pelo maior nó da subarvore esquerda
            troca_max_esq(no->esq, no, no);
        }
    }
    else if(elemento < no->chave){
        //se o elemento é menor, andamos propagando para aesquerda
        no = propagar_vermelho_esquerda(no);
        no->esq = no_llrbt_remover(no->esq, elemento);
    }
    else{
        //se não, andamos propagando para a direita
        no = propagar_vermelho_direita(no);
        no->dir = no_llrbt_remover(no->dir, elemento);
    }

    //aqui "consertamos" a árvore na volta da recursão
    if(no){
        if(!vermelho(no->esq) && vermelho(no->dir)){
            no = rotacao_esquerda(no);
        }
        if(vermelho(no->esq) && vermelho(no->esq->esq)){
            no = rotacao_direita(no);
        }
        if(vermelho(no->esq) && vermelho(no->dir)){
            inverte_cor(no);
        }
    }

    return no;
}

//função que chama a função recursiva
bool llrbt_remover(LLRBT *T, int elemento){
    T->raiz = no_llrbt_remover(T->raiz, elemento);
    if(T->raiz){
        return true;//se o nó retornado existir, retornamos true
    }
    return false;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*FUNÇÕES DEDICADAS A APAGAR A ÁRVORE*/

//função recusiva que deleta os nós em pós ordem
void no_llrbt_apagar(NO_LLRBT *no){
    if(!no){
        return;
    }
    no_llrbt_apagar((no)->esq);
    no_llrbt_apagar((no)->dir);
    free(no);
    return;
}

//função de apagar a árvore
void llrbt_apagar(LLRBT **T){
    if(!T){
        return;//se a arvore não existir, retornamos
    }
    no_llrbt_apagar((*T)->raiz);//chama a função recursiva
    free(*T);//deleta a arvore
    *T = NULL;
    return;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*FUNÇÕES DEDICADAS A IMPRIMIR A ÁRVORE*/

//função recursiva que imprime o conteúdo dos nós em ordem
void no_llrbt_imprimir(NO_LLRBT *no){
    if(!no){
        return;
    }
    no_llrbt_imprimir(no->esq);
    printf("%d, ", no->chave);
    no_llrbt_imprimir(no->dir);
}

//função para chamar a recursão
void llrbt_imprimir(LLRBT *T){
    no_llrbt_imprimir(T->raiz);
    printf("\n");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*FUNÇÕES DEDICADAS A OPERAÇÃO UNIÃO*/

//insere recursivamente os nós de uma árvore em outra
void no_llrbt_unir(LLRBT *uniao, NO_LLRBT *no){
    if(no){
        llrbt_inserir(uniao, no->chave);
        no_llrbt_unir(uniao, no->esq);
        no_llrbt_unir(uniao, no->dir);
    }
}

LLRBT *llrbt_uniao(LLRBT *T, LLRBT *U){
    if(!T){
        printf("Essa operação requer dois conjuntos existentes!\n");
        return NULL;
    }
    if(!U){
        printf("Essa operação requer dois conjuntos existentes!\n");
        return NULL;
    }
    //caso as duas árvores existam, criamos uma terceira e inserimos nela
    //como a insersão já não faz nós repetidos, não precisamos verificar
    LLRBT *V = llrbt_criar();
    no_llrbt_unir(V, T->raiz);
    no_llrbt_unir(V, U->raiz);
    return V;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*FUNÇÕES DEDICADAS A OPERAÇÃO INTERSECÇÃO*/

//função auxiliar que será usada, ela conta quantos nó uma árvore tem 
int contar_no(NO_LLRBT *no){
    if(!no){
        return 0;
    }
    return 1 + contar_no(no->esq) + contar_no(no->dir);
}

//função recursiva da interseção
void no_llrbt_interseccao(LLRBT *interseccao, LLRBT *T, NO_LLRBT *no_U){
    if(no_U){
        if(llrbt_pertence(T, no_U->chave)){
            //se existe o nó em ambas as árvores, inserimos na da intersecção
            llrbt_inserir(interseccao, no_U->chave);
        }
        no_llrbt_interseccao(interseccao, T, no_U->esq);
        no_llrbt_interseccao(interseccao, T, no_U->dir);
    }
}

LLRBT *llrbt_interseccao(LLRBT *T, LLRBT *U){
    if(!T){
        printf("Essa operação requer dois conjuntos existentes!\n");
        return NULL;
    }
    if(!U){
        printf("Essa operação requer dois conjuntos existentes!\n");
        return NULL;
    }
    //se ambas as arvores existirem, criamos uma terceira para retornar como conjunto intersecção
    LLRBT *V = llrbt_criar();
    //pegaremos a árvore com menor quantidade de nós para verificar se cada um deles existe na outra árvore, para minimizar o número de operções
    if(contar_no(T->raiz) > contar_no(U->raiz)){
        no_llrbt_interseccao(V, T, U->raiz); //chamada da recursão
    }
    else{
        no_llrbt_interseccao(V, U, T->raiz);//chamada da recursão
    }
    return V;
}