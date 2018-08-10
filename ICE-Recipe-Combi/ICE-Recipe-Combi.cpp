// ICE-Recipe-Combi.cpp : Defines the entry point for the application.
//

#include "ICE-Recipe-Combi.h"
#include "Recipe.h"

using namespace std;

int main()
{
	std::ifstream file("ICE-CombisDB.csv");
	RecipeFinder test = IngredientList(file);
	const Recipe<3> AppleJuice({ test.getIngredient("Nori"),test.getIngredient("Rice"),test.getIngredient("Oranggge") });
	cout << test.calcBonus(AppleJuice);
	cout << "Hello CMake." << endl;
	return 0;
}
