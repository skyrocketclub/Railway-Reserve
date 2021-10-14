// Railway reservation system.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

/*
things to implement

3RD 

RESERVATIONS FUNCTION
beautify the display of reservations already made when a user logs in
--- What should be on display there is the details of the trains that he has reserved
--- the train number, the boarding and destination details and the category...
--- All these details are being displayed from the reservations txt file...


2ND 

MODIFY THE MAKE_RESERVATIONS ASPECT

modify the data that is displayed in the reservations to show the reservations by the train number
Reservations
 --yaba - unilag
	-- train 001 
		-- The name of the user , the boarding & destination details and the category of the user is stored here...
		

1ST

- deduct from available spaces once a reservation is made
	--This is done in the make_reservations section
	--It is done by deducting one from the number of seats once the user confirms his reservation
	--These are done in the trains txt file
	--There is also a function here always brings in the number of seats available at the beginning of the function
	(this is implemented by changing the number in the trains document)
	(It is done during the user making the reservations)

4TH
- implement feature to cancel reservations

5TH
- enable admin to view cancelled reservation

6TH
- give the admin some flexibility so that he does not have to log out everytime

c'est fini
*/

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
void user_op();
void add_trains_1(std::string);
void remove_train_1(std::string);
bool reg_train_1(std::string,std::string);
void create_user();
void list_user();
int verify(int,int);

//FOR THE ADMIN
void reserve();
void display_reserves();
void display_creserves();

//FOR THE USER 
void reservations(std::string,std::string);
void make_reservation(std::string,std::string);
void cancel_reservation(std::string,std::string);
bool check_number(std::string, std::string); // To check if the train number entered by the user is actually there at the moment
std::string fetch_details(std::string, std::string);
int check_f_class_seats(std::string, std::string);
int check_c_class_seats(std::string, std::string);


int	 get_serialnum();
bool check_user(std::string,std::string);
std::string capitalise(std::string);

char quitter{ '1'}; //Universal Variable Used to Quit the Application...

