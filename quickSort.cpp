#include "quickSort.h"

static void troca (ITEM_VENDA *itens, int i, int j) {
  ITEM_VENDA element = itens[i];
  itens[i] = itens[j];
  itens[j] = element;
}

static int partition (ITEM_VENDA *itens, int p, int r) {
  ITEM_VENDA pivot;
  int i, j;
  
  pivot = itens[r];
  i = p-1;

  for (j = p; j < r; j++) {
    if (itens[j].id <= pivot.id) {
      i++;
      troca(itens, i, j);
    }
  }

  troca(itens, i+1, r);
  return i+1;
}

void quickSort (ITEM_VENDA *itens, int left, int right) {
  int q;

  if (left < right) {
    q = partition(itens, left, right);
    quickSort(itens, left, q-1);
    quickSort(itens, q+1, right);
  }
}