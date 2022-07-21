#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

//Constantes
#define E 0
#define D 1
#define R -1

//Tipo n�
typedef struct NO {
	int dado;
	struct NO *esq;
	struct NO *dir;
	struct NO *pai;
} NO;

//Tipo �rvore
typedef struct ARVORE{
	NO *raiz;
}ARVORE;

//Declara��o da �rvore
ARVORE a;

//Prot�tipos das fun��es
void inicializaArvore(ARVORE arv);
void inicializaNo(NO* n, int val);
void insereNoArvoreOrdenada(int valor);
void preOrdem(NO* raiz);

//Fun��o que sempre deve ser chamada ao se criar uma nova �rvore
void inicializaArvore(ARVORE arv)
{
	arv.raiz = NULL;
}

//Fun��o utilizada para inicializar um novo n� na �rvore
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

//Fun��o que realiza a inser��o de maneira ordenada
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

//Executa o caminhamento pr�-ordem a partir do n� indicado por "raiz"
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

	// ESCOLHA A COMPOSI��O DA �RVORE
	int i, RA[9] = {9, 9, 9, 9, 9, 9, 9, 9, 9}; 
	
	for(i = 0; i < 9; i++) {
		insereNoArvoreOrdenada(RA[i]);
	}	

	printf("Caminhamento pr�-ordem: \n\n");
	preOrdem(a.raiz);
	return 0;
}

