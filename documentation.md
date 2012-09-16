Documentation
========

This is the documentation for the source code. I'll update it from time to time if I found bugs or things that
need to be discussed.

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







