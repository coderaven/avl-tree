// Algrotihm design and Code implemented from scratch by Raven G. Duran - BSIT - 2R1 MUST

#include <stdio.h>
#include <math.h> // for the abs() function. (Absolute value)


struct node {
    int value;
    struct node *parent;
    struct node *left;
    struct node *right;
} *tRoot = NULL, *tLeaf = NULL;

// Menu functions
void showMenu();
void doInsert();
void doDelete();
void doSearch();
void doInOrder();
void doShowHeight();

// Functions for creating a BST structure
struct node* newNode(int value,struct node *parent);  
struct node* insertN(struct node *root,int value,struct node *parent);

// AVL Utilities
void rotateLL(struct node *root);
void rotateLR(struct node *root);
void rotateRR(struct node *root);
void rotateRL(struct node *root);

void balanceCheck(struct node *root);
void bFactorPostOrder(struct node *root);
void correctParents(struct node *a,struct node *b,struct node *c,struct node *f);

// Common Operations for BST structues
struct node* searchNode(struct node *root, int value); // Return NULL if not found or Pointer to node if found
struct node* findMin(struct node *root);  
struct node* findMax(struct node *root); 
int getHeight(struct node *root);   // Note: This is a generic getHeight function if you want
                                    // to do as ask by Ma'am Raboy for the project to have getHeight of root, left and right
                                    // then just use these: getHeight(root), getHeight(root->left), getHeight(root->right)
// InOrder print
void inOrder(struct node *root);

int main(){
    showMenu();
    
    getch();
    return 0;
}

void showMenu(){
    system("cls"); // This clears everything
   printf("     ___   ___      _____ ___ ___ ___       \n");
   printf("     /_\\ \\ / / |    |_   _| _ \\ __| __|  \n");
   printf("    / _ \\ - /| |__    | | |   / _|| _|     \n");
   printf("   /_/ \\_\\_/ |____|   |_| |_|_\\___|___|  \n");
   printf("                     By: Raven G. Duran     \n");
    printf("\n\n");
    printf("(1) Insert a Node\n");
    printf("(2) Delete a Node\n");
    printf("(3) Search a Node\n");
    printf("(4) Print In Order\n");
    printf("(5) Show Heights of Root\n");
    printf("(6) Exit\n");
    
    switch(getch()){
       case '1' : doInsert();   break;
       case '2' : doDelete();   break;
       case '3' : doSearch();   break;
       case '4' : doInOrder();   break;
       case '5' : doShowHeight();   break;
       default  : exit(0);
    }
}

void doInsert(){
    system("cls");
    
    int value;
    printf("Node Value: ");
    scanf("%d",&value);    
    tRoot = insertN(tRoot,value,tRoot); 
    
    printf("Inserted!\n");
    
    printf("\n--Balance Factor Sheet--\n");
    bFactorPostOrder(tRoot);
    
    printf("\n--Last Inserted Trace--\n");
     while (tLeaf != NULL){
           printf(" %d\n | \n",tLeaf->value);
           balanceCheck(tLeaf);
           tLeaf = tLeaf->parent;
     } printf("NULL");
    
    
    printf("\n\n\nPress any key to continue...");
    getch();
    showMenu();
}

