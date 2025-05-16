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

int is_valid(Node* n) {
    int i, j, num;
    // Validación de las filas
    for (i = 0; i < 9; i++) {
        int row_check[10] = {0};  // Arreglo para marcar los números de la fila(10 y no 9 ya que empezar con indice 0 no funcionaria)
        for (j = 0; j < 9; j++) {
            num = n->sudo[i][j];
            if (num != 0) {  // Si la casilla no está vacía
                if (row_check[num] == 1) {  // Si ya está marcado, la fila no es válida
                    return 0;
                }
                row_check[num] = 1;  // Marcar el número
            }
        }
    }
    
    // Validación de las columnas
    for (j = 0; j < 9; j++) {
        int col_check[10] = {0};  // Arreglo para marcar los números de la columna
        for (i = 0; i < 9; i++) {
            num = n->sudo[i][j];
            if (num != 0) {  // Si la casilla no está vacía
                if (col_check[num] == 1) {  // Si ya está marcado, la columna no es válida
                    return 0;
                }
                col_check[num] = 1;  // Marcar el número
            }
        }
    }
    
    // Validación de las submatrices 3x3
    for (int k = 0; k < 9; k++) {
        int sub_check[10] = {0};  // Arreglo para marcar los números de la submatriz 3x3
        for (int p = 0; p < 9; p++) {
            int i = 3 * (k / 3) + (p / 3);  // Calcular la fila dentro de la submatriz
            int j = 3 * (k % 3) + (p % 3);  // Calcular la columna dentro de la submatriz
            
            num = n->sudo[i][j];
            if (num != 0) {  // Si la casilla no está vacía
                if (sub_check[num] == 1) {  // Si ya está marcado, la submatriz no es válida
                    return 0;
                }
                sub_check[num] = 1;  // Marcar el número
            }
        }
    }

    return 1;  // Si no hemos encontrado ningún error, el nodo es válido
}


List* get_adj_nodes(Node* n) {
  List* list = createList();  // Crear la lista vacía que contendrá los nodos adyacentes
  
  // Paso 1: Buscar la primera casilla vacía (0) en el Sudoku
  int fila = -1;
  int col = -1;
  for (int i = 0; i < 9 && fila == -1; i++) {
    for (int j = 0; j < 9 && col == -1; j++) {
      if (n->sudo[i][j] == 0) {  // Si encontramos una casilla vacía
        fila = i;
        col = j;
        break;  // Romper el ciclo para no seguir buscando
      }
    }
  }

  // Si no se encuentra una casilla vacía, retornamos la lista vacía
  if (fila == -1 || col == -1) {
    return list;
  }

  // Paso 2: Generar nodos adyacentes con números del 1 al 9 en la casilla vacía
  for (int k = 1; k <= 9; k++) {
    Node* copia = copy(n);  // Copiar el nodo original
    copia->sudo[fila][col] = k;  // Colocar el número 'k' en la casilla vacía
    
    // Paso 3: Verificar si el nodo generado es válido
    if (is_valid(copia)) {  // Si el nodo es válido
      pushBack(list, copia);  // Agregar el nodo a la lista
    } else {
      free(copia);  // Si no es válido, liberar la memoria del nodo
    }
  }

  // Paso 4: Retornar la lista con los nodos válidos
  return list;
}



int is_final(Node* n) {
    // Recorremos todas las casillas del Sudoku
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (n->sudo[i][j] == 0) {  // Si encontramos una casilla vacía
                return 0;  // No es un nodo final, retornamos 0
            }
        }
    }
    return 1;  // Si no encontramos ninguna casilla vacía, es un nodo final
}


Node* DFS(Node* initial, int* cont){
  Stack* S = createStack();
  pushBack(S, initial) ;
  while(top(S) != NULL){
    cont++;
    Node* nodo = top(S);
    pop(S) ;
    if(is_final(nodo)) return nodo;
    List* nodos_adj = get_adj_nodes(nodo);
    Node *aux = first(nodos_adj) ;
    while(aux != NULL){
      push(S,aux);
      aux = next(nodos_adj) ;
    }
    free(nodo);
  }

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