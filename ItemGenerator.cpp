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
				items.push_back(generateSword(level));
				items.push_back(generateSword(level));
				items.push_back(generateSword(level));
				items.push_back(generateSword(level));
		}
	}
	return items;
}

std::shared_ptr<Sword> ItemGenerator::generateSword(int enemyLevel) {

	ItemRarities rarity;
	float rarityRoll = utils::randFloat(0, 1);
	std::cout << "rarityRoll: " << rarityRoll << std::endl;
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

	SwordProperties properties;
	properties.minAttack = enemyLevel * 3 + (float)utils::randInt(-2, 2);
	properties.maxAttack = enemyLevel * 8 + (float)utils::randInt(-2, 2);
	properties.weight = 1.5f + utils::randFloat(-0.3f, 0.3f);


	for (int i = 0; i < static_cast<int>(rarity); i++) {
		OptSwordProperties optProperties = static_cast<OptSwordProperties>(
			rand() % static_cast<int>(OptSwordProperties::LAST_ELEMENT)
			);
		switch (optProperties) {

			case OptSwordProperties::CRIT_CHANCE: {
				if (not properties.critChance.has_value()) {
					properties.critChance = std::make_optional<float>(0.0f);
				}
				float newAmount = properties.critChance.value() + (3.0f + static_cast<int>(rarity)) * 2;
				properties.critChance.emplace(newAmount);
				break;
			}
				
			case OptSwordProperties::DAMAGE_PERCENT: { //added scope so that i can init variable in here
				if (not properties.damagePercent.has_value()) {
					properties.damagePercent = std::make_optional<float>(0.0f);
				}
				float x = 2.0f + (float)rarity;
				float newAmount = properties.damagePercent.value() + std::sqrt(x) * std::log(x) * 10;
				properties.damagePercent.emplace(newAmount);
				break;
			}

			case OptSwordProperties::FIRE_BONUS:
				std::cout << "elements not implemented yet" << std::endl;
				break;
		}
	}
	return std::make_shared<Sword>(ItemTypes::SWORD, rarity, enemyLevel, properties);
}
