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


void choose_mode();
void display_menu();
void quit();
void admin_mode();
void user_mode();
bool grant_access();
void update_station();
void user_op();
void create_user();
void list_user();
void reserve();
void display_reserves();
void display_creserves();
int	 get_serialnum();

char quitter{ '1'}; //Universal Variable Used to Quit the Application...

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
		std::cout << "1 - UPDATE TRAIN DETAILS\n2 - USER SECTION\n3 - VIEW RESERVATIONS\n4 - GO TO HOME\n";
		
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

void update_station() {
};

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
		out_file << first_name << "#";

		std::cout << "LAST NAME: ";
		std::getline(std::cin, last_name);
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

}
void reserve() {}
void display_reserves() {}
void display_creserves() {}

void user_mode() {

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
