#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define TAM_MAX	40

//Definição da estrutura de armazenamento.
typedef struct Item {
	int cod_cliente;
	char nome_cliente[TAM_MAX];
	int consumo;
	float preco_unitario;
	float valor_total;
	
	struct vencimento
	{
		int ano;
		int mes;
		int dia;
		}	dt_vencimento;

	struct Item *anterior; //ponteiro para estrutra anterior
	
} Conta_de_luz;

// Inicializa a pilha
void Inicializar(Conta_de_luz **topo) {
	// apontar para Null elimina o endereço de controle
	*topo = NULL;
}

// Verifica se a pilha está vazia (NULL)
int EstaVazia(Conta_de_luz **topo){
	if(*topo == NULL)
		return TRUE;
	else
		return FALSE;
}

//Empilha um novo elemento
//Não é necessário verificar se a planilha está cheia
void Empilhar(Conta_de_luz **topo, int codCliente, char nomeCliente[TAM_MAX], int consm, float precoUn, float valorTotal, int dd, int mm, int aaaa){
	//cria um novo elemento
	Conta_de_luz *novo;
	
	//aloca memória para o novo elemento
	novo = (Conta_de_luz *) malloc(sizeof(Conta_de_luz));
	
	//armazena o valor do novo elemento na nova estrutura
	novo->cod_cliente = codCliente;
	strcpy(novo->nome_cliente, nomeCliente);
	novo->consumo = consm;
	novo->preco_unitario = precoUn;
	novo->valor_total = valorTotal;
	novo->dt_vencimento.dia = dd;
	novo->dt_vencimento.mes = mm;
	novo->dt_vencimento.ano = aaaa;
	//novo->consumo equivale a (*novo).consumo que gets pointer membro consumo da struct novo
	
	//anterior recebe endereço do elemento anterior
	//o que estava no topo
	novo->anterior = *topo;
	
	//topo aponta para o endereço do novo elemento;
	*topo = novo;
}

// Desempilha um elemento
int Desempilhar(Conta_de_luz **topo){
	//cria uma estrutura auxiliar
	Conta_de_luz *antigo;
	
	// a estrutura auxiliar aponta para o elemento do topo da pilha
	antigo = *topo;
	float result; //define variável para o valor do elemento
	
	if(EstaVazia(topo)){ //verifica se a pilha esta vazia(NULL)
		printf("\n Pilha Vazia!\n");
		// se quiser sair caso a pilha esteja vazia, use: exit(1);
	}
	else { // -> Conta_de_luz retirado do topo
		
		result = (*topo)->cod_cliente; //recupera o valor do elemento
		
		//recupera o endereço do elemento anterior
		*topo = (*topo)->anterior;
		
		//libera a memória da estrutura auxiliar (elemento do topo da pilha)
		free(antigo);
		return result; // retorna o valor desempilhado
	}
}

void MostrarPilha(Conta_de_luz *topo){
	int i = 0; //contador de itens da pilha
	Conta_de_luz *item; // cria uma estrutura da pilha
	printf("\n\n Listando...\n\n");
	printf("---------------------------------\n");
	if (EstaVazia(&topo)){ //verifica se a pilha está vazia
		printf("A pilha esta vazia!\n");
	}
	else{ //item recebe o endereço do elemento do topo
	item = topo;
	// cabeçalho da pilha
	printf("\nItem 	Codigo Cliente	Nome Cliente	Consumo Kwh	Preco Unitario	Valor Total	Vencimento	Endereco Ativo		Endereco Anterior\n");
	// enquanto tiver elementos <> NULL
		while(item !=NULL){
			i++; //conta elementos
			//exibe elemento
			printf("[%2d] -> %d		%s		%d		%0.2f		%0.2f		%d/%d/%d	:%p	:%p\n", i, item->cod_cliente, item->nome_cliente, item->consumo, item->preco_unitario, item->valor_total, item->dt_vencimento.dia, item->dt_vencimento.mes, item->dt_vencimento.ano, item, item->anterior);  
			//item->consumo equivale a (*item).consumo que gets pointer  consumo da struct item
			
			// pega endereço do elemento anterior
			item = item->anterior;
		}
	}
	printf("---------------------------------\n\n\n");
}

//Menu de opções
void Menu(){
	printf("\n\nDigite a sua escolha: \n"
		"    1 - Empilhar elemento \n"
		"    2 - Desempilhar \n"
		"    3 - Finalizar \n"
		"?\n");
}



int main(){
	//Define uma estrutura para a pilha
	Conta_de_luz *topo = NULL;
	
	//Para a leitura da escolha do usuário
	int opcao;
	
	//Para a leitura e exibição do valor do elemento da pilha
	int cod_cliente;
	int consumo;
	float preco_unitario;
	float valor_total;
	char nome_cliente[TAM_MAX];
	int venc_dia, venc_mes, venc_ano;
	
	//Exibe o Menu
	Menu();
	
	// Faz a leitura da opção do usuário
	fflush(stdin);
	scanf("%d", &opcao);
	
	//Gerencia as escolhas do usúario
	while (opcao !=3){
		switch (opcao){
			case 1: //Lê o valor do novo elemento
				fflush(stdin);
				printf("Digite:\nCodigo do Cliente, Nome do Cliente, Consumo, Preco unitario, Valor total, Vencimento.\n");
				scanf("\n%d%s%d%f%f%d%d%d",&cod_cliente, &nome_cliente, &consumo, &preco_unitario, &valor_total, &venc_dia, &venc_mes, &venc_ano);
			
				// Empilha novo elemento
				Empilhar(&topo, cod_cliente, nome_cliente, consumo, preco_unitario, valor_total, venc_dia, venc_mes, venc_ano);
			
				//Mostra os elementos da pilha
				MostrarPilha(topo);
				break;
			
			case 2: // Desempilha
				preco_unitario = Desempilhar(&topo);
			
				// Exibe o valor desempilhado
				printf("\nCodigo do cliente desempilhado %d", cod_cliente);
			
				// Mostra os elementos da pilha
				MostrarPilha(topo);
				break;
			
			default:
				printf("Escolha invalida.\n\n");
				break;
		}
		fflush(stdin);
		// Exibe o Menu
		Menu();
	
		//Faz a leitura da opção do usuário
		scanf("%d", &opcao);
		
	} // encerra while
	

	return 0;
}

