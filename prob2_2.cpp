#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <map>
#include <cstdio>

using namespace std;

class Object
{
	string valuable;
	float price;
public:
	Object()
	{

	}

	Object(string valuable, float price)
	{
		this->valuable = valuable;
		this->price = price;
	}

	string getValuable()
	{
		return valuable;
	}

	float getPrice()
	{
		return price;
	}
};

class House
{
	string street, city;
	uint32_t number;
	vector<Object> valuables;
public:
	House()
	{

	}

	House(string street, string city, uint32_t number)
	{
		this->street = street;
		this->city = city;
		this->number = number;
	}
	string getStreet()
	{
		return street;
	}

	string getCity()
	{
		return city;
	}

	uint32_t getNumber()
	{
		return number;
	}

	uint32_t getValuablesSize()
	{
		return valuables.size();
	}

	Object getValuable(uint32_t index)
	{
		return valuables.at(index);
	}

	void add(Object obj)
	{
		valuables.push_back(obj);
	}
};

float getTotalPrice(House house)
{
	float sum = 0.0f;
	for (uint32_t i = 0; i < house.getValuablesSize(); ++i)
	{
		sum += house.getValuable(i).getPrice();
	}
	return sum;
}

int main()
{
	vector<House> houses;
	string s;
	getline(cin, s);
	while (cin)
	{
		char *p = strtok(const_cast<char*>(s.c_str()), " ");
		string street, city;
		uint32_t i = 0, houseNumber = 0, nValuables = 0;
		vector<string>sValuables;
		vector<float>fValuables;
		while (p)
		{
			switch (i++)
			{
			case 0:

				street = p;

				break;

			case 1:
				city = p;
				break;

			case 2:

				houseNumber = atoi(p);

				break;

			case 3:

				nValuables = atoi(p);

				break;

			default:
			{
				if (i & 1) sValuables.push_back(p);
				else fValuables.push_back((float)atof(p));
			}
			}

			p = strtok(NULL, " ");
		}

		House h(street, city, houseNumber);
		for (uint32_t i = 0; i < nValuables; ++i)
		{
			h.add(Object(sValuables.at(i), fValuables.at(i)));
		}
		houses.push_back(h);
		getline(cin, s);
	}

	map<pair<string, string>, float> m;
	for (uint32_t i = 0; i < houses.size(); ++i)
	{
		m[make_pair(houses.at(i).getStreet(), houses.at(i).getCity())] += getTotalPrice(houses.at(i));
	}

	for (auto it = m.begin(); it != m.end(); it++)
	{
		std::cout << it->first.first << ' ' << it->first.second << "  - " << it->second << std::endl;
	}

	//std::cin.ignore();
	//std::cin.get();
	return 0;
}
