// Railway reservation system.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <direct.h>
#include <stdlib.h>
#include <stdio.h>
#include <iomanip>
#include <string>
#include <conio.h>
#include <vector>
#include <cctype>


void choose_mode();
void display_menu();
void quit();
void admin_mode();
void user_mode();
bool grant_access();
void update_station();
void view_trains(std::string);
void update_station_1();
void update_station_2();
void user_op();
//void train_op();
void add_trains_1(std::string);
void add_trains_2(std::string);
void create_user();
void list_user();
void reserve();
void display_reserves();
void display_creserves();
int	 get_serialnum();
std::string capitalise(std::string);

char quitter{ '1'}; //Universal Variable Used to Quit the Application...

using namespace std;
/*
1 - MAKE A FOLDER CALLED FILES WHERE ALL THE .TXT FILES WILL BE KEPT
2 - UPDATE_STATIONS
		1 - STATION-1 (YABA STATION)
				WHAT ROUTE?
					YABA - UNILAG
						-ENTER TRAIN DETAILS
					YABA - IKORODU
						-ENTER TRAIN DETAILS
					YABA - CMS
						-ENTER TRAIN DETAILS
		2 - STATION-2 (COSTAIN STATION)
				WHAT ROUTE?
					COSTAIN - UNILAG
						-ENTER TRAIN DETAILS
					COSTAIN - IKORODU
						-ENTER TRAIN DETAILS
					COSTAIN - CMS
						ENTER TRAIN DETAILS
*/

int main()
{
	_mkdir("FILES"); //this line of code returns 0 if the folder is successfully created and -1 if otherwise...
	const char* path = "FILES/README.txt";
	std::ofstream out_file(path);
	out_file << "This is the Read me that shows the functionality of this operation---";
	out_file.close();

	std::cout <<std::setw(50)<< "RAILWAY RESERVATION SYSTEM" << std::endl;
	std::cout << std::setw(75) << std::setfill('=') << " " << std::endl;
	display_menu();

	return 0;
}

void display_menu() {
	if (quitter != '0') {
		int option{};
		std::string entry{};
		bool done{ false };

		std::cout << "1 - CHOOSE MODE\n2 - QUIT\n";
		do {
			std::cout << "OPTION: ";
			std::cin >> entry;
			std::istringstream validator{ entry };
			if (validator >> option && (option == 1 || option == 2)) {
				done = true;
			}
			else {
				std::cout << "PLEASE ENTER A VALID OPTION\n"<<std::endl;
				std::cin.ignore(std::numeric_limits<std::streamsize> ::max(), '\n');
			}
		} while (!done);
		switch (option)
		{
			case 1:
			{
				choose_mode();
				display_menu();
			}
			break;
			case 2:
			{
				quit();
			}
			break;

			default:
			{}
		}
	}
}

void choose_mode() {
	system("CLS");
	int option{};
	std::string entry;
	bool done{ false };

	do {
		std::cout << "WHAT MODE WOULD YOU LIKE TO ENTER?\n1 - ADMIN MODE\n2 - USER MODE\nOPTION: ";
		
		std::cin >> entry;
		std::istringstream validator{ entry };

		if (validator >> option && (option ==1 ||option == 2)) {
			done = true;
		}
		else {
			std::cout << "KINDLY ENTER A VALID OPTION\n";
			std::cin.ignore(std::numeric_limits<std::streamsize> ::max(), '\n');
		}
	} while (!done);

	if (option == 1) {
		admin_mode();
	}
	else {
		user_mode();
	}
	
}

bool grant_access() {
	system("CLS");
	int ch;
	std::string pass;
	bool done{ false };

	//Unable to get the Backspace to work properly so as at now, Backspace reads as a character---
		std::cout << "ENTER ADMIN PASSWORD\nPASSWORD: ";
		ch = _getch();

		while (ch != 13) {
			
			pass += ch;
			std::cout << '*';
			ch = _getch();
		}

		if (pass == "0000") {
			done = true;	
		}

		else {
			std::cout << "\n\nYOU ENTERED AN INCORRECT PASSWORD\n\n";
		}

		return done;
}
 
