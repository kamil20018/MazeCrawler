#include "ItemGenerator.h"

std::vector<Item> ItemGenerator::generateItems(std::vector<int> enemyLevels) {
	std::vector<Item> items;
	ItemTypes type = ItemTypes::SWORD;

	for (int level : enemyLevels) {
		switch (type) {
		case ItemTypes::SWORD:
			continue;
		}
	}
	return items;
}