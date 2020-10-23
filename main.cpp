#include "hash.h"

#include <iostream>

using namespace std;

int main() {
  PolTabelaHashEADH* tabela1 = new PolTabelaHashEADH();
  tabela1->insere("Eduardo Kussler");
  printf("\n%d", tabela1->busca("Eduardo Kussler"));
  tabela1->insere("Kussler Eduardo");
  printf("\n%d", tabela1->busca("Kussler Eduardo"));
  return 0;
}