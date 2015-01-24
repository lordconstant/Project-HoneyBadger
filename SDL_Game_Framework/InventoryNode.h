#pragma once
#include <iostream>

template<class T>
class Inventory;

template<class T>
class InventoryNode{
	//Saves using setCurStack straight after construction
	InventoryNode(T* data, int curStack, int maxStack);
	//Assumes curStack is 1
	InventoryNode(T* data, int maxStack);

	InventoryNode();

	T* m_data;
	int m_curStack, m_maxStack;
public:
	~InventoryNode();

	T* getData();
	int getCurStack();
	int getMaxStack();

	void setCurStack(int stack);
	void setMaxStack(int maxStack);
	void setData(T* data);
	//Allows Inventory to access private and protected members
	friend Inventory<T>;
};

template<class T>
InventoryNode<T>::InventoryNode(T* data, int curStack, int maxStack){
	m_data = new T;
	*m_data = *data;
	m_curStack = curStack;
	m_maxStack = maxStack;
}

template<class T>
InventoryNode<T>::InventoryNode(T* data, int maxStack){
	m_data = new T;
	*m_data = *data;
	m_curStack = 1;
	m_maxStack = maxStack;
}

template<class T>
InventoryNode<T>::InventoryNode(){
	m_data = NULL;
	m_curStack = 0;
	m_maxStack = 0;
}

template<class T>
InventoryNode<T>::~InventoryNode(){
	if (m_data != NULL){
		delete m_data;
		m_data = NULL;
	}

	m_curStack = 0;
	m_maxStack = 0;
}

template<class T>
T* InventoryNode<T>::getData(){
	return m_data;
}

template<class T>
int InventoryNode<T>::getCurStack(){
	return m_curStack;
}

template<class T>
int InventoryNode<T>::getMaxStack(){
	return m_maxStack;
}

template<class T>
void InventoryNode<T>::setCurStack(int stack){
	m_curStack = stack;
}

template<class T>
void InventoryNode<T>::setMaxStack(int maxStack){
	m_maxStack = maxStack;
}
template<class T>
void InventoryNode<T>::setData(T* data){
	if(data == NULL){
		return;
	}

	if(m_data == NULL){
		m_data = new T;
	}

	*m_data = *data;
}