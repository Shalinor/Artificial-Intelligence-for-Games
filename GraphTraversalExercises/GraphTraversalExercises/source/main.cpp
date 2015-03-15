#include "Graph.h"

int main(int numArgs, char** args)
{
	Graph* graph = new Graph();

	Graph::Node *a, *b, *c, *d, *e, *f, *g, *h, *i, *j;
	a = graph->AddNode('a', 0);
	b = graph->AddNode('b', 0);
	c = graph->AddNode('c', 0);
	d = graph->AddNode('d', 0);
	e = graph->AddNode('e', 0);
	f = graph->AddNode('f', 0);
	g = graph->AddNode('g', 0);
	h = graph->AddNode('h', 0);
	i = graph->AddNode('i', 0);
	j = graph->AddNode('j', 0);

	graph->AddConnection(a, b);
	graph->AddConnection(a, d);
	graph->AddConnection(a, e);
	graph->AddConnection(b, c);
	graph->AddConnection(d, h);
	graph->AddConnection(e, h);
	graph->AddConnection(e, f);
	graph->AddConnection(f, c);
	graph->AddConnection(f, j);
	graph->AddConnection(g, c);
	graph->AddConnection(g, j);
	graph->AddConnection(i, j);
	graph->AddConnection(i, h);


	//graph->PrintBFS(a);
	//printf("\n");
	//graph->PrintDFS(a);

	graph->TraverseGraph(a, true);
	printf("\n");
	graph->TraverseGraph(a, false);

	printf("\n");
	system("pause");


	delete graph;

	return 0;
}