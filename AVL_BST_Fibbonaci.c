// Programa C para inserir um n� na �rvore AVL
#include<stdio.h> 
#include<stdlib.h> 
#define COUNT 10

// Um n� de �rvore AVL  
struct Node 
{ 
	int key; 
	struct Node *left; 
	struct Node *right; 
	int height; 
}; 


// Uma fun��o para obter a altura da �rvore  
int height(struct Node *N) 
{ 
	if (N == NULL) 
		return 0; 
	return N->height; 
} 

// Uma fun��o para obter um m�ximo de dois inteiros  
int max(int a, int b) 
{ 
	return (a > b)? a : b; 
} 

//Fun��o que atribui um novo n� com o valor inserido e NULL aos ponteiros esquerdo e direito.
struct Node* newNode(int key) 
{ 
	struct Node* node = (struct Node*) malloc(sizeof(struct Node)); 
	node->key = key; 
	node->left = NULL; 
	node->right = NULL; 
	node->height = 1; // novo n� � inicialmente adicionado na folha 
	return(node); 
} 


/* Visualiza��o das rota��es:

T1, T2 e T3 s�o sub-�rvores enraizadas em y (no lado esquerdo) ou x (no lado direito)

     y                               x
    / \     Rota��o a direita       /  \
   x   T3   - - - - - - - >        T1   y 
  / \       < - - - - - - -            / \
 T1  T2     Rota��o a esquerda       T2  T3
 
  */ 
  
// Fun��o para rota��o � direita da sub-�rvore enraizada em y 
struct Node *rightRotate(struct Node *y) 
{ 
	struct Node *x = y->left; 
	struct Node *T2 = x->right; 

	// Rota��o a direita 
	x->right = y; 
	y->left = T2; 

	// Atualizar alturas 
	y->height = max(height(y->left), height(y->right))+1; 
	x->height = max(height(x->left), height(x->right))+1; 

	// Retorna nova raiz
	return x; 
} 

/* Visualiza��o das rota��es:

T1, T2 e T3 s�o sub-�rvores enraizadas em y (no lado esquerdo) ou x (no lado direito)

     y                               x
    / \     Rota��o a direita       /  \
   x   T3   - - - - - - - >        T1   y 
  / \       < - - - - - - -            / \
 T1  T2     Rota��o a esquerda       T2  T3
 
  */ 

// Fun��o para rota��o � esquerda da sub-�rvore enraizada em x 
struct Node *leftRotate(struct Node *x) 
{ 
	struct Node *y = x->right; 
	struct Node *T2 = y->left; 

	// Rota��o a esquerda 
	y->left = x; 
	x->right = T2; 

	// Atualizar alturas 
	x->height = max(height(x->left), height(x->right))+1; 
	y->height = max(height(y->left), height(y->right))+1; 

	// Retorna nova raiz
	return y; 
} 

// Obter fator de balanceamento do n� N
int getBalance(struct Node *N) 
{ 
	if (N == NULL) 
		return 0; 
	return height(N->left) - height(N->right); 
} 

// Fun��o recursiva para inserir na sub-�rvore enraizada com o n� e retorna a nova raiz da sub-�rvore
struct Node* insert(struct Node* node, int key) 
{ 
	// 1. Realiza a inser��o normal da BST
	if (node == NULL) // se vazio, cria nova �rvore
		return(newNode(key)); 

	if (key < node->key) //se menor, insere a esquerda
		node->left = insert(node->left, key); 
	else if (key > node->key) // se maior,  insere a direita
		node->right = insert(node->right, key); 
	else // Se igual, retorna o mesmo n�
		return node; 

	// 2. Atualiza a altura do n� ancestral
	node->height = 1 + max(height(node->left), 
						height(node->right)); 

	// 3. Obter o fator de balanceamento do n� ancestral para verificar se este n� se tornou desequilibrado 
	int balance = getBalance(node); 

