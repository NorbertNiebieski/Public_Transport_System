#include "Przystanki.h"
#include "Line.h"
#include <iostream>
#include <vector>
#include <windows.h>
#include <fstream>
#include <string>
#include <map>
#include <stdio.h>
#include "Rozklad.h"

using namespace std;

// funkcja usuwająca stworzone obiekty poszczególnych klas

void closing() {

	for (pair<string, Rozklad*> element : roz) {

		delete element.second;
	}

	for (pair<string, Line*> element : lines) {

		delete element.second;
	}

	for (pair<string, Przystanek*> element : bus_stops) {

		delete element.second;
	}


}

int main()
{
	fstream file;


	//Tworzenie obiektów rozkladu z plikow

	int file_number = 1;
	string path = "schedules/.txt";
	path.insert(10, (to_string(file_number)));

	file.open(path, std::ios::in);
	string line_number, bus_stop_name, end_bus_stop;
	string name;
	string line;
	int counter = 0;
	vector<string> arrival_times;

	//wpisywanie odpowiednich danych do zmienych

	while (file.good() == true)
	{
		counter = 0;

		while (getline(file, line))
		{
			counter++;

			switch (counter)
			{
			case 1:
			{
				line_number = line;
				break;
			}
			case 2:
			{
				bus_stop_name = line;
				break;
			}
			case 3:
			{
				end_bus_stop = line;
				break;
			}
			default:
			{
				arrival_times.push_back(line);
				break;
			}
			}

		}
		//tworzenie obiektu
		name = line_number + bus_stop_name + end_bus_stop;;
		roz[name] = new Rozklad(line_number, bus_stop_name, end_bus_stop);
		//"zerowanie" zmiennych roboczych
		line_number = "none";
		bus_stop_name = "none";
		end_bus_stop = "none";
		roz[name]->set_arrival_times(arrival_times);
		arrival_times.erase(arrival_times.begin(), arrival_times.end());

		file.close();
		// przejscie do kolejnego pliku
		file_number++;
		path = "schedules/.txt";
		path.insert(10, (to_string(file_number)));
		file.open(path, std::ios::in);

	}
	file.close();

	//Tworzenie obiektów klasy line z plików
	file_number = 1;
	path = "lines/.txt";
	path.insert(6, (to_string(file_number)));

	file.open(path, std::ios::in);

	line_number = " ";
	end_bus_stop = " ";
	bool bus_or_tram = 0, night_line = 0, low_floor = 0, passes_trought_tariff_change = 0;
	vector<string> bus_stop_list;

	while (file.good() == true)
	{
		counter = 0;

		while (getline(file, line))
		{
			counter++;

			switch (counter)
			{
			case 1:
			{
				line_number = line;
				break;
			}
			case 2:
			{
				end_bus_stop = line;
				break;
			}
			case 3:
			{
				bus_or_tram = stoi(line);
				break;
			}
			case 4:
			{
				night_line = stoi(line);
				break;
			}
			case 5:
			{
				low_floor = stoi(line);
				break;
			}
			case 6:
			{
				passes_trought_tariff_change = stoi(line);
				break;
			}
			default:
			{
				bus_stop_list.push_back(line);
				break;
			}
			}

		}
		//Tworzenie obietku
		name = line_number + end_bus_stop;
		lines[name] = new Line(line_number, end_bus_stop, bus_or_tram, night_line, low_floor, passes_trought_tariff_change);
		lines[name]->set_bus_stop_list(bus_stop_list);
		//"zerowanie" zmienych roboczych
		line_number = "none";
		bus_or_tram = 0;
		night_line = 0;
		low_floor = 0;
		passes_trought_tariff_change = 0;
		bus_stop_list.erase(bus_stop_list.begin(), bus_stop_list.end());

		file.close();
		//przejście do kolejnego pliku
		file_number++;
		path = "lines/.txt";
		path.insert(6, (to_string(file_number)));
		file.open(path, std::ios::in);
	}

	file.close();

	//Tworzenie obiektów klasy przystanek z plikow tekstowych
	file_number = 1;
	path = "busstops/.txt";
	path.insert(9, (to_string(file_number)));

	file.open(path, std::ios::in);

	bus_stop_name = " ";
	bool on_demand = 0, frist_zone = 0;
	vector<string> line_list;

	while (file.good() == true)
	{
		counter = 0;

		while (getline(file, line))
		{
			counter++;

			switch (counter)
			{
			case 1:
			{
				bus_stop_name = line;
				break;
			}
			case 2:
			{
				on_demand = stoi(line);
				break;
			}
			case 3:
			{
				frist_zone = stoi(line);
				break;
			}
			default:
			{
				line_list.push_back(line);
				break;
			}
			}

		}
		// tworzenie nowego obiektu klasy Przystanek
		name = bus_stop_name;
		bus_stops[name] = new Przystanek(bus_stop_name, on_demand, frist_zone);
		bus_stops[name]->set_line_list(line_list);

		bus_stop_name = "none";
		on_demand = 0;
		frist_zone = 0;
		line_list.erase(line_list.begin(), line_list.end());

		file.close();
		//Przejscie do kolejnego pliku
		file_number++;
		path = "busstops/.txt";
		path.insert(9, (to_string(file_number)));
		file.open(path, std::ios::in);
	}

	file.close();

	// Menu
	char choice = '0';

	while (true)
	{

		choice = '0';

		system("cls");

		cout << "1. Wyszukaj trase" << endl;
		cout << "2. Pokaz przystanek" << endl;
		cout << "3. Pokaz linie" << endl;
		cout << "4. Wyjscie" << endl;

		cout << endl << "Twoj wybor (napisz numer opcji): ";
		cin >> choice;

		switch (choice)
		{
			//wyszukiwanie połączenia między przystankami
		case '1':
		{

			string bus_stop1, bus_stop2, arrival_time;

			system("cls");

			cout << "Podaj przystanek poczatkowy: ";
			cin >> bus_stop1;

			cout << "Podaj przystanek docelowy: ";
			cin >> bus_stop2;

			cout << "Prosze podac czas przyjazdu (GG:MM): ";
			cin >> arrival_time;

			cout << "Prosze podac kierunek: ";
			cin >> end_bus_stop;

			vector<string> line1, line2, common_line;

			line1 = bus_stops[bus_stop1]->get_line_list();
			line2 = bus_stops[bus_stop2]->get_line_list();
			//sprawdznie wspólnych lini między przystankami
			for (unsigned int i = 0; i < line1.size(); i++)
			{
				for (unsigned int j = 0; j < line2.size(); i++)
				{
					if (line1[i] == line2[j])
					{
						common_line.push_back(line1[i]);
						j = line2.size();
					}
				}
			}

			if (common_line.size() == 0)
			{
				cout << "Nie ma polaczenia miedzy tymi przystankami";
			}
			else
			{
				//wyznaczanie najlepszego połaczenia
				string best_line;
				string t = arrival_time;
				int best_time = 0;
				int hour = stoi(t.erase(2, t.size() - 1));
				t = arrival_time;
				int minutes = stoi(t.erase(0, t.size() - 2));
				int time = hour * 100 + minutes;



				for (unsigned int i = 0; i < common_line.size(); i++)
				{
					vector<string> arrival_tim;
					name = common_line[i] + bus_stop1 + end_bus_stop;
					arrival_tim = roz[name]->get_arrival_times();

					for (unsigned j = 0; j < arrival_tim.size(); j++)
					{
						t = arrival_tim[j];
						int time2 = stoi(t.erase(2, t.size() - 1)) * 100;
						t = arrival_tim[j];
						time2 += stoi(t.erase(0, t.size() - 2));

						if ((time2 < time) && (best_time < time2)) {
							best_time = time2;
							best_line = common_line[i];
						}
					}

				}
				cout << "Prosze byc na prszystanku " << bus_stop1 << " o godzinie " << best_time / 100 << ":" << (best_time - (best_time / 100) * 100) << " i pojechac autobusem nr " << best_line;
				char bin;
				bin = getchar();
				bin = getchar();
			}


			break;

		}
		// Podgląd Przystanku
		case '2':
		{
			system("cls");

			cout << "Prosze podac nazwe przystanku: ";
			cin >> bus_stop_name;
			cout << "Prosze podac kierunek jazdy: ";
			cin >> end_bus_stop;

			system("cls");

			bus_stops[bus_stop_name]->show_up(end_bus_stop);

			string choice2 = "100";

			cout << endl << "100. Powrot do menu glownego!";
			cout << endl << endl << "Ktory rozklad pokazac: ";
			cin >> choice2;

			int i_choice2 = stoi(choice2);

			switch (i_choice2)
			{
			case 100:
			{
				break;
			}

			default:

				line_number = bus_stops[bus_stop_name]->get_line_list()[i_choice2 - 1];

				name = line_number + bus_stop_name + end_bus_stop;
				roz[name]->show_up();
				cout << endl << "Nacisni dowolny klawisz aby kontynuwac";
				char bin;
				bin = getchar();
				bin = getchar();

				break;
			}

			break;
		}
		//Podglad liniautobusowej/tramwajowej
		case '3':
		{
			system("cls");

			cout << "Prosze podac numer lini: ";
			cin >> line_number;

			cout << "Prosze podac przystanke koncowy: ";
			cin >> end_bus_stop;

			system("cls");

			lines[line_number + end_bus_stop]->show_up();

			string choice2 = "100";

			cout << endl << "100. Powrot do menu glownego!";
			cout << endl << endl << "Rozklad ktorego przystanku pokazac: ";
			cin >> choice2;

			int i_choice2 = stoi(choice2);

			switch (i_choice2)
			{
			case 100:
			{
				break;
			}

			default:

				bus_stop_name = lines[line_number + end_bus_stop]->get_bus_stop_list()[i_choice2 - 1];
				name = line_number + bus_stop_name + end_bus_stop;
				roz[name]->show_up();
				cout << endl << "Nacisni dowolny klawisz aby kontynuwac";
				char bin;
				bin = getchar();
				bin = getchar();

				break;
			}

			break;
		}

		case '4':
		{
			closing();
			exit(0);
			break;
		}

		default:
		{
			system("cls");
			break;
		}
		}


	}

	closing();

	return 0;
}


