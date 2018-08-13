#pragma once

#include "Ingredient.h"
#include <array>
#include <algorithm>
#include <utility>
#include <map>
#include<vector>
#include <iostream>

template<int N>
struct Recipe
{
	/*const*/ std::array<IngredientRef, N> ingredients_;

	Recipe(const std::array<IngredientRef, N> ingredients) :ingredients_(ingredients) {}
	Recipe(){}
	Recipe<N + 1> addIngredient(IngredientRef ingredient) const;
	bool operator==(const Recipe& x) const { return ingredients_ == x.ingredients_; }
};

class RecipeFinder : public IngredientList
{

public:
	RecipeFinder(IngredientList ingredients) : IngredientList(std::move(ingredients)) {}
	template<int N>
	int calcBonus(const Recipe<N>& recipe) const;
	template<int N>
	std::vector<std::pair<Recipe<N>, int>> getBestCountRecipes(int count) const;
	template<int N>
	void disp(Recipe<N> rec, std::ostream& out = std::cout);
};



template <int N>
Recipe<N + 1> Recipe<N>::addIngredient(IngredientRef ingredient) const
{
	std::array<IngredientRef, N + 1> temp{};
	std::copy(ingredients_.begin(), ingredients_.end(), temp.begin());
	auto it1 = ingredients_.begin();
	for (auto it2 = temp.begin(); it1 != ingredients_.end(); ++it1, ++it2)
	{
		if (*it1 > ingredient)
			return
			*it2 = ingredient,
			std::copy(it1, ingredients_.end(), ++it2),
			Recipe<N + 1>{ temp };
		if (*it1 == ingredient) ///duplicate
			return temp[N] = { 127 }, Recipe<N + 1>{temp};
	}
	//if the ingredient we want to add is already the biggest id
	temp[N] = ingredient;
	return { temp };
}

template <int N>
int RecipeFinder::calcBonus(const Recipe<N>& recipe) const
{
	int bonus = 0;
	for (auto ingredient1 = recipe.ingredients_.begin(); ingredient1 != recipe.ingredients_.end(); ++ingredient1)
	{
		for (auto ingredient2 = ingredient1 + 1; ingredient2 != recipe.ingredients_.end(); ++ingredient2)
			bonus += findBonus(*ingredient1, *ingredient2);
	}
	return bonus * 2;
}

template<int N>
std::vector<std::pair<Recipe<N>, int>> RecipeFinder::getBestCountRecipes(int count) const
{
	auto recipeComp = [](const auto& x, const auto& y) {return x.ingredients_ > y.ingredients_; };
	typedef std::map < Recipe<N>, int, decltype(recipeComp)> RecipeList;// (recipeComp);
	RecipeList list(recipeComp);
	if constexpr(N > 2) {
		auto bestPrevious = getBestCountRecipes<N - 1>(count);
		for (auto recipe : bestPrevious)
		{
			for (IngredientRef ingredient = { 0 }; ingredient < IngredientRef{ 114 }; ingredient.id++)
			{
				auto newRecipe = recipe.first.addIngredient(ingredient);
				list[newRecipe] = calcBonus(newRecipe);
			}
		}
	}
	else if constexpr(N==2){
		for (IngredientRef ingredient = { 0 }; ingredient < IngredientRef{ 114 }; ingredient.id++)
		{
			for (IngredientRef ingredient2 = {ingredient.id + 1}; ingredient2 < IngredientRef{ 114 }; ingredient2.id++)
			{
				Recipe<2> recipe = { {ingredient, ingredient2} };
				list[recipe] = calcBonus(recipe);
			}
		}
	}
	std::vector < std::pair<Recipe<N>, int>> ra_list(list.begin(), list.end());
	std::nth_element(ra_list.begin(), ra_list.begin() + count, ra_list.end(), [](const auto& x, const auto& y) {return x.second > y.second; });
	return { ra_list.begin(), ra_list.begin() + count };
}

template <int N>
void RecipeFinder::disp(Recipe<N> recipe, std::ostream& out)
{
	for (auto ingredient = recipe.ingredients_.begin(); ingredient != recipe.ingredients_.end(); ++ingredient)
		out << ingredient_names_[*ingredient] << "\n";
	out << calcBonus(recipe);
}