using namespace std;


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
*/
	system("CLS");
	std::cout << "\t\t\tWELCOME TO THE STATIONS SECTIONS. GUIDE THE WORLD TO MOVEMENT\n";
	std::cout << "CHOOSE STATION\n1 - STATION 1 (YABA STATION)\n";

	std::string entry;
	bool done{ false };
	int opt;

	do {
		std::cout << "OPTION: ";
		std::cin >> entry;

		std::istringstream validator{ entry };
		if (validator >> opt && (opt == 1)) {
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

bool reg_train_1(std::string num,std::string route) {

	if (route == "yaba-unilag") {
		bool present{ false };
		std::string line, t_name;

		/*
				trains.at(0) = train number
				trains.at(1) = train Name
				trains.at(2) = boarding point
				trains.at(3) = destination point
				trains.at(4) = first class seats
				trains.at(5) = first class fare
				trains.at(6) = commercial seats
				trains.at(7) = commercial fare
		*/

		std::ifstream in_file;
		const char* path = "FILES/STATION_1/yaba-unilag.txt";
		in_file.open(path);

		if (!in_file) {
			std::cerr << "ERROR OPENING FILE\n\n";
		}

		while (std::getline(in_file, line)) {

			std::stringstream s_stream{ line };
			std::string substr;
			std::vector<std::string> trains;

			while (s_stream.good()) {
				std::getline(s_stream, substr, '#');
				trains.push_back(substr);
			}
			if (num == trains.at(0)) {
				present = true;
			}
		}

		in_file.close();
		return present;
	}
	else if (route == "yaba-ikorodu") {
		bool present{ false };
		std::string line, t_name;

		/*
				trains.at(0) = train number
				trains.at(1) = train Name
				trains.at(2) = boarding point
				trains.at(3) = destination point
				trains.at(4) = first class seats
				trains.at(5) = first class fare
				trains.at(6) = commercial seats
				trains.at(7) = commercial fare
		*/

		std::ifstream in_file;
		const char* path = "FILES/STATION_1/yaba-ikorodu.txt";
		in_file.open(path);

		if (!in_file) {
			std::cerr << "ERROR OPENING FILE\n\n";
		}

		while (std::getline(in_file, line)) {

			std::stringstream s_stream{ line };
			std::string substr;
			std::vector<std::string> trains;

			while (s_stream.good()) {
				std::getline(s_stream, substr, '#');
				trains.push_back(substr);
			}
			if (num == trains.at(0)) {
				present = true;
			}
		}

		in_file.close();
		return present;
	}
	
}

void remove_train_1(std::string route) {

	if (route == "yaba-unilag") {
		retry: std::string number;
		bool present{ false };

		std::cout << "\nENTER THE TRAIN NUMBER OF THE TRAIN TO BE REMOVED\nTRAIN NUMBER: ";
		std::cin >> number;
		present = reg_train_1(number,"yaba-unilag");
		if (present == true) {

			const char* path = "FILES/STATION_1/yaba-unilag.txt";
			const char* path_2 = "FILES/STATION_1/temp.txt";

			std::ifstream in_file;
			in_file.open(path);
			std::ofstream out_file(path_2, std::ios::app);

			std::string line;

				while (std::getline(in_file, line)) {

					std::stringstream s_stream{ line };
					std::string substr;
					std::vector<std::string> trains;

					while (s_stream.good()) {
						std::getline(s_stream, substr, '#');
						trains.push_back(substr);
					}
					if (number == trains.at(0)) {
					
					}
					else {
						out_file << line << std::endl;
					}
				}
			std::cout <<"Train "<<number << " has been successfully deleted!" << std::endl<<std::endl;
			in_file.close();
			out_file.close();
			std::remove(path);
			std::rename(path_2, path);

		}
		else {
			std::cout << number << " IS NOT A REGISTERED TRAIN IN " << route << " ROUTE\n";
			goto retry;
		}
		
	}
	
	else if (route == "yaba-ikorodu") {
	retry_1: std::string number;
		bool present{ false };

		std::cout << "\nENTER THE TRAIN NUMBER OF THE TRAIN TO BE REMOVED\nTRAIN NUMBER: ";
		std::cin >> number;
		present = reg_train_1(number,"yaba-ikorodu");
		if (present == true) {

			const char* path = "FILES/STATION_1/yaba-ikorodu.txt";
			const char* path_2 = "FILES/STATION_1/temp.txt";

			std::ifstream in_file;
			in_file.open(path);
			std::ofstream out_file(path_2, std::ios::app);

			std::string line;

			while (std::getline(in_file, line)) {

				std::stringstream s_stream{ line };
				std::string substr;
				std::vector<std::string> trains;

				while (s_stream.good()) {
					std::getline(s_stream, substr, '#');
					trains.push_back(substr);
				}
				if (number == trains.at(0)) {

				}
				else {
					out_file << line << std::endl;
				}
			}
			std::cout << "Train " << number << " has been successfully deleted!" << std::endl << std::endl;
			in_file.close();
			out_file.close();
			std::remove(path);
			std::rename(path_2, path);

		}
		else {
			std::cout << number << " IS NOT A REGISTERED TRAIN IN " << route << " ROUTE\n";
			goto retry_1;
		}
	}
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
					-- remove a train 

				*/
				system("cls");
				view_trains("yaba-unilag");

				bool done_4{ false };
				std::string entry_4;
				int opt_4;

				std::cout << "1 - ADD A NEW TRAIN\n2 - REMOVE A TRAIN\n3 - GO TO HOME\n";
				do {
					std::cout << "OPTION: ";
					std::cin >> entry_4;

					std::istringstream validator_4{ entry_4 };
					if (validator_4 >> opt_4 &&(opt_4 ==1 || opt_4 ==2||opt_4 ==3)) {
						done_4 = true;
					}
					else {
						std::cout << "KINDLY ENTER A VALID OPTION\n\n";
						std::cin.ignore(std::numeric_limits<std::streamsize> ::max(), '\n');
					}
				} while (!done_4);
				
				if (opt_4 == 1) {
					add_trains_1("yaba-unilag");
				}
				else if(opt_4 ==2){
					remove_train_1("yaba-unilag");
				}
				else {
					display_menu();
				}

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
				system("cls");
				view_trains("yaba-ikorodu");

				bool done_4{ false };
				std::string entry_4;
				int opt_4;

				std::cout << "1 - ADD A NEW TRAIN\n2 - REMOVE A TRAIN\n3 - GO TO HOME\n";
				do {
					std::cout << "OPTION: ";
					std::cin >> entry_4;

					std::istringstream validator_4{ entry_4 };
					if (validator_4 >> opt_4 && (opt_4 == 1 || opt_4 == 2 || opt_4 ==3)) {
						done_4 = true;
					}
					else {
						std::cout << "KINDLY ENTER A VALID OPTION\n\n";
						std::cin.ignore(std::numeric_limits<std::streamsize> ::max(), '\n');
					}
				} while (!done_4);

				if (opt_4 == 1) {
					add_trains_1("yaba-ikorodu");
				}
				else if(opt_4 ==2) {
					remove_train_1("yaba-ikorodu");
				}
				else {
					display_menu();
				}

			}
		}
		break;
		default:
			break;
	}
}

