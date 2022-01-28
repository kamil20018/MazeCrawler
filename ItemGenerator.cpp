#include "ItemGenerator.h"

std::vector<std::shared_ptr<Item>> ItemGenerator::generateItems(std::vector<int> enemyLevels) {
	std::vector<std::shared_ptr<Item>> items;
	ItemTypes type = ItemTypes::SWORD;

	for (int level : enemyLevels) {
		switch (type) {
		case ItemTypes::SWORD:
			items.push_back(generateSword(level));
			items.push_back(generateSword(level));
			items.push_back(generateSword(level));
			items.push_back(generateSword(level));
		}
	}
	return items;
}

std::shared_ptr<Sword> ItemGenerator::generateSword(int enemyLevel){

	ItemRarities rarity;
	float rarityRoll = utils::randFloat(0, 1);

	if (rarityRoll > this->LEGENDARY_CHANCE) {
		rarity = ItemRarities::LEGENDARY;
	}
	else if (rarityRoll > this->EPIC_CHANCE) {
		rarity = ItemRarities::EPIC;
	}
	else if (rarityRoll > this->RARE_CHANCE) {
		rarity = ItemRarities::RARE;
	}
	else if (rarityRoll > this->UNCOMMON_CHANCE) {
		rarity = ItemRarities::UNCOMMON;
	}
	else {
		rarity = ItemRarities::COMMON;
	}

	std::cout << "item rarity: " << (int)rarity << std::endl;

	SwordProperties properties;
	properties.minAttack = enemyLevel * 3 + utils::randInt(-2, 2);
	properties.maxAttack = enemyLevel * 8 + utils::randInt(-2, 2);
	properties.weight = 1.5f + utils::randFloat(-0.3f, 0.3f);


	for (int i = 0; i <= static_cast<int>(rarity); i++) {
		OptSwordProperties optProperties = static_cast<OptSwordProperties>(
			rand() % static_cast<int>(OptSwordProperties::LAST_ELEMENT)
		);
		switch (optProperties) {
			case OptSwordProperties::CRIT_CHANCE:
				if (properties.critChance < 0.0f) {
					properties.critChance = 0.0f;
				}
				properties.critChance += (3.0f + static_cast<int>(rarity)) * 2;
				break;
			case OptSwordProperties::DAMAGE_PERCENT:{ //added scope so that i can init variable in here
				if (properties.damagePercent < 0.0f) {
					properties.damagePercent = 0.0f;
				}
				float x = 2.0f + (float)rarity;
				properties.damagePercent += std::sqrt(x) * std::log(x) * 10;
				break;
			}
			case OptSwordProperties::FIRE_BONUS:
				std::cout << "elements not implemented yet" << std::endl;
				break;
		}
	}
	return std::make_shared<Sword>(ItemTypes::SWORD, rarity, enemyLevel, properties);
}
