// Programa C para inserir um nó na árvore AVL
#include<stdio.h> 
#include<stdlib.h>
#include <locale.h>
#define COUNT 10

// Um nó de árvore AVL  
struct Arvore 
{ 
	float key; 
	struct Arvore *left; 
	struct Arvore *right; 
	int height; 
};


struct Arvore *raiz = NULL;

// Uma função para obter a altura da árvore  
int height(struct Arvore *N) 
{ 
	if (N == NULL) 
		return 0; 
	return N->height; 
} 

// Uma função para obter um máximo
float max(float a, float b) 
{ 
	return (a > b)? a : b; 
}

// Uma função para obter um minimo
float min(float a, float b) 
{ 
	return (a < b)? a : b; 
}



//Função que atribui um novo nó com o valor inserido e NULL aos ponteiros esquerdo e direito.
struct Arvore* newArvore(float key) { 
	struct Arvore* node = (struct Arvore*) malloc(sizeof(struct Arvore)); 
	node->key = key; 
	node->left = NULL; 
	node->right = NULL; 
	node->height = 1; // novo nó é inicialmente adicionado na folha 
	return(node); 
} 


/* Visualização das rotações:

T1, T2 e T3 são sub-árvores enraizadas em y (no lado esquerdo) ou x (no lado direito)

     y                               x
    / \     Rotação a direita       /  \
   x   T3   - - - - - - - >        T1   y 
  / \       < - - - - - - -            / \
 T1  T2     Rotação a esquerda       T2  T3
 
  */ 
  
// Função para rotação à direita da sub-árvore enraizada em y 
struct Arvore *rightRotate(struct Arvore *y) 
{ 
	struct Arvore *x = y->left; 
	struct Arvore *T2 = x->right; 

	// Rotação a direita 
	x->right = y; 
	y->left = T2; 

	// Atualizar alturas 
	y->height = max(height(y->left), height(y->right))+1; 
	x->height = max(height(x->left), height(x->right))+1; 

	// Retorna nova raiz
	return x; 
} 

/* Visualização das rotações:

T1, T2 e T3 são sub-árvores enraizadas em y (no lado esquerdo) ou x (no lado direito)

     y                               x
    / \     Rotação a direita       /  \
   x   T3   - - - - - - - >        T1   y 
  / \       < - - - - - - -            / \
 T1  T2     Rotação a esquerda       T2  T3
 
  */ 

// Função para rotação à esquerda da sub-árvore enraizada em x 
struct Arvore *leftRotate(struct Arvore *x) 
{ 
	struct Arvore *y = x->right; 
	struct Arvore *T2 = y->left; 

	// Rotação a esquerda 
	y->left = x; 
	x->right = T2; 

	// Atualizar alturas 
	x->height = max(height(x->left), height(x->right))+1; 
	y->height = max(height(y->left), height(y->right))+1; 

	// Retorna nova raiz
	return y; 
} 

// Obter fator de balanceamento do nó N
int getBalance(struct Arvore *N) 
{ 
	if (N == NULL) 
		return 0; 
	return height(N->left) - height(N->right); 
} 

// Função recursiva para inserir na sub-árvore enraizada com o nó e retorna a nova raiz da sub-árvore
struct Arvore* incluir(struct Arvore* node, float key) 
{ 
	// 1. Realiza a inserção normal da BST
	if (node == NULL) // se vazio, cria nova árvore
		return(newArvore(key)); 

	if (key < node->key) //se menor, insere a esquerda
		node->left = incluir(node->left, key); 
	else if (key > node->key) // se maior,  insere a direita
		node->right = incluir(node->right, key); 
	else // Se igual, retorna o mesmo nó
		return node; 

	// 2. Atualiza a altura do nó ancestral
	node->height = 1 + max(height(node->left), 
						height(node->right)); 

	// 3. Obter o fator de balanceamento do nó ancestral para verificar se este nó se tornou desequilibrado 
	int balance = getBalance(node); 

		// Se o nó se desequilibrar, então um dos quatro casos abaixo irá ocorrer


		// Esquerda esquerda
		/*
	
		T1, T2, T3 and T4 são sub-árvores
		
 	        z                                       y 
 	       / \                                   /     \
 	      y   T4      Rotação a direita (z)     x       z
	      / \          - - - - - - - - ->      /  \    /  \ 
 	    x   T3                               T1  T2  T3  T4
 	   / \
 	 T1   T2
	
		*/
	//y é filho a esquerda de z e x é filho a esquerda de y 
	if (balance > 1 && key < node->left->key) 
		return rightRotate(node); 

	// Direita direita
	/*
	
		   z                                  y
         /  \                               /   \ 
		T1   y     Rotação a esquerda(z)  z      x
 		   /  \  	- - - - - - - ->     / \    / \
 		 T2   x     	               T1  T2 T3  T4
 	 	     / \
 		    T3  T4
	
	*/ 
	
