#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <cmath>

using namespace std;



typedef struct dados {
  int chave;
  string nome;
  bool usado = false; //Se já foi usado alguma vez
  bool ocupado = false; // Se está sendo usado no momento
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
    return chave;
  }
  DADOS tabela[M];
  public: 
  PolTabelaHashEABL() = default;
  void insere(string nome) {
    // Chave é o código hash inicial, resultado do polinomio.    
    unsigned int chave = PolTabelaHashEABL::hash(nome);
    // Procura a primeira posição livre
    unsigned int hash = chave % M;
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
    int chave = PolTabelaHashEABL::hash(nome);
    int hash = chave % M;
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

  //Número primo para a segunda função de hash
  static const int a = 11971;
  private: 
  unsigned int hash(string nome) {
    unsigned int chave = 0;
    int a = 37;
    for(int i = 0; i < nome.length(); i++){
      // Atribui um peso a cada caractere do nome
      chave += (int)nome[i] * (int)pow(a, i);
    }
    return chave;
  }
  DADOS tabela[M];
  public: 
  PolTabelaHashEADH() = default;
  int colisoes = 0;
  void insere(string nome) {
    unsigned int chave = PolTabelaHashEADH::hash(nome);
    unsigned int hash;
    int i = 0;
    do{
      //segundo hash em caso de colisão
      hash = (chave + (i *(chave % a))) % M; 
      i++;
    }while(tabela[hash].ocupado);
    colisoes += i;
    tabela[hash].ocupado = true;
    tabela[hash].usado = true;
    tabela[hash].nome = nome;
    tabela[hash].chave = chave;
  }
  int busca(string nome) {
    unsigned int chave = PolTabelaHashEADH::hash(nome);
    unsigned int hash;
    int tentativas = 0;
    int i = 0;
    do {
      hash = (chave + (i *(chave % a))) % M; 
      tentativas++;
      if(tabela[hash].usado){
        if((tabela[hash].ocupado) && (tabela[hash].chave == chave) && (tabela[hash].nome == nome)){
          break;
        } else {
          i++;
        }
      }else {
        tentativas = -1;
        break;
      }
    } while(tabela[hash].usado);

    return tentativas;
  }

  double taxaOcupacao(){
    int ocupados = 0;
    for(int i = 0 ; i < M; i++){
      if(tabela[i].ocupado){
        ocupados++;
      }
    }
    return (double) ocupados/M;
  }
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
  unsigned int hash(string nome) {
    unsigned int chave = 0;
    for (int i = 0; i < nome.length(); i++){
      chave += (int)nome[i];
    }
    return chave;
  }
  DADOS tabela[M];
  public: 
  TabelaHashEABL() = default;
  void insere(string nome) {
    unsigned int chave = TabelaHashEABL::hash(nome);
    unsigned int hash = chave % M;
    while(tabela[hash].ocupado){
      hash++;
    }
    tabela[hash].ocupado = true;
    tabela[hash].usado = true;
    tabela[hash].nome = nome;
    tabela[hash].chave = chave;
  }
  int busca(string nome) {
    unsigned int chave = TabelaHashEABL::hash(nome);
    unsigned int hash = chave % M;
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
// Sem hash polinomial
// Com endereçamento aberto e duplo hashing
class TabelaHashEADH {
  //M - tamanho da tabela = 12007 já que o duplo hashing permite uma alta
  //taxa de ocupação  
  //e 12007 é o primeiro número primo maior igual a 12000
  static const int M = 12007;
  //Número primo para a segunda função de hash
  static const int a = 11971;

  //N - numero de elementos = 10000
  static const int N = 10000;
  private: 
  unsigned int hash(string nome) {
    unsigned int chave = 0;
    for (int i = 0; i < nome.length(); i++){
      chave += (int)nome[i];
    }
    return chave;
  }
  DADOS tabela[M];
  public:
  string getNome(int pos){
    return tabela[pos].nome;
  } 
  TabelaHashEADH() = default;
  void insere(string nome) {
    unsigned int chave = TabelaHashEADH::hash(nome);
    unsigned int hash;
    int i = 0;
    do{
      //segundo hash em caso de colisão
      hash = (chave + (i *(chave % a))) % M; 
      i++;
    }while(tabela[hash].ocupado);

    tabela[hash].ocupado = true;
    tabela[hash].usado = true;
    tabela[hash].nome = nome;
    tabela[hash].chave = chave;
  }
  int busca(string nome) {
    unsigned int chave = TabelaHashEADH::hash(nome);
    unsigned int hash;
    int tentativas = 0;
    int i = 0;
    do {
      hash = (chave + (i *(chave % a))) % M; 
      tentativas++;
      if(tabela[hash].usado){
        if((tabela[hash].ocupado) && (tabela[hash].chave == chave) && (tabela[hash].nome == nome)){
          break;
        } else {
          i++;
        }
      }else {
        tentativas = -1;
        break;
      }
    } while(tabela[hash].usado);

    return tentativas;
  }
};