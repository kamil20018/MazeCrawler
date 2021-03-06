#pragma once
#include <iostream>
#include <optional>

enum class ItemTypes {
	SWORD,
	HELMET,
	BOOTS,
	SHIELD,
	BREAST_PLATE,
	LAST_ELEMENT
};

struct SwordProperties {
	float minAttack = 0.0f;
	float maxAttack = 10.0f;
	float weight = 1.5f;

	std::optional<float> critChance;
	std::optional<float> damagePercent;
	std::optional<float> fireBonus;
};

enum class OptSwordProperties {
	CRIT_CHANCE,
	DAMAGE_PERCENT,
	FIRE_BONUS,
	LAST_ELEMENT
};

struct ShieldProperties {
	float weight = 2.0f;
	float defence = 0.0f;
	float blockChance = 10.0f;

	std::optional<float> bonusBlockChance;
	std::optional<float> defensePercent;
	std::optional<float> elementalResistance;
};

enum class OptShieldProperties {
	BONUS_BLOCK_CHANCE,
	DEFENSE_PERCENT,
	ELEMENTAL_RESISTANCE,
	LAST_ELEMENT
};

struct BootsProperties {
	float weight = 1.0f;
	float defence = 5.0f;
	float moveCostReduction = 10.0f;

	std::optional<float> defenceBonus;
	std::optional<float> moveCostBonus;
};

enum class OptBootsProperties {
	DEFENCE_BONUS,
	MOVE_COST_BONUS,
	LAST_ELEMENT
};



enum class ItemRarities {
	COMMON,
	UNCOMMON,
	RARE,
	EPIC,
	LEGENDARY,
	LAST_ELEMENT
};

inline std::string itemEnumToString(ItemTypes itemType) {
	switch (itemType) {
		case ItemTypes::SWORD:
			return "sword";
		case ItemTypes::BOOTS:
			return "boots";
		case ItemTypes::HELMET:
			return "helmet";
		case ItemTypes::SHIELD:
			return "shield";
		case ItemTypes::BREAST_PLATE:
			return "breastplate";
	}
	return "";
}

inline std::string itemEnumToString(ItemRarities itemRarity) {
	switch (itemRarity) {
		case ItemRarities::COMMON:
			return "common";
		case ItemRarities::UNCOMMON:
			return "uncommon";
		case ItemRarities::RARE:
			return "rare";
		case ItemRarities::EPIC:
			return "epic";
		case ItemRarities::LEGENDARY:
			return "legendary";
		case ItemRarities::LAST_ELEMENT:
			return "last element isn't rarity";
	}
	return ""; //won't be returned, all cases were covered
}

inline std::string itemEnumToString(OptSwordProperties property) {
	switch (property) {
		case OptSwordProperties::CRIT_CHANCE:
			return "crit chance";
		case OptSwordProperties::DAMAGE_PERCENT:
			return "damage percent";
		case OptSwordProperties::FIRE_BONUS:
			return "fire bonus";
		case OptSwordProperties::LAST_ELEMENT:
			return "last element isn't a property";
	}
	return ""; //won't return anything, all cases are covered
}

inline std::ostream& operator<<(std::ostream& os, ItemRarities rarity){
	switch (rarity) {
	case ItemRarities::COMMON:
		os << "common";
		break;
	case ItemRarities::UNCOMMON:
		os << "uncommon";
		break;	
	case ItemRarities::RARE:
		os << "rare";
		break;	
	case ItemRarities::EPIC:
		os << "epic";
		break;	
	case ItemRarities::LEGENDARY:
		os << "legendary";
		break;
	case ItemRarities::LAST_ELEMENT:
		os << "wrong rarity, cause it's last element";
		break;
	}
	return os;
}
