#pragma once
#include <string>
#include <iostream>

using namespace std;

class User {
private:
	string name;
	string password;
	int score;
public:
	// constructor
	User(string name, string password);
	User();

	User(string name, int score) : name(name), score(score) {};
	// get set
	void setName(string name);
	string getName();
	void setPassword(string password);
	string getPassword();
	void setScore(int score) { this->score = score; }
	int getScore() { return score; }

};

