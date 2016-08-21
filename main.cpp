/*
# Copyright (c) 2016 Jingzhe Yu. All rights reserved.
# This program or module is free software: you can redistribute it and/or
# modify it under the terms of the GNU General Public Licence as published
# by the Free Software Foundation, either version 2 of the Licence, or
# version 3 of the Licence, or (at your option) any later version. It is
# provided for educational purposes and is distributed in the hope that
# it will be useful, but WITHOUT ANY WARRANTY; without even the implied
# warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See
# the GNU General Public Licence for more details.
*/

/*
# who-own-fish
Solve the who owns the fish problem

The Puzzle:
There are five houses in a row in different colors. In each house lives a person with a different nationality. The five owners drink a different drink, smoke a different brand of cigar and keep a different pet, one of which is a Walleye Pike.

Who owns the fish?

The 15 clues:

1. The Brit lives in the red house.
2. The Swede keeps dogs as pets.
3. The Dane drinks tea.
4. The green house is on the left of the white house.
5. The green house owner drinks coffee.
6. The person who smokes Pall Malls keeps birds.
7. The owner of the yellow house smokes Dunhills.
8. The man living in the house right in the center drinks milk.
9. The man who smokes Blends lives next to the one who keeps cats.
10. The Norwegian lives in the first house.
11. The man who keeps horses lives next to the one who smokes Dunhills.
12. The owner who smokes Bluemasters drinks beer.
13. The German smokes Princes.
14. The Norwegian lives next to the blue house.
15. The man who smokes Blends has a neighbor who drinks water.
*/

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

struct Family
{
	int country;    // 1-Brit 	2-Swede 	3-Dane 		4-Norway 		5-German
	int pet;        // 1-dog 	2-bird 		3-cat 		4-fish 			5-horse
	int color;      // 1-red 	2-green 	3-white 	4-blue 			5-yellow
	int smoke;      // 1-pall 	2-Dunhill 	3-blends 	4-Bluemaster 	5-prince
	int drink;      // 1-tea 	2-coffee 	3-milk 		4-beer 			5-water

	Family()
	: country(0)
	, pet(0)
	, color(0)
	, smoke(0)
	, drink(0)
	{
	}
};

/*
            family1     family2     family3     family4     family5
country:
pet:
color:
smoke:
drink:
*/

std::vector<Family> convertStringToFamilyArray(const std::string& str)
{
	std::vector<Family> familyArray;
	for(int i = 0; i < 5; i++)
	{
		Family f;
		f.country = atoi(str.substr(i, 1).c_str());
		f.pet = atoi(str.substr(i+5,1).c_str());
		f.color = atoi(str.substr(i+10,1).c_str());
		f.smoke = atoi(str.substr(i+15,1).c_str());
		f.drink = atoi(str.substr(i+20,1).c_str());
		familyArray.push_back(f);
	}

	return familyArray;
}

bool canPlace(const std::string& str, int index, int number)
{
    int row = index / 5;
	for(int i=0; i<5;i++)
	{
        int n = row*5+i;
		if(n != index)
		{
			if(str.at(n) == '0' + number)
			{
				return false;
			}
		}
	}
	return true;
}

