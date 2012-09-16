Documentation
========

This is the documentation for the source code. I'll update it from time to time if I found bugs or things that
needs to be discussed.

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