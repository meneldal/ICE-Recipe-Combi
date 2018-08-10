#pragma once

#include "Ingredient.h"
#include <array>
#include <utility>
#include <vector>

template<int N>
struct Recipe
{
	const std::array<IngredientRef, N> ingredients_;

	Recipe(const std::array<IngredientRef, N> ingredients) :ingredients_(ingredients) {}
	Recipe<N + 1> AddIngredient(IngredientRef ingredient);
};

class RecipeFinder: public IngredientList
{

public:
	RecipeFinder(IngredientList ingredients) : IngredientList(ingredients){}
	template<int N>
	int calcBonus(const Recipe<N>& recipe) const;
};



template <int N>
Recipe<N + 1> Recipe<N>::AddIngredient(IngredientRef ingredient)
{
	std::array<IngredientRef, N + 1> temp(ingredients_);
	temp[N] = ingredient;
	return {temp};
}

template <int N>
int RecipeFinder::calcBonus(const Recipe<N>& recipe) const
{
	int bonus = 0;
	for (auto ingredient1 = recipe.ingredients_.begin(); ingredient1 != recipe.ingredients_.end(); ++ingredient1)
	{
			for (auto ingredient2 = ingredient1 + 1; ingredient2 != recipe.ingredients_.end(); ++ingredient2)
					bonus += findBonus(*ingredient1,*ingredient2);
	}
	return bonus * 2;
}


