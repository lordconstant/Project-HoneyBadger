#pragma once
#include "AWSprite.h"
#include "GUI.h"
#include <map>
#include "Log.h"

class Item: public AWSprite{
	int m_id;
	string m_name, m_type, m_subType, m_filePath;
	map<string, int> m_properties;
protected:
	GUIBox* m_backgroundBox;
	bool m_displaying;
public:
	Item();
	Item(string filePath, string name, string type, string subType, map<string, int> properties);
	~Item(void);

	string getFilePath();
	string getName();
	string getType();
	string getSubType();

	int getId();

	void setId(int id);

	bool isDisplayingToolTip();
	virtual void deleteSelf();
	virtual void itemDisplay(int x, int y);

	void stopDisplay();

	void renderDisplay();

	int getProperty(string propertyName);
	map<string, int> getProperties();

	bool operator ==(const Item &r);
};

