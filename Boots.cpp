#include "Boots.h"

Boots::Boots(ItemTypes type, ItemRarities rarity, int level, BootsProperties properties) : Item(type, rarity, level) {
	this->properties = properties;
}

BootsProperties Boots::getProperties() {
	return this->properties;
}

void Boots::print() {
}

std::string Boots::getDescription() {
	std::ostringstream desc;
	desc << this->rarity << " boots lvl " << this->level;
	return desc.str();
}

std::string Boots::getBaseStatString() {
	std::ostringstream desc;
	desc << "rarity: " << (int)rarity << '\n';
	desc << "weight: " << properties.weight << '\n';
	desc << "defence: " << properties.defence << '\n';
	desc << "moveCostRed: " << properties.moveCostReduction << '\n';
	return desc.str();
}

std::string Boots::getSpecialStatString() {
	std::ostringstream desc;
	if (properties.defenceBonus.has_value()) {
		desc << "defenceBonus: " << properties.defenceBonus.value() << '\n';
	}
	if (properties.moveCostBonus.has_value()) {
		desc << "moveCostBonus: " << properties.moveCostBonus.value() << '\n';
	}
	return desc.str();
}