	//y é filho a direita de z e x é filho a direita de y 
	if (balance < -1 && key > node->right->key) 
		return leftRotate(node); 

	// Esquerda direita
	
	/*
	
	     z                               z                         	 	   x
	    / \                            /   \                            /    \ 
	   y   T4  Rotação a esquerda(y)  x    T4  Rotação a direita(z)    y      z
	  / \      - - - - - - - - ->    /  \      - - - - - - - ->		  / \    / \
	T1   x                          y    T3                    		T1  T2 T3  T4
	    / \                        / \
	  T2   T3                    T1   T2
	
	*/ 
	
	//y é filho a esquerda de z e x é filho a direita de y
	if (balance > 1 && key > node->left->key) 
	{ 
		node->left = leftRotate(node->left); 
		return rightRotate(node); 
	} 

	// Direita esquerda
	
	/*
	
	   z                             z                                    x
	  / \                           / \                                 /   \ 
	T1   y   Rotação a direita(y) T1   x      Rotação a esquerda(z)   z      y
	    / \  - - - - - - - - ->      /  \       - - - - - - - ->     / \    / \
	   x   T4                       T2   y                         T1  T2  T3  T4
	  / \                               /  \
	T2   T3                            T3   T4
	
	*/
	 
	 //y é filho a direita de z e x é filho a esquerda de y
	if (balance < -1 && key < node->right->key) 
	{ 
		node->right = rightRotate(node->right); 
		return leftRotate(node); 
	} 

	//  retornar o ponteiro (inalterado) do nó 
	return node; 
} 

// Uma função de utilidade para imprimir a travessia da árvore antes da solicitação
void preOrder(struct Arvore *raiz) 
{ 
	if(raiz != NULL) 
	{ 
		printf("%.2f", raiz->key); 
		preOrder(raiz->left); 
		preOrder(raiz->right); 
	} 
} 


// Função para imprimir árvore binária em 2D  
// Faz travessia inversa
void print2DUtil(struct Arvore *raiz, int space){ 

	int i;
	// Caso base 
	if (raiz == NULL) 
		return; 

	// Aumeta distancia entre níveis
	space += COUNT; 

	// Processar primeiro a criança a direita 
	print2DUtil(raiz->right, space); 

	// Imprimir nó atual após espaço
	// count 
	printf("\n"); 
	for (i = COUNT; i < space; i++) 
		printf(" "); 
	printf("%.2f\n", raiz->key); 

	// Processar a criança a esquerda
	print2DUtil(raiz->left, space); 
} 

// Wrapp print2DUtil() 
void print2D(struct Arvore *raiz){ 
// Passar espaço inicial countar como 0 
print2DUtil(raiz, 5); 
}


// Funçao de busca 
struct Arvore* search(struct Arvore* raiz, float key) 
{ 
    // A raiz é nula ou o dado está presente na raiz 
    if (raiz == NULL || raiz->key == key) 
       return raiz; 
     
    // O dado é maior que a raiz
    if (raiz->key < key) 
       return search(raiz->right, key); 
  
    // O dado é menor que a raiz
    return search(raiz->left, key);
} 

// Retorna o  nó com valor mínimo encontrado nessa árvore. 
struct Arvore * minValueArvore(struct Arvore* node) 
{ 
    struct Arvore* current = node; 
  
    // loop down para encontrar a folha mais à esquerda
    while (current->left != NULL) 
        current = current->left; 
  
    return current; 
} 


//função recursiva para apagar um nó Retorna raiz da sub-árvore modificada. 
struct Arvore* remover(struct Arvore* raiz, float key) 
{ 
    // PASSO 1: EXECUTAR BST APAGAR PADRÃO  
  
    if (raiz == NULL) 
        return raiz; 
  
    // Se o elelemtno eliminado for menor do que a raiz, está na sub-árvore esquerda 
    if ( key < raiz->key ) 
        raiz->left = remover(raiz->left, key); 
  
	 // Se o elelemtno eliminado for maior do que a raiz, está na sub-árvore direita   
        else if( key > raiz->key ) 
        raiz->right = remover(raiz->right, key); 
  
    // O elemento for igual à raiz, então é o nó a ser eliminado  
    else
    { 
        // nó com apenas uma filho ou sem filho 
        if( (raiz->left == NULL) || (raiz->right == NULL) ) 
        { 
            struct Arvore *temp = raiz->left ? raiz->left : 
                                             raiz->right; 
  
            // sem filho 
            if (temp == NULL) 
            { 
                temp = raiz; 
                raiz = NULL; 
            } 
            else // um filho 
             *raiz = *temp; // copia o conteúdo do filho não vazio 
            free(temp); 
        } 
        else
        { 
            // nódulo com dois filhos: Obter a ordem, sucessor(o menor da arvore direita) 
            struct Arvore* temp = minValueArvore(raiz->right); 
  
            // Copiar os dados do sucessor da ordem para este nó  
            raiz->key = temp->key; 
  
            // Apagar o sucessor da ordem 
            raiz->right = remover(raiz->right, temp->key); 
        } 
    } 
  
