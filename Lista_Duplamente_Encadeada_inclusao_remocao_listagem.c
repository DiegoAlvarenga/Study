#include <stdio.h>
#include <stdlib.h>

float rendimento(float passado, float taxa, float *futuro){
	*futuro = passado*(1+taxa/100);
}

int main(int argc, char *argv[]){

	float passado, taxa, futuro;
	
	printf("\nDigite o valor a ser reajustado: ");
	scanf("%f", &passado);
			
	printf("Digite a taxa: ");
	scanf("%f", &taxa);
		
	printf("O valor reajustado e: %2.f", rendimento(passado, taxa, &futuro));

	
	
	
	return 0;
}

