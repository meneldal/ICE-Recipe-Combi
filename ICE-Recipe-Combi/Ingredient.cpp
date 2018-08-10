#include "Ingredient.h"
#include <istream>
#include <string_view>

void Ingredient::addBonus(std::string other_ingredient, int16_t bonus)
{
	combis_.insert({ other_ingredient, bonus });
}

int Ingredient::findBonus(const std::string& other_ingredient) const
{
	if (const auto it = combis_.find(other_ingredient); it != combis_.end())
		return it->second;
	return 0;
}


IngredientList::IngredientList(std::istream & file)
{
	if (!file) throw std::exception("");
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
		auto ingredient1 = ingredients_.find(name1);
		if (ingredient1 == ingredients_.end())
		{
			ingredient1 = ingredients_.emplace(name1).first;
		}
		auto ingredient2 = ingredients_.find(name2);
		if (ingredient2 == ingredients_.end())
		{
			ingredient2 = ingredients_.emplace(name2).first;
		}
		ingredient1._Ptr->_Myval.addBonus(name2, iBonus); //goes through the const
		//ingredient2._Ptr->_Myval.addBonus(name1, iBonus);
	}
}

IngredientRef IngredientList::getIngredient(const std::string & name) const
{
	if (const auto it = ingredients_.find(name); it != ingredients_.end())
		return &*it;
	return nullptr;
}