void doDelete(){
     system("cls");
     
     int toDelete;
     struct node *dNode = NULL, *predecessor = NULL, *successor = NULL, *temp = NULL;
     printf("Node to delete: ");
     scanf("%d",&toDelete);
     
     dNode = searchNode(tRoot,toDelete);

     if (dNode == NULL) printf("The node does not exist!\n");
     else if(dNode == tRoot && dNode->left == NULL && dNode->right == NULL) {
        free(dNode);
        tRoot = NULL;
        dNode = NULL;
        printf("Node with value %d is deleted!\nThe tree is now empty.\n");
        printf("\n\n\nPress any key to continue...");
        getch();
        showMenu();
     } else {
          printf("Deleting node...\n");
          temp = dNode;
          if (dNode->left == NULL && dNode->right == NULL){   // Case 1 : leaf
             if (tRoot == dNode) tRoot = NULL;
             else {
                  if(dNode->parent->right == dNode) dNode->parent->right = NULL;
                  else dNode->parent->left = NULL;
             }
             
             dNode = NULL;
          } else if (dNode->left != NULL){
             predecessor = findMax(dNode->left); // Get predecessor
             // update predecessor parent
             if (predecessor->parent->left != NULL) {
                if (predecessor->parent->left->value == predecessor->value) predecessor->parent->left = NULL;
             } else predecessor->parent->right = NULL;

             // swap with predecessor
             dNode->value = predecessor->value;
             free(predecessor);
             
          } else {
             successor = findMin(dNode->right); // Get successor
             // update successor parent
             if (successor->parent->left != NULL) {
                if (successor->parent->left->value == successor->value) successor->parent->left = NULL;
             } else successor->parent->right = NULL;
             
              // swap with predecessor
             dNode->value = successor->value;
             free(successor);
          }
          
          if (temp->parent != NULL) balanceCheck(temp->parent);
          temp = NULL;
          
          printf("The node is now deleted!\n");
          
          if(dNode != NULL) balanceCheck(dNode);
          
          printf("\n--Balance Factor Sheet--\n");
          if (tRoot != NULL) bFactorPostOrder(tRoot);
          else printf("\nThe tree is empty!\n");
     }
     
     printf("\n\n\nPress any key to continue...");
     getch();
     showMenu();
}

void doSearch(){
    system("cls"); 
     
    int toFind;
    printf("Search Node with value: ");
    scanf("%d",&toFind);
    
    struct node *nodeF = searchNode(tRoot,toFind);
    if (nodeF!= NULL){
        printf("Found Node %d!\n",toFind);
        printf("Node %d Height: %d\n",toFind,getHeight(nodeF));
        printf("Node %d Left sub-tree Height: %d\n",toFind,getHeight(nodeF->left));
        printf("Node %d Right subtree Height: %d\n",toFind,getHeight(nodeF->right));
    } else printf("Not found!\n"); 
    
    printf("\n\n\nPress any key to continue...");
    getch();
    showMenu();
}

void doInOrder(){
     system("cls");
     printf("--In Order Print--\n");
     if (tRoot != NULL) inOrder(tRoot);
     else printf("\nThe tree is empty!\n");
     
     printf("\n--Balance Factor Sheet (By Post Order Traversal)--\n");
     if (tRoot != NULL) bFactorPostOrder(tRoot);
     else printf("\nThe tree is empty!\n");
     
     printf("\n\n\nPress any key to continue...");
     getch();
     showMenu();
}

void doShowHeight(){
    system("cls"); 
    printf("--- Show Heights ---\n");
    if (tRoot!= NULL){
        printf("Node %d Height: %d\n",tRoot->value,getHeight(tRoot));
        printf("Node %d Left sub-tree Height: %d\n",tRoot->value,getHeight(tRoot->left));
        printf("Node %d Right subtree Height: %d\n",tRoot->value,getHeight(tRoot->right));
    } else printf("The tree is empty!\n"); 
    
    printf("\n\n\nPress any key to continue...");
    getch();
    showMenu();
}

struct node* newNode(int value,struct node *parent){
       struct node *root = (struct node*)malloc(sizeof(struct node));
       root->value = value;
       root->parent = parent;
       root->left = NULL;
       root->right = NULL;
}

struct node* insertN(struct node *root,int value,struct node *parent){
       if (root == NULL){
          return tLeaf = newNode(value,parent);
       } else {
         if (value < root->value) root->left =  insertN(root->left,value,root);
         else if (value > root->value) root->right = insertN(root->right,value,root);
         
         return root;
       }
}

// AVL Functions - As AVL tree is derived from Binary Search Trees

void rotateRL(struct node *root){
    struct node *a = root;
    struct node *b = root->right;
    struct node *c = root->right->left;
    struct node *f = root->parent;
    
    b->left =  c->right;
    a->right = c->left;
    c->right = b;
    c->left = a;
    
    if (f != NULL){
       if (f->right->value == a->value) f->right = c;
       else f->left = c;
    } else {
      tRoot = c;
      c->parent = NULL;
    }
    
    // Correct Parents
    correctParents(a,b,c,f);
    
}

