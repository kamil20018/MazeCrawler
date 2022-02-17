#pragma once
#include "ItemData.h"
#include <sstream>
#include <SFML/Graphics.hpp>
class Item{
	public:
		Item(ItemTypes type, ItemRarities rarity, int level);
		ItemTypes getType();
		ItemRarities getRarity();
		virtual void print() {};
		virtual std::string getDescription() = 0;
		virtual std::string getBaseStatString() = 0;
		virtual std::string getSpecialStatString() = 0;
	protected:
		ItemTypes type;
		ItemRarities rarity;
		int level;
		sf::Texture texture;
	private:

};

