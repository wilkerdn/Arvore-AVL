#include <stdio.h>
#include <stdlib.h>

struct arvore{
    int n, fb;

    struct arvore *esq;
    struct arvore *dir;
    struct arvore *pai;
};

struct arvore *raiz = NULL;

void menu();
void insere();
void exibir_pre_ordem(struct arvore*);
void exibir_pos_ordem(struct arvore*);
void exibir_in_ordem(struct arvore*);
/*void exibir_niveis(struct arvore*);
void exibir_nv_aux(struct arvore*, int, int);*/
void remover_aux();
void remover(struct arvore*);
struct arvore* menor_dir(struct arvore*);
struct arvore* busca_elemento(int);
void excluir_arvore(struct arvore*);
int altura(struct arvore*);
struct arvore* balancear(struct arvore*);
struct arvore* rotacaoRR(struct arvore*);
struct arvore* rotacaoLL(struct arvore*);

int main(){
    struct arvore *b;
    int op, n;

    while(1){
        menu();

        scanf("%d", &op);

        switch(op){
            case 1: insere();
                    /*exibir_niveis(raiz);
                    printf("\n\n");*/
                    break;

            case 2: printf("\n");
                    remover_aux();
                    printf("\n");
                    /*exibir_niveis(raiz);*/
                    break;

            case 3: printf("Digite o numero: ");
                    scanf("%d", &n);

                    b = busca_elemento(n);

                    if(b){
                        printf("O numero %d esta presente na arvore\n\n", b->n);
                    }

                    else{
                        printf("O numero %d nao esta presente na arvore\n\n");
                    }

                    b = NULL;
                    break;

            case 4: printf("\nPre-ordem: ");
                    exibir_pre_ordem(raiz);
                    printf("\n");
                    break;

            case 5: printf("\nPos-ordem: ");
                    exibir_pos_ordem(raiz);
                    printf("\n");
                    break;

            case 6: printf("\nIn-ordem: ");
                    exibir_in_ordem(raiz);
                    printf("\n");
                    break;

            case 7: printf("\nAltura da arvore: %d\n\n", altura(raiz)-1);
                    break;

            case 8: if(raiz){
                        excluir_arvore(raiz);
                        printf("Arvore excluida\n\nComecando uma nova arvore\n\n");
                    }

                    else{
                        printf("A arvore ja estava limpa\n\n");
                    }
                    break;

            case 9: if(raiz){
                        excluir_arvore(raiz);
                    }
                    exit(0);

            default: printf("Opcao inexistente\n");
                     break;
        }
    }
}

void menu(){
    printf("Inserir numero = 1\nRemover numero = 2\nEfetuar busca = 3\nExibir pre-ordem = 4\nExibir pos-ordem = 5\nExibir in-ordem = 6\nAltura da arvore = 7\nExcluir arvore = 8\nSair = 9 \nDigite uma opcao: ");
}

void insere(){
    struct arvore *aux1 = NULL, *aux2 = NULL;
    int n;

    printf("\nDigite o numero a inserir: ");
    scanf("%d", &n);

    if(!raiz){
        raiz = (struct arvore*) malloc(sizeof(struct arvore));

        if(!raiz){
            printf("Erro ao inserir\n");
            exit(1);
        }

        raiz->n = n;
        raiz->esq = NULL;
        raiz->dir = NULL;
        raiz->pai = NULL;

        raiz->fb = 0;
    }else{
        aux1 = raiz;
        aux2 = aux1;

        while(aux2){
            if(n < aux2->n){
                aux2 = aux2->esq;

                if(!aux2){
                    aux1->esq = (struct arvore*) malloc(sizeof(struct arvore));

                    if(!aux1->esq){
                        printf("Erro ao inserir\n");
                        exit(1);
                    }

                    aux2 = aux1->esq;

                    aux2->esq = NULL;
                    aux2->dir = NULL;
                    aux2->pai = aux1;
                    aux2->n = n;
                    break;
                }else{
                    aux1 = aux2;
                }
            }else{
                aux2 = aux2->dir;

                if(!aux2){
                    aux1->dir = (struct arvore*) malloc(sizeof(struct arvore));

                    if(!aux1->dir){
                        printf("Erro ao inserir\n\n");
                        exit(1);
                    }

                    aux2 = aux1->dir;

                    aux2->esq = NULL;
                    aux2->dir = NULL;
                    aux2->pai = aux1;
                    aux2->n = n;
                    break;
                }else{
                    aux1 = aux2;
                }
            }
        }
    }
    printf("Elemento inserido\n\n");

    if(aux2){
        while(aux2){
            aux2->fb = altura(aux2->dir) - altura(aux2->esq);

            if(aux2->fb > 1 || aux2->fb < -1){
                aux2 = balancear(aux2);
            }

            aux2 = aux2->pai;
        }
    }
}

void exibir_pre_ordem(struct arvore *aux){
    if(!raiz){
        printf("Arvore vazia");
        return;
    }
    if(aux){
        printf("%d(%d) ", aux->n, aux->fb);
        exibir_pre_ordem(aux->esq);
        exibir_pre_ordem(aux->dir);
    }
}

void exibir_pos_ordem(struct arvore *aux){
    if(!raiz){
        printf("Arvore vazia");
        return;
    }
    if(aux){
        exibir_pos_ordem(aux->esq);
        exibir_pos_ordem(aux->dir);
        printf("%d(%d) ", aux->n, aux->fb);
    }
}

