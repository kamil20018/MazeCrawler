#include "Sword.h"

Sword::Sword(ItemTypes type, ItemRarities rarity, int level, SwordProperties properties) : Item(type, rarity, level){
	this->properties = properties;
	print();
}

SwordProperties Sword::getProperties(){
	return this->properties;
}

void Sword::print() {
	std::cout << std::endl;
	std::cout << "rarity: " << (int)rarity << std::endl;
	std::cout << "minAttack: " << properties.minAttack << std::endl;
	std::cout << "maxAttack: " << properties.maxAttack << std::endl;
	std::cout << "weight: " << properties.weight << std::endl;
	if (properties.critChance.has_value()) {
		std::cout << "critChance: " << properties.critChance.value() << std::endl;
	}
	if (properties.damagePercent.has_value()) {
		std::cout << "damagePercent: " << properties.damagePercent.value() << std::endl;
	}
	if (properties.fireBonus.has_value()) {
		std::cout << "fireBonus: " << properties.fireBonus.value() << std::endl;
	}
	std::cout << std::endl;
}

std::string Sword::getDescription(){
	std::ostringstream desc;
	desc << this->rarity << " sword lvl " << this->level;
	return desc.str();
}

std::string Sword::getBaseStatString() {
	std::ostringstream desc;
	desc << "rarity: " << (int)rarity << '\n';
	desc << "weight: " << properties.weight << '\n';
	desc << "minAttack: " << properties.minAttack << '\n';
	desc << "maxAttack: " << properties.maxAttack << '\n';
	return desc.str();
}

std::string Sword::getSpecialStatString() {
	std::ostringstream desc;
	if (properties.critChance.has_value()) {
		desc << "critChance: " << properties.critChance.value() << '\n';
	}
	if (properties.damagePercent.has_value()) {
		desc << "damagePercent: " << properties.damagePercent.value() << '\n';
	}
	if (properties.fireBonus.has_value()) {
		desc << "fireBonus: " << properties.fireBonus.value() << '\n';
	}
	return desc.str();
}
