#include "hash.h"

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

typedef struct nomeEcolisoes {
  string nome;
  int colisoes;
}CONSULTA;


int main() {
  ifstream arq;
  //Armazena os nomes encontrados na tabela hash e o numero de colisões
  std::vector<CONSULTA> encontrados; 
  int itEn;
  
  //Armazena os nomes não encontrados na tabela hash
  std::vector<CONSULTA> nEncontrados;

  //Numero total de colisões durante a busca
  int totCol = 0;
  int totEncontrados = 0;

  PolTabelaHashEADH* tabela = new PolTabelaHashEADH();
  string line = "";
  int i =0;
  arq.open("nomes_10000.txt");
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
  //Testa se encontrou ou não o nome na tabela
  //Pra não alterar a média
  int tmp;
  //Armazena temporariamente o nome para a inserção na lista
  CONSULTA temp;
  //Total de nomes consultados
  int totNomes = 0;
  while(arq){
    getline(arq,line);
    if(line != ""){
      totNomes++;
      tmp = tabela->busca(line);
      if (tmp != -1){
        totCol += tmp;
        totEncontrados++;
        //Salvando os dados na struc temporaria
        temp.colisoes = tmp;
        temp.nome = line;
        encontrados.push_back(temp);
      }else {
        temp.colisoes = tmp;
        temp.nome = line;
        nEncontrados.push_back(temp);
      }
      line = "";
    }
  }
  printf("\n\n");
  printf("Média de entradas verificadas durante a busca: %.2f\n", (float)totCol/totNomes);

  //Procurar o nome que mais causou colisões
  CONSULTA menosVerificacoes = encontrados[0];
  CONSULTA maisVerificacoes = encontrados[0];
  for(itEn = 1; itEn < encontrados.size(); itEn++){
    //Encontra o nome que gerou menos colisoes
    if(menosVerificacoes.colisoes > encontrados[itEn].colisoes){
      menosVerificacoes = encontrados[itEn];
    }
    //Encontra o nome que gerou mais colisoes
    if(maisVerificacoes.colisoes < encontrados[itEn].colisoes){
      maisVerificacoes = encontrados[itEn];
    }
  }

  printf("Nome que gerou menos colisões: %s, com %d colisões\n", menosVerificacoes.nome.c_str(), menosVerificacoes.colisoes);
  printf("Nome que gerou mais colisões: %s, com %d colisões\n", maisVerificacoes.nome.c_str(), maisVerificacoes.colisoes);
  //Imprimir a lista de nomes
  printf("\n\n");
  printf("Tamanho da lista de nomes encontrados: %ld \nNomes encontrados:\n",encontrados.size());
  for(itEn = 0; itEn < encontrados.size(); itEn++){
    printf("%s\n", encontrados[itEn].nome.c_str());
  }

  printf("\n\n");
  printf("Tamanho da lista de nomes não encontrados: %ld \nNomes não encontrados:\n",nEncontrados.size());
  for(itEn = 0; itEn < nEncontrados.size(); itEn++){
    printf("%s\n", nEncontrados[itEn].nome.c_str());
  }
  return 0;
}