bool checkRules(const std::vector<Family>& familyArray)
{
	//rule 1 The Brit lives in the red house
	bool good = false;
	for(int i = 0; i < 5; i++)
	{
		Family f = familyArray[i];
		if ((f.country == 1||f.country == 0) && (f.color == 1||f.color==0))
		{
			good = true;
			break;
		}
	}
	if(!good)
        return false;


	//rule2 The Swede keeps dogs as pets
	good = false;
	for(int i = 0; i < 5; i++)
	{
		Family f = familyArray[i];
		if ((f.country == 2||f.country==0) && (f.pet == 1||f.pet==0))
		{
			good = true;
			break;
		}
	}
	if(!good)
        return false;

	//rule3 The Dane drinks tea
	good = false;
	for(int i = 0; i < 5; i++)
	{
		Family f = familyArray[i];
		if ((f.country==0||f.country == 3) && (f.drink==0||f.drink == 1))
		{
			good = true;
			break;
		}
	}
	if(!good)
        return false;

	//rule4 The green house is on the left of the white house.
	good = false;
	for(int i = 0; i < 5 && !good; i++)
	{
		Family f = familyArray[i];
		if(f.color == 2||f.color==0)
		{
            if(i+1 < 5)
            {
                Family f1 = familyArray[i+1];
				if(f1.color == 3||f1.color==0)
				{
					good = true;
				}
            }
		}
	}
	if(!good)
        return false;

	//rule5 The green house owner drinks coffee
	good = false;
	for(int i = 0; i < 5; i++)
	{
		Family f = familyArray[i];
		if ((f.color==0||f.color == 2) && (f.drink==0||f.drink == 2))
		{
			good = true;
			break;
		}
	}
	if(!good)
        return false;

	//rule6 The person who smokes Pall Malls keeps birds.
	good = false;
	for(int i = 0; i < 5; i++)
	{
		Family f = familyArray[i];
		if ((f.smoke==0||f.smoke == 1) && (f.pet==0 ||f.pet == 2))
		{
			good = true;
			break;
		}
	}
	if(!good)
        return false;

	//rule7 The owner of the yellow house smokes Dunhills.
	good = false;
	for(int i = 0; i < 5; i++)
	{
		Family f = familyArray[i];
		if ((f.color==0||f.color == 5) && (f.smoke==0||f.smoke == 2))
		{
			good = true;
			break;
		}
	}
	if(!good)
        return false;

	//rule8 he man living in the house right in the center drinks milk.
	good = false;
	if (familyArray[2].drink == 0||familyArray[2].drink == 3)
	{
		good = true;
	}
	if(!good)
        return false;

	//rule9 The man who smokes Blends lives next to the one who keeps cats.
	good = false;
	for(int i = 0; i < 5 && !good; i++)
	{
		Family f = familyArray[i];
		if(f.smoke==0||f.smoke == 3)
		{
			for(int j = 0; j < 5 && !good; j++)
			{
				if(i == j)
				{
					continue;
				}
				Family f1 = familyArray[j];
				if((f1.pet==0||f1.pet == 3) && (i == j-1 || i == j+1))
				{
					good = true;
				}
			}
		}
	}
	if(!good)
        return false;

	//rule10 The Norwegian lives in the first house.
	good = false;
	if (familyArray[0].country == 0||familyArray[0].country == 4)
	{
		good = true;
	}
	if(!good)
        return false;

	//rule11 he man who keeps horses lives next to the one who smokes Dunhills.
	good = false;
	for(int i = 0; i < 5 && !good; i++)
	{
		Family f = familyArray[i];
		if(f.pet==0||f.pet == 5)
		{
			for(int j = 0; j < 5 && !good; j++)
			{
				if(i == j)
				{
					continue;
				}
				Family f1 = familyArray[j];
				if((f1.smoke==0||f1.smoke == 2) && (i == j-1 || i == j+1))
				{
					good = true;
				}
			}
		}
	}
	if(!good)
        return false;

	//rule12 The owner who smokes Bluemasters drinks beer.
	good = false;
	for(int i = 0; i < 5; i++)
	{
		Family f = familyArray[i];
		if ((f.smoke==0||f.smoke == 4) && (f.drink == 0||f.drink == 4))
		{
			good = true;
			break;
		}
	}
	if(!good)
        return false;

	//rule13 The German smokes Princes.
	good = false;
	for(int i = 0; i < 5; i++)
	{
		Family f = familyArray[i];
		if ((f.country==0||f.country == 5) && (f.smoke==0||f.smoke == 5))
		{
			good = true;
			break;
		}
	}
	if(!good)
        return false;

	//rule14 The Norwegian lives next to the blue house.
	good = false;
	for(int i = 0; i < 5 && !good; i++)
	{
		Family f = familyArray[i];
		if(f.country==0||f.country == 4)
		{
			for(int j = 0; j < 5 && !good; j++)
			{
				if(i == j)
				{
					continue;
				}
				Family f1 = familyArray[j];
				if((f1.color==0||f1.color == 4) && (i == j-1 || i == j+1))
				{
					good = true;
				}
			}
		}
	}
	if(!good)
        return false;

	//rule15 The man who smokes Blends has a neighbor who drinks water.
	good = false;
	for(int i = 0; i < 5 && !good; i++)
	{
		Family f = familyArray[i];
		if(f.smoke==0||f.smoke == 3)
		{
			for(int j = 0; j < 5 && !good; j++)
			{
				if(i == j)
				{
					continue;
				}
				Family f1 = familyArray[j];
				if((f1.drink==0||f1.drink == 5) && (i == j-1 || i == j+1))
				{
					good = true;
				}
			}
		}
	}
	if(!good)
        return false;

	return true;

}

void calculate(std::string str)
{
	//std::cout << "calculate: " << str << std::endl;
	std::size_t index = str.find('0');
	if (index == std::string::npos)
	{
		//print out
		std::cout << "------------------------------------------" << std::endl;
		for(int i=0; i< 5; i++)
		{
			std::cout << str.at(i*5) << " " << str.at(i*5+1) << " " << str.at(i*5+2) << " " << str.at(i*5+3) << " " << str.at(i*5+4) << std::endl;
		}

		std::vector<Family> familyArray = convertStringToFamilyArray(str);
		for(int i=0; i< 5; i++)
		{
            Family f = familyArray[i];
            if(f.pet == 4)
            {
                std::cout << "country " << f.country << " owns the fish" << std::endl;
            }
		}
		std::cout << "------------------------------------------" << std::endl;
		return;
	}

	for(int number = 1; number <= 5; number++)
	{
		if(canPlace(str, index, number))
		{
			str.replace(index, 1, 1, '0' + number);
		}
		else
		{
			continue;
		}

		std::vector<Family> familyArray = convertStringToFamilyArray(str);
		if(checkRules(familyArray))
		{
			//this str is good so far, go to next step
			calculate(str);
		}
	}

}

int main()
{
	std::cout << "start calculate..." << std::endl;
	std::string str;
	for(int i=0; i<25;i++)
	{
		str.append("0");
	}

	calculate(str);
	std::cout << "finish calculation." << std::endl;
}
