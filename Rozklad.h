#ifndef Rozklad_h
#define Rozklad_h

#include <iostream>
#include <vector>
#include <map>


using namespace std;

class Rozklad {
private:

	string m_line_number;
	string m_bus_stop_name;
	string m_end_bus_stop;
	vector<string> m_arrival_times;

public:

	//konstruktor

	Rozklad ( string line_number = " ", string bus_stop_name = " ", string end_bus_stop = " ") : m_line_number{line_number}, m_bus_stop_name{bus_stop_name}, m_end_bus_stop{end_bus_stop}
	{}

	//gettery oraz settery zmienych
	
	string get_line_number() 
	{
		return m_line_number;
	}

	void set_line_number(const string& line_number) 
	{ 
		m_line_number = line_number; 
	}

	string get_bus_stop_name() 
	{
		return m_bus_stop_name;
	}

	void set_bus_stop_name(const string& bus_stop_name)
	{
		m_bus_stop_name = bus_stop_name;
	}

	string get_end_bus_stop() 
	{
		return m_end_bus_stop;
	}

	void set_end_bus_stop(const string& end_bus_stop)
	{
		m_end_bus_stop = end_bus_stop;
	}

	vector<string> get_arrival_times() 
	{
		return m_arrival_times;
	}

	void set_arrival_times( vector<string> arrival_times)
	{
		m_arrival_times = arrival_times;
	}


	void add_arrival_time(string arrival_time) 
	{
		m_arrival_times.push_back(arrival_time);
	}

	// metoda wyœwietlaj¹ca rozklad w konsoli

	void show_up() {

		cout << endl << m_bus_stop_name << endl << endl;
		cout << m_line_number << "->" << m_end_bus_stop << endl << endl;

		string hour, vector_string;
		vector_string = m_arrival_times[0];
		vector_string.erase(vector_string.begin() + 2, vector_string.end());
		hour = vector_string;


		for (unsigned int i = 0; i < m_arrival_times.size(); i++)
		{
			vector_string = m_arrival_times[i];
			vector_string.erase(vector_string.begin() + 2, vector_string.end());


			if (hour == vector_string)
			{
				cout << m_arrival_times[i] << " ";
			}
			else
			{
				hour = vector_string;
				cout << endl << m_arrival_times[i] << " ";
			}
		}

	}

};

// s³ownik do przechowywania obiektów klasy Rozklad
map<string, Rozklad*> roz;

#endif // !Rozklad_h