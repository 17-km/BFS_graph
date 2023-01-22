#include "BFS.h"

// tworzenie grafu
struct graphNode **createGraph(int graphSize, int numberOfEdges, struct graphEdge *edges)
{
    struct graphNode **graph;
    graph = (struct graphNode**) malloc (graphSize * sizeof(struct graphNode*));

    // dodanie podstawowych wezlow do grafu
    for (int i = 0; i < graphSize; i++)
    {
        struct graphNode *newNode = (struct graphNode*)malloc(sizeof(struct graphNode));
        newNode->value = i;
        newNode->adjacentNode = NULL;
        graph[i] = newNode;
    }

    // dodawanie krawedzi
    for (int i = 0; i < numberOfEdges; i++)
    {
        int first = edges[i].first;
        int second = edges[i].second;

        struct graphNode *newNode1 = (struct graphNode*)malloc(sizeof(struct graphNode));

        newNode1->value = second;
        newNode1->adjacentNode = NULL;

        if (graph[first]->adjacentNode == NULL)
        {
            graph[first]->adjacentNode = newNode1;
        }
        else
        {
            struct graphNode *parent = graph[first];
            struct graphNode *child = graph[first]->adjacentNode;

            while(1)
            {
                if (child->value == second)
                {
                    free(newNode1);
                    break;
                }
                else if (child->value > second)
                {
                    parent->adjacentNode = newNode1;
                    newNode1->adjacentNode = child;
                    break;
                }
                else
                {
                    if (child->adjacentNode == NULL)
                    {
                        child->adjacentNode = newNode1;
                        break;
                    }
                    else
                    {
                        parent = child;
                        child = child->adjacentNode;
                    }
                }
            }
        }

        struct graphNode *newNode2 = (struct graphNode*) malloc (sizeof(struct graphNode));
        newNode2->value = first;
        newNode2->adjacentNode = NULL;

        if (graph[second]->adjacentNode == NULL)
        {
            graph[second]->adjacentNode = newNode2;
        }
        else
        {
            struct graphNode *parent = graph[second];
            struct graphNode *child = graph[second]->adjacentNode;

            while(1)
            {
                if (child->value == first)
                {
                    free(newNode2);
                    break;
                }
                else if (child->value > first)
                {
                    parent->adjacentNode = newNode2;
                    newNode2->adjacentNode = child;
                    break;
                }
                else
                {
                    if (child->adjacentNode == NULL)
                    {
                        child->adjacentNode = newNode2;
                        break;
                    }
                    else
                    {
                        parent = child;
                        child = child->adjacentNode;
                    }
                }
            }
        }
    }

    return graph;
}

// wyswietla caly graf ze wszystkimi relacjami
void printGraph(struct graphNode **graph, int graphSize)
{
    for (int i = 0; i < graphSize; i++)
    {
        struct graphNode* node = graph[i]->adjacentNode;
        printf("%d:\t", i);

        while (node != NULL)
        {
            printf("(%d - %d)  \t", i, node->value);
            node = node->adjacentNode;
        }

        printf("\n");
    }
}

void deleteNode(struct graphNode *node)
{
    if(node != NULL)
    {
        deleteNode(node->adjacentNode);
    }
    free(node);
}

void deleteGraph(struct graphNode **graph, int graphSize)
{
    for (int i = 0; i < graphSize; i++)
    {
        deleteNode(graph[i]);
    }
    free(graph);
}

int findDistance(struct graphNode **graph,int first, int second, bool *visitedNodes, int minDistance, int distance)
{
    if (graph[first]->value == second)
    {
        if (distance <= minDistance) minDistance = distance;
        //printf("dystans %d \n",distance);
    }
    else
    {
        visitedNodes[graph[first]->value] = true;
        struct graphNode *childNode = graph[first];

        while (childNode->adjacentNode != NULL)
        {
            childNode = childNode->adjacentNode;
            if (visitedNodes[childNode->value] == false)
            {
                //printf("wchodze %d %d \n",first,childNode->value);
                minDistance = findDistance(graph,childNode->value,second,visitedNodes,minDistance,distance+1);
            }
        }
    }

    return minDistance;
}

void clearVisitedNodes(bool *visitedNodes, int graphSize)
{
    for (int i = 0; i < graphSize; i++)
    {
        visitedNodes[i] = false;
    }
}

int distanceInGraph(struct graphNode **graph,int first, int second, int numberOfEdges, int graphSize)
{
    bool *visitedNodes;
    visitedNodes = (bool*) malloc (graphSize * sizeof(bool));
    clearVisitedNodes(visitedNodes,graphSize);
    int distance = findDistance(graph,first,second,visitedNodes,numberOfEdges+1,0);
    free(visitedNodes);
    if (distance == numberOfEdges+1) distance = -1;
    return distance;
}
