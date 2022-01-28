#include "Sword.h"

Sword::Sword(ItemTypes type, ItemRarities rarity, int level, SwordProperties properties) : Item(type, rarity, level){
	this->properties = properties;
	print();
}

SwordProperties Sword::getProperties(){
	return this->properties;
}

void Sword::print() {
	std::cout << (int)rarity << std::endl;
	std::cout << properties.minAttack << std::endl;
	std::cout << properties.maxAttack << std::endl;
	std::cout << properties.weight << std::endl;
	std::cout << properties.critChance << std::endl;
	std::cout << properties.damagePercent << std::endl;
	std::cout << properties.fireBonus << std::endl;
}