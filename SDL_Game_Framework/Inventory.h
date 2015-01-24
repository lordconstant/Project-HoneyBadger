#pragma once
#include "InventoryNode.h"
#include <iostream>

using namespace std;

template<class T>
class Inventory{
	InventoryNode<T>*  m_inv;
	int m_maxSize;
public:
	Inventory(int size);
	Inventory(int size, int maxStack, T* node);
	Inventory(int size, int maxStack, T* node, int nodeStack);
	~Inventory();

	//Returns remaining stack
	int addElement(T* element, int curstack, int maxStack);
	//Returns remaining stack
	int addElement(T* element, int maxStack);

	//Returns removed element
	T* removeElement(int pos);
	T* removeElement(T* element);
	InventoryNode<T>* getElement(int pos);

	//Permanently destroys the element
	bool destroyElement(int pos);
	bool destroyElement(T* element);
	bool destroyElement(T* element, int amount);

	//Sorts in order of lowest to highest
	bool sortElements();

	void show();
private:
	//Used for sorting
	void swapElements(int pos1, int pos2);
};

template<class T>
Inventory<T>::Inventory(int size){
	if(size > 0){
		m_inv = new InventoryNode<T>[size];
		m_maxSize = size;
	}else{
		return;
	}
}

template<class T>
Inventory<T>::Inventory(int size, int maxStack, T* node){
	if (size > 0 && node != NULL && maxStack > 0){
		m_inv = new InventoryNode<T>[size];
		m_maxSize = size;
		m_inv[0] = new InventoryNode<T>(node, maxStack);
	}
	else{
		return;
	}
}

template<class T>
Inventory<T>::Inventory(int size, int maxStack, T* node, int nodeStack){
	if (size > 0 && node != NULL && maxStack > 0 && nodeStack > 0){
		m_inv = new InventoryNode<T>[size];
		m_maxSize = size;
		addElement(node, nodeStack, maxStack);
	}else{
		return;
	}
}

template<class T>
int Inventory<T>::addElement(T* element, int curStack, int maxStack){
	int stack = curStack;

	for (int i = 0; i < m_maxSize; i++){
		if (m_inv[i].getData() != NULL){
			if (*m_inv[i].getData() == *element && m_inv[i].getCurStack() < m_inv[i].getMaxStack()){
				int difference = m_inv[i].getCurStack() + stack;

				if (difference > maxStack){
					stack = difference - maxStack;
					m_inv[i].setCurStack(m_inv[i].getMaxStack());
				}else{
					m_inv[i].setCurStack(difference);
					return NULL;
				}
			}
		}
	}

	for (int i = 0; i < m_maxSize; i++){
		if (m_inv[i].getData() == NULL){
			m_inv[i].setData(element);
			m_inv[i].setMaxStack(maxStack);
			
			int difference = m_inv[i].getCurStack() + stack;

			if (difference > maxStack){
				stack = difference - maxStack;
				m_inv[i].setCurStack(m_inv[i].getMaxStack());
			}else{
				m_inv[i].setCurStack(difference);
				return NULL;
			}
		}
	}

	return stack;
}

template<class T>
int Inventory<T>::addElement(T* element, int maxStack){
	return addElement(element, 1, maxStack);
}

template<class T>
T* Inventory<T>::removeElement(int pos){
	if (pos >= m_maxSize || pos < 0){
		return NULL;
	}

	T* tempElement;
	tempElement = m_inv[pos].getData();

	m_inv[pos].~InventoryNode();

	return tempElement;
}

template<class T>
T* Inventory<T>::removeElement(T* element){
	if (element == NULL){
		return NULL;
	}

	for (int i = 0; i < m_maxSize; i++){
		if(m_inv[i].getData() != NULL){
			if (*element == *m_inv[i].getData()){
				return removeElement(i);
			}
		}
	}

	return NULL;
}

template<class T>
InventoryNode<T>* Inventory<T>::getElement(int pos){
	return &m_inv[pos];
}

template<class T>
bool Inventory<T>::destroyElement(int pos){
	if (pos >= m_maxSize || pos < 0){
		return false;
	}

	m_inv[pos].~InventoryNode();

	return true;
}

template<class T>
bool Inventory<T>::destroyElement(T* element){
	if (element == NULL){
		return false;
	}

	for (int i = 0; i < m_maxSize; i++){
		if (element == m_inv[i]){
			return destroyElement(i);
		}
	}

	return false;
}

template<class T>
bool Inventory<T>::destroyElement(T* element, int amount){
	if (element == NULL || amount < 0){
		return false;
	}

	for (int i = 0; i < m_maxSize; i++){
		if (amount > 0){
			if(m_inv[i].getData() != NULL){
				if (*element == *m_inv[i].getData()){
					destroyElement(i);
					amount--;
				}
			}
		}
	}

	return true;
}

template<class T>
void Inventory<T>::swapElements(int pos1, int pos2){
	if(m_inv[pos1].getData() != NULL){
		T data;
		int stack, maxStack;

		data = *m_inv[pos1].getData();
		stack = m_inv[pos1].getCurStack();
		maxStack = m_inv[pos1].getMaxStack();

		m_inv[pos1].setData(m_inv[pos2].getData());
		m_inv[pos1].setCurStack(m_inv[pos2].getCurStack());
		m_inv[pos1].setMaxStack(m_inv[pos2].getMaxStack());

		m_inv[pos2].setData(&data);
		m_inv[pos2].setCurStack(stack);
		m_inv[pos2].setMaxStack(maxStack);
	}else{
		m_inv[pos1].setData(m_inv[pos2].getData());
		m_inv[pos1].setCurStack(m_inv[pos2].getCurStack());
		m_inv[pos1].setMaxStack(m_inv[pos2].getMaxStack());
		destroyElement(pos2);
	}
}

template<class T>
bool Inventory<T>::sortElements(){
	for (int i = 0; i < m_maxSize; i++){
		for (int j = 0; j < m_maxSize; j++){
			if (m_inv[i].getData() != NULL && m_inv[j].getData() != NULL){
				if (*m_inv[i].getData() < *m_inv[j].getData()){
					swapElements(i, j);
				}
			}
		}
	}
	return true;
}

template<class T>
void Inventory<T>::show(){
	for (int i = 0; i < m_maxSize; i++){
		if (m_inv[i].getData() != NULL){
			cout << "InvNum: |" << i+1 << "| Data: |" << *m_inv[i].getData() << "| CurStack: |" << m_inv[i].getCurStack() << "|" << endl;
		}
	}
}

template<class T>
Inventory<T>::~Inventory(){
	for (int i = 0; i < m_maxSize; i++){
		delete m_inv[i];
		m_inv[i] = NULL;
	}
}