void view_trains(std::string route) {

	if (route == "yaba-unilag") {
		std::ifstream in_file;
		const char* path_1 = "FILES/STATION_1/yaba-unilag.txt";
		in_file.open(path_1);
		std::string line;
		

		//TRAIN NO # TRAIN NAME # BOARDING POINT # DESTINATION POINT # F_C_SEATS # F_C_FARE # C_C_SEATS # C_C_FARE
		/*
			trains.at(0) = train number
			trains.at(1) = train Name
			trains.at(2) = boarding point
			trains.at(3) = destination point
			trains.at(4) = first class seats
			trains.at(5) = first class fare
			trains.at(6) = commercial seats 
			trains.at(7) = commercial fare
		*/
		std::cout << "=====================================================================================================================================================================" << std::endl;
		std::cout << std::setfill(' ') << std::setw(10) << std::left << "|TRAIN NO"
			<< std::setw(15) << std::left << "| TRAIN NAME"
			<< std::setw(35) << std::left << "| BOARDING POINT & TIME" << std::setw(35)<<std::left<<"| DESTINATION POINT & TIME"
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
				std::cout << std::setfill(' ') << std::setw(10) << std::left << trains.at(0)
					<< std::setw(15) << std::left << trains.at(1)
					<< std::setw(38) << std::left << trains.at(2) << std::setw(38) << std::left << trains.at(3)
					<< std::setw(18) << std::left << trains.at(4) << std::setw(15) << std::left << trains.at(5)
					<< std::setw(20) << std::left << trains.at(6) << std::setw(20) << std::left << trains.at(7) << std::endl;
		}
		std::cout << std::endl<<std::endl;
		in_file.close();
	}
	else if (route == "yaba-ikorodu") {
		std::ifstream in_file;
		const char* path_1 = "FILES/STATION_1/yaba-ikorodu.txt";
		in_file.open(path_1);
		std::string line;


		//TRAIN NO # TRAIN NAME # BOARDING POINT # DESTINATION POINT # F_C_SEATS # F_C_FARE # C_C_SEATS # C_C_FARE
		/*
			trains.at(0) = train number
			trains.at(1) = train Name
			trains.at(2) = boarding point
			trains.at(3) = destination point
			trains.at(4) = first class seats
			trains.at(5) = first class fare
			trains.at(6) = commercial seats
			trains.at(7) = commercial fare
		*/
		std::cout << "=====================================================================================================================================================================" << std::endl;
		std::cout << std::setfill(' ') << std::setw(10) << std::left << "|TRAIN NO"
			<< std::setw(15) << std::left << "| TRAIN NAME"
			<< std::setw(35) << std::left << "| BOARDING POINT" << std::setw(35) << std::left << "| DESTINATION POINT"
			<< std::setw(15) << std::left << "| 1ST CLASS STS" << std::setw(15) << std::left << "| 1ST CLASS FARE"
			<< std::setw(20) << std::left << "| COMMERCIAL SEATS" << std::setw(20) << std::left << "| COMMERCIAL FARE||" << std::endl;
		std::cout << "=====================================================================================================================================================================" << std::endl;

		while (std::getline(in_file, line)) {
			std::stringstream s_stream(line);
			std::string substr;
			std::vector<std::string> trains;

			while (s_stream.good()) {
				std::getline(s_stream, substr, '#');
				trains.push_back(substr);
			}
			std::cout << std::setfill(' ') << std::setw(10) << std::left << trains.at(0)
				<< std::setw(15) << std::left << trains.at(1)
				<< std::setw(38) << std::left << trains.at(2) << std::setw(38) << std::left << trains.at(3)
				<< std::setw(18) << std::left << trains.at(4) << std::setw(15) << std::left << trains.at(5)
				<< std::setw(20) << std::left << trains.at(6) << std::setw(20) << std::left << trains.at(7) << std::endl;
		}
		std::cout << std::endl << std::endl;
		in_file.close();
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

void reserve() {
	system("CLS");
	std::cout << "1 - VIEW ALL RESERVATIONS\n2 - VIEW CANCELLED RESERVATIONS\n3 - GO TO HOME\n";
	int option = verify(1, 3);
	if (option == 1) {
		display_reserves();
	}
	else if (option == 2) {
		display_creserves();
	}
	else {
		display_menu();
	}
}
void display_reserves() {
	_mkdir("FILES/RESERVES");
	//The reservations that he has are displayed from both routes
	int count{ 0 };

	const char* path_1 = "FILES/RESERVES/yaba-unilag.txt";
	std::ofstream out_file(path_1, std::ios::app);
	out_file.close();

	std::string line;
	std::ifstream in_file;
	const char* path = "FILES/RESERVES/yaba-unilag.txt";
	in_file.open(path);

	std::setfill(" ");
	std::cout << "\t\tYABA - UNILAG\n";
	std::cout << "===========================================================================================\n";
	std::cout << std::setfill(' ') << "||" << std::setw(4) << std::left << "S/N" << std::setw(20) << std::left << "FIRST NAME" << std::setw(20) << std::left << "LAST NAME" << std::setw(5) << std::left << "AGE" << std::setw(8) << std::left << "SEX" << std::setw(15) << std::left << "CATEGORY" << std::setw(15) << std::left << "CATEGORY" << "||" << std::endl;
	std::cout << "===========================================================================================\n";

	while (std::getline(in_file, line)) {
		count++;
		std::stringstream s_stream(line);
		std::string substr;
		std::vector<std::string> users;

		while (s_stream.good()) {
			std::getline(s_stream, substr, '#');
			users.push_back(substr);
		}
		std::cout << "||";
		std::cout << std::setw(4) << std::left << users.at(0) << std::setw(20) << std::left << users.at(1) << std::setw(20) << std::left << users.at(2) << std::setw(5) << std::left << users.at(3) << std::setw(8) << std::left << users.at(4) << std::setw(15) << std::left << users.at(5) << std::setw(15) << std::left << users.at(6);
		std::cout << "||" << std::endl;
	}
	std::cout << "===========================================================================================\n";

	in_file.close();


	std::cout << std::endl << std::endl;
	std::cout << "\t\tYABA - IKORODU\n";
	const char* path_2 = "FILES/RESERVES/yaba-ikorodu.txt";
	out_file.open(path_2, std::ios::app);
	out_file.close();

	;
	const char* path_3 = "FILES/RESERVES/yaba-ikorodu.txt";
	in_file.open(path_3);

	std::setfill(" ");
	std::cout << "===========================================================================================\n";
	std::cout << std::setfill(' ') << "||" << std::setw(4) << std::left << "S/N" << std::setw(20) << std::left << "FIRST NAME" << std::setw(20) << std::left << "LAST NAME" << std::setw(5) << std::left << "AGE" << std::setw(8) << std::left << "SEX" << std::setw(15) << std::left << "CATEGORY" << std::setw(15) << std::left << "CATEGORY" << "||" << std::endl;
	std::cout << "===========================================================================================\n";

	while (std::getline(in_file, line)) {
		count++;
		std::stringstream s_stream(line);
		std::string substr;
		std::vector<std::string> users;

		while (s_stream.good()) {
			std::getline(s_stream, substr, '#');
			users.push_back(substr);
		}
		std::cout << "||";
		std::cout << std::setw(4) << std::left << users.at(0) << std::setw(20) << std::left << users.at(1) << std::setw(20) << std::left << users.at(2) << std::setw(5) << std::left << users.at(3) << std::setw(8) << std::left << users.at(4) << std::setw(15) << std::left << users.at(5) << std::setw(15) << std::left << users.at(6);
		std::cout << "||" << std::endl;
	}
	std::cout << "===========================================================================================\n";

	in_file.close();

}
void display_creserves() {}

void user_mode() {
	/*
	1 - ASK THE USER FOR HIS FIRST NAME AND HIS LAST NAME AS HIS USERNAME AND PASSWORD
	2 - IF HE IS GRANTED ACCESS, FINE, ELSE HE IS PROMPTED TO TRY AGAIN OR TO REGISTER (THE ADMIN IS CONTROLLING ALL THE TIME
	FROM THE POINT OF VIEW OF THIS APPLICATION)
	3 - 
		SHOW RESERVATION
			MAKE A RESERVATION
			CANCEL RESERVATION
	
	*/
	std::string f_name, l_name;
	bool  status;

	system("CLS");
	std::cout << "\t\tENTER USER DETAILS\n";
	std::cout << "FIRST NAME: ";
	std::cin >> f_name;
	f_name = capitalise(f_name);

	std::cout << "LAST NAME: ";
	std::cin >> l_name;
	l_name = capitalise(l_name);

	status = check_user(f_name, l_name);
	
	if (status == true) {
		system("CLS");
		reservations(f_name,l_name); //your current reservations should be displayed here...

		std::cout << "\n\nWELCOME TO THE ROAD " << f_name << std::endl;
		std::cout << "1 - NEW RESERVATION\n2 - CANCEL RESERVATION\n3 - GO TO HOME\n";

		bool done_r{ false };
		std::string entry_r;
		int opt_r;

		do {
			std::cout << "OPTION: ";
			std::cin >> entry_r;
			std::istringstream validator_r{ entry_r };

			if (validator_r >> opt_r &&(opt_r == 1 || opt_r == 2||opt_r == 3)) {
				done_r = true;
			}
			else {
				std::cout << "KINDLY ENTER A VALID OPTION\n";
				std::cin.ignore(std::numeric_limits<std::streamsize> ::max(), '\n');
			}
		} while (!done_r);

		if (opt_r == 1) {
			make_reservation(f_name,l_name);
		}
		else if (opt_r ==2){
			cancel_reservation(f_name, l_name);
		}
		else {
			display_menu();
		}

	}
	else if(status == false) {
		std::cout << l_name << " " << f_name << " IS NOT REGISTERED" << std::endl;
		std::cout << "WOULD YOU LIKE TO REGISTER " << f_name << " ?\n1 - YES\n2 - N0\n0 - GO TO HOME\n";

		bool done_n{ false };
		std::string entry_n;
		int opt_n;
		do {
			std::cout << "OPTION: ";
			std::cin >> entry_n;
			std::istringstream validator_n{ entry_n };

			if (validator_n >> opt_n && (opt_n == 1 || opt_n == 2)) {
				done_n = true;
			}
			else {
				std::cout << "KINDLY ENTER A VALID OPTION\n";
				std::cin.ignore(std::numeric_limits<std::streamsize> ::max(), '\n');
			}
		} while (!done_n);

		if (opt_n == 1) {
			std::cout << "ENTER THE ADMIN MODE TO REGISTER A NEW CUSTOMER\n\n";
		}
		else {
			display_menu();
		}

	}
}

bool check_user(std::string f_name,std::string l_name) {
	bool status{ false };

	std::ifstream in_file;
	const char* path = "FILES/users.txt";
	in_file.open(path);

	if (!in_file) {
		std::cout << "ERROR OPENING FILE\n\n";
	}
	else {
		std::string line;
		while (std::getline(in_file, line)) {
			std::stringstream s_stream{ line };
			std::vector<std::string> users;
			std::string substr;

			while (s_stream.good()) {
				std::getline(s_stream, substr, '#');
				users.push_back(substr);
			}
			/*
			users.at(0) = serial number
			users.at(1) = first name
			users.at(2) = last name
			users.at(3) = age
			users.at(4) = sex
			users.at(5) = category
			*/
			if (users.at(1) == f_name && users.at(2) == l_name) {
				status = true;
			}
		}

		in_file.close();
	}
	
	return status;
}


//to read the reservations available...
void reservations(std::string f_name, std::string l_name) {
	
	
int count{ 0 };
	bool status_1{ false }, status_2{ false };

	std::ifstream in_file;
	const char* path = "FILES/RESERVES/yaba-unilag.txt";
	in_file.open(path);

	if (!in_file) {
		std::cout << "ERROR OPENING FILE\n\n";
	}
	else {
		std::string line;
		while (std::getline(in_file, line)) {
			std::stringstream s_stream{ line };
			std::vector<std::string> users;
			std::string substr;

			while (s_stream.good()) {
				std::getline(s_stream, substr, '#');
				users.push_back(substr);
			}
			if (users.at(1) == f_name && users.at(2) == l_name) {
				count++;
				status_1 = true; //it means that this user has a reservation for the yaba - unilag trip.
			}
		}
		in_file.close();
	}

	
	const char* path_1 = "FILES/RESERVES/yaba-ikorodu.txt";
	in_file.open(path_1);

	if (!in_file) {
		std::cout << "ERROR OPENING FILE\n\n";
	}
	else {
		std::string line;
		while (std::getline(in_file, line)) {
			std::stringstream s_stream{ line };
			std::vector<std::string> users;
			std::string substr;

			while (s_stream.good()) {
				std::getline(s_stream, substr, '#');
				users.push_back(substr);
			}
			/*
			users.at(0) = serial number
			users.at(1) = first name
			users.at(2) = last name
			users.at(3) = age
			users.at(4) = sex
			users.at(5) = category
			*/
			if (users.at(1) == f_name && users.at(2) == l_name) {
				count++;
				status_2 = true;
			}
		}

		in_file.close();
	}


	if (count == 0) {
		std::cout << "YOU HAVE NO RESERVATIONS YET\n\n";
	}
	else {
		if (status_1 = true) {
			//the user has a reservation for the yaba to unilag train

		}

		if (status_2 = true) {
			//the user has a reservation for the yaba to ikorodu train

		}
	}

}

int verify(int low, int high) {

	std::string entry;
	int option;
	bool done{ false };

	do {
		std::cout << "OPTION: ";
		std::cin >> entry;
		std::istringstream validator{ entry };

		if (validator >> option && (option >=low && option <= high)) {
			done = true;
		}
		else {
			std::cout << "KINDLY ENTER A VALID OPTION\n";
			std::cin.ignore(std::numeric_limits<std::streamsize> ::max(), '\n');
		}
	} while (!done);
	return option;
}

std::string fetch_details(std::string f_name, std::string l_name) {
	bool status{ false };
	std::string chosen;

	std::ifstream in_file;
	const char* path = "FILES/users.txt";
	in_file.open(path);

	if (!in_file) {
		std::cout << "ERROR OPENING FILE\n\n";
	}
	else {
		std::string line;
		while (std::getline(in_file, line)) {
			std::stringstream s_stream{ line };
			std::vector<std::string> users;
			std::string substr;

			while (s_stream.good()) {
				std::getline(s_stream, substr, '#');
				users.push_back(substr);
			}
			/*
			users.at(0) = serial number
			users.at(1) = first name
			users.at(2) = last name
			users.at(3) = age
			users.at(4) = sex
			users.at(5) = category
			*/
			if (users.at(1) == f_name && users.at(2) == l_name) {
				status = true;
				chosen = line;
			}
		}

		in_file.close();
	}
	return chosen;
}

int check_f_class_seats(std::string train_num, std::string route) {
	if (route == "yaba-unilag") {
		const char* path = "FILES/STATION_1/yaba-unilag.txt";
		std::ifstream in_file;
		in_file.open(path);

		std::string line;
		std::string f_seats;
		int f_seat;

		while (std::getline(in_file, line)) {
			std::stringstream s_stream{ line };
			std::vector<std::string> trains;
			std::string substr;

			while (s_stream.good()) {
				std::getline(s_stream, substr, '#');
				trains.push_back(substr);
			}

			if (trains.at(0) == train_num) {
				f_seats = trains.at(4);
				f_seat = stoi(f_seats);
			}
		}

		in_file.close();
		return f_seat;
	}
	else if(route == "yaba-ikorodu") {
		const char* path_1 = "FILES/STATION_1/yaba-ikorodu.txt";
		std::ifstream in_file;
		in_file.open(path_1);

		std::string line;
		std::string f_seats;
		int f_seat;

		while (std::getline(in_file, line)) {
			std::stringstream s_stream{ line };
			std::vector<std::string> trains;
			std::string substr;

			while (s_stream.good()) {
				std::getline(s_stream, substr, '#');
				trains.push_back(substr);
			}

			if (trains.at(0) == train_num) {
				f_seats = trains.at(4);
				f_seat = stoi(f_seats);
			}
		}

		in_file.close();
		return f_seat;
	}
	
}

int check_c_class_seats(std::string train_num, std::string route) {
	if (route == "yaba-unilag") {
		const char* path = "FILES/STATION_1/yaba-unilag.txt";
		std::ifstream in_file;
		in_file.open(path);

		std::string line;
		std::string f_seats;
		int f_seat;

		while (std::getline(in_file, line)) {
			std::stringstream s_stream{ line };
			std::vector<std::string> trains;
			std::string substr;

			while (s_stream.good()) {
				std::getline(s_stream, substr, '#');
				trains.push_back(substr);
			}

			if (trains.at(0) == train_num) {
				f_seats = trains.at(6);
				f_seat = stoi(f_seats);
			}
		}

		in_file.close();
		return f_seat;
	}
	else if (route == "yaba-ikorodu") {
		const char* path_1 = "FILES/STATION_1/yaba-ikorodu.txt";
		std::ifstream in_file;
		in_file.open(path_1);

		std::string line;
		std::string f_seats;
		int f_seat;

		while (std::getline(in_file, line)) {
			std::stringstream s_stream{ line };
			std::vector<std::string> trains;
			std::string substr;

			while (s_stream.good()) {
				std::getline(s_stream, substr, '#');
				trains.push_back(substr);
			}

			if (trains.at(0) == train_num) {
				f_seats = trains.at(6);
				f_seat = stoi(f_seats);
			}
		}

		in_file.close();
		return f_seat;
	}
}

void make_reservation(std::string f_name, std::string l_name) {

	/*
	1ST

- deduct from available spaces once a reservation is made
	--This is done in the make_reservations section
	--It is done by deducting one from the number of seats once the user confirms his reservation
	--These are done in the trains txt file
	--There is also a function here always brings in the number of seats available at the beginning of the function
	(this is implemented by changing the number in the trains document)
	(It is done during the user making the reservations)
	*/

	system("CLS");
	std::cout << "\t\tCHOOSE PREFERRED ROUTE\n";
	std::cout << "1 - YABA - UNILAG\n2 - YABA - IKORODU\n";


	bool done_r{ false };
	std::string entry_r;
	int opt_r;

	do {
		std::cout << "OPTION: ";
		std::cin >> entry_r;
		std::istringstream validator_r{ entry_r };

		if (validator_r >> opt_r && (opt_r == 1 || opt_r == 2)) {
			done_r = true;
		}
		else {
			std::cout << "KINDLY ENTER A VALID OPTION\n";
			std::cin.ignore(std::numeric_limits<std::streamsize> ::max(), '\n');
		}
	} while (!done_r);

	if (opt_r == 1) {
		view_trains("yaba-unilag");
		num_retry: std::cout << "ENTER THE TRAIN NUMBER: ";
		std::string train_num;
		std::cin >> train_num;
		
		bool done_train{ false };


		int f_class_seats, c_class_seats;
		f_class_seats = check_f_class_seats(train_num, "yaba-unilag");
		c_class_seats = check_c_class_seats(train_num, "yaba-unilag");

		do {
			bool train_status = check_number(train_num, "yaba-unilag");
			if (train_status == true) {
				done_train = true;
				std::cout << "TYPE OF RESERVATION\n1 - FIRST CLASS\n2 - COMMERCIAL\n3 - GO TO HOME\n";
				int choice = verify(1, 3);//Data validation is now done in this line of code...
				if (choice == 1) {
					//his details will be fetched and the the type of reservation will be attached...
					if (f_class_seats > 0) {

						std::cout << "\nFIRST CLASS RESERVATION SUCCESSFULL\n";
						//his details will be fetched and the the type of reservation will be attached...
						const char* path_1 = "FILES/RESERVES/yaba-unilag.txt";
						std::ofstream out_file(path_1, std::ios::app);

						std::string details;
						details = fetch_details(f_name, l_name);
						out_file << details << "#" << "FIRST CLASS" << std::endl;

						out_file.close();
					}
					else {
						std::cout << "SORRY THERE ARE NO SPACES LEFT" << std::endl;
						std::cout << "1 - TRY ANOTHER TRAIN\n2 - GO TO HOME\n";
						int relieve = verify(1, 2);
						if (relieve == 1) {
							goto num_retry1;
						}
						else {
							display_menu();
						}
					}
				}
				else if(choice == 2){
					if (c_class_seats > 0) {

						std::cout << "\nFIRST CLASS RESERVATION SUCCESSFULL\n";
						//his details will be fetched and the the type of reservation will be attached...
						const char* path_1 = "FILES/RESERVES/yaba-unilag.txt";
						std::ofstream out_file(path_1, std::ios::app);

						std::string details;
						details = fetch_details(f_name, l_name);
						out_file << details << "#" << "FIRST CLASS" << std::endl;

						out_file.close();
					}
					else {
						std::cout << "SORRY THERE ARE NO SPACES LEFT" << std::endl;
						std::cout << "1 - TRY ANOTHER TRAIN\n2 - GO TO HOME\n";
						int relieve = verify(1, 2);
						if (relieve == 1) {
							goto num_retry1;
						}
						else {
							display_menu();
						}
					}
				}
				else {
					display_menu();
				}
			}
			else {
				std::cout << train_num << " IS NOT A VALID TRAIN IN THIS ROUTE\n";
				std::cout << "1 - ENTER ANOTHER TRAIN NUMBER\n2 - GO TO HOME\n";

				//Data Validation...
				bool done{ false };
				std::string entry;
				int num;
				do {
					std::cout << "OPTION: ";
					std::cin >> entry;
					std::istringstream validator{ entry };
					if (validator >> num && (num==1 ||num == 2)) {
						done = true;
					}
					else {
						std::cout << "KINDLY ENTER A VALID INPUT\n\n";
						std::cin.ignore(std::numeric_limits<std::streamsize> ::max(), '\n');
					}

				} while (!done);
				if (num == 1) {
					goto num_retry;
				}
				else {
					done = true;
					display_menu();
				}

			}
		} while (!done_train);
		
	}
	else {
		view_trains("yaba-ikorodu");
		
		/*
		Then you ask the user
		1 - enter the train number
		2 - first class or commercial?
		3 - Then the fee is shown and the user is asked if he/she would like to continue
		4 - Then If he does so... The data of the user is added to the reservations
		5 - Then the details of the train is updated...
		*/
	num_retry1: std::cout << "ENTER THE TRAIN NUMBER: ";
		std::string train_num;
		std::cin >> train_num;

		bool done_train{ false };

		do {
			bool train_status = check_number(train_num, "yaba-ikorodu");
			if (train_status == true) {
				//check the number of first class and commercial class seats available here...

				int f_class_seats, c_class_seats;
				f_class_seats = check_f_class_seats(train_num, "yaba-ikorodu");
				c_class_seats = check_c_class_seats(train_num, "yaba-ikorodu");

				done_train = true;
				std::cout << "TYPE OF RESERVATION\n1 - FIRST CLASS\n2 - COMMERCIAL\n3 - GO TO HOME\n";
				int choice = verify(1, 3);//Data validation is now done in this line of code...
				if (choice == 1) {
					//check if there are enough first class seats here...
					if (f_class_seats > 0) {

						std::cout << "\nFIRST CLASS RESERVATION SUCCESSFULL\n";
						//his details will be fetched and the the type of reservation will be attached...
						const char* path_1 = "FILES/RESERVES/yaba-ikorodu.txt";
						std::ofstream out_file(path_1, std::ios::app);

						std::string details;
						details = fetch_details(f_name, l_name);
						out_file << details << "#" << "FIRST CLASS" << std::endl;

						out_file.close();
					}
					else {
						std::cout << "SORRY THERE ARE NO SPACES LEFT" << std::endl;
						std::cout << "1 - TRY ANOTHER TRAIN\n2 - GO TO HOME\n";
						int relieve = verify(1, 2);
						if (relieve == 1) {
							goto num_retry1;
						}
						else {
							display_menu();
						}
					}

				}
				else if (choice == 2) {
					// check if there are enough commercial class seats here........
					//check if there are enough first class seats here...
						if (c_class_seats > 0) {

							std::cout << "\nFIRST CLASS RESERVATION SUCCESSFULL\n";
							//his details will be fetched and the the type of reservation will be attached...
							const char* path_1 = "FILES/RESERVES/yaba-ikorodu.txt";
							std::ofstream out_file(path_1, std::ios::app);

							std::string details;
							details = fetch_details(f_name, l_name);
							out_file << details << "#" << "FIRST CLASS" << std::endl;

							out_file.close();
						}
						else {
							std::cout << "SORRY THERE ARE NO SPACES LEFT" << std::endl;
							std::cout << "1 - TRY ANOTHER TRAIN\n2 - GO TO HOME\n";
							int relieve = verify(1, 2);
							if (relieve == 1) {
								goto num_retry1;
							}
							else {
								display_menu();
							}
						}
				}
				else {
					display_menu();
				}
				
				if (choice != 3) {
					//deduct from the train here.......CONTINUE FROM HERE
				}
			}
			else {
				std::cout << train_num << " IS NOT A VALID TRAIN IN THIS ROUTE\n";
				std::cout << "1 - ENTER ANOTHER TRAIN NUMBER\n2 - GO TO HOME\n";

				//Data Validation...
				bool done{ false };
				std::string entry;
				int num;
				do {
					std::cout << "OPTION: ";
					std::cin >> entry;
					std::istringstream validator{ entry };
					if (validator >> num && (num == 1 || num == 2)) {
						done = true;
					}
					else {
						std::cout << "KINDLY ENTER A VALID INPUT\n\n";
						std::cin.ignore(std::numeric_limits<std::streamsize> ::max(), '\n');
					}

				} while (!done);
				if (num == 1) {
					goto num_retry1;
				}
				else {
					done = true;
					display_menu();
				}

			}
		} while (!done_train);

	}

	/*
	1 - The reservations are in terms of the trains...
	2 - They are stored in a folder...
	3 - When a user logs in, his reservations are displayed
	4 - If he has no reservations, it is displayed there as well...
	*/
}

bool check_number(std::string train_no, std::string route) {
	
	if (route == "yaba-unilag") {
		std::string line;
		bool status{ false };

		const char* path_1 = "FILES/STATION_1/yaba-unilag.txt";
		std::ifstream in_file;
		in_file.open(path_1);

		while (std::getline(in_file, line)) {
			std::vector<std::string> trains;
			std::string substr;
			std::stringstream s_stream{ line };

			while (s_stream.good()) {
				std::getline(s_stream, substr, '#');
				trains.push_back(substr);
			}
			if (train_no == trains.at(0)) {
				status = true;
			}
		}

		in_file.close();
		return status;
	}
	else if (route == "yaba-ikorodu") {
		std::string line;
		bool status{ false };

		const char* path_1 = "FILES/STATION_1/yaba-ikorodu.txt";
		std::ifstream in_file;
		in_file.open(path_1);

		while (std::getline(in_file, line)) {
			std::vector<std::string> trains;
			std::string substr;
			std::stringstream s_stream{ line };

			while (s_stream.good()) {
				std::getline(s_stream, substr, '#');
				trains.push_back(substr);
			}
			if (train_no == trains.at(0)) {
				status = true;
			}
		}

		in_file.close();
		return status;
	}
}

void cancel_reservation(std::string f_name, std::string l_name) {
	
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
