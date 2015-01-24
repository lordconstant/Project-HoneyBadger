#include "ItemDatabase.h"

ItemDatabase::ItemDatabase(void){
	ofstream myFile;

	m_databaseFile = "ItemDatabase.csv";
	m_propertiesFile = "ItemProperties.csv";

	myFile.open(m_databaseFile, ios::out | ios::app);
	myFile.close();

	myFile.open(m_propertiesFile, ios::out | ios::app);
	myFile.close();
}


ItemDatabase::~ItemDatabase(void){
}

ItemDatabase& ItemDatabase::getInstance(){
	static ItemDatabase iDatabase;

	return iDatabase;
}

bool ItemDatabase::addItemToDataBase(Item* newItem){
	if (!newItem){
		return false;
	}

	ifstream myIFile;
	string line;
	int nextId = 0;

	myIFile.open(m_databaseFile, ios::in);

	bool firstLine = true;

	while (getline(myIFile, line)){
		if (firstLine){
			firstLine = false;

			continue;
		}

		istringstream lineString(line);
		string field;
		getline(lineString, field, ',');
		nextId = atoi(field.c_str());
		getline(lineString, field, ',');

		if (field == newItem->getName()){
			newItem->setId(nextId);
			return false;
		}
	}

	nextId++;

	myIFile.close();

	string fileText;

	fileText = to_string(nextId) + ",";
	fileText += newItem->getName() + ",";
	fileText += newItem->getType() + ",";
	fileText += newItem->getSubType();

	ofstream myOFile;
	myOFile.open(m_databaseFile, ios::out | ios::app);
	myOFile << fileText.c_str() << "\n";
	myOFile.close();

	map<string, int> tempProperties = newItem->getProperties();

	fileText = to_string(nextId);

	for (auto curProperty : tempProperties){
		fileText += "," + curProperty.first + ",";
		fileText += to_string(curProperty.second);
	}

	myOFile.open(m_propertiesFile, ios::out | ios::app);
	myOFile << fileText.c_str() << "\n";
	myOFile.close();

	newItem->setId(nextId);

	return true;
}

Item* ItemDatabase::getItem(int id, bool load){
	if (id <= 0){
		return NULL;
	}

	ifstream myIFile;
	string line;
	int nextId = 0;

	myIFile.open(m_databaseFile, ios::in);

	bool firstLine = true;

	while (getline(myIFile, line)){
		if (firstLine){
			firstLine = false;

			continue;
		}

		istringstream lineString(line);
		string field;
		getline(lineString, field, ',');
		if (id == atoi(field.c_str())){
			string name;
			string type;
			string subType;
			string filePath;
			map<string, int> curProperties;

			getline(lineString, field, ',');
			name = field;
			getline(lineString, field, ',');
			type = field;
			getline(lineString, field, ',');
			subType = field;

			ifstream myIFileProp;
			string lineProp;

			myIFileProp.open(m_propertiesFile, ios::in);

			while (getline(myIFileProp, lineProp)){
				istringstream lineStringprop(lineProp);
				string fieldProp;

				getline(lineStringprop, fieldProp, ',');
				if (id == atoi(fieldProp.c_str())){
					while (getline(lineStringprop, fieldProp, ',')){
						string propName;
						propName = fieldProp;
						getline(lineStringprop, fieldProp, ',');
						curProperties[propName] = atoi(fieldProp.c_str());
					}

					filePath = "images/";
					filePath += subType;
					filePath += "_icon.png";

					Item* newItem = new Item(filePath, name, type, subType, curProperties);
					newItem->setId(id);

					if (load){
						for (auto curItem : m_loadedItems){
							if (curItem.first == id){
								return newItem;
							}
						}

						m_loadedItems[id] = newItem;

						return newItem;
					}
					else{
						return newItem;
					}
				}
			}
		}
	}

	return NULL;
}

bool ItemDatabase::loadItem(int id){
	for (auto curItem : m_loadedItems){
		if (curItem.first == id){
			return true;
		}
	}

	ifstream myIFile;
	string line;
	int nextId = 0;

	myIFile.open(m_databaseFile, ios::in);

	bool firstLine = true;

	while (getline(myIFile, line)){
		if (firstLine){
			firstLine = false;

			continue;
		}

		istringstream lineString(line);
		string field;
		getline(lineString, field, ',');
		if (id == atoi(field.c_str())){
			string name;
			string type;
			string subType;
			string filePath;
			map<string, int> curProperties;

			getline(lineString, field, ',');
			name = field;
			getline(lineString, field, ',');
			type = field;
			getline(lineString, field, ',');
			subType = field;

			ifstream myIFileProp;
			string lineProp;

			myIFileProp.open(m_propertiesFile, ios::in);

			while (getline(myIFileProp, lineProp)){
				istringstream lineStringprop(lineProp);
				string fieldProp;

				getline(lineStringprop, fieldProp, ',');
				if (id == atoi(fieldProp.c_str())){
					while (getline(lineStringprop, fieldProp, ',')){
						string propName;
						propName = fieldProp;
						getline(lineStringprop, fieldProp, ',');
						curProperties[propName] = atoi(fieldProp.c_str());
					}

					filePath = "images/";
					filePath += subType;
					filePath += "_icon.png";

					m_loadedItems[id] = new Item(filePath, name, type, subType, curProperties);

					myIFile.close();
					myIFileProp.close();

					return true;
				}
			}
		}
	}

	return false;
}
