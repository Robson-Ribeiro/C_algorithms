//Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

//Variáveis
int destino, origem, vertices = 5;
float custo, *custos = NULL; 

//Prototipação
void dijkstra(int vertices, int origem, int destino, float *custos);

//Função principal
int main(int argc, char **argv) {
	setlocale(LC_ALL, "Portuguese");
	int opt = -1;
	custos = (float *) malloc(sizeof(float)*5*5);
	
	//Preenchendo a matriz com -1
	int c;
	for (c = 0; c <= vertices * vertices; c++){
		custos[c] = -1; 
	}
	
	// RA: 22191756-5
	
 	custos[(1-1) * 5 + 2 - 1] = 2 * 6.596;
 	custos[(1-1) * 5 + 3 - 1] = 2 * 6.596;
 	custos[(2-1) * 5 + 4 - 1] = 1 * 6.596;
 	custos[(2-1) * 5 + 5 - 1] = 9 * 6.596;
 	custos[(3-1) * 5 + 2 - 1] = 1 * 6.596;
 	custos[(3-1) * 5 + 5 - 1] = 7 * 6.596;
 	custos[(4-1) * 5 + 5 - 1] = 5 * 6.596;
 	
 	system("color 03");
 	printf("A seguinte matriz de custos representa os trajetos da sua corrida: \n\n");
 	int i;
	for(i=0 ;i < vertices; i++){
		printf("[");
		for( c=0; c < vertices; c++){
			printf(" %.3f ",custos[i * 5 + c]);
    	}
    	if(i == 1 || i == 2) {
    		printf(" ]");	
		} else{
			printf("]");
		}
    	printf("\n");
  	}
 
	do {
		printf("\nInforme o nó inicial:");
		scanf("%d",&origem);
	} while (origem < 1 || origem > 5);

	printf("\nLista dos Menores Caminhos na sua corrida a partir de %d: \n\n", origem); 
	for (i = 1; i <= vertices; i++) {
		dijkstra(vertices, origem, i, custos);
	} 

	printf("\nAlgoritmo de Dijkstra finalizado...\n\n");
	free(custos);
	system("pause");
	return 0;
}

//Implementação do algoritmo de Dijkstra
void dijkstra(int vertices, int origem, int destino, float *custos) {
	int i, v, cont = 0;
	int *ant, *tmp; 
	int *z; /* vertices para os quais se conhece o caminho minimo */
	double min;
	double dist[vertices]; /* vetor com os custos dos caminhos */
	
	/* aloca as linhas da matriz */
	ant = (int*) calloc (vertices, sizeof(int *));
	if (ant == NULL) {
		system("color fc"); 
		printf ("** Erro: Memoria Insuficiente **");
		exit(-1);
	}
	
	tmp = (int*) calloc (vertices, sizeof(int *));
	if (tmp == NULL) {
		system("color fc"); 
		printf ("** Erro: Memoria Insuficiente **");
		exit(-1);
	} 
	
	z = (int *) calloc (vertices, sizeof(int *));
	if (z == NULL) {
		system("color fc");
		printf ("** Erro: Memoria Insuficiente **");
		exit(-1);
	}
	
	for (i = 0; i < vertices; i++) {
		if (custos[(origem - 1) * vertices + i] !=- 1) {
			ant[i] = origem - 1;
			dist[i] = custos[(origem-1)*vertices+i];
		}
		else {
			ant[i]= -1;
			dist[i] = HUGE_VAL;
		}
		z[i]=0;
	}
	z[origem-1] = 1;
	dist[origem-1] = 0;
	
	/* Laco principal */
	do {
		/* Encontrando o vertice que deve entrar em z */
		min = HUGE_VAL;
		for (i=0;i<vertices;i++){
			if (!z[i]){
				if (dist[i]>=0 && dist[i]<min) {
					min=dist[i];v=i;
				} 
			}
		}
		
		/* Calculando as distancias dos novos vizinhos de z */
		if (min != HUGE_VAL && v != destino - 1) {
			z[v] = 1;
			for (i = 0; i < vertices; i++){
				if (!z[i]) {
					if (custos[v*vertices+i] != -1 && dist[v] + custos[v*vertices+i] < dist[i]) {
						dist[i] = dist[v] + custos[v*vertices+i];
						ant[i] =v;
					}
				}
			}
		}
	} while (v != destino - 1 && min != HUGE_VAL);
	
	/* Mostra o Resultado da busca */
	printf("\tDe %d para %d: \t", origem, destino);
	if (min == HUGE_VAL) {
		printf("Nao Existe\n");
		printf("\tCusto: \t- \n");
	}
	else {
		i = destino;
		i = ant[i-1];
		while (i != -1) {
			tmp[cont] = i+1;
			cont++;
			i = ant[i];
		} 
		for (i = cont; i > 0 ; i--) {
			printf("%d -> ", tmp[i-1]);
		}
		printf("%d", destino);
		printf("\n\tCusto: %.3f\n", (float) dist[destino-1]);
	}
}

