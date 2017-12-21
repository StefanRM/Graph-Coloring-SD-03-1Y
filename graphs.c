#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"
#include "heap.h"

#define MAXIMUM 1000000 // biggest cost (unreachable)
#define MAX 1000 // maximum number of nodes in graph

// A utility function used to print path in Dijkstra Algorithm
void printParentPath(int* parent, int j)
{
	if (parent[j] == -1) // the path is completed
	{
		return;
	}

	printParentPath(parent, parent[j]);

	printf("%d ", j);
}

// A utility function used to print the solution
void printArr_Dijkstra(float* dist, int n, int s, int* parent, char* colors)
{
	float min = MAXIMUM;

	if (colors[s] == 'B') // the node is black (min distance = 0)
    {
    	min = 0;
    	printf("%f %d\n", min, s);
    	return;
    }

    int j;

    // find min distance to a black node
    for (int i = 0; i < n; ++i) 
    {
    	if ((colors[i] == 'B') && (min > dist[i]))
    	{
    		min = dist[i];
    		j = i;
    	}
    }

	if (min == MAXIMUM) // no path found to a black node
	{
		min = -1;
		printf("%.f\n", min);
	}
	else
	{
	    printf("%f %d ", min, s);
	    printParentPath(parent, j); // printing path
	    printf("\n");
	}

}

void dijkstra(TGraphL graph, int s, char* colors)
{
    int V = graph.nn;// Get the number of vertices in graph
    float* dist = (float*) malloc (V * sizeof(float)); // dist values used to pick minimum c edge in cut
    int* parent = (int*) malloc (V * sizeof(int)); // parent array for path
 
    // minheap represents set E
    MinHeap* h = newQueue(V);
 
    // Initialize min heap with all vertices. dist value of all vertices 
    for (int v = 0; v < V; ++v)
    {
        dist[v] = MAXIMUM;
        h->elem[v] = newNodeHeap(v, dist[v]);
        h->pos[v] = v;

        parent[v] = -1;
    }
 
    // Make dist cost of source vertex as 0 so that it is extracted first
    h->elem[s] = newNodeHeap(s, dist[s]);
    h->pos[s] = s;
    dist[s] = 0;
    SiftUp(h, s, dist[s]);
 
    // Initially size of min heap is equal to V
    h->size = V;
 
    // In the followin loop, min heap contains all nodes
    // whose shortest distance is not yet finalized.
    while (!isEmpty(h))
    {
        // Extract the vertex with minimum distance value
        MinHeapNode* node = removeMin(h);
        int u = node->v; // Store the extracted vertex number
 
        // Traverse through all adjacent vertices of u (the extracted
        // vertex) and update their distance values
        ATNode it = graph.adl[u];
        while (it != NULL)
        {
            int v = it->v;
 
            // If shortest distance to v is not finalized yet, and distance to v
            // through u is less than its previously MAXIMUM calculated distance
            if (isInMinHeap(h, v) && dist[u] != MAXIMUM && 
                                          it->c + dist[u] < dist[v])
            {
                dist[v] = dist[u] + it->c;
                parent[v] = u; 
 
                // update distance value in min heap also
                SiftUp(h, v, dist[v]);
            }

            it = it->next;
        }

        free(node);

    }
    destroyMinHeap(h);
 
    // print the calculated distances
    printArr_Dijkstra(dist, V, s, parent, colors);

    // deallocating memory
    free(parent);
    free(dist);
}

// solution for backtracking method
int solution(TGraphL* graph, int k, int n, char* colors, char* pattern, int* sol)
{
	if (k == n) // if enough nodes
	{
		// check if nodes' colors match pattern
		for (int i = 1; i <= n; i++)
		{
			if (colors[sol[i]] != pattern[i-1])
			{
				return 0;
			}
		}

		ATNode p, graphNode = graph->adl[sol[1]]; // p - for iteration, graphNode - current node in graph
		int ok; // signal if nodes adjacent or not

		// check if nodes are adjacent
		for (int i = 2; i <= n; i++)
		{
			ok = 0;
			p = graphNode;
			while((p != NULL) && (ok == 0))
			{
				if (p->v == sol[i])
				{
					ok = 1;
				}
				else
				{
					p = p->next;
				}
			}

			if (ok == 1) // nodes are not adjacent
			{
				graphNode = graph->adl[sol[i]]; // go to this node adjacent list
			}
			else
			{
				return 0;
			}
		}

		return 1;
	}
	return 0;
}

