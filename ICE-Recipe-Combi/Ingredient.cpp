#include "Ingredient.h"
#include <istream>

IngredientList::IngredientList(std::istream & file)
{
	for (auto it : ingredient_combis_)
		for (auto it2 : it)
			it2 = 0;
	if (!file) throw std::exception("");
	uint8_t ingredients_counter = 0;
	for (std::string line; std::getline(file, line);)
	{
		const int comma1 = line.find(',');
		const std::string name1 = line.substr(0, comma1);
		const int comma2 = line.find(',', comma1 + 1);
		const std::string name2 = line.substr(comma1 + 1, comma2 - comma1 - 1);
		const int comma3 = line.find(',', comma2 + 1);
		const auto bonus = line.substr(comma2 + 1, comma3 - comma2 - 1);
		int iBonus;
		try {
			iBonus = std::stoi(bonus);
		}
		catch (...) { continue; }
		auto ingredient1 = ingredient_names_map_.find(name1);
		if (ingredient1 == ingredient_names_map_.end())
		{
			ingredient1 = ingredient_names_map_.emplace( name1, IngredientRef{ingredients_counter} ).first;
			ingredient_names_[ingredients_counter++] = name1;
		}
		auto ingredient2 = ingredient_names_map_.find(name2);
		if (ingredient2 == ingredient_names_map_.end())
		{
			ingredient2 = ingredient_names_map_.emplace(name2, IngredientRef{ ingredients_counter }).first;
			ingredient_names_[ingredients_counter++] = name2;
		}
		ingredient_combis_[ingredient1->second][ingredient2->second] = iBonus;
	}
}

IngredientRef IngredientList::getIngredient(const std::string & name) const
{
	if (const auto it = ingredient_names_map_.find(name); it != ingredient_names_map_.end())
		return { it->second };
	return { 127 };
}

int IngredientList::findBonus(IngredientRef first, IngredientRef second) const
{
	return ingredient_combis_[first][second];
}

