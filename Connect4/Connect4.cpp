// Connect4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "GameManager.cpp";
using namespace std;

int main()
{
	
	int col = 1;
	GameManager gameManager;
	gameManager.displayWelcome();
	gameManager.instructions();
	bool choice = gameManager.gameChoice();
	if (choice) {
		system("cls");
		gameManager.displayStartMessage();
		gameManager.displayBoard();
		while (true) {
			do {
				if (col<1 || col>gameManager.maxColumns) {
					cout << "    Please enter valid input" << endl;
				}
				if (gameManager.isPlayer1()) {
					cout <<"    Player - 1 (R)" << endl;
				}
				else {
					cout <<"    Player - 2 (B)" << endl;
				}
				cout <<"    Enter a Column no (1-7) : " << endl;
				cout << "    ";
				cin >> col;
			} while (col<1 || col>gameManager.maxColumns);
			if (!gameManager.InsertCoin(col - 1, gameManager.isPlayer1())) {
				continue;
			}
			system("cls");
			gameManager.displayBoard();
			gameManager.checkDraw();
			if (gameManager.gameStatus()) {
				break;
			}
			gameManager.changeTurn();
		}
	}
	

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
