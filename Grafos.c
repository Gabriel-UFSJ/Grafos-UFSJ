#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define INF 999 // infinito para vertices não conectados

#define MAX 100

// atividade 1

typedef struct No {
  int vertice; //número do bloco
  struct No* prox;// ponteiro para o prox no
} No; // struct no

typedef struct Grafo{
  int numVertices; // número do vertice
  No** listaAdj; // matriz de lista adjacente
} Grafo;// sctruct grafo

No* criarNo(int v){
  No* newNo = malloc(sizeof(No)); // alocação do No
  newNo->vertice = v; // define o número do vertice
  newNo->prox = NULL; // aponta o prox para NULL
  return newNo;
}

//Grafo com um vértice
Grafo* criarGrafo(){
  Grafo* grafo = malloc(sizeof(Grafo)); // alocação do Grafo
  grafo->numVertices = 1; // define o numero do bloco
  grafo->listaAdj = malloc(sizeof(No*)); // aloca uma matriz de lista dentro do grafo
  grafo->listaAdj[0] = NULL; // define a posição [0] da matriz para NULL
  
  return grafo;
}

void addLig(Grafo* grafo, int v1, int v2) {// faz a ligação dos blocos no grafo
  if(v2 >= grafo->numVertices) {
    int antigo = grafo->numVertices;
    grafo->numVertices = v2 + 1;
    grafo->listaAdj = realloc(grafo->listaAdj, grafo->numVertices * sizeof(No*)); // realoca o tamanho do grafo de acordo com a quatidade de blocos

    while(antigo < grafo->numVertices) { // limpa o primeiro grafo criado
      grafo->listaAdj[antigo] = NULL;
      antigo++;
    }
  }
  No* newNo = criarNo(v2); // cria um novo No para grafo seguinte
  No* noAtual = grafo->listaAdj[v1]; // define o Noatual
  //Primeiro elemento (da lista ou por ordenação)
  if(noAtual == NULL || newNo->vertice < noAtual->vertice) {
    newNo->prox = noAtual;
    grafo->listaAdj[v1] = newNo;
    return;
  }

  //Elementos posteriores
  while(noAtual->prox != NULL && noAtual->prox->vertice < newNo->vertice) {
    newNo = noAtual->prox;
  }

  newNo->prox = noAtual->prox;
  noAtual->prox = newNo;

}

void sumario(int lig, int numblock){ // Uma função sumário, que retorna algumas informações importantes sobre o grafo, como número de vértices, número de arestas e densidade do grafo;
  printf("\nO Grafo tem:");
  printf("%d nos, %d vertices\n",numblock,lig);
  int density;
  density = (2 * lig)/numblock*(numblock-1);
  printf("\nA densidade do grafo: %d", density);
  printf("\n\n");
}

void grau(Grafo* grafo,int numgrafo){ // Uma função grau de vértice, que recebe um índice de um vértice e retorna seu grau;
  int g= 0;
  No* temporario = grafo->listaAdj[numgrafo]; // cria um no temporario para impressão

  while(temporario){
    temporario = temporario->prox;
    g++;
  }
  printf("O grau do vertice %d:  %d", numgrafo, g);
  printf("\n\n");
}
  
void sucessores(Grafo* grafo, int vertice){ // Uma função sucessores de vértice, que recebe um índice de um vértice e retorna seus sucessores;
  printf("\nOs vertices sucessores de %d: ",vertice);
  No* temporario = grafo->listaAdj[vertice]; // cria um no temporario para impressão
  while(temporario){
    printf("%d ",temporario->vertice);
    temporario = temporario->prox;
  }
  printf("\n\n");
}

void antecessores(Grafo* grafo, int vertice){ // Uma função antecessores de vértice, que recebe um índice de um vértice e retorna seus antecessores.
  int v;
  printf("\nOs vertices antecessores de %d: ", vertice);
  for(v = 0; v < grafo->numVertices; v++){
    No* temporario = grafo->listaAdj[v]; // cria um no temporario para impressão
    while(temporario){
      if(temporario->vertice == vertice){
        printf("%d ", v);
      }
      temporario = temporario->prox;
    }
  }
  printf("\n\n");
}

void imprimeLinha(char caractere, int qtdx) {
	for (int i = 0; i <= qtdx; i++) {
		printf("%c", caractere);
	}
}

