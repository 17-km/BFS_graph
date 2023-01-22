#ifndef BFS_H
#define BFS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// pojedynczy wezel grafu
struct graphNode
{
    int value;
    struct graphNode *adjacentNode;
};

// krawedzie
struct graphEdge
{
    int first;
    int second;
};

struct graphNode **createGraph(int graphSize, int numberOfEdges, struct graphEdge *edges);

void printGraph(struct graphNode **graph, int graphSize);

void deleteNode(struct graphNode *node);

void deleteGraph(struct graphNode **graph, int graphSize);

int findDistance(struct graphNode **graph,int first, int second, bool *visitedNodes, int minDistance, int distance);

void clearVisitedNodes(bool *visitedNodes, int graphSize);

int distanceInGraph(struct graphNode **graph,int first, int second, int numberOfEdges, int graphSize);

#endif // BFS_H
