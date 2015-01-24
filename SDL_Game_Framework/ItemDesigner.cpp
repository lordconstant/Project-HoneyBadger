#include "ItemDesigner.h"

ItemDesigner::ItemDesigner(void){
	properties["value"] = properties["stamina"] = properties["agility"] = properties["strength"] = properties["intellect"] = properties["luck"] = properties["reqLvl"] = properties["rarity"] = 0;
	name = iType = "";
}

ItemDesigner::~ItemDesigner(void){
}
//Creates a random item around the provided level
Item* ItemDesigner::createRandom(int lvl){
	int rndNum;

	rndNum = rand() % 3;

	Item* tempItem;

	switch (rndNum){
	case 0: 
		tempItem = createWeapon(lvl);
		ItemDatabase::getInstance().addItemToDataBase(tempItem);
		return tempItem;
		break;
	case 1:
		tempItem = createArmor(lvl);
		ItemDatabase::getInstance().addItemToDataBase(tempItem);
		return tempItem;
		break;
	case 2:
		tempItem = createConsumable(lvl);
		ItemDatabase::getInstance().addItemToDataBase(tempItem);
		return tempItem;
		break;
	default: Log::getInstance().addLine("Error occured while creating a random item"); break;
	}

	return NULL;
}
//Creates a randomised weapon around the lvl
Item* ItemDesigner::createWeapon(int lvl){
	string midName, endName;

	properties["value"] = properties["stamina"] = properties["agility"] = properties["strength"] = properties["intellect"] = properties["luck"] = properties["reqLvl"] = properties["rarity"] = 0;
	properties["minDamage"] = properties["maxDamage"] = properties["speed"] = properties["range"] = 0;
	int rndNum, quality, type, power;
	
	quality = rand() % QCOUNT;
	type = rand() % WTCOUNT;
	power = rand() % PCOUNT;

	rndNum = rand() % 3;

	if(rand() % 2 < 1){
		properties["reqLvl"] = lvl - rndNum;
	}else{
		properties["reqLvl"] = lvl - rndNum;
	}

	if (properties["reqLvl"] <= 0){
		properties["reqLvl"] = 1;
	}

	setQuality(quality, lvl);

	switch(quality){
		case WEAK:
			properties["minDamage"] = lvl * 3; properties["maxDamage"] = lvl * 3 + 10; properties["speed"] = 10;
		break;
		case DULL: 
			properties["minDamage"] = lvl * 2; properties["maxDamage"] = lvl * 3 + 10; properties["speed"] = 15;
		break;
		case PATHETIC:
			properties["minDamage"] = lvl; properties["maxDamage"] = lvl + 5; properties["speed"] = 10;
		break;
		case SILLY:
			properties["minDamage"] = lvl; properties["maxDamage"] = lvl + lvl * 2; properties["speed"] = 15;
		break;
		case BENDY: 
			properties["minDamage"] = lvl * 2; properties["maxDamage"] = lvl * 2 + 10; properties["speed"] = 5;
		break;
		case HEROIC: 
			properties["minDamage"] = lvl * 5; properties["maxDamage"] = lvl * 5 + 20; properties["speed"] = 10;
		break;
		case SWIFT: 
			properties["minDamage"] = lvl * 3; properties["maxDamage"] = lvl * 3 + 5; properties["speed"] = 3;
		break;
		case SHARP:
			properties["minDamage"] = lvl * 6; properties["maxDamage"] = lvl * 4 + 10; properties["speed"] = 10;
		break;
		case EPIC: 
			properties["minDamage"] = lvl * 8; properties["maxDamage"] = lvl * 8 + 15; properties["speed"] = 15;
		break;
		case GREAT: 
			properties["minDamage"] = lvl * 5; properties["maxDamage"] = lvl * 5 + 10; properties["speed"] = 9;
		break;
		case OLD: 
			properties["minDamage"] = lvl * 2; properties["maxDamage"] = lvl * 2 + 3; properties["speed"] = 15;
		break;
		case POWERFUL: 
			properties["minDamage"] = lvl * 7; properties["maxDamage"] = lvl * 7 + 14; properties["speed"] = 20;
		break;
		case MAJESTIC: 
			properties["minDamage"] = lvl * 8; properties["maxDamage"] = lvl * 8 + 5; properties["speed"] = 5;
		break;
		case UNIQUE: 
			properties["minDamage"] = lvl * 9; properties["maxDamage"] = lvl * 9 + 15; properties["speed"] = 15;
		break;
		case POINTLESS:
			properties["minDamage"] = lvl - 1; properties["maxDamage"] = lvl; properties["speed"] = 20;
		break;
		case GODLY: 
			properties["minDamage"] = lvl * 10; properties["maxDamage"] = lvl * 10 + 30; properties["speed"] = 15;
		break;
		case RANDOM: 
			properties["minDamage"] = lvl * properties["rarity"] * rand() % 3; properties["maxDamage"] = properties["minDamage"] + rand() % 20; properties["speed"] = 15;
		break;
		case SANTA:
			properties["minDamage"] = lvl * 9; properties["maxDamage"] = lvl * 9 + 18; properties["speed"] = 20;
		break;
		case DOLEY:
			properties["minDamage"] = lvl; properties["maxDamage"] = lvl + 3; properties["speed"] = 20;
		break;
	}

	switch(type){
		case SWORD:
			midName = "sword ";
			iType = "sword";
			properties["range"] = 0; properties["strength"] += lvl * 7; properties["stamina"] += lvl * 2; properties["speed"] += 3;
		break;
		case MACE:
			midName = "mace ";
			iType = "mace";
			properties["range"] = 0; properties["intellect"] += lvl * 5; properties["stamina"] += lvl * 2; properties["speed"] += 6;
		break;
		case BOW: 
			midName = "bow ";
			iType = "bow";
			properties["range"] = 1; properties["agility"] += lvl * 7; properties["luck"] += lvl * 5;
		break;
		case STAFF: 
			midName = "staff ";
			iType = "staff";
			properties["range"] = 0; properties["intellect"] += lvl * 10; properties["stamina"] += lvl * 3; properties["minDamage"] += 10; properties["maxDamage"] += 10; properties["speed"] += 10;
		break;
		case WAND: 
			midName = "wand ";
			iType = "wand";
			properties["range"] = 1; properties["intellect"] += lvl * 7; properties["speed"] -= 2;
		break;
		case CROSSBOW: 
			midName = "crossbow ";
			iType = "crossbow";
			properties["range"] = 1; properties["agility"] += lvl * 5; properties["stamina"] += lvl * 2; properties["minDamage"] += 5; properties["maxDamage"] += 5; properties["speed"] += 6;
		break;
		case SPEAR:
			midName = "spear ";
			iType = "spear";
			properties["range"] = 0; properties["strength"] += lvl * 7; properties["stamina"] += lvl * 4; properties["speed"] += 3;
		break;
		case AXE:
			midName = "axe ";
			iType = "axe";
			properties["range"] = 0; properties["strength"] += lvl * 8; properties["speed"] += 4;
		break;
	}

	switch(power){
		case STORM: 
			endName = "of the storm";
			properties["agility"] += lvl * 3; properties["strength"] += lvl * 2; properties["luck"] += lvl;
		break;
		case ZEPHYR: 
			endName = "of the zephyr";
			properties["agility"] += lvl * 4; properties["luck"] += lvl; properties["speed"] -= 2;
		break;
		case POWER: 
			endName = "of power";
			properties["intellect"] += lvl * 3; properties["stamina"] += lvl * 2;
		break;
		case WINTER: 
			endName = "of winter";
			properties["strength"] += lvl * 4;
		break;
		case NIGHT: 
			endName = "of night";
			properties["agility"] += lvl * 4; properties["stamina"] += lvl;
		break;
		case ELEMENTS:
			endName = "of the elements";
		break;
		case ACCURACY:
			endName = "of accuracy";
			properties["luck"] += lvl * 4; properties["minDamage"] += lvl; properties["maxDamage"] += lvl -2;
		break;
		case FIRE: 
			endName = "of fire";
		break;
		case ICE: 
			endName = "of ice";
		break;
		case EARTH: 
			endName = "of the earth";
		break;
		case LIGHTNING:
			endName = "of lightning";
		break;
		case GODS:
			endName = "of the gods";
			properties["stamina"] += lvl * 6;
		break;
		case UNICORN: 
			endName = "of the unicorn";
			properties["strength"] += lvl * 2; properties["agility"] += lvl * 2; properties["intellect"] += lvl * 2; properties["luck"] += lvl * 7;
		break;
		case MOUNTAIN: 
			endName = "of the mountain";
			properties["strength"] += lvl * 4; properties["stamina"] += lvl * 2;
		break;
		case STREAM: 
			endName = "of the stream";
			properties["intellect"] += lvl * 5; properties["speed"] -= 2;
		break;
		case IMAGINATION: 
			endName = "of imaginaton";
			properties["agility"] += lvl * 4; properties["intellect"] += lvl * 4; properties["luck"] += lvl * 4;
		break;
		case RAIDER: 
			endName = "of the raider";
			properties["strength"] += lvl * 2; properties["stamina"] += lvl * 4;
		break;
		case THIEF: 
			endName = "of the thief";
			properties["agility"] += lvl * 5; properties["luck"] += lvl * 3; properties["speed"] -= 2;
		break;
		case MOON:
			endName = "of the moon";
			properties["intellect"] += lvl * 6; properties["strength"] += lvl * 3;
		break;
		case JOKER:
			endName = "of the joker";
			properties["intellect"] += lvl; properties["strength"] += lvl; properties["agility"] += lvl;
		break;
	}

	int spec = rand() % 3;

	switch (spec)
	{
		//Strength spec
	case 0:
		properties["agility"] = 0; properties["intellect"] = 0;
		break;
		//Agility spec
	case 1:
		properties["strength"] = 0; properties["intellect"] = 0;
		break;
		//Intellect spec
	case 2:
		properties["strength"] = 0; properties["agility"] = 0;
		break;
	default:
		Log::getInstance().addLine("Spec select failed in Weapon - " + to_string(spec));
		break;
	}

	vector<string> propsToRemove;

	for (auto curProp : properties){
		if (curProp.second <= 0){
			propsToRemove.push_back(curProp.first);
		}
	}

	for (int i = 0; i < propsToRemove.size(); ++i){
		properties.erase(propsToRemove[i]);
	}

	name += midName + endName + " (" + to_string(properties["reqLvl"]) + ")";

	filePath = "images/";
	filePath += iType;
	filePath += "_icon.png";

	char c[255];

	strcpy_s(c, filePath.c_str());

	Item* tempWep = new Item(c, name, "Weapon", iType, properties);
	ItemDatabase::getInstance().addItemToDataBase(tempWep);

	properties.clear();

	int itemId = tempWep->getId();

	if (itemId > -1){
		delete tempWep;

		return ItemDatabase::getInstance().getItem(itemId);
	}

	return tempWep;
}
//Creates a randomised armor around the lvl
Item* ItemDesigner::createArmor(int lvl){
	string midName, endName;

	properties["value"] = properties["stamina"] = properties["agility"] = properties["strength"] = properties["intellect"] = properties["luck"] = properties["reqLvl"] = properties["rarity"] = 0;
	properties["defence"] = properties["magicResist"] = 0;
	int rndLvl, quality, type, power;

	quality = rand() % QCOUNT;
	type = rand() % ATCOUNT;
	power = rand() % PCOUNT;

	rndLvl = rand() % 3;

	if(rand() % 2 < 1){
		properties["reqLvl"] = lvl - rndLvl;
	}else{
		properties["reqLvl"] = lvl + rndLvl;
	}

	if (properties["reqLvl"] <= 0){
		properties["reqLvl"] = 1;
	}

	setQuality(quality, lvl);

	switch(quality){
		case WEAK:
			properties["defence"] = lvl; properties["magicResist"] = lvl;
		break;
		case DULL: 
			properties["defence"] = lvl; properties["magicResist"] = lvl;
		break;
		case PATHETIC:
			properties["defence"] = lvl * 0.5; properties["magicResist"] = lvl * 0.5;
		break;
		case SILLY:
			properties["defence"] = lvl; properties["magicResist"] = lvl*2;
		break;
		case BENDY: 
			properties["defence"] = lvl*2; properties["magicResist"] = lvl;
		break;
		case HEROIC: 
			properties["defence"] = lvl*4; properties["magicResist"] = lvl*2;
		break;
		case SWIFT: 
			properties["defence"] = lvl*2; properties["magicResist"] = lvl*3;
		break;
		case SHARP:
			properties["defence"] = lvl*4;
		break;
		case EPIC: 
			properties["defence"] = lvl*3; properties["magicResist"] = lvl*4;
		break;
		case GREAT: 
			properties["defence"] = lvl*3; properties["magicResist"] = lvl*2;
		break;
		case OLD: 
			properties["magicResist"] = lvl*4;
		break;
		case POWERFUL: 
			properties["defence"] = lvl*2; properties["magicResist"] = lvl*4;
		break;
		case MAJESTIC: 
			properties["defence"] = lvl*3; properties["magicResist"] = lvl*5;
		break;
		case UNIQUE: 
			properties["defence"] = lvl*4; properties["magicResist"] = lvl*2;
		break;
		case POINTLESS: 
			properties["defence"] = 1; properties["magicResist"] = 1;
		break;
		case GODLY: 
			properties["defence"] = lvl*5; properties["magicResist"] = lvl*5;
		break;
		case RANDOM: 
			properties["defence"] = lvl+properties["rarity"]*3; properties["magicResist"] = lvl*3;
		break;
		case SANTA:
			properties["defence"] = lvl*2; properties["magicResist"] = lvl*5;
		break;
		case DOLEY:
			properties["defence"] = lvl;
		break;
	}

	switch(type){
	case HANDS: 
		midName = "gauntlets ";
		iType = "gauntlets";
		properties["stamina"] += lvl * 2;
		properties["strength"] += lvl * 2;
		properties["agility"] += lvl * 2;
		properties["intellect"] += lvl * 2;
	break;
	case FEET:
		midName = "treads ";
		iType = "treads";
		properties["stamina"] += lvl * 2;
		properties["strength"] += lvl * 2;
		properties["agility"] += lvl * 2;
		properties["intellect"] += lvl * 2;
	break;
	case HEAD: 
		midName = "helm ";
		iType = "helm";
		properties["stamina"] += lvl * 3;
		properties["strength"] += lvl * 3;
		properties["agility"] += lvl * 3;
		properties["intellect"] += lvl * 3;
	break;
	case CHEST: 
		midName = "breastplate ";
		iType = "breastplate";
		properties["stamina"] += lvl * 5;
		properties["strength"] += lvl * 5;
		properties["agility"] += lvl * 5;
		properties["intellect"] += lvl * 5;
	break;
	case LEGS:
		midName = "leggings ";
		iType = "leggings";
		properties["stamina"] += lvl * 4;
		properties["strength"] += lvl * 4;
		properties["agility"] += lvl * 4;
		properties["intellect"] += lvl * 4;
	break;
	}

	endName = setPower(power, lvl);

	int spec = rand() % 3;

	switch (spec)
	{
		//Strength spec
	case 0:
		properties["agility"] = 0; properties["intellect"] = 0;
		break;
		//Agility spec
	case 1:
		properties["strength"] = 0; properties["intellect"] = 0;
		break;
		//Intellect spec
	case 2:
		properties["strength"] = 0; properties["agility"] = 0;
		break;
	default:
		Log::getInstance().addLine("Spec select failed in armor - " + to_string(spec));
		break;
	}

	vector<string> propsToRemove;

	for (auto curProp : properties){
		if (curProp.second <= 0){
			propsToRemove.push_back(curProp.first);
		}
	}

	for (int i = 0; i < propsToRemove.size(); ++i){
		properties.erase(propsToRemove[i]);
	}

	name += midName + endName + " (" + to_string(properties["reqLvl"]) + ")";

	filePath = "images/";
	filePath += iType;
	filePath += "_icon.png";

	char c[255];

	strcpy_s(c, filePath.c_str());

	Item* tempArmor = new Item(c, name, "Armor", iType, properties);
	ItemDatabase::getInstance().addItemToDataBase(tempArmor);

	properties.clear();

	int itemId = tempArmor->getId();

	if (itemId > -1){
		delete tempArmor;

		return ItemDatabase::getInstance().getItem(itemId);
	}

	return tempArmor;
}
//Creates a randomised Consumable around the lvl
Item* ItemDesigner::createConsumable(int lvl){
	properties["value"] = properties["stamina"] = properties["agility"] = properties["strength"] = properties["intellect"] = properties["luck"] = properties["reqLvl"] = properties["rarity"] = 0;
	properties["health"] = properties["mana"] = 0;

	int quality, type;
	string endName;

	quality = rand() % QCOUNT;
	type = rand() % CTCOUNT;

	setQuality(quality, lvl);
	
	properties["stamina"] = properties["agility"] = properties["strength"] = properties["intellect"] = properties["luck"] = properties["reqLvl"] = properties["rarity"] = 0;
	properties["reqLvl"] = lvl;

	switch (type){
	case BREAD:
		endName = "bread";
		iType = "bread";
		properties["health"] = lvl * 100; properties["rarity"] = 1;
		break;
	case CHEESE:
		endName = "cheese";
		iType = "cheese";
		properties["health"] = lvl * 115; properties["rarity"] = 1;
		break;
	case MILK:
		endName = "milk";
		iType = "milk";
		properties["mana"] = lvl * 100; properties["rarity"] = 1;
		break;
	case MANAPOT:
		endName = "mana potion";
		iType = "mana_potion";
		properties["mana"] = lvl * 200; properties["rarity"] = 2;
		break;
	case HEALTHPOT:
		endName = "health potion";
		iType = "health_potion";
		properties["health"] = lvl * 250; properties["rarity"] = 2;
		break;
	case CAKE:
		endName = "cake";
		iType = "cake";
		properties["health"] = lvl * 100; properties["mana"] = lvl * 80; properties["rarity"] = 2;
		break;
	case ORANGE:
		endName = "orange";
		iType = "orange";
		properties["health"] = lvl * 100; properties["mana"] = lvl * 40; properties["rarity"] = 1;
	break;
	case APPLE: 
		endName = "apple";
		iType = "apple";
		properties["health"] = lvl * 50; properties["mana"] = lvl * 75; properties["rarity"] = 1;
	break;
	case CHERRY:  
		endName = "cherry";
		iType = "cherry";
		properties["health"] = lvl * 25; properties["mana"] = lvl * 20; properties["rarity"] = 1;
	break;
	case WATER:  
		endName = "water"; 
		iType = "water";
		properties["mana"] = lvl * 200; properties["rarity"] = 1;
	break;
	case BEER: 
		endName = "beer";
		iType = "beer";
		properties["health"] = -lvl * 20; properties["mana"] = lvl * 150; properties["rarity"] = 2;
	break;
	}

	vector<string> propsToRemove;

	for (auto curProp : properties){
		if (curProp.second <= 0){
			propsToRemove.push_back(curProp.first);
		}
	}

	for (int i = 0; i < propsToRemove.size(); ++i){
		properties.erase(propsToRemove[i]);
	}

	name += endName + " (" + to_string(properties["reqLvl"]) + ")";

	filePath = "images/";
	filePath += iType;
	filePath += "_icon.png";

	char c[255];

	strcpy_s(c, filePath.c_str());

	Item* tempConsumable = new Item(c, name, "Consumable", iType, properties);
	ItemDatabase::getInstance().addItemToDataBase(tempConsumable);

	properties.clear();

	int itemId = tempConsumable->getId();

	if (itemId > -1){
		delete tempConsumable;

		return ItemDatabase::getInstance().getItem(itemId);
	}

	return tempConsumable;
}
//Sets the quality that the item will be
void ItemDesigner::setQuality(int quality, int lvl){
	switch(quality){
		case WEAK:
			name = "Weak ";
			properties["value"] = lvl * 50; properties["stamina"] = lvl; properties["rarity"] = 1;
		break;
		case DULL: 
			name = "Dull ";
			properties["value"] = lvl * 50; properties["stamina"] = lvl; properties["rarity"] = 1;
		break;
		case PATHETIC:
			name = "Pathetic ";
			properties["value"] = lvl * 50; properties["stamina"] = lvl; properties["rarity"] = 1;
		break;
		case SILLY:
			name = "Silly ";
			properties["value"] = lvl * 75; properties["stamina"] = lvl; properties["rarity"] = 1;
		break;
		case BENDY: 
			name = "Bendy ";
			properties["value"] = lvl * 100; properties["stamina"] = lvl; properties["rarity"] = 2;
		break;
		case HEROIC: 
			name = "Heroic ";
			properties["value"] = lvl * 150; properties["stamina"] = lvl*3; properties["rarity"] = 3;
		break;
		case SWIFT: 
			name = "Swift ";
			properties["value"] = lvl * 150; properties["stamina"] = lvl; properties["agility"] = lvl * 2; properties["rarity"] = 3;
		break;
		case SHARP:
			name = "Sharp ";
			properties["value"] = lvl * 125; properties["stamina"] = lvl; properties["strength"] = lvl; properties["rarity"] = 2;
		break;
		case EPIC: 
			name = "Epic ";
			properties["value"] = lvl * 400; properties["stamina"] = lvl * 5; properties["strength"] = lvl * 3; properties["agility"] = lvl * 3; properties["intellect"] = lvl * 3; properties["rarity"] = 5;
		break;
		case GREAT: 
			name = "Great ";
			properties["value"] = lvl * 150; properties["stamina"] = lvl * 2; properties["strength"] = lvl * 2; properties["agility"] = lvl * 2; properties["intellect"] = lvl * 2; properties["rarity"] = 3;
		break;
		case OLD: 
			name = "Old ";
			properties["value"] = lvl * 200; properties["stamina"] = lvl; properties["rarity"] = 1;
		break;
		case POWERFUL: 
			name = "Powerful ";
			properties["value"] = lvl * 225; properties["stamina"] = lvl * 4; properties["intellect"] = lvl * 3; properties["rarity"] = 4;
		break;
		case MAJESTIC: 
			name = "Majestic ";
			properties["value"] = lvl * 350; properties["stamina"] = lvl * 3; properties["agility"] = lvl * 3; properties["luck"] = lvl * 2; properties["intellect"] = lvl * 4; properties["rarity"] = 5;
		break;
		case UNIQUE: 
			name = "Unique ";
			properties["value"] = lvl * 200; properties["stamina"] = lvl * 3; properties["luck"] = lvl * 4; properties["rarity"] = 3;
		break;
		case POINTLESS: 
			name = "Pointless ";
			properties["value"] = lvl * 50; properties["rarity"] = 1;
		break;
		case GODLY: 
			name = "Godly ";
			properties["value"] = lvl * 500; properties["stamina"] = lvl * 6; properties["strength"] = lvl * 4; properties["agility"] = lvl * 4; properties["intellect"] = lvl * 4; properties["rarity"] = 6;
		break;
		case RANDOM: 
			name = "Random ";
			int tempRnd;
			tempRnd = rand() % 6;

			if(tempRnd < 1){
				tempRnd = 1;
			}

			properties["value"] = lvl * tempRnd * 100; properties["stamina"] = lvl * tempRnd; properties["strength"] = (lvl - tempRnd) * tempRnd; properties["agility"] = (lvl - tempRnd) * tempRnd; properties["intellect"] = (lvl - tempRnd) * tempRnd; properties["rarity"] = tempRnd;
		break;
		case SANTA:
			name = "Santa's ";
			properties["value"] = lvl * 600; properties["stamina"] = lvl * 6; properties["strength"] = lvl * 4; properties["intellect"] = lvl * 4; properties["luck"] = lvl * 3; properties["rarity"] = 6;
		break;
		case DOLEY:
			name = "Doley ";
			properties["value"] = lvl * 25; properties["stamina"] = lvl; properties["rarity"] = 1;
		break;
	}
}

