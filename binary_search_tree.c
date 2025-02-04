#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#define N 20

// BST dugum yapisini tanimlayin
struct node {
	int data;
    struct node *left;
    struct node *right;
};

typedef struct node Node;


// Yeni dugum yaratma fonksiyonunu yazin
struct node* newNode(int data) {
    Node *result = malloc(sizeof(Node));
    if (result == NULL)
    {
        printf("Invalid memory allocation!");
        exit(1);
    }

    result->data = data;
    result->left = NULL;
    result->right = NULL;
    
    return result;
    
}

// Agaca rekursif olarak yeni dugum ekleyen fonksiyonu yazin
struct node* insertNode(struct node* n, int data) {
	if (n == NULL){
        n = newNode(data);
    }
    
    else if (data < n->data){
        n->left = insertNode(n->left,data);
    }

    else if (data >= n->data){
        n->right = insertNode(n->right,data);
    }

    return n;
}

// Agactaki en dusuk degeri bulup donduren fonksiyonu yazin
int findMin(struct node *tree) {
	if (tree == NULL)
    {   
        return INT_MAX;
    }

    int res = tree->data;
    int lres = findMin(tree->left);
    int rres = findMin(tree->right);

    if (lres < res)
    {
        res = lres;
    }
    
    if (rres < res)
    {
        res = rres;
    }
    
    return res;
}

// Agactaki en buyuk degeri bulup donduren fonksiyonu yazin
int findMax(struct node *tree) {
	if (tree == NULL)
    {   
        return INT_MIN;
    }

    int res = tree->data;
    int lres = findMax(tree->left);
    int rres = findMax(tree->right);

    if (lres > res)
    {
        res = lres;
    }
    
    if (rres > res)
    {
        res = rres;
    }
    
    return res;
}

// Agactaki en yuksek degerli dugumun adresini donduren fonksiyonu yazin
struct node* findMaxNode(struct node *tree) {
	Node *tmp = tree;
    
    while (tmp->right != NULL)
    {
        tmp = tmp->right;
    }
    
    return tmp;
}

// Agactan rekursif olarak dugum silen fonksiyonu yazin, silinecek dugumun 2 cocugu varsa, silinen dugumu sol alt-agacin maksimum degerli dugumu olarak guncelleyin (https://www.cs.usfca.edu/~galles/visualization/BST.html adresindeki Delete fonksiyonu gibi)
struct node* deleteNode(struct node *tree, int data) {
	if (tree == NULL)
    {
        return tree;
    }

    else if (data < tree->data)
    {
        tree->left = deleteNode(tree->left,data);
    }
    
    else if (data > tree->data)
    {
        tree->right = deleteNode(tree->right,data);
    }

    else{
        //Eğer çocuk yoksa
        if (tree->left == NULL && tree->right == NULL)
        {
            free(tree);
            tree = NULL;
        }
        
        //Eğer 1 çocuk varsa ve o da node un sağındaysa
        else if (tree->left == NULL)
        {
            Node *tmp = tree;
            tree = tree->right;
            free(tmp);
        }

        //Eğer 1 çocuk varsa ve o da node un solundaysa
        else if (tree->right == NULL)
        {
            Node *tmp = tree;
            tree = tree->left;
            free(tmp);
        }

        //Eğer 2 çocuk varsa
        else{
            Node *tmp = findMaxNode(tree->left);
            tree->data = tmp->data;
            tree->left = deleteNode(tree->left, tmp->data);

        }
        
    }

    return tree;
    
}

// Agaci rekursif olarak "in-order" yontemi ile dolasip degerleri ekrana bastiran fonksiyonu yazin
void printTreeInOrder(struct node* tree) {
	if (tree == NULL)
    {   
        return;
    }
    
    printTreeInOrder(tree->left);
    printf("%d ", tree->data);
    printTreeInOrder(tree->right);
}

// Agaci rekursif olarak "pre-order" yontemi ile dolasip degerleri ekrana bastiran fonksiyonu yazin
void printTreePreOrder(struct node* tree) {
	if (tree == NULL)
    {
        return;
    }
    
    printf("%d ", tree->data);
    printTreePreOrder(tree->left);
    printTreePreOrder(tree->right);


}