void printSolution(TGraphL* graph, int k, int n, int* sol)
{
	float cost = 0; // cost of path
	
	ATNode p, graphNode = graph->adl[sol[1]]; // p - for iteration, graphNode - current node in graph

	// iterate through path we found
	for (int i = 2; i <= n; i++)
	{
		p = graphNode;
		while(p != NULL) // we know it is a solution, we don't need extra conditions anymore
		{
			if (p->v == sol[i])
			{
				break;
			}
			else
			{
				p = p->next;
			}
		}

		cost = cost + p->c; // update cost
		graphNode = graph->adl[sol[i]]; // go to this node adjacent list
	}

	// print cost and solution array

	printf("%f ", cost);

	for (int i = 1; i <= k; i++)
	{
		printf("%d ", sol[i]);
	}
}


// Backtracking Method for finding numbers of solutions
void BK1(TGraphL* graph, int* nr_sol, int k, int n, int* sol, int* nodeSet, char* colors, char* pattern)
{
	// built array of solution
	for (int i = 0; i < nodeSet[k]; i++)
	{
		sol[k] = i;

		if (solution(graph, k, n, colors, pattern, sol)) // check if solution
		{
			(*nr_sol)++;			
		}
		else
			BK1(graph, nr_sol, k + 1, n, sol, nodeSet, colors, pattern);
	}
}

// Backtracking Method for finding the paths
void BK2(TGraphL* graph, int k, int n, int* sol, int* nodeSet, char* colors, char* pattern)
{
	// built array of solution
	for (int i = 0; i < nodeSet[k]; i++)
	{
		sol[k] = i;

		if (solution(graph, k, n, colors, pattern, sol)) // check if solution
		{
			printSolution(graph, k, n, sol);
			printf("\n");
		}
		else
			BK2(graph, k + 1, n, sol, nodeSet, colors, pattern);
	}
}


int main(int argc, char* argv[]) {
	// read & write normally with freopen()
	freopen(argv[1], "rt", stdin); // from where we read
  	freopen(argv[2], "wt", stdout); // where we write
	
	TGraphL *graph; // graph with adjacent lists
	int numOfVertices, i, j, nr_nodes, vertex, T1, T2; // i, j - contors
	float cost;
	char character, *colors, **patterns; // character - for reading purposes, colors - storing node colors, patterns - array of patterns to be found in graph

	scanf("%d", &numOfVertices);
	// printf("%d\n", numOfVertices);

	graph = createGraphAdjList(numOfVertices);
	colors = (char*) calloc((numOfVertices + 1), sizeof(char));

	scanf("%c", &character); // garbage

	// reading colors
	for (i = 0; i < numOfVertices; i++)
	{
		scanf("%c", &character);
		colors[i] = character;
		scanf("%c", &character); // garbage
	}

	// creating adjacent lists
	for (i = 0; i < numOfVertices; i++)
	{
		scanf("%d", &nr_nodes);

		for (j = 0; j < nr_nodes; j++)
		{
			scanf("%d %f", &vertex, &cost);
			addEdgeList(graph, i, vertex, cost);
		}

		// addEdgeList(graph, i, i, colors[i], INT_MAX);
	}

	scanf("%d", &T1);

	// first task
	for (i = 0; i < T1; i++)
	{
		scanf("%d", &j);
		dijkstra(*graph, j, colors);
	}
	
	scanf("%d", &T2);

	patterns = (char**) calloc(T2, sizeof(char*));

	// read patterns for second task
	for (i = 0; i < T2; i++)
	{
		scanf("%d", &nr_nodes);
		patterns[i] = (char*) calloc(nr_nodes + 1, sizeof(char));

		for (j = 0; j < nr_nodes; j++)
		{
			scanf("%c", &character);
			if (character == ' ')
			{
				scanf("%c", &character);
			}
			patterns[i][j] = character;
		}
	}


	int n, // number of colors in patterns[i]
		nr_sol, // number of solutions of paths matching the pattern[i]
		*sol = (int*) malloc(MAX * sizeof(int)), // solution array in backtracking method
		*nodeSet = (int*) malloc(MAX * sizeof(int)); // set of graph's nodes

	for (i = 0; i < T2; i++) // for every pattern
	{
		nr_sol = 0;
		n = strlen(patterns[i]);

		// initialize set of graph's nodes
		for(j=1; j<=n; j++)
		{
			nodeSet[j] = numOfVertices;
		}

		BK1(graph, &nr_sol, 1, n, sol, nodeSet, colors, patterns[i]); // find number of solutions

		printf("%d\n", nr_sol);

		BK2(graph, 1, n, sol, nodeSet, colors, patterns[i]); // print solutions
	}

	// deallocating memory

	free(sol);
	free(nodeSet);

	for (i = 0; i < T2; i++)
	{
		free(patterns[i]);
	}

	free(patterns);

	free(colors);
	destroyGraphAdjList(graph);

	// closing files
	fclose(stdin);
	fclose(stdout);
	return 0;
}