#pragma once
#ifndef _TABLE_H_
#define _TABLE_H_
#include <iostream>
#include <map>
#include <string>
#include "..\Library\News_Agencies.h"

namespace Tab_Agencies
{
	std::ostream& operator <<(std::ostream&, const std::pair<const std::string, News_Agencies::Agency*>&);

	class Table
	{
	private:
		
		std::map<const std::string, News_Agencies::Agency*> arr;
	public:
		Table(){}
		Table(const Table&);
		~Table();
		Table& operator = (const Table&);
		friend class ConstTableIt;
		typedef ConstTableIt Const_Iterator;
		Const_Iterator find(const std::string&) const;
		bool insert(const std::string &, const News_Agencies::Agency *);		//Добавление элемента
		bool replace(const std::string &, const News_Agencies::Agency *);		//Изменение элемента
		bool remove(const std::string &);										//Удаление элемента
		Const_Iterator begin() const;
		Const_Iterator end() const;
	};

	class ConstTableIt
	{
    private:
        std::map<const std::string, News_Agencies::Agency *>::const_iterator cur;
    public:
        ConstTableIt(){}
        ConstTableIt(std::map<const std::string, News_Agencies::Agency *>::iterator it) :cur(it){}
        ConstTableIt(std::map<const std::string, News_Agencies::Agency *>::const_iterator it) :cur(it){}
        int operator !=(const ConstTableIt &) const;
        int operator ==(const ConstTableIt &) const;
        const std::pair<const std::string, News_Agencies::Agency *> & operator *();
        const std::pair<const std::string, News_Agencies::Agency *> * operator ->();
        ConstTableIt & operator ++();
        ConstTableIt operator ++(int);
	};
};
#endif