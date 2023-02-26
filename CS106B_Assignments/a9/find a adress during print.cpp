/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>

// C++ program for different tree traversals
#include <bits/stdc++.h>
using namespace std;

/* A binary tree node has data, pointer to left child
and a pointer to right child */
struct Node {
	int data;
	struct Node *left, *right;
};

// Utility function to create a new tree node
Node* newNode(int data)
{
	Node* temp = new Node;
	temp->data = data;
	temp->left = temp->right = NULL;
	return temp;
}

/* Given a binary tree, print its nodes according to the
"bottom-up" postorder traversal. */
void printPostorder(struct Node* node,int goal)
{   
	if (node == NULL)
		return;
    if (node->data == goal) cout<<'*'<<node->data<<'*';

	// first recur on left subtree
	printPostorder(node->left,goal);

	// then recur on right subtree
	printPostorder(node->right,goal);

	// now deal with the node
	cout << node->data << " ";
}

Node* findChar (int goal,Node* root){
    if (root==nullptr) return nullptr;
    if (root->data == goal) return root;
    return findChar(goal,root->left) ;
    return findChar(goal,root->right) ;


    
}

Node* contains(Node* root, const int& key) {
    /* Base case: If the tree is empty, your key isn't here. */
    if (root == nullptr) return nullptr;

    /* Recursive case: See how we compare to the root. */
    if (key == root->data) return root;
    else if (key < root->data) return contains(root->left, key);
     else /*  key > root->value */ return contains(root->right, key);
}

/* Driver code*/
int main()
{
	struct Node* root = newNode(1);
	root->left = newNode(2);
	root->right = newNode(3);
	root->left->left = newNode(4);
	root->left->right = newNode(5);
    Node* found = contains(root,3);
	// Function call
	cout<<"\nPostorder traversal of binary tree is \n";
	printPostorder(root,3);
	return 0;
}
