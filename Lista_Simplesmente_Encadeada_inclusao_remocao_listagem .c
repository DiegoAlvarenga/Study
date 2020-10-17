#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>


#define TAM_MAX 40

struct no {
  int valor;

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


  struct no *proximo;
};

void Inserir();
void Exibir();
void Desenfileirar();
int Contar();
void Percorrer_Fila();
void Menu();
void Exibir_Elemento();
void Inserir_Dentro();

typedef struct no NO_DADOS;

NO_DADOS *ultimo_no, *primeiro_no, *no_temp = 0, *novo_no, *anterior_no, proximo_no;
int dado, consm, dd, mm, aaaa, escolha, opcao;
char nomeCliente[TAM_MAX];
float precoUn, valorTotal;


void Menu(){

    printf("\nFila Simplesmente Encadeada\n");
	
    	do  {

    printf("\nOpcoes\n\n");
    printf("1 : Inserir na Fila \n");
    printf("2 : Apaga da Fila \n");
    printf("3 : Exibe Fila\n");
    printf("4 : Contar Fila\n");
    printf("5 : Percorrer Fila\n");
    printf("Outras : Sair()\n");
    printf("Digite a opcao:\n");
    fflush(stdin);
    scanf("%d", &opcao);
	fflush(stdin);
	switch (opcao) {
      case 1:
        Inserir();
        Exibir();
        break;
      case 2:
        Desenfileirar();
        Exibir();
        break;
      case 3:
        Exibir();
        break;
      case 4:
        Contar();
        break;
      case 5:
      	Percorrer_Fila();
      	break;
      default:
      	break;
    }
  } while (opcao);
}
void Inserir() {

  printf("\nDigite:\n Nome 		Consumo		Preco Unitario		Valor Total		Vencimento\n");
  scanf("%s%d%f%f%d%d%d", nomeCliente, &consm, &precoUn, &valorTotal, &dd, &mm, &aaaa );

  no_temp = (NO_DADOS *) malloc(sizeof (NO_DADOS));


  strcpy(no_temp->nome_cliente, (nomeCliente));
  
  no_temp->consumo = consm;
  no_temp->preco_unitario = precoUn;
  no_temp->valor_total = valorTotal;
  no_temp->dt_vencimento.dia = dd;
  no_temp->dt_vencimento.mes = mm,
  no_temp->dt_vencimento.ano =aaaa;

  if (primeiro_no == 0) {
    primeiro_no = no_temp;
  } else {
    ultimo_no->proximo = no_temp;

  }
  no_temp->proximo = 0;
  ultimo_no = no_temp;
  fflush(stdin);
}
void Inserir_Dentro() {

  printf("\nDigite:\n Nome 		Consumo		Preco Unitario		Valor Total		Vencimento\n");
  scanf("%s%d%f%f%d%d%d", nomeCliente, &consm, &precoUn, &valorTotal, &dd, &mm, &aaaa );

  novo_no = (NO_DADOS *) malloc(sizeof (NO_DADOS));

  strcpy(novo_no->nome_cliente, nomeCliente);
  novo_no->consumo = consm;
  novo_no->preco_unitario = precoUn;
  novo_no->valor_total = valorTotal;
  novo_no->dt_vencimento.dia = dd;
  novo_no->dt_vencimento.mes = mm,
  novo_no->dt_vencimento.ano =aaaa;

  

  novo_no->proximo = no_temp->proximo;
  no_temp->proximo = novo_no;
  fflush(stdin);
}
void Desenfileirar(){
	// verifica se a fila está vazia
	if(primeiro_no==0){
		printf("Fila Vazia.");
	} 
	// pega o endereço do primeiro elemento da fila
	// aquele que será retirado
	
	no_temp= primeiro_no;
	// o endereço do próximo elemento passa a ser o início da fila
	primeiro_no = primeiro_no->proximo;
	
	
	// se a fila ficar vazia
	if(primeiro_no==NULL)
		ultimo_no= NULL;

	// libera a memória do elemento retirado
	free(no_temp);
}
void Exibir() {
  int contar = 0;
  no_temp = primeiro_no;
  printf("\nExibir Fila : \n");

  while (no_temp != 0) {
    //printf("\nNome: %s\nConsumo: %d\nPreco Unitario: %f\nValor Total: %f\nVencimento: %d/%d/%d\nMemoria:	%p >>>>> %p\n___________\n", no_temp->nome_cliente, no_temp->consumo, no_temp->preco_unitario, no_temp->valor_total, no_temp->dt_vencimento.dia, no_temp->dt_vencimento.mes, no_temp->dt_vencimento.ano, no_temp, no_temp->proximo);
    Exibir_Elemento();
	contar++;
    no_temp = no_temp -> proximo;
  }
  printf("\nNo de Items na Fila : %d\n", contar);
}
void Percorrer_Fila(){
	int continua = -1;
	opcao = -1;
	if(primeiro_no==NULL){
		printf(" Fila Vazia!\n");
		Menu();
		return;
	}
	no_temp = primeiro_no;
	printf("\n Primeiro Elemento da Fila:");
	Exibir_Elemento(no_temp);
	do{
		printf("\n Percorrer Fila;\n");
		printf("  0 Voltar;\n");
		printf("  1 Proximo;\n");
		printf("  2 Adicionar Elemento;\n");
		fflush(stdin);
		scanf("%d", &escolha);
		fflush(stdin);
		switch(escolha){
			case 0:
			 continua=0;
			 break;
			case 1:
			 if(no_temp->proximo!= NULL){
				no_temp = no_temp->proximo;
				Exibir_Elemento(no_temp);
			}else{
				printf("FIM DA FILA!");}
			break;
			case 2:
				Inserir_Dentro();
				Exibir();
				Menu();
				
			break;
			default:printf(" Opção Inválida!\n");
			
		}
	}while(continua);
	Menu();
}
int Contar() {
  int contar = 0;
  no_temp = primeiro_no;
  while (no_temp != 0) {
    contar++;
    no_temp = no_temp -> proximo;
  }
  printf("\nNo de Items na Fila : %d\n", contar);
  return contar;
}
void Exibir_Elemento(){
	printf("\n*****************************************************************************");
	printf("\n");
	printf("End Atual:%8p ", no_temp);
	printf("\nNome: %s\nConsumo: %d\nPreco Unitario: %0.2f\nValor Total: %0.2f\nVencimento: %d/%d/%d\n", no_temp->nome_cliente, no_temp->consumo, no_temp->preco_unitario, no_temp->valor_total, no_temp->dt_vencimento.dia, no_temp->dt_vencimento.mes, no_temp->dt_vencimento.ano);
	printf("End Proximo:%8p ", no_temp->proximo);
	printf("\n*****************************************************************************");
}	
int main() {
    Menu();
  return 0;
}
