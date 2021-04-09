#include "Grafo.hpp"
#include <vector>
#include <bits/stdc++.h>
#include <time.h>



int main()
{

	//Trabalhando com Arquivos
	vector <string> tokens;
	ifstream arquivo;
	string linha;
	string intermediate;

	Graph graph = GraphInitialize(100);
	arquivo.open("../Arquivos(txt)/adjacencia.txt");
	if(arquivo.is_open())
	{
		while(getline(arquivo,linha))
		{
			stringstream check1(linha);
			while(getline(check1, intermediate, ';'))
			{
				tokens.push_back(intermediate);
			}
			GraphInsertEdge(graph, stoi(tokens[0]), stoi(tokens[1]));
			tokens.clear();
		}
	}

    printGraph(graph);

	clock_t Ticks[2];
    Ticks[0] = clock();

	cout<<"\n\n ---------------BUSCA EM LARGURA--------------"<<endl;
	BFS(graph, 0);
	cout<<" -----------------------------------------------"<<endl;
	Ticks[1] = clock();

    double Tempo = (Ticks[1] - Ticks[0]) * 100.0 / CLOCKS_PER_SEC;
	clock_t Ticks1[2];
    Ticks1[0] = clock();

	cout<<"\n---------------BUSCA EM Profundidade--------------"<<endl;
	DFS(graph);
	cout<<" ----------------------------------------------------"<<endl;
	Ticks1[1] = clock();

	double Tempo1 = (Ticks1[1] - Ticks1[0]) * 100.0 / CLOCKS_PER_SEC;
	cout<<"\n*****Segundos Gastos BSF: "<<Tempo<<" *****"<<endl;
	cout<<"\n*****Segundos Gastos DSF: "<<Tempo1<<" *****"<<endl;

	return 0;
}