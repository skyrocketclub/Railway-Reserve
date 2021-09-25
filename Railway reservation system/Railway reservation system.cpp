// Railway reservation system.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <direct.h>
#include <stdlib.h>
#include <stdio.h>
#include <iomanip>


void choose_mode();
void display_menu();
void quit();

char quitter{ '1'};

int main()
{
	std::cout <<std::setw(50)<< "RAILWAY RESERVATION SYSTEM" << std::endl;
	std::cout << std::setw(75) << std::setfill('=') << " " << std::endl;
	display_menu();

	return 0;
}



void display_menu() {
	if (quitter != '0') {
		std::cout << "WHAT OPERATION WOULD YOU LIKE TO CARRY OUT\m1 - CHOOSE MODE\n2 - QUIT\nOPTION: ";
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
		}
	} while (!done);

	
}

void quit() {
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
