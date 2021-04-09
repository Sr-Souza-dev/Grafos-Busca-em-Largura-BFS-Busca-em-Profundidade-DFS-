#ifndef GRAFO_HPP
#define GRAFO_HPP
#endif

#include <iostream>
using namespace std;

//----------------------------------------------------Tratando grafo------------------------------------------------------
typedef struct graph *Graph;

struct graph{
	int numbVert;
	int numbEdges;
	int** adj;
};
int** VertexInitialize(int value);
Graph GraphInitialize(int numbVert);
void GraphInsertEdge(Graph graph, int v1, int v2);
void printGraph(Graph graph);

//--------------------------------------------------Busca em largura---------------------------------------------------
void BFS(Graph graph, int start);

//-----------------------------------------------Busca em Profundidade-------------------------------------------------
void DFS_VISIT(Graph graph, int vertex, int *color, int *distance, int *finale, int *time);
void DFS(Graph graph);

//--------------------------------------Fila para utilizar na busca em largura e profundidade (BFS / DFS)--------------------------------
typedef struct TipoItem Item;
typedef struct TipoFila Fila;
struct TipoItem{
	int data;
	Item *prox;
};
struct TipoFila{
	Item *head;
	Item *tail;
	int size;
};
Fila* FFVazia();
void Queue(Fila *f, int vertex);			//Enfilera
Item* Dequeue(Fila *f);						//Desenfilera