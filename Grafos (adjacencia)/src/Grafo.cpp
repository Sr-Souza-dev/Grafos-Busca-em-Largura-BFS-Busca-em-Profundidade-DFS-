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
int** VertexInitialize(int value){
	int **v = (int**) malloc(sizeof(int*)*value);
	for (int i=0; i<value; i++)
	{
		v[i] = new int[value];
		for (int j=0; j<value; j++)
			v[i][j] = 0;
	}
	return v;
}

Graph GraphInitialize(int numbVert){
	Graph graph = (Graph) malloc (sizeof(Graph));
	graph->numbVert = numbVert;
	graph->numbEdges = 0;
	graph->adj = VertexInitialize(numbVert);
	return graph;
}

void GraphInsertEdge(Graph graph, int v1, int v2){
	if(v1>-1 && v2>-1 && v1<graph->numbVert && v2<graph->numbVert)
	{
		graph->adj[v1][v2] = 1;
		graph->adj[v2][v1] = 1;
		graph->numbEdges++;
	}
	else	
		cout<<"[ERRO] Vertices não permitidos!"<<endl;

}

void printGraph(Graph graph){
	for(int i = 0; i<graph->numbVert; i++){
		cout<<"Conexões de ["<<i<<"]";
		for (int j = 0; j < graph->numbVert; j++)
		{
			if(graph->adj[i][j] != 0)
				cout<<" -> "<<j;
		}
		cout<<"\n";
	}
}
//---------------------------------------------------------------------------------------------------------------------

//--------------------------------------------------Busca em largura---------------------------------------------------
void BFS(Graph graph, int start)
{
	int i = 0;
    int *color = new int[graph->numbVert]; 				//0 Branco, 1 Cinza, 2 Preto
    int *distance = new int[graph->numbVert];			//Distancia até o vertice passado
    int *father = new int[graph->numbVert];				//Vetor pai
	Fila *fila = FFVazia();

    for(i=0; i<graph->numbVert; i++)
    {
        if(i != start)
        {
            color[i] = 0;
            distance[i] = -1;
            father[i] = -1;
        }
    }

    color[start] = 1;
    distance[start] = 0;
    father[start] = -1;

	Queue(fila, start);
	i=0;
	while(fila->size > 0)
	{
		Item *u = Dequeue(fila);
		for(int vertex = 0; vertex < graph->numbVert; vertex++)
		{
			if(color[vertex] == 0 && graph->adj[i][vertex] != 0)
			{
				color[vertex] = 1;
				distance[vertex] = distance[u->data] + 1;
				father[vertex] = u->data;
				Queue(fila,vertex);
			}
		}
		i++;
		color[u->data] = 2;
		cout<<"Vertex: "<<u->data<<endl;
	}
}
//---------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------Busca em Profundidade---------------------------------------------------

void DFS_VISIT(Graph graph, int vertex, int *color, int *distance, int *finale, int *time)
{
	color[vertex] = 1;
	*time += 1;
	distance[vertex] = *time;

	for(int u = 0; u < graph->numbVert; u++)
		if(color[u] == 0 && graph->adj[vertex][u] != 0)
			DFS_VISIT(graph, u, color, distance, finale, time);

	color[vertex] = 2;
	*time += 1;
	finale[vertex] = *time;
	cout<<"Vertex: "<<vertex<<"	Inicialização: "<<distance[vertex]<<"	Finalização: "<<finale[vertex]<<endl;
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
			DFS_VISIT(graph, vertex, color, distance, finale, &time);
}
//--------------------------------------------------------------------------------------------------------------------------
