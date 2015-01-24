#include "Item.h"

Item::Item(){
	m_filePath = "images/temp_img.png";
	m_name = "";
	m_type = "weapon";
	m_subType = "sword";

	m_backgroundBox = NULL;
	m_displaying = false;

	m_properties["value"] = 1;
	m_properties["stamina"] = 0;
	m_properties["agility"] = 0;
	m_properties["strength"] = 0;
	m_properties["intellect"] = 0;
	m_properties["luck"] = 0;
	m_properties["reqLvl"] = 0;
	m_properties["rarity"] = 0;

	m_id = -1;
}

Item::Item(string filePath, string name, string type, string subType, map<string, int> properties){
	m_filePath = filePath;
	m_name = name;
	m_type = type;
	m_subType = subType;
	m_properties = properties;

	m_backgroundBox = NULL;
	m_displaying = false;

	m_id = -1;
}

Item::~Item(void){
	deleteSelf();
}

string Item::getFilePath(){
	return m_filePath;
}

string Item::getName(){
	return m_name;
}

string Item::getType(){
	return m_type;
}

string Item::getSubType(){
	return m_subType;
}

int Item::getId(){
	return m_id;
}

void Item::setId(int id){
	if (id > -1){
		m_id = id;
	}
	else{
		m_id = -1;
	}
}

void Item::deleteSelf(){
}

bool Item::isDisplayingToolTip(){
	return m_displaying;
}

bool Item::operator ==(const Item &r){
	if(m_name == r.m_name){
		return true;
	}else{
		return false;
	}
}

void Item::itemDisplay(int x, int y){
	if (m_backgroundBox){
		delete m_backgroundBox;
		m_backgroundBox = NULL;
	}

	int boxWidth, boxHeight, boxNeededWidth;
	int numOfProps = 0;

	boxWidth = 200;
	boxHeight = 1;

	string tempString = "";

	for (auto curProp : m_properties){
		if (curProp.first != "reqLvl" && curProp.first != "rarity"){
			tempString.insert(0, "|" + curProp.first + ": " + to_string(curProp.second));
			numOfProps++;
		}
	}

	tempString.insert(0, "Name: " + m_name);
	numOfProps++;

	boxNeededWidth = (sizeof("Name:") + m_name.size()) * 8;

	boxHeight += 16 * numOfProps;

	if (boxNeededWidth > boxWidth){
		boxWidth = boxNeededWidth;
	}

	m_backgroundBox = GUI::addBox(x, y + (boxHeight / 2), boxWidth, boxHeight, 0, 0, 0);
	m_backgroundBox->setText(tempString);

	m_displaying = true;
}

void Item::stopDisplay(){
	if (m_backgroundBox){
		delete m_backgroundBox;
		m_backgroundBox = NULL;
	}

	m_displaying = false;
}

void Item::renderDisplay(){
	if (m_backgroundBox && m_displaying){
		m_backgroundBox->update();
	}
}

int Item::getProperty(string propertyName){
	for (auto curProperty : m_properties){
		if (curProperty.first == propertyName){
			return curProperty.second;
		}
	}

	return -1;
}

map<string, int> Item::getProperties(){
	return m_properties;
}