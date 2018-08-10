#pragma once

#include "Ingredient.h"
#include <array>
#include <utility>
#include <vector>

template<int N>
class Recipe
{
	const std::array<IngredientRef, N> ingredients_;

public:
	Recipe(const std::array<IngredientRef, N> ingredients) :ingredients_(ingredients) {}
	Recipe<N + 1> AddIngredient(IngredientRef ingredient);
	int calcBonus() const;
};

class RecipeFinder
{
	IngredientList ingredients_;

public:
	RecipeFinder(IngredientList ingredients) : ingredients_(std::move(ingredients)) {}
};



template <int N>
Recipe<N + 1> Recipe<N>::AddIngredient(IngredientRef ingredient)
{
	std::array<IngredientRef, N + 1> temp(ingredients_);
	temp[N] = ingredient;
	return {temp};
}

template <int N>
int Recipe<N>::calcBonus() const
{
	int bonus = 0;
	for (auto ingredient1 = ingredients_.begin(); ingredient1 != ingredients_.end(); ++ingredient1)
	{
		if (*ingredient1)
			for (auto ingredient2 = ingredient1 + 1; ingredient2 != ingredients_.end(); ++ingredient2)
				if (*ingredient2)
					bonus += (*ingredient1)->findBonus(**ingredient2);
	}
	return bonus * 2;
}


