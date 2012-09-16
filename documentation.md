Screenshots
===========
![AVL Tree](http://i.imgur.com/wTLbV.png "Program Frame Screenshots")

Documentation
=============

This is the documentation for the source code. I'll update it from time to time if I found bugs or things that
need to be discussed.

Thoroughly discussing the step by step flow of the program would make this documentation very long.
So I decided to document just the functions in a way you'll understand how it works. But I'll leave
the rest for you to debug and understand, this is a good way to really understand what's going on
the code. (Don't worry, almost everything is discussed) - Raven G. Duran

#### Main Program flow
```C
void showMenu();
void doInsert();
void doDelete();
void doSearch();
void doInOrder();
 ```
These are program specific functions use in directing our porgram flow.
* showMenu()	: Shows the menu with waits for the user to enter a menu choice.
* doInsert()	: A menu function that will handle the insertion process of the AVL tree.
* doDelete()	: A menu function that will handle the deletion process of the AVL tree.
* doInorder()	: A menu function that will handle the printing of the tree in order traversal.

#### Node Structure
```C
 struct node {
    int value;
    struct node *parent;
    struct node *left;
    struct node *right;
} *tRoot = NULL, *tLeaf = NULL;
 ```
 
The node is composed of 1 value and 3 pointers: (This is a bit self-explanatory, but for the sake of formality let's just define it)
* value 	: The variable to hold the value for the node
* parent	: Points to the parent of the node
* left		: Points to the smaller sub-tree node
* right		: Points to the bigger sub-tree node

There are also 2 global pointer variables used in the whole program:
* tRoot 	: Points to the root of the whole tree
* tLeaf		: Points to the last inserted leaf in the tree

#### BST Insertion like functions
```C
struct node* newNode(int value,struct node *parent);  
struct node* insertN(struct node *root,int value,struct node *parent);
 ```

The two functions are the core in creating a BST like structure.
* newNode function 	: This function creates a basic node. Paremeters:
	1. value		: The value you want to put to the node.
	2. parent		: The parent of the Node (Can also be NULL).
* insertN function	: This inserts a new node properly into the tree. Parameters:
	1. root			: Pointer to the root of the tree of where to insert the new node.
	2. value		: The value you want to insert.
	3. parent		: The parent of the new node you are inserting. (A bit redundant, but this helps a lot in tracking trees)
	
If you want a more thorough explanation of the BST functions,
then you can go to this link: [Binary Search Tree Operations Explanation (Bisaya)](http://pastebin.com/DCkF4JAn)

#### AVL functions (Helper, Utilities, and Rotations
```C
void rotateLL(struct node *root);
void rotateLR(struct node *root);
void rotateRR(struct node *root);
void rotateRL(struct node *root);

void balanceCheck(struct node *root);
void bFactorInorder(struct node *root);
void correctParents(struct node *a,struct node *b,struct node *c,struct node *f);
 ```

##### Rotations
There are 4 rotation types in an AVL tree and I implemented them in C by understanding the
algorithm behind. This is the reference for the rotation algorithms: [Rotation Algorithms](http://www.cse.ohio-state.edu/~sgomori/570/avlrotations.html)

Rotation forms:
```
LL Form		 A		RR Form		A		LR Form		A		RL Form		A
			/					 \				   /					 \
		   B					  B				  B						  B
		  /						   \			   \					 /
		 C 							C			    C					C

 ```

A - points to the node that is out of balance. 
B - points to the child of A in the direction of the out-of-balance
C - points to the child of B in the direction of the out-=of-balance
F - points to the parent of A. This is the only pointer of these 4 that is allowed to be NULL.

##### balanceCheck
The balanceCheck takes a root of a tree as a parameter.
It then compares the left and right sub-tree of that tree to check if the balance
factor is more than 1. 

If the tree is inbalance, then we perform the corresponding rotation based on what node
has the highest number of nodes. (Read the above A, B, C, and F pointers again to trace the code)

##### bFactorInorder
This is just a simple function that traverses a given tree (parameter is root)
and prints the balance factor for each and every node (Traverses in order)

The balance factor is calculated as: abs(heightLeft - heightRight). abs means get the absolute value of the result.

##### correctParents
This function is a bit trivial. It just corrects the pointer to parent for each and every 
affected nodes in the rotation. (Parents of A, B , C, and F)

#### Helper functions
```C
struct node* searchNode(struct node *root, int value); // Return NULL if not found or Pointer to node if found
struct node* findMin(struct node *root);  
struct node* findMax(struct node *root); 
int getHeight(struct node *root);
 ```
Helper functions are used in bigger functions to make it work. These functions are of big help
in structuring the AVL tree.

* searchNode	: Searches a node base by the value given to it. 
				  Returns (or equal to) NULL if the value is not found.
				  Returns (or equal to) the pointer to that node if it is found. Parameters:
	1. root		: Root of the tree you want to search the node on.
	2. value	: The value you want to search for.
* findMin		: Finds the minimum number in the given tree. (Gets the successor) The paremeter is the root.
* findMax		: Finds the maximum number in the given tree. (Gets the predecessor) The parameter is the root.
* getHegiht		: This function gets the height of a given tree and return that in integer. The paremeter is the root.

#### InOrder
```C
void inOrder(struct node *root);
 ```
This is just a trivial function that in Orderly traverse a given tree.
In Orderly traverse means that the whole tree will be traversed in ascending order.
If the node it puts are arrange correctly (increasing), then that means our solution worked!

#### Finally
######Comments? Suggestions? Problems?
You can place an issue (by going to the Issues tab above) so that I could get to the problem more easily.
You could also send me an email if anything bugs you at: me@ImRaven.com
Or if you're an MUST student, you can ask for help personally at school.

Hope it helped :)
	
	
P.S. : If you have a better algorithm or if there is a part in my solution that need
to be refactored, then feel free to make a pull request! :) 
	
	
(Bisaya)
Sa akong mga amigo nga nakakita ani nga solution : Walay libre dira? HAHA xD	
k-thnks-bye	
	
	
	
	
