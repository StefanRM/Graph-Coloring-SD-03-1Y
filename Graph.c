#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Graph.h"

TGraphL* createGraphAdjList(int numberOfNodes){
	int i;

	TGraphL* G = (TGraphL*) malloc(sizeof(TGraphL));
	G->adl = (ATNode*) calloc(numberOfNodes, sizeof(ATNode));

	for (i = 0; i < numberOfNodes; i++)
	{
		G->adl[i] = NULL;
	}

	G->nn = numberOfNodes;

	return G;
}

ATNode newNode(int v, TCost cost)
{
	ATNode nod = (ATNode) malloc(sizeof(TNode));
	nod->v = v;
	nod->c = cost;
	nod->next = NULL;
	return nod;
}

void addEdgeList(TGraphL* graph, int v1, int v2, TCost cost){
	ATNode nod = newNode(v2, cost);
	nod->next = graph->adl[v1];
	graph->adl[v1] = nod;
}

void removeEdgeList(TGraphL* graph, int v1, int v2){
	ATNode p, t;

	p = graph->adl[v1];
	while(p != NULL)
	{
		if (p->v == v2)
		{
			if (p == graph->adl[v1])
			{
				graph->adl[v1] = p->next;
				free(p);
				break;
			}

			t->next = p->next;
			free(p);
			break;
		}

		t = p;
		p = p->next;
	}
}

void removeNodeList(TGraphL* graph, int v){
	int i, n = graph->nn;

	for (i = 0; i < n; i++)
	{
		removeEdgeList(graph, i, v);
	}
}

void destroyGraphAdjList(TGraphL* graph){
	ATNode p, t;
	int i, n = graph->nn;

	for (i = 0; i < n; i++)
	{
		p = graph->adl[i];

		while(p != NULL)
		{
			t = p;
			p = p->next;
			free(t);
		}

	}

	free(graph->adl);

	free(graph);
}