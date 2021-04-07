#pragma once
#include <iostream>
#include <iomanip>
#include <stack>
#include <ostream>
#include "node.h"
using namespace std;

template <class K, class V>
class Dictionary 
{
private:
	unsigned size;
	Node <K, V>* root; // Radacina arborelui AVL

protected:
	Node <K, V>* Insert(Node <K, V>* node, K key, V value);			// Metoda de inserare 

	Node <K, V>* RemoveNode(Node <K, V>* node, K key);				// Metoda de stergere a unui nod

	void DeleteDictionar(Node <K, V>* node);						// Stergerea intregului dictionar

	Node <K, V>* RightRotate(Node <K, V>* node);					// Rotatie spre dreapta

	Node <K, V>* LeftRotate(Node <K, V>* node);						// Rotatie spre stanga

	Node <K, V>* MinValue(Node <K, V>* node);						// Determinarea valorii minime din dictionar
   
   void preOrderForKey(Node <K, V>* node, K key, V &value);			// Functie ajutatoare pentru cautare

public:

	Dictionary();								// Constructorul fara parametrii
	Dictionary(const Dictionary&ob);			// Constructorul de copiere
	~Dictionary();								// Destructorul

	unsigned getSize();							// Functie pentru obtinerea numarului de elemente din dictionar

	void preOrder(Node <K, V>* node);			// Parcurgere preOrdine
	void pre_order();
	void inOrder(Node <K, V>*  node);			// Parcurgere inOrdine
	void in_order();
	void postOrder(Node <K, V>*  node);			// Parcurgere postOrdine
	void post_order();
	void add(K, V);								// Adaugarea unui element
	void deleteAfterKey(K);						// Stergerea unui element dupa cheie

	void show();								// Functie de afisare

	void deleteAllElements();					// Functie de stergere a dictionarului

	bool searchKey(K key, V &aux);				// Functie de cautare dupa cheie

	bool isEmpty();								// Metoda de verificare a dictionarului - daca este gol sau nu

	V operator [] ( K index);					// Supraincarcare operator de indexare

    Dictionary <K, V> &operator = (Dictionary<K, V> &dictionary);	// Supraincarcare operator de atribuire

};

template <class K, class V>
Dictionary <K, V>::Dictionary() 
{
	root = nullptr;
	size = 0;
}

template <class K, class V>
Dictionary <K, V>::Dictionary(const Dictionary &ob)
{
	this->root = root;
	this->size = size;

	std::stack <Node <K, V>* > stiva;
	stiva.push(ob.root);
	while (!stiva.empty()) {
		Node <K, V>* node = stiva.top();
		stiva.pop();

		if (node->left != nullptr)
			stiva.push(node->left);

		if (node->right != nullptr)
			stiva.push(node->right);

		add(node->key, node->value);
	}
}

template <class K, class V>
Dictionary <K, V>::~Dictionary() 
{
	deleteAllElements();
}

template <class K, class V>
Node <K, V>* Dictionary<K, V>::Insert(Node <K, V>* node, K key, V value) {

	if (node == nullptr) // Daca dictionarul este gol
	{
		node = new Node <K, V>(key, value);
		return node;
	}
	if (key > node->key) 
	{
		node->right = Insert(node->right, key, value);
	}
	else if (key < node->key)
	{
		node->left = Insert(node->left, key, value);
	}
	else
		if (node->key == key) 
		{
			return node;
		}

	node->updateHeight(); // Actualizam inaltimea

	int balance = node->getBalance(node);
	
	// Cazuri de echilibrare: 

	// 1) Left Left
	if (balance > 1 && key < node->left->key)
		return RightRotate(node);

	// 2) Right Right  
	if (balance < -1 && key > node->right->key)
		return LeftRotate(node);

	// 3) Left Right 
	if (balance > 1 && key > node->left->key) {
		node->left = LeftRotate(node->left);
		return RightRotate(node);
	}

	// 4) Right Left 
	if (balance < -1 && key < node->right->key) {
		node->right = RightRotate(node->right);
		return LeftRotate(node);
	}
	return node;	// Nicio schimbare
}

template <class K, class V>
void Dictionary<K, V>::pre_order()
{
	preOrder(root);
}

template <class K, class V>
void Dictionary<K, V>::in_order()
{
	inOrder(root);
}

template <class K, class V>
void Dictionary<K, V>::post_order()
{
	postOrder(root);
}

template <class K, class V>
void Dictionary <K, V>::add(K key, V value)
{
	this->size += 1;
	this->root = Insert(this->root, key, value);
}

template <class K, class V>
unsigned Dictionary <K, V>::getSize() 
{
	return this->size;
}

template <class K, class V>
void Dictionary <K, V>::show() 
{
	if (root != nullptr && size > 0)
		inOrder(root);
}

template <class K, class V>
void Dictionary <K, V>::preOrder(Node<K, V>* node) {
	if (node == nullptr)
		return;
	cout << "Nodul: " << node->value;
	cout << "  -> Cheia: " << node->key;
	cout << "  -> Inaltimea: " << node->height << "\n";
	preOrder(node->left);
	preOrder(node->right);
}

template <class K, class V>
void Dictionary <K, V>::inOrder(Node <K, V>* node) 
{
	if (node == nullptr)
		return;
	inOrder(node->left);
	cout << "Nodul: " << node->value;
	cout << "  -> Cheia: " << node->key;
	cout << "  -> Inaltimea: " << node->height << "\n";
	inOrder(node->right);
}

