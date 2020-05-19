#ifndef Przystanki_H
#define Przystanki_H

#include <iostream>
#include <vector>
#include <string>
#include "Line.h"
#include <map>



using namespace std;


class Przystanek
{
private:
	string m_bus_stop_name;
	bool m_on_demand;
	bool m_frist_zone;
	vector<string> m_line_list;

public:

	//Konstruktor domyœlny

	Przystanek(string bus_stop_name = " ", bool on_deman = 0, bool frist_zone = 0) : m_bus_stop_name{ bus_stop_name }, m_on_demand{ on_deman },  m_frist_zone{frist_zone}
	{}

	//gettery i settery poszczegolnych zmienych

	string get_bus_stop_name()
	{
		return m_bus_stop_name;
	}

	void set_bus_stop_name(const string& bus_stop_name)
	{
		m_bus_stop_name = bus_stop_name;
	}

	bool get_on_demand()
	{
		return m_on_demand;
	}

	void set_on_demand(bool on_demand)
	{
		m_on_demand = on_demand;
	}

	bool get_frist_zone()
	{
		return m_frist_zone;
	}

	void set_frist_zone(bool frist_zone)
	{
		m_frist_zone = frist_zone;
	}

	vector<string> get_line_list()
	{
		return m_line_list;
	}

	void set_line_list(vector<string> bus_line_list)
	{
		m_line_list = bus_line_list;
	}


	void add_line_list(string line_number)
	{
		m_line_list.push_back(line_number);
	}

	//funkcja wyœwietlaj¹ca obiekty klasy Przystanek w konsolli

	void show_up( string end_bus_stop) {
		
		cout << m_bus_stop_name;
		if (m_on_demand)
		{
			cout << "   Na zadanie";
		}

		if (!m_frist_zone)
		{
			cout << "   Uwaga, przystanek w drugiej strefie!";
		}

		cout << endl << endl;

		for (unsigned int i = 0; i < m_line_list.size(); i++) {

			vector<string> wektor;
			wektor = lines[m_line_list[i]+end_bus_stop]->get_bus_stop_list();

			cout << i+1 << ". " << m_line_list[i] << " -> " << wektor[wektor.size()-1] << endl;
		}
	}
};

// œ³ownik przechowuj¹cy obiekty klasy przystanek

map<string, Przystanek*> bus_stops;

#endif // !Przystanki_h