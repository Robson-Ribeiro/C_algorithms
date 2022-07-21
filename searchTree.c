#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

//Constantes
#define E 0
#define D 1
#define R -1

//Tipo nó
typedef struct NO {
	int dado;
	struct NO *esq;
	struct NO *dir;
	struct NO *pai;
} NO;

//Tipo árvore
typedef struct ARVORE{
	NO *raiz;
}ARVORE;

//Declaração da árvore
ARVORE a;

//Protótipos das funções
void inicializaArvore(ARVORE arv);
void inicializaNo(NO* n, int val);
void insereNoArvoreOrdenada(int valor);
void preOrdem(NO* raiz);

//Função que sempre deve ser chamada ao se criar uma nova árvore
void inicializaArvore(ARVORE arv)
{
	arv.raiz = NULL;
}

//Função utilizada para inicializar um novo nó na árvore
void inicializaNo(NO* n, int val){
	if(!n)
	{
		printf("Falha de alocacao.\n");
		return;
	}
	n->pai = NULL;
	n->esq = NULL;
	n->dir = NULL;
	n->dado = val;
}

//Função que realiza a inserção de maneira ordenada
void insereNoArvoreOrdenada(int valor)
{
	NO* corrente = a.raiz;
	NO* pai;

	NO* novoNo = (NO*) malloc(sizeof(NO));
	inicializaNo(novoNo, valor);
	
	if(corrente == NULL)
	{
		a.raiz = novoNo;
		return;
	}
	
	while(corrente){
		pai = corrente;
		if(novoNo->dado < corrente->dado){
			corrente = corrente->esq;
			if(!corrente){
				pai->esq = novoNo;
				return;
			}
		}
		else{
			corrente = corrente->dir;
			if(!corrente){
				pai->dir = novoNo;
				return;
			}
		}
	}
}

//Executa o caminhamento pré-ordem a partir do nó indicado por "raiz"
void preOrdem(NO* raiz){
	if(raiz){
		printf("%d \t", raiz->dado);
		preOrdem(raiz->esq);
		preOrdem(raiz->dir);
	}
}

int main()
{
	setlocale(LC_ALL, "Portuguese");
	inicializaArvore(a);

	// ESCOLHA A COMPOSIÇÃO DA ÁRVORE
	int i, RA[9] = {9, 9, 9, 9, 9, 9, 9, 9, 9}; 
	
	for(i = 0; i < 9; i++) {
		insereNoArvoreOrdenada(RA[i]);
	}	

	printf("Caminhamento pré-ordem: \n\n");
	preOrdem(a.raiz);
	return 0;
}
