// Lab_4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <string>
#include <iostream>
#include "..\Library\Table.h"
#include "..\Library\News_Agencies.h"

using namespace News_Agencies;
using namespace Tab_Agencies;
const std::string Names[] = { "Print edition", "Radiostation", "TV company" };
const std::string Menu[] = { "1. Add a agency", "2. Find a agency",
"3. Delete a agency", "4. Replace a agency",
"5. Show all", "6. Use an Iterator", "7. Use an Iterator by type",
"8. Check the constant object", "0. Quit" },

Choice = "Make your choice",
Msg = "You are wrong; repeate please";
int Answer(const std::string alt[], int n);
int Add(Table&), Find(Table&), Remove(Table&), Replace(Table&), ShowAll(Table&), Iter(Table&), IterByAgType(Table&), ConstObj(Table&);
int(*Funcs[])(Table&) = { nullptr, Add, Find, Remove, Replace, ShowAll, Iter, IterByAgType, ConstObj };
const int Num = sizeof(Menu) / sizeof(Menu[0]);
int main()
{
	Table ar;
	int ind;
	try {
		while (ind = Answer(Menu, Num))
			Funcs[ind](ar);
		std::cout << "That's all. Buy!" << std::endl;
	}
	catch (const std::exception & er)
	{
		std::cout << er.what() << std::endl;
	}
	return 0;
}
int Answer(const std::string alt[], int n)
{
	int answer;
	std::string prompt = Choice;
	std::cout << "\nWhat do you want to do:" << std::endl;
	for (int i = 0; i < n; i++)
		std::cout << alt[i].c_str() << std::endl;
	do {
		std::cout << prompt.c_str() << ": -> ";
		prompt = Msg;
		std::cin >> answer;
		if (!std::cin.good())
		{
			//std::cout << "Error when number of choice was entered; nRepeat, please." << std::endl;
			std::cin.clear();
			std::cin.ignore(80, '\n');
		}
		else
		{
			if (std::cin.peek() != '\n')
			{
				std::cin.ignore(80, '\n');
				answer = -1;
			};
		};
	} while (answer < 0 || answer >= n);
	std::cin.ignore(80, '\n');
	return answer;
}
const std::string Ag[] = { "1. Print edition", "2. Radiostation", "3. TV company", "0. Quit" };
const int NumAg = sizeof(Ag) / sizeof(Ag[0]);
int Add(Table & tab)
{
	Agency* ptr = nullptr;	// Агенство класса Agency (базовый класс)
	//Print_edition pe;		// Агенство класса Print_edition
	//Radiostation r;			// Агенство класса Radiostation
	//TV_company tv;			// Агенство класса TV_company
	std::string name;		// Название агенства
	int ans;
	while (ans = Answer(Ag, NumAg)) {
		std::cout << "Enter name for agency: --> ";
		std::getline(std::cin, name, '\n');
		if (!std::cin.good())
			throw std::exception("Error when a agency name was entered");
		switch (ans) {
		case 1: // Print_Edition
			ptr = new Print_edition;
			break;
		case 2: // Radiostation
			ptr = new Radiostation;
			break;
		case 3: //TV_company
			ptr = new TV_company;
			break;
		}
		std::cin >> (*ptr);
		if (!std::cin.good())
			throw std::exception("Error when agency values were entered");
		if (tab.insert(name, ptr))
			std::cout << "Ok" << std::endl;
		else
			std::cout << "Duplicate name" << std::endl;
	}
	return 0;
}

int Find(Table & a)
{
	std::string name;
	Table::Const_Iterator it;
	const Agency* ptr = nullptr;
	std::cout << "Enter a agency name: --> ";
	std::getline(std::cin, name, '\n');
	if (!std::cin.good())
		throw std::exception("Error when a agency name was entered");
	it = a.find(name);
	if (it == a.end()) {
		std::cout << "The Agency with Name \"" << name << "\" is absent in container"
			<< std::endl;
		return -1;
	}
	std::cout << (*it) << std::endl;
	return 0;
}

int Remove(Table & a)
{
	std::string name;
	const Agency* ptr = nullptr;
	std::cout << "Enter a Agency name: --> ";
	std::getline(std::cin, name, '\n');
	if (!std::cin.good())
		throw std::exception("Error when a Agency name was entered");
	if (a.remove(name))
		std::cout << "Ok" << std::endl;
	else
		std::cout << "The Agency with Name \"" << name << "\" is absent in container"
		<< std::endl;
	return 0;
}

