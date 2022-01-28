#pragma once

#include "Item.h"
#include "ItemData.h"
#include <iostream>
class Sword : public Item
{	public: 
		Sword(ItemTypes type, ItemRarities rarity, int level, SwordProperties properties);
		SwordProperties getProperties();
		virtual void print();
	private:
		SwordProperties properties;
};

