#include "Grafo.hpp"
//--------------------------------------Fila para utilizar na busca em largura (BFS)--------------------------------

Fila* FFVazia(){
	Fila *f = new Fila;
	f->head = NULL;
	f->tail = NULL;
	return f;
}
void Queue(Fila *f, int vertex){			//Enfilera
	Item *d = new Item;
	d->data = vertex;
	d->prox = NULL;

	if(f->head == NULL){
		f->head = d;
		f->tail = d;
	}else{
		f->tail->prox = d;
		f->tail = d;
	}

	f->size ++;
}
Item* Dequeue(Fila *f){						//Desenfilera
	Item *aux;

	if(f->head == NULL)
		return NULL;

	aux = f->head;
	f->head = f->head->prox;
	f->size --;

	return aux;
}
//---------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------Tratando grafo------------------------------------------------------
Vertex VertexInitialize(int value){
	Vertex v = (Vertex) malloc (sizeof(Vertex));
	v->value = value;
	v->prox  = NULL;

	return v;
}

Graph GraphInitialize(int numbVert){
	Graph graph = (Graph) malloc (sizeof(Graph));
	graph->numbVert = numbVert;
	graph->numbEdges = 0;
	graph->adj = (Vertex*) malloc(numbVert * sizeof(Vertex));

	for(int i=0; i<numbVert; i++)
		graph->adj[i] = VertexInitialize(i);

	return graph;
}

void GraphInsertEdge(Graph graph, Vertex v1, Vertex v2){
	Vertex v = graph->adj[v1->value];
	Vertex v0 = graph->adj[v2->value];
	
	while(v->prox != NULL){
		if (v->value == v2->value)
			return;
		v = v->prox;
	}

	while(v0->prox != NULL){
		if (v0->value == v1->value)
			return;
		v0 = v0->prox;
	}

	v->prox = VertexInitialize(v2->value);
	v0->prox = VertexInitialize(v1->value);
	graph->numbEdges++;
}

void printGraph(Graph graph){
	Vertex aux;

	for(int v=0; v<graph->numbVert; v++){
		aux = graph->adj[v];
		while(aux != NULL){
			printf(" %d -> ", aux->value);
			aux = aux->prox;
		}
		printf("\n");
	}
}
//---------------------------------------------------------------------------------------------------------------------

//--------------------------------------------------Busca em largura---------------------------------------------------
void BFS(Graph graph, Vertex start)
{
    int *color = new int[graph->numbVert]; 			//0 Branco, 1 Cinza, 2 Preto
    int *distance = new int[graph->numbVert];			//Distancia até o vertice passado
    int *father = new int[graph->numbVert];			//Vetor pai
	Fila *fila = FFVazia();

    for(int i=0; i<graph->numbVert; i++)
    {
        if(i != start->value)
        {
            color[i] = 0;
            distance[i] = -1;
            father[i] = -1;
        }
    }

    color[start->value] = 1;
    distance[start->value] = 0;
    father[start->value] = -1;

	Queue(fila, start->value);

	while(fila->size > 0)
	{
		Item *u = Dequeue(fila);
		for(Vertex vertex = graph->adj[u->data]; vertex != NULL; vertex = vertex->prox)
		{
			if(color[vertex->value] == 0)
			{
				color[vertex->value] = 1;
				distance[vertex->value] = distance[u->data] + 1;
				father[vertex->value] = u->data;
				Queue(fila,vertex->value);
			}
		}
		color[u->data] = 2;
		cout<<"Vertex: "<<u->data<<endl;
	}
}
//---------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------Busca em Profundidade---------------------------------------------------
void DFS_VISIT(Graph graph, Vertex vertex, int *color, int *distance, int *finale, int *time)
{
	color[vertex->value] = 1;
	*time += 1;
	distance[vertex->value] = *time;

	for(Vertex u = graph->adj[vertex->value]; u != NULL; u = u->prox)
		if(color[u->value] == 0)
			DFS_VISIT(graph, u, color, distance, finale, time);

	color[vertex->value] = 2;
	*time += 1;
	finale[vertex->value] = *time;
	cout<<"Vertex: "<<vertex->value<<"	Inicialização: "<<distance[vertex->value]<<"	Finalização: "<<finale[vertex->value]<<endl;
}

void DFS(Graph graph)
{
	int *color = new int[graph->numbVert];			//0 Branco, 1 Cinza, 2 Preto;
	int *distance = new int[graph->numbVert];		//Marcar o tempo de inicialização;
	int *finale = new int[graph->numbVert];		//Marca o tempo de Finalização
	int time = 0;						//Tempo de percurso

	for(int vertex = 0; vertex < graph->numbVert; vertex++)
		color[vertex] = 0;
	
	for(int vertex = 0; vertex < graph->numbVert; vertex++)
		if(color[vertex] == 0)
			DFS_VISIT(graph, graph->adj[vertex], color, distance, finale, &time);
}
//--------------------------------------------------------------------------------------------------------------------------
