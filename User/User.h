#pragma once
#include <string>
#include <iostream>

using namespace std;

class User {
private:
	string name;
	string password;
public:
	// constructor
	User(string name, string password);
	User();

	// get set
	void setName(string name);
	string getName();
	void setPassword(string password);
	string getPassword();
};

