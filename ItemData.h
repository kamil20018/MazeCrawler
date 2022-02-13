#pragma once
#include <iostream>

struct SwordProperties {
	//must have
	float minAttack = 0.0f;
	float maxAttack = 10.0f;
	float weight = 1.5f;
	//optional
	float critChance = -1.0f;
	float damagePercent = -1.0f;
	float fireBonus = -1.0f;
};

enum class OptSwordProperties {
	CRIT_CHANCE,
	DAMAGE_PERCENT,
	FIRE_BONUS,
	LAST_ELEMENT
};

enum class ItemTypes {
	SWORD,
	HELMET,
	BOOTS,
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
