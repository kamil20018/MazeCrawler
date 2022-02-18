#include "Shield.h"

Shield::Shield(ItemTypes type, ItemRarities rarity, int level, ShieldProperties properties) : Item(type, rarity, level) {
	this->properties = properties;
	print();
}

ShieldProperties Shield::getProperties() {
	return this->properties;
}

void Shield::print() {
}

std::string Shield::getDescription() {
	std::ostringstream desc;
	desc << this->rarity << " shield lvl " << this->level;
	return desc.str();
}

std::string Shield::getBaseStatString() {
	std::ostringstream desc;
	desc << "rarity: " << (int)rarity << '\n';
	desc << "weight: " << properties.weight << '\n';
	desc << "defence: " << properties.defence << '\n';
	desc << "blockChance: " << properties.blockChance << '\n';
	return desc.str();
}

std::string Shield::getSpecialStatString() {

	std::ostringstream desc;
	if (properties.bonusBlockChance.has_value()) {
		desc << "bonusBlockChance: " << properties.bonusBlockChance.value() << '\n';
	}
	if (properties.defensePercent.has_value()) {
		desc << "defensePercent: " << properties.defensePercent.value() << '\n';
	}
	if (properties.elementalResistance.has_value()) {
		desc << "elementalResistance: " << properties.elementalResistance.value() << '\n';
	}
	return desc.str();
}
