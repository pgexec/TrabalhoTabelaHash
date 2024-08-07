
#include "hash.h"

municipio* criarArrayMuni(int tam);
int comparar_nomeCidade(const void *a, const void *b);
void salvarDadosArray(char* nomeArquivo, municipio* municipios,  int MAX, int numeroMes);
void abrirTodosArquivosMuni(municipio* array, int tam);
void buscarTodosComBSearch(municipio *array, int tam);
int comparar_mesArquivo(const void *a, const void *b);
void buscarComBsearch(municipio* arrayB,int tam, int mes, char* nomeMuni);
int tamanhoArraySearch();
int qtdComparacao();