void admin_mode() {

retry:
	int option{};
	std::string entry;
	bool done{ false };

	bool access = grant_access();

	if (access == true) {
		//IT MEANS THE ADMIN NOW HAS ACCESS
		/*
		UPDATE THE DETAILS FOR THE STATIONS (1 & 2)
		USER SECTIONS
			CREATE A NEW USER
			VIEW ALL USERS
		VIEW RESERVATIONS (ALL RESERVATIONS ARE DONE IN THE USER MODE)
			VIEW ALL SUCCESSFUL RESERVATIONS
			VIEW CANCELLED RESERVATIONS (ALL RESERVATIONS CANCELLATIONS ARE DONE IN THE USER MODE)
		*/
		system("CLS");
		std::cout << "WELCOME DEAR ADMINISTRATOR - THE TRANSPORT SYSTEM IS IN YOUR HANDS\n\n";
		std::cout << "1 - TRAIN SECTION\n2 - USER SECTION\n3 - VIEW RESERVATIONS\n4 - GO TO HOME\n";
		
		std::string entry_admin;
		int option_admin;
		bool done_admin{ false };

		do {
			std::cout << "OPTION: ";
			std::cin >> entry_admin;
			std::istringstream validator_admin{ entry_admin };

			if (validator_admin >> option_admin&&(option_admin >0 && option_admin<5)) {
				done_admin = true;
			}
			else {
				std::cout << "\n\nKINDLY ENTER A VALID OPTION\n";
				std::cin.ignore(std::numeric_limits<std::streamsize> ::max(), '\n');
			}
		} while (!done_admin);
		
		switch (option_admin)
		{

			case 1:
			{
				update_station();
			}
				break;
			case 2:
			{
				user_op();
			}
			break;

			case 3:
			{
				reserve();
			}
			break;
			case 4:
			{
				display_menu();
			}
			break;
			default:{}
				break;
		}
	}
	else {

		std::cout << "1 - RETRY PASSWORD\n2 - GO TO HOME\n";
		do {
			std::cout << "OPTION:";
			std::cin >> entry;

			std::istringstream validator{ entry };
			if (validator >> option && (option == 1 || option == 2)) {
				done = true;
			}

			else {
				std::cout << "KINDLY ENTER A VALID OPTION\n\n";
				std::cin.ignore(std::numeric_limits<std::streamsize> ::max(), '\n');
			}
		} while (!done);
		if (option == 1) {
			goto retry;
		}

		else {

			display_menu();
		}
	}
}

void user_op() {
	system("CLS");
	std::cout << "\t\t\tUSER SECTION\n";
	std::cout << "1 - CREATE USER\n2 - LIST USERS\n";

	std::string entry;
	int option;
	bool done{ false };

	do {
		std::cout << "OPTION: ";
		std::cin >> entry;
		std::istringstream validator{ entry };

		if (validator >> option && (option ==1 ||option == 2)) {
			done = true;
		}
		else {
			std::cout << "KINDLY ENTER A VALID OPTION\n\n";
			std::cin.ignore(std::numeric_limits<std::streamsize> ::max(), '\n');
		}
	} while (!done);

	if (option == 1) {
		create_user();
	}
	else {
		list_user();
	}
};

//void train_op() {
//	system("CLS");
//	std::cout << "\t\tTRAIN SECTION\n";
//	std::cout << "1 - VIEW TRAIN DETAILS\n2 - UPDATE TRAIN DETAILS\n";
//	
//	bool done{ false };
//	std::string entry;
//	int option;
//
//	do {
//		std::cout << "OPTION: ";
//		std::cin >> entry;
//		std::istringstream validator{ entry };
//		if (validator >> option && (option ==1 || option == 2)) {
//			done = true;
//		}
//		else {
//			std::cout << "KINDLY ENTER A VALID INPUT\n\n";
//			std::cin.ignore(std::numeric_limits<std::streamsize> ::max(), '\n');
//		}
//	} while (!done);
//
//	if (option == 1) {
//		system("CLS");
//		view_train();
//	}
//	else {
//		system("CLS");
//		update_station();
//	}
//}

