#ifndef __HEAP_H__
#define __HEAP_H__

#include <stdlib.h>
#include <math.h>

typedef struct MinHeapNode
{
    int  v;
    int d;
} MinHeapNode;


typedef struct MinHeap
{
    int size;
    int capacity;
    int *pos;
    MinHeapNode **elem;
} MinHeap;


MinHeapNode* newNodeHeap(int v, int d)
{
	MinHeapNode* newNode = (MinHeapNode*) malloc(sizeof(MinHeapNode));
    newNode->v = v;
    newNode->d = d;

    return newNode;
}

MinHeap* newQueue(int capacity)
{
	MinHeap* h = (MinHeap*) malloc(sizeof(struct MinHeap));
    h->pos = (int *)malloc(capacity * sizeof(int));
    h->size = 0;
    h->capacity = capacity;
    h->elem = (MinHeapNode**) malloc(capacity * sizeof(MinHeapNode*));

    return h;
}

void swap(MinHeapNode** a, MinHeapNode** b)
{
	MinHeapNode* aux = *a;
    *a = *b;
    *b = aux;
}

void SiftDown(MinHeap* h, int idx)
{
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;
 
    if (left < h->size &&
        h->elem[left]->d < h->elem[smallest]->d )
      smallest = left;
 
    if (right < h->size &&
        h->elem[right]->d < h->elem[smallest]->d )
      smallest = right;
 
    if (smallest != idx)
    {
        // The nodes to be swapped in min heap
        MinHeapNode *smallestNode = h->elem[smallest];
        MinHeapNode *idxNode = h->elem[idx];
 
        // Swap positions
        h->pos[smallestNode->v] = idx;
        h->pos[idxNode->v] = smallest;
 
        // Swap nodes
        swap(&h->elem[smallest], &h->elem[idx]);
 
        SiftDown(h, smallest);
    }
}

int isEmpty(MinHeap* h)
{
    return h->size == 0;
}

MinHeapNode* removeMin(MinHeap* h)
{
    if (isEmpty(h))
    {
        return NULL;
    }
 
    // Store the root node
    MinHeapNode* root = h->elem[0];
 
    // Replace root node with last node
    MinHeapNode* lastNode = h->elem[h->size - 1];
    h->elem[0] = lastNode;
 
    // Update position of last node
    h->pos[root->v] = h->size-1;
    h->pos[lastNode->v] = 0;
 
    // Reduce heap size and heapify root
    h->size--;
    SiftDown(h, 0);
 
    return root;   
}

void SiftUp(MinHeap* h, int v, int d)
{
    // Get the index of v in  heap elem
    int i = h->pos[v];
 
    // Get the node and update its d value
    h->elem[i]->d = d;
 
    // Travel up while the complete tree is not hepified.
    // This is a O(Logn) loop
    while (i && h->elem[i]->d < h->elem[(i - 1) / 2]->d)
    {
        // Swap this node with its parent
        h->pos[h->elem[i]->v] = (i-1)/2;
        h->pos[h->elem[(i-1)/2]->v] = i;
        swap(&h->elem[i],  &h->elem[(i - 1) / 2]);
 
        // move to parent index
        i = (i - 1) / 2;
    }
}

int isInMinHeap(MinHeap *h, int v)
{
    if (h->pos[v] < h->size)
    {
        return 1;
    }

   return 0;
}

void destroyMinHeap(MinHeap *h)
{
    int i;
    for (i = 0; i < h->size; i++)
    {
        free(h->elem[i]);
    }
    free(h->elem);
    free(h->pos);
    free(h);
}

#endif

