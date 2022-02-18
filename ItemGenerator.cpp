#include "ItemGenerator.h"

std::vector<std::shared_ptr<Item>> ItemGenerator::generateItems(std::vector<int> enemyLevels) {
	std::vector<std::shared_ptr<Item>> items;
	ItemTypes type = ItemTypes::SWORD;

	for (int level : enemyLevels) {
		for (int i = 0; i < 4; i++) { //more items for debug purposes
			items.push_back(generateSword(level));
			items.push_back(generateShield(level));
		}
	}
	return items;
}

ItemRarities ItemGenerator::getRarity() {
	float rarityRoll = utils::randFloat(0, 1);
	std::cout << "rarityRoll: " << rarityRoll << std::endl;
	ItemRarities rarity;
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
	return rarity;
}

void ItemGenerator::initOptionalFloat(std::optional<float>& optional) {
	if (not optional.has_value()) {
		optional = std::make_optional(0.0f);
	}
}

std::shared_ptr<Sword> ItemGenerator::generateSword(int enemyLevel) {
	ItemRarities rarity = getRarity();
	SwordProperties properties;
	properties.minAttack = enemyLevel * 3 + (float)utils::randInt(-2, 2);
	properties.maxAttack = enemyLevel * 8 + (float)utils::randInt(-2, 2);
	properties.weight = 1.5f + utils::randFloat(-0.3f, 0.3f);

	for (int i = 0; i < static_cast<int>(rarity); i++) {
		OptSwordProperties optProperty = (OptSwordProperties)( rand() % (int)(OptSwordProperties::LAST_ELEMENT) );
		switch (optProperty) {
			case OptSwordProperties::CRIT_CHANCE: {
				initOptionalFloat(properties.critChance);
				float newAmount = properties.critChance.value() + (3.0f + static_cast<int>(rarity)) * 2;
				properties.critChance.emplace(newAmount);
				break;
			}
				
			case OptSwordProperties::DAMAGE_PERCENT: { 
				initOptionalFloat(properties.damagePercent);
				float x = 2.0f + (float)rarity;
				float newAmount = properties.damagePercent.value() + std::sqrt(x) * std::log(x) * 10;
				properties.damagePercent.emplace(newAmount);
				break;
			}

			case OptSwordProperties::FIRE_BONUS: {
				initOptionalFloat(properties.fireBonus);
				float newAmount = properties.fireBonus.value() + (float)utils::randInt(3, 5);
				properties.fireBonus.emplace(newAmount);
				break;
			}
		}
	}
	return std::make_shared<Sword>(ItemTypes::SWORD, rarity, enemyLevel, properties);
}

std::shared_ptr<Shield> ItemGenerator::generateShield(int enemyLevel) {
	ItemRarities rarity = getRarity();
	ShieldProperties properties;
	properties.weight = 2.0f + utils::randFloat(-0.5f, 0.5f);
	properties.defence = (10.0f + (float)utils::randInt(-3, 3)) * enemyLevel;
	properties.blockChance = 15.0f + 2.0f * enemyLevel + (float)utils::randInt(-3.0f, 3.0f);

	for (int i = 0; i < static_cast<int>(rarity); i++) {
		OptShieldProperties optProperties = (OptShieldProperties)(rand() % (int)(OptShieldProperties::LAST_ELEMENT));
		switch (optProperties) {
			case OptShieldProperties::BONUS_BLOCK_CHANCE: {
				initOptionalFloat(properties.bonusBlockChance);
				float newAmount = properties.bonusBlockChance.value() + (float)utils::randInt(3, 6);
				properties.bonusBlockChance.emplace(newAmount);
				break;
			}
			case OptShieldProperties::DEFENSE_PERCENT: {
				initOptionalFloat(properties.defensePercent);
				float newAmount = properties.defensePercent.value() + (float)utils::randInt(8, 12);
				properties.defensePercent.emplace(newAmount);
				break;
			}
			case OptShieldProperties::ELEMENTAL_RESISTANCE: {
				initOptionalFloat(properties.elementalResistance);
				float newAmount = properties.elementalResistance.value() + (float)utils::randInt(7, 10);
				properties.elementalResistance.emplace(newAmount);
				break;
			}
		}
	}

	return std::make_shared<Shield>(ItemTypes::SHIELD, rarity, enemyLevel, properties);
}