void exibir_in_ordem(struct arvore *aux){
    if(!raiz){
        printf("Arvore vazia");
        return;
    }
    if(aux){
        exibir_in_ordem(aux->esq);
        printf("%d(%d) ", aux->n, aux->fb);
        exibir_in_ordem(aux->dir);
    }
}

void remover_aux(){
    struct arvore *aux;
    int n;

    printf("Digite o numero para remover: ");
    scanf("%d", &n);

    aux = busca_elemento(n);

    if(aux){
        remover(aux);
    }else{
        printf("O numero nao esta presente na arvore\n");
    }
}

void remover(struct arvore *aux){
    struct arvore *aux2, *salva = aux->pai;

    if(aux != raiz){
        if(!aux->esq && !aux->dir){
            if(aux->n < aux->pai->n){
                aux->pai->esq = NULL;
            }else{
                aux->pai->dir = NULL;
            }
            free(aux);
        }else if(!aux->dir){
            if(aux->n < aux->pai->n){
                aux->pai->esq = aux->esq;
            }else{
                aux->pai->dir = aux->esq;
            }
            aux->esq->pai = aux->pai;
            free(aux);
        }else if(!aux->esq){
            if(aux->n < aux->pai->n){
                aux->pai->esq = aux->dir;
            }else{
                aux->pai->dir = aux->dir;
            }
            aux->dir->pai = aux->pai;
            free(aux);
        }else{
            aux2 = menor_dir(aux->dir);
            aux->n = aux2->n;
            remover(aux2);
        }
    }else{
        if(!aux->esq && !aux->dir){
            free(aux);
            raiz = NULL;
        }else if(!aux->dir){
            aux->esq->pai = NULL;
            raiz = aux->esq;
            free(aux);
        }else if(!aux->esq){
            aux->dir->pai = NULL;
            raiz = aux->dir;
            free(aux);
        }else{
            aux2 = menor_dir(aux->dir);
            aux->n = aux2->n;
            remover(aux2);
        }
    }
    if(salva){
        while(salva){
            salva->fb = altura(salva->dir) - altura(salva->esq);

            if(salva->fb > 1 || salva->fb < -1){
                salva = balancear(salva);
            }
            salva = salva->pai;
        }
    }
}

struct arvore* menor_dir(struct arvore *aux){
    while(aux->esq){
        aux = aux->esq;
    }
    return aux;
}

struct arvore* busca_elemento(int n){
    struct arvore *aux;

    aux = raiz;

    while(aux && aux->n != n){
        if(n < aux->n){
            aux = aux->esq;
        }else{
            aux = aux->dir;
        }
    }
    return aux;
}

void excluir_arvore(struct arvore *aux){
    if(aux->esq){
        excluir_arvore(aux->esq);
    }
    if(aux->dir){
        excluir_arvore(aux->dir);
    }
    free(aux);
    raiz = NULL;
}

int altura(struct arvore *aux){
    if(!aux){
        return 0;
    }
    int ae = altura(aux->esq);
    int ad = altura(aux->dir);

    return (ae > ad) ? ae + 1: ad + 1;
}

struct arvore* rotacaoRR(struct arvore *aux){
    struct arvore *esq = aux->esq;

    aux->esq = esq->dir;
    esq->dir = aux;

    if(aux->esq){
        aux->esq->pai = aux;
    }

    esq->pai = aux->pai;
    aux->pai = esq;

    if(aux == raiz){
        raiz = esq;
    }

    if(esq->pai){
        if(esq->n < esq->pai->n){
            esq->pai->esq = esq;
        }else{
            esq->pai->dir = esq;
        }
    }

    esq->fb = altura(esq->dir) - altura(esq->esq);
    aux->fb = altura(aux->dir) - altura(aux->esq);

    return esq;
}

struct arvore* rotacaoLL(struct arvore *aux){
    struct arvore *dir = aux->dir;

    aux->dir = dir->esq;
    dir->esq = aux;

    if(aux->dir){
        aux->dir->pai = aux;
    }

    dir->pai = aux->pai;
    aux->pai = dir;

    if(aux == raiz){
        raiz = dir;
    }
    if(dir->pai){
        if(dir->n < dir->pai->n){
            dir->pai->esq = dir;
        }else{
            dir->pai->dir = dir;
        }
    }
    dir->fb = altura(dir->dir) - altura(dir->esq);
    aux->fb = altura(aux->dir) - altura(aux->esq);
    return dir;
}

struct arvore* balancear(struct arvore *aux){
    if(aux->fb < -1){
        if(aux->esq->fb > 0){
            aux->esq = rotacaoLL(aux->esq);
        }
        aux = rotacaoRR(aux);
    }

    else if(aux->fb > 1){
        if(aux->dir->fb < 0){
            aux->dir = rotacaoRR(aux->dir);
        }
        aux = rotacaoLL(aux);
    }

    return aux;
}

/*void exibir_niveis(struct arvore *aux){
    int i;

    for(i = 0; i <= altura(raiz); i++){
        printf("Nivel %d -> ", i);
        exibir_nv_aux(raiz, i, 0);
    }
}

void exibir_nv_aux(struct arvore *aux, int atual, int cont){
    if(!raiz){
        printf("A arvore esta vazia!");
        getchar();
        return;
    }
    if(aux){
        exibir_nv_aux(aux->esq, atual, cont+1);
        if(atual == cont){
            printf("%d\n", aux->n);
        }
        exibir_nv_aux(aux->dir, atual, cont+1);
    }
}*/
