#pragma once

#include <cmath>
#include <stdlib.h>
#include <time.h>  
#include "Item.h"
#include "ItemData.h"
#include "Sword.h"
#include "Shield.h"
#include "Constants.h"

class ItemGenerator{
	public:
		std::vector<std::shared_ptr<Item>> generateItems(std::vector<int> enemyLevels);
		std::shared_ptr<Sword> generateSword(int enemyLevel);
		std::shared_ptr<Shield> generateShield(int enemyLevel);
	private:
		ItemRarities getRarity();
		void initOptionalFloat(std::optional<float>& optional);
		//temporary hardcoaded solution
		const float COMMON_CHANCE = 0.20f;
		const float UNCOMMON_CHANCE = 0.40f;
		const float	RARE_CHANCE = 0.60f;
		const float	EPIC_CHANCE = 0.70f;
		const float	LEGENDARY_CHANCE = 0.80f;
};

