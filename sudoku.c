#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){

    return 1;
}


List* get_adj_nodes(Node* n) {
    List* list = createList();  // Crear una lista para almacenar los nodos adyacentes
    int found_empty = 0;  // Variable para indicar si hemos encontrado una casilla vacía

    // Buscar la primera casilla vacía (un 0) en el tablero de Sudoku
    for (int i = 0; i < 9 && !found_empty; i++) {
        for (int j = 0; j < 9 && !found_empty; j++) {
            if (n->sudo[i][j] == 0) {  // Si encontramos una casilla vacía
                found_empty = 1;  // Marcamos que encontramos una casilla vacía

                // Generamos los nodos adyacentes reemplazando la casilla vacía por números del 1 al 9
                for (int num = 1; num <= 9; num++) {
                    Node* adj_node = copy(n);  // Copiamos el nodo original
                    adj_node->sudo[i][j] = num;  // Reemplazamos el 0 por el número
                    add_to_list(list, adj_node);  // Agregamos el nodo a la lista
                }
            }
        }
    }

    return list;  // Devolvemos la lista de nodos adyacentes
}


int is_final(Node* n){
    return 0;
}

Node* DFS(Node* initial, int* cont){
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/