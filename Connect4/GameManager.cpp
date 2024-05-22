#include<iostream>
#include "Board.cpp"
using namespace std;

enum GameState {
	Playing,
	Draw,
	RedWin,
	BlueWin
};
class GameManager {
	private:
	char ch;
	public:
	bool playerOneTurn;
	int maxRows;
	int maxColumns;
	int maxCount;
	int *columnContentCount;
	GameState gamestate;
	Board **board;
	GameManager() {
		playerOneTurn = true;
		maxRows = 6;
		maxColumns = 7;
		maxCount = 4;
		setGameState(Playing);
		columnContentCount = new int[maxColumns]();
		board = new Board *[maxRows];
		for (int i = 0; i < maxRows; i++) {
			board[i] = new Board[maxColumns];
		}
	}
	void setGameState(GameState gamestate) {
		this->gamestate = gamestate;
	}
	GameState getGameState() {
		return gamestate;
	}

	void displayWelcome() {
		cout << "   -------------------------------------------------------------------" << endl;
		cout << "   |""                                                                 ""|" << endl;
		cout << "   |""                WELCOME TO CONNECT-4 GAME                        ""|" << endl;
		cout << "   |""                                                                 ""|" << endl;
		cout << "   -------------------------------------------------------------------" << endl;
		
	}
	void instructions() {
		cout << endl;
		cout <<"    *****GAME INSTRUCTIONS*****    " << endl;
		cout <<"    1. Two-player (red & blue) game." << endl;
		cout <<"    2. Board size is 6 rows × 7 columns." << endl;
		cout <<"    3. A player wins if he/she is able to connect 4 dots horizontally, vertically or diagonally." << endl;
		cout <<"    4. Draw when the matrix is fully filled." << endl;
		cout <<"    5. Game always starts with the player - 1 i.e. Red(R)." << endl;
		cout <<"    6. In each step, each player can choose the column number in which they want to drop the ball. " << endl;
		cout <<"    7. Rows will be filled from bottom to top in any column." << endl;
	}
	bool gameChoice() {
		bool isGameStarted = false;
		cout << endl;
		cout <<"    Enter y/Y to start game or N/n to close game." << endl;
		cout << "    ";
		cin>> ch;
		if (ch == 'y' || ch == 'Y') {
			isGameStarted = true;
		}
		else if (ch == 'n' || ch == 'N') {
			cout <<"   Exited successfully" << endl;
			exit(0);
		}
		else {
			cout <<"   Invalid input" << endl;
			cout <<"   Please enter correct input." << endl;
			gameChoice();
		}
		return isGameStarted;
	}
	void displayStartMessage() {
		cout << "   -------------------------------------------------------------------" << endl;
		cout << "   |""                                                                 ""|" << endl;
		cout << "   |""***************************GAME STARTED**************************""|" << endl;
		cout << "   |""                                                                 ""|" << endl;
		cout << "   -------------------------------------------------------------------" << endl;
		cout << endl << endl;
	}

	bool isPlayer1() {
		return playerOneTurn;
	}
	void displayBoard() {
		for (int i = 0; i < maxColumns; i++) {
			cout <<"      ";
			cout << i + 1 ;
		}
		cout << endl;
		
		for (int i = 0; i < maxRows; i++) {
			cout << "     -------------------------------------------------" << endl;
			for (int j = 0; j < maxColumns; j++) {
				
				switch (board[i][j].getCellValue()) {
				case Empty:
					cout << "     | ";
					break;
				case Red:
					cout << "     |R";
					break;
				case Blue:
					cout << "     |B";
					break;
				}

			}
			cout << "     |" << endl;
		}
		cout << "     -------------------------------------------------" << endl;
		cout << endl;
	}
	bool InsertCoin(int column, bool playerOne) {
		if (columnContentCount[column] == maxRows) {
			cout << "    Column is full.Please enter other number..." << endl;
			return false;
		}
		Cell cellValue;
		if (playerOne) {
			cellValue = Red;
		}
		else {
			cellValue = Blue;
		}
		if (board[(maxRows - 1) - columnContentCount[column]][column].getCellValue() == Empty) {
			board[(maxRows - 1) - columnContentCount[column]][column].setCellValue(cellValue);
		}
		if (checkWin((maxRows - 1) - columnContentCount[column], column, cellValue)) {
			if (playerOne) {
				setGameState(RedWin);
			}
			else {
				setGameState(BlueWin);
			}
		}
		columnContentCount[column]++;
		return true;
	}
	void changeTurn() {
		playerOneTurn = !playerOneTurn;
	}
	void checkDraw() {
		for (int i = 0; i < maxColumns; i++) {
			if (columnContentCount[i] != maxRows) {
				return;
			}
		}
		setGameState(Draw);
		return;
	}
	bool checkVertical(int row, int col, Cell cellValue) {
		int count = 0;
		for (int i = 0; i < maxRows; i++) {
			if (board[i][col].getCellValue() == cellValue) {
				count++;
			}
			else {
				count = 0;
			}
			if (count == maxCount) {
				return true;
			}
		}
		return false;
	}
	bool checkHorizontal(int row, int col, Cell cellValue) {
		int count = 0;
		for (int i = 0; i < maxColumns; i++) {
			if (board[row][i].getCellValue() == cellValue) {
				count++;
			}
			else {
				count = 0;
			}
			if (count == maxCount) {
				return true;
			}
		}
		return false;
	}
	bool checkDiagonal(int row, int col, Cell cellValue) {
		int count = 0;
		//Diagonal left top
		for (int i = row, j = col; i > 0&& j > 0; i--, j--) {
			if (board[i][j].getCellValue() == cellValue) {
				count++;
			}
			else {
				break;
			}
			if (count == maxCount) {
				return true;
			}
		}
		if (count != 0) {
			count--;
		}
		//Diagonal right bottom
		for (int i = row, j = col; i < maxRows && j < maxColumns; i++, j++) {
			if (board[i][j].getCellValue() == cellValue) {
				count++;
			}
			else {
				break;
			}
			if (count == maxCount) {
				return true;
			}
		}
		count = 0;
		//Right-top
		for (int i = row, j = col; i >= 0 && j < maxColumns; i--, j++) {
			if (board[i][j].getCellValue() == cellValue) {
				count++;
			}
			else {
				break;
			}
			if (count == maxCount) {
				return true;
			}

		}
		if (count != 0) {
			count--;
		}
		//left-bottom
		for (int i = row, j = col; i < maxRows && j >= 0; i++, j--) {
			if (board[i][j].getCellValue() == cellValue) {
				count++;
			}
			else {
				break;
			}
			if (count == maxCount) {
				return true;
			}

		}
		return false;
	}
	bool checkWin(int row, int col, Cell cellValue) {
		if (checkVertical(row, col, cellValue) || checkHorizontal(row, col, cellValue) || checkDiagonal(row, col, cellValue)) {
			return true;
		}
		else {
			return false;
		}
	}
	bool gameStatus() {
		if (getGameState() != Playing) {
			switch (getGameState()) {
				case RedWin:
					cout << "     Player Red Won!!" << endl;
					return true;
					//break;
				case BlueWin:
					cout << "     Player Blue Won!!" << endl;
					return true;
				case Draw:
					cout << "     Game is Draw!!" << endl;
					return true;
			}
		}
	}
};