void update_station() {
	/*
	How you go about it...
	--- There is a .txt file named after the particular station
	--- Then the admin chooses the station the he/she wishes to update
	--- Then in the particular station, the admin chooses the route to be updated
	--- If the route has been updated prior, a message asks the admin if he/she wishes to edit the information for that route
	--- 
2 - UPDATE_STATIONS
		1 - STATION-1 (YABA STATION)
				WHAT ROUTE?
					YABA - UNILAG
						-ENTER TRAIN DETAILS
					YABA - IKORODU
						-ENTER TRAIN DETAILS
					YABA - CMS
						-ENTER TRAIN DETAILS
		2 - STATION-2 (COSTAIN STATION)
				WHAT ROUTE?
					COSTAIN - UNILAG
						-ENTER TRAIN DETAILS
					COSTAIN - IKORODU
						-ENTER TRAIN DETAILS
					COSTAIN - CMS
						ENTER TRAIN DETAILS
*/
	system("CLS");
	std::cout << "\t\t\tWELCOME TO THE STATIONS SECTIONS. GUIDE THE WORLD TO MOVEMENT\n";
	std::cout << "CHOOSE STATION\n1 - STATION 1 (YABA)\n2 - STATION 2 (COSTAIN)\n";

	std::string entry;
	bool done{ false };
	int opt;

	do {
		std::cout << "OPTION: ";
		std::cin >> entry;

		std::istringstream validator{ entry };
		if (validator >> opt && (opt == 1 || opt == 2)) {
			done = true;
		}
		else {
			std::cout << "KINDLY ENTER A VALID INPUT\n\n";
			std::cin.ignore(std::numeric_limits<std::streamsize> ::max(), '\n');
		}
	} while (!done);

	if (opt == 1) {
		system("cls");
		update_station_1();
	}
	else {
		system("cls");
		update_station_2();
	}

}

