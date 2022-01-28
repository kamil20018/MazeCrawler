#pragma once

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
