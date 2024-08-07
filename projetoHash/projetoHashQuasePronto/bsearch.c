#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bsearch.h"


int tamArray = 0;
int contagemComparacao = 0;
int comparacaoMaior = 0;
int totalComparacao = 0;


int qtdComparacao()
{
	return contagemComparacao = 0;
}


municipio* criarArrayMuni(int tam) 
{
    municipio* array = (municipio*) calloc(tam, sizeof(municipio));  
    if (array == NULL) 
	{
        printf("Erro ao alocar a memoria\n");
        return NULL;
    }
    return array;
}


int comparar_nomeCidade(const void *a, const void *b) 
{
	
    municipio *municipioA = (municipio *)a;
    municipio *municipioB = (municipio *)b;
    int resultado = strcmp(municipioA->nomeCidade, municipioB->nomeCidade);
    contagemComparacao++;
    if (resultado == 0)
	{ 
        return municipioA->mesNumero - municipioB->mesNumero; 
    }

    return resultado;
}

void abrirTodosArquivosMuni(municipio* array, int tam)
{
	char nomeArquivo[20];
    for (int i = 1; i <= 12; i++) 
	{
        sprintf(nomeArquivo, "mes%d.csv", i);  
        salvarDadosArray(nomeArquivo, array, tam, i);
    }
}


void salvarDadosArray(char* nomeArquivo, municipio* municipios,  int MAX, int numeroMes) 
{
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) 
	{
        printf("Erro ao abrir o arquivo %s\n", nomeArquivo);
        return;
    }
	
	
    char linha[1024];
    fgets(linha, sizeof(linha), arquivo);  

    while (fgets(linha, sizeof(linha), arquivo) && tamArray < MAX) 
	{
        municipio m;
        memset(&m, 0, sizeof(municipio));
        m.mesNumero = numeroMes;  
        linha[strcspn(linha, "\r\n")] = 0;  
		
		int linhasLidas = sscanf(linha,"%[^,],%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
                   m.nomeCidade, 
				   &m.homicidio, 
				   &m.totalVitimaHomi, 
				   &m.latrocinio, 
                   &m.furtos, 
				   &m.abigeatos, 
				   &m.furtoVeiculo, 
				   &m.roubo, 
                   &m.rouboVeiculos, 
				   &m.estelionato, 
				   &m.delitosArmas, 
				   &m.entorpecentes,
                   &m.vitimaLatrocinio, 
				   &m.vitimaLesao, 
				   &m.totalVitimaCvli);
		
		if(linhasLidas != 15)
		{
			printf("deu ruim ao ler");
			return;
		}
		
		
        if (tamArray < MAX) {
            municipios[tamArray] = m;   
            tamArray++;
        } 
		else 
		{
            printf("Limite de armazenamento alcançado durante a leitura de %s\n", nomeArquivo);
            break;
        }
    }
    fclose(arquivo);
}


void buscarComBsearch(municipio* arrayB,int tam, int mes, char* nomeMuni)
{
		
		municipio encontrar;
		strcpy(encontrar.nomeCidade, nomeMuni);
		encontrar.mesNumero = mes; 
		contagemComparacao = 0;
		
		municipio* achou = (municipio*) bsearch(&encontrar, arrayB, tam, sizeof(municipio), comparar_nomeCidade);		

		if(achou == NULL)																						
		{                                                                                                       	 
			printf("rapaz tem algo errado aqui, veio NULL"); 
			return;                                                	
		}
		
		printf("\n---------------------------------------\n"
		"Busca por %s no mês %d  \n"
		"Dados do Municipio:\n"
		"Nome da Cidade: %s\n"
		"Mes do Arquivo: %d\n"
		"Homicidios: %d\n"
		"Total de Vítimas de Homicídio: %d\n"
		"Latrocínios: %d\n"
		"Furtos: %d\n"
		"Abigeatos: %d\n"
		"Furto de Veículos: %d\n"
		"Roubos: %d\n"
		"Roubo de Veículos: %d\n"
		"Estelionatos: %d\n"
		"Delitos Relacionados a Armas: %d\n"
		"Entorpecentes: %d\n"
		"Vitimas de Latrocinio: %d\n"
		"Vitimas de Lesão: %d\n"
		"Total de Vitimas de Crimes Violentos Letais Intencionais (CVLI): %d\n"
		"Comparaçoes: %d",
		achou->nomeCidade, 
		achou->mesNumero, 
		achou->nomeCidade,
		achou->mesNumero,
		achou->homicidio,
		achou->totalVitimaHomi,
		achou->latrocinio,
		achou->furtos,
		achou->abigeatos,
		achou->furtoVeiculo,
		achou->roubo,
		achou->rouboVeiculos,
		achou->estelionato,
		achou->delitosArmas,
		achou->entorpecentes,
		achou->vitimaLatrocinio,
		achou->vitimaLesao,
		achou->totalVitimaCvli,
		contagemComparacao);
		
		if(comparacaoMaior < contagemComparacao)
		{
			comparacaoMaior = contagemComparacao;
		}
		
		totalComparacao += contagemComparacao;
		
}



void buscarTodosComBSearch(municipio *array, int tam) 
{
   	for(int i = 0; i < tam; i++)
	{
		buscarComBsearch(array,tam, array[i].mesNumero, array[i].nomeCidade);
	}		
	printf("\ntotal de comparacao: %d", totalComparacao);
	printf("\nMaior comparacao: %d", comparacaoMaior);
	totalComparacao = 0;
	comparacaoMaior = 0;
}

int tamanhoArraySearch()
{
	return tamArray;
}