void add_trains_1(std::string route) {
	std::string rte;
	rte = route;
	
	if (rte == "yaba-unilag") {
		std::cout << "\t\t\tYABA - UNILAG (ET-RETURN ROUTE)\n\n";
		bool done{ false };
		std::string entry;
		int count;

		std::cout << "HOW MANY TRAINS WOULD YOU LIKE TO ADD\n";
		do {
			std::cout << "OPTION: ";
			std::cin >> entry;
			std::istringstream validator{ entry };

			if (validator >> count && count > 0) {
				done = true;
			}
			else {
				std::cout << "KINDLT ENTER A VALID INPUT\n\n";
				std::cin.ignore(std::numeric_limits<std::streamsize> ::max(), '\n');
			}
		} while (!done);

		for (int i{ 0 }; i < count; i++) {
			const char* path = "FILES/STATION_1/yaba-unilag.txt";
			std::ofstream out_file(path, std::ios::app);

			std::string t_name, b_point, d_point, train_no;
			int no_f_seat, no_c_seat;
			double f_fare, c_fare;


			/*	bool done_r{ false };
				std::string entry_r;
				int opt_r;*/

		
					/*
					THE DETAILS TO BE ENTERED BY THE ADMIN:
					<--- train number # train name # boarding point # destination point #  no of first class seats
					# first class seat fare # no of commercial seat #commercial class seat fare # DEPARTURE TIME--->
					*/

					// There is an assumption that all of the trains do the return trip...
					//The reuturn_line string is supposed to take care of that...
			std::string return_line;
			std::cin.ignore(1, '\n');

			std::cout << "TRAIN NUMBER (e.g YAB001): ";
			std::getline (std::cin, train_no);
			out_file << train_no << "#";
			return_line += train_no;
			return_line += "#";

			std::cout << "TRAIN NAME: ";
			std::getline(std::cin, t_name);
			out_file << t_name << "#";
			return_line += train_no;
			return_line += "#";

			std::cout << "BOARDING POINT: ";
			std::getline(std::cin, b_point);
			out_file << b_point << "#";

			std::cout << "DESTINATION: ";
			std::getline(std::cin, d_point);
			out_file << d_point << "#";

			//The Boarding point is passed as the destination point and the destination as the boarding point in the reverse mode...
			return_line += d_point;
			return_line += "#";
			return_line += b_point;
			return_line += "#";

			bool done_f{ false };
			std::string entry_f;


			std::cout << "NUMBER OF FIRST CLASS SEATS: ";
			do {
				std::cin >> entry_f;
				std::istringstream validator_f{ entry_f };
				if (validator_f >> no_f_seat && no_f_seat > 0) {
					done_f = true;
				}
				else {
					std::cout << "KINDLY ENTER A NUMBER\n\n";
					std::cin.ignore(std::numeric_limits<std::streamsize> ::max(), '\n');
				}
			} while (!done_f);

			out_file << no_f_seat << "#";
			std::string no_f_seats = std::to_string(no_f_seat);
			return_line += no_f_seats;
			return_line += "#";



			bool done_ff{ false };
			std::string entry_ff;

			std::cout << "PRICE PER SEAT FOR FIRST CLASS: N";
			do {
				std::cin >> entry_ff;
				std::istringstream validator_ff{ entry_ff };

				if (validator_ff >> f_fare && f_fare > 0) {
					done_ff = true;
				}
				else {
					std::cout << "KINDLY ENTER A VALID INPUT\n\n";
					std::cin.ignore(std::numeric_limits<std::streamsize> ::max(), '\n');
				}
			} while (!done_ff);
			out_file << f_fare << "#";
			std::string f_fares = std::to_string(f_fare);
			return_line += f_fares;
			return_line += "#";


			bool done_c{ false };
			std::string entry_c;

			std::cout << "NUMBER OF COMMERCIAL CLASS SEATS: ";
			do {
				std::cin >> entry_c;
				std::istringstream validator_c{ entry_c };
				if (validator_c >> no_c_seat && no_c_seat > 0) {
					done_c = true;
				}
				else {
					std::cout << "KINDLY ENTER A NUMBER\n\n";
					std::cin.ignore(std::numeric_limits<std::streamsize> ::max(), '\n');
				}
			} while (!done_c);

			out_file << no_c_seat << "#";
			std::string no_c_seats = std::to_string(no_c_seat);
			return_line += no_c_seats;
			return_line += "#";


			bool done_cf{ false };
			std::string entry_cf;

			std::cout << "PRICE PER SEAT FOR FIRST CLASS: N";
			do {
				std::cin >> entry_cf;
				std::istringstream validator_cf{ entry_cf };

				if (validator_cf >> c_fare && c_fare > 0) {
					done_cf = true;
				}
				else {
					std::cout << "KINDLY ENTER A VALID INPUT\n\n";
					std::cin.ignore(std::numeric_limits<std::streamsize> ::max(), '\n');
				}
			} while (!done_cf);
			out_file << c_fare << std::endl;
			std::string c_fares = std::to_string(c_fare);
			return_line += c_fares;
			out_file.close();

			std::cout << std::endl;
			std::cout << t_name << " SUCCESFULLY ADDED!\n\n";

			//In order to pass in the info of the train for the return trip...
			const char* path_r = "FILES/STATION_1/unilag-yaba.txt";
			out_file.open(path_r, std::ios::app);

			if (!out_file) {
				std::cerr << "ERROR OPENING FILE\n";
			}
			else {
				out_file << return_line << std::endl;
			}
			out_file.close();
		}
	}
	
	else if (rte == "yaba-ikorodu") {
	std::cout << "\t\t\tYABA - IKORODU (ET-RETURN ROUTE)\n\n";
	bool done{ false };
	std::string entry;
	int count;

	std::cout << "HOW MANY TRAINS WOULD YOU LIKE TO ADD\n";
	do {
		std::cout << "OPTION: ";
		std::cin >> entry;
		std::istringstream validator{ entry };

		if (validator >> count && count > 0) {
			done = true;
		}
		else {
			std::cout << "KINDLT ENTER A VALID INPUT\n\n";
			std::cin.ignore(std::numeric_limits<std::streamsize> ::max(), '\n');
		}
	} while (!done);

	for (int i{ 0 }; i < count; i++) {
		const char* path = "FILES/STATION_1/yaba-ikorodu.txt";
		std::ofstream out_file(path, std::ios::app);

		std::string t_name, b_point, d_point, train_no;
		int no_f_seat, no_c_seat;
		double f_fare, c_fare;

			/*
			THE DETAILS TO BE ENTERED BY THE ADMIN:
			<--- train number # train name # boarding point # destination point #  no of first class seats
			# first class seat fare # no of commercial seat #commercial class seat fare # DEPARTURE TIME--->
			*/

			// There is an assumption that all of the trains do the return trip...
			//The reuturn_line string is supposed to take care of that...
		std::string return_line;
		std::cin.ignore(1, '\n');

		std::cout << "TRAIN NUMBER (e.g YIK001): ";
		std::getline(std::cin, train_no);
		out_file << train_no << "#";
		return_line += train_no;
		return_line += "#";

		std::cout << "TRAIN NAME: ";
		std::getline(std::cin, t_name);
		out_file << t_name << "#";
		return_line += train_no;
		return_line += "#";

		std::cout << "BOARDING POINT: ";
		std::getline(std::cin, b_point);
		out_file << b_point << "#";

		std::cout << "DESTINATION: ";
		std::getline(std::cin, d_point);
		out_file << d_point << "#";

		//The Boarding point is passed as the destination point and the destination as the boarding point in the reverse mode...
		return_line += d_point;
		return_line += "#";
		return_line += b_point;
		return_line += "#";

		bool done_f{ false };
		std::string entry_f;


		std::cout << "NUMBER OF FIRST CLASS SEATS: ";
		do {
			std::cin >> entry_f;
			std::istringstream validator_f{ entry_f };
			if (validator_f >> no_f_seat && no_f_seat > 0) {
				done_f = true;
			}
			else {
				std::cout << "KINDLY ENTER A NUMBER\n\n";
				std::cin.ignore(std::numeric_limits<std::streamsize> ::max(), '\n');
			}
		} while (!done_f);

		out_file << no_f_seat << "#";
		std::string no_f_seats = std::to_string(no_f_seat);
		return_line += no_f_seats;
		return_line += "#";



		bool done_ff{ false };
		std::string entry_ff;

		std::cout << "PRICE PER SEAT FOR FIRST CLASS: N";
		do {
			std::cin >> entry_ff;
			std::istringstream validator_ff{ entry_ff };

			if (validator_ff >> f_fare && f_fare > 0) {
				done_ff = true;
			}
			else {
				std::cout << "KINDLY ENTER A VALID INPUT\n\n";
				std::cin.ignore(std::numeric_limits<std::streamsize> ::max(), '\n');
			}
		} while (!done_ff);
		out_file << f_fare << "#";
		std::string f_fares = std::to_string(f_fare);
		return_line += f_fares;
		return_line += "#";


		bool done_c{ false };
		std::string entry_c;

		std::cout << "NUMBER OF COMMERCIAL CLASS SEATS: ";
		do {
			std::cin >> entry_c;
			std::istringstream validator_c{ entry_c };
			if (validator_c >> no_c_seat && no_c_seat > 0) {
				done_c = true;
			}
			else {
				std::cout << "KINDLY ENTER A NUMBER\n\n";
				std::cin.ignore(std::numeric_limits<std::streamsize> ::max(), '\n');
			}
		} while (!done_c);

		out_file << no_c_seat << "#";
		std::string no_c_seats = std::to_string(no_c_seat);
		return_line += no_c_seats;
		return_line += "#";


		bool done_cf{ false };
		std::string entry_cf;

		std::cout << "PRICE PER SEAT FOR FIRST CLASS: N";
		do {
			std::cin >> entry_cf;
			std::istringstream validator_cf{ entry_cf };

			if (validator_cf >> c_fare && c_fare > 0) {
				done_cf = true;
			}
			else {
				std::cout << "KINDLY ENTER A VALID INPUT\n\n";
				std::cin.ignore(std::numeric_limits<std::streamsize> ::max(), '\n');
			}
		} while (!done_cf);
		out_file << c_fare << std::endl;
		std::string c_fares = std::to_string(c_fare);
		return_line += c_fares;
		out_file.close();

		std::cout << std::endl;
		std::cout << t_name << " SUCCESFULLY ADDED!\n\n";

		//In order to pass in the info of the train for the return trip...
		const char* path_r = "FILES/STATION_1/ikorodu-yaba.txt";
		out_file.open(path_r, std::ios::app);

		if (!out_file) {
			std::cerr << "ERROR OPENING FILE\n";
		}
		else {
			out_file << return_line << std::endl;
		}
		out_file.close();
	}
	}
}

