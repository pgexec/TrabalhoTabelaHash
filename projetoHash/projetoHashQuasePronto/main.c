#include <stdio.h>
#include <string.h>
#include<stdbool.h>
#include <stdlib.h>
#include "bsearch.h"
#define MAX_ARRAY 5964  
#define MAX 9000

int main(int argc, char *argv[]) {
	
	int opcao;
	Hash* arrayHash = criarTabelaHash(MAX);
	municipio* arrayB = criarArrayMuni(MAX_ARRAY);
					
	if(arrayB == NULL)
	{
		printf("\nErro ao criar o array!\n");
		return 1;
	}
	printf("Array criado com sucesso.\n");
	
	if(arrayHash == NULL)
	{
		printf("\nErro ao criar a tabela!\n");
		return 1;
	}
	printf("Tabela hash criada com sucesso.\n");
	
	abrirTodosArquivosMuni(arrayB, MAX_ARRAY);
	qsort(arrayB, MAX_ARRAY, sizeof(municipio), comparar_nomeCidade);
	if(qtdComparacao() == 0)
	{
		printf("comparacoes zeradas!");
	}
	abrirTodosArquivos(arrayHash, MAX);
	 do{
	 	
 		printf("\n0 – SAIR");
		printf("\n1 – BUSCAR TUDO COM BSEARCH");
		printf("\n2 – BUSCAR TUDO COM TABELA HASH");
		printf("\n3 - PROCURAR UM COM BSEARCH");
		printf("\n4 – PROCURAR UM COM TABELA HASH");
		printf("\n5 – DADOS DA MEMORIA");
		printf("\ndigite: a opcao: ");
		scanf("%d", &opcao);
		
		
		switch(opcao)
		{
			case 1:
			{	
				buscarTodosComBSearch(arrayB, MAX_ARRAY);
				break;
			}
			
			case 2:
			{
				
				exibirTodosDados(arrayHash,MAX, arrayB,MAX_ARRAY);
				break;
			}
			
			case 3:
			{
				char nomeCidade[100];
				int numbMes = 0;
				printf("\nDigite o Nome da Cidade que deseja procurar: ");
				scanf(" %[^\n]s", nomeCidade);
				getchar();
				
				printf("\nDigite o Numero do Mes que deseja procurar: ");
				scanf("%d", &numbMes);
				getchar();
				
				buscarComBsearch(arrayB, MAX_ARRAY,  numbMes, nomeCidade);
				break;
			}
			
			case 4:
			{	
				
				char nomeCidade[100];
				int numbMes = 0;
				
				printf("\nDigite o Nome da Cidade que deseja procurar: ");
				scanf(" %[^\n]s", nomeCidade);
				getchar();
				
				printf("\nDigite o Numero do Mes que deseja procurar: ");
				scanf("%d", &numbMes);
				getchar();
				
				ProcurarMunicipio(arrayHash,nomeCidade, numbMes, MAX);
				break;
			}
			
			case 5:
			{
				printf("\ntamanho do array utilizado do bsearch e: %d", MAX_ARRAY);
				printf("\nquantos bytes o array de Bsearch ocupa: %d", sizeof(arrayB));
				printf("\ntamanho do array da tabela Hash: %d", MAX);
				printf("\nquantos bytes o array de Bsearch ocupa: %d", sizeof(arrayHash));
			}
		}
	 }
	 while(opcao != 0);
	
	liberarTabelaHash(arrayHash, MAX);
	
	return 0;
}