int showMenu(){
  int op;
  imprimeLinha('*', 50);
  printf("\n                  MENU DE OPCOES\n");
  imprimeLinha('*', 50);
  printf("\n0 - SAIR");
  printf("\n1 - SUMARIO");
  printf("\n2 - GRAU DE VERTICE");
  printf("\n3 - SUCESSORES DE VERTICE");
  printf("\n4 - ANTECESSORES DE VERTICE");
  printf("\n5 - IMPRIMIR GRAFO");
  printf("\n6 - FLOYD WARSHALL\n");
  imprimeLinha('*', 50);
  printf("\nINFORME A OPCAO: ");
  scanf("%d", &op);
  setbuf(stdin, NULL);
  return op;
}

int showMenu2(){
  int op;
  imprimeLinha('*', 50);
  printf("\n\tMENU DE MEDIAS E VERTICES\n");
  imprimeLinha('*', 50);
  printf("\n0 - VOLTAR");
  printf("\n1 - MATRIZ DE DISTANCIAS");
  printf("\n2 - EXCENTRICIDADE DE CADA VERTICE");
  printf("\n3 - RAIO DO GRAFO");
  printf("\n4 - DIAMETRO DO GRAFO");
  printf("\n5 - CENTRO DO GRAFO");
  printf("\n6 - CENTROIDE DO GRAFO");
  printf("\n7 - PERIFERIA DO GRAFO\n");
  imprimeLinha('*', 50);
  printf("\nINFORME A OPCAO: ");
  scanf("%d", &op);
  setbuf(stdin, NULL);
  return op;
}

void imprimir(Grafo* grafo){
  int v;
  printf("\nGraph:\n");
  for(v = 1; v < grafo->numVertices; v++){
    No* temporario = grafo->listaAdj[v]; // cria um no temporario para impressão
    printf("\nB%d --> ", v);

    while(temporario){
      printf("%d ",temporario->vertice);
      temporario = temporario->prox;
    }
  }
  printf("\n");
}

// atividade 2

void Periferia(int dist[MAX][MAX], int numblock){
  int maxgraph = 0;
  for (int i = 0; i < numblock; i++){
    for (int j = 0; j < numblock; j++){
      if(dist[i][j] > maxgraph && dist[i][j] != INF){
        maxgraph = dist[i][j];
      }
    }
  }
  printf("\n");
  printf("As periferias do grafo vertice(s): ");
  for (int i = 0; i < numblock; i++){
    for (int j = 0; j < numblock; j++){
      if(dist[i][j] == maxgraph){
        printf("%d", i+1);
      }
    }
  }
  printf("\n");
}

void Centroid(int dist[MAX][MAX], int numblock){
  int TAM = numblock;
  int d[TAM];
  int subinf[TAM];
  for(int i = 0; i < TAM; i++) {
    d[i] = 0;
    for(int j = 0; j < TAM; j++){
      d[i] += dist[i][j];
    }
  }
  int index = 0, soma = 999;

  for(int i = 0; i < TAM;i++){
    if(d[i] < soma){
      index = i;
      soma = d[i];
    }
  }
  printf("\nCentroid = %d\n", index + 1);
}

void Centro(int dist[MAX][MAX], int numblock){
  int mingraph = INF, eccentricity = 0;
  for (int i = 0; i < numblock; i++){
    for (int j = 0; j < numblock; j++){
      if(dist[i][j] > eccentricity && dist[i][j] != INF){
        eccentricity = dist[i][j];
      }
    }
    if(eccentricity < mingraph){
      mingraph = eccentricity;
    }
  }

  printf("\n");
  printf("\nOs Centros do grafo vertice(s): ");
  for (int i = 0; i < numblock; i++){
    for (int j = 0; j < numblock; j++){
      if(dist[i][j] == mingraph){
        printf("%d ", i+1);
      }
    }
  }
  printf("\n");
}

void Raio(int dist[MAX][MAX], int numblock){
  int mingraph = INF, eccentricity = 0;
  for (int i = 0; i < numblock; i++){
    for (int j = 0; j < numblock; j++){
      if(dist[i][j] > eccentricity && dist[i][j] != INF){
        eccentricity = dist[i][j];
      }
    }
    if(eccentricity < mingraph){
      mingraph = eccentricity;
    }
  }
  printf("\nRaio do grafo = %d \n", mingraph);
}

void Diametro(int dist[MAX][MAX], int numblock){
  int maxgraph = 0;
  for (int i = 0; i < numblock; i++){
    for (int j = 0; j < numblock; j++){
      if(dist[i][j] > maxgraph && dist[i][j] != INF){
        maxgraph = dist[i][j];
      }
    }
  }
  printf("\nO Diametro do grafo = %d\n",maxgraph);
}

