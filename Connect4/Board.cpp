#include<iostream>
using namespace std;

enum Cell {
	Empty,
	Red,
	Blue
};
class Board {
	Cell cell;
	public:
	Board(){
		cell = Empty;
	}
	void setCellValue(Cell cell) {
		this->cell = cell;
	}
	Cell getCellValue() {
		return cell;
	}
};
