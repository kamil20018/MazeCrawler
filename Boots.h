#pragma once

#include "Item.h"
#include "ItemData.h"
#include <iostream>
class Boots : public Item {
public:
	Boots(ItemTypes type, ItemRarities rarity, int level, BootsProperties properties);
	BootsProperties getProperties();
	virtual void print();
	virtual std::string getDescription();
	virtual std::string getBaseStatString();
	virtual std::string getSpecialStatString();
private:
	BootsProperties properties;
};

