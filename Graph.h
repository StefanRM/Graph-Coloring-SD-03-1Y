#ifndef GRAPH_H_
#define GRAPH_H_

typedef float TCost; // Cost(weight) of path to a specific node

typedef struct TNode{
	int v; // Destination node index
	TCost c; // Cost of the edge associated with the nodes
	struct TNode *next; // Link to the next node in the list
}TNode, *ATNode;

typedef struct{
	int nn; // Number of nodes in the graph
	ATNode *adl; // Adjancey list (TNode**)
}TGraphL;


TGraphL* createGraphAdjList(int numberOfNodes);

void addEdgeList(TGraphL* graph, int v1, int v2, TCost cost);
void removeEdgeList(TGraphL* graph, int v1, int v2);
void removeNodeList(TGraphL* graph, int v);

void destroyGraphAdjList(TGraphL* graph);


#endif /* GRAPH_H_ */