void add_trains_2(std::string route) {

}

void update_station_1() {
	/*
	How you go about it...
	--- There is a .txt file named after the particular station
	--- Then the admin chooses the station the he/she wishes to update
	--- Then in the particular station, the admin chooses the route to be updated
	--- If the route has been updated prior, a message asks the admin if he/she wishes to edit the information for that route
	*/

	_mkdir("FILES/STATION_1");

	std::cout << "\t\t\tWELCOME TO STATION 1 (YABA STATION)\nCHOOSE A ROUTE TO UPDATE\n";
	std::cout << "1 - [YABA - UNILAG]\n2 - [YABA - IKORODU]\n";
	
	bool done{ false };
	std::string entry;
	int option;


	do {
		std::cout << "OPTION: ";
		std::cin >> entry;
		std::istringstream validator{ entry };

		if (validator >> option && (option > 0 && option < 5)) {
			done = true;
		}
		else {
			std::cout << "KINDLY ENTER A VALID INPUT\n\n";
			std::cin.ignore(std::numeric_limits<std::streamsize> ::max(), '\n');
		}

	} while (!done);

	switch (option)
	{
		case 1:
		{
			//folder called station which is inside the files
			//then each of the routes have a .txt file
			//thus you can add trains to each of the routes at will


			//If it does not exist, it is created for the first time...
			const char* path = "FILES/STATION_1/yaba-unilag.txt";
			std::ofstream out_file(path, std::ios::app);
			out_file.close();
			system("CLS");

			std::ifstream in_file;
			in_file.open(path);
			
			std::string line;
			std::vector <std::string> lines;

			while (std::getline(in_file, line)) {
				lines.push_back(line);
			}
			in_file.close(); //signifies that you are done reading from the file...

			if (lines.size() == 0) {
				std::cout << "THERE ARE CURRENTLY NO REGISTERED TRAINS\n1 - ADD TRAINS\n0 - RETURN TO HOME MENU\n";
				
				bool done_1{ false };
				std::string entry_1;
				int opt_1;

				do {
					std::cout << "OPTION: ";
					std::cin >> entry_1;
					std::istringstream validator_1{ entry_1 };

					if (validator_1 >> opt_1 && (opt_1 == 1 || opt_1 == 0)) {
						done_1 = true;
					}
					else {
						std::cout << "KINDLY ENTER A VALID OPTION\n";
						std::cin.ignore(std::numeric_limits<std::streamsize> ::max(), '\n');
					}
				} while (!done_1);

				if (opt_1 == 1) {
					add_trains_1("yaba-unilag");
				}
				else {
					display_menu();
				}

			}
			//What happens if the List of trains for that station is not empty---
			else {

				/*
				Then you can choose to
				LIST OF TRAIN:
				----The list of trains and their respective details are shown then the options below come up...
					-- add a new train
					-- remove a train or edit a train

				*/
				system("cls");
				view_trains("yaba-unilag");
				
				

				/*
				WHAT OPERATION WOULD YOU LIKE TO CARRY OUT?
					- REMOVE A TRAIN --- (REMOVE TRAINS.)
					- EDIT A TRAIN	 --- (EDIT DETAILS FOR A TRAIN)
					- ADD A TRAIN
				*/

			}
			
			
			
		}
		break;
		case 2:
		{
			//folder called station which is inside the files
			//then each of the routes have a .txt file
			//thus you can add trains to each of the routes at will


			//If it does not exist, it is created for the first time...
			const char* path = "FILES/STATION_1/yaba-ikorodu.txt";
			std::ofstream out_file(path, std::ios::app);
			out_file.close();
			system("CLS");

			std::ifstream in_file;
			in_file.open(path);

			std::string line;
			std::vector <std::string> lines;

			while (std::getline(in_file, line)) {
				lines.push_back(line);
			}
			in_file.close(); //signifies that you are done reading from the file...

			if (lines.size() == 0) {
				std::cout << "THERE ARE CURRENTLY NO REGISTERED TRAINS\n1 - ADD TRAINS\n0 - RETURN TO HOME MENU\n";

				bool done_1{ false };
				std::string entry_1;
				int opt_1;

				do {
					std::cout << "OPTION: ";
					std::cin >> entry_1;
					std::istringstream validator_1{ entry_1 };

					if (validator_1 >> opt_1 && (opt_1 == 1 || opt_1 == 0)) {
						done_1 = true;
					}
					else {
						std::cout << "KINDLY ENTER A VALID OPTION\n";
						std::cin.ignore(std::numeric_limits<std::streamsize> ::max(), '\n');
					}
				} while (!done_1);

				if (opt_1 == 1) {
					add_trains_1("yaba-ikorodu");
				}
				else {
					display_menu();
				}

			}
			//What happens if the List of trains for that station is not empty---
			else {

				/*
				Then you can choose to
				LIST OF TRAIN:
				----The list of trains and their respective details are shown then the options below come up...
					-- add a new train
					-- remove a train or edit a train

				*/

			}
		}
		break;
		default:
			break;
	}
}

