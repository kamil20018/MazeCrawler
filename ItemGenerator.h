#pragma once
#include "Item.h"
#include <stdlib.h>
#include <time.h>  
#include "ItemData.h"
class ItemGenerator
{
	std::vector<Item> generateItems(std::vector<int> enemyLevels);
};

