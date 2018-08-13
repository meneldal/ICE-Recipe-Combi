// ICE-Recipe-Combi.cpp : Defines the entry point for the application.
//

#include "ICE-Recipe-Combi.h"
#include "Recipe.h"

using namespace std;

int main()
{
	std::ifstream file("ICE-CombisDB.csv");
	RecipeFinder test = IngredientList(file);
	const Recipe<3> appleJuice({ test.getIngredient("Nori"),test.getIngredient("Rice"),test.getIngredient("Orange") });
	cout << test.calcBonus(appleJuice);
	const auto betterJuice = appleJuice.addIngredient(test.getIngredient("Apple"));
	cout << test.calcBonus(betterJuice);
	const Recipe<10> desert({ test.getIngredient("Flour"),test.getIngredient("Cinnamon"),test.getIngredient("Vanilla"),test.getIngredient("Nutmeg"),
		test.getIngredient("Sugar"),test.getIngredient("Cream"),test.getIngredient("Coffee"),test.getIngredient("Cocoa"),test.getIngredient("Milk"),test.getIngredient("Pumpkin") });
	cout << test.calcBonus(desert)<<"\n";
	test.disp(desert);
	auto a=test.getBestCountRecipes<10>(2000);
	test.disp(max_element(a.begin(), a.end(), [](auto x, auto y) {return x.second < y.second; })->first);
	cout << "Hello CMake." << endl;
	return 0;
}