//Sets the power that the item has
string ItemDesigner::setPower(int power, int lvl){
	switch(power){
		case STORM: 
			properties["agility"] += lvl * 3; properties["strength"] += lvl * 2; properties["intellect"] += lvl;
			return "of the storm";
		break;
		case ZEPHYR: 
			properties["agility"] += lvl * 4; properties["strength"] += lvl * 2; properties["intellect"] += lvl * 2;
			return "of the zephyr";
		break;
		case POWER: 
			properties["stamina"] += lvl * 2; properties["agility"] += lvl * 2; properties["strength"] += lvl * 3; properties["intellect"] += lvl * 4;
			return "of power";
		break;
		case WINTER: 
			properties["stamina"] += lvl * 2; properties["agility"] += lvl; properties["strength"] += lvl * 4; properties["intellect"] += lvl * 3;
			return "of winter";
		break;
		case NIGHT: 
			properties["agility"] += lvl * 4; properties["strength"] += lvl * 2; properties["intellect"] += lvl;
			return "of night";
		break;
		case ELEMENTS:
			return "of the elements";
		break;
		case ACCURACY:
			properties["agility"] += lvl * 3; properties["strength"] += lvl * 2; properties["intellect"] += lvl; properties["luck"] += lvl * 2;
			return "of accuracy";
		break;
		case FIRE: 
			return "of fire";
		break;
		case ICE: 
			return "of ice";
		break;
		case EARTH: 
			return "of the earth";
		break;
		case LIGHTNING:
			return "of lightning";
		break;
		case GODS:
			properties["stamina"] += lvl * 5; properties["agility"] += lvl * 3; properties["strength"] += lvl * 3; properties["intellect"] += lvl * 4;
			return "of the gods";
		break;
		case UNICORN: 
			properties["stamina"] += lvl;  properties["agility"] += lvl * 2; properties["strength"] += lvl * 3; properties["intellect"] += lvl * 3; properties["luck"] += lvl * 4;
			return "of the unicorn";
		break;
		case MOUNTAIN:
			properties["stamina"] += lvl * 3; properties["agility"] += lvl; properties["strength"] += lvl * 4; properties["intellect"] += lvl * 2;
			return "of the mountain";
		break;
		case STREAM: 
			properties["agility"] += lvl * 3; properties["strength"] += lvl * 2; properties["intellect"] += lvl * 4;
			return "of the stream";
		break;
		case IMAGINATION: 
			properties["agility"] += lvl * 3; properties["strength"] += lvl * 2; properties["intellect"] += lvl * 3; properties["luck"] += lvl;
			return "of imaginaton";
		break;
		case RAIDER: 
			properties["stamina"] += lvl * 3; properties["agility"] += lvl * 2; properties["strength"] += lvl * 3; properties["intellect"] += lvl;
			return "of the raider";
		break;
		case THIEF: 
			properties["stamina"] += lvl * 2; properties["agility"] += lvl * 3; properties["strength"] += lvl * 2; properties["intellect"] += lvl; properties["luck"] += lvl * 3;
			return "of the thief";
		break;
		case MOON:
			properties["agility"] += lvl; properties["strength"] += lvl * 3; properties["intellect"] += lvl * 5;
			return"of the moon";
		break;
		case JOKER:
			properties["agility"] += lvl * 4; properties["strength"] += lvl * 2; properties["intellect"] += lvl;
			return "of the joker";
		break;
	}
}