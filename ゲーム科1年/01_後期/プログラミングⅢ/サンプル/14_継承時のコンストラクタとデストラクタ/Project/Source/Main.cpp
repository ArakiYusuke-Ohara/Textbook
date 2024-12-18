#include <iostream>
#include "Food/Fruit.h"
#include "Food/Meat.h"

using namespace std;

int main()
{
	// ¶¬
	Food* fruit = new Fruit;
	Food* meat = new Meat;

	// íœ
	delete fruit;
	delete meat;

	return 0;
}

