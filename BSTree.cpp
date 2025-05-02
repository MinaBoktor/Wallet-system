#include "BSTree.h"
#include <iostream>
#include <assert.h>


template <class T>
Node<T>::Node()
{
	left = right = NULL;
}

template <class T>
Node<T>::Node(T val)
{
	value = val;
	left = right = NULL;
}

template <class T>
BSTree<T>::BSTree(void)
{
	root = NULL;
}

template <class T>
bool BSTree<T>::contains(T val)
{
	Node<T>* tmp = findNode(val);
	return (tmp != NULL);
}

template <class T>
Node<T>* BSTree<T>::findNode(T val)
{
	Node<T>* temp = root;
	while (temp != NULL)
	{
		if (temp->value == val)
		{
			return temp;
		}
		else if (temp->value < val)
		{
			//right
			temp = temp->right;
		}
		else
		{
			//left
			temp = temp->left;
		}
	}

	return temp;	
}

template <class T>
void BSTree<T>::insert(T val)
{
	assert(contains(val) == false);

	Node<T>* nodeToBeAdded = new Node<T>(val);
	if (root == NULL)
	{
		root = nodeToBeAdded;
	}
	else
	{
		Node<T> *temp = root;
		while (true)
		{
			if (temp->value < val)
			{
				// right
				if (temp->right == NULL)
				{
					temp->right = nodeToBeAdded;
					break;
				}
				else
				{
					temp = temp->right;
				}
			}
			else
			{
				// left
				if (temp->left == NULL)
				{
					temp->left = nodeToBeAdded;
					break;
				}
				else
				{
					temp = temp->left;
				}
			}
		}
	}	
}

template <class T>
void BSTree<T>::traverse(Order order)
{
	if (order == INORDER)
		inOrder(root);
	else if (order == PREORDER)
		preOrder(root);
	else
		postOrder(root);
}

template <class T>
void BSTree<T>::inOrder(Node<T>* node)
{
	if (node != NULL)
	{
		//left
		inOrder(node->left);
		//node
		cout << node->value << endl;
		//right
		inOrder(node->right);
	}
}

template <class T>
void BSTree<T>::preOrder(Node<T>* node)
{
	if (node != NULL)
	{
		cout << node->value << endl;
		preOrder(node->left);
		preOrder(node->right);
	}
}

template <class T>
void BSTree<T>::postOrder(Node<T>* node)
{
	if (node != NULL)
	{
		postOrder(node->left);
		postOrder(node->right);
		cout << node->value << endl;
	}
}

template <class T>
void BSTree<T>::deleteBST(Node<T> *node)
{
	if (!node)
		return;

	Node<T>* currentTreeNode = node;
	Node<T> * leftTreeNode = node->left;
	Node<T> * rightTreeNode = node->right;
	delete(currentTreeNode);
	deleteBST(leftTreeNode);
	deleteBST(rightTreeNode);
}

template <class T>
BSTree<T>::~BSTree(void)
{
	deleteBST(root);
}