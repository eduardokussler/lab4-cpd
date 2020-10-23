#include "hash.h"

#include <iostream>

using namespace std;

int main() {
  PolTabelaHashEABL* tabela1 = new PolTabelaHashEABL();
  tabela1->insere("Eduardo Kussler");
  printf("\n%d", tabela1->busca("Eduardo Kussler"));
  tabela1->insere("Kussler odraudE");
  printf("\n%d", tabela1->busca("Kussler odraudE"));
  return 0;
}