void Eccentricity(int dist[MAX][MAX], int numblock){
  for (int i = 0; i < numblock; i++){
    int eccentricity = 0;
    for (int j = 0; j < numblock; j++){
      if(dist[i][j] > eccentricity && dist[i][j] != INF){
        eccentricity = dist[i][j];
      }
    }
    printf("\nExcentricidade do vertice %d = %d", i+1, eccentricity);
  }
  printf("\n");
}

void printDist(int dist[MAX][MAX], int numblock){
  printf ("\n\t\tMATRIZ DE DISTANCIA\n");
  int V = numblock;
  for (int i = 0; i < V; i++){
    for (int j = 0; j < V; j++){
      if (dist[i][j] == INF){
        printf("%s \t", "INF");
      }
      else{
        printf ("%d \t", dist[i][j]);
      }
    }
    printf("\n");
  }
}

int floydWarshall (int matriz[MAX][MAX], int numblock){
  int V = numblock;
  int dist[MAX][MAX], i, j, k;

  for (i = 0; i < V; i++){
    for (j = 0; j < V; j++){
      dist[i][j] = matriz[i][j];
    }
  }
  
  for (k = 0; k < V; k++){
    for (i = 0; i < V; i++){
      for (j = 0; j < V; j++){
        if (dist[i][k] + dist[k][j] < dist[i][j]){
          dist[i][j] = dist[i][k] + dist[k][j];
        }
      }
    }
  }

  while(1){
    int op = showMenu2();
    if(op == 0){
      return 0;
    }
    else if(op == 1){
      printDist(dist, V);
    }
    else if(op == 2){
      Eccentricity(dist, V);
    }
    else if(op == 3){
      Raio(dist, V);
    }
    else if(op == 4){
      Diametro(dist, V);
    }
    else if(op == 5){
      Centro(dist, V);
    }
    else if(op == 6){
      Centroid(dist, V);
    }
    else if(op == 7){
      Periferia(dist, V);
    }
  }
}



// int main

int main(){
  struct Grafo* grafo = criarGrafo(); // cria o primeiro grafo

  int origem = 0, destino = 0, valor;
  char entrada[100]; 
  char *codigo[100];
  int numblock = 0; // define o número de blocos
  int lig = 0;
  int numlinhas=0, i = 0;

  FILE *arquivo;// abre o arquivo
  arquivo = fopen("entrada.txt", "r");
  
  if(arquivo == NULL){// se o arquivo não existir retorna uma mensagem de erro
    printf("\nFalha ao abrir arquivo\n");
    return 0;
  }

  while(fgets(entrada, sizeof entrada, arquivo)!= NULL){
    codigo[i] = strdup(entrada);// copia as intruções presentes no arquivo
    i++;
    numlinhas++;
  }

  printf("\nEntrada:\n\n");
  for (int j = 0; j < numlinhas; j++){
    printf("%s", codigo[j]); // imprime entrada gravada no arquivo
  }
  printf("\n\n");
  
  for(int i = 0; i < numlinhas; i++){
    origem = (codigo[i][0]- '0');
    destino = (codigo[i][2]- '0');
    addLig(grafo,origem,destino);
    lig++;
  }
  numblock = grafo->numVertices-1;
  
  // iniciando a matriz onde cada celula é não conectada
  int matriz[MAX][MAX];
  for(int i = 0; i < numblock; i++){
    for(int j = 0; j < numblock; j++){
      matriz[i][j] = 999;
    }
  }
  for(int i = 0; i < numlinhas; i++){
    int origem = 0, destino = 0, valor = 1;
    origem = (codigo[i][0]- '0')-1;
    destino = (codigo[i][2]- '0')-1;
    valor = (codigo[i][4]- '0');
    matriz[origem][destino] = valor;
  }

  while(1){
    int op = showMenu();
    if(op == 0){
      return 0;
    }
    else if(op == 1){
      sumario(lig,numblock);
    }
    else if(op == 2){
      int numgrafo;
      printf("\nIndique o indice do vertice: ");
      scanf("%d", &numgrafo);
      grau(grafo,numgrafo);
    }
    else if (op == 3){
      int vertice;
      printf("\nIndique o indice do vertice: ");
      scanf("%d", &vertice);
      sucessores(grafo,vertice);
    }
    else if (op == 4){
      int vertice;
      printf("\nIndique o indice do vertice: ");
      scanf("%d", &vertice);
      antecessores(grafo,vertice);
    }
    else if (op == 5){
      imprimir(grafo);
    }
    else if (op == 6){
      floydWarshall(matriz,numblock);
    }
  }
}