int Replace(Table & a)
{
	Table::Const_Iterator it;
	//Agency* ptr = nullptr;	// Агенство класса Agency (базовый класс)
	Print_edition* pe;			// Агенство класса Print_edition
	Radiostation* r;			// Агенство класса Radiostation
	TV_company* tv;				// Агенство класса TV_company
	std::string name;

	std::cout << "Enter a Agency name for replace: --> ";
	std::getline(std::cin, name, '\n');
	//std::cin >> name;
	if (!std::cin.good())
		throw std::exception("Error when a Agency name was entered");
	it = a.find(name);
	if (it == a.end())
	{
		std::cout << "The Agency with Name \"" << name << "\" is absent in container"
			<< std::endl;
	}
	else
	{
		if ((*it).second->get_type() == "Print_edition")
		{
			pe = static_cast<Print_edition*>((*it).second);
			pe->set_frequency_publication();
			pe->set_edition_circulation();
		}
		else if ((*it).second->get_type() == "Radiostation")
		{
			r = static_cast<Radiostation*>((*it).second);
			r->set_mas();
		}
		else if ((*it).second->get_type() == "TV_company")
		{
			tv = static_cast<TV_company*>((*it).second);
		};
	};
	return 0;
}

/*int Replace(Table & a)
{
	Table::Const_Iterator it;
	Agency* ptr = nullptr;		// Агенство класса Agency (базовый класс)
	const Agency* oldptr = nullptr;	// Агенство класса Agency (базовый класс)
	Print_edition pe;			// Агенство класса Print_edition
	Radiostation r;				// Агенство класса Radiostation
	TV_company tv;				// Агенство класса TV_company
	std::string name;
	std::cout << "Enter a Agency name for replace: --> ";
	std::cin >> name;
	if (!std::cin.good())
		throw std::exception("Error when a Agency name was entered");
	it = a.find(name);
	if (it == a.end())
	{
		std::cout << "The Agency with Name \"" << name << "\" is absent in container"
			<< std::endl;
	}
	else
	{
		oldptr = (*it).second;
		if (oldptr->get_type() == "Print_edition")
		{
			std::cout << "Enter information: profile license_number location_information periodicity circulation: --> ";
			ptr = &pe;
		}
		else if (oldptr->get_type() == "Radiostation")
		{
			std::cout << "Enter information: profile license_number location_information frequency range: --> ";
			ptr = &r;
		}
		else if (oldptr->get_type() == "TV_company")
		{
			std::cout << "Enter information: profile license_number location_information channel: --> ";
			ptr = &tv;
		};
		std::cin >> (*ptr);
		if (!std::cin.good())
			throw std::exception("Error when shape values were entered");
		std::cin.ignore(80, '\n');
		if (a.replace(name, ptr))
			std::cout << "Ok" << std::endl;
		else
			std::cout << "The Agency with Name \"" << name << "\" is absent in container"
			<< std::endl;
	};
	return 0;
}*/

int ShowAll(Table & a)
{
	Table::Const_Iterator it;
	for (it = a.begin(); it != a.end(); ++it)
		std::cout << (*it) << std::endl;
	return 0;
}

int Iter(Table & a)
{
	std::cout << "Calculate the length location for all agency in container" << std::endl;
	Table::Const_Iterator it;
	std::pair<std::string, Agency*> p;
	const Agency* ptr = nullptr;
	for (it = a.begin(); it != a.end(); ++it) {
		p = *it;
		ptr = p.second;
		std::cout << ptr->get_type() << " \"" << p.first
			<< "\": Its length location is equal to "
			<< ptr->length_location() << std::endl;
	}
	return 0;
}

int IterByAgType(Table & a)
{
	std::string ag_type, name;
	std::cout << "Calculate the length location for all agency in container" << std::endl;
	Table::Const_Iterator it;
	std::pair<std::string, Agency*> p;
	const Agency* ptr = nullptr;
	int ans;
	while (ans = Answer(Ag, NumAg)) {
		switch (ans) {
		case 1: // Print_Edition
			ag_type = "Print_edition";
			break;
		case 2: // Radiostation
			ag_type = "Radiostation";
			break;
		case 3:
			ag_type = "TV_company";
			break;
		};
		for (it = a.begin(); it != a.end(); ++it) {
			p = *it;
			ptr = p.second;
			if (ptr->get_type() == ag_type)
			{
				std::cout << ptr->get_type() << " \"" << p.first
					<< "\": Its length location is equal to "
					<< ptr->length_location() << std::endl;
			};
		};
	};
	return 0;
}

int ConstObj(Table & par)
{
	const Table a(par);
	std::string name;
	Table::Const_Iterator res;
	std::cout << "Enter a Agency name: --> ";
	std::getline(std::cin, name, '\n');
	//std::cin >> name;
	if (!std::cin.good())
		throw std::exception("Error when a Agency name was entered");
	res = a.find(name);
	if (res != a.end()) {
		std::cout << "The Agency with Name \"" << res->first << "\" is a "
			<< res->second->get_type()
			<< std::endl;
		std::cout << *(res->second) << std::endl;
		std::cout << "   Its Summa of all numbers in license is equal to " << res->second->summa() << std::endl;
		std::cout << "   Its length location is equal to " << res->second->length_location() << std::endl;
	}
	else
		std::cout << "The Agency with Name \"" << name << "\" is absent in container"
		<< std::endl;
	return 0;
}