		// Se o n� se desequilibrar, ent�o um dos quatro casos abaixo ir� ocorrer


		// Esquerda esquerda
		/*
	
		T1, T2, T3 and T4 s�o sub-�rvores
		
 	        z                                       y 
 	       / \                                   /     \
 	      y   T4      Rota��o a direita (z)     x       z
	      / \          - - - - - - - - ->      /  \    /  \ 
 	    x   T3                               T1  T2  T3  T4
 	   / \
 	 T1   T2
	
		*/
	//y � filho a esquerda de z e x � filho a esquerda de y 
	if (balance > 1 && key < node->left->key) 
		return rightRotate(node); 

	// Direita direita
	/*
	
		   z                                  y
         /  \                               /   \ 
		T1   y     Rota��o a esquerda(z)  z      x
 		   /  \  	- - - - - - - ->     / \    / \
 		 T2   x     	               T1  T2 T3  T4
 	 	     / \
 		    T3  T4
	
	*/ 
	
	//y � filho a direita de z e x � filho a direita de y 
	if (balance < -1 && key > node->right->key) 
		return leftRotate(node); 

	// Esquerda direita
	
	/*
	
	     z                               z                         	 	   x
	    / \                            /   \                            /    \ 
	   y   T4  Rota��o a esquerda(y)  x    T4  Rota��o a direita(z)    y      z
	  / \      - - - - - - - - ->    /  \      - - - - - - - ->		  / \    / \
	T1   x                          y    T3                    		T1  T2 T3  T4
	    / \                        / \
	  T2   T3                    T1   T2
	
	*/ 
	
	//y � filho a esquerda de z e x � filho a direita de y
	if (balance > 1 && key > node->left->key) 
	{ 
		node->left = leftRotate(node->left); 
		return rightRotate(node); 
	} 

	// Direita esquerda
	
	/*
	
	   z                             z                                    x
	  / \                           / \                                 /   \ 
	T1   y   Rota��o a direita(y) T1   x      Rota��o a esquerda(z)   z      y
	    / \  - - - - - - - - ->      /  \       - - - - - - - ->     / \    / \
	   x   T4                       T2   y                         T1  T2  T3  T4
	  / \                               /  \
	T2   T3                            T3   T4
	
	*/
	 
	 //y � filho a direita de z e x � filho a esquerda de y
	if (balance < -1 && key < node->right->key) 
	{ 
		node->right = rightRotate(node->right); 
		return leftRotate(node); 
	} 

	//  retornar o ponteiro (inalterado) do n� 
	return node; 
} 

// Uma fun��o de utilidade para imprimir a travessia da �rvore antes da solicita��o
void preOrder(struct Node *root) 
{ 
	if(root != NULL) 
	{ 
		printf("%d ", root->key); 
		preOrder(root->left); 
		preOrder(root->right); 
	} 
} 

// Fun��o para s�rie de Fibbonacci
int fibbonacci(int n) {
   if(n == 0){
      return 0;
   } else if(n == 1) {
      return 1;
   } else {
      return (fibbonacci(n-1) + fibbonacci(n-2));
   }
}

// Fun��o para imprimir �rvore bin�ria em 2D  
// Faz travessia inversa
void print2DUtil(struct Node *root, int space) 
{ 

	int i;
	// Caso base 
	if (root == NULL) 
		return; 

	// Aumeta distancia entre n�veis
	space += COUNT; 

	// Processar primeiro a crian�a a direita 
	print2DUtil(root->right, space); 

	// Imprimir n� atual ap�s espa�o
	// count 
	printf("\n"); 
	for (i = COUNT; i < space; i++) 
		printf(" "); 
	printf("%d\n", root->key); 

	// Processar a crian�a a esquerda
	print2DUtil(root->left, space); 
} 

// Wrapp print2DUtil() 
void print2D(struct Node *root) 
{ 
// Passar espa�o inicial countar como 0 
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