void update_station_2() {

}

void view_trains(std::string route) {

	if (route == "yaba-unilag") {
		std::ifstream in_file;
		const char* path_1 = "FILES/STATION_1/yaba-unilag.txt";
		in_file.open(path_1);
		std::string line;
		

		//TRAIN NO # TRAIN NAME # BOARDING POINT # DESTINATION POINT # F_C_SEATS # F_C_FARE # C_C_SEATS # C_C_FARE
		/*
			std::stringstream s_stream(line);
		std::string substr;
		std::vector<std::string> users;

		while (s_stream.good()) {
			std::getline(s_stream, substr, '#');
			users.push_back(substr);
		}
		
			trains.at(0) = train number
			trains.at(1) = train Name
			trains.at(3) = boarding point
			trains.at(4) = destination point
			trains.at(5) = first class seats
			trains.at(6) = first class fare
			trains.at(7) = commercial seats 
			trains.at(8) = commercial fare
		*/
		std::cout << "=====================================================================================================================================================================" << std::endl;
		std::cout << std::setfill(' ') << std::setw(10) << std::left << "||TRAIN NO"
			<< std::setw(15) << std::left << "| TRAIN NAME"
			<< std::setw(35) << std::left << "| BOARDING POINT" << std::setw(35)<<std::left<<"| DESTINATION POINT"
			<< std::setw(15)<<std::left<<"| 1ST CLASS STS"<<std::setw(15)<<std::left<<"| 1ST CLASS FARE"
			<< std::setw(20)<<std::left<<"| COMMERCIAL SEATS"<<std::setw(20)<<std::left<<"| COMMERCIAL FARE||"<<std::endl;
		std::cout << "====================================================================================================================================================================="<< std::endl;

		while (std::getline(in_file, line)) {
			std::stringstream s_stream(line);
			std::string substr;
			std::vector<std::string> trains;

				while (s_stream.good()) {
					std::getline(s_stream, substr, '#');
					trains.push_back(substr);
				}

		}

		in_file.close();
	}
	else if (route == "yaba-ikorodu") {

	}
}

