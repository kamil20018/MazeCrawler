#include "Item.h"

Item::Item(ItemTypes type, ItemRarities rarity, int level) {
	this->type = type;
	this->rarity = rarity;
	this->level = level;
}

ItemTypes Item::getType() {
	return this->type;
}

ItemRarities Item::getRarity() {
	return this->rarity;
}
