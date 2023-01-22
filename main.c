#include <stdio.h>
#include <stdlib.h>

#include "BFS.h"

int getNumber()
{
    char decimal = getchar();
    bool sign = true;
    if (decimal == '-')
    {
        sign = false;
        decimal = getchar();
    }
    int number = 0;
    do
    {
        number = number * 10 + (int)(decimal - '0');
        decimal = getchar();
    }
    while (decimal != '\n' && decimal != ' ');
    if (!sign) number *= -1;
    return number;
}

// Directed graph implementation in C
int main(int argc,const char **argv)
{
    char command[3];
    int graphSize = 0;
    int numberOfEdges = 0;

    if(argc != 2)
    {
        fprintf(stderr, "Nie odczytano pliku z tekstem!\n");
        return -1;
    }

    FILE *textFile;
    if((textFile = fopen(argv[1], "r")) == NULL)
    {
        fprintf(stderr, "Blad w otwarciu pliku nr: %s", argv[0]);
    }

    int character;

    do
    {
        character = fgetc(textFile);
    }
    while(character == ' ');

    do
    {
        graphSize = graphSize*10 + character - '0';
        character = fgetc(textFile);
    }
    while(character != ' ' && character != '\n');

    do
    {
        character = fgetc(textFile);
    }
    while(character == ' ');

    do
    {
        numberOfEdges = numberOfEdges*10 + character - '0';
        character = fgetc(textFile);
    }
    while(character != ' ' && character != '\n');

    struct graphEdge *edges;
    edges = (struct graphEdge*) malloc (numberOfEdges * sizeof(struct graphEdge));

    for (int i = 0; i < numberOfEdges; i++)
    {
        edges[i].first = 0;
        edges[i].second = 0;
        do
        {
            character = fgetc(textFile);
        }
        while(character == ' ');

        do
        {
            edges[i].first = edges[i].first*10 + character - '0';
            character = fgetc(textFile);
        }
        while(character != ' ' && character != '\n');

        do
        {
            character = fgetc(textFile);
        }
        while(character == ' ');

        do
        {
            edges[i].second = edges[i].second*10 + character - '0';
            character = fgetc(textFile);
        }
        while(character != ' ' && character != '\n' && character != EOF);
    }

    fclose(textFile);

    struct graphNode **graph = createGraph(graphSize, numberOfEdges, edges);
    free(edges);

    // obsluga polecen
    while (1)
    {
        printf ("Podaj komende: ");

        command[0] = getchar();
        command[1] = getchar();
        command[2] = getchar();
        char ignore;
        do
        {
            ignore = getchar();
        }
        while(ignore != ' ' && ignore != '\n');


        if (command[0] == 'p' && command[1] == 'r' && command[2] == 'i')
        {
            printGraph(graph,graphSize);

        }
        else if (command[0] == 'd' && command[1] == 'i' && command[2] == 's')
        {
            int first = getNumber();
            int second = getNumber();
            int distance = distanceInGraph(graph,first,second,numberOfEdges,graphSize);
            printf("Odleglosc od %d do %d wynosi %d\n", first, second, distance);
        }
        else if (command[0] == 'q' && command[1] == 'u' && command[2] == 'i')
        {
            deleteGraph(graph,graphSize);
            exit(0);
        }
        else
        {
            fprintf(stderr, "Brak polecenia!\n");
        }
    }

    //printGraph(graph,graphSize);

    return 0;
}
