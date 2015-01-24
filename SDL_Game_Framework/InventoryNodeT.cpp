#include "InventoryNodeT.h"


InventoryNodeT::InventoryNodeT(int id, int curStack, int maxStack){
	m_id = id;
	m_maxStack = 1;
	m_curStack = 0;

	setMaxStack(maxStack);
	addToStack(curStack);
}


InventoryNodeT::~InventoryNodeT(){
}

void InventoryNodeT::setId(int id){
	m_id = id;
}

void InventoryNodeT::setMaxStack(int maxStack){
	if (maxStack < 1){
		return;
	}

	m_maxStack = maxStack;

	if (m_curStack > m_maxStack){
		m_curStack = m_maxStack;
	}
}

void InventoryNodeT::addToStack(int& amount){
	if (amount <= 0){
		return;
	}

	if (m_curStack == m_maxStack){
		return;
	}

	m_curStack += amount;

	if (m_curStack > m_maxStack){
		int remaining = m_curStack - m_maxStack;

		m_curStack = m_maxStack;

		amount = remaining;
	}
	else{
		amount = 0;
	}
}

void InventoryNodeT::removeFromStack(int& amount){
	if (amount < -1 || amount == 0 || m_curStack == 0){
		return;
	}

	if (amount != -1){
		int stackStart = m_curStack;

		m_curStack -= amount;

		if (m_curStack < 0){
			m_curStack = 0;
		}

		amount -= stackStart - m_curStack;
	}
	else{
		m_curStack = 0;
	}
}

int InventoryNodeT::getId(){
	return m_id;
}

int InventoryNodeT::getCurStack(){
	return m_curStack;
}

int InventoryNodeT::getMaxStack(){
	return m_maxStack;
}