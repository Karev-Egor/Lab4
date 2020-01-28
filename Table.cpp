#include <iostream>
#include "..\Library\Table.h"


namespace Tab_Agencies
{
    std::ostream & operator <<(std::ostream &os,
							   const std::pair<const std::string, News_Agencies::Agency *> &p) {

         return os << '"' << p.first << '"' << " - " << (*p.second);
    }
    Table::Table(const Table &a)
    {
	    std::map<const std::string, News_Agencies::Agency *>::const_iterator p;
		for (p = a.arr.begin(); p != a.arr.end(); ++p)
			arr.insert(std::make_pair(p->first, p->second->clone()));
	}

    Table::~Table()
    {
		std::map<const std::string, News_Agencies::Agency *>::iterator p;
		for (p = arr.begin(); p != arr.end(); ++p)
		{
			delete p->second;
			p->second = nullptr;
		}
    }

    Table& Table::operator = (const Table &a)
    {
		std::map<const std::string, News_Agencies::Agency *>::iterator p;
		if (this != &a)
		{
			// Рсвобождение памяти, занятой объектом слева от присванивания
			for (p = arr.begin(); p != arr.end(); ++p)
				delete p->second;
			arr.clear();
			// Копирование фигур из контейнера справа от присванивания (a.arr)
		    // в контейнер слева от присваивания (arr)
			std::map<const std::string, News_Agencies::Agency *>::const_iterator pp;
			for (pp = a.arr.begin(); pp != a.arr.end(); ++pp)
				arr.insert(std::make_pair(pp->first, pp->second->clone()));
		}
		return *this;
    }

    bool Table::insert(const std::string &s, const News_Agencies::Agency *f)
    {
		bool res = false;
		std::map<const std::string, News_Agencies::Agency *>::iterator p = arr.find(s);
		if (p == arr.end())	// Поиск неуспешен
		{
			std::pair<std::map<const std::string, News_Agencies::Agency *>::iterator, bool> pp =
			arr.insert(std::make_pair(s, f->clone()));
			if (!pp.second)
				throw std::exception("can't insert new item into map");
			res = true;
		}
		return res;
    }

    bool Table::remove(const std::string &s)
    {
		bool res = false;
		std::map<const std::string, News_Agencies::Agency *>::iterator p = arr.find(s); //arr.erase(s);
		if (p != arr.end())	// Поиск успешен
		{
			delete p->second;
			p->second = nullptr;
			arr.erase(p); // Удаление элемента из контейнера (по значению итератора)
			res = true;
		}
		return res;
    }

    bool Table::replace(const std::string &s, const News_Agencies::Agency *f)
    {
		bool res = false;
		std::map<const std::string, News_Agencies::Agency *>::iterator p = arr.find(s);
    
		if (p != arr.end())	// Поиск успешен
		{
			delete p->second;
			p->second = f->clone();
			res = true;
		}
        return res;
    }

    Table::Const_Iterator Table::find(const std::string &s) const
    {
		std::map<const std::string, News_Agencies::Agency *>::const_iterator p = arr.find(s);
        return ConstTableIt(p);
    }

    Table::Const_Iterator Table::begin() const
    {
        return ConstTableIt(arr.begin());
    }

    Table::Const_Iterator Table::end() const
    {
        return ConstTableIt(arr.end());
    }

	// Сеиоды класса AssocIt
    int Table::Const_Iterator::operator !=(const ConstTableIt &it) const
    {
        return cur != it.cur;
    }

    int ConstTableIt::operator ==(const ConstTableIt &it) const
    {
        return cur == it.cur;
    }

    const std::pair<const std::string, News_Agencies::Agency *> & ConstTableIt::operator *()
    {
        return *cur;
    }

    const std::pair<const std::string, News_Agencies::Agency *> * ConstTableIt::operator ->()
    {
        return &*cur;
    }

    ConstTableIt & ConstTableIt::operator ++()
    {
        ++cur;
        return *this;
    }

    ConstTableIt ConstTableIt::operator ++(int)
    {
		ConstTableIt res(*this);
		++cur;
		return res;
	 }
};