// Agaci rekursif olarak "post-order" yontemi ile dolasip degerleri ekrana bastiran fonksiyonu yazin	
void printTreePostOrder(struct node* tree) {
	if (tree == NULL)
    {
        return ;
    }

    printTreePostOrder(tree->left);
    printTreePostOrder(tree->right);
    printf("%d ", tree->data);
    
}

// Level-order yontemi icin extra fonksiyonlar
// Rekursif olarak agacin yuksekligini hesaplayan fonksiyon
int findHeight(struct node *tree) {
	if (!tree)
		return 0;
	else {
		int h_left = findHeight(tree->left);
		int h_right = findHeight(tree->right);
		if (h_left > h_right)
			return (h_left + 1);
		else
			return (h_right + 1);
	}
}

// Rekursif olarak ayni hizadaki dugumleri bastiran fonksiyon
void printLevel(struct node *tree, int level) {
	if (!tree)
		return;
	if (level == 1)
		printf("%d ", tree->data);
	else if (level > 1) {
		printLevel(tree->left, level - 1);
		printLevel(tree->right, level - 1);
	}
}

// Yukaridaki iki fonksiyonu kullanarak agaci "level-order" yontemi ile dolasip degerleri ekrana bastiran fonksiyonu yazin	
void printTreeLevelOrder(struct node* tree) {
	int x = findHeight(tree);

    for (int i = 1; i <=x; i++)
    {
        printLevel(tree,i);
    }
    
    
}


int main(int argc, char *argv[]) {
    Node *BinarySearchTree = NULL;
    
    for (int i = 1; i < argc; i++)
    {
        BinarySearchTree = insertNode(BinarySearchTree,atoi(argv[i]));
    }
    
        
    /*BinarySearchTree = insertNode(BinarySearchTree,78);
    BinarySearchTree = insertNode(BinarySearchTree,85);
    BinarySearchTree = insertNode(BinarySearchTree,56);
    BinarySearchTree = insertNode(BinarySearchTree,65);
    BinarySearchTree = insertNode(BinarySearchTree,13);
    BinarySearchTree = insertNode(BinarySearchTree,79);
    BinarySearchTree = insertNode(BinarySearchTree,85);
    BinarySearchTree = insertNode(BinarySearchTree,86);
    BinarySearchTree = insertNode(BinarySearchTree,43);
    BinarySearchTree = insertNode(BinarySearchTree,97);*/

    printf("---<Before Actions!>---\n\n");

    printf("---<In Order>---\n");
    printTreeInOrder(BinarySearchTree);
    printf("\n\n");
    printf("---<Pre Order>---\n");
    printTreePreOrder(BinarySearchTree);
    printf("\n\n");
    printf("---<Post Order>---\n");
    printTreePostOrder(BinarySearchTree);
    printf("\n\n");
    printf("---<Level order>---\n");
    printTreeLevelOrder(BinarySearchTree);
    printf("\n\n");

    insertNode(BinarySearchTree,97);

    deleteNode(BinarySearchTree,85);
    deleteNode(BinarySearchTree,56);
    
    printf("---<After Actions!>---\n\n");

    printf("---<In Order>---\n");
    printTreeInOrder(BinarySearchTree);
    printf("\n\n");
    printf("---<Pre Order>---\n");
    printTreePreOrder(BinarySearchTree);
    printf("\n\n");
    printf("---<Post Order>---\n");
    printTreePostOrder(BinarySearchTree);
    printf("\n\n");   
    printf("---<Level order>---\n");
    printTreeLevelOrder(BinarySearchTree);
    printf("\n\n");

    printf("Maximum element is : %d\n",findMax(BinarySearchTree));
    printf("Minimum element is : %d\n",findMin(BinarySearchTree));

	
	// Copy paste icin: 78 85 56 65 13 79 85 86 43
	
	// Komut satirindan aldiginiz parametreleri kullanarak bir BST tanimlayin ve olusturun
	// ...
	
	// Agaciniza 97 degerli yeni bir dugum ekleyin
	// ...
	
	// Agactaki dugumlerin min ve max degerlerini ekrana bastırın
	// ...
	
	// Sirayla 85 ve 56 degerli dugumleri silin
	// ...
	
	// In-order, pre-order, post-order ve level-order yontemleri ile agaci dolasarak dügümlerin degerlerini duzgun bir sekilde ekrana bastirin
	// ...
	
	return 0;
}