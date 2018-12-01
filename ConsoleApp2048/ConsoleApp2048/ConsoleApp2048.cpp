// ConsoleApp2048.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<iomanip>

#include <stack>
#include <vector>

using namespace std;

int score = 0;

enum axis { x, y };

class play {
	int game[4][4];
	void initialize();
	void display();
	void move_up();
	void move_down();
	void move_left();
	void move_right();
	int check_full();
	int random_index(int x);
	void generate_new_index();
	int get_max_value();
	int game_ends();
	void game_line();
	void pull_row_minus(int line, axis axis);
	void pull_row_plus(int line, axis axis);
	bool handle_pull(int pos1, int pos2, int static_pos, axis axis);

public:
	void play_game();
	play() {}
};

int play::random_index(int x) {
	int index;
	index = rand() % x;
	return index;
}

int play::check_full() {
	int full_flag = 1;
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			if (game[x][y] == 0) {
				return 0;
			}
		}
	}
	return 1;
}

int play::get_max_value() {
	int max = 0;
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			if (game[x][y] > max) {
				max = game[x][y];
			}
		}
	}
	return max;
}

int play::game_ends() {
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 3; x++) {
			if (game[x][y] == game[x][y + 1]) {
				return 0;
			}
		}
	}
	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 4; x++) {
			if (game[x][y] == game[x + 1][y]) {
				return 0;
				break;
			}
		}
	}
	return 1;
}


void play::generate_new_index() {
	if (!check_full()) {
		while (true) {
			int y = random_index(4);
			int x = random_index(4);
			if (game[x][y] == 0) {
				int y = rand() % 10 + 0;
				if (y < 6) {
					game[x][y] = 2;
				}
				else {
					game[x][y] = 4;
				}
				break;
			}
		}
	}
}

void play::initialize() {
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			game[x][y] = 0;
		}
	}
	int y = random_index(4);
	int x = random_index(4);
	game[x][y] = 2;
	y = random_index(4);
	x = random_index(4);
	game[x][y] = 2;
	display();
}


// MAIN LOGIC
void play::pull_row_plus(int line, axis axis) {
	for (int a = 0; a < 4; a++) {
		for (int b = a + 1; b < 4; b++) {
			if (!handle_pull(a, b, line, axis)) {
				break;
			}
		}
	}
}

void play::pull_row_minus(int line, axis axis) {
	for (int a = 3; a >= 0; a--) {
		for (int b = a - 1; b >= 0; b--) {
			if (!handle_pull(a, b, line, axis)) {
				break;
			}
		}
	}
}

bool play::handle_pull(int base_pos, int pull_pos, int static_pos, axis axis) {
	if (axis == x) {	// At X the Y is static
		if (game[pull_pos][static_pos]) {	// Check pull position is set
			if (!game[base_pos][static_pos]) {	// Check if base position is 0
				game[base_pos][static_pos] = game[pull_pos][static_pos];
				game[pull_pos][static_pos] = 0;
				return true;
			}
			else {
				if (game[base_pos][static_pos] == game[pull_pos][static_pos]) {
					game[base_pos][static_pos] += game[pull_pos][static_pos];
					game[pull_pos][static_pos] = 0;
					score += game[base_pos][static_pos];
					return true;
				}
				else {
					return false;
				}
			}
		}
	}
	else if (axis == y) {	// At Y the X is static
		if (game[static_pos][pull_pos]) {	// Check pull position is set
			if (!game[static_pos][base_pos]) {	// Check if base position is 0
				game[static_pos][base_pos] = game[static_pos][pull_pos];
				game[static_pos][pull_pos] = 0;
				return true;
			}
			else {
				if (game[static_pos][base_pos] == game[static_pos][pull_pos]) {
					game[static_pos][base_pos] += game[static_pos][pull_pos];
					game[static_pos][pull_pos] = 0;
					score += game[static_pos][pull_pos];
					return true;
				}
				else {
					return false;
				}
			}
		}
	}
}
// END MAIN LOGIC

void play::move_left() {
	for (int y = 0; y < 4; y++) {
		pull_row_plus(y, x);
	}
}

void play::move_right() {
	for (int y = 0; y < 4; y++) {
		pull_row_minus(y, x);
	}
}

void play::move_up() {
	for (int x = 0; x < 4; x++) {
		pull_row_plus(x, y);
	}
}


void play::move_down() {
	for (int x = 0; x < 4; x++) {
		pull_row_minus(x, y);
	}
}


void play::play_game() {
	char choice, ch;
	initialize();
	cin >> choice;

	while ((choice == 'w' || choice == 'a' || choice == 's' || choice == 'd')) {
		switch (choice) {
			//move up
			case 'w':
				move_up();
				generate_new_index();
				system("clear");
				display();
				break;
			//move down
			case 's':
				move_down();
				generate_new_index();
				system("clear");
				display();
				break;
			//move left
			case 'a':
				move_left();
				generate_new_index();
				system("clear");
				display();
				break;
			//move right
			case 'd':
				move_right();
				generate_new_index();
				system("clear");
				display();
				break;
		}
		//check if any block of matrix reached to value = 2048
		int find_max = get_max_value();
		if (find_max == 2048) {
			cout << "\n\nGame won!" << endl;
		}
		if (check_full()) {
			if (game_ends()) {
				cout << "\n\nToo bad restart and try again" << endl;
			}
		}
		cin >> choice;
		while (choice != 'w'  && choice != 's'  && choice != 'd'  && choice != 'a') {
			cout << "\nPlease hit WASD to make a move!" << endl;
			cin >> choice;
		}
	}
}

void play::display() {
	cout << "\n\nScore: " << score << endl;
	cout << "Max value: " << get_max_value() << endl << endl;
	for (int y = 0; y < 4; y++) {
		game_line();
		cout << "       |";
		for (int x = 0; x < 4; x++) {
			cout << setw(4) << game[x][y] << setw(4) << "|" << setw(4);
		}
		cout << endl;
	}
	game_line();
	cout << "\n\n\n";
	cout << "\n\tw\na\ts\td" << endl << endl;
	cout << "Enter 1 move Up (W) / Left(A) / Down(S) or Right(D) and hit enter: " << endl;
}

void play::game_line() {
	cout << "       |";
	for (int a = 0; a < 4; a++) {
		cout << "-------" << "|" << setw(4);
	}
	cout << endl;
}

int main() {
	play p;
	srand(time(NULL));
	p.play_game();
	return 0;
}