int get_serialnum() {

	/*const char* path_1 = "FILES/users.txt";
	std::ofstream out_file(path_1, std::ios::app);*/

	std::ifstream in_file;
	const char* path_1 = "FILES/users.txt";
	in_file.open(path_1);

	if (!in_file) {
		std::cerr << "ERROR OPENING users.txt\n\n";
	}

	std::vector < std::string > lines;
	std::string line;
	int size{}, current{};

	while (getline(in_file, line)) {
		lines.push_back(line);
	}
	in_file.close();
	size = lines.size();
	current = size + 1;
	
	return current;
}

void create_user() {
/*
	The details that are required to create a new user are:
	 1 - THE SERIAL NUMBER - Every User has a serial number---
	 2 - Name 
	 3 - Age
	 4 - Category
*/

	int serial_num{}, age{}, count{};
	std::string last_name{}, first_name{}, category{}, sex{};
	std::ofstream out_file;

	system("CLS");
	std::cout << "HOW MANY USERS WOULD YOU LIKE TO CREATE: ";
	
	
	//Data Validation...
	bool done{ false };
	std::string entry;
	do {
		std::cin >> entry;
		std::istringstream validator{ entry };
		if (validator >> count && count >0) {
			done = true;
		}
		else {
			std::cout << "KINDLY ENTER A NUMBER (GREATER THAN 0)\n\n";
			std::cin.ignore(std::numeric_limits<std::streamsize> ::max(), '\n');
		}

	} while (!done);

	

	for (int i{ 0 }; i < count; i++) {
		/*const char* path = "FILES/README.txt";
		std::ofstream out_file(path);
		out_file << "This is the Read me that shows the functionality of this operation---";
		out_file.close();*/

		// "users.txt" --> is the file where the users information are saved...

		//The details that are required to create a new user are :
		//1 - THE SERIAL NUMBER - Every User has a serial number-- -
		//	2 - Name
		//	3 - Age
		//	4 - Sex
		//	5 - Category
		std::cout << "\t\tUSER " << i+1 << std::endl << "=====================================================" << std::endl;
		const char* path_1 = "FILES/users.txt";
		out_file.open(path_1, std::ios::app);
		out_file.close();
	
		out_file.open(path_1, std::ios::app);

		serial_num = get_serialnum();
		out_file << serial_num << "#";

		std::cin.ignore(1, '\n');
		std::cout << "\n\nFIRST NAME: ";
		std::getline(std::cin, first_name);
		first_name = capitalise(first_name);
		out_file << first_name << "#";

		std::cout << "LAST NAME: ";
		std::getline(std::cin, last_name);
		last_name = capitalise(last_name);
		out_file << last_name << "#";

		std::cout << "AGE: ";
		//IMPLEMENT DATA VERIFICATION HERE --- 

		std::string entry_4;
		bool done_4{ false };
		do {
			std::cin >> entry_4;
			std::istringstream validator_4{ entry_4 };

			if (validator_4 >> age && age > 0) {
				done_4 = true;
			}
			else {
				std::cout << "KINDLY ENTER A VALID NUMBER\n\n";
				std::cin.ignore(std::numeric_limits<std::streamsize> ::max(), '\n');
			}
		} while (!done_4);

	
		out_file << age << "#";

		std::cout << "SEX: \n\t1 - MALE\n\t2 - FEMALE\n";
		std::string entry_3;
		bool done_3{ false };
		int opt_3;

		do {
		
			std::cout << "\tOPTION: ";
			std::cin >> entry_3;

			std::istringstream validator_3{ entry_3 };
			if (validator_3 >> opt_3 && (opt_3 == 1 || opt_3 == 2)) {
				done_3 = true;
			}
			else {
				std::cout << "KINDLY ENTER A VALID INPUT\n\n";
				std::cin.ignore(std::numeric_limits<std::streamsize> ::max(), '\n');
			}
		} while (!done_3);
		
		if (opt_3 == 1) {
			sex = "MALE";
		}
		else {
			sex = "FEMALE";
		}
		out_file << sex << "#";


		std::cout << "CATEGORY: \n\t1 - MILITARY\n\t2 - SENIOR CITIZEN\n\t3 - CHILD\n\t4 - NONE\n";
		
		std::string entry_2;
		bool done_2{ false };
		int opt_2{};

		do {
			std::cout << "\tOPTION: ";
			std::cin >> entry_2;
			std::istringstream validator_2{ entry_2 };

			if (validator_2 >> opt_2 && (opt_2 > 0 && opt_2 < 5)) {
				done_2 = true;
			}
			else {
				std::cout << "PLEASE ENTER A VALID INPUT\n\n";
				std::cin.ignore(std::numeric_limits<std::streamsize> ::max(), '\n');
			}
		} while (!done_2);

		switch (opt_2)
		{
			case 1:
			{
				category = "MILITARY";
			}
			break;

			case 2:
			{
				category = "SENIOR CITIZEN";
			}
			break;

			case 3:
			{
				category = "CHILD";
			}
			break;

			case 4:
			{
				category = "NONE";
			}
			break;

			default:
				break;
		}
		out_file << category << std::endl;

		std::cout << first_name << " SUCCESSFULLY ADDED\n\n";

	}
	out_file.close();
}

