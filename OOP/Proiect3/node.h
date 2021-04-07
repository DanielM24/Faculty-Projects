#pragma once
#include <iostream>
#include <algorithm>
template <typename K, typename V> class Dictionary;

template <class K, class V>
class Node
{
private:
	K key;
	V value;
	Node <K, V>* left;
	Node <K, V>* right;
	int height;
protected:
	int getBalance(Node <K, V>* node);

	static int getHeight(Node <K, V>* node);
	void updateHeight();

	unsigned getKey();

	friend class Dictionary <K, V>;
public:
	Node();
	Node(K key, V value);
	Node(const Node<K,V> &other);

	//Node<K,V> &operator=(const Node<K,V> &other);
};

template <class K, class V>
Node <K, V>::Node() {
	this->key = 0;
	this->value = 0;
	this->height = 0;
	this->left = nullptr;
	this->right = nullptr;
}

template <class K, class V>
Node <K, V>::Node(K key, V value)
{
	this->key = key;
	this->value = value;
	height = 1;
	left = nullptr;
	right = nullptr;
}

template <class K, class V>
int Node <K, V>::getHeight(Node <K, V>* node)
{
	if (node == nullptr)
		return 0;
	return node->height;
}

template <class K, class V>
void Node<K, V>::updateHeight()
{
	height = std::max(Node<K, V>::getHeight(left), Node<K, V>::getHeight(right)) + 1;
}

template <class K, class V>
int Node <K, V>::getBalance(Node <K, V>* node)
{
	if (node == nullptr)
		return 0;
	return getHeight(node->left) - getHeight(node->right);
}

template <class K, class V>
unsigned Node <K, V>::getKey()
{
	return this->key;
}

template <class K, class V>
Node<K,V>::Node(const Node<K,V> &other) :
    key {other.key},
    value {other.value},
    height {other.height}
{
    if (other.left)
        this->left = new Node<K,V>(*other.left);
    else
        this->left = nullptr;

    if (other.right)
        this->right = new Node<K,V>(*other.right);
    else
        this->right = nullptr;
}
