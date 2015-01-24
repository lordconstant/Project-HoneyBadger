#include "InventoryT.h"


InventoryT::InventoryT(int size){
	m_curSize = 0;
	m_size = size;
	m_full = false;

	for (int i = 0; i < m_size; ++i){
		m_itemNodes.push_back(NULL);
	}
}

InventoryT::~InventoryT(){
}

bool InventoryT::addItem(int id, int maxStack){
	int temp = 1;
	return addItem(id, temp, maxStack);
}

bool InventoryT::addItem(int id, int& curStack, int maxStack){
	if (maxStack < 1){
		maxStack = 1;
	}

	//Attempts to merge into existing nodes with item id
	for (auto* invNode : m_itemNodes){
		if (invNode){
			if (invNode->getId() == id){
				invNode->addToStack(curStack);

				if (curStack == 0){
					return true;
				}
			}
		}
	}

	//If it failed to merge in, it looks for free slots and adds itself in where possible
	for (auto* invNode : m_itemNodes){
		if (!invNode){
			invNode = new InventoryNodeT(id, curStack, maxStack);

			m_curSize++;

			if (curStack == 0){
				if (m_curSize != m_size){
					m_full = false;
				}
				else{
					m_full = true;
				}

				return true;
			}
		}
	}

	if (m_curSize != m_size){
		m_full = false;
	}
	else{
		m_full = true;
	}

	return false;
}

bool InventoryT::addItem(InventoryNodeT* item){
	if (!item){
		return false;
	}

	return addItem(item->getId(), item->m_curStack, item->getMaxStack());
}

bool InventoryT::addItemAt(int id, int maxStack, int loc){
	int temp = 1;
	return addItemAt(id, temp, maxStack, loc);
}

bool InventoryT::addItemAt(int id, int& curStack, int maxStack, int loc){
	if (loc < 0 || loc >= m_size){
		return false;
	}

	if (m_itemNodes.at(loc)){
		return false;
	}

	m_itemNodes.at(loc) = new InventoryNodeT(id, curStack, maxStack);

	m_curSize++;

	if (m_curSize != m_size){
		m_full = false;
	}
	else{
		m_full = true;
	}

	return true;
}

bool InventoryT::addInventory(InventoryT* otherInv){
	bool success = true;

	for (auto* otherInvNode : otherInv->m_itemNodes){
		if (!addItem(otherInvNode)){
			if (otherInvNode->getCurStack() == 0){
				otherInv->removeInvNode(otherInvNode);
			}

			success = false;
		}
	}

	return success;
}

bool InventoryT::checkForItem(int id){
	for (auto* invNode : m_itemNodes){
		if (invNode){
			if (invNode->getId() == id){
				return true;
			}
		}
	}

	return false;
}

InventoryNodeT* InventoryT::getNodeOfItem(int id){
	for (auto* invNode : m_itemNodes){
		if (invNode){
			if (invNode->getId() == id){
				return invNode;
			}
		}
	}

	return NULL;
}

InventoryNodeT* InventoryT::getItemAtNode(int nodeNum){
	if (nodeNum < 0 || nodeNum >= m_size){
		return false;
	}

	return m_itemNodes.at(nodeNum);
}

int InventoryT::getSize(){
	return m_size;
}

bool InventoryT::setSize(int size){
	if (size <= 0){
		size = 1;
	}

	if (m_curSize > size){
		return false;
	}

	sort();

	m_size = size;

	m_itemNodes.resize(size);
}

bool InventoryT::removeItem(int id, int amount){
	for (auto* invNode : m_itemNodes){
		if (invNode){
			if (invNode->getId() == id){
				invNode->removeFromStack(amount);

				if (invNode->getCurStack() <= 0){
					delete invNode;
					invNode = NULL;

					m_curSize--;
				}

				if (amount == 0){
					if (m_curSize != m_size){
						m_full = false;
					}
					else{
						m_full = true;
					}

					return true;
				}
			}
		}
	}

	if (m_curSize != m_size){
		m_full = false;
	}
	else{
		m_full = true;
	}

	return false;
}

bool InventoryT::removeItemAt(int loc){
	if (loc < 0 || loc >= m_size){
		return false;
	}

	if (m_itemNodes.at(loc)){
		delete m_itemNodes.at(loc);
		m_itemNodes.at(loc) = NULL;

		m_curSize--;
	}

	if (m_curSize != m_size){
		m_full = false;
	}
	else{
		m_full = true;
	}

	return true;
}

bool InventoryT::removeInvNode(InventoryNodeT* invNode){
	if (!invNode){
		return false;
	}

	for (auto* myInvNode : m_itemNodes){
		if (myInvNode == invNode){
			delete myInvNode;
			myInvNode = NULL;

			m_curSize--;

			if (m_curSize != m_size){
				m_full = false;
			}
			else{
				m_full = true;
			}

			return true;
		}
	}

	if (m_curSize != m_size){
		m_full = false;
	}
	else{
		m_full = true;
	}

	return false;
}

bool InventoryT::clearInv(){
	for (auto* invNode : m_itemNodes){
		if (invNode){
			delete invNode;
			invNode = NULL;
		}
	}

	m_curSize = 0;

	m_full = false;

	return true;
}

void InventoryT::sort(){
	for (int i = 0; i < m_size; ++i){
		for (int j = 0; j < m_size; ++j){
			if (i == j){
				continue;
			}

			if (!m_itemNodes[i]){
				if (i < j){
					if (m_itemNodes[j]){
						m_itemNodes[i] = m_itemNodes[j];
						m_itemNodes[j] = NULL;
					}
				}
			}
			else{
				if (m_itemNodes[j]){
					if (m_itemNodes[i]->getId() > m_itemNodes[j]->getId()){
						InventoryNodeT* tempNode;
						tempNode = m_itemNodes[i];
						m_itemNodes[i] = m_itemNodes[j];
						m_itemNodes[j] = tempNode;
					}
				}
			}
		}
	}
}