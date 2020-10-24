#include "hash.h"

#include <iostream>
#include <fstream>

using namespace std;

int main() {
  ifstream arq;
  arq.open("nomes_10000.txt");
  PolTabelaHashEADH* tabela = new PolTabelaHashEADH();
  string line = "";
  int i =0;
  // executa até encontrar EOF
  while(arq){
    getline(arq, line);
    if(line != ""){
      tabela->insere(line);
    }
  }
  arq.close();
  printf("Número de colisões durante construção da tabela: %d\n", tabela->colisoes);
  printf("Taxa de Ocupação: %d%% \n", (int)(tabela->taxaOcupacao() * 100));
  //Abre o arquivo de consultas e gera as estatísticas de saída
  arq.open("consultas.txt");

  return 0;
}