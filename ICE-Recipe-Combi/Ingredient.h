#pragma once

#include <array>
#include <string>
#include <iosfwd>
#include <unordered_map>

struct IngredientRef
{
	uint8_t id;
	operator int() const
	{ return id; }
};
class IngredientList
{
	std::array<std::string,128> ingredient_names_;
	std::unordered_map<std::string, IngredientRef> ingredient_names_map_;
	std::array<std::array<int8_t, 128>, 128> ingredient_combis_;

public:
	/**
	 * \brief 
	 * \param file reads list of ingredients and combinations from file
	 */
	explicit IngredientList(std::istream& file);
	IngredientRef getIngredient(const std::string & name) const;
	int findBonus(IngredientRef first, IngredientRef second) const;
};