#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <cmath>

using namespace std;



typedef struct dados {
  int chave;
  string nome;
  bool usado; //Se já foi usado alguma vez
  bool ocupado; // Se está sendo usado no momento
}DADOS;

// Classe hash que implementa hash polinomial para strings
// Com endereçamento aberto e linear probing
class PolTabelaHashEABL {
  //M - tamanho da tabela = 20011 para manter a taxa de ocupação em 0.5
  //e 20011 é o primeiro número primo maior igual a 20000
  static const int M = 20011;

  //N - numero de elementos = 10000
  static const int N = 10000;
  private: 
  
  unsigned int hash(string nome) {
    unsigned int chave = 0;
    int a = 37;
    for(int i = 0; i < nome.length(); i++){
      // Atribui um peso a cada caractere do nome
      chave += (int)nome[i] * (int)pow(a, i);
    }
    return chave % M;
  }
  DADOS tabela[M];
  public: 
  PolTabelaHashEABL() = default;
  void insere(string nome) {
    unsigned int hash = PolTabelaHashEABL::hash(nome);
    // Chave é o código hash inicial, resultado do polinomio.    
    unsigned int chave = hash;
    // Procura a primeira posição livre
    while(tabela[hash].ocupado){
      hash++;
      if (hash >= M){
        hash = 0;
      }
    }
    tabela[hash].ocupado = true;
    tabela[hash].chave = chave;
    tabela[hash].nome = nome;
    tabela[hash].usado = true;
  }
  int busca(string nome) {
    int hash = PolTabelaHashEABL::hash(nome);
    int chave = hash;
    int tentativas = 0;
    do {
      if(tabela[hash].usado){
        tentativas++;
        if((tabela[hash].ocupado) && (tabela[hash].chave == chave) && (tabela[hash].nome == nome)){
          break;
        }else {
          hash = (hash % M)+1;
        }
      }else {
        tentativas = -1;
        break;
      }
    }while(chave != hash);
    return tentativas;
  }

};

// Classe hash que implementa hash polinomial para strings
// Com endereçamento aberto e duplo hashing
class PolTabelaHashEADH {
  //M - tamanho da tabela = 12007 já que o duplo hashing permite uma alta
  //taxa de ocupação  
  //e 12007 é o primeiro número primo maior igual a 20000
  static const int M = 12007;

  //N - numero de elementos = 10000
  static const int N = 10000;
  private: 
  unsigned int hash(string nome) {
    unsigned int chave = 0;
    int a = 37;
    for(int i = 0; i < nome.length(); i++){
      // Atribui um peso a cada caractere do nome
      chave += (int)nome[i] * (int)pow(a, i);
    }
    return chave % M;
  }
  DADOS tabela[M];
  public: 
  void insere(string nome) {
    unsigned int hash = PolTabelaHashEADH::hash(nome);
    unsigned int chave = hash;
  }
  int busca(string nome);
};

// Sem hash polinomial
// Endereçamento aberto com linear probing
class TabelaHashEABL {
  //M - tamanho da tabela = 20011 para manter a taxa de ocupação em 0.5
  //e 20011 é o primeiro número primo maior igual a 20000
  static const int M = 20011;

  //N - numero de elementos = 10000
  static const int N = 10000;
  private: 
  int hash(string nome);
  DADOS tabela[M];
  public: 
  void insere(string nome);
  int busca(string nome);
};
// Sem hash polinomial
// Com endereçamento aberto e duplo hashing
class TabelaHashEADH {
  //M - tamanho da tabela = 12007 já que o duplo hashing permite uma alta
  //taxa de ocupação  
  //e 12007 é o primeiro número primo maior igual a 20000
  static const int M = 12007;

  //N - numero de elementos = 10000
  static const int N = 10000;
  private: 
  int hash(string nome);
  DADOS tabela[M];
  public: 
  void insere(string nome);
  int busca(string nome);
};