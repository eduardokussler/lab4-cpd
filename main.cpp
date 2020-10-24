#include "hash.h"

#include <iostream>

using namespace std;

int main() {
  FILE* arq = fopen("nomes_10000.txt", "r");
  PolTabelaHashEADH* tabela = new PolTabelaHashEADH();
  string tmp = "";
  while(!feof(arq)){
    tmp = fgetc(arq);
  }
  return 0;
}