#pragma warning(disable:4996)
#include "..\Library\News_Agencies.h"
#include "..\Library\Table.h"
#include "c:\Distrib\gtest-1_7_0-rc1\gtest-1.7.0\include\gtest\gtest.h"
#include "conio.h"
using namespace News_Agencies;
using namespace Tab_Agencies;
using namespace std;

// Проверяет число
TEST(TestList, Printedition)
{
	Print_edition* pe = new Print_edition();
	pe->set_Print_edition_periodicity(1);
	pe->set_Print_edition_total_circulation(120000);
	pe->set_inform("Sport", 12345, "Moscow, danilovskaya nab 1");
	ASSERT_EQ(pe->summa(), 15);
	ASSERT_EQ(pe->length_location(), 26);
}

TEST(TestList, Radiostations)
{
	Radiostation* r = new Radiostation();
	r->set_inform("Music", 12000, "Moscow, sumskoy proezd 12");
	ASSERT_EQ(r->summa(), 3);
	ASSERT_EQ(r->length_location(), 25);
}

TEST(TestList, TVCompany)
{
	TV_company* tv = new TV_company();
	tv->set_inform("Novosti", 12345678, "Moscow, kashirskoe shosse 31");
	ASSERT_EQ(tv->summa(), 36);
	ASSERT_EQ(tv->length_location(), 28);
}

TEST(TestList, GetType)
{
	Print_edition* pe = new Print_edition();
	Radiostation* r = new Radiostation();
	TV_company* tv = new TV_company();
	Agency* ptr = nullptr;
	pe->set_inform("Sport", 12345, "Moscow, danilovskaya nab 1");
	r->set_inform("Music", 12000, "Moscow, sumskoy proezd 12");
	tv->set_inform("Novosti", 12345678, "Moscow, kashirskoe shosse 31");
	ptr = pe;
	ASSERT_EQ(ptr->get_type(), "Print_edition");
	ptr = r;
	ASSERT_EQ(ptr->get_type(), "Radiostation");
	ptr = tv;
	ASSERT_EQ(ptr->get_type(), "TV_company");
}

TEST(TestList, Clone)
{
	Print_edition* pe = new Print_edition();
	Radiostation* r = new Radiostation();
	TV_company* tv = new TV_company();
	Agency* ptr = nullptr;
	pe->set_inform("Sport", 12345, "Moscow, danilovskaya nab 1");
	r->set_inform("Music", 12000, "Moscow, sumskoy proezd 12");
	tv->set_inform("Novosti", 12345678, "Moscow, kashirskoe shosse 31");
	ptr = pe->clone();
	ASSERT_EQ(ptr->get_type(), "Print_edition");
	ptr = r->clone();
	ASSERT_EQ(ptr->get_type(), "Radiostation");
	ptr = tv->clone();
	ASSERT_EQ(ptr->get_type(), "TV_company");
}

TEST(TestList, Find)
{
	Table tab;
	Print_edition* pe = new Print_edition();
	Radiostation* r = new Radiostation();
	TV_company* tv = new TV_company();
	Agency* ptr = nullptr;
	pe->set_inform("Sport", 12345, "Moscow, danilovskaya nab 1");
	r->set_inform("Music", 12000, "Moscow, sumskoy proezd 12");
	tv->set_inform("Novosti", 12345678, "Moscow, kashirskoe shosse 31");
	ptr = pe->clone();
	tab.insert("Odin", ptr);
	ptr = r->clone();
	tab.insert("Dva", ptr);
	ptr = tv->clone();
	tab.insert("Tri", ptr);
	if (tab.find("Dva") != tab.end())
	{
		ASSERT_EQ((*tab.find("Dva")).second->get_type(), "Radiostation");
	};

}

TEST(TestList, NotFind)
{
	Table tab;
	Print_edition* pe = new Print_edition();
	Radiostation* r = new Radiostation();
	TV_company* tv = new TV_company();
	Agency* ptr = nullptr;
	pe->set_inform("Sport", 12345, "Moscow, danilovskaya nab 1");
	r->set_inform("Music", 12000, "Moscow, sumskoy proezd 12");
	tv->set_inform("Novosti", 12345678, "Moscow, kashirskoe shosse 31");
	ptr = pe->clone();
	tab.insert("Odin", ptr);
	ptr = r->clone();
	tab.insert("Dva", ptr);
	ptr = tv->clone();
	tab.insert("Tri", ptr);
	tab.remove("Odin");
	ASSERT_EQ(tab.find("Odin"), tab.end());
}


int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

