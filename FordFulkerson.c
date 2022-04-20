#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define A 0
#define B 1
#define C 2

#define MAX_NODES 1000

int n;                              // numeros de Blocos
int e;                              // numero de arestas
int capacity[MAX_NODES][MAX_NODES]; // matriz de capacidade
int flow[MAX_NODES][MAX_NODES];     // matriz flow
int color[MAX_NODES];               // vetor cores

int inicio, fim;
int queue[MAX_NODES + 2]; // vetor de queue

int vetor[MAX_NODES];

int minimo(int x, int y)
{ // função de comparação para facilidade de lógica
    return x < y ? x : y;
}

void read_arq()
{
    int a, b, c;
    FILE *arq;
    arq = fopen("entrada.txt", "r"); // Lê o arquivo contendo o grafo com fluxo
    fscanf(arq, "%d %d", &n, &e);
    printf("\nNumero de Vertices : %d   Arestas : %d", n, e);
    for (int i = 0; i < n; i++)
    { // inicia a matriz como nula
        for (int j = 0; j < n; j++)
        {
            capacity[i][j] = 0;
        }
    }
    for (int i = 0; i < e; i++)
    { // lê a capacidade das arestas
        fscanf(arq, "%d %d %d", &a, &b, &c);
        capacity[a][b] = c;
        printf("\nVertice %d - %d  Capacidade : %d", a, b, c);
    }
    fclose(arq);
}

void enfilerar(int x)
{
    queue[fim] = x;
    fim++;
    color[x] = B;
}

int desenfilerar()
{
    int x = queue[inicio];
    inicio++;
    color[x] = C;
    return x;
}
int busca(int inicio, int seleção)
{
    for (int u = 0; u < n; u++)
    {
        color[u] = A;
    }
    inicio = fim = 0;
    enfilerar(inicio);
    vetor[inicio] = -1;
    while (inicio != fim)
    {
        int i = desenfilerar();
        for (int v = 0; v < n; v++)
        {
            if (color[v] == A && capacity[i][v] - flow[i][v] > 0)
            {
                enfilerar(v);
                vetor[v] = i;
            }
        }
    }
    return color[seleção] == C;
}

//fordfulkerson algorithm
int fordFulkerson(int vertice1, int vertice2)
{
    int u;
    int max_flow = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            flow[i][j] = 0;
        }
    }

    while (busca(vertice1, vertice2))
    {
        int soma = 0;
        for (u = n - 1; vetor[u] >= 0; u = vetor[u])
        {
            soma = minimo(soma, capacity[vetor[u]][u] - flow[vetor[u]][u]);
        }
        for (u = n - 1; vetor[u] >= 0; u = vetor[u])
        {
            flow[vetor[u]][u] += soma;
            flow[u][vetor[u]] -= soma;
        }
        max_flow += soma;
    }
    return max_flow;
}


void imprimeLinha(char caractere, int qtdx)
{
    for (int i = 0; i <= qtdx; i++)
    {
        printf("%c", caractere);
    }
}

int showMenu()
{
    int op;
    imprimeLinha('*', 50);
    printf("\n                  MENU DE OPCOES\n");
    imprimeLinha('*', 50);
    printf("\n0 - SAIR");
    printf("\n1 - FORD-FULKERSON\n");
    imprimeLinha('*', 50);
    printf("\nINFORME A OPCAO: ");
    scanf("%d", &op);
    setbuf(stdin, NULL);
    return op;
}

int main()
{
    read_arq();

    while (1)
    {
        int op = showMenu();
        if (op == 0)
        {
            return 0;
        }
        if (op == 1)
        {
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j > i; j++)
                {
                    fordFulkerson(i, j);
                }
            }
        }
    }
    return 0;
}