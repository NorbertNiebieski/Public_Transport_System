
#ifndef Line_h
#define Line_h

#include <iostream>
#include <vector>
#include <string>
#include "Rozklad.h"
#include <map>



class Line {
private:

	string m_line_number;
	string m_end_bus_stop;
	bool m_bus_or_tram;									// true = bus / false = tram
	bool m_night_line;									// true = night line
	bool m_low_floor;									// true = yes
	bool m_passes_trought_tariff_change;				// true = yes

	vector<string>  m_bus_stop_list;

public:

	//kosntruktor domyœlny

	Line(string line_number = "none", string end_bus_stop = "none", bool bus_or_tram = false, bool night_line = false, bool low_floor = false, bool passes_trought_tariff_change = false) : m_line_number{ line_number }, m_end_bus_stop{end_bus_stop}, m_bus_or_tram{ bus_or_tram }, m_night_line{ night_line }, m_low_floor{ low_floor }, m_passes_trought_tariff_change{ passes_trought_tariff_change }
	{}
	
	//gettery oraz settery poszczegolnych zmienych

	string get_line_number()
	{
		return m_line_number;
	}

	void set_line_number(string line_number)
	{
		m_line_number = line_number;
	}

	string get_end_bus_stop()
	{
		return m_end_bus_stop;
	}

	void set_end_bus_stop(string end_bus_stop)
	{
		m_end_bus_stop = end_bus_stop;
	}

	bool get_bus_or_tram()
	{
		return m_bus_or_tram;
	}

	void set_bus_or_tram(bool bus_or_tram)
	{
		m_bus_or_tram = bus_or_tram;
	}

	bool get_night_line()
	{
		return m_night_line;
	}

	void set_night_line(bool night_line)
	{
		m_night_line = night_line;
	}

	bool get_low_floor()
	{
		return m_low_floor;
	}

	void set_low_floor(bool low_floor)
	{
		m_low_floor = low_floor;
	}

	bool get_passes_trought_tariff_change()
	{
		return m_passes_trought_tariff_change;
	}

	void set_passes_trought_tariff_change(bool passes_trought_tariff_change)
	{
		m_passes_trought_tariff_change = passes_trought_tariff_change;
	}

	vector<string> get_bus_stop_list()
	{
		return m_bus_stop_list;
	}

	void set_bus_stop_list(vector<string> bus_stop_list)
	{
		m_bus_stop_list = bus_stop_list;
	}


	void add_bus_stop(string bus_stop_name)
	{
		m_bus_stop_list.push_back(bus_stop_name);
	}

	// funkcja s³u¿¹ca do wyœwietlania obiektów klasy line w konsoli

	void show_up() 
	{
		if (m_night_line)		cout << "Nocna linia ";
		else					cout << "linia ";

		if (m_bus_or_tram)	cout << "autobusowa";
		else				cout << "tramwajowa";

		cout << " o numerze " << m_line_number << ". ";
		
		if (m_low_floor)		cout << "Posiada tabor niskopodlogowy. ";

		if (m_passes_trought_tariff_change) cout << "Podczas przejazdu nastepuje zmiana strefy. ";
				
		cout << endl << endl;
		cout << "Lista przystankow:" << endl << endl;

		for (unsigned int i = 0; i < m_bus_stop_list.size(); i++) {
			cout << i+1 << ". " << m_bus_stop_list[i] << endl;
		}

	}


};

//s³owniek do przechowywania obietków klasy line

map<string, Line*> lines;



#endif // !Line_h
