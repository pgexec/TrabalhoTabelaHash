#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hash.h"

int contComparacoes = 0;
int contMaior = 0;
int totalComp = 0;


Hash* criarTabelaHash(int tam) 
{
    Hash* tabela = (Hash*) calloc(tam, sizeof(Hash));  
    if (tabela == NULL) 
	{
        printf("Erro ao alocar a memoria\n");
        return NULL;
    }
    return tabela;
}

int chaveFunctionHash(int chave, int MAX)
{
	float A = 0.6180339887;
	float val = chave * A;
	val = val - (int) val;
	return (int) (MAX * val);
}

int valorString(char* str)
{
	int valor = 7;
	int primo = 311;
	int tam = strlen(str);
	
	for(int i = 0; i < tam; i++)
	{
		valor = (2 * valor + (int) str[i]) % primo;
	}
	return valor;
}


void inserirNaTabelaHash(Hash* tabela, municipio m, int index) 
{
		
    Hash* novo = (Hash*) malloc(sizeof(Hash));
    if (novo == NULL) 
	{
        printf("Falha ao alocar memória para novo no\n");
        return;
    }
    novo->dados = m;
    novo->prox = NULL;
    
    if (tabela[index].prox == NULL) 
	{
        tabela[index].prox = novo;     
    } 
	else 
	{
        novo->prox = tabela[index].prox;
        tabela[index].prox = novo;
    }
}


void salvarDados(char* nomeArquivo, Hash* tabela, int tam, int numeroArquivo) 
{
	
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) 
	{
        printf("Erro ao abrir o arquivo\n");
        return;
    }
    
    char linha[1024] = {0};
    fgets(linha, sizeof(linha), arquivo);

    while (fgets(linha, sizeof(linha), arquivo)) 
	{	
    	municipio m;
    	memset(&m, 0, sizeof(m));
    	m.mesNumero = numeroArquivo;
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
			printf("Erro na leitura dos dados");
			continue;
		}
		
        int valor = valorString(m.nomeCidade);
        int index = chaveFunctionHash(valor, tam);
        if(index < 0 || index >= tam)
        {
        	printf("indice está incorreto");
        	return;
		}
        inserirNaTabelaHash(tabela, m, index);
    }

    fclose(arquivo);
   }


void abrirTodosArquivos(Hash* tabela, int tam)
{
	char nomeArquivo[20];
    for (int i = 1; i <= 12; i++) 
	{
        sprintf(nomeArquivo, "mes%d.csv", i);  
        salvarDados(nomeArquivo, tabela, tam, i);
    }
}



void exibirTodosDados(Hash* tabela, int tam, municipio* array, int tamArray) 
{
	
	
   for(int i = 0; i < tamArray; i++)
   {
  		ProcurarMunicipio(tabela, array[i].nomeCidade, array[i].mesNumero,tam);    	
   }
	printf("\ntotal de comparacao: %d", totalComp);
	printf("\nMaior comparacao: %d", contMaior);
	totalComp = 0;
	contMaior = 0;
}

void liberarTabelaHash(Hash* tabela, int tam) 
{
    if (tabela == NULL) 
	{
        return; 
    }

    for (int i = 0; i < tam; i++) 
	{
        Hash* atual = tabela[i].prox;  
        while (atual != NULL) 
		{
            Hash* temp = atual;
            atual = atual->prox;  
            free(temp);  
        }
    }
    free(tabela); 
}
	

void ProcurarMunicipio(Hash* tabela, char* nomeMuni, int numbMes, int tam)
{
	
	int valor = valorString(nomeMuni);
    int index = chaveFunctionHash(valor, tam);
      
    Hash* atual = tabela[index].prox;
    if(atual == NULL)
    {
    	printf("\nrealmente o erro está aqui");
	}
	
    int contComparacoes = 0;

    while (atual != NULL) 
	{
        
        if( (atual->dados.mesNumero == numbMes) && strcmp(atual->dados.nomeCidade, nomeMuni) == 0)
        {
        	contComparacoes++;
    		printf("\nMES:%d,\nCidade: %s, \nHomicidios: %d\n, Total de vitimas homicidio: %d\n, Latrocinio: %d\n, Furtos: %d\n, abigeatos: %d\n, Furto de Veiculos: %d\n, Roubo: %d\n, Roubo de Veiculos: %d\n Estelionato: %d\n Delitos c/ Armas: %d\n Entorpecentes: %d\n Vitima D/ Latrocinio: %d\n Vitima D/ Lesão: %d\n Total d/ Vitima Cvli: %d\n Comparações: %d\n", 
			atual->dados.mesNumero,
			atual->dados.nomeCidade, 
			atual->dados.homicidio, 
			atual->dados.totalVitimaHomi,
			atual->dados.latrocinio,
			atual->dados.furtos,
			atual->dados.abigeatos,
			atual->dados.furtoVeiculo,
			atual->dados.roubo,
			atual->dados.rouboVeiculos,
			atual->dados.estelionato,
			atual->dados.delitosArmas,
			atual->dados.entorpecentes,
			atual->dados.vitimaLatrocinio,
			atual->dados.vitimaLesao,
			atual->dados.totalVitimaCvli,
			contComparacoes);
			
		}
        atual = atual->prox;
        
        if(contMaior < contComparacoes)
        {
        	contMaior = contComparacoes;
		}
		totalComp += contComparacoes;
	}
}






