#pragma once

#include <unordered_set>
#include <unordered_map>
#include <string>
#include <iosfwd>

class Ingredient
{
	/**
	 * \brief Name of the ingredient (for display purposes and cross-reference)
	 */
	std::string name_;
	/**
	 * \brief Stores the bonus of the ingredient with other ingredients
	 */
	std::unordered_map<std::string, int16_t> combis_;

public:
	/**
	 * \brief Constructs the Ingredient with the name provided
	 * \param name name of the ingredient
	 */
	Ingredient(std::string name) : name_(std::move(name)) {}
	operator std::string() const { return name_; }
	bool operator==(const Ingredient& other) const { return name_ == other.name_; }
	void addBonus(std::string other_ingredient, int16_t bonus);
	int findBonus(const std::string& other_ingredient) const;
};
typedef const Ingredient* IngredientRef;
class IngredientList
{
	std::unordered_set<Ingredient, std::hash<std::string>> ingredients_;

public:
	/**
	 * \brief 
	 * \param file reads list of ingredients and combinations from file
	 */
	explicit IngredientList(std::istream& file);
	IngredientRef getIngredient(const std::string& name) const;
};