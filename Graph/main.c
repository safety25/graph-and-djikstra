#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct adjListNode {
  int neighbour;
  struct adjListNode* next;
}adjListNode;

typedef struct adjList {
  adjListNode* head;
}adjList;

adjListNode* newAdjListNode(int neighbour) {
  adjListNode* newNode = malloc(sizeof(adjListNode));
  newNode->neighbour = neighbour;
  newNode->next = NULL;
  return newNode;
}

typedef struct graph {
  int num_vertices;
  adjList* adjacency_lists;
}graph;

graph* createGraph(int v) {
  graph* g = malloc(sizeof(graph));
  g->num_vertices = v;
  g->adjacency_lists = malloc(v * sizeof(adjList));
  for (int i = 0; i < v; i++) {
    g->adjacency_lists[i].head = NULL;
  }
  return g;
}

void addEdge(graph* g, int center, int neighbour) {
  adjListNode* newNode = newAdjListNode(neighbour);
  newNode->next = g->adjacency_lists[center].head;
  g->adjacency_lists[center].head = newNode;
}

typedef struct City {
  int code;
  char name[30];
  int distance;
} City;

int readSehirData(char* fileName, City* sehirler) {
  FILE* fp = fopen(fileName, "r");
  if (fp == NULL) {
    perror("Error opening file");
    exit(1);
  }

  int plaka;
  char isim[30];
  int km;
  int numSehirler = 0;
  while (fscanf(fp, "%d %s %d", &plaka, isim, &km) == 3) {
    sehirler[numSehirler].code = plaka;
    strcpy(sehirler[numSehirler].name, isim);
    sehirler[numSehirler].distance = km;
    numSehirler++;
  }

  fclose(fp);

  return numSehirler;
}

graph* createNeighbourGraph(City* sehirler, int sehirSayisi, int maxDistance) {
  graph* g = createGraph(sehirSayisi);
  for (int i = 0; i < sehirSayisi; i++){
    for (int j = 0; j < sehirSayisi; j++){
      if (i != j && sehirler[i].distance <= sehirler[j].distance + maxDistance && sehirler[i].distance >= sehirler[j].distance - maxDistance) { // Distance ın mutlak değeri
        addEdge(g, i, j);
      }
    }
  }
  return g;
}

int neighbourCount(graph* g, int vertex) {
  int neighbours = 0;
  adjListNode* tmp = g->adjacency_lists[vertex].head;

  while (tmp != NULL) {
    neighbours++;
    tmp = tmp->next;
  }

  return neighbours;
}

void printCities(graph* g, City* cities){  
  for (int i = 0; i < g->num_vertices; i++){
    int komsu_sayisi = neighbourCount(g, i);
    printf("Sehir: %s, merkeze uzaklik: %d, komsu sayisi: %d, komsulari:", cities[i].name, cities[i].distance, komsu_sayisi);
    adjListNode* tmp = g->adjacency_lists[i].head;
    
    while (tmp != NULL){
      printf(" %s", cities[tmp->neighbour].name);
      tmp = tmp->next;
    }
    
    printf("\n");

  }
}


int main(){
  // Read the data from the sehir.txt file
  City sehirler[81];
  int sehir_sayisi = readSehirData("sehir.txt", sehirler);;
  
  // Create the graph based on the distance from Istanbul
  graph* g = createNeighbourGraph(sehirler, sehir_sayisi, 250);

  printCities(g, sehirler);

  return 0;
}