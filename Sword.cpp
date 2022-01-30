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
	std::cout << "critChance: " << properties.critChance << std::endl;
	std::cout << "damagePercent: " << properties.damagePercent << std::endl;
	std::cout << "fireBonus: " << properties.fireBonus << std::endl;
	std::cout << std::endl;
}