    // Se a árvore tinha apenas um nó, então retorna 
    if (raiz == NULL) 
      return raiz; 
  
    // PASSO 2: ATUALIZAR A ALTURA DO NÓ ATUAL 
    raiz->height = 1 + max(height(raiz->left), 
                           height(raiz->right)); 
  
    //PASSO 3: DETERMINAR O FATOR DE BALANCEAMENTO DESTE NODE (para verificar se este nó ficou desequilibrado)
    int balance = getBalance(raiz); 
  
    // Se este nó se tornar desequilibrado, então há 4 casos
  
    // esquerda esquerda 
    if (balance > 1 && getBalance(raiz->left) >= 0) 
        return rightRotate(raiz); 
  
    // esquerda direita 
    if (balance > 1 && getBalance(raiz->left) < 0) 
    { 
        raiz->left =  leftRotate(raiz->left); 
        return rightRotate(raiz); 
    } 
  
    // direita direita 
    if (balance < -1 && getBalance(raiz->right) <= 0) 
        return leftRotate(raiz); 
  
    // direita esquerda 
    if (balance < -1 && getBalance(raiz->right) > 0) 
    { 
        raiz->right = rightRotate(raiz->right); 
        return leftRotate(raiz); 
    } 
  
    return raiz; 
} 

// Uma função de utilidade para fazer a travessia na ordem da BST 
void inorder(struct Arvore *raiz) 
{ 
    if (raiz != NULL) 
    { 
        inorder(raiz->left); 
        printf("%.2f ", raiz->key); 
        inorder(raiz->right); 
    } 
} 


// Função para encontrar o maior valor (o mais a direita)
float maxValue(struct Arvore* node) 
{    

    struct Arvore* current = node; 
    while (current->right != NULL)  
        current = current->right; 
      
    return (current->key); 
} 

// Função para encontrar o menor valor (o mais a esquerda)
float minValue(struct Arvore* node) 
{    
 
    struct Arvore* current = node; 
    while (current->left != NULL)  
        current = current->left; 
      
    return (current->key); 
} 



//Função que imprime o maior e menor valor
void limites(struct Arvore *node)
{
	struct Arvore* current = node;
	printf("\n\nMaior nota: %.2f\n", maxValue(node));
    printf("\nMenor nota: %.2f\n", minValue(node));
}


void menu(){
    
    printf("\n\n----------MENU----------\n");    

    printf("1 - Inserir\n");
    printf("2 - Remover\n");
    printf("3 - Buscar\n");
    printf("4 - Exibir Arvore\n");

    printf("Digite uma opcao: ");
}







void main(){
 setlocale(LC_ALL, "Portuguese");	
	
 struct Arvore *raiz = NULL;
 struct Arvore *b;
 int op;
 float maior, menor, n;
 
  

    
    raiz = incluir(raiz, 9.75);
	raiz = incluir(raiz, 0.7);
	raiz = incluir(raiz, 7.8);
	raiz = incluir(raiz, 6.3);
	raiz = incluir(raiz, 8.4);
	raiz = incluir(raiz, 5.99);
	

  
  
  while(1){
  		menu:
        menu();

        scanf("%d", &op);
        getchar();

        switch(op){
            case 1: 
					printf("Digite uma nota válida: ");
    				scanf("%f", &n);
    				if(n>=0 && n<=10){
    					incluir(raiz, n);
            			print2D(raiz);
            			printf("\n\n\nArvore ordenada:\n\n");
            			inorder(raiz);
            			limites(raiz); 
					} else{
							printf("\n\Digite uma nota válida!\n");
					  } goto menu;				            	
                    break;
            case 2: 
					printf("Digite o numero que deseja remover: ");
    				scanf("%f", &n);
					remover(raiz, n);
                    printf("Pronto!\n");
                    getchar();
                    print2D(raiz);
                    printf("\n\n\nArvore ordenada:\n\n");
            		inorder(raiz);
            		limites(raiz);
                    break;
            case 3: printf("Digite o numero que deseja achar: ");
                    scanf("%f", &n);
                    getchar();
                    b = search(raiz, n);
                    if(b){
                        printf("Elemento encontrado: %d\n", b->key);
                    }
                    else{
                        printf("Elemento nao encontrado!\n");
                    }
                    b = NULL;
                    getchar();
                    break;
            case 4: printf("\nArvore:\n\n");
            		print2D(raiz);
            		printf("\n\n\nArvore ordenada:\n\n");
            		inorder(raiz);
            		limites(raiz);
            		break;
            default: printf("Opcao incorreta!\n");
                     getchar();
                     break;
        }
    }
  

printf("\nArvore balanceada:\n");
  print2D(raiz);
}