void list_user() {
	std::string line;

	std::ifstream in_file;
	const char* path = "FILES/users.txt";
	in_file.open(path);
																							
	std::setfill(" ");
	std::cout << "============================================================================\n";
	std::cout<<	std::setfill(' ') << "||" << std::setw(4) << std::left << "S/N" << std::setw(20) << std::left << "FIRST NAME" << std::setw(20) << std::left << "LAST NAME" << std::setw(5) << std::left << "AGE" << std::setw(8) << std::left << "SEX" << std::setw(15) << std::left << "CATEGORY" << "||" << std::endl;
	std::cout << "============================================================================\n";

	while (std::getline(in_file, line)) {
		
		std::stringstream s_stream(line);
		std::string substr;
		std::vector<std::string> users;

		while (s_stream.good()) {
			std::getline(s_stream, substr, '#');
			users.push_back(substr);
		}
		/*
			user.at(0) = Serial Number
			user.at(1) = First Name
			user.at(3) = Last Name
			user.at(4) = Age
			user.at(5) = Sex
			user.at(6) = Category
		*/
		std::cout << "||";
		std::cout << std::setw(4) << std::left << users.at(0) << std::setw(20) << std::left << users.at(1) << std::setw(20) << std::left << users.at(2) << std::setw(5) << std::left << users.at(3) << std::setw(8) << std::left << users.at(4) << std::setw(15) << std::left << users.at(5);
		std::cout << "||"<<std::endl;
	}
	std::cout << "============================================================================\n";

	in_file.close();
}
void reserve() {}
void display_reserves() {}
void display_creserves() {}

void user_mode() {

}

std::string capitalise(std::string word) {
	std::string new_word{};
	for (auto letter : word) {
		letter = toupper(letter);
		new_word+= letter;
	}
	return new_word;
}

void quit() {
	system("CLS");
	std::cout << "\t\t\t\tGOODBYE\n\n\n";
	quitter = '0';
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