template <class K, class V>
void Dictionary <K, V>::postOrder(Node <K, V>* node)
{
	if (node == nullptr)
		return;
	postOrder(node->left);
	postOrder(node->right);
	cout << "Nodul: " << node->value;
	cout << "  -> Cheia: " << node->key;
	cout << "  -> Inaltimea: " << node->height << "\n";
}

template <class K, class V>
void Dictionary <K, V>::preOrderForKey(Node <K, V>* node, K key, V &value)
{
	if (node == nullptr)
    {
	    value = V();
        return;
    }

	if (node->key == key) {
		value = node->value;
		return;
	}
	if (node->key > key)
		preOrderForKey(node->left, key, value);
	if (node->key < key)
		preOrderForKey(node->right, key, value);
}

template <class K, class V>
bool Dictionary <K, V>::searchKey(K key, V &aux) 
{
	preOrderForKey(root, key, aux);
	if (aux != V())
		return true;
	return false;
}

template <class K, class V>
Node <K, V>* Dictionary<K, V>::RightRotate(Node <K, V>* node)
{
	Node <K, V>* leftChild = node->left;
	Node <K, V>* rightChild = leftChild->right;

	leftChild->right = node;	// Efectuarea rotatiei
	node->left = rightChild;

	node->updateHeight();		// Actualizarea inaltimilor in arbore
	leftChild->updateHeight();
	return leftChild;
}

template <class K, class V>
Node <K, V>* Dictionary<K, V>::LeftRotate(Node <K, V>* node) {
	Node <K, V>* rightChild = node->right;
	Node <K, V>* leftChild = rightChild->left;

	rightChild->left = node;	// Efectuarea rotatiei
	node->right = leftChild;

	node->updateHeight();		// Actualizarea inaltimilor in arbore
	rightChild->updateHeight();
	return rightChild;
}

template <class K, class V>
Node <K, V>* Dictionary<K, V>::MinValue(Node <K, V>* node) 
{
	Node <K, V>* aux = node;
	while (aux->left != nullptr)
		aux = aux->left;
	return aux;
}

template <class K, class V>
void Dictionary<K, V>::deleteAfterKey(K key) 
{
	this->size -= 1;
	RemoveNode(root, key);
}

template <class K, class V>
Node <K, V>* Dictionary <K, V>::RemoveNode(Node <K, V>* root, K key) {
	if (root == nullptr)
		return root;
	if (key < root->key)	
		root->left = RemoveNode(root->left, key);
	else
		if (key > root->key)
			root->right = RemoveNode(root->right, key);

		else {														// In cazul in care nodul respectiv are maxim un copil
			
			if (root->left == nullptr || root->right == nullptr) {
				Node <K, V>* temp = root->left ? root->left : root->right;

				// Nodul nu are niciun copil
				if (temp == nullptr) {
					temp = root;
					root = nullptr;
				}
				// Nodul are doar un copil
				else
					*root = *temp;
				delete temp;
			}
			// Nodul are 2 copii
			else 
			{   
				Node <K, V>* temp = MinValue(root->right);
				root->key = temp->key;
				root->right = RemoveNode(root->right, temp->key);
			}
		}
	if (root == nullptr)
		return root;

	root->updateHeight();

	int balance = root->getBalance(root);

	// Analizam daca arborele este echilibrat si ajungem in cele 4 cazuri de echilibrare: 

	//1) Left Left
	if (balance > 1 && root->left->getBalance(root->left) >= 0)
		return RightRotate(root);

	//2) Right Right
	if (balance < -1 && root->right->getBalance(root->right) <= 0)
		return LeftRotate(root);
	
	//3) Left Right
	if (balance > 1 && root->left->getBalance(root->left) < 0) {
		root->left = LeftRotate(root->left);
		return RightRotate(root);
	}

	//4) Right Left
	if (balance < -1 && root->right->getBalance(root->right) > 0) {
		root->right = RightRotate(root->right);
		return LeftRotate(root);
	}

	return root;
}

template <class K, class V>
void Dictionary <K, V>::deleteAllElements() {
	DeleteDictionar(root);
	size = 0;
	root = nullptr;
}

template <class K, class V>
void Dictionary <K, V>::DeleteDictionar(Node <K, V>* node) {
	if (node == nullptr)
		return;

	DeleteDictionar(node->left);
	DeleteDictionar(node->right);

	delete node;
}

template <class K, class V>
std::ostream & operator << (std::ostream &out, Dictionary <K, V> &dictionary) {
	out << "Numarul de elemente din dictionar: " << dictionary.getSize() << "; \n";
	if (dictionary.getSize()) {
		dictionary.show();
	}
	return out;
}

template <class K, class V>
V Dictionary<K, V>::operator[] (K key) {
    V value;
    preOrderForKey(root, key, value);
    return value;
}

template <class K, class V>
Dictionary<K, V>&Dictionary<K, V>::operator= (Dictionary <K, V> &dictionary) {
    if (dictionary.root)
    {
        this->root = new Node<K,V>(*dictionary.root);
    }
    else
        this->root = nullptr;
	this->size = dictionary.size;
	return *this;
}

template <class K, class V>
bool Dictionary <K, V>::isEmpty() {
	if (getSize())
		return false;
	return true;
}