void rotateRR(struct node *root){
    struct node *a = root;
    struct node *b = root->right;
    struct node *c = root->right->right;
    struct node *f = root->parent;
    
    a->right = b->left;
    b->left = a;
    
    if (f != NULL){
       if (f->right->value == a->value) f->right = b;
       else f->left = b;
    } else {
      tRoot = b;
      b->parent = NULL;
    }
    
    // Correct Parents
    correctParents(a,b,c,f);
}

void rotateLR(struct node *root){
    struct node *a = root;
    struct node *b = root->left;
    struct node *c = root->left->right;
    struct node *f = root->parent;
    
    a->left = c->right;
    b->right = c->left;
    c->left = b;
    c->right = a;
    
    if (f != NULL){
       if (f->right->value == a->value) f->right = c;
       else f->left = c;
    } else {
      tRoot = c;
      c->parent = NULL;
    }
    
    // Correct Parents
    correctParents(a,b,c,f);
}

void rotateLL(struct node *root){
    struct node *a = root;
    struct node *b = root->left;
    struct node *c = root->left->left;
    struct node *f = root->parent;
    
    a->left = b->right;
    b->right = a;
    
    if (f != NULL){
       if (f->right->value == a->value) f->right = b;
       else f->left = b;
    } else {
      tRoot = b;
      b->parent = NULL;
    }
    
    // Correct Parents
    correctParents(a,b,c,f);
}

void balanceCheck(struct node *root){     
     if ( getHeight(root->left) > (getHeight(root->right) + 1) ){
        printf("Imbalance! The Right sub-tree of node %d is taller!\n",root->value);
        if ( getHeight(root->left->right) > (getHeight(root->left->left)) ){
           printf("Rotating using LR Rotation...\n");
           rotateLR(root);
        } else {
          printf("Rotating using LL Rotation...\n");
          rotateLL(root);
        }
        
     } else if ( getHeight(root->right) > (getHeight(root->left) + 1) ){
        printf("Imbalance! The Right sub-tree of node %d is taller!\n",root->value);
        
        if ( getHeight(root->right->left) > (getHeight(root->right->right)) ){
           printf("Rotating using RL Rotation...\n");
           rotateRL(root);
        } else {
           printf("Rotating using RR Rotation...\n");
           rotateRR(root);
        }
     }
}

void bFactorPostOrder(struct node *root){
     if (root == NULL) return;
     else {
          bFactorPostOrder(root->left);
          bFactorPostOrder(root->right);
          
          int rHeight = getHeight(root->right);
          int lHeight = getHeight(root->left);
          int bFactor = abs(rHeight - lHeight);
          printf("~Node %d~ \t lHeight: %d \t rHeight: %d \t Balance Factor: %d\n",root->value,lHeight,rHeight,bFactor);                              
     }
}

void correctParents(struct node *a,struct node *b,struct node *c,struct node *f){
    if (a->left  != NULL) a->left->parent  = a;
    if (a->right != NULL) a->right->parent = a;
    if (b->left  != NULL) b->left->parent  = b;
    if (b->right != NULL) b->right->parent = b;
    if (c->left  != NULL) c->left->parent  = c;
    if (c->right != NULL) c->right->parent = c;
    if (f  != NULL) f->left->parent  = f;
    if (f  != NULL) f->right->parent = f;
}

struct node* searchNode(struct node *root, int value){
    if (root == NULL) return NULL;
    else {
         if (root->value == value) return root;
         else {
              if (value < root->value) return searchNode(root->left,value);
              else return searchNode(root->right,value);
         }
    }
}

int getHeight(struct node *root){
   if (root==NULL) return 0;
   else {
       /* compute the depth of each subtree */
       int lDepth = getHeight(root->left);
       int rDepth = getHeight(root->right);
 
       /* use the larger one */
       if (lDepth > rDepth) 
           return (root == tRoot? lDepth : (lDepth+1) );
       else return (root == tRoot? rDepth : (rDepth+1) );
   }
} 

struct node* findMin(struct node *root){ 
    // Go to left most part to get the minimum
    while (root->left != NULL) {
       root = root->left;
    }
    
    return(root);
}

struct node* findMax(struct node *root){
   // Go to right most part to get the maximum
   while (root->right != NULL) {
       root = root->right;
    }
    
    return(root);
}

void inOrder(struct node *root){
     if (root == NULL) return;
     else {
          inOrder(root->left);
          printf("~%d~\n",root->value);
          inOrder(root->right);
     }
}

