#include "quickSort.h"

static void troca (ITEM_VENDA *itens, int i, int j) {
  ITEM_VENDA element = itens[i]; // Elemento auxiliar
  itens[i] = itens[j]; // Troca
  itens[j] = element; // Troca
}

static int partition (ITEM_VENDA *itens, int p, int r) {
  ITEM_VENDA pivot; // Pivô
  int i, j;
  
  pivot = itens[r]; // Pivô é o último elemento
  i = p-1; // Índice do menor elemento

  for (j = p; j < r; j++) { // Percorre o vetor
    if (itens[j].id <= pivot.id) { // Se o elemento for menor ou igual ao pivô
      i++;
      troca(itens, i, j);
    }
  }

  troca(itens, i+1, r);
  return i+1;
}

void quickSort (ITEM_VENDA *itens, int left, int right) { //  Função de ordenação QuickSort
  int q;

  if (left < right) {
    q = partition(itens, left, right);
    quickSort(itens, left, q-1);
    quickSort(itens, q+1, right);
  }
}