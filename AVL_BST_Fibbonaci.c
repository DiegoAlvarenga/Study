// Programa C para inserir um nó na árvore AVL
#include<stdio.h> 
#include<stdlib.h> 
#define COUNT 10

// Um nó de árvore AVL  
struct Node 
{ 
	int key; 
	struct Node *left; 
	struct Node *right; 
	int height; 
}; 


// Uma função para obter a altura da árvore  
int height(struct Node *N) 
{ 
	if (N == NULL) 
		return 0; 
	return N->height; 
} 

// Uma função para obter um máximo de dois inteiros  
int max(int a, int b) 
{ 
	return (a > b)? a : b; 
} 

//Função que atribui um novo nó com o valor inserido e NULL aos ponteiros esquerdo e direito.
struct Node* newNode(int key) 
{ 
	struct Node* node = (struct Node*) malloc(sizeof(struct Node)); 
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
struct Node *rightRotate(struct Node *y) 
{ 
	struct Node *x = y->left; 
	struct Node *T2 = x->right; 

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
struct Node *leftRotate(struct Node *x) 
{ 
	struct Node *y = x->right; 
	struct Node *T2 = y->left; 

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
int getBalance(struct Node *N) 
{ 
	if (N == NULL) 
		return 0; 
	return height(N->left) - height(N->right); 
} 

// Função recursiva para inserir na sub-árvore enraizada com o nó e retorna a nova raiz da sub-árvore
struct Node* insert(struct Node* node, int key) 
{ 
	// 1. Realiza a inserção normal da BST
	if (node == NULL) // se vazio, cria nova árvore
		return(newNode(key)); 

	if (key < node->key) //se menor, insere a esquerda
		node->left = insert(node->left, key); 
	else if (key > node->key) // se maior,  insere a direita
		node->right = insert(node->right, key); 
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
void preOrder(struct Node *root) 
{ 
	if(root != NULL) 
	{ 
		printf("%d ", root->key); 
		preOrder(root->left); 
		preOrder(root->right); 
	} 
} 

// Função para série de Fibbonacci
int fibbonacci(int n) {
   if(n == 0){
      return 0;
   } else if(n == 1) {
      return 1;
   } else {
      return (fibbonacci(n-1) + fibbonacci(n-2));
   }
}

// Função para imprimir árvore binária em 2D  
// Faz travessia inversa
void print2DUtil(struct Node *root, int space) 
{ 

	int i;
	// Caso base 
	if (root == NULL) 
		return; 

	// Aumeta distancia entre níveis
	space += COUNT; 

	// Processar primeiro a criança a direita 
	print2DUtil(root->right, space); 

	// Imprimir nó atual após espaço
	// count 
	printf("\n"); 
	for (i = COUNT; i < space; i++) 
		printf(" "); 
	printf("%d\n", root->key); 

	// Processar a criança a esquerda
	print2DUtil(root->left, space); 
} 

// Wrapp print2DUtil() 
void print2D(struct Node *root) 
{ 
// Passar espaço inicial countar como 0 
print2DUtil(root, 5); 
}



void main(){
	
 struct Node *root = NULL; 
 int n, i;
 
  printf("Digite a posicao do elemento na serie: \n dado que n >1 \n\n");
 
  scanf("%d", &n);
  
if(n>1){
  
   printf("\nSequencia de Fibonacci:\n\n");
  for(i = 0; i < n; i++){
    
    root = insert(root, fibbonacci(i));  
      
   printf("[%d]:  %d\n",i+1 , fibbonacci(i));
  }
  
}else{
  	printf("\nNumero invalido!\n\n");
  }
printf("\nArvore balanceada:\n");
  print2D(root);
}

