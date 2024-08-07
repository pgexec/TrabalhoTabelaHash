

typedef struct municipio
{
	char nomeCidade[100];
	int mesNumero;
	int homicidio;
	int totalVitimaHomi;
	int latrocinio;
	int furtos;
	int abigeatos;
	int furtoVeiculo;	
	int roubo;
	int rouboVeiculos;
	int estelionato;
	int delitosArmas;
	int entorpecentes;
	int vitimaLatrocinio;
	int vitimaLesao;
	int totalVitimaCvli;
	int comparacoes;
	
}municipio;

typedef struct hash
{
	municipio dados;
	struct hash* prox;	
}Hash;

Hash* criarTabelaHash(int tam);

int valorString(char* str);
int chaveFunctionHash(int chave, int MAX);

void inserirNaTabelaHash(Hash* tabela, municipio m, int index);
void salvarDados(char* nomeArquivo, Hash* tabela, int tam, int numeroArquivo);


void abrirTodosArquivos(Hash* tabela, int tam);
void exibirTodosDados(Hash* tabela, int tam,municipio* array, int tamArray);
void liberarTabelaHash(Hash* tabela, int tam);
void ProcurarMunicipio(Hash* tabela, char* nomeMuni, int numbMes, int tam);
void ProcurarHashUm(Hash* tabela, char* nomeMuni, int numbMes, int tam);
