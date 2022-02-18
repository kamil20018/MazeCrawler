#pragma once

#include "Item.h"
#include "ItemData.h"
#include <iostream>
class Shield : public Item {
	public:
		Shield(ItemTypes type, ItemRarities rarity, int level, ShieldProperties properties);
		ShieldProperties getProperties();
		virtual void print();
		virtual std::string getDescription();
		virtual std::string getBaseStatString();
		virtual std::string getSpecialStatString();
	private:
		ShieldProperties properties;
};
