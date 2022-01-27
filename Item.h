#pragma once
#include "ItemData.h"
#include <SFML/Graphics.hpp>
class Item
{
	public:
		Item(ItemTypes type, ItemRarities rarity, int level);
		ItemTypes getType();
		ItemRarities getRarity();
	protected:
		ItemTypes type;
		ItemRarities rarity;
		int level;
		sf::Texture texture;
	private:

};

